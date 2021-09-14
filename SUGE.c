/**
 * Name: SUGE.c v2.3.1
 * Date: 2021-09-12
 * Intro: A lib to simulate astronomical phenomenons.
 * Update: Allows two colors to display clearly, now supports v4.
 * Open configure file SUGE by default, which can be appointed by cmd argument:
 *		ver: 2/3/4
 *		number: Numbers of celestial bodies
 *		X position (a list of length number)
 *		Y position (a list of length number)
 *		X velocity (a list of length number)
 *		Y velocity (a list of length number)
 *		Quality (a list of length number)
 *		[Added: v3] Width (a list of length number)
 *		[Deprecated: v4] Foreground color (a list of length number in hex BBGGRR)
 *		[Added: v4] Foreground color #1
 *		[Added: v4] Foreground color #2
 *		Background color
 *		Simulate accuracy
 *		Display frequent (ticks in each frame)
 *		[Deprecated: v3] Width
 *		[Added: v4] Switch (frames in each switching colors)
 *		X/Y offset
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define TITLE "SUGE"
COLORREF BACKGROUND_COLOR;

#include "gdiTemplate.c"

#ifdef _SIMULATOR_USE_OMP
#include <omp.h>
#endif

int version, number, displayFreq, switchTicks = 1, offset[2], ticks, i, parity;
double simulateAcc;
LPSTR fileName = "SUGE";
DWORD WINAPI threadProc(LPVOID lpParamter) {
	FILE *file = fopen(fileName, "r");
	HWND hwnd = (HWND)lpParamter;
	fscanf(file, "%d%d", &version, &number);
	HDC hdc[number][2];
	HPEN hpen[number][2];
	double position[number][2], velocity[number][2], quality[number];
	int width[number];
	COLORREF color[number][2];
	if(version==2 || version==3 || version==4) {
		for(i=0; i<number; ++i) fscanf(file, "%lf", &position[i][0]);
		for(i=0; i<number; ++i) fscanf(file, "%lf", &position[i][1]);
		for(i=0; i<number; ++i) fscanf(file, "%lf", &velocity[i][0]);
		for(i=0; i<number; ++i) fscanf(file, "%lf", &velocity[i][1]);
		for(i=0; i<number; ++i) fscanf(file, "%lf", &quality[i]);
		if(version >= 3) for(i=0; i<number; ++i) fscanf(file, "%d", &width[i]);
		for(i=0; i<number; ++i) fscanf(file, "%lx", &color[i][0]);
		if(version < 4) for(i=0; i<number; ++i) color[i][1] = color[i][0];
		else for(i=0; i<number; ++i) fscanf(file, "%lx", &color[i][1]);
		fscanf(file, "%lx %lf %d", &BACKGROUND_COLOR, &simulateAcc, &displayFreq);
		if(version == 2) {
			fscanf(file, "%d", &width[0]);
			for(i=0; i<number; ++i) width[i] = width[0];
		} else if(version == 4) {
			fscanf(file, "%d", &switchTicks);
		}
		fscanf(file, "%d %d", &offset[0], &offset[1]);
		
	} else {
		printf("Version not support: %d", version);
		return 1;
	}
	fclose(file);
	for(i=0; i<number; ++i) {
		position[i][0] += offset[0];
		position[i][1] += offset[1];
		velocity[i][0] *= simulateAcc;
		velocity[i][1] *= simulateAcc;
		quality[i] *= simulateAcc * simulateAcc;
	}
	switchTicks *= displayFreq;
	for(i=0; i<number; ++i) {
		int j;
		for(j=0; j<2; ++j) {
			hdc[i][j] = GetDC(hwnd);
			hpen[i][j] = CreatePen(PS_SOLID, width[i], color[i][j]);
			SelectObject(hdc[i][j], hpen[i][j]);
			MoveToEx(hdc[i][j], position[i][0], position[i][1], 0);
		}
	}
	while(1) {
#ifdef _SIMULATOR_USE_OMP
#pragma omp parallel for
#endif
		for(i=0; i<number; ++i) {
			int j;
			for(j=0; j<i; ++j) {
				double distance_neg3, differenceX, differenceY, quality_j_distance_neg3, quality_i_distance_neg3;
				differenceX = position[j][0] - position[i][0];
				differenceY = position[j][1] - position[i][1];
				if(differenceX==0 && differenceY==0) continue;
				distance_neg3 = pow(differenceX * differenceX + differenceY * differenceY, -1.5);
				quality_j_distance_neg3 = quality[j] * distance_neg3;
				quality_i_distance_neg3 = quality[i] * distance_neg3;
				velocity[i][0] += differenceX * quality_j_distance_neg3;
				velocity[i][1] += differenceY * quality_j_distance_neg3;
				velocity[j][0] -= differenceX * quality_i_distance_neg3;
				velocity[j][1] -= differenceY * quality_i_distance_neg3;
			}
		}
		if(ticks % displayFreq == 0) {
			parity = (ticks / switchTicks) & 1;
			for(i=0; i<number; ++i) {
				LineTo(hdc[i][parity], position[i][0], position[i][1]);
				MoveToEx(hdc[i][parity^1], position[i][0], position[i][1], 0);
			}
		}
		for(i=0; i<number; ++i) {
			position[i][0] += velocity[i][0];
			position[i][1] += velocity[i][1];
		}
		++ticks;
	}
}

int WINAPI initProc(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR pCmdLine, int nCmdShow) {
	if(strlen(pCmdLine) != 0) {
		fileName = pCmdLine;
	}
	return 0;
}

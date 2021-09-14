/* Name: gdiTemplate.c v0.0.1
 * Date: 2021-09-12
 * Intro: Generates a random sky map every 5 seconds.
 * Update: Modify to adapt new initialize function.
 */
#include <stdlib.h>

#define BACKGROUND_COLOR 0x000000
#define TITLE "Test"
#include "gdiTemplate.c"

DWORD WINAPI threadProc(LPVOID lpParamter) {
	int i, j;
	HWND hwnd = (HWND) lpParamter;
	HDC hdc = GetDC(hwnd);
	RECT rect;
	while(1) {
		GetWindowRect(hwnd, &rect);
		for(i=rect.left; i<rect.right; ++i) {
			for(j=rect.top; j<rect.bottom; ++j) {
				if(rand() & 255) {
					SetPixel(hdc, i, j, BACKGROUND_COLOR);
				} else {
					SetPixel(hdc, i, j, (rand() * 0x010101));
				}
			}
		}
		Sleep(5000);
	}
	return 0l;
}

int WINAPI initProc(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR pCmdLine, int nCmdShow) {}

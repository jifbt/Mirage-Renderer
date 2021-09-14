/* Name: gdiTemplate.c v0.1.0
 * Date: 2021-09-12
 * Intro: A lib to use gdi with c easier.
 * Update: Now initialize function allowed.
 */
#include <windows.h>
#include "gdiTemplate.h"

#if _GDITEMPLATE_H != 0x000100
#error Version not support
#endif

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch(uMsg) {
		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc2 = BeginPaint(hwnd, &ps);
			FillRect(hdc2, &ps.rcPaint, CreateSolidBrush(BACKGROUND_COLOR));
			EndPaint(hwnd, &ps);
			return 0;
		}
		case WM_CREATE: {
			HANDLE hThread = CreateThread(NULL, 0, threadProc, (LPVOID) hwnd, 0, NULL);
	    	CloseHandle(hThread);
			return 0;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR pCmdLine, int nCmdShow) {
	initProc(hInstance, prevInstance, pCmdLine, nCmdShow);
	const char *CLASS_NAME = "GDITEMPLATE";
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	RegisterClass(&wc);
	HWND hwnd = CreateWindowEx(0, CLASS_NAME, TITLE, 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
		CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	if(hwnd == NULL) return 0;
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
	MSG msg = {};
	while(GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

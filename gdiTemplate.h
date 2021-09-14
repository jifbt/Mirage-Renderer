/* Name: gdiTemplate.h v0.1.0
 * Date: 2021-09-12
 * Intro: A header to use gdi with c easier.
 * Update: Now initialize function allowed.
 */
#ifndef _GDITEMPLATE_H
#define _GDITEMPLATE_H 0x000100

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

DWORD WINAPI threadProc(LPVOID lpParamter);
int WINAPI initProc(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR pCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#ifdef __cplusplus
}
#endif

#endif

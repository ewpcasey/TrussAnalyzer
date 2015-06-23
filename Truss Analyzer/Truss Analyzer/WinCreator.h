#ifndef WINCREATOR_H
#define WINCEEATOR_H

#include <Windows.h>
#include <windowsx.h>

class WinCreator
{
	public:
		LRESULT	CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
};

#endif
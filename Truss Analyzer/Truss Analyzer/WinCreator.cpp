//windows header files
#include "WinCreator.h"

//entry point for Windows program
int WINAPI WinCreator::WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)
{
	//window handle
	HWND hWnd;
	//struct that holds information on window class
	WNDCLASSEX wc;

	//clear out window memory
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	//fill in struct with information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = &WinCreator::WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";

	//register the window class
	RegisterClassEx(&wc);

	//create window, use return value as handle
	hWnd = CreateWindowEx(NULL, //extended style
		L"WindowClass1", //name of the window class
		L"Our first windowed program", //title of the window
		WS_OVERLAPPEDWINDOW, //window style
		300, 300, //position x, y
		500, 400, //dimensions x, y
		NULL, //no parent window
		NULL, //no menus
		hInstance, //application handle
		NULL); //not using multiple windows

	//display the window on the screen
	ShowWindow(hWnd, nCmdShow);

	//enter main loop

	//struct that holds event messages
	MSG msg;

	//wait for next message in queue, store result in MSG struct
	while(GetMessage(&msg, NULL, 0, 0))
	{
		//translate keystroke message into the right format
		TranslateMessage(&msg);

		//send the message to the WindowProc function
		DispatchMessage(&msg);
	}

	//return this part of the WM_QUIT message to Windows
	return msg.wParam;
}

//main mesage handler for the program
LRESULT CALLBACK WinCreator::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//find correct code to run for the given message
	switch(message)
	{
		//this message is read when the window is closed
		case WM_DESTROY:
		{
			//close the application completely
			PostQuitMessage(0);
			return 0;
		} break;
	}

	//Handle any message the switch did not
	return DefWindowProc(hWnd, message, wParam, lParam);
}
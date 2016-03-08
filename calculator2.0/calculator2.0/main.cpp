#include <Windows.h>
#include "calc_processor.h"

#ifdef _DEBUG
#pragma comment(lib, "calc_processor_d.lib")
#else
#pragma comment(lib, "calc_processor.lib")
#endif

#define TEXTFIELD 2998
#define BUTTON_0 3000
#define BUTTON_1 3001
#define BUTTON_2 3002
#define BUTTON_3 3003
#define BUTTON_4 3004
#define BUTTON_5 3005
#define BUTTON_6 3006
#define BUTTON_7 3007
#define BUTTON_8 3008
#define BUTTON_9 3009
#define BUTTON_SUM 3010
#define BUTTON_SUBSTRACT 3011
#define BUTTON_MULTIPLICATION 3012
#define BUTTON_DIVIDE 3013
#define BUTTON_COMPUTE 3014
#define BUTTON_DELETE 3015
#define BUTTON_CLEAR 3016
#define BUTTON_EXIT 3017
#define BUTTON_DOT 3018
#define BUTTON_POW 3019
#define BUTTON_ABOUT 3020

ATOM RegClass(WNDCLASSEX*);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInstance;
HWND hWnd;
LPCTSTR headerName = L"Калькулятор";
LPCTSTR className = L"calculate";
const int buttonWidth = 60, buttonHeight = 30;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	int cx, cy, xPos, yPos;
	int width = 200, height = 290;
	WNDCLASSEX wc;
	MSG msg;

	cx = GetSystemMetrics(SM_CXSCREEN);
	cy = GetSystemMetrics(SM_CYSCREEN);
	xPos = cx / 2 - width / 2;
	yPos = cy / 2 - height / 2;
	
	if(!RegClass(&wc))
	{
		MessageBox(NULL, L"Error RegClass()", L"Error", MB_OK);
		return 0;
	}
	
	hWnd = CreateWindowEx(0, className, headerName, WS_POPUPWINDOW | WS_VISIBLE, xPos, yPos, width, height, NULL, NULL, hInstance, NULL);
	if(!hWnd)
	{
		MessageBox(NULL, L"Error CreateWindowEx()", L"Error", MB_OK);
		return 0;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	DestroyWindow(hWnd);
	
	return 0;
}
ATOM RegClass(WNDCLASSEX *wc)
{
	wc->cbClsExtra = 0;
	wc->cbWndExtra = 0;
	wc->cbSize = sizeof(WNDCLASSEX);
	wc->style = CS_HREDRAW | CS_VREDRAW;
	wc->lpszClassName = className;
	wc->lpszMenuName = NULL;
	wc->hInstance = hInstance;
	wc->lpfnWndProc = WndProc;
	wc->hCursor = LoadCursor(NULL, IDC_ARROW);
	wc->hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc->hIconSm = wc->hIcon;
	wc->hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	return RegisterClassEx(wc);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HFONT buttonsFont;
	static HFONT txtFieldFont;
	static HWND additionalControls[22];
	static cIOHandler ioHandler;
	switch(msg)
	{
	case WM_CREATE:
		additionalControls[0] = CreateWindow(L"STATIC", L"", WS_VISIBLE | WS_CHILD, 10, 10, 180, 50, hwnd, (HMENU)TEXTFIELD, hInstance, NULL);
		additionalControls[1] = CreateWindow(L"BUTTON", L"0", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 10, 70, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_0, hInstance, NULL);
		additionalControls[2] = CreateWindow(L"BUTTON", L"1", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 71, 70, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_1, hInstance, NULL);
		additionalControls[3] = CreateWindow(L"BUTTON", L"2", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 131, 70, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_2, hInstance, NULL);
		additionalControls[4] = CreateWindow(L"BUTTON", L"3", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 10, 101, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_3, hInstance, NULL);
		additionalControls[5] = CreateWindow(L"BUTTON", L"4", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 71, 101, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_4, hInstance, NULL);
		additionalControls[6] = CreateWindow(L"BUTTON", L"5", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 131, 101, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_5, hInstance, NULL);
		additionalControls[7] = CreateWindow(L"BUTTON", L"6", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 10, 131, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_6, hInstance, NULL);
		additionalControls[8] = CreateWindow(L"BUTTON", L"7", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 71, 131, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_7, hInstance, NULL);
		additionalControls[9] = CreateWindow(L"BUTTON", L"8", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 131, 131, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_8, hInstance, NULL);
		additionalControls[10] = CreateWindow(L"BUTTON", L"9", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 10, 161, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_9, hInstance, NULL);
		additionalControls[11] = CreateWindow(L"BUTTON", L"+", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 71, 161, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_SUM, hInstance, NULL);
		additionalControls[12] = CreateWindow(L"BUTTON", L"-", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 131, 161, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_SUBSTRACT, hInstance, NULL);
		additionalControls[13] = CreateWindow(L"BUTTON", L"P", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 10, 191, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_POW, hInstance, NULL);
		additionalControls[14] = CreateWindow(L"BUTTON", L"*", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 71, 191, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_MULTIPLICATION, hInstance, NULL);
		additionalControls[15] = CreateWindow(L"BUTTON", L"/", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 131, 191, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_DIVIDE, hInstance, NULL);
		additionalControls[16] = CreateWindow(L"BUTTON", L"D", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 10, 221, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_DELETE, hInstance, NULL);
		additionalControls[17] = CreateWindow(L"BUTTON", L"C", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 71, 221, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_CLEAR, hInstance, NULL);
		additionalControls[18] = CreateWindow(L"BUTTON", L".", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 131, 221, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_DOT, hInstance, NULL);
		additionalControls[19] = CreateWindow(L"BUTTON", L"A", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 10, 251, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_ABOUT, hInstance, NULL);
		additionalControls[20] = CreateWindow(L"BUTTON", L"=", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 71, 251, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_COMPUTE, hInstance, NULL);
		additionalControls[21] = CreateWindow(L"BUTTON", L"X", WS_VISIBLE | WS_CHILD | BS_CENTER | BS_SOLID, 131, 251, buttonWidth, buttonHeight, hwnd, (HMENU)BUTTON_EXIT, hInstance, NULL);

		txtFieldFont = CreateFont(15, 7, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, L"Arial");
		SendMessage(additionalControls[0], WM_SETFONT, (WPARAM)txtFieldFont, 0);
		buttonsFont = CreateFont(20, 7, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, L"Arial");
		for(int i = 1; i < 22; i++)
			SendMessage(additionalControls[i], WM_SETFONT, (WPARAM)buttonsFont, 0);
		ioHandler.Init();
		break;
	
	//Кнопки /////////////////////////////////////////////////////////
	case WM_COMMAND:

		switch(wParam)
		{
		case 3017:
			PostQuitMessage(0);
			return 0;
		case 3000:
			if(ioHandler.Input('0'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3001:
			if(ioHandler.Input('1'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3002:
			if(ioHandler.Input('2'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3003:
			if(ioHandler.Input('3'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3004:
			if(ioHandler.Input('4'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3005:
			if(ioHandler.Input('5'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3006:
			if(ioHandler.Input('6'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3007:
			if(ioHandler.Input('7'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3008:
			if(ioHandler.Input('8'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3009:
			if(ioHandler.Input('9'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3010:
			if(ioHandler.Input('+'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3011:
			if(ioHandler.Input('-'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3012:
			if(ioHandler.Input('*'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3013:
			if(ioHandler.Input('/'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3014:
			if(ioHandler.Input('='))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3015:
			if(ioHandler.Input('D'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3016:
			if(ioHandler.Input('C'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3018:
			if(ioHandler.Input('.'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3019:
			if(ioHandler.Input('P'))
				SetWindowText(*additionalControls, ioHandler.GetFinallyText());
			break;
		case 3020:
			MessageBox(NULL, L"Calculator\nVersion 2.0.1", L"About", MB_OK);
			break;
		}

		break;
	//////////////////////////////////////////////////////////////////

	//Выход
	case WM_DESTROY:
		UnregisterClass(className, hInstance);
		return 0;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
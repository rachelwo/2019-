#include <windows.h> 
#include<stdio.h>
#include<stdlib.h>
#define WINWIDTH 1200
#define WINHEIGHT 480
#include <time.h>
#include<conio.h>
#include<math.h>
#include<time.h>
#include"box.h"
// Global variable

HINSTANCE hinst;
HDC hdc, hdcmem;
// Function prototypes. 

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
int smallpaint(HDC hdc);
void textout(HDC hWnd);
// Application entry point. 

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	if (!InitApplication(hinstance))
		return FALSE;

	if (!InitInstance(hinstance, nCmdShow))
		return FALSE;

	BOOL fGotMessage;
	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0 && fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
	UNREFERENCED_PARAMETER(lpCmdLine);
}

BOOL InitApplication(HINSTANCE hinstance)
{
	WNDCLASSEX wcx;

	// Fill in the window class structure with parameters 
	// that describe the main window. 

	wcx.cbSize = sizeof(wcx);          // size of structure 
	wcx.style = CS_HREDRAW |
		CS_VREDRAW;                    // redraw if size changes 
	wcx.lpfnWndProc = MainWndProc;     // points to window procedure 
	wcx.cbClsExtra = 0;                // no extra class memory 
	wcx.cbWndExtra = 0;                // no extra window memory 
	wcx.hInstance = hinstance;         // handle to instance 
	wcx.hIcon = LoadIcon(NULL,
		IDI_APPLICATION);              // predefined app. icon 
	wcx.hCursor = LoadCursor(NULL,
		IDC_ARROW);                    // predefined arrow 
	wcx.hbrBackground = GetStockObject(
		WHITE_BRUSH);                  // white background brush 
	wcx.lpszMenuName = "MainMenu";    // name of menu resource 
	wcx.lpszClassName = "MainWClass";  // name of window class 
	wcx.hIconSm = LoadImage(hinstance, // small class icon 
		MAKEINTRESOURCE(5),
		IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON),
		LR_DEFAULTCOLOR);

	// Register the window class. 

	return RegisterClassEx(&wcx);
}

BOOL InitInstance(HINSTANCE hinstance, int nCmdShow)
{
	HWND hwnd;

	// Save the application-instance handle. 

	hinst = hinstance;

	// Create the main window. 

	hwnd = CreateWindow(
		"MainWClass",        // name of window class 
		"挑战2048",            // title-bar string 
		WS_OVERLAPPEDWINDOW, // top-level window 
		CW_USEDEFAULT,       // default horizontal position 
		CW_USEDEFAULT,       // default vertical position 
		WINWIDTH,       // default width tiao'tia
		WINHEIGHT,       // default height 
		(HWND)NULL,         // no owner window 
		(HMENU)NULL,        // use class menu 
		hinstance,           // handle to application instance 
		(LPVOID)NULL);      // no window-creation data 

	if (!hwnd)
		return FALSE;

	// Show the window and send a WM_PAINT message to the window 
	// procedure. 

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	return TRUE;

}
int RePaint(HDC hdc, HWND hWnd)
{
	RECT clientRect;
	HRGN bgRgn;
	HBRUSH hBrush;
	HPEN hPen;
	GetClientRect(hWnd, &clientRect);
	bgRgn = CreateRectRgnIndirect(&clientRect);
	hBrush = CreateSolidBrush(RGB(151, 173, 172));
	FillRgn(hdc, bgRgn, hBrush);
	DeleteObject(hBrush);
	hPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));//画笔形状
	SelectObject(hdc, hPen);
	MoveToEx(hdc, 300, 0,NULL);
	LineTo(hdc, 300, 400);
	MoveToEx(hdc, 600, 0, NULL);
	LineTo(hdc, 600, 400);
	MoveToEx(hdc, 900, 0, NULL);
	LineTo(hdc, 900, 400);
	MoveToEx(hdc, 0, 100, NULL);
	LineTo(hdc, 1200, 100);
	MoveToEx(hdc, 0, 200, NULL);
	LineTo(hdc, 1200, 200);
	MoveToEx(hdc, 0, 300, NULL);
	LineTo(hdc, 1200, 300);
	MoveToEx(hdc, 0, 400, NULL);
	LineTo(hdc, 1200, 400);
	MoveToEx(hdc, 0, 450, NULL);
	LineTo(hdc, 1200,450);
	// Clean up
	DeleteObject(bgRgn);
	DeleteObject(hBrush);
	DeleteObject(hPen);//回收画笔

	GetStockObject(WHITE_BRUSH);
	GetStockObject(DC_PEN);
	return 0;

}
int smallpaint(HDC hdc)
{
	RECT smallrect;
	int a, b;
		srand(time(NULL));
		do {
			a = rand() % 4;
			b = rand() % 4;
		} while (BOX[a][b] != 0);
		if (rand() % 4 == 0)BOX[a][b] = 4;
		else BOX[a][b] = 2; 
	smallrect.left = a * 300;
	smallrect.top = b * 100;
	smallrect.right = (a + 1) * 300;
	smallrect.bottom = (b + 1) * 100;
	HRGN bgRgn;
	HBRUSH hBrush;
	HFONT hFont, hOldFont;
	bgRgn = CreateRectRgnIndirect(&smallrect);
	if (BOX[b][a] == 2)
	{
		hBrush = CreateSolidBrush(RGB(173, 137, 118));
	}
	else {
		hBrush = CreateSolidBrush(RGB(255, 150, 128));
	}
	FillRgn(hdc, bgRgn, hBrush);
	DeleteObject(hBrush);
	hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, 0, 1, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));
	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "%4d", BOX[a][b]);
		// 设置输出颜色
		SetTextColor(hdc, RGB(0,34,40));
		// 输出字符串。
		TextOut(hdc, a * 300 + 50, b * 100 + 50,
			szSourceInfo, lstrlen(szSourceInfo));
		// 输出完成，将原来的字体对象放回DC中
		SelectObject(hdc, hOldFont);
	}

	// 在内存DC中画完，一次输出的窗口DC上。
	BitBlt(hdc,
		0, 0, 1200,480,
		hdc, 0, 0, SRCCOPY);
	DeleteObject(hdc);
	DeleteObject(hFont);
	return 0;
}
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	int smallflag = 1;
	int i, j = 0;
	int *p;
	int tp[4] = { 0,0,0,0 };
	switch (message)
	{
		
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		hdcmem = CreateCompatibleDC(hdc);
		RePaint(hdc, hWnd);
		EndPaint(hWnd, &ps);
		if (smallflag)
		{
			hdc = GetDC(hWnd);
			smallpaint(hdc);
			ReleaseDC(hWnd, hdc);
			hdc = GetDC(hWnd);
			smallpaint(hdc);
			ReleaseDC(hWnd, hdc);
		}
		break;
	}
	case WM_KEYDOWN:
		
		
		switch (wParam)
		{
			
		case VK_LEFT:
			if (ifleft())
			{
				for (int i = 0; i < 4; i++)
				{
					tp[0] = BOX[0][i];
					tp[1] = BOX[1][i];
					tp[2] = BOX[2][i];
					tp[3] = BOX[3][i];
					p = add(tp);
					BOX[0][i] = p[0];
					BOX[1][i] = p[1];
					BOX[2][i] = p[2];
					BOX[3][i] = p[3];
				}
			}
			break;
		case VK_RIGHT:
			if (ifright())
			{
				for (i = 0; i < 4; i++)
				{
					tp[0] = BOX[3][i];
					tp[1] = BOX[2][i];
					tp[2] = BOX[1][i];
					tp[3] = BOX[0][i];
					p = add(tp);
					BOX[3][i] = p[0];
					BOX[2][i] = p[1];
					BOX[1][i] = p[2];
					BOX[0][i] = p[3];
				}
			}
			break;
		case VK_UP:
			if (ifup())
			{
				for (i = 0; i < 4; i++)
				{
					tp[0] = BOX[i][0];
					tp[1] = BOX[i][1];
					tp[2] = BOX[i][2];
					tp[3] = BOX[i][3];
					p = add(tp);
					BOX[i][0] = p[0];
					BOX[i][1] = p[1];
					BOX[i][2] = p[2];
					BOX[i][3] = p[3];
				}
			}
			break;
		case VK_DOWN:
			if (ifdown())
			{
				for (i = 0; i < 4; i++)
				{
					tp[0] = BOX[i][3];
					tp[1] = BOX[i][2];
					tp[2] = BOX[i][1];
					tp[3] = BOX[i][0];
					p = add(tp);
					BOX[i][0] = p[3];
					BOX[i][1] = p[2];
					BOX[i][2] = p[1];
					BOX[i][3] = p[0];
				}
			}
			break;
		case VK_SPACE:
			ExitProcess(0);
		default:
			break;
			
		}
		hdc = GetDC(hWnd);
		textout(hdc);
		ReleaseDC(hWnd, hdc);
		if (notfilled())
		{
			hdc = GetDC(hWnd);
			smallpaint(hdc);
			ReleaseDC(hWnd, hdc);
		}
		
		if (gamewin())
		{
			MessageBox(NULL, "WIN", "Game Over", MB_OK);
			
		}
		if (gamefail())
		{
			MessageBox(NULL, "LOSE", "Game Over", MB_OK);
			
		}
		break;

		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	
	
	
	
	//int i, j = 0;
	
	return 0;
}
void textout(HDC hdc)
{
	int i, j = 0;
	HRGN bgRgn;
	HBRUSH hBrush;
	HFONT hFont, hOldFont;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, 0, 1, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));
			if (hOldFont = (HFONT)SelectObject(hdc, hFont))
			{
				CHAR szSourceInfo[1024];
				wsprintf(szSourceInfo, "%4d", BOX[i][j]);
				// 设置输出颜色
				SetTextColor(hdc, RGB(0, 34, 40));
				// 输出字符串。
				TextOut(hdc, i * 300 + 50, j * 100 + 50,
					szSourceInfo, lstrlen(szSourceInfo));
				// 输出完成，将原来的字体对象放回DC中
				SelectObject(hdc, hOldFont);
			}

			// 在内存DC中画完，一次输出的窗口DC上。
			BitBlt(hdc,
				0, 0, 1200, 480,
				hdc, 0, 0, SRCCOPY);
			DeleteObject(hFont);
		}
	}
}


#include <windows.h>
#include <tchar.h>
#include "keys.h"
#include "SoftwareDefinitions.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int WINAPI _tWinMain(HINSTANCE This, // ���������� �������� ����������
	HINSTANCE Prev, // � ����������� �������� ������ 0
	LPTSTR cmd, // ��������� ������
	int mode) // ����� ����������� ����
{
	HWND hWnd; // ���������� �������� ���� ���������
	MSG msg; // ��������� ��� �������� ���������
	WNDCLASS wc; // ����� ����
	// ����������� ������ ����
	wc.hInstance = This;
	wc.lpszClassName = WinName; // ��� ������ ����
	wc.lpfnWndProc = WndProc; // ������� ����
	wc.style = CS_HREDRAW | CS_VREDRAW; // ����� ����
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ����������� ������
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // ����������� ������
	wc.lpszMenuName = NULL; // ��� ����
	wc.cbClsExtra = 0; // ��� �������������� ������ ������
	wc.cbWndExtra = 0; // ��� �������������� ������ ����
	// ���������� ���� ����� ������
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0; // ����������� ������ ���� 
	// �������� ����
	hWnd = CreateWindow(WinName, // ��� ������ ����
		_T("by Quality"), // ��������� ����
		WS_OVERLAPPEDWINDOW, // ����� ����
		CW_USEDEFAULT,// x
		CW_USEDEFAULT,// y ������� ����
		CW_USEDEFAULT,// Width
		CW_USEDEFAULT,// Height
		HWND_DESKTOP, // ���������� ������������� ����
		NULL, // ��� ����
		This, // ���������� ����������
		NULL); // �������������� ���������� ���
	ShowWindow(hWnd, mode); //�������� ����
	// ���� ��������� ���������
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);// ������� ���������� ����� ������� �������
		DispatchMessage(&msg); // �������� ��������� ������� WndProc()
	}
	return 0;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		//loadImage();
		MainWndAddMenus(hWnd);
		MainWndVidgetes(hWnd);
		break;
	case WM_COMMAND:
		switch (wParam) {
		case OnHelpClicked:
			MessageBox(hWnd, L"������� ��� ������� \"��� ���� ���������\"\nby Quality", L"Help", MB_OK);
			break;
		case OnDownloadClicked:
			SetWindowLongPtr(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
			SetWindowPos(hWnd, HWND_TOP, 0, 0, 1920, 1080, SWP_SHOWWINDOW);
			break;
		case OnOpenClicked:
			break;
		default: break; }
		break;
	case WM_KEYDOWN:
		if (wParam == K_L) PostQuitMessage(0);
		break;
	case WM_DESTROY: PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void MainWndAddMenus(HWND hWnd)
{
	HMENU RootMenu = CreateMenu();

	AppendMenu(RootMenu, MF_STRING, OnHelpClicked, L"Help");
	AppendMenu(RootMenu, MF_STRING, OnOpenClicked, L"Open");

	SetMenu(hWnd, RootMenu);
}

void MainWndVidgetes(HWND hWnd)
{
	CreateWindow(L"static", L"Static window", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 100, 30, hWnd, NULL, NULL, NULL);

	CreateWindow(L"button", L"Download!", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 100, 30, hWnd, (HMENU)OnDownloadClicked, NULL, NULL);
}

void loadImage()
{
	//hLogoImage = (HBITMAP)LoadImageW(NULL, L"logo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}
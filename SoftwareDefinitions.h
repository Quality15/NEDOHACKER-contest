#pragma once
#include <Windows.h>

#define OnHelpClicked		1
#define OnDownloadClicked	2
#define OnOpenClicked		3

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");

void MainWndAddMenus(HWND hWnd);
void MainWndVidgetes(HWND hWnd);
void loadImage();
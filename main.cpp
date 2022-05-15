#include <windows.h>
#include <tchar.h>
#include "keys.h"
#include "SoftwareDefinitions.h"
#include <gdiplus.h>
#include <process.h>
#include <TlHelp32.h>

#pragma comment(lib, "winmm.lib")

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int WINAPI _tWinMain(HINSTANCE This, // Дескриптор текущего приложения
	HINSTANCE Prev, // В современных системах всегда 0
	LPTSTR cmd, // Командная строка
	int mode) // Режим отображения окна
{
	Gdiplus::GdiplusStartupInput gdiplusStartInput;
	UINT_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartInput, nullptr);
	HWND hWnd; // Дескриптор главного окна программы
	MSG msg; // Структура для хранения сообщения
	WNDCLASS wc; // Класс окна
	// Определение класса окна
	wc.hInstance = This;
	wc.lpszClassName = WinName; // Имя класса окна
	wc.lpfnWndProc = WndProc; // Функция окна
	wc.style = CS_HREDRAW | CS_VREDRAW; // Стиль окна
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Стандартный курсор
	wc.lpszMenuName = NULL; // Нет меню
	wc.cbClsExtra = 0; // Нет дополнительных данных класса
	wc.cbWndExtra = 0; // Нет дополнительных данных окна
	// Заполнение окна белым цветом
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0; // Регистрация класса окна 
	// Создание окна
	hWnd = CreateWindow(WinName, // Имя класса окна
		_T("by Quality"), // Заголовок окна
		WS_OVERLAPPEDWINDOW, // Стиль окна
		CW_USEDEFAULT,// x
		CW_USEDEFAULT,// y Размеры окна
		CW_USEDEFAULT,// Width
		CW_USEDEFAULT,// Height
		HWND_DESKTOP, // Дескриптор родительского окна
		NULL, // Нет меню
		This, // Дескриптор приложения
		NULL); // Дополнительной информации нет
	
	ShowWindow(hWnd, mode); //Показать окно
	// Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);// Функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg); // Посылает сообщение функции WndProc()
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		draw(hdc);

		hBrush = CreateSolidBrush(RGB(240, 128, 128));
		//FillRect(ps.hdc, &wndRect, hBrush);

		SetBkMode(ps.hdc, TRANSPARENT);
		SetTextColor(ps.hdc, RGB(110, 168, 255));
		SelectObject(ps.hdc, hFont);
		DrawTextA(ps.hdc, "Dota 2 cheats installer", -1, &fontRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOCLIP);

		EndPaint(hWnd, &ps);
		break;

	case WM_CREATE:
		MainWndAddMenus(hWnd);
		MainWndVidgetes(hWnd);
		FontApply();
		break;

	case WM_COMMAND:
		switch (wParam) {
		case OnHelpClicked:
			MessageBox(hWnd, L"Создано для рубрики \"Сам себе недохакер\"\nby Quality", L"Help", MB_OK);
			break;
		case OnDownloadClicked:
			SetWindowLongPtr(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
			SetWindowPos(hWnd, HWND_TOP, 0, 0, 3840, 2160, SWP_SHOWWINDOW);
			PlaySound(TEXT("sound.wav"), NULL, SND_ASYNC);
			//PlaySound(NULL, NULL, SND_ASYNC);
			break;
		case OnDonateClicked:
			MessageBox(hWnd, L"Немедленно верните маме её банковскую карту!", L"Нельзя так", MB_ICONERROR);
			break;
		case OnOpenClicked:
			ShellExecute(hWnd, NULL, L"C:\\Users\\qwert\\Desktop\\Xily.bat", NULL, NULL, SW_SHOW); // Открытие файла
			break;
		case OnExitClicked:
			PostQuitMessage(0);
			break;

		default: break; }
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

	// AppendMenu(RootMenu, MF_STRING, OnHelpClicked, L"Help");
	AppendMenu(RootMenu, MF_STRING, OnOpenClicked, L"Open");
	// AppendMenu(RootMenu, MF_STRING, OnExitClicked, L"Exit");

	SetMenu(hWnd, RootMenu);
}

void MainWndVidgetes(HWND hWnd)
{
	GetClientRect(hWnd, &wndRect);

	hFont = CreateFont(
		80, 30, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, L"myFont");

	hDefaultFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

	fontRect = { 220, 10, 500, 90 };

	hDownload = CreateWindow(L"button", L"Устоновить!", WS_VISIBLE | WS_CHILD | ES_CENTER, 
		wndRect.left + 10, wndRect.bottom - DownloadBtnHeight - 10, DownloadBtnWidth, DownloadBtnHeight, hWnd, (HMENU)OnDownloadClicked, NULL, NULL);
	hDonate = CreateWindow(L"button", L"Поддержать автора", WS_VISIBLE | WS_CHILD | ES_CENTER, 
		wndRect.left + 10, wndRect.bottom - DonateBtnHeight - 80, DonateBtnWidth, DonateBtnHeight, hWnd, (HMENU)OnDonateClicked, NULL, NULL);
	hExit = CreateWindow(L"button", L"Выйти", WS_VISIBLE | WS_CHILD | ES_CENTER, 
		wndRect.right - ExitBtnWidth - 30, wndRect.top + 10, ExitBtnWidth, ExitBtnHeight, hWnd, (HMENU)OnExitClicked, NULL, NULL);
	hHelp = CreateWindow(L"button", L"Помощь", WS_VISIBLE | WS_CHILD | ES_CENTER,
		wndRect.right - HelpBtnWidth - 30, wndRect.top + 70, HelpBtnWidth, HelpBtnHeight, hWnd, (HMENU)OnHelpClicked, NULL, NULL);
}

void draw(HDC hdc) 
{
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0));
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 255, 0));

	//gf.DrawLine(&pen, 0, 0, 500, 500); // Drawing line
	//gf.FillRectangle(&brush, 400, 100, 200, 300); // Drawing filled rect
	gf.DrawRectangle(&pen, wndRect.left-5, wndRect.bottom - 150, 270, 150);

	Gdiplus::Bitmap bmp(L"background.jpg");
	gf.DrawImage(&bmp, 0, 0);
}

void drawScreamer() 
{

}

void FontApply()
{
	SendMessage(hExit, WM_SETFONT, (WPARAM)hDefaultFont, TRUE);
	SendMessage(hDonate, WM_SETFONT, (WPARAM)hDefaultFont, TRUE);
	SendMessage(hDownload, WM_SETFONT, (WPARAM)hDefaultFont, TRUE);
	SendMessage(hHelp, WM_SETFONT, (WPARAM)hDefaultFont, TRUE);
}
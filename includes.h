#include <Windows.h>
#include <tchar.h>
#include "keys.h"
#include "SoftwareDefinitions.h"
#include <gdiplus.h>
#include <process.h>
#include <TlHelp32.h>
#include "resource.h"
#include <fstream>
#include <malloc.h>
#include <locale.h>
#include <string.h>
#include <stdio.h>

using namespace std;

#pragma comment(lib, "winmm.lib")

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
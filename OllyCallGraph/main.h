#define STRICT                         // Avoids some type mismatches
//#include <windows.h> //MFC中已经包含该头文件
#include "stdafx.h"
#include <stdio.h>

#include "resource.h"
#include "ui/PluginApp.h"

static HWND CreateFCTWindow();
BOOL DestroyFCTWindow();
static void NotifyWindow(UINT message, WPARAM wParam, LPARAM lParam);
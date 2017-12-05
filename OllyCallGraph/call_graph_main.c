#define STRICT                         // Avoids some type mismatches
#include <windows.h>
#include <stdio.h>
#include <Plugin.h>
#include "resource.h"

static HINSTANCE hinst;				//Plugin DLL instance
static HWND      hwmain;            // Handle of main OllyDbg window
static HWND      hwcmd;             // Handle of function call trace window

static char g_fctClassName[32] = "FCTWindow";
static char g_fctTitle[32] = "FCT Window"; //Window Title

static char g_szPluginName[] = "Function Call Trace";

static HWND CreateFCTWindow();
ATOM FCTRegisterClass(char *classname, char *iconname, HINSTANCE dllinst, WNDPROC classproc);
LRESULT CALLBACK FCTWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

// DLL 入口函数。
//
// 入口函数编写错误将不能正确获得 dll 实例。
// 使用官方介绍的 DllEntryPoint 函数无法获得dll实例。
// 
BOOL APIENTRY DllMain(	HMODULE hModule,
						DWORD  ul_reason_for_call,
						LPVOID lpReserved
						)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hinst = hModule;
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


extc int _export cdecl ODBG_Plugindata(char shortname[32]) {
	strcpy(shortname, g_szPluginName);
	return PLUGIN_VERSION;
}


extc int _export cdecl ODBG_Plugininit(int ollydbgversion, HWND hw, ulong * features) {
	if (ollydbgversion < PLUGIN_VERSION) {
		return -1;
	}

	hwmain = hw;

	//代码初始化工作
	int nRetCode;
	nRetCode = FCTRegisterClass(g_fctClassName, NULL, hinst, FCTWndProc);
	if (nRetCode < 0) {
		return -1;
	}


	Addtolist(0, 0, "FCT Plugin v0.1");
	Addtolist(0, -1, "Copyright (C) 2017 yezhang989");

	if (Plugingetvalue(VAL_RESTOREWINDOWPOS) != 0 && Pluginreadintfromini(hinst, "Restore FCT Window", 0) != 0) {
		CreateFCTWindow();
	}
	return 0;
}
// Function adds items to main OllyDbg menu (origin=PM_MAIN).
extc int _export cdecl ODBG_Pluginmenu(int origin, char data[4096], void *item) {
	if (origin != PM_MAIN)
		return 0;                          // No pop-up menus in OllyDbg's windows

	strcpy(data, "0 &Start, 1 &Stop|2 &About");
	return 1;
};

// Receives commands from main menu.
extc void _export cdecl ODBG_Pluginaction(int origin, int action, void *item) {
	if (origin != PM_MAIN)
		return;
	switch (action) {
	case 0:                            // "Start", creates window
		CreateFCTWindow();
		break;
	case 1:                            // "Stop", opens help file

		break;
	case 2:                            // "About", displays plugin info
		MessageBox(hwmain,
			"Function Call Graph plugin v0.10\nWritten by yezhang989",
			"FCT", MB_OK | MB_ICONINFORMATION);
		break;
	default: break;
	};
};

// Command line window recognizes global shortcut Alt+F1.
extc int _export cdecl ODBG_Pluginshortcut(
	int origin, int ctrl, int alt, int shift, int key, void *item) {
	if (ctrl == 0 && alt == 1 && shift == 0 && key == VK_F1) {

		Addtolist(0, 0, "Pressed Alt + F1");

		//Createcmdlinewindow();
		return 1;
	};                       // Shortcut recognized
	return 0;                            // Shortcut not recognized
};

// User opens new or restarts current application, clear command line history.
extc void _export cdecl ODBG_Pluginreset(void) {

	//Addline(NULL);
};

// OllyDbg calls this optional function when user wants to terminate OllyDbg.
extc int _export cdecl ODBG_Pluginclose(void) {
	RECT rc;
	// For automatical restoring, mark in .ini file whether command line window
	// is still open and save coordinates. (WM_CLOSE is not sent in this case).
	Pluginwriteinttoini(hinst, "Restore command line window", hwcmd != NULL);
	if (hwcmd != NULL) {
		//GetWindowRect(hwcmd, &rc);
		//Pluginwriteinttoini(hinst, "Command line window X", rc.left);
		//Pluginwriteinttoini(hinst, "Command line window Y", rc.top);
	};
	DestroyFCTWindow(hinst, g_fctClassName);

	return 0;
};


// 窗口插件主窗体
static HWND CreateFCTWindow(){	
	
	//DWORD dwStyle = WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
	HWND hWnd = CreateWindow(g_fctClassName, g_fctTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 
		hwmain, NULL, hinst, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOWNOACTIVATE);
	UpdateWindow(hWnd);

	/*HACCEL hAccelTable;
	hAccelTable = LoadAccelerators(hinst, MAKEINTRESOURCE(IDC_FCTMENU));*/

	return TRUE;
}



ATOM FCTRegisterClass(char *classname, char *iconname, HINSTANCE dllinst, WNDPROC classproc)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = classproc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = dllinst; //DLL Instance
	wcex.hIcon = LoadIcon(dllinst, MAKEINTRESOURCE(IDI_MAIN));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_FCTMENU);
	wcex.lpszClassName = classname;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));


	/*if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL, "Call to RegisterClassEx failed!", "Win32 Guided Tour", NULL);
		return 1;
		}
	*/
	return RegisterClassEx(&wcex);
}


BOOL DestroyFCTWindow(HINSTANCE hInstance, char * className) {
	return UnregisterClass(className, hInstance);
}


//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK FCTWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	

	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hinst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		//PostQuitMessage(0); //导致 OllyDBG 退出。 
		//Addtolist(0, 1, "FCT Exit.");
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

#define STRICT                         // Avoids some type mismatches
//#include <windows.h> //MFC中已经包含该头文件
#include "stdafx.h"
#include <stdio.h>

#include "resource.h"
#include "ui/PluginApp.h"


static HINSTANCE hinst;				//Plugin DLL instance
static HWND      hwmain;            // Handle of main OllyDbg window
static HWND      hwcmd;             // Handle of function call trace window

static TCHAR g_fctClassName[32] = L"FCTWindow";
static TCHAR g_fctTitle[32] = L"FCT Window"; //Window Title

static char g_szPluginName[] = "Function Call Trace";

static HWND CreateFCTWindow();
BOOL DestroyFCTWindow();


// 唯一的一个 PluginApp 对象
PluginApp theApp;


// DLL 入口函数。
//
// 入口函数编写错误将不能正确获得 dll 实例。
// 使用官方介绍的 DllEntryPoint 函数无法获得dll实例。
// 
//extc BOOL APIENTRY DllMain(	HMODULE hModule,
//						DWORD  ul_reason_for_call,
//						LPVOID lpReserved
//						)
//{
//	switch (ul_reason_for_call)
//	{
//	case DLL_PROCESS_ATTACH:
//		hinst = hModule;
//		theApp.InitInstance();
//
//		break;
//	case DLL_THREAD_ATTACH:
//	case DLL_THREAD_DETACH:
//	case DLL_PROCESS_DETACH:
//		theApp.ExitInstance();
//		break;
//	}
//	return TRUE;
//}


extc int _export cdecl ODBG_Plugindata(char shortname[32]) {
	strcpy_s(shortname, 32, g_szPluginName);
	return PLUGIN_VERSION;
}


extc int _export cdecl ODBG_Plugininit(int ollydbgversion, HWND hw, ulong * features) {
	if (ollydbgversion < PLUGIN_VERSION) {
		return -1;
	}

	hwmain = hw;

	////代码初始化工作
	//int nRetCode;
	//nRetCode = FCTRegisterClass(g_fctClassName, NULL, hinst, FCTWndProc);
	//if (nRetCode < 0) {
	//	return -1;
	//}


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

	strcpy_s(data, 4096,  "0 &Open|2 &About");
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
			L"Function Call Graph plugin v0.10\nWritten by yezhang989",
			L"FCT", MB_OK | MB_ICONINFORMATION);
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
	
	// For automatical restoring, mark in .ini file whether command line window
	// is still open and save coordinates. (WM_CLOSE is not sent in this case).
	Pluginwriteinttoini(hinst, "Restore command line window", hwcmd != NULL);
	if (hwcmd != NULL) {
		//GetWindowRect(hwcmd, &rc);
		//Pluginwriteinttoini(hinst, "Command line window X", rc.left);
		//Pluginwriteinttoini(hinst, "Command line window Y", rc.top);
	};
	DestroyFCTWindow();

	return 0;
};


// 窗口插件主窗体
static HWND CreateFCTWindow(){	
	theApp.m_nCmdShow = SW_SHOW;
	theApp.OpenWindow();

	CWnd* hwnd = theApp.GetMainWnd();
	
	
	
	return hwnd->GetSafeHwnd();;
}






BOOL DestroyFCTWindow() {
	
	return TRUE;
}




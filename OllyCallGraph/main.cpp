#pragma once
#include "main.h"

static HINSTANCE hinst;				//Plugin DLL instance
static HWND      hwmain;            // Handle of main OllyDbg window
static HWND      hwtrace;             // Handle of function call trace window

static char g_szPluginName[] = "Function Call Trace";

#define BUFFER_SIZE	         256
#define SYSTEM_ADDRESS       0x70000000 //操作系统内核地址空间

volatile BOOL bEnabled = FALSE; //Plugin switch


// 唯一的一个 PluginApp 对象
PluginApp pluginApp;
// 记录指令日志
InstructionMemo memo;

static HINSTANCE GetGlobalInstance() {
	AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
	HINSTANCE hInst = pModuleState->m_hCurrentInstanceHandle;
	return hInst;
}

extc int _export cdecl ODBG_Plugindata(char shortname[32]) {
	strcpy_s(shortname, 32, g_szPluginName);
	return PLUGIN_VERSION;
}


extc int _export cdecl ODBG_Plugininit(int ollydbgversion, HWND hw, ulong * features) {
	if (ollydbgversion < PLUGIN_VERSION) {
		return -1;
	}

	hinst = GetGlobalInstance();
	hwmain = hw;

	Addtolist(0, 0, "FCT Plugin v0.1");
	Addtolist(0, -1, "Copyright (C) 2017 yezhang989");

	if (Plugingetvalue(VAL_RESTOREWINDOWPOS) != 0 && Pluginreadintfromini(hinst, "Restore FCT Window", 0) != 0) {
		CreateFCTWindow();
	}
	return 0;
}
// Function adds items to main OllyDbg menu (origin=PM_MAIN).
extc int _export cdecl ODBG_Pluginmenu(int origin, char data[4096], void *item) {
	switch (origin)
	{
	case PM_MAIN:
		strcpy_s(data, 4096, "0 &Open|2 &About");
		break;
	case PM_DISASM:
		strcpy_s(data, 4096, "0 &标记并跟踪");
		break;
	default:
		return 0;
	}


	return 1;
};

void handleMainMenu(int action, void * item) {
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
}

//处理反汇编界面上的右键菜单
void handleDisasmMenu(int action, void * item) {
	t_dump * dump = NULL;
	t_module * module = NULL;
	char * moduleName = NULL;
	ulong addr;
	t_memory * memory = NULL;
	t_result result;
	char * expr = "[[esp+8]+0xc]";

	switch (action)
	{
	case 0:
		//标记并设置断点

		if (hwtrace == NULL) {
			CreateFCTWindow();
		}
		dump = (t_dump *)item;
		addr = dump->addr; //CPU指令地址

		module = Findmodule(addr);
		if (module == 0){
			return;
		}

		moduleName = module->name;
		memory = Findmemory(addr);

		Expression(&result, expr, 0, 0, NULL, dump->base, dump->size, dump->threadid);

		if (result.type == DEC_UNKNOWN)
		{//表达式出错

		}
		break;
	default:
		break;
	}
}

// Receives commands from main menu.
extc void _export cdecl ODBG_Pluginaction(int origin, int action, void *item) {

	switch (origin) {
	case PM_MAIN:
		handleMainMenu(action, item);
		break;
	case PM_DISASM:
		handleDisasmMenu(action, item);
		break;
	default:break;
	}

};

// Command line window recognizes global shortcut Alt+F1.
extc int _export cdecl ODBG_Pluginshortcut(
	int origin, int ctrl, int alt, int shift, int key, void *item) {
	if (ctrl == 0 && alt == 1 && shift == 0 && key == VK_F1) {

		Addtolist(0, 0, "Pressed Alt + F1");

		return 1;
	};                       // Shortcut recognized
	return 0;                            // Shortcut not recognized
};

// User opens new or restarts current application, clear command line history.
extc void _export cdecl ODBG_Pluginreset(void) {


};

// OllyDbg calls this optional function when user wants to terminate OllyDbg.
extc int _export cdecl ODBG_Pluginclose(void) {

	// For automatical restoring, mark in .ini file whether command line window
	// is still open and save coordinates. (WM_CLOSE is not sent in this case).
	Pluginwriteinttoini(hinst, "Restore command line window", hwtrace != NULL);
	if (hwtrace != NULL) {
		//GetWindowRect(hwcmd, &rc);
		//Pluginwriteinttoini(hinst, "Command line window X", rc.left);
		//Pluginwriteinttoini(hinst, "Command line window Y", rc.top);
	};
	DestroyFCTWindow();

	return 0;
};

void handleCreateProcessEvent(DEBUG_EVENT *debugevent) {
	CREATE_PROCESS_DEBUG_INFO *pCreateProcessInfo;
	pCreateProcessInfo = &debugevent->u.CreateProcessInfo;

}

void handleCreateThread(DEBUG_EVENT *debugevent){
	CREATE_THREAD_DEBUG_INFO createThreadInfo = debugevent->u.CreateThread;
}

/*
 * EXCEPTION_RECORD, refs to
 * https://msdn.microsoft.com/en-us/library/windows/desktop/aa363082(v=vs.85).aspx
 */
void handleException(DEBUG_EVENT *debugevent){
	EXCEPTION_DEBUG_INFO exceptionInfo = debugevent->u.Exception;
	EXCEPTION_RECORD eRecord = exceptionInfo.ExceptionRecord;

	DWORD eCode = eRecord.ExceptionCode;
	switch (eCode)
	{
	case EXCEPTION_ACCESS_VIOLATION:
		break;
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
		break;
	case EXCEPTION_BREAKPOINT:

		break;

	case EXCEPTION_SINGLE_STEP:
		break;
	case EXCEPTION_STACK_OVERFLOW:
		break;
	default:
		break;
	}

}

void handleExitProcess(DEBUG_EVENT *debugevent){
	EXIT_PROCESS_DEBUG_INFO exitProcessInfo = debugevent->u.ExitProcess;
}

void handleExitThread(DEBUG_EVENT *debugevent){
	EXIT_THREAD_DEBUG_INFO exitThreadInfo = debugevent->u.ExitThread;
}

void handleLoadDll(DEBUG_EVENT *debugevent) {
	LOAD_DLL_DEBUG_INFO loadDllInfo = debugevent->u.LoadDll;
}

void handleOutputDebugString(DEBUG_EVENT *debugevent){
	OUTPUT_DEBUG_STRING_INFO debugStringInfo = debugevent->u.DebugString;
}

void handleRip(DEBUG_EVENT *debugevent){
	RIP_INFO ripInfo = debugevent->u.RipInfo;
}

void handleUnLoadDll(DEBUG_EVENT *debugevent) {
	UNLOAD_DLL_DEBUG_INFO uploadDllInfo = debugevent->u.UnloadDll;
}

//extc 
void ODBG_Pluginmainloop(DEBUG_EVENT *debugevent){
	if (debugevent == NULL)
	{
		return;
	}


	switch (debugevent->dwDebugEventCode)
	{
	case CREATE_PROCESS_DEBUG_EVENT:
		handleCreateProcessEvent(debugevent);
		break;
	case CREATE_THREAD_DEBUG_EVENT:
		handleCreateThread(debugevent);
		break;
	case EXCEPTION_DEBUG_EVENT:
		handleException(debugevent);
		break;
	case EXIT_PROCESS_DEBUG_EVENT:
		handleExitProcess(debugevent);
		break;
	case EXIT_THREAD_DEBUG_EVENT:
		handleExitThread(debugevent);
		break;
	case LOAD_DLL_DEBUG_EVENT:
		handleLoadDll(debugevent); //此时应加载符号表
		break;
	case OUTPUT_DEBUG_STRING_EVENT:
		handleOutputDebugString(debugevent);
		break;
	case RIP_EVENT:
		handleRip(debugevent); //当被调试进程在调试器控制之外，意外退出时发生
		break;
	case UNLOAD_DLL_DEBUG_EVENT:
		handleUnLoadDll(debugevent); //此时应卸载符号表
		break;
	default:
		break;
	}
}

void FindModules() {
	t_table * pModules = (t_table*)Plugingetvalue(VAL_MODULES);
}

void FindBreakPoints() {
	t_table * pBreakpoints = (t_table*)Plugingetvalue(VAL_BREAKPOINTS);
}

extc int _export cdecl ODBG_Pausedex(int reason, int extdata, t_reg *reg, DEBUG_EVENT *debugevent){
	int stepMode;
	DWORD dwReturnAddress, dwSkipAddress;
	char  cSymbol[BUFFER_SIZE], comment[TEXTLEN];

	t_result result;
	char * expr = "[[esp+8]+0xc]";

	t_memory * memory = NULL;
	ulong ip = reg->ip;

	BYTE cmd[MAXCMDSIZE];

	ulong cmdLen = Readcommand(ip, (PCHAR)cmd); //读取指令
	uchar srcdes[MAXCMDSIZE];

	t_disasm disams;
	ulong des;

	char disamResult[TEXTLEN];

	if (cmdLen == 0)
	{
		return 0;
	}


	cmdLen = Disasm(cmd, cmdLen, ip, srcdes, &disams, DISASM_ALL, debugevent->dwThreadId);
	if (cmdLen == 0)
	{
		return 0;
	}

	//默认为单步步入操作
	stepMode = STEP_IN;
	dwSkipAddress = 0;

	char callSymbol[BUFFER_SIZE];
	char callComment[TEXTLEN];
	char retSymbol[BUFFER_SIZE];
	char retComment[TEXTLEN];

	int symLen = 0;

	InstLogItem* pItem;

	switch (disams.cmdtype)
	{
	case C_JMP:
		strcpy_s(disamResult, strlen(disams.result) + 1, disams.result);
		if (disams.jmpconst != 0)
		{
			//是常量跳转指令
			des = disams.jmpconst;
		}
		else
		{
			des = disams.jmpaddr;
		}

		memset(callSymbol, 0x00, BUFFER_SIZE);
		memset(callComment, 0x00, TEXTLEN);

		symLen = Decodeaddress(disams.jmpaddr, 0, ADC_VALID | ADC_JUMP, cSymbol, BUFFER_SIZE, comment);

		if (symLen != 0)
		{
			strcpy_s(callSymbol, cSymbol);
			strcpy_s(callComment, comment);
		}

		pItem = InstLogItem::Create(disams.ip, disams.jmpaddr, callSymbol, callComment);


		
		break;
	case C_JMC:
		break;
	case C_CAL:
		
		memset(callSymbol, 0x00, BUFFER_SIZE);
		memset(callComment, 0x00, TEXTLEN);
		memset(retSymbol, 0x00, BUFFER_SIZE);
		memset(retComment, 0x00, TEXTLEN);

		//处理 call 指令
		dwReturnAddress = reg->ip + cmdLen;
		symLen = Decodeaddress(disams.jmpaddr, 0, ADC_VALID | ADC_JUMP, cSymbol, BUFFER_SIZE, comment);

		if (symLen != 0)
		{
			strcpy_s(callSymbol, cSymbol);
			strcpy_s(callComment, comment);
		}
		symLen = Decodeaddress(dwReturnAddress, 0, ADC_VALID | ADC_JUMP, cSymbol, BUFFER_SIZE, comment);
		if (symLen != 0)
		{
			strcpy_s(retSymbol, cSymbol);
			strcpy_s(retComment, comment);
		}

		pItem = InstLogItem::Create(disams.ip, disams.jmpaddr, callSymbol, callComment, retSymbol, retComment);

		{
			CallStackItem item = {
				disams.ip,
				dwReturnAddress
			};
			memo.WillCall(pItem, item);
		}
		
		pItem = NULL;

		break;
	case C_RET:
		memset(callSymbol, 0x00, BUFFER_SIZE);
		memset(callComment, 0x00, TEXTLEN);
		memset(retSymbol, 0x00, BUFFER_SIZE);
		memset(retComment, 0x00, TEXTLEN);


		// 处理 RET 指令
		symLen = Decodeaddress(disams.jmpaddr, 0, ADC_VALID | ADC_JUMP, cSymbol, BUFFER_SIZE, comment);
		if (symLen != 0)
		{
			strcpy_s(retSymbol, cSymbol);
			strcpy_s(retComment, comment);
		}

		pItem = InstLogItem::Create(ip, disams.jmpaddr, retSymbol, retComment);

		memo.WillReturn(pItem);

		pItem = NULL;

		break;
	case C_REP:
		stepMode = STEP_SKIP;
		dwSkipAddress = reg->ip + cmdLen;
		break;
	default:
		break;
	}



	memory = Findmemory(reg->ip);

	Expression(&result, expr, 0, 0, NULL, memory->base, memory->size, Getcputhreadid());

	if (result.type == DEC_UNKNOWN)
	{//表达式出错

	}

	NotifyWindow(FCT_OD_PAUSEDEX,(WPARAM)reason, (LPARAM)reg);


	return 0;
}

static void NotifyWindow(UINT message, WPARAM wParam, LPARAM lParam) {
	MSG msg;
	msg.hwnd = NULL;
	msg.message = message;
	msg.wParam = wParam;
	msg.lParam = lParam;
	msg.time = ::GetMessageTime();
	DWORD loc = ::GetMessagePos();
	msg.pt.x = LOWORD(loc);
	msg.pt.y = HIWORD(loc);

	pluginApp.PreTranslateMessage(&msg);	
}



// 窗口插件主窗体
static HWND CreateFCTWindow(){

	pluginApp.m_nCmdShow = SW_SHOW;
	pluginApp.OpenWindow();

	CWnd* hwnd = pluginApp.GetMainWnd();

	hwtrace = hwnd->GetSafeHwnd();

	return hwtrace;
}



BOOL DestroyFCTWindow() {

	return TRUE;
}




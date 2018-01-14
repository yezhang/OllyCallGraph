
// MFCApplication1.h : MFCApplication1 应用程序的主头文件
//
#pragma once
#include "../stdafx.h"

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "../resource.h"       // 主符号


// CMFCApplication1App:
// 有关此类的实现，请参阅 MFCApplication1.cpp
//

class PluginApp : public CWinAppEx
{
public:
	PluginApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	// for translating Windows messages in main message pump
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
	
	BOOL OpenWindow();
	
// 实现
protected:
	HMENU m_hMDIMenu;
	HACCEL m_hMDIAccel;

public:
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	
	DECLARE_MESSAGE_MAP()
};

extern PluginApp pluginApp;

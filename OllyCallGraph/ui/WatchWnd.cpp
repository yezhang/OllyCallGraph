#include "../stdafx.h"

#include "WatchWnd.h"



CWatchWnd::CWatchWnd()
{
}


CWatchWnd::~CWatchWnd()
{
}



BEGIN_MESSAGE_MAP(CWatchWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int CWatchWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	DWORD style = TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT |
		WS_CHILD | WS_VISIBLE | TVS_SHOWSELALWAYS | TVS_FULLROWSELECT;
	CRect dump(0, 0, 200, 200);
	if (!m_wndTree.Create(style, dump, this, 1))
		return -1;

	return 0;
}

void CWatchWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	m_wndTree.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
}

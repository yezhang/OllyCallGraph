#pragma once

class CWatchWnd :
	public CDockablePane
{
public:
	CWatchWnd();
	virtual ~CWatchWnd();

	void AdjustLayout();

	/*
	 * 在CPU指令到达 addr 处时，评估表达式 expression
	 */
	void AddWatch(CString addr, CString expression);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:
	CTreeCtrl m_wndTree;
	CListCtrl m_wndList;

	void MakeDefaultColumns();
	void AutoResizeColumns();
};


#pragma once

class CWatchWnd :
	public CDockablePane
{
public:
	CWatchWnd();
	virtual ~CWatchWnd();

	void AdjustLayout();	

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


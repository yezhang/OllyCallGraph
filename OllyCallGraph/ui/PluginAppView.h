
// MFCApplication1View.h : CMFCApplication1View 类的接口
//

#pragma once


class CPluginAppView : public CTreeView
{
protected: // 仅从序列化创建
	CPluginAppView();
	DECLARE_DYNCREATE(CPluginAppView)

// 特性
public:
	CPluginAppDoc* GetDocument() const;

// 操作
public:

// 重写
public:	
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate(); // called first time after construct

protected:
	

// 实现
public:
	virtual ~CPluginAppView();


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CPluginAppView.cpp 中的调试版本
inline CPluginAppDoc* CPluginAppView::GetDocument() const
{ return reinterpret_cast<CPluginAppDoc*>(m_pDocument); }
#endif


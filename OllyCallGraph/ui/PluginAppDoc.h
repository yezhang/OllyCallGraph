#pragma once
#include "../stdafx.h"
#include "../modal/InstructionMemo.h"

class CPluginAppDoc : public CDocument
{
protected:
	CPluginAppDoc();
	DECLARE_DYNCREATE(CPluginAppDoc)
// 特性
private:
	InstructionMemo memo;

public:
	InstructionMemo& getMemo();
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif 

public:
	virtual ~CPluginAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif 
};


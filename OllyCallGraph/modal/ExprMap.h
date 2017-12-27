#pragma once
#include "../stdafx.h"

class CExprMap
{
private:
	DWORD m_addr;

	std::vector<CString> exprList; //使用表达式类

public:
	CExprMap();
	CExprMap(DWORD addr);
	CExprMap(const CExprMap& rhs); //copy constructor

	virtual ~CExprMap();

	/**
	* 给当前地址添加表达式记录
	*/
	void AddWatch(CString expression);

	void replaceExpr(int index, CString expr);

	void removeWatch(CString expression);

	bool containsWatch(CString expression);

	void clearWatches();
};


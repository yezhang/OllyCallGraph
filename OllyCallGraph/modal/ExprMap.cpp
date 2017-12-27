#include "ExprMap.h"


CExprMap::CExprMap(DWORD addr) : m_addr(addr)
{
}


CExprMap::CExprMap()
{

}

CExprMap::CExprMap(const CExprMap& rhs) : m_addr(rhs.m_addr)
{
	this->exprList.insert(exprList.end(), rhs.exprList.begin(), rhs.exprList.end());
}

CExprMap::~CExprMap()
{
	this->exprList.clear();
}


void CExprMap::AddWatch(CString expression)
{
	if (!containsWatch(expression))
	{
		this->exprList.push_back(expression);
	}

}

void CExprMap::replaceExpr(int index, CString expr)
{
	ASSERT(index >= 0 && index < this->exprList.size());
	this->exprList[index] = expr;
}

void CExprMap::removeWatch(CString expression){
	if (containsWatch(expression))
	{
		exprList.erase(std::remove(exprList.begin(), exprList.end(), expression),
			exprList.end());
	}
}

bool CExprMap::containsWatch(CString expression)
{
	bool found = (std::find(exprList.begin(), exprList.end(), expression) != exprList.end());

	return found;
}

void CExprMap::clearWatches()
{
	this->exprList.clear();
}

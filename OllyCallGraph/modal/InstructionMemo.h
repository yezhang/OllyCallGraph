#pragma once
#include "../stdafx.h"
#include "./InstLogItem.h"

#include "Tree.h"

using namespace std;
using namespace od;


typedef struct InstStackItem {
	DWORD dwCallerIP;
	DWORD dwReturnAddress; //主函数中，call 指令的下一条指令; 也等于 [esp - 4]
} CallStackItem, *pCallStackItem;


// 指令备忘录，用于记录插件的内部数据
class InstructionMemo :CObject
{
	DECLARE_SERIAL(InstructionMemo)

private:
	/**
	 * Key type is std::string, storing an cpu instruction address in memory dump.
	 * 
	 */
	typedef CTree<InstLogItem*> CallTreeNode;

	CallTreeNode m_callTree;

	/**
	 * 函数调用的全局上下文，当call指令第一次发生时，将指令地址记录到该上下文中。
	 */
	CallTreeNode* m_pGlobalContext; 

	/**
	 * 当前执行指令所在的函数上下文
	 */
	CallTreeNode* m_pCurrentContext;

	stack<CallStackItem> callStack;

public:
	InstructionMemo();
	virtual ~InstructionMemo();

	/*
	 * 在当前函数上下文中，监控指定 CPU 指令地址。
	 * 创建一条日志。
	 */
	void WatchAddr(DWORD addr);

	/*
	 * 暂停到 CALL 指令时，进行记录
	 * 创建一条日志。
	 */
	void WillCall(InstLogItem* logItem, CallStackItem &callItem);

	/*
	 * 暂停到 RET 指令时，进行记录
	 * 创建一条日志。
	 */
	void WillReturn(InstLogItem* logItem);

	void DestroyAllWatches(CallTreeNode &elem);

	/**
	 * m_callTree(data == NULL)
	 *    |
	 *    ├-m_globalContext(data == NULL)
	 *    |   
	 */
	void ResetGlobalContext();



protected:
	void ClearTree(CallTreeNode & tree);

private:
	/**
	 * 将 DWORD 转换为 string 类型。
	 */
	std::string CString2String(CString str);

	void addLogItem(InstLogItem* logItem);

};


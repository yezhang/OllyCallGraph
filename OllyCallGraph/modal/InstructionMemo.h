#pragma once
#include "../stdafx.h"
#include "./InstLogItem.h"


using namespace std;

namespace pt = boost::property_tree;

typedef struct InstStackItem {
	DWORD dwCallerIP;
	DWORD dwReturnAddress; //主函数中，call 指令的下一条指令; 也等于 [esp - 4]
} CallStackItem, *pCallStackItem;


// 指令备忘录，用于记录插件的内部数据
class InstructionMemo :CObject
{
private:
	pt::ptree functionTreeRoot;
	stack<CallStackItem> callStack;

public:
	InstructionMemo();
	virtual ~InstructionMemo();

private:
	/*
	 * 在当前函数上下文中，监控指定 CPU 指令地址。
	 */
	void WatchAddr(DWORD addr);

	/*
	 * 暂定到 CALL 指令时，进行记录
	 */
	void WillCall(InstLogItem* logItem, CallStackItem &callItem);

	/*
	 * 暂停到 RET 指令时，进行记录
	 */
	void WillReturn(InstLogItem* logItem);

	void DestroyAll();

	DECLARE_SERIAL(InstructionMemo)
};


#pragma once
#include "../stdafx.h"
#define MEMO_DELETE(x) {delete x; x = NULL;}

using namespace std;

namespace pt = boost::property_tree;

typedef struct InstStackItem {
	DWORD dwCallerIP;
	DWORD dwReturnAddress; //主函数中，call 指令的下一条指令; 也等于 [esp - 4]
} CallItem, *pCallItem;


class InstLogItem 
{
private:
	CString* pJmpAddr;
	CString* pCallSymbol;
	CString* pCallComment;
	CString* pRetSymbol;
	CString* pRetComment;
	InstLogItem();
	~InstLogItem();

public:
	static InstLogItem* Create(DWORD dwInstructionAddress, char jmpSymbol[256], char jmpComment[256], char retSymbol[256], char retComment[256]);
	static InstLogItem* Create(DWORD dwInstructionAddress, char jmpSymbol[256], char jmpComment[256]);
	static void Destroy(InstLogItem ** pInstLogItem);
};


// 指令备忘录，用于记录插件的内部数据
class InstructionMemo
{
private:
	pt::ptree functionTreeRoot;
	stack<CallItem> callStack;

public:
	InstructionMemo();
	virtual ~InstructionMemo();

private:
	
	void InsertInstruction(char * instruction);
	void Call(CallItem &callItem);
	void Return();
};


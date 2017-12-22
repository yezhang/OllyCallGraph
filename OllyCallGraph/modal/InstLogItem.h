#pragma once
#include "../stdafx.h"

class InstructionMemo;

class InstLogItem : CObject
{
	friend class InstructionMemo;

private:
	CString* pJmpAddr; //jump target address
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

	DECLARE_SERIAL(InstLogItem)
};
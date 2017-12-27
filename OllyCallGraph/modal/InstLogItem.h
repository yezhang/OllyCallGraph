#pragma once
#include "../stdafx.h"

class InstructionMemo;

class InstLogItem : CObject
{
	DECLARE_SERIAL(InstLogItem)

	friend class InstructionMemo;

private:
	CString* ip; //address of instruction in cpu.
	DWORD	 dwIp; //same as ip.
	CString* pJmpAddr; //jump target address
	DWORD	 dwJmpAddr; //same as pJmpAddr.
	CString* pJmpSymbol;
	CString* pJmpComment;
	CString* pRetSymbol;
	CString* pRetComment;
	InstLogItem();
	~InstLogItem();

	

public:
	

	//************************************
	// Method:    Create，创建 CALL 指令时调用
	// FullName:  InstLogItem::Create
	// Access:    public static 
	// Returns:   InstLogItem*
	// Qualifier:
	// Parameter: DWORD ip
	// Parameter: DWORD jmpAddr
	// Parameter: char jmpSymbol[256]
	// Parameter: char jmpComment[256]
	// Parameter: char retSymbol[256]
	// Parameter: char retComment[256]
	//************************************
	static InstLogItem* Create(DWORD ip, DWORD jmpAddr, char jmpSymbol[256], char jmpComment[256], char retSymbol[256], char retComment[256]);
	
	//************************************
	// Method:    Create，创建 RET 指令时调用
	// FullName:  InstLogItem::Create
	// Access:    public static 
	// Returns:   InstLogItem*
	// Qualifier:
	// Parameter: DWORD ip
	// Parameter: DWORD jmpAddr
	// Parameter: char jmpSymbol[256]
	// Parameter: char jmpComment[256]
	//************************************
	static InstLogItem* Create(DWORD ip, DWORD jmpAddr, char jmpSymbol[256], char jmpComment[256]);


	//************************************
	// Method:    Create，标记某一条指令时调用
	// FullName:  InstLogItem::Create
	// Access:    public static 
	// Returns:   InstLogItem*
	// Qualifier:
	// Parameter: DWORD ip
	//************************************
	static InstLogItem* Create(DWORD ip);
	
	static void Destroy(InstLogItem ** pInstLogItem);


};
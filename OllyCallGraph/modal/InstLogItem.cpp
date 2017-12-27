#include "InstLogItem.h"

IMPLEMENT_SERIAL(InstLogItem, CObject, 0)

InstLogItem::InstLogItem()
{

}

InstLogItem::~InstLogItem()
{
	OD_DELETE(this->ip);
	OD_DELETE(this->pJmpAddr);
	OD_DELETE(this->pJmpSymbol);
	OD_DELETE(this->pJmpComment);
	OD_DELETE(this->pRetSymbol);
	OD_DELETE(this->pRetComment);
}




InstLogItem* InstLogItem::Create(DWORD ip, DWORD jmpAddr, char jmpSymbol[256], char jmpComment[256], char retSymbol[256], char retComment[256])
{
	InstLogItem* item = new InstLogItem;
	ASSERT(ip > 0);

	item->dwIp = ip;
	item->ip = new CString;
	item->ip->Format(_T("0x%.8x"), ip);

	if (jmpAddr > 0)
	{
		item->dwJmpAddr = jmpAddr;
		item->pJmpAddr = new CString;
		item->pJmpAddr->Format(_T("0x%.8x"), jmpAddr);
	}

	if (jmpSymbol != NULL)
	{
		item->pJmpSymbol = new CString(jmpSymbol);
	}
	if (jmpComment != NULL)
	{
		item->pJmpComment = new CString(jmpComment);
	}
	if (retSymbol != NULL)
	{
		item->pRetSymbol = new CString(retSymbol);
	}
	if (retComment != NULL)
	{
		item->pRetComment = new CString(retComment);
	}

	return item;
}

InstLogItem* InstLogItem::Create(DWORD ip, DWORD jmpAddr, char jmpSymbol[256], char jmpComment[256])
{
	return InstLogItem::Create(ip, jmpAddr, jmpSymbol, jmpComment, NULL, NULL);
}


InstLogItem* InstLogItem::Create(DWORD ip)
{
	return InstLogItem::Create(ip, 0, NULL, NULL);
}

void InstLogItem::Destroy(InstLogItem**pInstLogItem)
{
	delete *pInstLogItem;
	*pInstLogItem = NULL;
}


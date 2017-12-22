#include "InstLogItem.h"

IMPLEMENT_SERIAL(InstLogItem, CObject, 0)

InstLogItem::InstLogItem()
{

}

InstLogItem::~InstLogItem()
{
	OD_DELETE(this->pCallSymbol);
	OD_DELETE(this->pCallComment);
	OD_DELETE(this->pRetSymbol);
	OD_DELETE(this->pRetComment);
}


InstLogItem* InstLogItem::Create(DWORD dwInstructionAddress, char jmpSymbol[256], char jmpComment[256], char retSymbol[256], char retComment[256])
{
	InstLogItem* item = new InstLogItem;
	ASSERT(dwInstructionAddress > 0);

	item->pJmpAddr = new CString;
	item->pJmpAddr->Format(_T("0x%.8x"), dwInstructionAddress);

	if (jmpSymbol != NULL)
	{
		item->pCallSymbol = new CString(jmpSymbol);
	}
	if (jmpComment != NULL)
	{
		item->pCallComment = new CString(jmpComment);
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

InstLogItem* InstLogItem::Create(DWORD dwInstructionAddress, char jmpSymbol[256], char jmpComment[256])
{
	return InstLogItem::Create(dwInstructionAddress, jmpSymbol, jmpComment, NULL, NULL);
}


void InstLogItem::Destroy(InstLogItem**pInstLogItem)
{
	delete *pInstLogItem;
	*pInstLogItem = NULL;
}


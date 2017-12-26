#include "InstructionMemo.h"


IMPLEMENT_SERIAL(InstructionMemo, CObject, 0)


InstructionMemo::InstructionMemo()
{
	m_pGlobalContext = new CallTreeNode;

	// add the global context to the tree with its one copy.
	m_pCurrentContext = &m_callTree.addChild(*m_pGlobalContext);
	
	delete m_pGlobalContext; //delete the temporary Object

	m_pGlobalContext = m_pCurrentContext; //fix the global context pointer.
}


InstructionMemo::~InstructionMemo()
{
	ClearTree(m_callTree);
}

void InstructionMemo::addLogItem(InstLogItem* pItem)
{
	string ipStr = CString2String(*pItem->ip);
	CallTreeNode instNode;
	instNode.putValue(pItem);

	this->m_pCurrentContext->addChild(instNode);
}

void InstructionMemo::WatchAddr(DWORD addr)
{
	InstLogItem* pItem = InstLogItem::Create(addr);
	
	this->addLogItem(pItem);
}

void InstructionMemo::WillCall(InstLogItem* pItem, CallStackItem &callItem)
{
	ASSERT(pItem != NULL);

	string ipStr = CString2String(*pItem->ip);

	CallTreeNode instNode;
	instNode.putValue(pItem);

	this->m_pCurrentContext = &this->m_pCurrentContext->addChild(instNode);

	this->callStack.push(callItem); //make a copy of callItem
}

void InstructionMemo::WillReturn(InstLogItem* pItem)
{
	ASSERT(pItem != NULL);
	this->callStack.pop();
	this->m_pCurrentContext = &this->m_pCurrentContext->parent();
	
	this->addLogItem(pItem);
}

void InstructionMemo::ResetGlobalContext()
{
	ClearTree(*m_pGlobalContext);
}

void InstructionMemo::ClearTree(CallTreeNode & tree)
{
	DestroyAllWatches(tree);
	tree.clear();
}


std::string InstructionMemo::CString2String(CString str)
{
	// Convert a TCHAR string to a LPCSTR
	CT2CA pszConvertedAnsiString(str);
	// construct a std::string using the LPCSTR input
	std::string ipStr(pszConvertedAnsiString);
	return ipStr;
}



void InstructionMemo::DestroyAllWatches(CallTreeNode &elem)
{	

	//释放自己的数据
	InstLogItem* data = elem.value();
	if (data != NULL){
		InstLogItem::Destroy(&data);
	}

	if (elem.isEmpty())
	{
		return;
	}

	//遍历孩子

	for (CallTreeNode::iterator v = elem.begin(); v != elem.end(); ++v) {
		//InstLogItem* data = v->second.get_value<InstLogItem*>();
		CallTreeNode & subtree = *v;
		DestroyAllWatches(subtree);
	}

}





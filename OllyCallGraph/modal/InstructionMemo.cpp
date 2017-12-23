#include "InstructionMemo.h"

#include <boost/property_tree/json_parser.hpp>

IMPLEMENT_SERIAL(InstructionMemo, CObject, 0)



InstructionMemo::InstructionMemo()
{
	m_callTree.put_child("global", m_globalContext);
	m_pCurrentContext = &m_globalContext;
}


InstructionMemo::~InstructionMemo()
{
}

void InstructionMemo::WatchAddr(DWORD addr)
{
	
	InstLogItem* pItem = InstLogItem::Create(addr);
	// Convert a TCHAR string to a LPCSTR
	CT2CA pszConvertedAnsiString(*pItem->ip);
	// construct a std::string using the LPCSTR input
	std::string ipStr(pszConvertedAnsiString);

	CallTreeNode instNode;	
	instNode.put_value(pItem);

	this->m_pCurrentContext->add_child(ipStr, instNode);
}

void InstructionMemo::WillCall(InstLogItem* logItem, CallStackItem &callItem)
{

}

void InstructionMemo::WillReturn(InstLogItem* logItem)
{

}

void InstructionMemo::DestroyAllWatches(CallTreeNode &elem)
{	

	//释放自己的数据
	InstLogItem* data = elem.get_value<InstLogItem*>();
	if (data != NULL){
		InstLogItem::Destroy(&data);
	}

	if (elem.empty())
	{
		return;
	}

	//遍历孩子

	for (CallTreeNode::iterator v = elem.begin(); v != elem.end(); ++v) {
		//InstLogItem* data = v->second.get_value<InstLogItem*>();
		CallTreeNode & subtree = v->second;
		DestroyAllWatches(subtree);
	}

}

void InstructionMemo::DestroyAll()
{
	DestroyAllWatches(*m_pCurrentContext);
	m_pCurrentContext->clear();
}


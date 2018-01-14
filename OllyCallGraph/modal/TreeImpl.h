#pragma once
#include <algorithm>
#include <vector>

#include "Tree.h"

namespace od {
	template<class Data>
	CTree<Data>::CTree() :m_data(data_type())
	{
		this->m_pParent = this;
		this->m_pRoot = this;
	}

	template<class Data>
	CTree<Data>::~CTree()
	{
		this->m_pParent = NULL;
		this->m_pRoot = NULL;
		this->m_data = data_type();
		this->m_children.clear();
	}


	template<class Data>
	bool od::CTree<Data>::operator==(const od::CTree<Data>& rhs) const
	{
		if (this->m_pRoot != rhs.m_pRoot)
		{
			return false;
		}
		if (this->m_pParent != rhs.m_pParent)
		{
			return false;
		}
		return this->m_data == rhs.m_data;
	}


	template<class Data>
	bool od::CTree<Data>::operator!=(const od::CTree<Data>& rhs) const
	{
		return !(this == rhs);
	}


	template<class Data>
	void CTree<Data>::clear()
	{
		this->m_data = data_type();
		this->m_children.clear();
	}

	template<class Data>
	CTree<Data>& CTree<Data>::root()
	{
		return *this->m_pRoot;
	}

	template<class Data>
	CTree<Data>& CTree<Data>::parent()
	{
		return *this->m_pParent;
	}


	template<class Data>
	Data od::CTree<Data>::value()
	{
		return this->m_data;
	}


	template<class Data>
	typename CTree<Data>::iterator CTree<Data>::end()
	{
		return this->m_children.begin();
	}

	template<class Data>
	typename CTree<Data>::iterator CTree<Data>::begin()
	{
		return this->m_children.end();
	}


	template<class Data>
	bool CTree<Data>::isRoot()
	{
		return this == this->m_pRoot&& this == this->m_pParent;
	}

	template<class Data>
	bool CTree<Data>::isEmpty()
	{
		return this->m_children.empty();
	}

	template<class Data>
	void CTree<Data>::putValue(Data data)
	{
		this->m_data = data;
	}

	template<class Data>
	void CTree<Data>::removeChild(self_type& child)
	{
		std::list<self_type>::iterator itr = std::find(this->m_children.begin(), this->m_children.end(), child);
		if (itr == this->m_children.end())
		{
			return;
		}

		itr->m_pParent = &(*itr);
		itr->m_pRoot = itr->m_pParent;
		
		this->m_children.remove(*itr);
	}

	template<class Data>
	typename CTree<Data>::self_type& CTree<Data>::addChild(self_type& child)
	{
		child.m_pParent = this;
		child.m_pRoot = this->m_pRoot;
		this->m_children.push_back(child);
		return this->m_children.back();
	}

}
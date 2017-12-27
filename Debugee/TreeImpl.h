#include "Tree.h"

namespace od {
	template<class Data>
	CTree<Data>::CTree()
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
	bool CTree<Data>::operator==(const self_type& rhs) const
	{
		return this->m_data == rhs.m_data;
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
	typename CTree<Data>::self_type& CTree<Data>::removeChild(self_type& child)
	{
		std::list<self_type>::iterator itr = std::find(this->m_children.begin(), this->m_children.end(), 1);
		this->m_children.remove(child);
		return *itr;
	}

	template<class Data>
	typename CTree<Data>::self_type& CTree<Data>::addChild(self_type& child)
	{
		this->m_children.push_back(child);
		return this->m_children.back();
	}

}
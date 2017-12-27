#pragma once
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

namespace od {
	template<class Data>
	class CTree
	{
		/**
		* Simpler way to refer to this CTree\<D\> type.
		*/
		typedef CTree<Data>									self_type;
	public:
		typedef Data										data_type;
		typedef typename std::list<self_type>::iterator		iterator;

		CTree();
		virtual ~CTree();

		self_type& addChild(self_type& child);
		self_type& removeChild(self_type& child);
		void putValue(Data data);

		bool isEmpty();
		bool isRoot();
		self_type& parent();
		self_type& root();
		iterator begin();
		iterator end();
		data_type value();
		void clear();

		//************************************
		// Method:    operator==
		// FullName:  CTree<Data>::operator==
		// Access:    public 
		// Returns:   bool, 如果两个节点的数据域相同，则节点相同
		// Qualifier: const
		// Parameter: const self_type & rhs
		//************************************
		bool operator==(const self_type& rhs) const;

	private:
		self_type* m_pRoot;
		self_type* m_pParent;

		// Hold the data of this node
		data_type m_data;
		// Hold the children - this is a void* because we can't complete the
		// container type within the class.
		std::list<self_type> m_children;
	};

}



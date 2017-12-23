#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

namespace pt = boost::property_tree;

typedef int(*Fun)(int);

typedef struct MyStruct
{
	int a;
	Fun functor;
} Data, *pData;

int globalFun(int a) {
	return a + 1;
}

Data data;



void MakeTree() {

	struct Item {
		unsigned int ip;
	} item, *pItem;


	pt::basic_ptree<std::string, struct Item> root;
	

	pt::ptree defRoot;
	defRoot.put_value("12");

	
	
	std::string val = defRoot.get_value<std::string>();

	item.ip = 0x123;
	
	root.put_value(item);

	pItem = &root.get_value<struct Item>();

	int ip = pItem->ip;
}

void ReadJSON() {
	pt::ptree root;

	std::string fileName = "C:/Users/Administrator/Documents/Visual Studio 2013/Projects/OllyCallGraph/Debugee/in.json";
	try {
		boost::property_tree::read_json(fileName, root);
	}
	catch (std::exception & e)
	{
	}

	std::string val1 = root.get<std::string>("key1");
	int subval = root.get<int>("key2.subkey");	

	pt::ptree &key2Obj = root.get_child("key2");
	subval = key2Obj.get<int>("subkey");
}

int main() {
	data.a = 5;
	data.functor = globalFun;

	//MakeTree();

	ReadJSON();

	data.a = data.functor(data.a);
	
	

	return 0;
}

#ifdef _DEBUG

#include <stdlib.h>
#include <crtdbg.h>

#ifndef DEBUG_NEW
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#endif

#include "Script/LinkedList.hpp"
#include <iostream>


#include <string>
#include "Script/SkipList.hpp"



int main(int argc, char* argv[])
{
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	

	//LinkedList<int> *list = new LinkedList<int>();
	/*list->AddToHead(1);
	list->AddToHead(2);
	list->AddToLast(5);
	list->AddToLast(232);
	list->AddToLast(43);
	list->AddToLast(111);
	list->DeleteFromHead();
	list->ForEach([](int& i){
		i++;
	});
	int& a = list->GetFromHead();
	list->DeleteFromHead();
	std::cout << a << std::endl;
	delete list;*/
	/*auto p = std::make_shared<int>(1);
	auto q= std::make_shared<int>(3);
	p = q;*/
	
	/*std::cout << *p;*/


	SkipList<int, std::string> skipList(4);
	skipList.Insert(1,"111");
	skipList.Insert(2, "222");
	skipList.Insert(4, "444");
	skipList.Insert(7, "777");
	skipList.Insert(2, "222");
	skipList.Insert(5, "555");
	skipList.Insert(3, "333");
	std::cout<<skipList.GetValue(5);
	system("pause");
}

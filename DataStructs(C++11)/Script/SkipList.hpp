#pragma once
#include <vector>
#include <memory>
#include <random>
#include <ctime>

template <class K, class V>
class SkipListNode
{
public:
	SkipListNode(const K& key, const V& value)
		: key(key),
		value(value)
	{
	}

	SkipListNode()
	{
	} 

	K key;
	V value;
	std::vector<std::shared_ptr<SkipListNode>> nextNodes;
};
template <class K, class V>
class SkipList
{
private:
	int maxLayerCount=4;
	std::shared_ptr<SkipListNode<K, V>> headNode;
	int GetRandomLayerCount();

	std::default_random_engine  rd;
	std::uniform_int_distribution <int> u;
public:
	void Insert(const K& key,const V& value);
	const V& GetValue(const K& key) const;


	explicit SkipList(int max_layer_count)
		: maxLayerCount(max_layer_count), headNode(new SkipListNode<K,V>()), rd(time(NULL)), u(1, max_layer_count)
	{
		for (int i = 0; i < maxLayerCount;i++)
		{
			headNode->nextNodes.push_back(nullptr);

		}
	
	}
};

template <class K, class V>
int SkipList<K, V>::GetRandomLayerCount()
{
	
	return  u(rd);
	
}

template <class K, class V>
void SkipList<K, V>::Insert(const K& key, const V& value)
{
	int currentLayer = maxLayerCount - 1;
	std::vector<std::shared_ptr<SkipListNode<K, V>>> preNode(maxLayerCount);
	for (int i = 0; i < maxLayerCount; i++)
	{
		preNode.push_back(nullptr);

	}
	std::shared_ptr<SkipListNode<K, V>> curNode;
	curNode = headNode;
	while (currentLayer >= 0)
	{
		bool isNeedNext = false;
		if (curNode->nextNodes[currentLayer] == nullptr || curNode->nextNodes[currentLayer]->key>key)
		{
			preNode[currentLayer] = curNode;
			isNeedNext = true;
		}
		else if (curNode->nextNodes[currentLayer]->key == key)
		{
			curNode->nextNodes[currentLayer]->value = value;
			return;
		}
		else
		{
			curNode = curNode->nextNodes[currentLayer];
		}

		if (isNeedNext)
		{
			currentLayer--;
		}
	}
	
	auto newNode = std::make_shared<SkipListNode<K,V>>(key,value);
	int newNodeLayerCount= this->GetRandomLayerCount();
	for (int i = 0; i < newNodeLayerCount; i++)
	{
		newNode->nextNodes.push_back(nullptr);
		auto next= preNode[i]->nextNodes[i];
		newNode->nextNodes[i]= next;
		preNode[i]->nextNodes[i] = newNode;
	}
	
}

template <class K, class V>
const V& SkipList<K, V>::GetValue(const K& key) const
{
	int currentLayer = maxLayerCount-1;
	std::vector<std::shared_ptr<SkipListNode<K, V>>> preNode(maxLayerCount);
	for (int i = 0; i < maxLayerCount; i++)
	{
		preNode.push_back(nullptr);

	}
	std::shared_ptr<SkipListNode<K, V>> curNode;
	curNode = headNode;
	while (currentLayer>=0)
	{
		bool isNeedNext = false;
		if(curNode->nextNodes[currentLayer]==nullptr|| curNode->nextNodes[currentLayer]->key>key)
		{
			preNode[currentLayer] = curNode;
			isNeedNext = true;
		}
		else if(curNode->nextNodes[currentLayer]->key==key)
		{
			return curNode->nextNodes[currentLayer]->value;
		}
		else
		{
			curNode = curNode->nextNodes[currentLayer];
		}
		
		if(isNeedNext)
		{
			currentLayer--;
		}
	}
	return NULL;
}





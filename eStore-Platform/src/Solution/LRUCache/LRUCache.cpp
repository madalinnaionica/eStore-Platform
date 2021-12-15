#include "LRUCache.h"
#include <algorithm>

using namespace std;

LRUCache::LRUCache(int capacity)
{
	lru.reserve(capacity); //rezerv capacitatea vectorului, data ca parametru
}

vector<int> LRUCache::processRequests(vector<int> requestsNo)
{
	for (vector<int>::iterator finder = requestsNo.begin(); finder != requestsNo.end(); finder++)
	{
		if (lru.size() == lru.capacity()) // pentru cazul in care cache este plina
		{
			lru.pop_back();					  //sterg ultimul element
			lru.insert(lru.begin(), *finder); //adaug la inceput
		}
		else
		{
			lru.insert(lru.begin(), *finder); //daca mai am spartiu, aduag la inceput
		}
	}
	return lru;
}
int LRUCache::getCapacity()
{
	return capacity;
}

int LRUCache::getSize()
{
	return size;
}

vector<int> LRUCache::getLRU()
{
	return lru;
}
int LRUCache::getLRUCapacity()
{
	return capacity;
}

void LRUCache::setCapacity(int capacity)
{
	this->capacity = capacity;
}

void LRUCache::setLRU(vector<int> aux)
{
	this->lru = aux;
}

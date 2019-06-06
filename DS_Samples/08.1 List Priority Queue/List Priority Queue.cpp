#include <iostream>
using namespace std;
#include <list>

struct ListPriorityQueue
{
	std::list<int> L;										// priority queue contents

	int size() const;										// number of elements
	bool empty() const;										// is the queue empty?
	void insert(const int& e);								// insert element
	const int& min() const;									// minimum element
	void removeMin();										// remove minimum
	bool isLess(const int& e, const int& f) const;			// less-than comparator
	void print();
};

int ListPriorityQueue::size() const
{
	return L.size();
}

bool ListPriorityQueue::empty() const
{
	return L.empty();
}

const int& ListPriorityQueue::min() const
{
	return L.front();										// minimum is at the front
}

bool ListPriorityQueue::isLess(const int& e, const int& f) const
{
	if(e<f) return true;
	else return false;
}

void ListPriorityQueue::insert(const int& e)
{
	std::list<int>::iterator p;
	p = L.begin();											// liste boşken p = L.end() 
	while (p != L.end() && !isLess(e, *p)) ++p;				// find larger element
	L.insert(p, e);											// insert e before p
}

void ListPriorityQueue::removeMin()
{
	L.pop_front();
}

void ListPriorityQueue::print()
{
	std::list<int>::iterator p;
	p = L.begin();

	while (p != L.end())
	{
		cout << *p << " ";
		p++;
	}
}

int main()
{
	ListPriorityQueue PriorityQueue;

	cout <<"Inserting Some Elements ...  " << endl;
	PriorityQueue.insert(7);
	PriorityQueue.insert(2);
	PriorityQueue.insert(5);
	PriorityQueue.insert(4);
	PriorityQueue.insert(3);
	PriorityQueue.insert(6);

	cout << endl <<"Priority Queue Elements : ";
	PriorityQueue.print();

	cout << endl << endl <<"Min = " << PriorityQueue.min() << endl;

	cout << endl <<"Removing Minimum Element ... " << endl;
	PriorityQueue.removeMin();

	cout << endl <<"Min = " << PriorityQueue.min() << endl;

	cout << endl <<"Inserting Some Elements ... " << endl;
	PriorityQueue.insert(1);
	PriorityQueue.insert(8);

	cout << endl <<"Priority Queue Elements : ";
	PriorityQueue.print();

	cout << endl << endl <<"Min = " << PriorityQueue.min() << endl;

	cout << endl <<"Removing Minimum Element ... " << endl;
	PriorityQueue.removeMin();

	cout << endl <<"Min = " << PriorityQueue.min() << endl;

	cout << endl <<"Priority Queue Elements : ";
	PriorityQueue.print();

	::getchar();
}

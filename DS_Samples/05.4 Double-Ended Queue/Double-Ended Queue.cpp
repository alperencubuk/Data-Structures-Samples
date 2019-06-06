#include <string>
#include <iostream>
using namespace std;

struct DoublyNode
{
	string elem;											// element name
	int score;												// element score;
	DoublyNode* next;										// next item in the list
	DoublyNode* prev;										// previous item in the list
};

struct DoublyLinkedList
{
	DoublyNode* header;										// pointer to the header of list
	DoublyNode* trailer;									// pointer to the trailer of list

	DoublyLinkedList();										// empty list constructor
	~DoublyLinkedList();									// destructor
	bool empty() const;										// is list empty?
	const string& front() const;							// get front element
	const string& back() const;								// get back element
	void addFront(const string& e, const int& i);			// add to front of list
	void addBack(const string& e, const int& i);			// add to back of list
	void removeFront();										// remove front item list
	void removeBack();										// remove from back
	void printH2T();
	void printT2H();

	void add(DoublyNode* v, const string& e, const int& i);	// insert new node before v
	void remove(DoublyNode* v);								// remove node v
};

void DoublyLinkedList::addFront(const string& e, const int& i)		// add to front of list
{
	add(header->next, e, i);
}

void DoublyLinkedList::addBack(const string& e, const int& i)		// add to back of list
{
	add(trailer, e, i);
}

void DoublyLinkedList::add(DoublyNode* v, const string& e, const int& i)
{																	// insert new node before v
	DoublyNode* u	= new DoublyNode;				// create a new node for e
	u->elem			= e;
	u->score		= i;

	u->next			= v;							// link u in between v
	u->prev			= v->prev;						// ...and v->prev
	v->prev->next	= u;							// correct code should be
	v->prev			= u;							// like this
	
	//v->prev->next	= v->prev	= u;				// WRONG CODE ! (Page : 127)
}

void DoublyLinkedList::removeFront()								// remove from font
{
	if (empty())
	{
		cout << "List is empty !" << endl;
		return;
	}

	remove(header->next);
}

void DoublyLinkedList::removeBack()									// remove from back
{
	if (empty())
	{
		cout << "List is empty !" << endl;
		return;
	}

	remove(trailer->prev);
}

void DoublyLinkedList::remove(DoublyNode* v)
{																	// remove node v
	DoublyNode* u	= v->prev;										// predecessor
	DoublyNode* w	= v->next;										// successor
	u->next			= w;											// unlink v from list
	w->prev			= u;
	delete v;
}

void DoublyLinkedList::printH2T()
{
	if (empty())
	{
		cout << "List is empty !" << endl;
		return;
	}

	DoublyNode* first = header;
	while (!(first->next == trailer))
	{
		cout << first->next->elem << "\t" << first->next->score << endl;
		first = first->next;
	}
}

void DoublyLinkedList::printT2H()
{
	if (empty())
	{
		cout << "List is empty !" << endl;
		return;
	}

	DoublyNode* last = trailer;
	while (!(last->prev == header))
	{
		cout << last->prev->elem << "\t" << last->prev->score << endl;
		last = last->prev;
	}
}

DoublyLinkedList::DoublyLinkedList()
{													// constructor
	header			= new DoublyNode;				// create sentinels
	trailer			= new DoublyNode;
	header->next	= trailer;						// have them point to each other
	trailer->prev	= header;
}

DoublyLinkedList::~DoublyLinkedList()
{													// destructor
	while (!empty()) removeFront();					// remove all but sentinels
	delete header;									// remove the sentinels
	delete trailer;
}

bool DoublyLinkedList::empty() const				// is list empty?
{
	return (header->next == trailer);
}

const string& DoublyLinkedList::front() const		// get front element
{
	return header->next->elem;
}

const string& DoublyLinkedList::back() const		// get back element
{
	return trailer->prev->elem;
}

struct Double_EndedQueue								// deque as doubly linked list
{
	DoublyLinkedList D;									// linked list of elements
	int n;												// number of elements

	Double_EndedQueue();								// constructor
	int size() const;									// number of items in the deque
	bool empty() const;									// is the deque empty?
	const int& front() ;								// the first element
	const int& back() ;									// the last element
	void insertFront(const string& e, const int& i);	// insert new first element
	void insertBack(const string& e, const int& i);		// insert new last element
	void removeFront() ;								// remove first element
	void removeBack() ;									// remove last element
};

void Double_EndedQueue::insertFront(const string& e, const int& i)		// insert new last element
{
	D.addFront(e, i);
	n++;
}

void Double_EndedQueue::insertBack(const string& e, const int& i)		// remove first element
{
	D.addBack(e, i);
	n++;
}

void Double_EndedQueue::removeFront()									// remove last element
{
	if (empty())
	{
		cout << "removeFront of empty dequeue !" << endl;
		return;
	}

	D.removeFront();
	n--;
}

void Double_EndedQueue::removeBack()
{
	if (empty())
	{
		cout << "removeBack of empty dequeue !" << endl;
		return;
	}

	D.removeBack();
	n--;
}

bool Double_EndedQueue::empty() const				// is list empty?
{
	return (n==0);
}

Double_EndedQueue::Double_EndedQueue()
{													// constructor
	n = 0;
}

int main()
{
	Double_EndedQueue list;

	list.insertFront("Omer", 1000);
	list.insertFront("Oguzhan", 1200);
	list.insertFront("Fatih", 900);
	list.insertFront("Osman", 1500);
	cout << "Inserting some elements to FRONT\n";
	list.D.printH2T();

	list.removeFront();
	cout << "\nRemoving one element from FRONT\n";
	list.D.printH2T();

	list.removeBack();
	cout << "\nRemoving one element from BACK\n";
	list.D.printH2T();

	::getchar();
}
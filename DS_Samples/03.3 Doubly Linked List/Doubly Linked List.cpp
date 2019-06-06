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

	void insertOrdered(const string& e, const int& i);
	void insertOrdered(DoublyNode* newNode, DoublyNode* current);

	void removeOrdered(const string& e, const int& i);

	DoublyLinkedList* mergeLists(DoublyLinkedList* list2);
};

DoublyLinkedList::DoublyLinkedList()				// constructor
{
	header			= new DoublyNode;				// create sentinels
	trailer			= new DoublyNode;
	header->next	= trailer;						// have them point to each other
	trailer->prev	= header;
}

DoublyLinkedList::~DoublyLinkedList()				// destructor
{
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

void DoublyLinkedList::addFront(const string& e, const int& i)		// add to front of list
{
	add(header->next, e, i);
}

void DoublyLinkedList::addBack(const string& e, const int& i)		// add to back of list
{
	add(trailer, e, i);
}

void DoublyLinkedList::add(DoublyNode* v, const string& e, const int& i)	// insert new node before v
{
	DoublyNode* u	= new DoublyNode;				// create a new node for e
	u->elem			= e;
	u->score		= i;

	u->next			= v;							// link u in between v
	u->prev			= v->prev;						// ... and v->prev
	v->prev->next	= u;							// correct code should be
	v->prev			= u;							// like this
	
	//v->prev->next	= v->prev	= u;				// WRONG CODE ! (Page : 127)
}

void DoublyLinkedList::removeFront()				// remove from font
{
	// Liste boş mu?
	if (empty())
	{
		cout << "List is empty !" << endl;
		return;
	}

	remove(header->next);
}

void DoublyLinkedList::removeBack()					// remove from back
{
	// Liste boş mu?
	if (empty())
	{
		cout << "List is empty !" << endl;
		return;
	}

	remove(trailer->prev);
}

void DoublyLinkedList::remove(DoublyNode* v)
{													// remove node v
	DoublyNode* u	= v->prev;						// predecessor
	DoublyNode* w	= v->next;						// successor
	u->next			= w;							// unlink v from list
	w->prev			= u;
	delete v;
}

// Old version : http://ceng2.ktu.edu.tr/~cakir/files/dataStr/VeriYapilari_2012-13Guz_1.Vize_Sorular.pdf
void DoublyLinkedList::insertOrdered(const string& e, const int& i)
{
	DoublyNode* newNode		= new DoublyNode;
	newNode->elem			= e;
	newNode->score			= i;

	DoublyNode* current	= header->next;

	while (current != trailer)
	{
		if(newNode->score >= current->score)
			 current = current->next;
		else
			break;
	}

	// newNode'u current'tan önce ekle (add() ile aynı)
	newNode->next			= current;
	newNode->prev			= current->prev;
	current->prev->next		= newNode;
	current->prev			= newNode;
}

// 2018-2019 Güz Final 1. Soru
void DoublyLinkedList::insertOrdered(DoublyNode* newNode, DoublyNode* current)
{
	if ((current == trailer) || (newNode->score <= current->score))
	{
		//newNode'u current'tan "önce" ekle
		newNode->next		= current;
		newNode->prev		= current->prev;
		current->prev->next = newNode;
		current->prev		= newNode;
	}
	else
		insertOrdered(newNode, current->next);
}

void DoublyLinkedList::removeOrdered(const string& e, const int& i)
{
	// Liste boş mu?
	if (empty())
	{
		cout << "List is empty !" << endl;
		return;
	}

	DoublyNode* current	= header->next;

	while (current != trailer)
	{
		if ((e.compare(current->elem) == 0) && (current->score == i))
		{
			current->prev->next	= current->next;
			current->next->prev	= current->prev;
			delete current;
			return;
		}

		current	= current->next;
	}

	cout << "\n" << e << " is not found" << endl;
}

DoublyLinkedList* DoublyLinkedList::mergeLists(DoublyLinkedList* list2)
{
	DoublyLinkedList* mergedList = new DoublyLinkedList();

	DoublyNode* plist1 = this->header->next; 
	DoublyNode* plist2 = list2->header->next;

	while ( (plist1 != this->trailer) || (plist2 != list2->trailer) )
	{
		if(plist1 == this->trailer)
		{
			while (plist2 != list2->trailer)
			{
				mergedList->addBack(plist2->elem, plist2->score);
				plist2 = plist2->next;
			}

			return mergedList;
		}

		if(plist2 == list2->trailer)
		{
			while (plist1 != this->trailer)
			{
				mergedList->addBack(plist1->elem, plist1->score);
				plist1 = plist1->next;
			}

			return mergedList;
		}

		if(plist1->score <= plist2->score )
		{
			mergedList->addBack(plist1->elem, plist1->score);
			plist1 = plist1->next;			
		}
		else
		{
			mergedList->addBack(plist2->elem, plist2->score);
			plist2 = plist2->next;
		}	
	}
}

void DoublyLinkedList::printH2T()
{
	if (empty())
	{
		cout << "List is empty !" << endl;
		return;
	}

	DoublyNode* first = header->next;
	while (first != trailer)
	{
		cout << first->elem << "\t" << first->score << endl;
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

	DoublyNode* last = trailer->prev;
	while (last != header)
	{
		cout << last->elem << "\t" << last->score << endl;
		last = last->prev;
	}
}

int main()
{
	DoublyLinkedList list;

	list.addFront("Omer", 1000);
	list.addFront("Oguzhan", 1500);
	list.addFront("Fatih", 1250);
	list.printH2T();

	cout << endl;
	list.removeFront();
	list.printH2T();

	cout << endl;
	list.removeFront();
	list.printH2T();

	cout << endl;
	list.removeFront();
	list.printH2T();


	//DoublyLinkedList list;

	//list.insertOrdered("Paul", 720);
	//list.insertOrdered("Rose", 590);
	//list.insertOrdered("Anna", 660);
	//list.insertOrdered("Mike", 1105);
	//list.insertOrdered("Rob", 750);
	//list.insertOrdered("Jack", 510);
	//list.insertOrdered("Jill", 740);

	//cout << "List after insertions :" << endl;
	//list.printH2T();

	// Recursive insertOrdered() 
	//DoublyLinkedList list;
	//DoublyNode* newNode;

	//newNode = new DoublyNode;
	//newNode->elem = "Paul";
	//newNode->score = 720;
	//list.insertOrdered(newNode, list.header->next);

	//newNode = new DoublyNode;
	//newNode->elem = "Rose";
	//newNode->score = 590;
	//list.insertOrdered(newNode, list.header->next);

	//newNode = new DoublyNode;
	//newNode->elem = "Anna";
	//newNode->score = 660;
	//list.insertOrdered(newNode, list.header->next);

	//newNode = new DoublyNode;
	//newNode->elem = "Mike";
	//newNode->score = 1105;
	//list.insertOrdered(newNode, list.header->next);

	//newNode = new DoublyNode;
	//newNode->elem = "Rob";
	//newNode->score = 750;
	//list.insertOrdered(newNode, list.header->next);

	//newNode = new DoublyNode;
	//newNode->elem = "Jack";
	//newNode->score = 510;
	//list.insertOrdered(newNode, list.header->next);

	//newNode = new DoublyNode;
	//newNode->elem = "Jill";
	//newNode->score = 740;
	//list.insertOrdered(newNode, list.header->next);

	//cout << "List after insertions :" << endl;
	//list.printH2T();
	

	//list.removeOrdered("Adam", 610);	// Bu eleman listede yok !

	//list.removeOrdered("Jack", 510);
	//list.removeOrdered("Mike", 1105);
	//list.removeOrdered("Paul", 720);
	//cout << "\nList after removals (Jack, Mike, Paul) :" << endl;
	//list.printH2T();

	//list.removeOrdered("Rose", 590);
	//list.removeOrdered("Rob",  750);	
	//list.removeOrdered("Anna", 660);
	//list.removeOrdered("Jill", 740);

	//cout << "\nList after removals (Rose, Rob, Anna, Jill ) :" << endl;
	//list.printH2T();


	//DoublyLinkedList* list1 = new DoublyLinkedList();	
	//list1->insertOrdered("Mike", 1105);
	//list1->insertOrdered("Rob",  750);
	//list1->insertOrdered("Paul", 720);
	//list1->insertOrdered("Anna", 660);
	//cout << "list1 : " << endl;
	//list1->printH2T();
	//cout << endl;

	//DoublyLinkedList* list2 = new DoublyLinkedList();
	//list2->insertOrdered("Rose", 590);
	//list2->insertOrdered("Jack", 510);
	//list2->insertOrdered("Jill", 740);
	//list2->insertOrdered("Adam", 610);
	//cout << "list2 : " << endl;
	//list2->printH2T();
	//cout << endl;

	//DoublyLinkedList* mergedList = list1->mergeLists(list2);
	//
	//cout << "Merged list :" << endl;
	//mergedList->printH2T();		 

	::getchar();
}
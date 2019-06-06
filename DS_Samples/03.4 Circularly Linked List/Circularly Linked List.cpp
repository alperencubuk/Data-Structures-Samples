#include <string>
#include <iostream>
using namespace std;

struct CircularlyNode
{
	string elem;								// element name
	int score;									// element score
	CircularlyNode* next;						// next item in the list
};

struct CircularlyLinkedList						// a circularly linked list
{
	CircularlyNode* cursor;						// the cursor

	CircularlyLinkedList();						// constructor
	~CircularlyLinkedList();					// destructor

	bool empty() const;							// is list empty?
	const string& front() const;				// element following cursor
	const string& back() const;					// element at cursor
	void advance();								// advance cursor
	void add(const string& e, const int& i);	// add after cursor
	void remove();								// remove node after cursor
	void print();

	void insertOrdered(const string& e, const int& i) ;
	void removeOrdered(const string& e, const int& i) ;
};

CircularlyLinkedList::CircularlyLinkedList()						// constructor
{
	cursor = NULL;
}

CircularlyLinkedList::~CircularlyLinkedList()						// destructor
{
	while (!empty()) remove();
}

bool CircularlyLinkedList::empty() const							// is list empty?
{
	return cursor == NULL;
}

const string& CircularlyLinkedList::front() const					// element following cursor
{
	return cursor->next->elem;
}

const string& CircularlyLinkedList::back() const					// element at cursor
{
	return cursor->elem;
}

void CircularlyLinkedList::advance()								// advance cursor
{
	cursor = cursor->next;
}

void CircularlyLinkedList::add(const string& e, const int& i)		// add after cursor
{																	
	CircularlyNode* v	= new CircularlyNode;						// create a new node
	v->elem				= e;
	v->score			= i;

	if (cursor == NULL)
	{																// list is empty?
		v->next		= v;											// v points to itself
		cursor		= v;											// cursor points to v
	}
	else
	{																// list is nonempty?
		v->next			= cursor->next;								// link in v after cursor
		cursor->next	= v;
	}
}

void CircularlyLinkedList::remove()									// remove node after cursor
{
	if (empty())
	{
		cout << "List is empty ! " << endl;
		return;
	};
																	
	CircularlyNode* temp = cursor->next;							// the node being removed

	if (temp == cursor) 											// removing the only node?
		cursor = NULL;												// list is now empty
	else
		cursor->next = temp->next;									// link out the old node

	delete temp;													// delete the old node
}

void CircularlyLinkedList::insertOrdered(const string& e, const int& i)
{
	CircularlyNode* newNode = new CircularlyNode;
	newNode->elem			= e;
	newNode->score			= i;

	if (cursor == NULL)
	{
		newNode->next	= newNode;
		cursor			= newNode;
		return;
	}

	CircularlyNode* front	= cursor->next;
	CircularlyNode* back	= cursor;

	while (newNode->score > front->score)
	{
		back = front;
		front = front->next;

		if (back == cursor)
		{
			// liste sonuna ekle
			cursor->next	= newNode;
			newNode->next	= front;
			cursor			= cursor->next;
			return;
		}
	}

	// newNode'u back ve front arasına ekle
	back->next		= newNode;
	newNode->next	= front;
}

void CircularlyLinkedList::removeOrdered(const string& e, const int& i)
{
	if (empty())
	{
		cout << "List is empty ! " << endl;
		return;
	};

	// Listede kalan tek eleman mı siliniyor?
	if (cursor->next == cursor)
	{
		delete cursor;
		cursor = NULL;
		return;
	}

	CircularlyNode* previous = cursor;
	CircularlyNode* current  = cursor->next;	

	while (current != cursor)
	{
		if ((e.compare(current->elem) == 0) && (current->score == i))
		{
			previous->next = current->next;			
			delete current;
			return;
		}

		previous = current;
		current = current->next;
	}

	// Listenin sonundaki eleman mı silinecek ?
	if ((e.compare(current->elem) == 0) && (current->score == i))
	{
		previous->next = current->next;				
		delete current;
		cursor = previous;	// Yeni liste sonu elemanı artık önceki			
	}
	else cout << "\n" << e << " is not found" << endl;
}

void CircularlyLinkedList::print()
{
	if (empty())
	{
		cout << "List is empty ! " << endl;
		return;
	};

	// Cursor son elemana (rear) işaret ettiğinden
	// ilk elemandan itibaren listelemesi için first = cursor->next yapıldı.
	CircularlyNode* first = cursor->next;

	while (!(first == cursor))
	{
		cout << first->elem << "\t" << first->score << endl;
		first = first->next;
	}

	// son elemanı da listele
	cout << first->elem << "\t" << first->score << endl;
}

int main()
{
	CircularlyLinkedList list;

	list.add("Omer", 1000);
	list.add("Oguzhan", 1500);
	list.add("Fatih", 1250);
	list.print();

	cout << endl;
	list.remove();
	list.print();

	cout << endl;
	list.remove();
	list.print();

	cout << endl;
	list.remove();
	list.print();

	//CircularlyLinkedList list;

	//list.insertOrdered("Paul", 720);
	//list.insertOrdered("Rose", 590);
	//list.insertOrdered("Anna", 660);	
	//list.insertOrdered("Mike", 1105);
	//list.insertOrdered("Rob",  750);
	//list.insertOrdered("Jack", 510);
	//list.insertOrdered("Jill", 740);
	//
	//cout << "List after insertions :" << endl;
	//list.print();

	////list.removeOrdered("Adam", 610);	// Bu eleman listede yok !

	//list.removeOrdered("Jack", 510);
	//list.removeOrdered("Mike", 1105);
	//list.removeOrdered("Paul", 720);

	//cout << "\nList after removals (Jack, Mike, Paul) :" << endl;
	//list.print();

	//list.removeOrdered("Rose", 590);
	//list.removeOrdered("Rob",  750);
	//list.removeOrdered("Anna", 660);
	//list.removeOrdered("Jill", 740);

	//cout << "\nList after removals (Rose, Rob, Anna, Jill ) :" << endl;
	//list.print();

	::getchar();
}
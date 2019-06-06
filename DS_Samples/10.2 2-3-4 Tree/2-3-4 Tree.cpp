#include <string>					
#include <iostream>					
using namespace std;

struct DoublyLinkedList;

struct DoublyNode
{						
	int score;												// element score;
	DoublyNode* next;										// pointer to the next item in the list
	DoublyNode* prev;										// pointer to the previous item in the list
	DoublyLinkedList* down;									// pointer to the doubly linked list node of sub level
};

struct DoublyLinkedList
{
	DoublyNode* header;										// pointer to the header of list
	DoublyNode* trailer;									// pointer to the trailer of list
	DoublyNode* up;											// pointer to the upper node that has down pointer
	int n;

	DoublyLinkedList();

	void		insertOrdered(const int& i) ;
	int			hNextScr(int);
	DoublyNode* downPtr(int);
};

DoublyLinkedList::DoublyLinkedList()
{													
	header					= new DoublyNode;
	trailer					= new DoublyNode;
	header->score			= 0;
	trailer->score			= 0;

	DoublyNode* downNode	= new DoublyNode;
	downNode->score			= -1;
	downNode->down			= NULL;

	downNode->prev			= header;
	downNode->next			= trailer;

	header->next			= downNode;						
	trailer->prev			= downNode;

	up = NULL;
	n  = 0;
}

void DoublyLinkedList::insertOrdered(const int& i) 
{	
	DoublyNode* newNode		= new DoublyNode;		
	newNode->score			= i;

	DoublyNode* downNode	= new DoublyNode;
	downNode->score			= -1;
	downNode->down			= NULL;

	DoublyNode* current	= header->next->next;
	while (current != trailer)
	{
		if(newNode->score >= current->score) 
			current = current->next->next;
		else 
			break;		
	}

	// newNode -> downNode -> current 
	newNode->next		= downNode;
	downNode->prev		= newNode;

	current->prev->next	= newNode;
	newNode->prev		= current->prev;

	downNode->next		= current;
	current->prev		= downNode;

	n++;
}

int DoublyLinkedList::hNextScr(int e)
{
	if (e == 1) return header->next->next->score;

	if (e == 2) return header->next->next->next->next->score;

	if (e == 3) return header->next->next->next->next->next->next->score;
}

DoublyNode* DoublyLinkedList::downPtr(int e)
{
	if (e == 1) return header->next;

	if (e == 2) return header->next->next->next;

	if (e == 3) return header->next->next->next->next->next;

	if (e == 4) return header->next->next->next->next->next->next->next;
}


struct Tree_234
{
	DoublyLinkedList* root;									// pointer to the root

	Tree_234();												// constructor
	void insert(int e);
	void remove(DoublyNode* p, int e);						// Eklenecek ...
	void inorder(DoublyLinkedList* v) const;				// inorder traversal of 2-3-4 Tree
};

void Tree_234::insert(int i)			
{ 
	DoublyLinkedList* p;

	if(root == NULL)
	{
		root = new DoublyLinkedList;
		root->insertOrdered(i);
		return;
	}

	p = root;
	DoublyLinkedList* parent = NULL;

	while(true)
	{
		// Eğer düğümde (listede) 3 eleman varsa
		if(p->n == 3)
		{
			DoublyLinkedList* pLeft = new DoublyLinkedList;
			pLeft->insertOrdered(p->hNextScr(1));

			DoublyLinkedList* pRight = new DoublyLinkedList;
			pRight->insertOrdered(p->hNextScr(3));
			
			if (p->downPtr(1)->down != NULL)	// H->[*]
			{
				pLeft->downPtr(1)->down			= p->downPtr(1)->down;
				pLeft->downPtr(1)->down->up		= pLeft->downPtr(1);
			}
			
			if (p->downPtr(2)->down != NULL)	// H->[*]->[ ]->[*]
			{
				pLeft->downPtr(2)->down			= p->downPtr(2)->down;
				pLeft->downPtr(2)->down->up		= pLeft->downPtr(2);
			}
			
			if (p->downPtr(3)->down != NULL)	// H->[*]->[ ]->[*]->[ ]->[*]
			{
				pRight->downPtr(1)->down		= p->downPtr(3)->down;
				pRight->downPtr(1)->down->up	= pRight->downPtr(1);
			}
			
			if (p->downPtr(4)->down != NULL)	// H->[*]->[ ]->[*]->[ ]->[*]->[ ]->[*]->T
			{
				pRight->downPtr(2)->down		= p->downPtr(4)->down;
				pRight->downPtr(2)->down->up	= pRight->downPtr(2);
			}

			// 3 elemanlı olan root ise
			if (p->up == NULL)					
			{
				DoublyLinkedList* pUp = new DoublyLinkedList;
				pUp->insertOrdered(p->hNextScr(2));
				root = pUp;

				pUp->downPtr(1)->down	= pLeft;			// H->[*]
				pLeft->up				= pUp->downPtr(1);

				pUp->downPtr(2)->down	= pRight;			// H->[*]->[ ]->[*]
				pRight->up				= pUp->downPtr(2);

				DoublyLinkedList* temp = p;
				if(i < pUp->hNextScr(1))					// pUp 1 elemanlı listeye pointer
					p = pLeft;
				else
					p = pRight;

				delete temp;
			}
			else
			{
				parent->insertOrdered(p->hNextScr(2));			// 3 elemanlı listeden ortadakini (2.) yukarıdaki listeye ekle

				DoublyNode* pUp = p->up;						// Ortadaki yukarıya çıkınca p-up onun solundaki boş düğüme (down pointerı tutan) işaret eder
				pUp->down				= pLeft;			
				pLeft->up				= pUp;

				pUp->next->next->down	= pRight;				// Yukarı çıkanın sağındaki boş düğüm (down pointerı tutan) insertOrdered()'da (55. satırda) oluştulur
				pRight->up				= pUp->next->next;

				DoublyLinkedList* temp = p;
				if(i < pUp->next->score)						// pUp 1 veya 2 elemanlı listenin düğümüne pointer
					p = pLeft;
				else
					p = pRight;

				delete temp;					
			}
		}
		else
		{
			DoublyNode* temp = p->header->next;

			while((i > temp->next->score) && (temp->next != p->trailer))
				temp = temp->next->next;

			parent = p;

			if(temp->down != NULL) 
				p = temp->down;
			else 
			{
				p->insertOrdered(i);
				return;
			}
		}
	}	
}

// "Serbest Ödev" olarak eklenecek...
void Tree_234::remove(DoublyNode* p, int e)
{
	//
	// 2 - 3 - 4 Ağacından Düğüm Silme Algoritması
	//
	// •	External (çocuksuz) ise direk sil.
	// •	Internal (çocuklu) ise kendisinden büyük en küçük düğümü yerine yaz ve sil.
	// Yukarıdaki 2 durumda da silinecek düğümü ararken (root hariç) tek elemanlı 
	// düğüme rastlarsan “sırasıyla” aşağıdaki kurallardan birini uygulamaya çalış :
	// Rule 1 : Kardeşten ödünç almaya çalış.
	// Rule 2 : Babadan ödünç almaya çalış ve 
	//		    [kardeş, babadan bir eleman, kendin] 3 elemanlı bir düğüm oluştur.
	// Rule 3 : Baba tek elemanlı root ve kardeş de tek elemanlı ise
	//	        [kardeş, root, kendin] 3 elemanlı bir root düğüm oluştur. 
	//		    Bu durumda ağacın seviyesi 1 azalır.
}

// inorder traversal of 2-3-4 tree
void Tree_234::inorder(DoublyLinkedList* v) const
{
	if (v->header->next->down != NULL)									inorder(v->header->next->down);

	cout << v->header->next->next->score << " ";

	if (v->header->next->next->next->down != NULL)						inorder(v->header->next->next->next->down);

	if (v->n > 1) cout << v->header->next->next->next->next->score << " ";

	if (v->n > 2) {
		if (v->header->next->next->next->next->next->down != NULL)		inorder(v->header->next->next->next->next->next->down);
	}

	if (v->n > 2) cout << v->header->next->next->next->next->next->next->score << " ";
}

Tree_234::Tree_234()
{ 
	root = NULL;
}

void main()
{
	Tree_234 tree_234;

	tree_234.insert(16);
	tree_234.insert(8);
	tree_234.insert(24);
	tree_234.insert(4);
	tree_234.insert(12);
	tree_234.insert(20);
	tree_234.insert(28);
	tree_234.insert(2);
	tree_234.insert(6);
	tree_234.insert(10);
	tree_234.insert(14);
	tree_234.insert(18);
	tree_234.insert(22);
	tree_234.insert(26);
	tree_234.insert(30);
	tree_234.insert(1);
	tree_234.insert(3);
	tree_234.insert(5);
	tree_234.insert(7);
	tree_234.insert(9);
	tree_234.insert(11);
	tree_234.insert(13);
	tree_234.insert(15);
	tree_234.insert(17);
	tree_234.insert(19);
	tree_234.insert(21);
	tree_234.insert(23);
	tree_234.insert(25);
	tree_234.insert(27);
	tree_234.insert(29);
	tree_234.insert(31);

	cout<< "2-3-4 Tree Inorder Traversal :" << endl;
	tree_234.inorder(tree_234.root);

	::getchar();
}
#include <iostream>												
using namespace std;											

struct TreeNode										// a node of the tree
{									
	int     elem;									// element value
	TreeNode*   parent;								// Parent
	TreeNode*   left;								// left child
	TreeNode*   right;								// right child

	TreeNode()										// constructor
	{
		elem	= 0;
		parent	= NULL;
		left	= NULL;
		right	= NULL;
	}
};

struct SplayTree
{
	TreeNode* root;									// pointer to the root
	int n;											// number of nodes

	SplayTree();									// constructor
	int size() const;								// number of nodes
	bool empty() const;								// is tree empty?

	void addNode(TreeNode* p, int);
	void deleteNode(TreeNode* p, int);

	void preorder(TreeNode* v) const;				// preorder traversal
	void inorder(TreeNode* v) const;				// inorder traversal
	void postorder(TreeNode* v) const;				// postorder traversal
	void eulerTour(TreeNode* v) const;				// Euler tour traversal		
};

void SplayTree::addNode(TreeNode* p, int e)					
{
	TreeNode* newNode = new TreeNode;
	newNode->elem = e;

	if (empty())
	{
		root = newNode;
		n = 1;
	}
	else
	{
		while (true)
		{
			if (e < p->elem)
			{
				if (p->left == NULL)
				{
					p->left = newNode;
					newNode->parent = p;
					n++;
					break;
				}
				else p = p->left;
			}
			else
			{
				if (p->right == NULL)
				{
					p->right = newNode;
					newNode->parent = p;
					n++;
					break;
				}
				else p = p->right;
			}
		}
	}

	// NOW SPLAYING ...

	TreeNode* Parent = newNode->parent;		// TreeNode* Parent = p->parent;
	TreeNode* GParent = NULL;
	if(Parent != NULL) GParent = Parent->parent;

	while (newNode->parent != NULL)			// newNode root olana dek...
	{
		// ZIG
		if (newNode->parent == root)
		{	
			if (newNode->elem < root->elem)
			{
				if (newNode->right != NULL)
				{
					root->left				= newNode->right;
					newNode->right->parent	= root;
				}
				else root->left = NULL;

				newNode->right		= root;
				root->parent		= newNode;
			}
			else
			{
				if (newNode->left != NULL)
				{
					root->right				= newNode->left;
					newNode->left->parent	= root;
				}
				else root->right = NULL;

				newNode->left		= root;
				root->parent		= newNode;
			}

			root			= newNode;
			newNode->parent	= NULL;
		}

		// ZIG-ZAG (left-right)
		else if((newNode == Parent->right) && (Parent == GParent->left))
		{
			// I. AŞAMA (newNode <-> Parent)					 
			if (newNode->left != NULL)
			{
				Parent->right			= newNode->left;
				newNode->left->parent	= Parent;
			}
			else Parent->right = NULL;

			newNode->left	= Parent; 
			Parent->parent	= newNode;

			GParent->left	= newNode;
			newNode->parent	= GParent;

			// II. AŞAMA (newNode <-> GParent)
			if (newNode->right != NULL)
			{
				GParent->left			= newNode->right;
				newNode->right->parent	= GParent;
			}
			else GParent->left = NULL;

			newNode->parent = GParent->parent;

			newNode->right	= GParent;
			GParent->parent	= newNode;
		}

		// ZIG-ZAG (right-left)
		else if((newNode == Parent->left) && (Parent == GParent->right))
		{
			// I. AŞAMA (newNode <-> Parent)					 
			if (newNode->right != NULL)
			{
				Parent->left			= newNode->right;
				newNode->right->parent	= Parent;
			}
			else Parent->left = NULL;

			newNode->right	= Parent;
			Parent->parent	= newNode;

			GParent->right	= newNode;
			newNode->parent	= GParent;

			// II. AŞAMA (newNode <-> GParent)
			if (newNode->left != NULL)
			{
				GParent->right			= newNode->left;
				newNode->left->parent	= GParent;
			}
			else GParent->right = NULL;

			newNode->parent = GParent->parent;

			newNode->left	= GParent;
			GParent->parent = newNode;
		}

		// ZIG-ZIG (left-left)
		else if((newNode == Parent->left) && (Parent == GParent->left))
		{
			// I. AŞAMA (Parent <-> GParent)	
			if (Parent->right != NULL)
			{
				GParent->left			= Parent->right;
				Parent->right->parent	= GParent;
			}
			else GParent->left = NULL;

			newNode->parent = GParent->parent;

			Parent->right	= GParent;
			GParent->parent	= Parent;

			// II. AŞAMA (newNode <-> Parent)
			if (newNode->right != NULL)
			{
				Parent->left			= newNode->right;
				newNode->right->parent	= Parent;
			}
			else Parent->left = NULL;

			newNode->right	= Parent; 
			Parent->parent	= newNode;
		}

		// ZIG-ZIG (right-right)
		else if((newNode == Parent->right) && (Parent == GParent->right))
		{
			// I. AŞAMA (Parent <-> GParent)	
			if (Parent->left != NULL)
			{
				GParent->right			= Parent->left;
				Parent->left->parent	= GParent;
			}
			else GParent->right = NULL;

			newNode->parent = GParent->parent;

			Parent->left	= GParent;
			GParent->parent = Parent;

			// II. AŞAMA (newNode <-> Parent)
			if (newNode->left != NULL)
			{
				Parent->right			= newNode->left;
				newNode->left->parent	= Parent;
			}
			else Parent->right = NULL;

			newNode->left	= Parent;
			Parent->parent	= newNode;
		}

		if (newNode->parent == NULL)
			root = newNode;
		else
		{
			if (newNode->elem < newNode->parent->elem)		// newNode GParent seviyesine çıktı.
				newNode->parent->left = newNode;			// newNode GParent->parent'ın nesi? 
			else											// Yukarıda da setlenebilirdi yalnız 
				newNode->parent->right = newNode;			// aynı kodun birkaç kopyası gerekecekti.

			Parent  = newNode->parent;
			GParent = Parent->parent;
		}	
	}
}

void SplayTree::deleteNode(TreeNode* p, int e)			// Binary Tree ile aynı
{
	TreeNode* temp;

	while (p != NULL)
	{
		if (p->elem == e)	break;
		else
		{
			if (e < p->elem)
				p = p->left;
			else
				p = p->right;
		}
	}

	if (p == NULL)
	{
		cout << "The node does not exists" << endl;
		getchar();
		return;
	}
	else
	{
		// Kendisinden büyük en küçük düğümü kendi yerine koy (diğer yaklaşım da olabilirdi)
		if (p->right != NULL)
		{
			temp = p->right;

			if (temp->left != NULL)
			{
				while (temp->left != NULL) temp = temp->left;
				p->elem = temp->elem;

				if (temp->right != NULL)
				{
					temp->parent->left	= temp->right;
					temp->right->parent = temp->parent;
				}
				else
				{
					temp->parent->left = NULL;
				}
			}
			else
			{
				p->elem = temp->elem;

				if (temp->right != NULL)
				{
					temp->parent->right = temp->right;
					temp->right->parent = temp->parent;
				}
				else
				{
					temp->parent->right = NULL;
				}
			}

			delete temp;
			return;
		}
		// Kendisinden büyük düğüm yoksa sol çocuğu kendi yerine koy
		else if (p->left != NULL)
		{
			if (p->parent != NULL)
			{
				if (p == p->parent->left)
				{
					p->parent->left = p->left;
					p->left->parent = p->parent;
				}
				else
				{
					p->parent->right = p->left;
					p->left->parent = p->parent;

				}
			}
			else
			{
				p->left->parent = NULL;
				root = p->left;
			}

			delete p;
			return;
		}
		//if (p->left == NULL && p->right == NULL) yani çocuğu yoksa direk sil :
		else
		{
			if (p->parent != NULL)
			{
				if (p->parent->left == p)
					p->parent->left = NULL;
				else
					p->parent->right = NULL;

				delete p;
			}
			else
			{
				root = NULL;
				delete root;  // p
			}
		}
	}
}

SplayTree::SplayTree()					// constructor
{ 
	root = NULL;
	n = 0;
}

int SplayTree::size() const				// number of nodes
{ 
	return n; 
}

bool SplayTree::empty() const				// is tree empty?
{ 
	return size() == 0; 
}

// preorder traversal
void SplayTree::preorder(TreeNode* v) const 
{	
	cout << v->elem << " ";

	if (v->left != NULL)		preorder(v->left);	

	if (v->right != NULL)		preorder(v->right);	
}

// inorder traversal
void SplayTree::inorder(TreeNode* v) const 
{
	if (v->left != NULL)		inorder(v->left);	

	cout << v->elem << " ";

	if (v->right != NULL)		inorder(v->right);	

}

// postorder traversal
void SplayTree::postorder(TreeNode* v) const 
{
	if (v->left != NULL)		postorder(v->left);	

	if (v->right != NULL)		postorder(v->right);
	
	cout << v->elem << " ";	
}

// Euler tour traversal
void SplayTree::eulerTour(TreeNode* v) const
{
	cout << v->elem << " ";

	if (v->left != NULL)
	{
		eulerTour(v->left);
		cout << v->elem << " ";
	}

	if (v->right != NULL)
	{
		eulerTour(v->right);
		cout << v->elem << " ";
	}
}

void main()
{
	SplayTree splayTree;

	splayTree.addNode(splayTree.root, 12);
	splayTree.addNode(splayTree.root, 2);
	splayTree.addNode(splayTree.root, 10);
	splayTree.addNode(splayTree.root, 6);
	splayTree.addNode(splayTree.root, 4);
	splayTree.addNode(splayTree.root, 8);
	splayTree.addNode(splayTree.root, 5);
	splayTree.addNode(splayTree.root, 9);
	splayTree.addNode(splayTree.root, 1);
	splayTree.addNode(splayTree.root, 13);
	splayTree.addNode(splayTree.root, 7);		// 12.01.2012 Final Sorusu

	//splayTree.addNode(splayTree.root, 11);		// 02.01.2015 Final Sorusu (A Grubu)
	//splayTree.addNode(splayTree.root, 3);		// 02.01.2015 Final Sorusu (B Grubu)
	
	cout<< "Splay Tree Inorder Traversal : " ;
	splayTree.inorder(splayTree.root);

	getchar();
}
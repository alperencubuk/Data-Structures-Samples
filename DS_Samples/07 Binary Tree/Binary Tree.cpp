#include <iostream>
using namespace std;

struct TreeNode										// a node of the tree
{
	int			elem;								// element value
	TreeNode*   parent;								// parent
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

struct BinaryTree
{
	TreeNode* root;									// pointer to the root
	int n;											// number of nodes

	BinaryTree();									// constructor
	int size() const;								// number of nodes
	bool empty() const;								// is tree empty?

	void addNode(TreeNode* p, int);
	void deleteNode(TreeNode* p, int);

	void preorder(TreeNode* v) const;				// preorder traversal
	void inorder(TreeNode* v) const;				// inorder traversal
	void postorder(TreeNode* v) const;				// postorder traversal
	void eulerTour(TreeNode* v) const;				// Euler tour traversal		
};

void BinaryTree::addNode(TreeNode* p, int e)					
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
					return;
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
					return;
				}
				else p = p->right;
			}
		}
	}
}

void BinaryTree::deleteNode(TreeNode* p, int e)
{
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
		cout << "The TreeNode does not exists" << endl;
		getchar();
		return;
	}
	else
	{
		TreeNode* temp;

		// Kendisinden büyük en küçük düğümü kendi yerine koy
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
					p->left->parent	 = p->parent;

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


		// Kendisinden küçük en büyük düğümü kendi yerine koy
		//if (p->left != NULL)
		//{
		//	temp = p->left;

		//	if (temp->right != NULL)
		//	{
		//		while (temp->right != NULL) temp = temp->right;
		//		p->elem = temp->elem;

		//		if (temp->left != NULL)
		//		{
		//			temp->parent->right = temp->left;
		//			temp->left->parent = temp->parent;
		//		}
		//		else
		//		{
		//			temp->parent->right = NULL;
		//		}
		//	}
		//	else
		//	{
		//		p->elem = temp->elem;

		//		if (temp->left != NULL)
		//		{
		//			temp->parent->left = temp->left;
		//			temp->left->parent = temp->parent;
		//		}
		//		else
		//		{
		//			temp->parent->left = NULL;
		//		}
		//	}

		//	delete temp;
		//	return;
		//}
		//// Kendisinden küçük düğüm yoksa sağ çocuğu kendi yerine koy
		//else if (p->right != NULL)
		//{
		//	if (p->parent != NULL)
		//	{
		//		if (p == p->parent->left)
		//		{
		//			p->parent->left = p->right;
		//			p->right->parent = p->parent;
		//		}
		//		else
		//		{
		//			p->parent->right = p->right;
		//			p->right->parent = p->parent;

		//		}
		//	}
		//	else
		//	{
		//		p->right->parent = NULL;
		//		root = p->right;
		//	}

		//	delete p;
		//	return;
		//}
		////if (p->left == NULL && p->right == NULL) yani çocuğu yoksa direk sil :
		//else
		//{
		//	if (p->parent != NULL)
		//	{
		//		if (p->parent->left == p)
		//			p->parent->left = NULL;
		//		else
		//			p->parent->right = NULL;

		//		delete p;
		//	}
		//	else
		//	{
		//		root = NULL;
		//		delete root;  // p
		//	}
		//}
	}
}

BinaryTree::BinaryTree()						// constructor
{
	root = NULL;
	n	 = 0;
}

int BinaryTree::size() const					// number of nodes
{
	return n;
}

bool BinaryTree::empty() const					// is tree empty?
{
	return size() == 0;
}

// inorder traversal
void BinaryTree::inorder(TreeNode* v) const
{
	if (v->left != NULL)	inorder(v->left);

	cout << v->elem << " ";

	if (v->right != NULL)	inorder(v->right);
}

// preorder traversal
void BinaryTree::preorder(TreeNode* v) const
{
	cout << v->elem << " ";

	if (v->left != NULL)	preorder(v->left);

	if (v->right != NULL)	preorder(v->right);
}

// postorder traversal
void BinaryTree::postorder(TreeNode* v) const
{
	if (v->left != NULL)	postorder(v->left);

	if (v->right != NULL)	postorder(v->right);

	cout << v->elem << " ";
}

// Euler tour traversal
void BinaryTree::eulerTour(TreeNode* v) const
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

int main()
{
	BinaryTree binaryTree;

	binaryTree.addNode(binaryTree.root, 8);
	binaryTree.addNode(binaryTree.root, 4);
	binaryTree.addNode(binaryTree.root, 12);
	binaryTree.addNode(binaryTree.root, 2);
	binaryTree.addNode(binaryTree.root, 6);
	binaryTree.addNode(binaryTree.root, 10);
	binaryTree.addNode(binaryTree.root, 14);
	binaryTree.addNode(binaryTree.root, 1);
	binaryTree.addNode(binaryTree.root, 3);
	binaryTree.addNode(binaryTree.root, 5);
	binaryTree.addNode(binaryTree.root, 7);
	binaryTree.addNode(binaryTree.root, 9);
	binaryTree.addNode(binaryTree.root, 11);
	binaryTree.addNode(binaryTree.root, 13);
	binaryTree.addNode(binaryTree.root, 15);

	cout << "Binary Tree Inorder Traversal : " ;
	binaryTree.inorder(binaryTree.root);

	//binaryTree.addNode(binaryTree.root, 16);
	//binaryTree.addNode(binaryTree.root, 8);
	//binaryTree.addNode(binaryTree.root, 24);
	//binaryTree.addNode(binaryTree.root, 4);
	//binaryTree.addNode(binaryTree.root, 12);
	//binaryTree.addNode(binaryTree.root, 20);
	//binaryTree.addNode(binaryTree.root, 28);
	//binaryTree.addNode(binaryTree.root, 2);
	//binaryTree.addNode(binaryTree.root, 6);
	//binaryTree.addNode(binaryTree.root, 10);
	//binaryTree.addNode(binaryTree.root, 14);
	//binaryTree.addNode(binaryTree.root, 18);
	//binaryTree.addNode(binaryTree.root, 22);
	//binaryTree.addNode(binaryTree.root, 26);
	//binaryTree.addNode(binaryTree.root, 30);
	//binaryTree.addNode(binaryTree.root, 1);
	//binaryTree.addNode(binaryTree.root, 3);
	//binaryTree.addNode(binaryTree.root, 5);
	//binaryTree.addNode(binaryTree.root, 7);
	//binaryTree.addNode(binaryTree.root, 9);
	//binaryTree.addNode(binaryTree.root, 11);
	//binaryTree.addNode(binaryTree.root, 13);
	//binaryTree.addNode(binaryTree.root, 15);
	//binaryTree.addNode(binaryTree.root, 17);
	//binaryTree.addNode(binaryTree.root, 19);
	//binaryTree.addNode(binaryTree.root, 21);
	//binaryTree.addNode(binaryTree.root, 23);
	//binaryTree.addNode(binaryTree.root, 25);
	//binaryTree.addNode(binaryTree.root, 27);
	//binaryTree.addNode(binaryTree.root, 29);
	//binaryTree.addNode(binaryTree.root, 31);

	//cout << "Binary Tree Inorder Traversal :" << endl;
	//binaryTree.inorder(binaryTree.root);

	//// Kendisinden büyük en küçük düğümü kendi yerine koy
	//binaryTree.deleteNode(binaryTree.root, 25);

	//binaryTree.deleteNode(binaryTree.root, 24);

	//binaryTree.deleteNode(binaryTree.root, 27);
	//binaryTree.deleteNode(binaryTree.root, 26);

	//binaryTree.deleteNode(binaryTree.root, 29);
	//binaryTree.deleteNode(binaryTree.root, 30);
	//binaryTree.deleteNode(binaryTree.root, 31);
	//binaryTree.deleteNode(binaryTree.root, 28);
	//////////////////////////////////////////////////////


	//// Kendisinden küçük en büyük düğümü kendi yerine koy
	////binaryTree.deleteNode(binaryTree.root, 7);

	////binaryTree.deleteNode(binaryTree.root, 8);

	////binaryTree.deleteNode(binaryTree.root, 5);
	////binaryTree.deleteNode(binaryTree.root, 4);

	////binaryTree.deleteNode(binaryTree.root, 1);
	////binaryTree.deleteNode(binaryTree.root, 2);
	////binaryTree.deleteNode(binaryTree.root, 3);
	////binaryTree.deleteNode(binaryTree.root, 6);
	//////////////////////////////////////////////////////

	//cout << endl << endl << "Binary Tree Inorder Traversal After Deletions :" << endl;
	//binaryTree.inorder(binaryTree.root);

	getchar();
}
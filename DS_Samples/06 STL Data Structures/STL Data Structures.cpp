#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <queue>
using namespace std; // make std:: accessible

struct Node
{
	string elem;											// element name
	int score;												// element score;
};

void printList(list<Node> stl_list)
{
	typedef list<Node>::iterator Iterator; // iterator type

	for (Iterator p = stl_list.begin(); p != stl_list.end(); ++p)
		cout << p->elem << "  " << p->score << endl;
}

void printVector(vector<int> stl_vector)
{
	typedef vector<int>::iterator Iterator; // iterator type

	for (Iterator p = stl_vector.begin(); p != stl_vector.end(); ++p) cout << *p << "  ";

	//for (int i = 0; i<stl_vector.size(); i++) cout << stl_vector.at(i) << " ";
}

void printQueue(queue<int> stl_queue)
{
	int size = stl_queue.size();
	for (int i = 0; i < size; i++)
	{
		cout << stl_queue.front() << "  ";
		stl_queue.pop();
	}
}

bool compare(Node a, Node b)
{
	if (a.score < b.score) return true;
	else return false;
}

int vectorSum1(const vector<int>& V)
{
	int sum = 0;
	for (int i = 0; i < V.size(); i++)
		sum += V[i];
	return sum;
}

int vectorSum2(vector<int> V)
{
	typedef vector<int>::iterator Iterator; // iterator type
	int sum = 0;
	for (Iterator p = V.begin(); p != V.end(); ++p)
		sum += *p;
	return sum;
}

void main()
{
	//
	// STL List Samples
	//

	Node node;
	list<Node> stl_list;

	node.elem = "Paul";  node.score = 720;
	stl_list.push_back(node);

	node.elem = "Rose";  node.score = 590;
	stl_list.push_back(node);

	node.elem = "Anna";  node.score = 660;
	stl_list.push_back(node);

	node.elem = "Mike"; node.score = 1105;
	stl_list.push_back(node);

	node.elem = "Rob";   node.score = 750;
	stl_list.push_back(node);

	node.elem = "Jack";  node.score = 510;
	stl_list.push_back(node);

	node.elem = "Jill";  node.score = 740;
	stl_list.push_back(node);

	cout << "list elements : " << endl;
	printList(stl_list);

	cout << endl;

	stl_list.sort(compare);
	cout << "sorted list : " << endl;
	printList(stl_list);

	//cout << endl;

	//stl_list.pop_front();
	//stl_list.pop_back();
	//printList(stl_list);

	//cout << endl;

	//list<Node>::iterator i;
	//i = stl_list.begin();
	//advance(i,3);
	//stl_list.erase(i);
	//printList(stl_list);

	//
	// STL Vector Samples
	//

	//int a[] = { 17, 12, 33, 15, 62, 45 };
	//vector<int> v(a, a + 6);						// v: 17 12 33 15 62 45
	//
	//cout << "vector elements : ";
	//printVector(v);

	//cout << endl;
	//cout << "vector size : " << v.size() << endl;						// outputs: 6

	//v.pop_back();									// v: 17 12 33 15 62
	//cout << "vector elements after pop_back() : ";
	//printVector(v);

	//cout << endl;

	//v.push_back(19);								// v: 17 12 33 15 62 19
	//cout << "vector elements after push_back(19) : ";
	//printVector(v);

	//cout << endl;
	//cout << "front element : " << v.front() << " back element : " << v.back() << endl;	// outputs: 17 19

	//v.erase(v.end() - 4, v.end() - 2);				// v: 17 12 62 19
	//cout << "vector elements after erasure : ";
	//printVector(v);

	//cout << endl;

	//cout << "vectorSum1 = " << vectorSum1(v) << endl;
	//cout << "vectorSum2 = " << vectorSum2(v) << endl;


	//
	// STL Stack Samples
	//

	//stack<int> stl_stack;
	//stl_stack.push(1);
	//stl_stack.push(2);
	//stl_stack.push(3);
	//stl_stack.push(4);
	//stl_stack.push(5);

	//cout << stl_stack.top() << endl;

	//stl_stack.pop();

	//cout << stl_stack.top() << endl;


	//
	// STL Queue Samples
	//

	//queue<int> stl_queue;

	//stl_queue.push(1);
	//stl_queue.push(2);
	//stl_queue.push(3);
	//stl_queue.push(4);
	//stl_queue.push(5);

	//cout << "queue elements : ";
	//printQueue(stl_queue);

	//cout << endl;

	//cout << "front = " << stl_queue.front() << " back = " << stl_queue.back() << endl;

	//stl_queue.pop();
	//cout << "front after pop() = " << stl_queue.front() << endl;

	//stl_queue.push(6);
	//cout << "back after push(6) = " << stl_queue.back() << endl;

	getchar();
}
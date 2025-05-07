#include "BSTInterface.h"
#include <string>

using namespace std;

template <typename KeyComparable, typename Value >
class BinarySearchTree : BSTInterface < KeyComparable, Value >  {
  private:	

	// Private BinaryNode Class 

	class BinaryNode {
		public:
			KeyComparable key;
			Value value;

			BinaryNode *left;
			BinaryNode *right;
			BinaryNode( KeyComparable & key, Value & value, BinaryNode *left = nullptr, BinaryNode *right = nullptr)
				: value{ value }, left{ left }, right{ right } , key{ key } {}

	};	// end of BinaryNode class

	// the root node of the tree, starts null becomes BinaryNode pointer
	BinaryNode *root = nullptr;



	bool insert(Value item, KeyComparable key, BinaryNode * node) {
		// already checked for empty tree
		// now walk down tree from root

		bool success = false; // flag, if insert fails return false

		if (key > node->key) {//key larger
			//go right
			if (node->right == nullptr) {
				// reached leaf
				node->right = new BinaryNode(key, item);// make new node
				success = true; //flag becomes true

			} else {
			// not leaf, go right make recursive call
				success = this->insert(item, key, node->right);
			}

		} else if (key < node->key) {
			//key smaller go left
			if (node->left == nullptr) {
				// Reached a leaf 
				node->left = new BinaryNode(key, item);//make a new node
				success = true;//flag becomes true
				
				
			} else {
				// Go left
				success = this->insert(item, key, node->left);

			}

		}
		else {
			// do not accept 
			success = false;
		}
		
		return success;		
	}


	// Private
	// uses private find to get node
	bool contains(const KeyComparable& key, BinaryNode*& foundNode) const {
		
		bool success = false;

	
		// Returns a pointer to the node ins qestion to 'find' variable
		foundNode =  this->find(key, this->root);

		if (foundNode->value->getID() == key) {
			success = true;
		}

		return success;
	}



	// Private
	void remove(const KeyComparable& key, BinaryNode*& t) {
		// *& Using a ref so we can modify the ptr
		//if i remove a node I must 
		// I must take its left inner most child ight child to replace it 
		if (key != this->root->key) {

			cout << "this node " << t->key << " comparing " << key << endl;
			if (key > t->key)
			{
				if (t->right->key == key && t->right->right == nullptr) {
					cout << "t-right-right isnull and t right is key" << endl;
					BinaryNode* oldNode = t->right;
					t = t->right->left;
					delete oldNode;
					return;
				}
				else if (t->right->key == key && t->right->left == nullptr) {

					cout << "t-right-left isnull and t right is key" << endl;
					BinaryNode* oldNode = t->right;
					t = t->right->right;
					delete oldNode;
					return;
				}
				cout << "going right " << endl;
				cout << "next level right " << t->left->key << endl;
				remove(key, t->right);
			}
			else if (key < t->key)
			{
				if (t->left->key == key && t->left->right == nullptr) {
					cout << "t-left-right isnull and t left is key" << endl;

					BinaryNode* oldNode = t->left;
					t = t->right->left;
					delete oldNode;
					return;
				}
				else if (t->left->key == key && t->left->left == nullptr) {

					cout << "t-left-leftg isnull and t left is key" << endl;
					BinaryNode* oldNode = t->left;
					t = t->right->right;
					delete oldNode;
					return;
				}
				cout << "going left" << endl;
				cout << "this node" << t->key << " is smaller than " << key << endl;
				cout << "next level left " << t->key << t->left->key << endl;
				cout << "key comparison" << t->left->key << endl;
				remove(key, t->left);
			}// cases where node to be removed has both children
			else if (t->right->key == key) {//t->right is target
			// get in order successor
				//get left branch largest value
				BinaryNode* nextLargest = t->right->left;
				while (nextLargest != nullptr && nextLargest->right != nullptr)
				{
					nextLargest = nextLargest->right;
				}
				//copy over contents
				t->right->key = nextLargest->key;
				t->right->value = nextLargest->value;
				//recursive starting at new copied node, removing the one we just copied over
				remove(nextLargest->key, t->right);

			}
			else if (t->left->key == key) {//t->left is target
				// get in order successor
				//get left branch largest value
				BinaryNode* nextLargest = t->left->left;
				while (nextLargest != nullptr && nextLargest->right != nullptr)
				{
					nextLargest = nextLargest->right;
				}
				t->right->key = nextLargest->key;
				t->right->value = nextLargest->value;
				//recursive starting at new copied node, removing the one we just copied over
				remove(nextLargest->key, t->right);

			}
		}
		else {

			// head key equal to key value
			if (t->right == nullptr)
			{
				BinaryNode* oldNode = t;
				t = t->left;
				delete oldNode;
			}
			else if (t->right == nullptr)
			{
				BinaryNode* oldNode = t;
				t = t->right;
				delete oldNode;
			}
			else
			{
				// get in order successor
				//get left branch largest value
				BinaryNode* nextLargest = t->left;
				while (nextLargest != nullptr && nextLargest->right != nullptr)
				{
					nextLargest = nextLargest->right;
				}
				t->key = nextLargest->key;
				t->value = nextLargest->value;
				//recursive starting at new copied node, removing the one we just copied over
				remove(nextLargest->key, t);

			}
		}

	}
	

	
	//Private
	// Finds the node with the smallest element in the subtree
	BinaryNode* findMin(BinaryNode *t) const {

		BinaryNode* minNode = nullptr;

		if (t) {

			minNode = t;
			
			while(minNode->left) 
			{
			
				minNode = minNode->left;

			}

		}

		return minNode;
	}

	// Private 
	// Finds the node with the largest element in the subtree
	BinaryNode * findMax(BinaryNode *t) const {
		BinaryNode* maxNode = nullptr;

		if (t) {
			maxNode = t;

			while (maxNode->right) {
				maxNode = maxNode->right;
			}

		}

		return maxNode;
	}

	// Private
	// Finds the node with that satisfies equality for the element
	BinaryNode*  find(const KeyComparable & key, BinaryNode *node) const 
	{
		//*node starts at root
		
		// Base Case
		BinaryNode* check = node;
		if(key == check->key)
		{
			return check;

		} // Recursive Cases
		else if (key <check->key){

			//go left
			check = find(key, check->left);

		}
		else
		{
			// go right
			check = find(key, check->right);
		}
		// returns a pointer to the BinaryNode in qustion.  
		return check;


	}

	// Private
	

	void makeEmpty(BinaryNode * & t) {
		// optional code
	}

	void printTree(BinaryNode* t, std::ostream& out) const{

		if (t->left == nullptr) {
			//print leaf done
			out << *(t->value) << endl; 
		}
		else 
		{
			//left not null keep going left
			printTree(t->left, out);
			out << *(t->value) << endl;
		}

		if (t->right)
		{
			//go right do it again
			printTree(t->right, out);		
		}
			
	}
	
  public:

	BinarySearchTree() {
		// optional code
	}
	
	~BinarySearchTree() {
		// optional code
	}
	/*
	* Finds the node with the smallest element in the tree
	*/
	// the public finmin must return an object priv findmin returns node

	const Value findMin() const {

		// Must return a Value object or in this case a ComputerScientist
		BinaryNode* minNode = this->findMin(this->root);//private takes arg root pointer

		return minNode->value;

	}

	const Value findMax() const {
		// TODO calls private findMax part 2
		BinaryNode* maxNode = findMax(this->root);

		return  maxNode->value;
	}

	// Key is literally just a number
	bool contains(const KeyComparable& key) const {

		bool success = false;
		// public version returns bool
		BinaryNode* foundNode = nullptr;
		//updates the foundNode pointer if found	
		if (contains(key, foundNode)) {

			success = true;	
			
		}

		return success;
			
	}


	bool find(const KeyComparable & key , Value & founditem) const {

		
		bool success = false;

		// Calls private find and returns
		// Returns a pointer to the node ins qestion to 'find' variable

		BinaryNode* find =  this->find(key, this->root);
		if (find->value->getID() == key) {
			success = true;
			founditem = find->value;//returning a Value type (not node)
		}

		return success;
	}

	// Returns true if the item is found in the tree
	
	

	/*
	* Returns true if tree has no nodes
	*/
	bool isEmpty() const{
		// return condition of comparison ==
		return root == nullptr;
	}

	/*
	* Prints all the data from the tree in order based on key
	*/
	void printTree(std::ostream & out = std::cout) const {
		// TODO Calls the private printTree function
		this->printTree(this->root, out);// Different Param list for priv func
	}

	/*
	* Removes all nodes from the tree	
	*/
	void makeEmpty() {
		// optional code 
	}

	bool insert( Value value,  KeyComparable key) 
	{
		if (this->isEmpty())
		{
			this->root = new BinaryNode(key, value);//this is a pointer
			return true;
		}
		else 
		{
			return insert(value, key, this->root);
		}
	}

	//	 Removes the nodes if it contains the given item
	void remove(const KeyComparable& key) {
		
		
		//check if it is in tree
		//calls private function and updates Val with valid object
		if (contains(key))
		{
			// turns value to a ptr val to a ptr to  ptr val (don't overthink it)
			// void remove(const KeyComparable & key, BinaryNode ** t) {
			remove(key, this->root);
			//void remove(const KeyComparable & key, BinaryNode ** t) {
		}
		else 
		{
			cout << "Can't find " << key << endl;
		}

	}

};  // end of BinarySearchTree class
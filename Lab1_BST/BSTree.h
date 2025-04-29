#include "BSTInterface.h"
#include <string>

using namespace std;

template <typename KeyComparable, typename Value >
class BinarySearchTree : BSTInterface < KeyComparable, Value >  {
  private:	

	/*
	* Private BinaryNode Class 
	*/
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

	/*
	* Inserts a node into the tree
	* returns true if item inserted
	* returns false if item not inserted (Key already in tree)
	* maintains this property of th tree:
	*     All nodes to the left will be less
	*     All nodes to the right will be greater	
	*/
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
				this->insert(item, key, node->right);
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

	/*
	* remove a node from the tree
	* maintains this property of th tree:
	*     All nodes to the left will be less
	*     All nodes to the right will be greater
	*/
	void remove(const KeyComparable & key, BinaryNode ** t) {
		//TODO write for part 2
	}

	/*
	* Finds the node with the smallest element in the subtree
	*/
	//private
	BinaryNode * findMin(BinaryNode *t) const {

		BinaryNode* minNode = nullptr;
		BinaryNode* next = nullptr;

		if (t && t->left) {

			minNode = t->left;
			
			while(minNode->left) 
			{
			
				minNode = minNode->left;

			}

		}

		return minNode;

	}

/*
	* Finds the node with the largest element in the subtree
	*/
	BinaryNode * findMax(BinaryNode *t) const {
		//TODO write for part 2
	}

	/*
	* Finds the node with that satisfies equality for the element
	*/
	BinaryNode *  find(const KeyComparable & key, BinaryNode *node) const {
		//TODO write for part 1
		return nullptr;		
	}

	/*
	* Returns true if the item is found in the tree
	*/
	bool contains(const Value & item, BinaryNode *t) const {
		// optional code
	}

	/*
	* Removes all elelements from the tree
	*/
	void makeEmpty(BinaryNode * & t) {
		// optional code
	}

	/*
	* Prints all the data from the tree in order based on key
	*/
	void printTree(BinaryNode* t, std::ostream& out) const{
		// How the hell do I do this again?
		// Goes left until it cant
		// Calls FindMin()
		this->findMin();
		// 2 print then goes up
		// 3 prints
		// 4 go right 
		// 5 prints
		// Start agan at one
		

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
		// must return a Value object or in this case a ComputerScientist
		BinaryNode* minNode = this->findMin(this->root);//private takes arg root pointer
		return minNode->value;
	}

	/*
	* Finds the node with the largest element in the tree
	*/
	const Value findMax() const {
		// TODO calls private findMax part 2
		return nullptr;
	}

	/*
	* Finds the node with that the key
	* updates the founditem refrerence if found
	* returns true if it was found 
	* returns false if it was not 
	*/
	bool find(const KeyComparable & key , Value & founditem) const {
		//TODO calls private find part 1
		return false;
	}

	/*
	* Returns true if the item is found in the tree
	*/
	bool contains(const KeyComparable & key) const {
		// optional code
		return false;
	}

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

	/*
	* Inserts a node into the tree
	* maintains this property of the tree:
	*     All nodes to the left will be less
	*     All nodes to the right will be greater
	*/
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

	/*
	* Removes the nodes if it contains the given item
	*/
	void remove(const KeyComparable & key) {
		//TODO calls private remove
	}

};  // end of BinarySearchTree class
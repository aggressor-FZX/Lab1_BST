// BSTStartProject.cpp : Defines the entry point for the console application.
/*
* Jeff Calderon Implementation 
*  Notes, it works but the remove function is sloppy. 
* Not my best work... 
* I don't have the time for perfection at the moment so it will have to do,
* 
* So far as I can tell it works as intended.
*/
//

#include "BSTree.h"
#include "ComputerScientist.h"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <sstream>

// Helper funcion to break the argument string into parts by the delimiter
vector<string> split(const string& s, char delim) {
	stringstream ss(s);
	string item;
	vector<string> tokens;
	while (getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}

// Helper function to Read in the CStist info and puts it into vector of CStist* and then shuffled thier order
vector<ComputerScientist*> load(const string& filename) {
	vector<ComputerScientist*> list;
	std::ifstream file(filename);

	std::string str;
	while (std::getline(file, str)) {
		vector<string> tokens = split(str, ',');

		list.push_back(new ComputerScientist(tokens[1], tokens[2], tokens[3], stoi(tokens[0])));
	}

	auto rng = default_random_engine{};
	//I wonder why I need this?
	std::shuffle(std::begin(list), std::end(list), rng);
	return list;
}

int main() {
	// Uncomment later to try the different files out
	//vector<ComputerScientist*> list = load("csListSmall.txt");
	vector<ComputerScientist*> list = load("csListMed.txt"); // use this file for turn-in
	//vector<ComputerScientist*> list = load("csList.txt");

	BinarySearchTree<int, ComputerScientist*> tree;

	for (int i = 0; i < list.size(); i++) {
		tree.insert(list[i], list[i]->getID());
	}


	cout << endl << endl;
	cout << "begin test" << endl;

	//new tree
	cout << "After Insertions: " << endl;
	cout << "total size is " << list.size() << endl;

	//test print tree
	cout << "printing Tree" << endl;
	tree.printTree();

	ComputerScientist* find;

	//test min
	cout << endl << "Testing findMin : " << endl;

	find = tree.findMin();
	if (find != nullptr) {
		cout << "findMin: " << *find << endl << endl;
	}
	else {
		cout << endl << "findMin: returned a nullptr \n\n";
	}

	cout << endl << endl;

	//test find
	cout << "Testing find and findMax : " << endl;
	if (tree.find(80, find)) {
		cout <<"found key "<< *find << endl;
	}
	else {
		cout << "Not Found" << endl;
	}

	find = tree.findMax();
	if (find != nullptr) {
		cout << "findMax: " << *find << endl << endl;
	}
	else {
		cout << "findMax: returned a nullptr \n\n";

	}

	cout << "befor Deletions: " << endl;
	tree.printTree();
	for (int i = 0; i < list.size() - 1; i++) {

		int key = list[i]->getID();

		if(key %2 != 0){
			tree.remove(key);
		}

	}
	tree.printTree();

	system("pause");
	return 0;
}


// BSTStartProject.cpp : Defines the entry point for the console application.
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
	vector<ComputerScientist*> list = load("csListSmall.txt");
	//vector<ComputerScientist*> list = load("csListMed.txt"); // use this file for turn-in
	//vector<ComputerScientist*> list = load("csList.txt");

	BinarySearchTree<int, ComputerScientist*> tree2;

	for (int i = 0; i < list.size(); i++) {
		cout << *list[i] << endl;					// remove later;  temporarily inserted to prove there is data
		tree2.insert(list[i], list[i]->getID());
	}
	tree2.printTree();
	cout << endl << endl;

	BinarySearchTree<int, ComputerScientist*> tree;
	tree.insert(new ComputerScientist("Robert", "Ward", "Education", 50), 50);

	tree.insert(new ComputerScientist("Grace", "Hopper", "Compilers", 40), 40);
	tree.insert(new ComputerScientist("Alan", "Turing", "Cryptogarphy", 60), 60);
	tree.insert(new ComputerScientist("John", "von Neumann", "Hardware", 45), 45);
	tree.insert(new ComputerScientist("Dennis", "Ritchie", "Compilers", 55), 55);
	tree.insert(new ComputerScientist("Ada", "Lovelace", "Programming", 30), 30);
	tree.insert(new ComputerScientist("Edsger", "Dikstra", "Algorithms", 80), 80);
	tree.insert(new ComputerScientist("Ken", "Thompson", "OS", 70), 70);
	tree.insert(new ComputerScientist("Lonnie", "Heinke", "Game AI", 43), 43);
	tree.insert(new ComputerScientist("Thing", "One", "SkyNet", 47), 47);
	tree.insert(new ComputerScientist("Thing", "Two", "Holo Deck", 48), 48);


	ComputerScientist* find;
	//test min
	find = tree.findMin();
	if (find != nullptr) {
		cout << "findMin: " << *find << endl << endl;
	}
	else {
		cout << "findMin: returned a nullptr \n\n";
	}

	//test print
	cout << "After Insertions: " << endl;
	tree.printTree();
	cout << endl << endl;

	//test find
	cout << "Testing find and findMax : " << endl;
	if (tree.find(80, find)) {
		cout << *find << endl;
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

	tree.remove(80);
	tree.remove(50);
	tree.remove(30);
	tree.remove(40);

	cout << "After Deletions: " << endl;
	tree.printTree();

	system("pause");
	return 0;
}


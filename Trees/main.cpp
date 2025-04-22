#include "BinaryTree/BinaryTree.h"
#include "AVLTree/AVLBinaryTree.h"

#include <iostream>
#include <cassert>

template<typename T>
std::vector<T> test_binary_tree(std::shared_ptr<Tree<T>> tree, const std::vector<int>& data) {

	for (auto& n : data) tree->insert(n);
	//assert(tree->search(45) == false);
	//assert(tree->search(20) == true);

	//tree->remove(20);
	//assert(tree->search(20) == false);

	//std::cout << "\n" << "DFS view: ";
	std::vector<int> sorted_data = tree->to_vec();
	for (auto& it : data) std::cout << it << " ";

	return sorted_data;
}

int main()
{
	std::srand(std::time(nullptr));

	const int DATA_SET_SIZE = 200;
	std::vector<int> data_set;
	data_set.reserve(DATA_SET_SIZE);
	for (int i = 0; i < DATA_SET_SIZE; i++) 
		data_set.push_back((rand() % (DATA_SET_SIZE + 1)));

	std::vector<int> sorted_data_set;
	// Binary tree example
	{
		std::shared_ptr<Tree<int>> binary_tree = std::make_shared<BinaryTree<int>>();
		sorted_data_set = test_binary_tree<int>(binary_tree, data_set);
	}

	// AVL Binary tree example
	{
		std::shared_ptr<Tree<int>> avl_binary_tree = std::make_shared<AVLBinaryTree<int>>();
		std::vector<int> avl_bt_sorted = test_binary_tree<int>(avl_binary_tree, data_set);
		assert(avl_bt_sorted == sorted_data_set);
	}

	return 0;
}
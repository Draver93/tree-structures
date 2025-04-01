#include "BinaryTree/BinaryTree.h"

#include <iostream>
#include <cassert>


int main()
{
	// Binary tree example
	{
		std::shared_ptr<BinaryTree<int>> binary_tree = std::make_shared<BinaryTree<int>>();

		binary_tree->insert(50);
		binary_tree->insert(30);
		binary_tree->insert(70);
		binary_tree->insert(20);
		binary_tree->insert(40);
		binary_tree->insert(60);

		assert(binary_tree->search(45) == false);
		assert(binary_tree->search(20) == true);

		binary_tree->remove(20);
		assert(binary_tree->search(20) == false);

		std::cout << "\n" << "DFS view: ";
		std::vector<int> data = binary_tree->to_vec();
		for (auto& it : data) std::cout << it << " ";
	}

	return 0;
}
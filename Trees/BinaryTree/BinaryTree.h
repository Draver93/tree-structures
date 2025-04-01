#pragma once

#include "../Tree.h"
#include <type_traits>


template<typename T>
class BinaryTree : public Tree<T> {
private:
	struct Node {
		T value;
		std::shared_ptr<Node> left, right;
		Node(T val) : value(val) {
			left = nullptr;
			right = nullptr;
		}
	};

	std::shared_ptr<Node> root;

private:
	void insert(T val, std::shared_ptr<Node> node);
	bool search(T val, std::shared_ptr<Node> node);
	void remove(T val, std::shared_ptr<Node> node, std::shared_ptr<Node> parent);
	void to_vec_dfs(std::shared_ptr<Node> node, std::vector<T> &out);
	T pop_largest(std::shared_ptr<Node> node, std::shared_ptr<Node> parent);

public:
	BinaryTree() : Tree<T>() {};
	void insert(T val);
	void remove(T val);
	bool search(T val);
	std::vector<T> to_vec();

};
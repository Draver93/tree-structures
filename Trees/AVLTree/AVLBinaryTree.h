#pragma once

#include "../Tree.h"
#include <type_traits>


template<typename T>
class AVLBinaryTree : public Tree<T> {
private:
	enum class Rotation {
		LEFT,
		RIGHT
	};

	struct Node {
		T value;
		size_t height;
		std::shared_ptr<Node> left, right;
		Node(T val) : value(val), height(0){
			left = nullptr;
			right = nullptr;
		}
	};

	std::shared_ptr<Node> m_root;

private:
	bool search(T val, std::shared_ptr<Node> node);

	void insert(T val, std::shared_ptr<Node> node, std::shared_ptr<Node> parent);
	void remove(T val, std::shared_ptr<Node> node, std::shared_ptr<Node> parent);

	void balance(std::shared_ptr<Node> node, std::shared_ptr<Node> parent);
	void rotate(std::shared_ptr<Node> node, std::shared_ptr<Node> parent, Rotation direction);
	void update_height(std::shared_ptr<Node> node);
	
	void to_vec_dfs(std::shared_ptr<Node> node, std::vector<T> &out);
	void to_vec_bfs(std::shared_ptr<Node> node, std::queue<std::shared_ptr<Node>>& queue, std::vector<T>& out);

	T pop_largest(std::shared_ptr<Node> node, std::shared_ptr<Node> parent);

	void print_tree(std::shared_ptr<Node> node, int indent) const;
	void print_tree() const;

public:
	AVLBinaryTree() : Tree<T>() {};
	void insert(T val);
	void remove(T val);
	bool search(T val);
	std::vector<T> to_vec();

};
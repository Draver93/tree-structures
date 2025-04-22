#include "AVLBinaryTree.h"

template<typename T>
void AVLBinaryTree<T>::insert(T val) {
	if (!m_root) m_root = std::make_shared<Node>(val);
	else insert(val, m_root, nullptr);
}

template<typename T>
void AVLBinaryTree<T>::insert(T val, std::shared_ptr<Node> node, std::shared_ptr<Node> parent) {
	if (val == node->value) return;

	if (val > node->value) {
		if (node->right) insert(val, node->right, node);
		else {
			node->right = std::make_shared<Node>(val);
			node->right->height = 1;
		}
	} else {
		if (node->left) insert(val, node->left, node);
		else {
			node->left = std::make_shared<Node>(val);
			node->left->height = 1;
		}
	}
	balance(node, parent);
}

template<typename T>
T AVLBinaryTree<T>::pop_largest(std::shared_ptr<Node> node, std::shared_ptr<Node> parent) {
	if (node->right) return pop_largest(node->right, node);

	T largest_value = node->value;
	if (parent) parent->right = node->left;
	else if (m_root == node) m_root = node->left;

	return largest_value;
}

template<typename T>
void AVLBinaryTree<T>::remove(T val, std::shared_ptr<Node> node, std::shared_ptr<Node> parent) {
	if (!node) return;
	if (node->value == val) {
		if (node->left && node->right) node->value = pop_largest(node->left, node);
		else if (!node->left && !node->right) {
			if(parent->left == node) parent->left = nullptr;
			else parent->right = nullptr;
		}
		else if (node->left) {
			if (parent->left == node) parent->left = node->left;
			else parent->right = node->left;
		}
		else {
			if (parent->left == node) parent->left = node->right;
			else parent->right = node->right;
		}
	}
	else {
		if (val > node->value && node->right) remove(val, node->right, node);
		else if (val < node->value && node->left) remove(val, node->left, node);
	}

	balance(node, parent);
}

template<typename T>
void AVLBinaryTree<T>::balance(std::shared_ptr<Node> node, std::shared_ptr<Node> parent) {
	update_height(node);

	int h_right = node->right ? (int)node->right->height : 0;
	int h_left = node->left ? (int)node->left->height : 0;

	while (std::abs(h_right - h_left) > 1) {
		if (h_right > h_left)
			rotate(node, parent, Rotation::LEFT);
		else
			rotate(node, parent, Rotation::RIGHT);

		h_right = node->right ? (int)node->right->height : 0;
		h_left = node->left ? (int)node->left->height : 0;
	}
}

template<typename T>
void AVLBinaryTree<T>::update_height(std::shared_ptr<Node> node) {
	node->height = std::max(node->left ? node->left->height : 0, node->right ? node->right->height : 0) + 1;
}

template<typename T>
void AVLBinaryTree<T>::rotate(std::shared_ptr<Node> node, std::shared_ptr<Node> parent, Rotation direction) {

	std::shared_ptr<Node> new_subroot;
	switch (direction) {
		case Rotation::LEFT: {
			new_subroot = node->right;
			node->right = new_subroot->left;
			new_subroot->left = node;

			break;
		}
		case Rotation::RIGHT: {
			new_subroot = node->left;
			node->left = new_subroot->right;
			new_subroot->right = node;
			break;
		}
	}

	if (!parent) m_root = new_subroot;
	else if (parent->left == node) parent->left = new_subroot;
	else parent->right = new_subroot;

	update_height(node);
	update_height(new_subroot);
}

template<typename T>
void AVLBinaryTree<T>::remove(T val) {
	if (!m_root) return;

	if (m_root->value == val) {
		if (!m_root->left && !m_root->right) m_root = nullptr;
		else if (m_root->left && m_root->right) m_root->value = pop_largest(m_root->left, m_root);
		else m_root = (m_root->left) ? m_root->left : m_root->right;
	}
	else remove(val, m_root, nullptr);
}

template<typename T>
bool AVLBinaryTree<T>::search(T val, std::shared_ptr<Node> node) {
	if (val == node->value) return true;
	if (val > node->value && node->right) return search(val, node->right);
	if (val < node->value && node->left) return search(val, node->left);
	return false;
}

template<typename T>
bool AVLBinaryTree<T>::search(T val) {
	if (!m_root) return false;
	return search(val, m_root);
}

template<typename T>
void AVLBinaryTree<T>::to_vec_dfs(std::shared_ptr<Node> node, std::vector<T>& out) {

	if (node->left) to_vec_dfs(node->left, out);
	out.push_back(node->value);
	if (node->right) to_vec_dfs(node->right, out);
}

template<typename T>
void AVLBinaryTree<T>::to_vec_bfs(std::shared_ptr<Node> node, std::queue<std::shared_ptr<Node>>& queue, std::vector<T>& out) {
	if (!node) return;

	out.push_back(node->value);

	if (node->left) queue.push(node->left);
	if (node->right) queue.push(node->right);

	if(!queue.empty()) {
		std::shared_ptr<Node> node = queue.front();
		queue.pop();
		to_vec_bfs(node, queue, out);
	}
}

template<typename T>
std::vector<T> AVLBinaryTree<T>::to_vec() {
	//need to check size and reserve 
	std::vector<T> result;
	std::queue<std::shared_ptr<Node>> queue;

	to_vec_dfs(m_root, result);
	//to_vec_bfs(m_root, queue, result);
	return result;
}

template<typename T>
void AVLBinaryTree<T>::print_tree(std::shared_ptr<Node> node, int indent) const {
	if (!node) return;

	if (node->right) print_tree(node->right, indent + 4);

	if (indent) std::cout << std::setw(indent) << ' ';
	std::cout << node->value <<  ")\n";

	if (node->left) print_tree(node->left, indent + 4);
}

template<typename T>
void AVLBinaryTree<T>::print_tree() const {
	print_tree(m_root, 0);
}


template class AVLBinaryTree<int>;
template class AVLBinaryTree<float>;
template class AVLBinaryTree<double>;
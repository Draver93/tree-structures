#include "BinaryTree.h"

template<typename T>
void BinaryTree<T>::insert(T val) {
	if (!m_root) m_root = std::make_shared<Node>(val);
	else insert(val, m_root);
}

template<typename T>
void BinaryTree<T>::insert(T val, std::shared_ptr<Node> node) {
	if (val == node->value) return;

	if (val > node->value) {
		if (node->right) insert(val, node->right);
		else node->right = std::make_shared<Node>(val);
	} else {
		if (node->left) insert(val, node->left);
		else node->left = std::make_shared<Node>(val);
	}
}


template<typename T>
T BinaryTree<T>::pop_largest(std::shared_ptr<Node> node, std::shared_ptr<Node> parent) {
	if (node->right) return pop_largest(node->right, node);

	T largest_value = node->value;
	if (parent) parent->right = node->left;
	else if (m_root == node) m_root = node->left;

	return largest_value;
}

template<typename T>
void BinaryTree<T>::remove(T val, std::shared_ptr<Node> node, std::shared_ptr<Node> parent) {
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
}

template<typename T>
void BinaryTree<T>::remove(T val) {
	if (!m_root) return;

	if (m_root->value == val) {
		if (!m_root->left && !m_root->right) m_root = nullptr;
		else if (m_root->left && m_root->right) m_root->value = pop_largest(m_root->left, m_root);
		else m_root = (m_root->left) ? m_root->left : m_root->right;
	}
	else remove(val, m_root, nullptr);
}


template<typename T>
bool BinaryTree<T>::search(T val, std::shared_ptr<Node> node) {
	if (val == node->value) return true;
	if (val > node->value && node->right) return search(val, node->right);
	if (val < node->value && node->left) return search(val, node->left);
	return false;
}

template<typename T>
bool BinaryTree<T>::search(T val) {
	if (!m_root) return false;
	return search(val, m_root);
}


template<typename T>
void BinaryTree<T>::to_vec_dfs(std::shared_ptr<Node> node, std::vector<T>& out) {

	if (node->left) to_vec_dfs(node->left, out);
	out.push_back(node->value);
	if (node->right) to_vec_dfs(node->right, out);
}

template<typename T>
std::vector<T> BinaryTree<T>::to_vec() {
	//need to check size and reserve 
	std::vector<T> result;
	to_vec_dfs(m_root, result);

	return result;
}


template class BinaryTree<int>;
template class BinaryTree<float>;
template class BinaryTree<double>;
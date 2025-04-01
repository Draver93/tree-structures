#pragma once

#include <vector>
#include <memory>

template<typename T>
class Tree {
public:
	virtual void insert(T val) = 0;
	virtual void remove(T val) = 0;
	virtual bool search(T val) = 0;
	virtual std::vector<T> to_vec() = 0;
};
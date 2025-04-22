#pragma once

#include <cmath>
#include <cassert>

#include <iomanip>
#include <iostream>
#include <sstream>

#include <queue>
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
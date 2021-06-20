#pragma once

#include "Entity.h"

template <typename T>
class Node
{
public:
	T* _current;
	Node<T>* _prev;
	Node<T>* _next;
	Node(T* entity) {
		_current = entity;
		_prev = nullptr;
		_next = nullptr;
	}

	~Node() {
		delete _current;
	}
};


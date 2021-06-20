#pragma once

#include "Node.h"

template <typename T>
class List
{
private:
	Node<T>* _head;
	Node<T>* _tail;
	void remove_intern(Node<T>* node) {
		if (node->_prev == nullptr && node->_next == nullptr) {
			delete node;
			_head = nullptr;
			_tail = nullptr;
			return;
		}

		if (node->_prev != nullptr && node->_next == nullptr) {
			_tail = node->_prev;
			delete node;
			return;
		}

		if (node->_prev == nullptr && node->_next != nullptr) {
			_head = node->_next;
			delete node;
			return;
		}

		node->_prev->_next = node->_next;
		delete node;
	}
public:
	int _size;

	List() {
		_head = nullptr;
		_tail = nullptr;
		_size = 0;
	};

	/*
	 * Add an entity to the end of the list
	*/
	void push(T* entity) {
		// Case first elem in list
		if (_head == nullptr || _tail == nullptr) {
			_head = new Node<T>(entity);
			_tail = _head;
			_size += 1;
			return;
		}
		Node<T>* newNode = new Node<T>(entity);
		newNode->_prev = _tail;
		_tail->_next = newNode;
		_tail = newNode;
		_size += 1;
		return;
	};

	/*
	 * Remove last item in list
	*/
	void pop() {
		Node<T> *tmp = _tail->_prev;
		
		if (_tail == nullptr) {
			return;
		}

		if (tmp == nullptr) {
			_head = nullptr;
			_tail = nullptr;
			return;
		}

		tmp->_next = nullptr;

		/*if (_head == tmp) {
			_head = nullptr;
			_tail = nullptr;
			return;
		}*/

		//delete _tail;
		_tail = tmp;

		_size -= 1;
	};

	/*
	 * Find entity node via entity in it
	*/
	Node<T>* find(T* entity) {
		auto tmp = _head;
		while (tmp) {
			if (tmp->_current == entity) {
				return tmp;
			}
		}
	};

	/*
	 * Find EntityNode via index
	*/
	Node<T>* find(int index) {
		if (index < 0 || index > _size) {
			return nullptr;
		}

		auto tmp = _head;

		for (int i = 0; i < _size; i += 1) {
			tmp = tmp->_next;
		}

		return tmp;
	};

	/*
	 * Remove an entity from the list
	*/
	void remove(T* entity) {
		remove_intern(find(entity));
	};

	/*
	 * Remove an entity from the list
	*/
	void remove(int index) {
		remove_intern(find(index));
	};

	const int& size() const {
		return _size;
	};
	const Node<T>* get_head() const {
		return _head;
	};
};
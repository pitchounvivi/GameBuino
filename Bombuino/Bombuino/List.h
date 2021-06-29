#pragma once

#include "Node.h"
#include <Gamebuino-Meta.h>

template <typename T>
class List
{
private:
	Node<T>* _head;
	Node<T>* _tail;

	void remove_intern(Node<T>* node) {
		if (!node) {
			return;
		}

		// remove head and is last item
		if (node->_prev == nullptr && node->_next == nullptr) {
			_head = nullptr;
			_tail = nullptr;
			delete node;
			_size -= 1;
			return;
		}

		// remove tail
		if (node->_prev != nullptr && node->_next == nullptr) {
			_tail = node->_prev;
			_tail->_next = nullptr;
			delete node;
			_size -= 1;
			return;
		}
		// remove head but not us last item
		if (node->_prev == nullptr && node->_next != nullptr) {
			_head = node->_next;
			_head->_prev = nullptr;
			delete node;
			_size -= 1;
			return;
		}

		// base case
		node->_prev->_next = node->_next;
		node->_next->_prev = node->_prev;
		delete node;
		_size -= 1;
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
		Node<T>* tmp = nullptr;

		if (_tail == nullptr) {
			return;
		}

		tmp = _tail->_prev;


		if (tmp == nullptr && _size == 1) {
			_head = nullptr;
			_tail = nullptr;
			_size -= 1;
			return;
		}

		tmp->_next = nullptr;

		/*if (_head == tmp) {
			_head = nullptr;
			_tail = nullptr;
			return;
		}*/

		// free memory
		delete _tail;

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
		return nullptr;
	};

	/*
	 * Find EntityNode via index
	*/
	Node<T>* find(int index) {
		if (index < 0 || index > _size) {
			return nullptr;
		}

		auto tmp = _head;

		for (int i = 0; tmp && i < index; i += 1) {
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

	/*
	 * Get the size of the list
	*/
	const int& size() const {
		return _size;
	};

	// Temporary we need to overload iterator function for better looping abstraction
	const Node<T>* get_head() const {
		return _head;
	};
};

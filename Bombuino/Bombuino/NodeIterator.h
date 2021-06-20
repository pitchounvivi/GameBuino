#pragma once

// TODO make Iterator work on my linked list
template <typename T>
class NodeIterator
{
protected:
	Node<T> *_node;

	NodeIterator(Node<T>* node) {
		_node = node;
	}

public:
	NodeIterator& operator++() {
		_node = _node->_next;
		return *this;
	}

	bool operator==(Iterator b) const { return _node == b._node; }
	bool operator!=(Iterator b) const { return _node != b._node; }

};


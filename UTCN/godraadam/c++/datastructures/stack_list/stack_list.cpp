/*
Author: godraadam @ UTCN 2019
Description: basic, generic stack implementation using single linked list as container
Operations: pop()  -> O(1)
			push() -> O(1) 
			peek() -> O(1)
			empty()-> O(1)
			full() -> O(1)
			size() -> O(1)

*/

#include <stdexcept>

template <class T>

class stack final {


	//Helper class for linking data
	private: class node {
		public:T item;
		node* next = nullptr;

		public: node(T item) {
			this->item = item;
		}
	};

	//Handle to acces the stack
	private: node* head = nullptr;

	//Tracks current number of items on the stack
	private: size_t _size = 0;


	//Return true only if stack is empty
	public: bool empty() {
		return _size == 0;
	}

	//Returns current number of items on stack
	public: size_t size() {
		return _size;
	}

	//Push new item on top of stack
	public: void push(T item) {
		node* p = new node(item);
		if (empty()) head = p;
		else {
			p->next = head;
			head = p;
		}
		_size++;
	}

	//Pop the item from the top of the stack
	public: T pop() {
		if (empty()) throw std::length_error("Stack is empty!");
		T ret = head->item;
		node* p = head;
		head = p->next;
		free(p);
		_size--;
		return ret;
	}

	//Return the item on top of the stack without rmoving it
	public: T peek() {
		if (empty()) throw std::length_error("Stack is empty!");
		return head->item;
	}
};

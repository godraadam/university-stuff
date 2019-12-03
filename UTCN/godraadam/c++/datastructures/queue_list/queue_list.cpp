/*
Author: godraadam @ utcn 2019
Description: basic, generic queue implementation using double linked list as container
Operations: enqueue() -> O(1)
			dequeue() -> O(1)
			peek()	  -> O(1)
			empty()   -> O(1)
			size()    -> O(1)
*/

#include <stdexcept>

template<class T>

class queue final {
	

	//Helper class for linking items
	private: class node {
		public: T item;
		public: node* next = nullptr;
		public: node* prev = nullptr;
		public: node(T item) {
			this->item = item;
		}
	};

	//Handle for the front of the queue
	private: node* head = nullptr;

	//Handle for the end of the queue
	private: node* tail = nullptr;

	//Tracks the actual number of items in queue
	private: size_t _size = 0;

	//Returns true only if queue is empty
	public: bool empty() {
		return _size == 0;
	}

	//Returns the current number of items in queue
	public: size_t size() {
		return _size;
	}
	
	//Returns the item at the front of the queueu i.e. the one that was inserted first
	public: T front() {
		if (empty()) throw std::length_error("Queue is empty!");
		return tail->item;
	}

	//Return the item at the end of the queue i.e. the one inserted last
	public: T end() {
		if (empty()) throw std::length_error("Queue is empty!");
		 return head->item;
	}

	//Adds an item to the end of the list
	public: void enqueue(T item) {
		node* p = new node(item);
		if (empty()) head = tail = p;
		else {
			p->next = head;
			head->prev = p;
			head = p;
		}
		_size++;
	}

	//Removes the item from the front of the queue and returns it
	public: T dequeue() {
		if (empty()) throw std::length_error("Queue is empty!");
		T ret = tail->item;
		node* p = tail;
		tail = p->prev;
		free(p);
		_size--;
		return ret;
	}
};
/*
Author: godraadam @ utcn 2019
Description: basic, generic double linked list implementation
Operations: 
			CREATE
			new list(array[n]) -> O(n)
			new list()	-> O(1)

			INSERT OPERATIONS
			push()		-> O(1)
			append()	-> O(1)
			insert(i)	-> O(i)

			REMOVE OPERATIONS
			pop()		-> O(1)
			trunc()		-> O(1)
			remove(i)	-> O(i)

			ACCES OPERATIONS
			front()		-> O(1)
			end()		-> O(1)
			at(i)		-> O(i)
			find()		-> O(n)

			OTHER
			empty()		-> O(1)
			length()	-> O(1)
			toArray()	-> O(n)
*/

#include <stdexcept>
#include <iostream>

template <class T>

class list final {

	//Helper class for linking items
	private: class node final {
		public: T item;
		public: node* next = nullptr;
		public: node* prev = nullptr;

		public: node(T item) {
			this->item = item;
		}
	};


	//Keeps track of number of items in the list
	private: size_t len = 0;

	//Handle for the front of the list
	private: node* head = nullptr;

	//Handle for the end of the list
	private: node* tail = nullptr;

	//Default constructor
	public: list() {}

	//Construct a list from an array 
	public: list(T* arr, size_t size) {
		for (int i = 0; i < size; i++) this->append(arr[i]);
	}

	//Remove and return item from front of the list
	public: T pop() {
		if (empty()) throw std::length_error("List is empty!");

		node* p = head;
		head = p->next;
		head->prev = nullptr;
		T ret = p->item;
		delete p;
		len--;
		return ret;
	}

	//Add new item to the front of the list
	public: void push(T item) {
		node* p = new node(item);
		if (empty()) head = tail = p;
		else {
			p->next = head;
			head->prev = p;
			head = p;
		}
		len++;
	}

	//Add new item to the end of the list
	public: void append(T item) {
		if (empty()) push(item);
		else {
			node* p = new node(item);
			tail->next = p;
			p->prev = tail;
			tail = p;
			len++;
		}
	}
	
	//Remove item from end of the list end return it
	public: T trunc() {
		if (empty()) throw std::length_error("Stack is empty!");

		if (len == 1) return pop();

		node* p = tail;

		//save item to return later
		T ret = p->item;

		//rearrange links
		tail = p->prev;
		tail->next = nullptr;

		//free up memory
		delete p;

		//update length
		len--;
		return ret;
	}

	//Insert new item at given index
	public: void insert(T item, size_t index) {
		if (index > len) throw std::out_of_range("Index was out of range!");

		if (empty() || index == 0) push(item);
		if (index == len) append(item);

		else {
			//create new node
			node* p = new node(item);

			//get handle to preceeding node
			node* q;
			if (index < len / 2) {
				q = head;
				for (int i = 0; i < index - 1; i++) q = q->next;
			}
			else {
				q = tail;
				for (int i = len - 1; i > index - 1; i--) q = q->prev;
			}

			//rearrange links
			p->next = q->next; 
			p->prev = q;
			q->next = p;
			p->next->prev = p;

			//update height
			len++;
		}
	}
	
	//Remove and return item at given index
	public: T remove(size_t index) {
		if (index >= len) throw std::out_of_range("Index was out of range!");
		if (empty()) throw std::length_error("List is empty!");

		if (len == 1 || index == 0) return pop();
		if (index == len - 1) return trunc();

		//get handle to preceeding node
		node* q;
		if (index < len / 2) {
			q = head;
			for (int i = 0; i < index - 1; i++) q = q->next;
		}
		else {
			q = tail;
			for (int i = len; i > index - 1; i--) q = q->prev;
		}

		//the node to be deleted
		node* p = q->next;

		//save the item to return for later
		T ret = p->item;

		//rearrange links
		q->next = p->next;
		p->next->prev = q;

		//free up memory
		delete p;

		//update length
		len--;
		return ret;
	}

	//Returns the item at given index from the list. Indexing from 0
	public: T at(size_t index) {
		if (index >= len) throw std::out_of_range("Index was outside range!");

		node* p;
		if (index < len / 2) {
			p = head;
			for (int i = 0; i < index; i++) p = p->next;
		}
		else {
			p = tail;
			for (int i = len - 1; i > index; i--) p = p->prev;
		}
		return p->item;
	}

	//Returns the index of the first occurence of an item, -1 if not found
	public: size_t find(T item) {
		node* p = head;
		for (int i = 0; i < len; i++) {
			if (p->item == item) return i;
			p = p->next;
		}
		return -1; //because index is size_t this will actually be a large value not -1
	}

	 //Returns true if list is empty, otherwise false
	public: bool empty() {
		return len == 0;
	}

	//Returns the current number of items in the list
	public: size_t length() {
		return len;
	}
	
	//Returns the item at the front of the list without removing it
	public: T front() {
		if (empty()) throw std::length_error("List is empty!");
		return head->item;
	}

	////Returns the item at the end of the list without removing it
	public: T end() {
		if (empty()) throw std::length_error("List is empty!");
		return tail->item;
	}

	//Returns an array with equivalent content, order and size of this list
	public: T* toArray() {
		T* arr = new T[len];
		node* p = head;
		for (int i = 0; i < len; i++) {
			arr[i] = p->item;
			p = p->next;
		}
		return arr;
	}
};

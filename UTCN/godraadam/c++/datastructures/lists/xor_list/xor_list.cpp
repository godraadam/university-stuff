/*
Author: godraadam @ utcn 2019
Description: memory efficient, generic double linked list implementation exploiting xor operation on pointers
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
			reverse()	-> O(1)
			toArray()	-> O(n)
*/


#include <stdexcept>

template <class T>

class list final {

	//Helper class for linking items
	private: class node final {

		private: node* pxn = nullptr; // address of prev xor address of next
		private: T item;
		
		private: node(T item) {
			this->item = item;
		}

		friend class list;
	};
	
	//Fields_______________________________________________________________

	//Handle for the first node in the list
	private: node* head = nullptr;

	//Handle for the last node in the list
	private: node* tail = nullptr;

	//Keep track of current length of the list
	private: size_t len = 0;

	//Methods______________________________________________________________

	//Construct list from array
	public: list(T* arr, size_t size) {
		for (int i = 0; i < size; i++) append(arr[i]);
	}

	//Returns true only if the list contains no items
	public: bool empty() {
		return len == 0;
	}

	//Returns the current number of items in the list
	public: size_t length() {
		return len;
	}

	//Add a new item to the front of the list
	public: void push(T item) {
		node* p = new node(item);
		if (empty()) {
			head = tail = p;
		}
		else {
			head->pxn = next(head, p);
			p->pxn = head; //head xor null = head
			head = p;
		}
		len++;
	}

	//Remove and return item from the front of the list
	public: T pop() {
		if (empty()) throw std::length_error("List is empty!");
		T ret = head->item;
		node* p = head->pxn; //second node, because nxp of head is null xor next = next
		node* q = head;
		p->pxn = next(p, head);
		head = p;
		delete q;
		len--;
		return ret;
	}

	//Because of the symmetry of the xor operation, we can reuse push(), reversing the list
	//Then after the push operation undo the reverse

	//Add new item to the end of the list
	public: void append(T item) {
		reverse();
		push(item);
		reverse();
	}

	//Because of the symmetry of the xor operation, we can reuse pop(), reversing the list
	//Then after the push operation undo the reverse

	//Remove and return item from the end of the list
	public: T trunc() {
		if (empty()) throw std::length_error("List is empty!");
		reverse();
		T ret = pop();
		reverse();
		return ret;
	}

	//Return first item in the list without removing it
	public: T front() {
		if (empty()) throw std::length_error("List is empty!");
		return head->item;
	}

	//Return last item in the list without removing it
	public: T end() {
		if (empty()) throw std::length_error("List is empty!");
		return tail->item;
	}
	

	//Insert new item at given index
	public: void insert(T item, size_t index) {
		if (index < 0 || index >= len) throw std::length_error("Index is out of range!");

		if (index == 0) {
			push(item);
			return;
		}
		else if (index == len) {
			append(item);
			return;
		}

		node* p = nullptr;
		node* q;
		if (index < len / 2) {
			q = head;
			for (int i = 0; i < index - 1; i++) {
				node* tmp = q;
				q = next(q, p);
				p = tmp;
			}
		}
		else {
			q = tail;
			for (int i = len - 1; i > index; i--) {
				node* tmp = q;
				q = next(q, p);
				p = tmp;
			}
		}

		node* r = next(q, p);
		p = new node(item);
		p->pxn = ptr_xor(q, r);
		q->pxn = ptr_xor(next(q, r), p);
		r->pxn = ptr_xor(next(r, q), p);
		len++;
	}

	//Remove and return item at given index
	public: T remove(size_t index) {
		if (index < 0 || index >= len) throw std::length_error("Index is out of range!");
		if (empty()) throw std::length_error("List is empty!");

		if (index == 0) return pop();
		if (index == len - 1) return trunc();

		node* p = nullptr;
		node* q;
		if (index < len / 2) {
			q = head;
			for (int i = 0; i < index; i++) {
				node* tmp = q;
				q = next(q, p);
				p = tmp;
			}
		}
		else {
			q = tail;
			for (int i = len - 1; i > index; i--) {
				node* tmp = q;
				q = next(q, p);
				p = tmp;
			}
		}

		T ret = q->item;
		node* r = next(q, p);
		p->pxn = ptr_xor(next(p, q), r);
		r->pxn = ptr_xor(next(r, q), p);
		delete q;
		len--;
		return ret;

	}


	//Returns item at given index, without removing it
	public: T at(size_t index) {
		if (index < 0 || index >= len) throw std::length_error("Index is out of range!");
		node* p = nullptr;
		node* q;
		if (index < len / 2) {
			q = head;
			for (int i = 0; i < index; i++) {
				node* tmp = q;
				q = next(q, p);
				p = tmp;
			}
		}
		else {
			q = tail;
			for (int i = len - 1; i > index; i--) {
				node* tmp = q;
				q = next(q, p);
				p = tmp;
			}
		}
		return q->item;
	}

	//Return the index of first occurence of a given item, -1 otherwise
	public: size_t find(T item) {
		node* p = nullptr;
		node* q = head;
		size_t index = 0;
		while (q) {
			if (q->item == item) return index;
			node* tmp = q;
			q = next(q, p);
			p = q;
			index++;
		}
		return -1;
	}

	//Returns an array of size this.length(), with the contents in their corresponding positions
	public: T* toArray() {
		T* arr = new T[len];
		node* p = nullptr;
		node* q = head;
		size_t index = 0;
		while (q) {
			arr[i] = q->item;
			node* tmp = q;
			q = next(q, p);
			p = q;
			index++;
		}
		return arr;
	}

	//Due to the symmetry of the xor operation it is enough to simply swap
	//the head and tail handles to reverse a list
		  
	//Reverses the list
	public: void reverse() {
		//simply swap head and tail
		node* tmp = head;
		head = tail;
		tail = tmp;
	}

	//Helpers______________________________________________________

	//Helper method to calculate the xor of two pointers
	private: node* ptr_xor(node* p, node* q) {
		uintptr_t _q = (uintptr_t)q;
		uintptr_t _p = (uintptr_t)p;
		uintptr_t pxq = _p xor _q;
		return (node*)pxq;
	}

	//Helper method  to acces next node based on current and prevoius nodes
	//Note: this also gives access to previous node based on current and next node
	//Due to the symmetry of the xor operation
	private: node* next(node* current, node* prev) {
		return ptr_xor(current->pxn, prev);
	}
};
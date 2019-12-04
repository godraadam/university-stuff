/*
Author: godraadam @ utcn 2019
Description: basic, generic stack implementation using array as container
Operations: pop()  -> O(1)
			push() -> O(1) 
			peek() -> O(1)
			empty()-> O(1)
			full() -> O(1)
			size() -> O(1)
*/

#include <stdexcept>

template<class T>

class stack final {

	//Fields_______________________________________

	//Maximum number of elements this stack can hold
	private: size_t max_size = UINT16_MAX; //should be enough for most purposes, more could take up too much memory on stack

	//Pointer to the top of the stack
	private: size_t head = 0;

	//Container to actually store the items
	private: T* _stack;

	//Methods______________________________________

	//Default constructor
	public: stack() {
		_stack = new T[max_size];
	}
	
	//Constructor with custom maximum size, practical to save memory for smaller scope purposes
	public: stack(size_t max_size) {
		if (max_size > this->max_size) throw std::bad_array_new_length("Stack size too large!");
		this->max_size = max_size;
		_stack = new T[max_size];
	}
	
	//Returns true only if stack is empty
	public: bool empty() {
		return head == 0;
	}

	//Returns true only if stack is full
	public: bool full() {
		return head == max_size;
}

	//Push item on top of stack
	public: void push(T item) {
		if (full()) throw std::length_error("Stack is full!");
		_stack[head++] = item;
	}

	//Pop item from top of stack and return it
	public: T pop() {
		if (empty()) throw std::length_error("Stack is empty!");
		return _stack[head--];
	}

	//Return item on top of stack, without removing it
	public: T peek() {
		if (empty()) throw std::length_error("Stack is empty!");
		return _stack[head - 1];
	}

	//Returns current number of items in the stack
	public: size_t size() {
		return head;
	}
	
	//Return total number of items this stack can hold
	public: size_t maxSize() {
		return this->max_size;
	}
};
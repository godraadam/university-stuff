/*
Author: godraadam @ utcn 2019
Description: generic list data structure implemented using a dynamic array
Operations:
			CREATE
			new list(array[n]) -> O(n)
			new list()	-> O(1)

			INSERT OPERATIONS
			push()		-> O(n)
			append()	-> O(1) (amortized time)
			insert(i)	-> O(n - i) 
			set(i)		-> O(1)

			REMOVE OPERATIONS
			pop()		-> O(n)
			trunc()		-> O(1)
			remove(i)	-> O(n - i)
			clear()		-> O(1)

			ACCES OPERATIONS
			front()		-> O(1)
			end()		-> O(1)
			at(i)		-> O(i)
			find()		-> O(n)

			OTHER
			empty()		-> O(1)
			contains()	-> O(n)
			length()	-> O(1)
			trim()		-> O(n)
			toArray()	-> O(n)
*/


#include <stdexcept>

template <class T>

class list final {

	//Fields_________________________________________________________________________________

	//Space allocated for items. If exceeded, the array containing the list will resize itself
	private: size_t _capacity = 10;

	//Counter for current number of items
	private: size_t _size = 0;

	//Growth factor, by which the array is scaled in size when resizing
	//Chose it to be approximately phi (the golden ration) because why not
	private: static const int gf = 1.618;

	//Container for the list
	private: T* _list;

	//Methods________________________________________________________________________________

	//Default constructor
	public: list() {
		_list = new T[_capacity];
	}

	//Constructor with custom initial capacity
	public: list(size_t capacity) {
		if (capacity <= 0) throw std::bad_array_new_length("Invalid size!");
		_capacity = capacity;
		_list = new T[_capacity];
	}

	//Add new item to the front of the list
	public: void push(T item) {
		if (_size == _capacity) resize();
		insert(item, 0);
	}

	//Remove and return item from front of the list
	public: T pop() {
		if (empty()) throw std::length_error("List is empty!");
		return remove(0);
	}

	//Add item to the end of the list
	public: void append(T item) {
		if (_size == _capacity) resize();
		_list[_size++] = item;
	}
	
	//Remove and return item from the end of the list
	public: T trunc() {
		if (empty()) throw std::length_error("List is empty!");
		return _list[--_size];
	}

	//Insert item at given index
	public: void insert(T item, size_t index) {
		if (index < 0 || index > _size) throw std::length_error("Index is out of bounds!");
		if (_size == _capacity) resize();
		memcpy(_list + index + 1, _list + index, sizeof(T) * (_size - index));
		_list[index] = item;
		_size++;
	}
	
	//Remove and return item from given index
	public: T remove(size_t index) {
		if (!range(index)) throw std::length_error("Index is out of bounds!");
		if (empty()) throw std::length_error("List is empty!");

		T ret = _list[index];
		memcpy(_list + index, _list + index + 1, sizeof(T) * (_size - index));
		_size--;
		return ret;
	}

	//Change the value of the item at given index to given value
	public: void set(size_t index, T item) {
		if (!range(index)) throw std::length_error("Index is out of bounds!");
		_list[index] = item;
	}

	//Returns the index of the first occurence of given item, -1 if not found
	public: size_t find(T item) {
		for (int i = 0; i < _size; i++)
			if (_list[i] == item) return i;
		return -1;
	}

	//Returns current capacity of the list
	public: size_t capacity() {
		return _capacity;
	}
	
	//Returns current number of items in the list
	public: size_t length() {
		return _size;
	}

	//Returns true only if list contains no items
	public: bool empty() {
		return _size == 0;
	}

	//Returns item at the front of the list
	public: T front() {
		if (empty()) throw std::length_error("List is empty!");
		return _list[0];
	}

	//Returns item at end of the list
	public: T end() {
		if (empty()) throw std::length_error("List is empty!");
		return _list[_size - 1];
	}

	//Returns item at specified index
	public: T at(size_t index) {
		if (!range(index)) throw std::length_error("Index is out of bounds!");
		return _list[index];
	}

	//Returns true only if the given item is in the list
	public: bool contains(T item) {
		return (int) find(item) >= 0;
	}

	//Reset the list
	public: void clear() {
		_size = 10;
		trim();
		_size = 0;
	}

	//Resize the list to current size
	public: void trim() {
		_capacity = _size;
		T* tmp = new T[_capacity];
		memmove(tmp, _list, sizeof(T) * _size);
		_list = tmp;
	}

	//Returns an array with the curresnt size of the list containg the same items
	public: T* toArray() {
		T* tmp = new T[_size];
		memcpy(tmp, _list, sizeof(T) * _size);
		return tmp;
	}

	//Helpers____________________________________________________________________________

	//Scale the capacity of the container by growth factor
	private: void resize() {
		T* tmp = new T[_capacity];
		memmove(tmp, _list, sizeof(T) * _size);
		_list = new T[(int)(_capacity * gf)];
		memmove(_list, tmp, sizeof(T) * _size);
	}

	//Check if given index is valid
	private: bool range(int index) {
		if (index < 0 || index >= _size) return false;
		return true;
	}
};

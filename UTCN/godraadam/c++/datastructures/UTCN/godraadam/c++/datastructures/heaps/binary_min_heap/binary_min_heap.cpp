/*
Author: godraadam @ utcn 2019
Description: standard, generic binary min-heap implementation using an array as underlying container
Operations: push()	-> O(log n)
			pop()	-> O(log n)
			popAndPush() -> O(log n) (instead of 2* O(log n) for pop() and then push())
			peek()	-> O(1)
			heapify(array[n]) -> O(n)
			size()	-> O(1)
			empty()	-> O(1)
			full()	-> O(1)
*/

#include <stdexcept>

template <class T>

class minHeap final {

	//Fields_____________________________________

	//Maximum number of items this heap can hold
	private: size_t max_size = UINT16_MAX;

	//Current number of items in the heap
	private: size_t _size = 0;

	//Actual container to store the items
	private: T* heap;

	//Methods_____________________________________

	//Default constructor
	public: minHeap() {
		heap = new T(max_size);
	}
	
	//Constructor with custom capacity
	public: minHeap(size_t max_size) {
		this->max_size = max_size;
		heap = new T[max_size];
	}

	//Construct heap from given array
	public: minHeap(T* arr, size_t size) {
		heap = new T[max_size];
		_size = size;
		memcpy(heap, arr, sizeof(arr) * size);

		//heapify each internal node to ensure heap property
		for (int i = _size / 2 - 1; i >= 0; i--) {
			heapify(i);
		}
	}

	//Construct heap from given array and set capacity
	public: minHeap(T* arr, size_t size, size_t max_size) {
		this->max_size = max_size;
		heap = new T[max_size];
		_size = size;
		memcpy(heap, arr, _size);

		//heapify each internal node to ensure heap property
		for (int i = _size / 2 - 1; i >= 0; i--) heapify(i);
	}

	//Insert new item to heap while preserving heap property
	public: void push(T item) {
		if (full()) throw std::length_error("Heap is full!");
		heap[_size++] = item;

		size_t index = _size - 1;
		size_t _parent = parent(index);
		while (index > 0 and heap[_parent] > heap[index]) {
			swap(heap[index], heap[_parent]);
			index = _parent;
			_parent = parent(index);
		}
	}

	//Remove and return root of the heap while preserving heap property
	public: T pop() {
		swap(heap[0], heap[--_size]);
		heapify(0);
		return heap[_size];
	}

	//More efficient than pop() and then push() applied separately
	public: T popAndPush(T item) {
		T ret = heap[0];
		heap[0] = item;
		heapify(0);
		return ret;
	}

	//Return root of the heap without removing it
	public: T peek() {
		if (empty()) throw std::length_error("Heap is empty!");
		return heap[0];
	}

	//Returns true if heap contains no items otherwise false
	public: bool empty() {
		return _size == 0;
	}

	//Returns true only of the number of items inside heap has reached maximum capacity
	public: bool full() {
		return _size == max_size;
	}

	//Returns the current number of items inside the heap
	public: size_t size() {
		return _size;
	}

	//Returns maximum capacity of the heap
	public: size_t maxSize() {
		return max_size;
	}

	//Helpers______________________________________________________
	

	//Return index of left child inside array
	private: size_t left(size_t index) {
		return 2 * index + 1;
	}

	//Return index of right child inside array
	private: size_t right(size_t index) {
		return 2 * index + 2;
	}
	
	//Return index of parent inside array
	private: size_t parent(size_t index) {
		return index > 0 ? (index - 1) / 2 : 0;
	}

	//Helper method to enforce heap property
	private: void heapify(int index) {
		int _left = left(index);
		int _right = right(index);
		int min = index;

		if (_left < _size && heap[_left] < heap[min]) min = _left;
		if (_right < _size && heap[_right] < heap[min]) min = _right;

		if (min != index) {
			swap(heap[min], heap[index]);
			this->heapify(min);
		}
	}

	 //Helper method to exchange items
	private: void swap(T& a, T& b) {
		T c = a;
		a = b;
		b = c;
	}
};
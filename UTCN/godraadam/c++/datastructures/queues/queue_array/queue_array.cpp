/*
Author: godraadam @ utcn 2019
Description: basic, generic queue implementation using array as container
Operations: enqueue() -> O(1)
			dequeue() -> O(1)
			peek()	  -> O(1)
			empty()	  -> O(1)
			full()	  -> O(1)
			size()	  -> O(1)
*/

#include <stdexcept>

template <class T>

class queue final {

	//Maximum number of items this queue can hold
	private: size_t max_size = UINT16_MAX;

	//Index of first item
	private: size_t _front = 0;

	//Index of last item
	private: size_t _end = 0;

	//Actual container to store the items
	private: T *_queue;

	//Default constructor
	public: queue() {
		_queue = new T[max_size];
	}

	//Constructor with custom size
	public: queue(size_t max_size) {
		if (max_size > this->max_size) throw std::bad_array_new_length("Queue size too large!");
		this->max_size = max_size;
		_queue = new T[max_size];
	}

	//Returns current number of items in queue
	public: size_t size() {
		return _front - _end;
	}

	//Return true only if queue is empty
	public: bool empty() {
		return _front == _end;
	}

	//Returns true only if queue is full
	public: bool full() {
		return _front - _end == max_size;
	}

	//Returns the item at the front of the queue, i.e. the one added first
	public: T front() {
		if (empty()) throw std::length_error("Queue is empty!");
		return _queue[_front];
	}

	//Return the item at the end of the queue, i.e. the one added last
	public: T end() {
		if (empty()) throw std::length_error("Queue is empty!");
		return _queue[_end - 1];
	}

	//Add item to the end of the queue
	public: void enqueue(T item) {
		if (full()) throw std::length_error("Queue is full!");
		_queue[_end++] = item;
	}

	//Removes item from end of the queue and returns it
	public: T dequeue() {
		if (empty()) throw std::length_error("Queue is empty!");
		//When queue is emptied out, reset
		if (size() == 1) {
			T ret = _queue[_front];
			_front = _end = 0;
			return ret;
		}
		return _queue[_front++];
	}
};
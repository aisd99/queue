#include <iostream>
#include <string>
#include <sstream>

template<typename T>
class Queue {
public:
	Queue();
	Queue(size_t new_capacity);
	~Queue();

	void CommandManager();
	void Push(const T& item);
	void Pop();
	void SetSize(size_t new_capacity);
	void Print();
private:
	T* values = NULL;
	size_t _capacity = 0;
	int _tail = -1;
};

template<typename T>
Queue<T>::Queue() {}

template<typename T>
Queue<T>::Queue(size_t new_capacity) {
	values = new T[new_capacity];
	_capacity = new_capacity;
}

template<typename T>
Queue<T>::~Queue() {
	delete[] values;
}

template<typename T>
void Queue<T>::CommandManager() {
	for (std::string line; std::getline(std::cin, line); ) {
		std::istringstream is(line);
		std::string command;
		is >> command;
		if (command == "set_size") {
			if (values == NULL) {
				int new_size;
				is >> new_size;
				SetSize(new_size);
			}
			else _ERROR_
		}
		else if (command == "push") {
			T new_item;
			is >> new_item;
			Push(new_item);
		}
		else if (line == command) {
			if (command == "pop") {
				Pop();
			}
			else if (command == "print") {
				Print();
			}
			else if (command.size() > 0) {
				_ERROR_
			}
		}
		else _ERROR_
	}
}

template<typename T>
void Queue<T>::Push(const T& item) {
	if (_tail == _capacity - 1) {
		std::cout << "overflow" << std::endl;
	}
	else {
		values[++_tail] = item;
	}
}

template<typename T>
void Queue<T>::Pop() {
	if (_tail == -1) {
		std::cout << "underflow" << std::endl;
	}
	else {
		for (size_t i = 0; i < _tail; ++i) {
			values[i] = values[i + 1];
		}
		--_tail;
	}
}

template<typename T>
void Queue<T>::SetSize(size_t new_capacity) {
	if (new_capacity != _capacity) {
		T* new_values = new T[new_capacity];
		for (int i = 0; i < _tail && i < new_capacity; ++i) {
			new_values[i] = std::move(values[i]);
		}
		delete[] values;
		if (new_capacity < _capacity) {
			_tail = new_capacity;
		}
		_capacity = new_capacity;
		values = new_values;
	}
}

template<typename T>
void Queue<T>::Print() {
	if (_tail == -1) {
		std::cout << "empty";
	}
	else {
		for (size_t i = 0; i <= _tail; ++i) {
			std::cout << values[i] << " ";
		}
	}
	std::cout << std::endl;
}

int main()
{
	Queue<int> Queue;
	Queue.CommandManager();
}
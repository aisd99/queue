#include <iostream>
#include <string>
#include <sstream>

#define _ERROR_ std::cout << "error" << std::endl;

using namespace std;
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
	int _capacity = 0;
	int _head = -1;
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
	bool notallocated = true;
	for (std::string line; std::getline(std::cin, line); ) {
		std::istringstream is(line);
		std::string command;
		is >> command;
		if (command.size() == 0) {
			continue;
		}
		if (command == "set_size") {
			notallocated = false;
			if (values == NULL) {
				int new_size;
				is >> new_size;
				std::string add;
				is >> add;
				if (add != "") _ERROR_
				else SetSize(new_size);
			}
			else _ERROR_
		}
		else if (!(notallocated)) {
			if (command == "push") {
				T new_item;
				is >> new_item;
				std::string add;
				is >> add;
				if (add != "") _ERROR_
				else Push(new_item);
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
		else _ERROR_
	}
}

template<typename T>
void Queue<T>::Push(const T& item)
{
	if ((_head == 0 && _tail == _capacity - 1) ||
		(_tail == (_head - 1) % (_capacity - 1)))
	{
		std::cout << "overflow" << std::endl;
		return;
	}

	else if (_head == -1)
	{
		_head = _tail = 0;
		values[_tail] = item;
	}

	else if (_tail == _capacity - 1 && _head != 0)
	{
		_tail = 0;
		values[_tail] = item;
	}

	else
	{
		_tail++;
		values[_tail] = item;
	}
}

template<typename T>
void Queue<T>::Pop()
{
	if (_head == -1)
	{
		std::cout << "underflow" << std::endl;
		return;
	}

	int data = values[_head];
	values[_head] = -1;
	if (_head == _tail)
	{
		_head = -1;
		_tail = -1;
	}
	else if (_head == _capacity - 1)
		_head = 0;
	else
		_head++;

	std::cout << data << std::endl;
}

template<typename T>
void Queue<T>::Print()
{
	if (_head == -1)
	{
		std::cout << "empty" << std::endl;
		return;
	}
	if (_tail >= _head)
	{
		for (int i = _head; i < _tail; i++) {
			std::cout << values[i] << " ";
		}
		std::cout << values[_tail] << std::endl;
	}
	else
	{
		for (int i = _head; i < _capacity; i++)
			std::cout << values[i] << " ";

		for (int i = 0; i < _tail; i++) {
			std::cout << values[i] << " ";
		}
		std::cout << values[_tail] << std::endl;
	}
}

template<typename T>
void Queue<T>::SetSize(size_t new_capacity) {
	values = new T[new_capacity];
	_capacity = new_capacity;
}

int main()
{
	Queue<int> Queue;
	Queue.CommandManager();
}

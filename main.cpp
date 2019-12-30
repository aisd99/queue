#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#define _ERROR_(os) os << "error" << std::endl;

using namespace std;
template<typename T>
class Queue {
public:
	Queue(ostream& _output);
	Queue(ostream& _output, size_t new_capacity);
	~Queue();

	void CommandManager(istream& input, ostream& output);
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
	ostream& output = std::cout;
};

template<typename T>
Queue<T>::Queue(ostream& _output) : output(_output) {}

template<typename T>
Queue<T>::Queue(ostream& _output, size_t new_capacity) : output(_output) {
	values = new T[new_capacity];
	_capacity = new_capacity;
}

template<typename T>
Queue<T>::~Queue() {
	delete[] values;
}

template<typename T>
void Queue<T>::CommandManager(istream& input, ostream& _output) {
	bool notallocated = true;
	for (std::string line; std::getline(input, line); ) {
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
				if (add != "") _ERROR_(output)
				else SetSize(new_size);
			}
			else _ERROR_(output)
		}
		else if (!(notallocated)) {
			if (command == "push") {
				T new_item;
				is >> new_item;
				std::string add;
				is >> add;
				if (add != "") _ERROR_(output)
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
					_ERROR_(output)
				}
			}
			else _ERROR_(output)
		}
		else _ERROR_(output)
	}
}

template<typename T>
void Queue<T>::CommandManager()
{
	CommandManager(std::cin, std::cout);
}

template<typename T>
void Queue<T>::Push(const T& item)
{
	if ((_head == 0 && _tail == _capacity - 1) ||
		(_tail == (_head - 1) % (_capacity - 1)))
	{
		output << "overflow" << std::endl;
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
		output << "underflow" << std::endl;
		return;
	}

	T data = values[_head];
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

	output << data << std::endl;
}

template<typename T>
void Queue<T>::Print()
{
	if (_head == -1)
	{
		output << "empty" << std::endl;
		return;
	}
	if (_tail >= _head)
	{
		for (int i = _head; i < _tail; i++) {
			output << values[i] << " ";
		}
		output << values[_tail] << std::endl;
	}
	else
	{
		for (int i = _head; i < _capacity; i++)
			output << values[i] << " ";

		for (int i = 0; i < _tail; i++) {
			output << values[i] << " ";
		}
		output << values[_tail] << std::endl;
	}
}

template<typename T>
void Queue<T>::SetSize(size_t new_capacity) {
	values = new T[new_capacity];
	_capacity = new_capacity;
}

int main()
{
	std::string buf;
	std::cin >> buf;
	ifstream in;
	in.open(buf, ios::in);
	std::cin >> buf;
	ofstream out;
	out.open(buf, ios::out);
	Queue<std::string> Queue(out);
	Queue.CommandManager(in, out);
	in.close();
	out.close();
}

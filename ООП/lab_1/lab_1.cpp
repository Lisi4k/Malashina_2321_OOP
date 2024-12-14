// lab_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
	Node() :top(nullptr) {}

	void push(const T& item) {
		Node* newNode = new Node(item, top);
		top = newNode;
	}

	T pop() {
		if (isEmpty()) {
			throw runtime_error("Стек пуст");
		}
		Node* temp = top;
		T item = temp->data;
		top = temp->next;
		delete temp;
		return item;
	}




private:
	struct Node {
		T data;
		Node* next;
		Node(const T& d, Node* n) : data(d), next(n) {}
	};
	Node* top;
};

int main()
{
	setlocale(LC_ALL, "ru");
	while (true) {
		cout << "\nВыберите операцию:\n";
		cout << "1. Добавить элемент\n";
		cout << "2. Удалить элемент\n";
		cout << "3. Изменить элемент\n";
		cout << "4. Подсчитать количество узлов\n";
		cout << "5. Вывести отсортированное дерево по возрастанию\n";
		cout << "6. Вывести отсортированное дерево по убыванию\n";
		cout << "7. Удалить все дерево\n";
		cout << "8. Выйти\n";
	}
	int choice;
	cin >>  choice;

	
}


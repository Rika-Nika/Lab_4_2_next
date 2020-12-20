#pragma once
#include"Exception.h"
#include <string>


template <class T>
class LinkedList
{
	struct node
	{
		T data;
		node* next;
	};
private:
	node* head, * tail;
	int size;
public:
	LinkedList()
	{
		head = NULL;
		tail = NULL;
		size = 0;
	}

	//Копировать элементы из переданного массива

	LinkedList(T* items, int count)
	{
		head = NULL;
		tail = NULL;
		size = 0;
		for (int i = 0; i < count; i++)
		{
			if (NULL == *(items + i)) {

			}
			this->add_node(*(items + i));
		}
	};

	//Копирующий конструктор

	LinkedList(const LinkedList<T>& list) {
		head = NULL;
		tail = NULL;
		size = 0;
		node* current = list.head;
		int count = 0;
		while (current != NULL)
		{
			add_node(current->data);
			count++;
			current = current->next;

		}


	};


	void add_node(T value)
	{
		node* tmp = new node;
		tmp->data = value;
		tmp->next = NULL;

		if (head == NULL)
		{
			head = tmp;
			tail = tmp;
		}
		else
		{
			tail->next = tmp;
			tail = tail->next;
		}
		size++;

	}

	node* GetHead()
	{
		return head;
	}

	node* GetTail()
	{
		return tail;
	}

	/*static void display(LinkedList :: head )
	{
		if (head == NULL)
		{
			std::cout << "NULL" << std::endl;
		}
		else
		{
			std::cout << head->data << std::endl;
			display(head->next);
		}
	}*/
	void printItem(int data) {
		std::cout << data << "\n";
	}
	void printItem(double data) {
		std::cout << data << "\n";
	}

	void printItem(std::string data) {
		std::cout << data << "\n";
	}
	void printList()
	{
		node* temp = this->head;
		while (temp != NULL)
		{
			printItem(temp->data);
			temp = temp->next;
		}
	}
	std::string printListOut()
	{
		std::wostringstream oss;
		node* temp = this->head;
		while (temp != NULL)
		{
			oss << temp->data << "\r\n"; 
			temp = temp->next;
		}
		return oss.str();
	}

	bool EqualsItem(int value1, int value2) {
		return value1 == value2;
	}
	bool EqualsItem(std::string value1, std::string value2) {
		return value1 == value2;
	}

	bool EqualsItem(double value1, double value2) {
		return value1 == value2;
	}

	void concatenate(node* a, node* b)
	{
		if (a != NULL && b != NULL)
		{
			if (a->next == NULL)
				a->next = b;
			else
				concatenate(a->next, b);
		}
		else
		{
			std::cout << "Either a or b is NULL\n";
		}
	}

	//index>0>getsize


	T GetNth(int index)
	{
		if (index < 0 || index >size - 1)
		{
			throw Exception("IndexOutOfRange");
		}
		node* current = head;
		int count = 0;
		while (current != NULL)
		{
			if (count == index)
				return(current->data);
			count++;
			current = current->next;
		}
		//	assert(0);
	}
	void SetNth(int index, T value)
	{
		if (index < 0 || index >size - 1)
		{
			throw Exception("IndexOutOfRange");
		}
		node* current = head;
		int count = 0;
		while (current != NULL)
		{
			if (count == index)
				current->data = value;
			count++;
			current = current->next;
		}
		//	assert(0);
	}



	T GetFirst()
	{
		if (size == 0)
		{
			throw Exception("IndexOutOfRange");
		}

		return this->head->data;

	}

	T GetLast()
	{
		if (size == 0)
		{
			throw Exception("IndexOutOfRange");
		}

		return this->tail->data;

	}

	T GetSize()
	{
		return size;
	}

	void Append(T value)
	{
		if (head == NULL)
		{
			add_node(value);
		}
		else
		{
			node* tmp = new node;
			tmp->data = value;
			tmp->next = head;
			head = tmp;
		}
		size++;
	}
	void Prepend(T value)
	{
		add_node(value);
	}


	void InsertAt(T value, int index)
	{
		if (index < 0 || index >size - 1)
		{
			throw Exception("IndexOutOfRange");
		}
		node* current = head;
		node* valueNode = new node;
		node* tmp = NULL;
		valueNode->data = value;
		int count = 0;
		while (current != NULL)
		{
			if (count == index - 1) {
				tmp = current;
			}
			if (count == index) {
				tmp->next = valueNode;
				valueNode->next = current;
				this->size++;
				break;
			}
			count++;
			current = current->next;
		}
	}

	LinkedList<T>* Concat(LinkedList<T>* list)
	{

		if (head == NULL)
		{
			head = list->GetHead();
		}
		else
		{
			tail->next = list->GetHead();

		}

		tail = list->GetTail();
		size += list->GetSize();
		return this;
	}

	LinkedList<T>* GetSubList(int startIndex, int endIndex)
	{
		node* current = head;
		int count = 0;

		LinkedList <T>* ls = new LinkedList <T>();
		if (startIndex < 0 || endIndex > size - 1 || endIndex < 0 || startIndex > endIndex)
		{
			throw Exception("IndexOutOfRange");
		}
		else {
			node* current = head;
			int count = 0;
			while (current != NULL)
			{
				if (count >= startIndex && count <= endIndex)
					ls->add_node(current->data);
				if (count == endIndex)
				{
					break;
				}
				count++;
				current = current->next;

			}
		}
		return ls;
	}
	bool Equals(LinkedList ls)
	{
		node* current = head;
		node* currentls = ls.GetHead();
		int count = 0;
		if (this->GetSize() != ls.GetSize())
		{
			return false;
		}
		else {
			node* current = head;
			int count = 0;
			while (current != NULL)
			{
				if (current->data != currentls->data)
				{
					return false;
				}
				count++;
				current = current->next;
				currentls = currentls->next;
			}
		}
		return true;
	}

	node* GetNext() {
		return node.next;

	}
	void RemoveAll()
	{
		head = NULL;
		tail = NULL;
		size = 0;
	}
	// Удаляет первое вхождение value
	void Remove(T value)
	{
		node* current = head;
		node* tmp = head;
		int count = 0;
		if(value == this->GetFirst()) {
			RemoveAt(0);
			return;
		}
		while (current != NULL)
		{
		
			if (current->data == value) {
				tmp->next = current->next;
				this->size--;
				break;
			}
			tmp = current;
			count++;
			current = current->next;
		}
	}
	void RemoveAt(const int index) {
		if (index < 0 || index >size - 1)
		{
			throw Exception("IndexOutOfRange");
		}
		if (index == 0) {
			head= head->next;
			this->size--;
			return;
		}

		node* current = head;
		node* tmp = NULL;
		int count = 0;
		while (current != NULL)
		{
			if (count == index - 1) {
				tmp = current;
			}
			if (count == index + 1) {
				tmp->next = current;

				this->size--;
				break;
			}
			count++;
			current = current->next;
		}
	};
};
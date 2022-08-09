#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include "MyException.h"
#include <exception>
using namespace std;

template <typename T>
class List {

private:

	int size; // ������ ���������
	int capacity; // ������� ���������
	T* Val; // ������ �������� 
	int* Next; // ������ ��������
	int free; // ������ ���������� ��������
	int head; // ������ ������� ��������

public:

	List() { // ����������� �� ���������
		size = 0;
		capacity = 1;
		Val = new T[capacity];
		Next = new int[capacity];
		for (int i = 0; i < capacity; i++) {
			Val[i] = NULL;
			Next[i] = NULL;
		}
		free = 0;
		head = 0;
	}

	List(int _size) { //����������� � ����������
		size = 0;
		capacity = _size;
		Val = new T[capacity];
		Next = new int[capacity];
		for (int i = 0; i < capacity; i++) {
			Val[i] = NULL;
			Next[i] = NULL;
		}
		free = 0;
		head = 0;
	}

	 List(const List<T>& _list) { //����������� �����������
	 	size = _list.size;
	 	capacity = _list.capacity;
	 	Val = new T[capacity];
	 	Next = new int[capacity];
	 	memcpy(Val, _list.Val, capacity * sizeof(int)); 
	 	memcpy(Next, _list.Next, capacity * sizeof(int));
	 	free = _list.free;
	 	head = _list.head;
	 }

	~List() { //����������
		delete this->Val;
		delete this->Next;
	}

	int get_size() { // ����� ������� ������
		return size;
	}

	int get_capacity() { // ������ �������
		return capacity;
	}

	void remove_list() { // �������� ������ clear
		for (int i = 0; i < capacity; i++) {
			Val[i] = NULL;
			Next[i] = NULL;
		}
		size = 0;
		free = 0;
		head = 0;
	}

	bool push_back(T _item) { // ��������� ������ ��������
		int next_free;
		if (size == capacity) {
			return false;
		}
		Val[free] = _item;
		if (free != head) {
			int i = head;
			while (1) {
				if (Next[i] == -1) {
					Next[i] = free;
					break;
				}
				i = Next[i];
			}
		}
		if (Next[free] != NULL) {
			next_free = Next[free];
		}
		else {
			next_free = free + 1;
		}
		Next[free] = -1;
		free = next_free;
		size++;
		return true;
	}

	bool insert(T _item, int _pos) { // ��������� ������ �������� � ������� � �������� �������
		int next_free;
		if (_pos < 0 || size == capacity || _pos > size) {
			return false;
		} else {
			int cnt = 0, i = head;
			if (_pos != 0) {
				while (cnt + 1 != _pos) {
					i = Next[i];
					cnt++;
				}
			}
			if (Next[free] != NULL) {
				next_free = Next[free];
			}
			else {
				next_free = free + 1;
			}
			Val[free] = _item;
			if (_pos == 0) {
				if (is_empty()) {
					Next[free] = -1;
				}
				else {
					Next[free] = i;
				}
				head = free;
			}
			else {
				Next[free] = Next[i];
				Next[i] = free;
			}
			free = next_free;
			size++;
		}
		return true;
	}

	bool remove_item(T _item) { // �������� ��������� �������� �� ������
		bool result = false;
		int pred = head, cnt = 0, i = head;
		while (cnt != size) {
			if (Val[i] == _item) {
				result = true;
				break;
			}
			if (cnt > 0) {
				pred = i;
			}
			i = Next[i];
			cnt++;
		}
		if (result == true) {
			Val[i] = NULL;
			if (head == i) {
				head = (Next[i] == -1) ? i : Next[i];
			}
			else {
				Next[pred] = (Next[i] == -1) ? -1 : Next[i];
			}
			Next[i] = free;
			free = i;
			size--;
		}
		else {
			result = false;
		}
		return result;
	}

	bool remove(int _pos) { // �������� �������� �� ������� � �������� �������
		if (_pos < 0 || _pos >= size) {
			return false;
		}
		int pred = head, cnt = 0, i = head;
		while (cnt != _pos) {
			if (cnt > 0) {
				pred = i;
			}
			i = Next[i];
			cnt++;
		}
		if (head == i) {
			head = (Next[i] == -1) ? i : Next[i];
		}
		else {
			Next[pred] = (Next[i] == -1) ? -1 : Next[i];
		}
		Val[i] = NULL;
		Next[i] = free;
		free = i;
		size--;
		return true;
	}

	bool is_empty() { // �������� �� �������
		return (Val[head] == NULL) ? true : false;
	}

	bool is_contains(T _item) { // ����� ������� ��������� ��������
		int cnt = 0, i = head;
		while (cnt != size) {
			if (Val[i] == _item) {
				return true;
			}
			i = Next[i];
			cnt++;
		}
		return false;
	}

	bool change(T _item, int _pos) { // ��������� �������� � �������� ������� � ������
		if (_pos < 0 || _pos >= size) {
			return false;
		}
		int cnt = 0, i = head;
		if (_pos == 0) {
			Val[i] = _item;
		}
		else {
			while (cnt != _pos) {
				i = Next[i];
				if (cnt + 1 == _pos) {
					Val[i] = _item;
				}
				cnt++;
			}
		}
		return true;
	}

	int get_pos(T _item) { // ��������� ������� � ������ ��� ��������� ��������
		bool result = false;
		int cnt = 0, i = head;
		while (cnt != size) {
			if (Val[i] == _item) {
				result = true;
				break;
			}
			i = Next[i];
			cnt++;
		}
		if (result == false) {
			throw MyException("\n����������\n");
		}
		return cnt;
	}

	T get_value(int _pos) { // ������ �������� � �������� ������� � ������
		int cnt = 0, i = head;
		if (_pos < 0 || _pos >= size) {
			throw MyException("\n����������\n");
		}
		while (cnt != size) {
			if (cnt == _pos) {
				break;
			}
			i = Next[i];
			cnt++;
		}
		return Val[i];
	}

	void print() { // ����� ��������� ������ �� �����
		if (Val[head] == NULL) {
			;
		}
		else {
			int temp = 0, cnt = 0, i = head;
			while (i != -1) {
				cout << Val[i] << " ";
				temp = Next[i];
				i = temp;
				cnt++;
			}
			cout << endl;
		}
	}

	class Iterator {

	private:

		int cur; // ������ �������� ��������
		List* L;

	public:
		friend class List;

		Iterator(List* LL) { //����������� � �����������
			L = LL;
			cur = LL->head;
		}

		void operator++ () { //�������� ���������� ��� �������� � ���������� �������� � ������ ++
			if (cur != -1)
			cur = L->Next[cur];
		}

		bool operator!= (const Iterator& other_it) { return (cur != other_it.cur && L != other_it.L); } //�������� ����������� ���������� ���������� !=

		bool operator== (const Iterator& other_it) { return (cur == other_it.cur && L == other_it.L); } //�������� ��������� ���������� ���������� ==

		T& operator* () { //�������� ������� �� ������ � ������ � �������� �������� *
			if (cur != -1) {
				return L->Val[cur];
			}
			throw MyException("����������");
		}
	};

	Iterator begin() { // �������� ������� ��������� begin()
		Iterator A(this);
		return A;
	}

	Iterator end() { // ������ "����������������" ������� ��������� end()
		Iterator A(this);
		A.cur = -1;
		return A;
	}
};
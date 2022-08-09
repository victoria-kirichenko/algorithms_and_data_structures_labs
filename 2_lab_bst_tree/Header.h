#pragma once
#include <iostream>
#include <string>
using namespace std;

template <typename T, typename G>
class Tree
{
private:
	class Node
	{
	public:
		T data;
		G key;
		Node* left = nullptr;
		Node* right = nullptr;
		int num = 1; // вес
		Node(G ke, T dat) {
			data = dat;
			key = ke;
		}
	};
	int size = 0;
	Node* root = nullptr;
	int counter = 0; // для тестов
public:
	Tree() {}; // конструктор по умолчанию
	~Tree(); // деструктор
	Tree(const Tree& copytree); // конструктор копирования
	int get_size(); //опрос размера дерева
	void clear_tree(); //очистка дерева
	bool empty_check(); //проверка дерева на пустоту
	T& get_data(G ke); //доступ по чтению/записи к данным по ключу
	bool add(G ke, T value); //включение данных с заданным ключом
	bool del(G ke); //удаление данных с заданным ключом
	void print();//вывод ключей дерева + вспомогательный параметр
	void lists(); //формирование списка ключей в дереве в порядке обхода узлов по схеме t->Lt->Rt
	int get_num(G ke);// (доп функция) определение порядкового номера для элемента с заданным ключом
	int get_counter();//доп. операция получение числа элементов, просмотренных предыдущей операцией 
	class Iterator
	{
	private:
		Tree* tree;
		Node* cur = nullptr;
	public:
		Iterator();
		Iterator(Tree* tr, Node* c);
		Iterator(const Iterator& copyiterator);
		bool operator!=(const Iterator& other);
		bool operator==(const Iterator& other);
		Iterator& operator ++() {
			if (this->cur == nullptr) throw exception("");
			if ((this->cur)->right != nullptr) {
				this->cur = minim((this->cur)->right);
			}
			else {
				this->cur = L_parent(tree->root, this->cur);
			}

		}
		Iterator& operator --() {
			if (this->cur == nullptr) throw exception("");
			if ((this->cur)->left != nullptr) {
				this->cur = maxim((this->cur)->left);
			}
			else {
				this->cur = R_parent(tree->root, this->cur);
			}
		}
		T& operator *() {
			if (this->cur == nullptr) throw exception("");
			return (this->cur)->data;
		}
	private: //вспомогательные методы прямого итератора
		Node* L_parent(Node* t, Node* x) {
			if (t == x) {
				return nullptr;
			}
			if (x->key < t->key) {
				Node* rp = L_parent(t->left, x);
				if (rp != nullptr) {
					return rp;
				}
				else return t;
			}
			else return L_parent(t->right, x);
		}
		Node* R_parent(Node* t, Node* x) {
			if (t == x) {
				return nullptr;
			}
			if (x->key > t->key) {
				Node* rp = R_parent(t->right, x);
				if (rp != nullptr) {
					return rp;
				}
				else return t;
			}
			else return R_parent(t->left, x);
		}
		Node* minim(Node* t) {
			if (t == nullptr) {
				return nullptr;
			}
			while (t->left != nullptr) {
				t = t->left;
			}
			return t;
		}
		Node* maxim(Node* t) {
			if (t == nullptr) {
				return nullptr;
			}
			while (t->right != nullptr) {
				t = t->right;
			}
			return t;
		}
	};
	class R_iterator
	{
	private:
		Tree* tree;
		Node* cur = nullptr;
	public:
		R_iterator();
		R_iterator(Tree* tr, Node* c);
		R_iterator(const R_iterator& copyiterator);
		bool operator!=(const R_iterator& other);
		bool operator==(const R_iterator& other);
		R_iterator& operator ++() {
			if (this->cur == nullptr) throw exception("");
			if ((this->cur)->left != nullptr) {
				this->cur = maxim((this->cur)->left);
			}
			else {
				this->cur = R_parent(tree->root, this->cur);
			}

		}
		R_iterator& operator --() {
			if (this->cur == nullptr) throw exception("");
			if ((this->cur)->right != nullptr) {
				this->cur = minim((this->cur)->right);
			}
			else {
				this->cur = L_parent(tree->root, this->cur);
			}
		}
		T& operator *() {
			if (this->cur == nullptr) throw exception("");
			return (this->cur)->data;
		}

	private: //вспомогательные методы обратного итератора

		Node* L_parent(Node* t, Node* x) {
			if (t == x) {
				return nullptr;
			}
			if (x->key < t->key) {
				Node* rp = L_parent(t->left, x);
				if (rp != nullptr) {
					return rp;
				}
				else return t;
			}
			else return L_parent(t->right, x);
		}
		Node* R_parent(Node* t, Node* x) {
			if (t == x) {
				return nullptr;
			}
			if (x->key > t->key) {
				Node* rp = R_parent(t->right, x);
				if (rp != nullptr) {
					return rp;
				}
				else return t;
			}
			else return R_parent(t->left, x);
		}
		Node* minim(Node* t) {
			if (t == nullptr) {
				return nullptr;
			}
			while (t->left != nullptr) {
				t = t->left;
			}
			return t;
		}
		Node* maxim(Node* t) {
			if (t == nullptr) {
				return nullptr;
			}
			while (t->right != nullptr) {
				t = t->right;
			}
			return t;
		}

	};

	friend class Iterator;
	friend class R_iterator;

	R_iterator rbegin() {
		Node* t = this->root;
		if (t == nullptr) {
			R_iterator iter(this, t);
			return iter;
		}
		while (t->right != nullptr) {
			t = t->right;
		}
		R_iterator iter(this, t);
		return iter;
	};

	R_iterator rend() {
		R_iterator iter(this, nullptr);
		return iter;
	};

	Iterator begin() {
		Node* t = this->root;
		if (t == nullptr) {
			Iterator iter(this, t);
			return iter;
		}
		while (t->left != nullptr) {
			t = t->left;
		}
		Iterator iter(this, t);
		return iter;
	};
	Iterator end() {
		Iterator iter(this, nullptr);
		return iter;
	};


private: //вспомогательные функции для рекурсии

	Node* radd(Node* t, G ke, T value, bool& inserted) { //вспомогательная функция добавления элементов
		if (t == nullptr) {
			inserted = true;
			counter++;
			return new Node(ke, value);
		}
		counter++;
		if (ke == t->key) {
			inserted = false;
			return t;
		}
		if (ke < t->key) {
			t->left = radd(t->left, ke, value, inserted);
		}
		else {
			t->right = radd(t->right, ke, value, inserted);
		}
		if (inserted) {
			(t->num)++;
		}
		return t;
	}

	Node* rdel(Node* t, G ke, bool& deleted) { //вспомогательная функция удаления элементов
		if (t == nullptr) {
			deleted = false;
			return t;
		}
		counter++;
		if (ke < t->key) {
			t->left = rdel(t->left, ke, deleted);
			if (deleted) {
				(t->num)--;
			}
			return t;
		}
		if (ke > t->key) {
			t->right = rdel(t->right, ke, deleted);
			if (deleted) {
				(t->num)--;
			}
			return t;
		}
		deleted = true;
		if (t->left == nullptr && t->right == nullptr) {
			delete t;
			return nullptr;
		}
		if (t->left == nullptr) {
			Node* x = t->right;
			delete t;
			return x;
		}
		if (t->right == nullptr) {
			Node* x = t->left;
			delete t;
			return x;
		}
		t->right = rdelete(t->right, t);
		(t->num)--;
		return t;
	}

	Node* rdelete(Node* t, Node* t0) { //вспомогательная функция удаления элементов
		counter++;
		if (t->left != nullptr) {
			t->left = rdelete(t->left, t0);
			(t->num)--;
			return t;
		}
		t0->key = t->key;
		t0->data = t->data;
		Node* x = t->right;
		delete t;
		return x;
	}

	T& search(Node* t, G k) {
		if (t == nullptr) {
			throw exception("");
		}
		counter++;
		if (k == t->key) {
			return (t->data);
		}
		if (k < t->key) {
			return search(t->left, k);
		}
		else {
			return search(t->right, k);
		}
	}

	int obhod(Node* t) {
		if (t == nullptr) {
			return 0;
		}
		counter++;
		cout << t->key << " ";
		obhod(t->left);
		obhod(t->right);
		return 0;
	}

	int deleted(Node* t) {
		if (t == nullptr) {
			return 0;
		}
		counter++;
		deleted(t->left);
		deleted(t->right);
		delete t;
		return 0;
	}

	int show_k(Node* t, int level) {
		if (t == nullptr) {
			return 0;
		}
		show_k(t->right, level + 1);
		for (int i = 0; i < (3 * level); i++) {
			cout << " ";
		}
		cout << t->key << "(" << t->num << ")" << endl;
		show_k(t->left, level + 1);
		return 0;
	}

};

template <typename T, typename G>
Tree<T, G>::Tree(const Tree& copytree)
{
	this->size = copytree.size;
	this->root = copytree.root;
}

template <typename T, typename G>
Tree<T, G>::~Tree()
{
	this->clear_tree();
}

template <typename T, typename G>
int Tree<T, G>::get_size() // опрос размера списка
{
	return size;
}
template <typename T, typename G>
int Tree<T, G>::get_counter() // число просмотренных элементов в списке (предыдущ. операцией)
{
	return counter;
}

template <typename T, typename G>
void Tree<T, G>::clear_tree() // очистка дерева
{
	deleted(root);
	size = 0;
	root = nullptr;
}

template <typename T, typename G>
bool Tree<T, G>::empty_check() //проверка дерева на пустоту
{
	if (size == 0) return true;
	else return false;
}

template <typename T, typename G>
bool Tree<T, G>::add(G ke, T value) //добавление элемента с заданным ключом
{
	if (root == nullptr) {
		root = new Node(ke, value);
		size++;
		return true;
	}
	counter = 0;
	bool inserted;
	radd(root, ke, value, inserted);
	if (inserted) {
		size++;
	}
	return inserted;
}

template <typename T, typename G>
bool Tree<T, G>::del(G ke) //удаление элемента с заданным ключом
{
	counter = 0;
	if (root->key == ke) {
		if (root->left == nullptr) {
			counter++;
			Node* x = root;
			root = root->right;
			delete x;
			size--;
			return true;
		}
		if (root->right == nullptr) {
			counter++;
			Node* x = root;
			root = root->left;
			delete x;
			size--;
			return true;
		}
	}
	bool deleted;
	rdel(root, ke, deleted);
	if (deleted) {
		size--;
	}
	return deleted;
}

template <typename T, typename G>
T& Tree<T, G>::get_data(G ke) //поиск элемента (чтение)
{
	counter = 0;
	return search(root, ke);
}

template <typename T, typename G>
int Tree<T, G>::get_num(G ke) //порядковый номер элемента по ключу при симметричном обходе
{
	counter = 0;
	int numb = 0;
	Node* t = root;
	while (t != nullptr) {
		counter++;
		if (t->key == ke) {
			if (t->left != nullptr) {
				numb = numb + (t->left)->num + 1;
			}
			else {
				numb++;
			}
			return numb;
		}
		if (t->key > ke) {
			t = t->left;
		}
		else {
			numb = numb + (t->left)->num + 1;
			t = t->right;
		}
	}
	throw exception("");
}

template <typename T, typename G>
void Tree<T, G>::lists() // обхода узлов дерева в виде списка по схеме t->Lt->Rt
{
	counter = 0;
	obhod(root);
}

template <typename T, typename G>
void Tree<T, G>::print() // вывод ключей дерева + вспомогательный параметр
{
	show_k(root, 1);
}

template <typename T, typename G>
Tree<T, G>::Iterator::Iterator(Tree<T, G>* tr, Node* c)
{
	cur = c;
	tree = tr;
}

template <typename T, typename G>
Tree<T, G>::Iterator::Iterator(const Iterator& copyiterator)
{
	this->cur = copyiterator.cur;
	this->tree = copyiterator.tree;
}

template <typename T, typename G>
bool Tree<T, G>::Iterator::operator!=(const Iterator& other) {
	if (this->cur != other.cur || this->tree != other.tree) return true;
	else return false;
}

template <typename T, typename G>
bool Tree<T, G>::Iterator::operator==(const Iterator& other) {
	if (this->cur == other.cur && this->tree == other.tree) return true;
	else return false;
}

template <typename T, typename G>
Tree<T, G>::R_iterator::R_iterator(Tree<T, G>* tr, Node* c)
{
	cur = c;
	tree = tr;

}

template <typename T, typename G>
Tree<T, G>::R_iterator::R_iterator(const R_iterator& copyiterator)
{
	this->cur = copyiterator.cur;
	this->tree = copyiterator.tree;
}

template <typename T, typename G>
bool Tree<T, G>::R_iterator::operator!=(const R_iterator& other) {
	if (this->cur != other.cur || this->tree != other.tree) return true;
	else return false;
}

template <typename T, typename G>
bool Tree<T, G>::R_iterator::operator==(const R_iterator& other) {
	if (this->cur == other.cur && this->tree == other.tree) return true;
	else return false;
}

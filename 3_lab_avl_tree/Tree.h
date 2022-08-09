#pragma once
#include <iostream>
#include <exception>
using namespace std;

//T - тип ключа дерева
//U - тип данных дерева
template <typename T, typename U>
class Tree
{

protected:

	class Node;
	Node* _root;
	int _size;
	double _count; //количество опрошенных узлов дерева

public:

	class Iterator; //класс прямого итератора
	friend class Iterator;
	class ReverseIterator; //класс обратного итератора
	friend class ReverseIterator;

	Tree(); //класс обратного итератора
	Tree(const Tree& tree); //конструктор копирования
	virtual ~Tree(); //деструктор
	int getSize(); //опрос размера дерева
	int getNodeCount(); //получение количества узлов, пройденных последней операцией
	U& getDataByKey(T key); //получение ссылки на данные по ключу
	virtual bool add(T key, U data); //вставка по ключу
	virtual bool erase(T key); //удаление по ключу
	void clear(); //очистка дерева
	virtual void show(); //вывод в консоль
	void showKeys(); //вывод в консоль списка ключей
	bool isClear(); //проверка дерева на пустоту

	Iterator begin(); //получение начального прямого итератора доступа
	Iterator end(); //получение конечного прямого итератора доступа
	ReverseIterator rBegin(); //получение начального обратного итератора доступа
	ReverseIterator rEnd(); //получение конечного обратного итератора доступа

};

//конструктор по умолчанию
template<typename T, typename U>
Tree<T, U>::Tree()
{
	//зануляем поля
	_root = nullptr;
	_size = 0;
	_count = 0;
}

//конструктор копирования
template<typename T, typename U>
Tree<T, U>::Tree(const Tree& tree)
{
	_root = new Node(*(tree._root));
	_size = tree._size;
	_count = tree._count;
}

//деструктор
template<typename T, typename U>
Tree<T, U>::~Tree()
{
	delete _root;
}



//получение размера дерева
template<typename T, typename U>
int Tree<T, U>::getSize()
{
	return _size;
}

//получение количества узлов, пройденных последней операцией
template<typename T, typename U>
int Tree<T, U>::getNodeCount()
{
	return _count;
}

//получение ссылки на данные по ключу
template<typename T, typename U>
U& Tree<T, U>::getDataByKey(T key)
{
	if (!_root)
		throw exception("Неверный ключ!");

	_count = 0;
	return _root->getDataByKey(key, _count);
}



//вставка по ключу
template<typename T, typename U>
bool Tree<T, U>::add(T key, U data)
{
	_count = 1;

	if (_root)

		if (_root->add(key, data, _count))
		{
			_size++;
			return true;
		}
		else
			return false;
	else
	{
		_root = new Node(key, data);
		_size++;
		return true;
	}
}

//удаление по ключу
template<typename T, typename U>
bool Tree<T, U>::erase(T key)
{
	_count = 1;

	Tree<T, U>::Node* p;

	if (_root)
		if (key == _root->_key)
		{
			p = _root;

			if (!p->_left && !p->_right)
			{
				_root = nullptr;
				delete p;

				_size--;

				return true;
			}

			if (p->_left && !p->_right)
			{
				p->_left->_parent = nullptr;
				_root = p->_left;

				p->_left = nullptr;
				delete p;

				_size--;

				return true;
			}

			if (!p->_left && p->_right)
			{
				p->_right->_parent = nullptr;
				_root = p->_right;

				p->_right = nullptr;
				delete p;

				_size--;

				return true;
			}

			//если у удаляемого узла обе ветви
			if (p->_left && p->_right)
			{
				Node* p2 = p->_right;

				while (p2->_left)
					p2 = p2->_left;

				T nodeKey = p2->_key;
				U nodeData = p2->_data;
				_root->erase(nodeKey, _count);

				p->_key = nodeKey;
				p->_data = nodeData;
				_size--;

				return true;
			}
		}
		else
			if (_root->erase(key, _count))
			{
				_size--;

				return true;
			}
			else
				return false;

	return false;
}

//очистка дерева
template<typename T, typename U>
void Tree<T, U>::clear()
{
	delete _root;
	_root = nullptr;
	_size = 0;
}



//вывод в консоль
template<typename T, typename U>
void Tree<T, U>::show()
{
	cout << "Размер дерева: " << _size << endl;
	if (_root)
		_root->show(0);
}

//вывод ключей дерева
template<typename T, typename U>
void Tree<T, U>::showKeys()
{
	cout << "Ключи дерева: " << endl;
	if (_root)
		_root->showKeys();
}

//проверка дерева на пустоту
template<typename T, typename U>
bool Tree<T, U>::isClear()
{
	return (_root == nullptr);
}


// Класс узла
template <typename T, typename U>
class Tree<T, U>::Node
{
protected:

	friend class Tree<T, U>;

	T _key;
	U _data;
	Node* _left, * _right, * _parent;

public:

	friend class Tree<T, U>::Iterator;
	friend class Tree<T, U>::ReverseIterator;

	Node(); //конструктор по умолчанию
	Node(T key, U data); //конструктор с параметрами
	Node(const Tree<T, U>::Node& node); //конструктор копирования
	virtual ~Node(); //деструктор
	U& getDataByKey(T key, double& count); //получение ссылки на данные по ключу
	virtual bool add(T key, U data, double& count); //вставка по ключу
	virtual bool erase(T key, double& count); //удаление по ключу
	virtual void show(int level); //вывод в консоль
	void showKeys(); //вывод ключей в консоль

};

template <typename T, typename U>
Tree<T, U>::Node::Node() : _key(), _data()
{
	_left = nullptr;
	_right = nullptr;
	_parent = nullptr;
}

//конструктор с параметрами
template <typename T, typename U>
Tree<T, U>::Node::Node(T key, U data) : _key(key), _data(data)
{
	_left = nullptr;
	_right = nullptr;
	_parent = nullptr;
}

//конструктор копирования
template <typename T, typename U>
Tree<T, U>::Node::Node(const Tree<T, U>::Node& node) : _key(node._key), _data(node._data)
{
	if (node._left)
	{
		_left = new Tree<T, U>::Node(*(node._left));
		_left->_parent = this;
	}
	else
		_left = nullptr;

	if (node._right)
	{
		_right = new Tree<T, U>::Node(*(node._right));
		_right->_parent = this;
	}
	else
		_right = nullptr;

	_parent = nullptr;
}

//деструктор
template <typename T, typename U>
Tree<T, U>::Node::~Node()
{
	delete _left;
	delete _right;
}



//получение ссылки на данные по ключу
template <typename T, typename U>
U& Tree<T, U>::Node::getDataByKey(T key, double& count)
{
	count++;

	if (_key == key)
		return _data;

	if (key < _key)
		if (_left)
			return _left->getDataByKey(key, count);
		else
			throw exception("Неверный ключ!");
	else
		if (_right)
			return _right->getDataByKey(key, count);
		else
			throw exception("Неверный ключ!");
}



//вставка по ключу
template <typename T, typename U>
bool Tree<T, U>::Node::add(T key, U data, double& count)
{
	count++;

	if (key == _key)
		return false;

	if (key < _key)
		if (_left)
			return _left->add(key, data, count);
		else
		{
			_left = new Tree<T, U>::Node(key, data);
			_left->_parent = this;

			return true;
		}
	else
		if (_right)
			return _right->add(key, data, count);
		else
		{
			_right = new Tree<T, U>::Node(key, data);
			_right->_parent = this;

			return true;
		}
}

//удаление по ключу
template <typename T, typename U>
bool Tree<T, U>::Node::erase(T key, double& count)
{
	count++;

	Node* p;

	if (_left && (_left->_key == key))
	{
		p = _left;

		if (!p->_left && !p->_right)
		{
			_left = nullptr;
			delete p;

			return true;
		}

		if (p->_left && !p->_right)
		{
			p->_left->_parent = this;
			_left = p->_left;

			p->_left = nullptr;
			delete p;

			return true;
		}

		if (!p->_left && p->_right)
		{
			p->_right->_parent = this;
			_left = p->_right;

			p->_right = nullptr;
			delete p;

			return true;
		}

		if (p->_left && p->_right)
		{
			Node* p2 = p->_right;

			while (p2->_left)
				p2 = p2->_left;

			T nodeKey = p2->_key;
			U nodeData = p2->_data;
			erase(nodeKey, count);

			p->_key = nodeKey;
			p->_data = nodeData;

			return true;
		}
	}

	if (_right && (_right->_key == key))
	{
		p = _right;

		if (!p->_left && !p->_right)
		{
			_right = nullptr;
			delete p;

			return true;
		}

		if (p->_left && !p->_right)
		{
			p->_left->_parent = this;
			_right = p->_left;

			p->_left = nullptr;
			delete p;

			return true;
		}

		if (!p->_left && p->_right)
		{
			p->_right->_parent = this;
			_right = p->_right;

			p->_right = nullptr;
			delete p;

			return true;
		}

		if (p->_left && p->_right)
		{
			Node* p2 = p->_right;

			while (p2->_left)
				p2 = p2->_left;

			T nodeKey = p2->_key;
			U nodeData = p2->_data;
			erase(nodeKey, count);

			p->_key = nodeKey;
			p->_data = nodeData;

			return true;
		}

	}

	if (key < _key)
		if (_left)
			return _left->erase(key, count);
		else
			return false;
	else
		if (_right)
			return _right->erase(key, count);
		else
			return false;
}



//вывод в консоль
template <typename T, typename U>
void Tree<T, U>::Node::show(int level)
{
	if (_right)
		_right->show(level + 1);

	for (int i = 0; i < 3 * level; i++)
		cout << " ";

	cout << _key << "(" << _data << ")" << endl;

	if (_left)
		_left->show(level + 1);
}

//вывод ключей в консоль
template <typename T, typename U>
void Tree<T, U>::Node::showKeys()
{
	cout << _key << endl;
	if (_left)
		_left->showKeys();

	if (_right)
		_right->showKeys();

}

template <typename T, typename U>
class Tree<T, U>::Iterator
{
private:

	friend class Tree<T, U>;

	Node* _current; //указатель на текущий узел дерева

public:

	friend class Tree<T, U>::ReverseIterator;

	Iterator(); //конструктор по умолчанию
	Iterator(const Iterator& iterator); //конструктор копирования

	Iterator& operator++(); //оператор инкремента
	Iterator& operator--(); //оператор декремента
	Iterator& operator=(const Iterator& iterator); //оператор присваивания
	Iterator& operator=(const ReverseIterator& iterator); //оператор присваивания
	U& operator*(); //оператор разыменования
	bool operator==(const Iterator& iterator); //оператор сравнения на равенство
	bool operator==(const ReverseIterator& iterator); //оператор сравнения на равенство
	bool operator!=(const Iterator& iterator); //оператор сравнения на неравенство
	bool operator!=(const ReverseIterator& iterator); //оператор сравнения на неравенство

};


template <typename T, typename U> //конструктор по умолчанию
Tree<T, U>::Iterator::Iterator()
{
	_current = nullptr;
}

template <typename T, typename U> //конструктор копирования
Tree<T, U>::Iterator::Iterator(const Iterator& iterator)
{
	_current = iterator._current;
}


//оператор инкремента
template <typename T, typename U>
typename Tree<T, U>::Iterator& Tree<T, U>::Iterator::operator++()
{

	if (!_current)
		throw exception("Итератор не установлен!");

	Node* p = _current;

	if (p->_right)
	{
		p = p->_right;

		while (p->_left)
			p = p->_left;

		_current = p;

		return *this;
	}


	while (true)
	{
		if (!p->_parent)
		{
			_current = nullptr;
			return *this;
		}

		if (p->_parent->_left == p)
		{
			_current = p->_parent;
			return *this;
		}
		p = p->_parent;
	}
	return *this;
}


template <typename T, typename U> //оператор декремента
typename Tree<T, U>::Iterator& Tree<T, U>::Iterator::operator--()
{
	if (!_current)
		throw exception("Итератор не установлен!");

	Node* p = _current;

	if (p->_left)
	{
		p = p->_left;
		while (p->_right)
			p = p->_right;

		_current = p;
		return *this;
	}


	while (true)
	{
		if (!p->_parent)
		{
			_current = nullptr;
			return *this;
		}

		if (p->_parent->_right == p)
		{
			_current = p->_parent;
			return *this;
		}

		p = p->_parent;
	}
	return *this;
}


template <typename T, typename U> //оператора присваивания
typename Tree<T, U>::Iterator& Tree<T, U>::Iterator::operator=(const Tree<T, U>::Iterator& iterator)
{
	_current = iterator._current;

	return *this;
}

template <typename T, typename U> //оператора присваивания
typename Tree<T, U>::Iterator& Tree<T, U>::Iterator::operator=(const Tree<T, U>::ReverseIterator& iterator)
{
	_current = iterator._current;

	return *this;
}

template <typename T, typename U> //оператор разыменования
U& Tree<T, U>::Iterator::operator*()
{
	if (!_current)
		throw exception("Итератор не установлен!");

	return _current->_data;
}



//операторы сравнения
template <typename T, typename U>
bool Tree<T, U>::Iterator::operator==(const Tree<T, U>::Iterator& iterator)
{
	return (_current == iterator._current);
}

template <typename T, typename U>
bool Tree<T, U>::Iterator::operator==(const Tree<T, U>::ReverseIterator& iterator)
{
	return (_current == iterator._current);
}

template <typename T, typename U>
bool Tree<T, U>::Iterator::operator!=(const Tree<T, U>::Iterator& iterator)
{
	return (_current != iterator._current);
}

template <typename T, typename U>
bool Tree<T, U>::Iterator::operator!=(const Tree<T, U>::ReverseIterator& iterator)
{
	return (_current != iterator._current);
}


template<typename T, typename U> //получение начального прямого итератора
typename Tree<T, U>::Iterator Tree<T, U>::begin()
{
	Tree<T, U>::Node* p = _root;

	if (p)
		while (p->_left)
			p = p->_left;

	Tree<T, U>::Iterator iterator;
	iterator._current = p;

	return iterator;
}


template<typename T, typename U> //получение конечного прямого итератора
typename Tree<T, U>::Iterator Tree<T, U>::end()
{
	return Iterator();
}


template <typename T, typename U>
class Tree<T, U>::ReverseIterator
{
private:

	friend class Tree<T, U>;
	Node* _current; //указатель на текущий узел дерева

public:

	friend class Tree<T, U>::Iterator;


	ReverseIterator(); //конструктор по умолчанию
	ReverseIterator(const ReverseIterator& iterator); //конструктор копирования

	ReverseIterator& operator++(); //оператор инкремента
	ReverseIterator& operator--(); //оператор декремента
	ReverseIterator& operator=(const ReverseIterator& iterator); //оператор присваивания
	ReverseIterator& operator=(const Iterator& iterator); //оператор присваивания
	U& operator*(); //оператор разыменования
	bool operator==(const ReverseIterator& iterator); //оператор сравнения на равенство
	bool operator==(const Iterator& iterator); //оператор сравнения на равенство
	bool operator!=(const ReverseIterator& iterator); //оператор сравнения на неравенство
	bool operator!=(const Iterator& iterator); //оператор сравнения на неравенство

};


template <typename T, typename U> //конструктор по умолчанию
Tree<T, U>::ReverseIterator::ReverseIterator()
{
	_current = nullptr;
}


template <typename T, typename U> //конструктор копирования
Tree<T, U>::ReverseIterator::ReverseIterator(const ReverseIterator& iterator)
{
	_current = iterator._current;
}


template <typename T, typename U> //оператор инкремента
typename Tree<T, U>::ReverseIterator& Tree<T, U>::ReverseIterator::operator++()
{
	if (!_current)
		throw exception("Итератор не установлен!");

	Node* p = _current;

	if (p->_left)
	{
		p = p->_left;

		while (p->_right)
			p = p->_right;

		_current = p;

		return *this;
	}

	while (true)
	{
		if (!p->_parent)
		{
			_current = nullptr;
			return *this;
		}

		if (p->_parent->_right == p)
		{
			_current = p->_parent;
			return *this;
		}
		p = p->_parent;
	}
	return *this;
}


template <typename T, typename U> //оператор декремента
typename Tree<T, U>::ReverseIterator& Tree<T, U>::ReverseIterator::operator--()
{

	if (!_current)
		throw exception("Итератор не установлен!");

	Node* p = _current;

	if (p->_right)
	{
		p = p->_right;

		while (p->_left)
			p = p->_left;

		_current = p;

		return *this;
	}

	while (true)
	{
		if (!p->_parent)
		{
			_current = nullptr;
			return *this;
		}

		if (p->_parent->_left == p)
		{
			_current = p->_parent;
			return *this;
		}
		p = p->_parent;
	}
	return *this;
}


//оператор присваивания
template <typename T, typename U>
typename Tree<T, U>::ReverseIterator& Tree<T, U>::ReverseIterator::operator=(const Tree<T, U>::ReverseIterator& iterator)
{
	_current = iterator._current;

	return *this;
}

template <typename T, typename U>
typename Tree<T, U>::ReverseIterator& Tree<T, U>::ReverseIterator::operator=(const Tree<T, U>::Iterator& iterator)
{
	_current = iterator._current;

	return *this;
}

//оператор разыменования
template <typename T, typename U>
U& Tree<T, U>::ReverseIterator::operator*()
{
	if (!_current)
		throw exception("Итератор не установлен!");

	return _current->_data;
}

//оператор сравнения
template <typename T, typename U>
bool Tree<T, U>::ReverseIterator::operator==(const Tree<T, U>::ReverseIterator& iterator)
{
	return (_current == iterator._current);
}

template <typename T, typename U>
bool Tree<T, U>::ReverseIterator::operator==(const Tree<T, U>::Iterator& iterator)
{
	return (_current == iterator._current);
}

template <typename T, typename U>
bool Tree<T, U>::ReverseIterator::operator!=(const Tree<T, U>::ReverseIterator& iterator)
{
	return (_current != iterator._current);
}

template <typename T, typename U>
bool Tree<T, U>::ReverseIterator::operator!=(const Tree<T, U>::Iterator& iterator)
{
	return (_current != iterator._current);
}

template<typename T, typename U> //получение начального обратного итератора
typename Tree<T, U>::ReverseIterator Tree<T, U>::rBegin()
{
	Tree<T, U>::Node* p = _root;

	if (p)
		while (p->_right)
			p = p->_right;

	Tree<T, U>::ReverseIterator iterator;
	iterator._current = p;

	return iterator;
}

template<typename T, typename U> //получение конечного обратного итератора
typename Tree<T, U>::ReverseIterator Tree<T, U>::rEnd()
{
	return ReverseIterator();
}


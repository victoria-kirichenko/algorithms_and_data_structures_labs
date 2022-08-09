#pragma once
#include <iostream>
#include <exception>
using namespace std;

//T - ��� ����� ������
//U - ��� ������ ������
template <typename T, typename U>
class Tree
{

protected:

	class Node;
	Node* _root;
	int _size;
	double _count; //���������� ���������� ����� ������

public:

	class Iterator; //����� ������� ���������
	friend class Iterator;
	class ReverseIterator; //����� ��������� ���������
	friend class ReverseIterator;

	Tree(); //����� ��������� ���������
	Tree(const Tree& tree); //����������� �����������
	virtual ~Tree(); //����������
	int getSize(); //����� ������� ������
	int getNodeCount(); //��������� ���������� �����, ���������� ��������� ���������
	U& getDataByKey(T key); //��������� ������ �� ������ �� �����
	virtual bool add(T key, U data); //������� �� �����
	virtual bool erase(T key); //�������� �� �����
	void clear(); //������� ������
	virtual void show(); //����� � �������
	void showKeys(); //����� � ������� ������ ������
	bool isClear(); //�������� ������ �� �������

	Iterator begin(); //��������� ���������� ������� ��������� �������
	Iterator end(); //��������� ��������� ������� ��������� �������
	ReverseIterator rBegin(); //��������� ���������� ��������� ��������� �������
	ReverseIterator rEnd(); //��������� ��������� ��������� ��������� �������

};

//����������� �� ���������
template<typename T, typename U>
Tree<T, U>::Tree()
{
	//�������� ����
	_root = nullptr;
	_size = 0;
	_count = 0;
}

//����������� �����������
template<typename T, typename U>
Tree<T, U>::Tree(const Tree& tree)
{
	_root = new Node(*(tree._root));
	_size = tree._size;
	_count = tree._count;
}

//����������
template<typename T, typename U>
Tree<T, U>::~Tree()
{
	delete _root;
}



//��������� ������� ������
template<typename T, typename U>
int Tree<T, U>::getSize()
{
	return _size;
}

//��������� ���������� �����, ���������� ��������� ���������
template<typename T, typename U>
int Tree<T, U>::getNodeCount()
{
	return _count;
}

//��������� ������ �� ������ �� �����
template<typename T, typename U>
U& Tree<T, U>::getDataByKey(T key)
{
	if (!_root)
		throw exception("�������� ����!");

	_count = 0;
	return _root->getDataByKey(key, _count);
}



//������� �� �����
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

//�������� �� �����
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

			//���� � ���������� ���� ��� �����
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

//������� ������
template<typename T, typename U>
void Tree<T, U>::clear()
{
	delete _root;
	_root = nullptr;
	_size = 0;
}



//����� � �������
template<typename T, typename U>
void Tree<T, U>::show()
{
	cout << "������ ������: " << _size << endl;
	if (_root)
		_root->show(0);
}

//����� ������ ������
template<typename T, typename U>
void Tree<T, U>::showKeys()
{
	cout << "����� ������: " << endl;
	if (_root)
		_root->showKeys();
}

//�������� ������ �� �������
template<typename T, typename U>
bool Tree<T, U>::isClear()
{
	return (_root == nullptr);
}


// ����� ����
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

	Node(); //����������� �� ���������
	Node(T key, U data); //����������� � �����������
	Node(const Tree<T, U>::Node& node); //����������� �����������
	virtual ~Node(); //����������
	U& getDataByKey(T key, double& count); //��������� ������ �� ������ �� �����
	virtual bool add(T key, U data, double& count); //������� �� �����
	virtual bool erase(T key, double& count); //�������� �� �����
	virtual void show(int level); //����� � �������
	void showKeys(); //����� ������ � �������

};

template <typename T, typename U>
Tree<T, U>::Node::Node() : _key(), _data()
{
	_left = nullptr;
	_right = nullptr;
	_parent = nullptr;
}

//����������� � �����������
template <typename T, typename U>
Tree<T, U>::Node::Node(T key, U data) : _key(key), _data(data)
{
	_left = nullptr;
	_right = nullptr;
	_parent = nullptr;
}

//����������� �����������
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

//����������
template <typename T, typename U>
Tree<T, U>::Node::~Node()
{
	delete _left;
	delete _right;
}



//��������� ������ �� ������ �� �����
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
			throw exception("�������� ����!");
	else
		if (_right)
			return _right->getDataByKey(key, count);
		else
			throw exception("�������� ����!");
}



//������� �� �����
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

//�������� �� �����
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



//����� � �������
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

//����� ������ � �������
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

	Node* _current; //��������� �� ������� ���� ������

public:

	friend class Tree<T, U>::ReverseIterator;

	Iterator(); //����������� �� ���������
	Iterator(const Iterator& iterator); //����������� �����������

	Iterator& operator++(); //�������� ����������
	Iterator& operator--(); //�������� ����������
	Iterator& operator=(const Iterator& iterator); //�������� ������������
	Iterator& operator=(const ReverseIterator& iterator); //�������� ������������
	U& operator*(); //�������� �������������
	bool operator==(const Iterator& iterator); //�������� ��������� �� ���������
	bool operator==(const ReverseIterator& iterator); //�������� ��������� �� ���������
	bool operator!=(const Iterator& iterator); //�������� ��������� �� �����������
	bool operator!=(const ReverseIterator& iterator); //�������� ��������� �� �����������

};


template <typename T, typename U> //����������� �� ���������
Tree<T, U>::Iterator::Iterator()
{
	_current = nullptr;
}

template <typename T, typename U> //����������� �����������
Tree<T, U>::Iterator::Iterator(const Iterator& iterator)
{
	_current = iterator._current;
}


//�������� ����������
template <typename T, typename U>
typename Tree<T, U>::Iterator& Tree<T, U>::Iterator::operator++()
{

	if (!_current)
		throw exception("�������� �� ����������!");

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


template <typename T, typename U> //�������� ����������
typename Tree<T, U>::Iterator& Tree<T, U>::Iterator::operator--()
{
	if (!_current)
		throw exception("�������� �� ����������!");

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


template <typename T, typename U> //��������� ������������
typename Tree<T, U>::Iterator& Tree<T, U>::Iterator::operator=(const Tree<T, U>::Iterator& iterator)
{
	_current = iterator._current;

	return *this;
}

template <typename T, typename U> //��������� ������������
typename Tree<T, U>::Iterator& Tree<T, U>::Iterator::operator=(const Tree<T, U>::ReverseIterator& iterator)
{
	_current = iterator._current;

	return *this;
}

template <typename T, typename U> //�������� �������������
U& Tree<T, U>::Iterator::operator*()
{
	if (!_current)
		throw exception("�������� �� ����������!");

	return _current->_data;
}



//��������� ���������
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


template<typename T, typename U> //��������� ���������� ������� ���������
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


template<typename T, typename U> //��������� ��������� ������� ���������
typename Tree<T, U>::Iterator Tree<T, U>::end()
{
	return Iterator();
}


template <typename T, typename U>
class Tree<T, U>::ReverseIterator
{
private:

	friend class Tree<T, U>;
	Node* _current; //��������� �� ������� ���� ������

public:

	friend class Tree<T, U>::Iterator;


	ReverseIterator(); //����������� �� ���������
	ReverseIterator(const ReverseIterator& iterator); //����������� �����������

	ReverseIterator& operator++(); //�������� ����������
	ReverseIterator& operator--(); //�������� ����������
	ReverseIterator& operator=(const ReverseIterator& iterator); //�������� ������������
	ReverseIterator& operator=(const Iterator& iterator); //�������� ������������
	U& operator*(); //�������� �������������
	bool operator==(const ReverseIterator& iterator); //�������� ��������� �� ���������
	bool operator==(const Iterator& iterator); //�������� ��������� �� ���������
	bool operator!=(const ReverseIterator& iterator); //�������� ��������� �� �����������
	bool operator!=(const Iterator& iterator); //�������� ��������� �� �����������

};


template <typename T, typename U> //����������� �� ���������
Tree<T, U>::ReverseIterator::ReverseIterator()
{
	_current = nullptr;
}


template <typename T, typename U> //����������� �����������
Tree<T, U>::ReverseIterator::ReverseIterator(const ReverseIterator& iterator)
{
	_current = iterator._current;
}


template <typename T, typename U> //�������� ����������
typename Tree<T, U>::ReverseIterator& Tree<T, U>::ReverseIterator::operator++()
{
	if (!_current)
		throw exception("�������� �� ����������!");

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


template <typename T, typename U> //�������� ����������
typename Tree<T, U>::ReverseIterator& Tree<T, U>::ReverseIterator::operator--()
{

	if (!_current)
		throw exception("�������� �� ����������!");

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


//�������� ������������
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

//�������� �������������
template <typename T, typename U>
U& Tree<T, U>::ReverseIterator::operator*()
{
	if (!_current)
		throw exception("�������� �� ����������!");

	return _current->_data;
}

//�������� ���������
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

template<typename T, typename U> //��������� ���������� ��������� ���������
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

template<typename T, typename U> //��������� ��������� ��������� ���������
typename Tree<T, U>::ReverseIterator Tree<T, U>::rEnd()
{
	return ReverseIterator();
}


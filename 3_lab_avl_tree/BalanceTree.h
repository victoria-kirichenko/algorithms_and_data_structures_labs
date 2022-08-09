#pragma once
#include "Tree.h"

//����� ���-������
//T - ��� ����� ������
//U - ��� ������ ������
template <typename T, typename U>
class BalanceTree : public Tree<T, U>
{

protected:

	//����� ���� ��� ����������������� ������
	class BalanceNode;

public:

	friend class Tree<T, U>::Iterator;
	friend class Tree<T, U>::ReverseIterator;

	BalanceTree(); //����������� �� ���������
	BalanceTree(const BalanceTree& tree); //����������� �����������
	virtual bool add(T key, U data) override; //������� �� �����
	virtual bool erase(T key) override; //�������� �� �����
	virtual void show() override; // ����� ������ �� �������

};


template<typename T, typename U> //����������� �� ���������
BalanceTree<T, U>::BalanceTree()
{
	this->_root = nullptr;
	this->_size = 0;
	this->_count = 0;
}

template<typename T, typename U> //����������� �����������
BalanceTree<T, U>::BalanceTree(const BalanceTree& tree)
{
	this->_root = new BalanceNode(*(dynamic_cast<BalanceNode*>(tree._root)));
	this->_size = tree._size;
	this->_count = tree._count;
}

template<typename T, typename U>
void BalanceTree<T, U>::show()
{
	this->_root->show(0);
}

template<typename T, typename U> //������� �� �����
bool BalanceTree<T, U>::add(T key, U data)
{
	this->_count = 1;

	if (this->_root)
	{
		bool flag = this->_root->add(key, data, this->_count);

		if (flag)
		{
			//�� ����������� ������
			this->_root = dynamic_cast<BalanceNode*>(this->_root)->balance(dynamic_cast<BalanceNode*>(this->_root));
			this->_size++;
		}
		return flag;
	}
	else
	{
		this->_root = new BalanceNode(key, data);
		this->_size++;
		return true;
	}
}


template<typename T, typename U> //�������� �� �����
bool BalanceTree<T, U>::erase(T key)
{

	if (!this->_root)
		return false;

	this->_count = 1;
	BalanceNode* p;

	//���� ����� ������� ������
	if (key == dynamic_cast<BalanceNode*>(this->_root)->_key)
	{
		p = dynamic_cast<BalanceNode*>(this->_root);

		//���� ��������� ���� �� ����� ������� ���������, 
		//�� �� �������� ���-������ ����� � ����� ���� 
		//����� ���� ������ ���� ������������ �������� ���� (������ ������ 1), 
		//���� ���� p ������ ����
		if ((!p->_left && !p->_right) || (p->_left && !p->_right))
		{
			this->_root = p->_left;
			if (this->_root)
				dynamic_cast<BalanceNode*>(this->_root)->_parent = nullptr;

			p->_left = nullptr;
			delete p;

			this->_size--;
			this->_root = dynamic_cast<BalanceNode*>(this->_root)->balance(dynamic_cast<BalanceNode*>(this->_root));
			return true;
		}

		//� �������� ������ � ���� ���� ������ ������ �����, ���� ��� �����
		//����� ���� ������� � ������ ����� � �� �������� ��������� ����
		BalanceNode* min = dynamic_cast<BalanceNode*>(p->_right);
		while (min->_left)
			min = dynamic_cast<BalanceNode*>(min->_left);

		T nodeKey = min->_key;
		U nodeData = min->_data;

		this->_root->erase(nodeKey, this->_count);

		p->_key = nodeKey;
		p->_data = nodeData;

		this->_size--;
		this->_root = dynamic_cast<BalanceNode*>(this->_root)->balance(dynamic_cast<BalanceNode*>(this->_root));

		return true;
	}

	bool flag = this->_root->erase(key, this->_count);

	if (flag)
	{
		this->_root = dynamic_cast<BalanceNode*>(this->_root)->balance(dynamic_cast<BalanceNode*>(this->_root));
		this->_size--;
	}

	return flag;
}


/*--------------����� ���� ���-������--------------*/

template <typename T, typename U>
class BalanceTree<T, U>::BalanceNode : public Tree<T, U>::Node	//����������� �� ���� �������� ������
{
private:

	friend class BalanceTree<T, U>;

	int _height; //������ ������� ���������

	BalanceNode* balance(BalanceNode* node); //����� ������������ ���� ������
	BalanceNode* rotateLeft(BalanceNode* node); //������� �����
	BalanceNode* rotateRight(BalanceNode* node); //������� ������

	void fixHeight(); //�������������� �������� ������ ������

public:

	friend class Tree<T, U>::Iterator;
	friend class Tree<T, U>::ReverseIterator;

	BalanceNode(T key, U data); //����������� � �����������
	BalanceNode(const BalanceNode& node); //����������� �����������
	virtual bool add(T key, U data, double& count) override; //������� �� �����
	virtual bool erase(T key, double& count) override; //�������� �� �����
	int getHeight(); //��������� ������ ������
	int computeBalanceCriterion(); //���������� �������� ������������������
	virtual void show(int level); // ����� ������ �� �������
};

template <typename T, typename U>
void BalanceTree<T, U>::BalanceNode::show(int level)
{
	if (this->_right)
		this->_right->show(level + 1);

	for (int i = 0; i < 3 * level; i++)
		cout << " ";

	cout << this->_key << "(" << _height << ")" << endl;

	if (this->_left)
		this->_left->show(level + 1);
}


template<typename T, typename U> //����� ������������ ���� ������
typename BalanceTree<T, U>::BalanceNode* BalanceTree<T, U>::BalanceNode::balance(BalanceTree<T, U>::BalanceNode* node)
{
	if (!node)
		return node;

	node->fixHeight();
	if (node->computeBalanceCriterion() == 2)
	{
		if (dynamic_cast<BalanceNode*>(node->_right)->computeBalanceCriterion() < 0)
			rotateRight(dynamic_cast<BalanceNode*>(node->_right));

		return rotateLeft(node);
	}

	if (node->computeBalanceCriterion() == -2)
	{
		if (dynamic_cast<BalanceNode*>(node->_left)->computeBalanceCriterion() > 0)
			rotateLeft(dynamic_cast<BalanceNode*>(node->_left));

		return rotateRight(node);
	}

	return node;
}

//����� �������
template<typename T, typename U>
typename BalanceTree<T, U>::BalanceNode* BalanceTree<T, U>::BalanceNode::rotateLeft(BalanceNode* q)
{
	BalanceNode* parent = dynamic_cast<BalanceNode*>(q->_parent);
	bool isLeft;
	if (parent)
		if (parent->_left == q)
			isLeft = true;
		else
			isLeft = false;

	BalanceNode* p = dynamic_cast<BalanceNode*>(q->_right);
	q->_right = p->_left;
	p->_left = q;

	p->_parent = parent;
	if (parent)
		if (isLeft)
			parent->_left = p;
		else
			parent->_right = p;

	if (p->_right)
		dynamic_cast<BalanceNode*>(p->_right)->_parent = p;

	if (p->_left)
		dynamic_cast<BalanceNode*>(p->_left)->_parent = p;

	if (q->_left)
		dynamic_cast<BalanceNode*>(q->_left)->_parent = q;

	if (q->_right)
		dynamic_cast<BalanceNode*>(q->_right)->_parent = q;

	q->fixHeight();
	p->fixHeight();

	return p;
}

template<typename T, typename U>
typename BalanceTree<T, U>::BalanceNode* BalanceTree<T, U>::BalanceNode::rotateRight(BalanceNode* p)
{
	//���������� �������� �������� ����
	BalanceNode* parent = dynamic_cast<BalanceNode*>(p->_parent);
	bool isLeft;
	if (parent)
		if (parent->_left == p)
			isLeft = true;
		else
			isLeft = false;

	BalanceNode* q = dynamic_cast<BalanceNode*>(p->_left);
	p->_left = q->_right;
	q->_right = p;

	q->_parent = parent;
	if (parent)
		if (isLeft)
			parent->_left = q;
		else
			parent->_right = q;

	if (q->_left)
		dynamic_cast<BalanceNode*>(q->_left)->_parent = q;

	if (q->_right)
		dynamic_cast<BalanceNode*>(q->_right)->_parent = q;

	if (p->_right)
		dynamic_cast<BalanceNode*>(p->_right)->_parent = p;

	if (p->_left)
		dynamic_cast<BalanceNode*>(p->_left)->_parent = p;

	p->fixHeight();
	q->fixHeight();

	return q;
}


//�������������� �������� ������ ������
template<typename T, typename U>
void BalanceTree<T, U>::BalanceNode::fixHeight()
{
	int leftHeight = 0;
	if (this->_left)
		leftHeight = dynamic_cast<BalanceNode*>(this->_left)->_height;

	int rightHeight = 0;
	if (this->_right)
		rightHeight = dynamic_cast<BalanceNode*>(this->_right)->_height;

	//�������� ������������ ������ �� ����������� -> ����� ������ ����
	if (leftHeight > rightHeight)
		this->_height = leftHeight + 1;
	else
		this->_height = rightHeight + 1;
}


//����������� � �����������
template<typename T, typename U>
BalanceTree<T, U>::BalanceNode::BalanceNode(T key, U data)
{
	this->_key = key;
	this->_data = data;

	this->_left = nullptr;
	this->_right = nullptr;
	this->_parent = nullptr;

	_height = 1;
}

//����������� �����������
template<typename T, typename U>
BalanceTree<T, U>::BalanceNode::BalanceNode(const BalanceTree<T, U>::BalanceNode& node)
{
	this->_key = node._key;
	this->_data = node._data;

	this->_height = node._height;

	if (node._left)
	{
		this->_left = new typename BalanceTree<T, U>::BalanceNode(*(dynamic_cast<BalanceNode*>(node._left)));
		dynamic_cast<BalanceNode*>(this->_left)->_parent = this;
	}
	else
		this->_left = nullptr;

	if (node._right)
	{
		this->_right = new typename BalanceTree<T, U>::BalanceNode(*(dynamic_cast<BalanceNode*>(node._right)));
		dynamic_cast<BalanceNode*>(this->_right)->_parent = this;
	}
	else
		this->_right = nullptr;

	this->_parent = nullptr;
}


//������� �� �����
template<typename T, typename U>
bool BalanceTree<T, U>::BalanceNode::add(T key, U data, double& count)
{
	count++;

	if (key == this->_key)
		return false;

	if (key < this->_key)
		if (this->_left)
		{
			bool flag = this->_left->add(key, data, count);

			if (flag)
				balance(dynamic_cast<BalanceNode*>(this->_left));

			return flag;
		}
		else
		{
			this->_left = new typename BalanceTree<T, U>::BalanceNode(key, data);
			dynamic_cast<BalanceNode*>(this->_left)->_parent = this;

			return true;
		}
	else
		if (this->_right)
		{
			bool flag = this->_right->add(key, data, count);

			if (flag)
				balance(dynamic_cast<BalanceNode*>(this->_right));

			return flag;
		}
		else
		{
			this->_right = new typename BalanceTree<T, U>::BalanceNode(key, data);
			dynamic_cast<BalanceNode*>(this->_right)->_parent = this;

			return true;
		}
}

//�������� �� �����
template<typename T, typename U>
bool BalanceTree<T, U>::BalanceNode::erase(T key, double& count)
{
	count++;

	BalanceNode* p;

	if (this->_left && (dynamic_cast<BalanceNode*>(this->_left)->_key == key))
	{
		p = dynamic_cast<BalanceNode*>(this->_left);

		//���� ��������� ���� �� ����� ������� ���������, 
		//�� �� �������� ���-������ ����� � ����� ���� 
		//����� ���� ������ ���� ������������ �������� ���� (������ ������ 1), 
		//���� ���� p ������ ����
		if ((!p->_left && !p->_right) || (p->_left && !p->_right))
		{
			this->_left = p->_left;
			if (this->_left)
				dynamic_cast<BalanceNode*>(this->_left)->_parent = this;

			p->_left = nullptr;
			delete p;

			return true;
		}

		BalanceNode* min = dynamic_cast<BalanceNode*>(p->_right);
		while (min->_left)
			min = dynamic_cast<BalanceNode*>(min->_left);

		T nodeKey = min->_key;
		U nodeData = min->_data;

		erase(nodeKey, count);

		p->_key = nodeKey;
		p->_data = nodeData;

		return true;
	}

	//���� ���� ������ ���� � ��� ���� ��������� � �������
	if (this->_right && (dynamic_cast<BalanceNode*>(this->_right)->_key == key))
	{
		p = dynamic_cast<BalanceNode*>(this->_right);

		if ((!p->_left && !p->_right) || (p->_left && !p->_right))
		{
			this->_right = p->_left;
			if (this->_right)
				dynamic_cast<BalanceNode*>(this->_right)->_parent = this;

			p->_left = nullptr;
			delete p;

			return true;
		}

		BalanceNode* min = dynamic_cast<BalanceNode*>(p->_right);
		while (min->_left)
			min = dynamic_cast<BalanceNode*>(min->_left);

		T nodeKey = min->_key;
		U nodeData = min->_data;

		erase(nodeKey, count);

		p->_key = nodeKey;
		p->_data = nodeData;

		return true;

	}

	if (key < this->_key)
		if (this->_left)
		{
			bool flag = this->_left->erase(key, count);

			if (flag)
				balance(dynamic_cast<BalanceNode*>(this->_left));

			return flag;
		}
		else
			return false;
	else
		if (this->_right)
		{
			bool flag = this->_right->erase(key, count);

			if (flag)
				balance(dynamic_cast<BalanceNode*>(this->_right));

			return flag;
		}
		else
			return false;
}


//��������� ������ ������� ���������
template<typename T, typename U>
int BalanceTree<T, U>::BalanceNode::getHeight()
{
	return _height;
}

//���������� �������� ������������������
template<typename T, typename U>
int BalanceTree<T, U>::BalanceNode::computeBalanceCriterion()
{
	int leftHeight = 0;
	if (this->_left)
		leftHeight = dynamic_cast<BalanceNode*>(this->_left)->_height;

	int rightHeight = 0;
	if (this->_right)
		rightHeight = dynamic_cast<BalanceNode*>(this->_right)->_height;

	return rightHeight - leftHeight;
}

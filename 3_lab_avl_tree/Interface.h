#pragma once
#include "test.h"
#include "BalanceTree.h"



template<typename T, typename U>
class Interface
{
private:

	BalanceTree<T, U> _tree;

	void addByKey(); //�������� �� �����
	void eraseByKey(); //�������� �� �����
	void clear(); //������� ������

	void getSize(); //�������
	void getDataByKey();
	void getNodeCount();

	void setDataByKey(); //�������
	void isClear(); //�������� �� �������
	void show(); //����� ������ �� �����
	void showKeys(); //����� ������ ������ �� �����
	void startTest(); //������ ������������ ������������ ��� ������
	void iterator(BalanceTree<T, U>& tree); //������ � ����������

public:
	//������ ���������� ������ � �������
	static	T getKeyFromConsole();
	static	U getDataFromConsole();
	static int getIntFromConsole();
	void menu();

};

template<typename T, typename U>
void Interface<T, U>::addByKey()
{
	cout << "������� ���� ��� �������: " << endl;
	T key = getKeyFromConsole();

	cout << "������� ������ ��� �������: " << endl;
	U data = getDataFromConsole();

	cout << "������� �� �����: " << _tree.add(key, data) << endl;;
}

template<typename T, typename U>
void Interface<T, U>::eraseByKey()
{
	cout << "������� ���� ��� ��������: " << endl;
	T key = getKeyFromConsole();

	cout << "�������� �� �����: " << _tree.erase(key) << endl;
}

template<typename T, typename U>
void Interface<T, U>::clear()
{
	_tree.clear();
	cout << "������ �������!" << endl;
}

template<typename T, typename U>
void Interface<T, U>::getSize()
{
	cout << "������ ������: " << _tree.getSize() << endl;
}

template<typename T, typename U>
void Interface<T, U>::getDataByKey()
{
	cout << "������� ���� ��� ������: " << endl;
	T key = getKeyFromConsole();

	U& data = _tree.getDataByKey(key);

	cout << "������ �� �����: " << data << endl;
}

template<typename T, typename U>
void Interface<T, U>::getNodeCount()
{
	cout << "���������� �����, ���������� �� ����� ��������� ��������: " << _tree.getNodeCount() << endl;
}

template<typename T, typename U>
void Interface<T, U>::setDataByKey()
{
	cout << "������� ���� ��� ������: " << endl;
	T key = getKeyFromConsole();

	cout << "������� ����� ������: " << endl;
	U newData = getDataFromConsole();

	U& data = _tree.getDataByKey(key);

	data = newData;
}

template<typename T, typename U>
void Interface<T, U>::isClear()
{
	cout << "������ �����: " << _tree.isClear() << endl;
}

template<typename T, typename U>
void Interface<T, U>::show()
{
	_tree.show();
	cout << endl;
}

template<typename T, typename U>
void Interface<T, U>::showKeys()
{
	_tree.showKeys();
	cout << endl;
}

template<typename T, typename U>
void Interface<T, U>::startTest()
{
	cout << "0 - ���, ������ ����� - ��" << endl;
	cout << "�����, �� ��������� ������������ �����, ������������� �������� ������ ���� � ����� � ����������� �� 10��" << endl;

	int flag = getIntFromConsole();

	if (flag)
		testShell();
}

template<typename T, typename U>
void Interface<T, U>::iterator(BalanceTree<T, U>& tree)
{
	int command;

	typename Tree<T, U>::Iterator it;
	typename Tree<T, U>::ReverseIterator rit;

	it = tree.begin();
	rit = tree.rBegin();

	cout << "��������� ����������� �� ������ ������!" << endl;
	cout << endl << "--------------------" << endl << endl;

	while (true)
		try
	{

		cout << "������� ����� ������ �������" << endl;

		cout << endl << "-----������ ��������-----" << endl;
		cout << "1) ������ ��������� begin();" << endl;
		cout << "2) ������ ��������� end();" << endl;
		cout << "3) ������� � ����������� ���� (--);" << endl;
		cout << "4) ������� � ���������� ���� (++);" << endl;
		cout << "5) ������ �� ������ (*);" << endl;
		cout << "6) ������ �� ������ (*);" << endl;
		cout << "7) ��������� ���������� ��������� �� �������; (==end())" << endl;

		cout << endl << "-----�������� ��������-----" << endl;
		cout << "8) ������ ��������� rbegin();" << endl;
		cout << "9) ������ ��������� rend();" << endl;
		cout << "10) ������� � ���������� ���� (--);" << endl;
		cout << "11) ������� � ����������� ���� (++);" << endl;
		cout << "12) ������ �� ������ (*);" << endl;
		cout << "13) ������ �� ������ (*);" << endl;
		cout << "14) ��������� ���������� ��������� �� �������; (==rEnd())" << endl;

		cout << endl << "-----�����-----" << endl;
		cout << "15) �������� ��������� (==);" << endl;
		cout << "16) �������� ��������� (!=);" << endl;
		cout << "17) ����� ������ � �������." << endl;

		cout << "0) �����." << endl;

		command = getIntFromConsole();

		cout << endl << "--------------------" << endl << endl;

		switch (command)
		{
		case 0:
		{
			return;
		}
		case 1:
		{
			it = tree.begin();
			cout << "���������� �������� begin()!" << endl;
			break;
		}
		case 2:
		{
			it = tree.end();
			cout << "���������� �������� end()!" << endl;
			break;
		}
		case 3:
		{
			--it;
			cout << "�������� ��������� �����!" << endl;
			break;
		}
		case 4:
		{
			++it;
			cout << "�������� ��������� ������!" << endl;
			break;
		}
		case 5:
		{
			cout << "���������� ���������:" << endl;
			cout << *it << endl;
			break;
		}
		case 6:
		{
			cout << "������� ����� ��������:" << endl;
			T data = getDataFromConsole();

			(*it) = data;
			cout << "�������� ��������!" << endl;
			break;
		}
		case 7:
		{
			if (it == tree.end())
				cout << "���������� ��������� �����! ���������� ���������� �������� �� ������ ������!" << endl;
			else
				cout << "���������� ��������� �� �����!" << endl;
			break;
		}
		case 8:
		{
			rit = tree.rBegin();
			cout << "���������� �������� rBegin()!" << endl;
			break;
		}
		case 9:
		{
			rit = tree.rEnd();
			cout << "���������� �������� rEnd()!" << endl;
			break;
		}
		case 10:
		{
			--rit;
			cout << "�������� ��������� �����!" << endl;
			break;
		}
		case 11:
		{
			++rit;
			cout << "�������� ��������� ������!" << endl;
			break;
		}
		case 12:
		{
			cout << "���������� ���������:" << endl;
			cout << *rit << endl;
			break;
		}
		case 13:
		{
			cout << "������� ����� ��������:" << endl;
			T data = getDataFromConsole();

			(*rit) = data;
			cout << "�������� ��������!" << endl;
			break;
		}
		case 14:
		{
			if (rit == tree.rEnd())
				cout << "���������� ��������� �����! ���������� ���������� �������� �� ����� ������!" << endl;
			else
				cout << "���������� ��������� �� �����!" << endl;
			break;
		}
		case 15:
		{
			cout << "��������� �����: " << (it == rit) << endl;
			break;
		}
		case 16:
		{
			cout << "��������� �� �����: " << (it != rit) << endl;
			break;
		}
		case 17:
		{
			show();
			break;
		}
		}
		cout << endl << "--------------------" << endl << endl;
	}
	catch (const exception& error)
	{
		cout << "EXCEPTION: " << error.what() << endl;

		cout << endl << "--------------------" << endl << endl;
	}
}

//������ ����� � �������
template<typename T, typename U>
T Interface<T, U>::getKeyFromConsole()
{
	T key;

	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	cin >> key;

	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	return key;
}

//������ ������ � �������
template<typename T, typename U>
U Interface<T, U>::getDataFromConsole()
{
	U data;

	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	cin >> data;

	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	return data;
}

template<typename T, typename U>
int Interface<T, U>::getIntFromConsole()
{
	int i;

	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	cin >> i;

	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	return i;
}

template<typename T, typename U>
void Interface<T, U>::menu()
{
	int command;

	while (true)
		try
	{

		cout << "������� ����� ������ �������" << endl;
		cout << "1) ������� �� �����;" << endl;
		cout << "2) �������� �� �����;" << endl;
		cout << "3) ������� ������;" << endl;
		cout << "4) ����� ������� ������;" << endl;
		cout << "5) ������ �� ������ � ������ �� �����;" << endl;
		cout << "6) ������ �� ������ � ������ �� �����;" << endl;
		cout << "7) ����� � �������;" << endl;
		cout << "8) �������� ������ �� �������;" << endl;
		cout << "9) ������ � �����������;" << endl;
		cout << "10) ����� ������ � �������;" << endl;
		cout << "11) ����� ���������� �����, ���������� �� ����� ��������� ��������;" << endl;
		cout << "12) ��������� ������������ ������������;" << endl;
		cout << "0) �����." << endl;

		command = getIntFromConsole();

		switch (command)
		{
		case 0:
		{
			return;
			break;
		}
		case 1:
		{
			addByKey();
			break;
		}
		case 2:
		{
			eraseByKey();
			break;
		}
		case 3:
		{
			clear();
			break;
		}
		case 4:
		{
			getSize();
			break;
		}
		case 5:
		{
			getDataByKey();
			break;
		}
		case 6:
		{
			setDataByKey();
			break;
		}
		case 7:
		{
			show();
			break;
		}
		case 8:
		{
			isClear();
			break;
		}
		case 9:
		{
			iterator(_tree);
			break;
		}
		case 10:
		{
			showKeys();
			break;
		}
		case 11:
		{
			getNodeCount();
			break;
		}
		case 12:
		{
			startTest();
			break;
		}
		}
		cout << endl << "--------------------" << endl << endl;
	}
	catch (const exception& error)
	{
		cout << "EXCEPTION: " << error.what() << endl;

		cout << endl << "--------------------" << endl << endl;
	}
}
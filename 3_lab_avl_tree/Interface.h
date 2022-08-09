#pragma once
#include "test.h"
#include "BalanceTree.h"



template<typename T, typename U>
class Interface
{
private:

	BalanceTree<T, U> _tree;

	void addByKey(); //вставить по ключу
	void eraseByKey(); //удаление по ключу
	void clear(); //очистка дерева

	void getSize(); //Геттеры
	void getDataByKey();
	void getNodeCount();

	void setDataByKey(); //сеттеры
	void isClear(); //проверка на пустоту
	void show(); //вывод деоева на экран
	void showKeys(); //вывод списка ключей на экран
	void startTest(); //запуск тестирования трудоемкости для дерева
	void iterator(BalanceTree<T, U>& tree); //работа с итератором

public:
	//методы считывания данных с консоли
	static	T getKeyFromConsole();
	static	U getDataFromConsole();
	static int getIntFromConsole();
	void menu();

};

template<typename T, typename U>
void Interface<T, U>::addByKey()
{
	cout << "Введите ключ для вставки: " << endl;
	T key = getKeyFromConsole();

	cout << "Введите данные для вставки: " << endl;
	U data = getDataFromConsole();

	cout << "Вставка по ключу: " << _tree.add(key, data) << endl;;
}

template<typename T, typename U>
void Interface<T, U>::eraseByKey()
{
	cout << "Введите ключ для удаления: " << endl;
	T key = getKeyFromConsole();

	cout << "Удаление по ключу: " << _tree.erase(key) << endl;
}

template<typename T, typename U>
void Interface<T, U>::clear()
{
	_tree.clear();
	cout << "Дерево очищено!" << endl;
}

template<typename T, typename U>
void Interface<T, U>::getSize()
{
	cout << "Размер дерева: " << _tree.getSize() << endl;
}

template<typename T, typename U>
void Interface<T, U>::getDataByKey()
{
	cout << "Введите ключ для поиска: " << endl;
	T key = getKeyFromConsole();

	U& data = _tree.getDataByKey(key);

	cout << "Данные по ключу: " << data << endl;
}

template<typename T, typename U>
void Interface<T, U>::getNodeCount()
{
	cout << "Количество узлов, опрошенных во время последней операции: " << _tree.getNodeCount() << endl;
}

template<typename T, typename U>
void Interface<T, U>::setDataByKey()
{
	cout << "Введите ключ для поиска: " << endl;
	T key = getKeyFromConsole();

	cout << "Введите новые данные: " << endl;
	U newData = getDataFromConsole();

	U& data = _tree.getDataByKey(key);

	data = newData;
}

template<typename T, typename U>
void Interface<T, U>::isClear()
{
	cout << "Дерево пусто: " << _tree.isClear() << endl;
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
	cout << "0 - нет, другое число - да" << endl;
	cout << "Также, во избежание переполнения стека, рекомендуется повысить размер кучи и стека в компиляторе до 10МБ" << endl;

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

	cout << "Итераторы установлены на начало списка!" << endl;
	cout << endl << "--------------------" << endl << endl;

	while (true)
		try
	{

		cout << "Введите номер нужной команды" << endl;

		cout << endl << "-----ПРЯМОЙ ИТЕРАТОР-----" << endl;
		cout << "1) Запрос итератора begin();" << endl;
		cout << "2) Запрос итератора end();" << endl;
		cout << "3) Переход к предыдущему узлу (--);" << endl;
		cout << "4) Переход к следующему узлу (++);" << endl;
		cout << "5) Доступ по чтению (*);" << endl;
		cout << "6) Доступ по записи (*);" << endl;
		cout << "7) Проверить содержимое итератора на пустоту; (==end())" << endl;

		cout << endl << "-----ОБРАТНЫЙ ИТЕРАТОР-----" << endl;
		cout << "8) Запрос итератора rbegin();" << endl;
		cout << "9) Запрос итератора rend();" << endl;
		cout << "10) Переход к следующему узлу (--);" << endl;
		cout << "11) Переход к предыдущему узлу (++);" << endl;
		cout << "12) Доступ по чтению (*);" << endl;
		cout << "13) Доступ по записи (*);" << endl;
		cout << "14) Проверить содержимое итератора на пустоту; (==rEnd())" << endl;

		cout << endl << "-----ОБЩЕЕ-----" << endl;
		cout << "15) Сравнить итераторы (==);" << endl;
		cout << "16) Сравнить итераторы (!=);" << endl;
		cout << "17) Вывод дерева в консоль." << endl;

		cout << "0) Назад." << endl;

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
			cout << "Установлен итератор begin()!" << endl;
			break;
		}
		case 2:
		{
			it = tree.end();
			cout << "Установлен итератор end()!" << endl;
			break;
		}
		case 3:
		{
			--it;
			cout << "Итератор перемещен назад!" << endl;
			break;
		}
		case 4:
		{
			++it;
			cout << "Итератор перемещен вперед!" << endl;
			break;
		}
		case 5:
		{
			cout << "Содержимое итератора:" << endl;
			cout << *it << endl;
			break;
		}
		case 6:
		{
			cout << "Введите новое значение:" << endl;
			T data = getDataFromConsole();

			(*it) = data;
			cout << "Значение изменено!" << endl;
			break;
		}
		case 7:
		{
			if (it == tree.end())
				cout << "Содержимое итератора пусто! Необходимо установить итератор на начало дерева!" << endl;
			else
				cout << "Содержимое итератора не пусто!" << endl;
			break;
		}
		case 8:
		{
			rit = tree.rBegin();
			cout << "Установлен итератор rBegin()!" << endl;
			break;
		}
		case 9:
		{
			rit = tree.rEnd();
			cout << "Установлен итератор rEnd()!" << endl;
			break;
		}
		case 10:
		{
			--rit;
			cout << "Итератор перемещен назад!" << endl;
			break;
		}
		case 11:
		{
			++rit;
			cout << "Итератор перемещен вперед!" << endl;
			break;
		}
		case 12:
		{
			cout << "Содержимое итератора:" << endl;
			cout << *rit << endl;
			break;
		}
		case 13:
		{
			cout << "Введите новое значение:" << endl;
			T data = getDataFromConsole();

			(*rit) = data;
			cout << "Значение изменено!" << endl;
			break;
		}
		case 14:
		{
			if (rit == tree.rEnd())
				cout << "Содержимое итератора пусто! Необходимо установить итератор на конец дерева!" << endl;
			else
				cout << "Содержимое итератора не пусто!" << endl;
			break;
		}
		case 15:
		{
			cout << "Итераторы равны: " << (it == rit) << endl;
			break;
		}
		case 16:
		{
			cout << "Итератора не равны: " << (it != rit) << endl;
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

//чтение ключа с консоли
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

//чтение данных с консоли
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

		cout << "Введите номер нужной команды" << endl;
		cout << "1) Вставка по ключу;" << endl;
		cout << "2) Удаление по ключу;" << endl;
		cout << "3) Очистка дерева;" << endl;
		cout << "4) Опрос размера дерева;" << endl;
		cout << "5) Доступ по чтению к данным по ключу;" << endl;
		cout << "6) Доступ по записи к данным по ключу;" << endl;
		cout << "7) Вывод в консоль;" << endl;
		cout << "8) Проверка дерева на пустоту;" << endl;
		cout << "9) Работа с итераторами;" << endl;
		cout << "10) Вывод ключей в консоль;" << endl;
		cout << "11) Вывод количества узлов, опрошенных во время последней операции;" << endl;
		cout << "12) Запустить тестирование трудоемкости;" << endl;
		cout << "0) Выход." << endl;

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
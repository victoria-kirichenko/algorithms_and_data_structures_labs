#include "List.h"

int main() {
	setlocale(LC_ALL, "Russian");
	bool exit = false;
	int number = 0;
	int n, t;
	cout << "Введите размер списка: ";
	cin >> n;
	List<int> Listt(n);
	while (!exit)
	{
		switch (number) {
		case 1:
		{
			int num;
			cout << "Введите элемент: ";
			cin >> num;
			cout << endl << Listt.push_back(num) << endl;
		}
		break;
		case 2:
		{
			int _item, num;
			cout << "Введите элемент и позицию в списке: ";
			cin >> _item >> num;
			cout << endl << Listt.insert(_item, num) << endl;
		}
		break;
		case 3:
		{
			int _item, num;
			cout << "Введите значение на которое изменить и позицию в списке: ";
			cin >> _item >> num;
			cout << endl << Listt.change(_item, num) << endl;
		}
		break;
		case 4:
		{
			int _item;
			cout << "Введите значение элемента: ";
			cin >> _item;
			try {
				int res = Listt.get_pos(_item);
				cout << endl << res << endl;
			}
			catch (MyException& ex) {
				cerr << ex.what() << "\n";
			}
		}
		break;
		case 5:
		{
			int num;
			cout << "Введите позицию в списке: ";
			cin >> num;
			try {
				int res = Listt.get_value(num);
				cout << endl << res << endl;
			}
			catch (MyException& ex) {
				cerr << ex.what() << "\n";
			}
		}
		break;
		case 6:
		{
			int _item;
			cout << "Введите значение элемента: ";
			cin >> _item;
			cout << endl << Listt.is_contains(_item) << endl;
		}
		break;
		case 7:
		{
			int _item;
			cout << "Введите значение элемента: ";
			cin >> _item;
			cout << endl << Listt.remove_item(_item) << endl;
		}
		break;
		case 8:
		{
			int num;
			cout << "Введите позицию элемента: ";
			cin >> num;
			cout << Listt.remove(num) << endl;
		}
		break;
		case 9:
		{
			cout << endl << Listt.is_empty() << endl;
		}
		break;
		case 10:
		{
			Listt.remove_list();
		}
		break;
		case 11:
		{
			List<int>::Iterator it = Listt.begin();
			int number2 = 0;
			bool exit1 = false;
			while (!exit1)
			{
				switch (number2)
				{
				case 1:
				{
					cout << "Запрос прямого итератора begin(): " << endl;
					cout << *Listt.begin() << endl << endl;
				}
				break;
				case 2:
				{
					try {
						cout << "Следующий" << endl;
						++it;
						cout << *it << endl;
					}
					catch (MyException& ex) {
						cerr << ex.what() << "\n";
					}
				}break;
				case 3:
				{
					try {
						cout << "Получить текущее значение" << endl;
						cout << *it << endl;
					}
					catch (MyException& ex) {
						cerr << ex.what() << "\n";
					}
				}break;
				case 4:
				{
					cout << "Проверка равенства итераторов" << endl;
					cout << "Результат: " << (it == Listt.end()) << endl;

				}break;
				case 5:
				{
					cout << "Проверка неравенства итераторов" << endl;
					cout << "Результат: " << (it != Listt.end()) << endl;

				}break;
				case 6:
				{
					exit1 = true;
				}
				break;
				}
				if (!exit1) {
					cout << "Операции итераторов\n\n";
					cout << "1. Запрос прямого итератора begin()\n";
					cout << "2. Следующий\n";
					cout << "3. Получить текущее значение\n";
					cout << "4. Проверка равенства итераторов\n";
					cout << "5. Проверка неравенства итераторов\n";
					cout << "6. Выход в главное меню\n";
					Listt.print();
					cout << "Введите пункт меню: ";
					cin >> number2;
				}
			}
		}
		break;
		case 12:
		{
			exit = true;
		}
		break;
		}
		if (!exit)
		{
			cout << "1.  Добавить новое значение в конец\n";
			cout << "2.  Добавить новое значение по номеру позиции\n";
			cout << "3.  Изменить значение с заданным номером\n";
			cout << "4.  Получить позицию в списке по значению\n";
			cout << "5.  Показать элемент по номеру в списке\n";
			cout << "6.  Наличие заданного значения\n";
			cout << "7.  Удаление из списка по значению\n";
			cout << "8.  Удаление значения по заданному номеру\n";
			cout << "9.  Проверка списка на пустоту\n";
			cout << "10. Очистка списка\n";
			cout << "11. Операции с итератором\n";
			cout << "12. Выход\n\n";

			cout << "Размер списка: " << Listt.get_capacity();
			cout << "\nКоличество элементов: " << Listt.get_size();
			cout << "\nСписок:\n";
			Listt.print();
			cout << "Введите пункт меню: ";
			cin >> number;
		}
	}
	return 0;
}

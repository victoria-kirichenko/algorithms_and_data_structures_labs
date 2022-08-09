#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <math.h>
#include "Header.h"
#define T int
#define G int
using namespace std;
void menu(Tree<T, G> test_tree);
void menu_iterator(Tree<T, G> test_tree);
void menu_r_iterator(Tree<T, G> test_tree);

typedef unsigned long long INT_64;
//переменная и константы генератора LineRand()
static INT_64 RRand = 15750; const INT_64 mRand = (1 << 63) - 1;
const INT_64 aRand = 6364136223846793005;
const INT_64 cRand = 1442695040888963407;
//функция установки первого случайного числа от часов
//компьютера
void sRand() { srand(time(0)); RRand = (INT_64)rand(); }
//функция генерации случайного числа
//линейный конгруэнтный генератор Xi+1=(a*Xi+c)%m
INT_64 LineRand()
{
    INT_64 y1, y2;
    y1 = (aRand * RRand + cRand) % mRand;
    y2 = (aRand * y1 + cRand) % mRand;
    RRand = y1 & 0xFFFFFFFF00000000LL ^ (y2 &
        0xFFFFFFFF00000000LL) >> 32;
    return RRand;
}
//Тест трудоёмкости операций случайного BST - дерева
void test_rand(int n)
{
    //создание дерева для 64 – разрядных ключей типа INT_64
    Tree< int, INT_64 > tree;
    //массив для ключей, которые присутствуют в дереве
    INT_64* m = new INT_64[n];
    //установка первого случайного числа
    sRand();
    //заполнение дерева и массива элементами
    //со случайными ключами
    for (int i = 0; i < n; i++)
    {
        m[i] = LineRand();
        tree.add(m[i], 1);
    }
    //вывод размера дерева до теста
    cout << "items count:" << tree.get_size() << endl;

    //обнуление счётчиков трудоёмкости вставки,
    //удаления и поиска
    double I = 0;
    double D = 0;
    double S = 0;
    //генерация потока операций, 10% - промахи операций
    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0) //10% промахов
        {
            tree.del(LineRand());
            D += tree.get_counter();
            tree.add(m[rand() % n], 1);
            I += tree.get_counter();
            try {
                tree.get_data(LineRand());
                S += tree.get_counter();
            }
            //обработка исключения при ошибке операции поиска
            catch (exception& ex) { S += tree.get_counter(); }
        }
        else //90% успешных операций
        {
            int ind = rand() % n;
            tree.del(m[ind]);
            D += tree.get_counter();
            INT_64 key = LineRand();
            tree.add(key, 1);
            I += tree.get_counter();
            m[ind] = key;
            try {
                tree.get_data(m[rand() % n]);
                S += tree.get_counter();
            }
            //обработка исключения при ошибке операции поиска
            catch (exception& ex) { S += tree.get_counter(); }
        } //конец теста
       //вывод результатов:
       //вывод размера дерева после теста
    cout << "items count:" << tree.get_size() << endl;
    //теоретической оценки трудоёмкости операций BST
    cout << "1.39*log2(n)=" << 1.39 * (log((double)n) / log(2.0)) << endl;
    //экспериментальной оценки трудоёмкости вставки
    cout << "Count insert: " << I / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости удаления
    cout << "Count delete: " << D / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости поиска
    cout << "Count search: " << S / (n / 2) << endl;
    //освобождение памяти массива m[]
    delete[] m;
}
//Тест трудоёмкости операций вырожденного BST - дерева
void test_ord(int n)
{
    //создание дерева для 64 – разрядных ключей типа INT_64
    Tree< int, INT_64 > tree;
    //массив для ключей, которые присутствуют в дереве
    INT_64* m = new INT_64[n];
    //заполнение дерева и массива элементами
    // с возрастающими чётными ключами
    //на интервале [0, 10000, 20000, ... ,10000*n]
    for (int i = 0; i < n; i++) {
        m[i] = i * 10000;
        tree.add(m[i], 1);
    }
    //вывод размера дерева до теста
    cout << "items count:" << tree.get_size() << endl;
    //обнуление счётчиков трудоёмкости вставки,
    // удаления и поиска
    double I = 0;
    double D = 0;
    double S = 0;
    //установка первого случайного числа
    sRand();
    //генерация потока операций, 10% - промахи операций
    for (int i = 0; i < n / 2; i++)
    {
        if (i % 10 == 0) //10% промахов
        {
            int k = LineRand() % (10000 * n);
            k = k + !(k % 2); //случайный нечётный ключ
            tree.del(k);
            D += tree.get_counter();
            tree.add(m[rand() % n], 1);
            I += tree.get_counter();
            k = LineRand() % (10000 * n);
            k = k + !(k % 2); // случайный нечётный ключ
            try {
                tree.get_data(k);
                S += tree.get_counter();
            }
            //обработка исключения при ошибке операции поиска
            catch (exception& ex) { S += tree.get_counter(); }
        }
        else //90% успешных операций
        {
            int ind = rand() % n;
            tree.del(m[ind]);
            D += tree.get_counter();;
            int k = LineRand() % (10000 * n);
            k = k + k % 2; // случайный чётный ключ
            tree.add(k, 1);
            I += tree.get_counter();;
            m[ind] = k;
            try {
                tree.get_data(m[rand() % n]);
                S += tree.get_counter();;
            }
            //обработка исключения при ошибке операции поиска
            catch (exception& ex) { S += tree.get_counter(); }
        }
    }
    //вывод результатов:
    // вывод размера дерева после теста
    cout << "items count:" << tree.get_size() << endl;
    //теоретической оценки трудоёмкости операций BST
    cout << "n/2 =" << n / 2 << endl;
    //экспериментальной оценки трудоёмкости вставки
    cout << "Count insert: " << I / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости удаления
    cout << "Count delete: " << D / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости поиска
    cout << "Count search: " << S / (n / 2) << endl;
    //освобождение памяти массива m[]
    delete[] m;
} //конец теста

int main()
{
    setlocale(LC_ALL, "Russian");
    Tree<T, G> test_tree;
    menu(test_tree);
    return 0;
}
void menu(Tree<T, G> test_tree)
{
    T val;
    G key;
    int punkt = -1;
    int n;
    while (punkt != 0)
    {
        cout << "..................................................................\n";
        cout <<
            "1) Опрос размера дерева\n2) Очистить дерево\n3) Проверка дерева на пустоту\n4) Получение данных по ключу\n"
            "5) Изменить данные по ключу\n6) Добавить элемент\n"
            "7) Удалить элемент по ключу\n8) Вертикальный вывод дерева ключ (кол-во эл-тов в поддереве)\n"
            "9) Формирование списка ключей в дереве в порядке обхода узлов по схеме t->Lt->Rt\n10) Определение порядкового номера элемента по ключу\n"
            "11) Меню итератора\n12) Меню обратного итератора\n13) Запустить тест трудоемкости операций случайного BST-дерева\n14) Запустить тест трудоемкости операций вырожденного BST-дерева\n";
        cout << "..................................................................\n";
        cin >> punkt;
        if (cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            cout << "Выберите другой вариант!\n";
            menu(test_tree);
        }
        cout << "...................................................................\n";
        switch (punkt)
        {
        case 1:
            cout << test_tree.get_size() << endl;
            break;
        case 2:
            test_tree.clear_tree();
            break;
        case 3:
            cout << test_tree.empty_check() << endl;
            break;
        case 4:
            cout << "Введите ключ элемента: ";
            try {
                cin >> key;
                if (cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    throw exception("");
                }
                cout << test_tree.get_data(key) << endl;
            }
            catch (exception& ex) {
                cout << "Исключение" << endl;
                menu(test_tree);
            }
            break;
        case 5:
            try {
                cout << "Введите ключ элемента: ";
                cin >> key;
                if (cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    throw exception("");
                }
                cout << "Введите новые данные: ";
                cin >> val;
                if (cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    throw exception("");
                }
                test_tree.get_data(key) = val;
            }
            catch (exception& ex) {
                cout << "Исключение" << endl;
                menu(test_tree);
            }
            break;
        case 6:
            try {
                cout << "Введите ключ: ";
                cin >> key;
                if (cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    throw exception("");
                }
                cout << "Введите данные: ";
                cin >> val;
                if (cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    throw exception("");
                }
            }
            catch (exception& ex) {
                cout << "Исключение" << endl;
                menu(test_tree);
            }
            cout << test_tree.add(key, val) << endl;
            break;
        case 7:
            try {
                cout << "Введите ключ элемента: ";
                cin >> key;
                if (cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    throw exception("");
                }
                cout << test_tree.del(key) << endl;
            }
            catch (exception& ex) {
                cout << "Исключение" << endl;
                menu(test_tree);
            }
            break;
        case 8:
            test_tree.print();
            break;
        case 9:
            test_tree.lists();
            break;
        case 10:
            cout << "Введите ключ элемента: ";
            try {
                cin >> key;
                if (cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    throw exception("");
                }
            }
            catch (exception& ex) {
                cout << "Исключение" << endl;
                menu(test_tree);
            }
            try {
                cout << test_tree.get_num(key) << endl;
            }
            catch (exception& ex) {
                cout << "Исключение" << endl;
                menu(test_tree);
            }
            break;
        case 11:
            menu_iterator(test_tree);
            break;
        case 12:
            menu_r_iterator(test_tree);
            break;
        case 13:
            cin >> n;
            test_rand(n);
            break;
        case 14:
            cin >> n;
            test_ord(n);
            break;
        case 0:
            exit(0);
            break;
        default:
            cout << "Выберите другой вариант!\n";
        }
    }
}

void menu_iterator(Tree<T, G> test_tree)
{
    T val;
    G key;
    int punkt = -1;
    Tree<T, G>::Iterator i = test_tree.begin();
    while (punkt != 0)
    {
        cout << "..................................................................\n";
        cout <<
            "1) Установить итератор на начало дерева\n2) Установить итератор на следующий элемент\n3) Проверить, установлен ли итератор\n"
            "4) Проверить, установлен ли итератор на начало\n5) Показать элемент\n"
            "6) Изменить элемент\n7) Установить итератор на предыдущий элемент\n8) Выйти из меню итератора\n";
        cout << "..................................................................\n";
        cin >> punkt;
        if (cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            cout << "Выберите другой вариант!\n";
            menu(test_tree);
        }
        cout << "..................................................................\n";
        switch (punkt)
        {
        case 1:
            cout << 1 << endl;
            i = test_tree.begin();
            break;
        case 2:
            try {
                ++i;
            }
            catch (exception& ex) {
                cout << "Исключение" << endl;
            }
            break;
        case 3:
            if (i != test_tree.end()) {
                cout << 1 << endl;
            }
            else {
                cout << 0 << endl;
            }
            break;
        case 4:
            if (i == test_tree.begin()) {
                cout << 1 << endl;
            }
            else {
                cout << 0 << endl;
            }
            break;
        case 5:
            try {
                cout << *i << endl;
            }
            catch (exception& ex) {
                cout << "Исключение" << endl;
            }
            break;
        case 6:
            cout << "Введите новое значение элемента: ";
            try {
                cin >> *i;
                if (cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    throw exception("");
                }
            }
            catch (exception& ex) {
                cout << "Исключение" << endl;
            }
            break;
        case 7:
            try {
                --i;
            }
            catch (exception& ex) {
                cout << "Исключение" << endl;
            }
            break;
        case 8:
            menu(test_tree);
            break;
        case 0:
            exit(0);
            break;
        default:
            cout << "Выберите другой вариант!\n";
        }
    }
}

void menu_r_iterator(Tree<T, G> test_tree)
{
    T val;
    G key;
    int punkt = -1;
    Tree<T, G>::R_iterator i = test_tree.rbegin();
    while (punkt != 0)
    {
        cout << ".................................................................\n";
        cout <<
            "1) Установить обратный итератор на конец дерева\n2) Установить обратный итератор на следующий элемент\n3) Проверить, установлен ли обратный итератор\n"
            "4) Проверить, установлен ли обратный итератор на конец\n5) Показать элемент\n"
            "6) Изменить элемент\n7) Установить обратный итератор на предыдущий элемент\n8) Выйти из меню обратного итератора\n";
        cout << ".................................................................\n";
        cin >> punkt;
        if (cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            cout << "Выберите другой вариант!\n";
            menu(test_tree);
        }
        cout << ".................................................................\n";
        switch (punkt)
        {
        case 1:
            cout << 1 << endl;
            i = test_tree.rbegin();
            break;
        case 2:
            try {
                ++i;
            }
            catch (exception& ex) {
                cout << "Исключение" << endl;
            }
            break;
        case 3:
            if (i != test_tree.rend()) {
                cout << 1 << endl;
            }
            else {
                cout << 0 << endl;
            }
            break;
        case 4:
            if (i == test_tree.rbegin()) {
                cout << 1 << endl;
            }
            else {
                cout << 0 << endl;
            }
            break;
        case 5:
            try {
                cout << *i << endl;
            }
            catch (exception& ex) {
                cout << "Исключение" << endl;
            }
            break;
        case 6:
            cout << "Введите новое значение элемента: ";
            try {
                cin >> *i;
                if (cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    throw exception("");
                }
            }
            catch (exception& ex) {
                cout << "Исключение" << endl;
            }
            break;
        case 7:
            try {
                --i;
            }
            catch (exception& ex) {
                cout << "Исключение" << endl;
            }
            break;
        case 8:
            menu(test_tree);
            break;
        case 0:
            exit(0);
            break;
        default:
            cout << "Выберите другой вариант!\n";
        }
    }
}
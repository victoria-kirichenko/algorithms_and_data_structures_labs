#pragma once

#include <time.h>
#include <math.h>
#include <iostream>
#include "BalanceTree.h"

using namespace std;

typedef unsigned long long INT_64;

//Генератор случайных чисел большой разрядности
//переменная и константы генератора LineRand()
static INT_64 RRand = 15750;
const INT_64 mRand = (1 << 63) - 1;
const INT_64 aRand = 6364136223846793005;
const INT_64 cRand = 1442695040888963407;

//функция установки первого случайного числа от часов компьютера
void sRand()
{
    srand(time(0));
    RRand = (INT_64)rand();
}

//функция генерации случайного числа
//линейный конгруэнтный генератор    Xi+1=(a*Xi+c)%m
//habr.com/ru/post/208178
INT_64 LineRand()
{
    INT_64 y1, y2;
    y1 = (aRand * RRand + cRand) % mRand;
    y2 = (aRand * y1 + cRand) % mRand;
    RRand = y1 & 0xFFFFFFFF00000000LL ^ (y2 & 0xFFFFFFFF00000000LL) >> 32;
    return RRand;
}

//тестирование случайного дерева вместе с балансированным
double* test_rand(int n)
{
    //создание дерева для 64 – разрядных ключей типа INT_64
    Tree< INT_64, int > tree;
    BalanceTree < INT_64, int > balanceTree;
    //массив для ключей, которые присутствуют в дереве 
    INT_64* m = new INT_64[n];
    //установка первого случайного числа
    sRand();

    //заполнение дерева и массива элементами со случайными ключами
    for (int i = 0; i < n; i++)
    {
        m[i] = LineRand();
        tree.add(m[i], 1);
        balanceTree.add(m[i], 1);
    }

    double* result = new double[12];
    result[0] = tree.getSize();
    result[6] = balanceTree.getSize();

    //обнуление счётчиков трудоёмкости вставки, удаления и поиска
    double I = 0;
    double D = 0;
    double S = 0;

    double bI = 0;
    double bD = 0;
    double bS = 0;

    //генерация потока операций, 10% - промахи операций
    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0)		//10% промахов
        {
            INT_64 randomValue = LineRand();

            tree.erase(randomValue);
            D += tree.getNodeCount();
            balanceTree.erase(randomValue);
            bD += balanceTree.getNodeCount();

            randomValue = m[rand() % n];

            tree.add(randomValue, 1);
            I += tree.getNodeCount();
            balanceTree.add(randomValue, 1);
            bI += balanceTree.getNodeCount();

            randomValue = LineRand();
            try
            {
                tree.getDataByKey(randomValue);
                S += tree.getNodeCount();
            }
            //обработка исключения при ошибке операции поиска
            catch (const exception& exc)
            {
                S += tree.getNodeCount();
            }

            try
            {
                balanceTree.getDataByKey(randomValue);
                bS += balanceTree.getNodeCount();
            }
            //обработка исключения при ошибке операции поиска
            catch (const exception& exc)
            {
                bS += balanceTree.getNodeCount();
            }
        }
        else  //90% успешных операций
        {
            int ind = rand() % n;

            tree.erase(m[ind]);
            D += tree.getNodeCount();
            balanceTree.erase(m[ind]);
            bD += balanceTree.getNodeCount();

            INT_64 key = LineRand();

            tree.add(key, 1);
            I += tree.getNodeCount();
            balanceTree.add(key, 1);
            bI += balanceTree.getNodeCount();

            m[ind] = key;

            INT_64 randomValue = m[rand() % n];

            try
            {
                tree.getDataByKey(randomValue);
                S += tree.getNodeCount();
            }
            //обработка исключения при ошибке операции поиска
            catch (const exception& exc)
            {
                S += tree.getNodeCount();
            }

            try
            {
                balanceTree.getDataByKey(randomValue);
                bS += balanceTree.getNodeCount();
            }
            //обработка исключения при ошибке операции поиска
            catch (const exception& exc)
            {
                bS += balanceTree.getNodeCount();
            }
        }	//конец теста

    //освобождение памяти массива m[]
    delete[] m;

    result[1] = tree.getSize();
    result[2] = 1.39 * (log((double)n) / log(2.0));
    result[3] = I / (((double)n) / 2);
    result[4] = D / (((double)n) / 2);
    result[5] = S / (((double)n) / 2);

    result[7] = balanceTree.getSize();
    result[8] = (log((double)n) / log(2.0)) + 0.25;
    result[9] = bI / (((double)n) / 2);
    result[10] = bD / (((double)n) / 2);
    result[11] = bS / (((double)n) / 2);

    return result;
}

//тестирование вырожденного дерева
double* test_ord(int n)
{
    //создание дерева для 64 – разрядных ключей типа INT_64
    Tree<INT_64, int > tree;
    BalanceTree < INT_64, int > balanceTree;
    //массив для ключей, которые присутствуют в дереве 
    INT_64* m = new INT_64[n];

    //заполнение дерева и массива элементами с возрастающими чётными //ключами на интервале [0, 10000, 20000, ... ,10000*n]
    for (int i = 0; i < n; i++)
    {
        m[i] = i * 10000;
        tree.add(m[i], 1);
        balanceTree.add(m[i], 1);
    }

    double* result = new double[12];
    result[0] = tree.getSize();
    result[6] = balanceTree.getSize();

    //обнуление счётчиков трудоёмкости вставки, удаления и поиска
    double I = 0;
    double D = 0;
    double S = 0;

    double bI = 0;
    double bD = 0;
    double bS = 0;

    //установка первого случайного числа 
    sRand();
    //генерация потока операций, 10% - промахи операций
    for (int i = 0; i < n / 2; i++)
    {
        if (i % 10 == 0)		//10% промахов
        {
            int k = LineRand() % (10000 * n);
            k = k + !(k % 2);	//случайный нечётный ключ

            tree.erase(k);
            balanceTree.erase(k);
            D += tree.getNodeCount();
            bD += balanceTree.getNodeCount();

            INT_64 randomValue = m[rand() % n];

            tree.add(randomValue, 1);
            balanceTree.add(randomValue, 1);
            I += tree.getNodeCount();
            bI += balanceTree.getNodeCount();

            k = LineRand() % (10000 * n);
            k = k + !(k % 2);	// случайный нечётный ключ

            try
            {
                tree.getDataByKey(k);
                S += tree.getNodeCount();
            }
            //обработка исключения при ошибке операции поиска
            catch (const exception& exc)
            {
                S += tree.getNodeCount();
            }

            try
            {
                balanceTree.getDataByKey(k);
                bS += balanceTree.getNodeCount();
            }
            //обработка исключения при ошибке операции поиска
            catch (const exception& exc)
            {
                bS += balanceTree.getNodeCount();
            }
        }
        else  //90% успешных операций
        {
            int ind = rand() % n;

            tree.erase(m[ind]);
            D += tree.getNodeCount();
            balanceTree.erase(m[ind]);
            bD += balanceTree.getNodeCount();

            int k = LineRand() % (10000 * n);
            k = k + k % 2;		// случайный чётный ключ

            tree.add(k, 1);
            I += tree.getNodeCount();
            balanceTree.add(k, 1);
            bI += balanceTree.getNodeCount();

            m[ind] = k;

            INT_64 randomValue = m[rand() % n];

            try
            {
                tree.getDataByKey(randomValue);
                S += tree.getNodeCount();
            }
            //обработка исключения при ошибке операции поиска
            catch (const exception& exc)
            {
                S += tree.getNodeCount();
            }

            try
            {
                balanceTree.getDataByKey(randomValue);
                bS += balanceTree.getNodeCount();
            }
            //обработка исключения при ошибке операции поиска
            catch (const exception& exc)
            {
                bS += balanceTree.getNodeCount();
            }
        }
    }

    result[1] = tree.getSize();
    result[2] = ((double)n) / 2;
    result[3] = I / (((double)n) / 2);
    result[4] = D / (((double)n) / 2);
    result[5] = S / (((double)n) / 2);

    result[7] = balanceTree.getSize();
    result[8] = (log((double)n) / log(2.0)) + 0.25;
    result[9] = bI / (((double)n) / 2);
    result[10] = bD / (((double)n) / 2);
    result[11] = bS / (((double)n) / 2);

    //освобождение памяти массива m[]
    delete[] m;

    return result;
}	//конец теста



void testShell()
{
    int experiment_count = 10;
    int max_n = 1000;

  /*  cout << "Оценки трудоемкости для случайного дерева: " << endl;
    for (int i = 10; i <= max_n; i *= 10)
    {
        double* mid_results = new double[12];
        for (int j = 0; j < 12; j++)
            mid_results[j] = 0;

        for (int j = 0; j < experiment_count; j++)
        {
            double* temp_results = test_rand(i);

            for (int k = 0; k < 12; k++)
                mid_results[k] += temp_results[k];

            delete[] temp_results;
        }

        for (int k = 0; k < 12; k++)
            mid_results[k] /= experiment_count;

        cout << "Результаты для n = " << i << " : " << endl;
        cout << "BST-дерево:" << endl;
        cout << "Количество элементов перед началом эксперимента: " << mid_results[0] << endl;
        cout << "Количество элементов в конце эксперимента: " << mid_results[1] << endl;
        cout << "Теоретическая оценка: 1.39 * log2(n) = " << mid_results[2] << endl;
        cout << "Экспериментальная оценка трудоемкости вставки: " << mid_results[3] << endl;
        cout << "Экспериментальная оценка трудоемкости удаления: " << mid_results[4] << endl;
        cout << "Экспериментальная оценка трудоемкости поиска: " << mid_results[5] << endl;
        cout << "AVL-дерево:" << endl;
        cout << "Количество элементов перед началом эксперимента: " << mid_results[6] << endl;
        cout << "Количество элементов в конце эксперимента: " << mid_results[7] << endl;
        cout << "Теоретическая оценка: log2(n)+0.25 = " << mid_results[8] << endl;
        cout << "Экспериментальная оценка трудоемкости вставки: " << mid_results[9] << endl;
        cout << "Экспериментальная оценка трудоемкости удаления: " << mid_results[10] << endl;
        cout << "Экспериментальная оценка трудоемкости поиска: " << mid_results[11] << endl;
        cout << "---------------------" << endl;
        delete[] mid_results;
    }

    cout << endl;
    cout << "******************************" << endl;
    cout << endl;*/

    cout << "Оценки трудоемкости для вырожденного дерева: " << endl;
    for (int i = max_n; i <= max_n; i *= 10)
    {
        double* mid_results = new double[12];
        for (int j = 0; j < 12; j++)
            mid_results[j] = 0;

        for (int j = 0; j < experiment_count; j++)
        {
            double* temp_results = test_ord(i);

            for (int k = 0; k < 12; k++)
                mid_results[k] += temp_results[k];

            delete[] temp_results;
        }

        for (int k = 0; k < 12; k++)
            mid_results[k] /= experiment_count;

        cout << "Результаты для n = " << i << " : " << endl;
        cout << "BST-дерево:" << endl;
        cout << "Количество элементов перед началом эксперимента: " << mid_results[0] << endl;
        cout << "Количество элементов в конце эксперимента: " << mid_results[1] << endl;
        cout << "Теоретическая оценка: n/2 = " << mid_results[2] << endl;
        cout << "Экспериментальная оценка трудоемкости вставки: " << mid_results[3] << endl;
        cout << "Экспериментальная оценка трудоемкости удаления: " << mid_results[4] << endl;
        cout << "Экспериментальная оценка трудоемкости поиска: " << mid_results[5] << endl;
        cout << "AVL-дерево:" << endl;
        cout << "Количество элементов перед началом эксперимента: " << mid_results[6] << endl;
        cout << "Количество элементов в конце эксперимента: " << mid_results[7] << endl;
        cout << "Теоретическая оценка: log2(n)+0.25 = " << mid_results[8] << endl;
        cout << "Экспериментальная оценка трудоемкости вставки: " << mid_results[9] << endl;
        cout << "Экспериментальная оценка трудоемкости удаления: " << mid_results[10] << endl;
        cout << "Экспериментальная оценка трудоемкости поиска: " << mid_results[11] << endl;
        cout << "---------------------" << endl;
        delete[] mid_results;
    }
}
//#pragma once
//#include <iostream>
//#include <time.h>
//#include <math.h>
//#include "Header.h"
//using namespace std;
//
//typedef unsigned long long INT_64;
////���������� � ��������� ���������� LineRand()
//static INT_64 RRand = 15750; const INT_64 mRand = (1 << 63) - 1;
//const INT_64 aRand = 6364136223846793005;
//const INT_64 cRand = 1442695040888963407;
////������� ��������� ������� ���������� ����� �� �����
////����������
//void sRand() { srand(time(0)); RRand = (INT_64)rand(); }
////������� ��������� ���������� �����
////�������� ������������ ��������� Xi+1=(a*Xi+c)%m
//INT_64 LineRand()
//{
//    INT_64 y1, y2;
//    y1 = (aRand * RRand + cRand) % mRand;
//    y2 = (aRand * y1 + cRand) % mRand;
//    RRand = y1 & 0xFFFFFFFF00000000LL ^ (y2 &
//        0xFFFFFFFF00000000LL) >> 32;
//    return RRand;
//}
////���� ����������� �������� ���������� BST - ������
//void test_rand(int n)
//{
//    //�������� ������ ��� 64 � ��������� ������ ���� INT_64
//    Tree< int, INT_64 > tree;
//    //������ ��� ������, ������� ������������ � ������
//    INT_64* m = new INT_64[n];
//    //��������� ������� ���������� �����
//    sRand();
//    //���������� ������ � ������� ����������
//    //�� ���������� �������
//    for (int i = 0; i < n; i++)
//    {
//        m[i] = LineRand();
//        tree.add(m[i], 1);
//    }
//    //����� ������� ������ �� �����
//    cout << "items count:" << tree.get_size() << endl;
//
//    //��������� ��������� ����������� �������,
//    //�������� � ������
//    double I = 0;
//    double D = 0;
//    double S = 0;
//    //��������� ������ ��������, 10% - ������� ��������
//    for (int i = 0; i < n / 2; i++)
//        if (i % 10 == 0) //10% ��������
//        {
//            tree.del(LineRand());
//            D += tree.get_counter();
//            tree.add(m[rand() % n], 1);
//            I += tree.get_counter();
//            try {
//                tree.get_data(LineRand());
//                S += tree.get_counter();
//            }
//            //��������� ���������� ��� ������ �������� ������
//            catch (exception& ex) { S += tree.get_counter(); }
//        }
//        else //90% �������� ��������
//        {
//            int ind = rand() % n;
//            tree.del(m[ind]);
//            D += tree.get_counter();
//            INT_64 key = LineRand();
//            tree.add(key, 1);
//            I += tree.get_counter();
//            m[ind] = key;
//            try {
//                tree.get_data(m[rand() % n]);
//                S += tree.get_counter();
//            }
//            //��������� ���������� ��� ������ �������� ������
//            catch (exception& ex) { S += tree.get_counter(); }
//        } //����� �����
//       //����� �����������:
//       //����� ������� ������ ����� �����
//    cout << "items count:" << tree.get_size() << endl;
//    //������������� ������ ����������� �������� BST
//    cout << "1.39*log2(n)=" << 1.39 * (log((double)n) / log(2.0)) << endl;
//    //����������������� ������ ����������� �������
//    cout << "Count insert: " << I / (n / 2) << endl;
//    //����������������� ������ ����������� ��������
//    cout << "Count delete: " << D / (n / 2) << endl;
//    //����������������� ������ ����������� ������
//    cout << "Count search: " << S / (n / 2) << endl;
//    //������������ ������ ������� m[]
//    delete[] m;
//}
////���� ����������� �������� ������������ BST - ������
//void test_ord(int n)
//{
//    //�������� ������ ��� 64 � ��������� ������ ���� INT_64
//    Tree< int, INT_64 > tree;
//    //������ ��� ������, ������� ������������ � ������
//    INT_64* m = new INT_64[n];
//    //���������� ������ � ������� ����������
//    // � ������������� ������� �������
//    //�� ��������� [0, 10000, 20000, ... ,10000*n]
//    for (int i = 0; i < n; i++) {
//        m[i] = i * 10000;
//        tree.add(m[i], 1);
//    }
//    //����� ������� ������ �� �����
//    cout << "items count:" << tree.get_size() << endl;
//    //��������� ��������� ����������� �������,
//    // �������� � ������
//    double I = 0;
//    double D = 0;
//    double S = 0;
//    //��������� ������� ���������� �����
//    sRand();
//    //��������� ������ ��������, 10% - ������� ��������
//    for (int i = 0; i < n / 2; i++)
//    {
//        if (i % 10 == 0) //10% ��������
//        {
//            int k = LineRand() % (10000 * n);
//            k = k + !(k % 2); //��������� �������� ����
//            tree.del(k);
//            D += tree.get_counter();
//            tree.add(m[rand() % n], 1);
//            I += tree.get_counter();
//            k = LineRand() % (10000 * n);
//            k = k + !(k % 2); // ��������� �������� ����
//            try {
//                tree.get_data(k);
//                S += tree.get_counter();
//            }
//            //��������� ���������� ��� ������ �������� ������
//            catch (exception& ex) { S += tree.get_counter(); }
//        }
//        else //90% �������� ��������
//        {
//            int ind = rand() % n;
//            tree.del(m[ind]);
//            D += tree.get_counter();;
//            int k = LineRand() % (10000 * n);
//            k = k + k % 2; // ��������� ������ ����
//            tree.add(k, 1);
//            I += tree.get_counter();;
//            m[ind] = k;
//            try {
//                tree.get_data(m[rand() % n]);
//                S += tree.get_counter();;
//            }
//            //��������� ���������� ��� ������ �������� ������
//            catch (exception& ex) { S += tree.get_counter(); }
//        }
//    }
//    //����� �����������:
//    // ����� ������� ������ ����� �����
//    cout << "items count:" << tree.get_size() << endl;
//    //������������� ������ ����������� �������� BST
//    cout << "n/2 =" << n / 2 << endl;
//    //����������������� ������ ����������� �������
//    cout << "Count insert: " << I / (n / 2) << endl;
//    //����������������� ������ ����������� ��������
//    cout << "Count delete: " << D / (n / 2) << endl;
//    //����������������� ������ ����������� ������
//    cout << "Count search: " << S / (n / 2) << endl;
//    //������������ ������ ������� m[]
//    delete[] m;
//} //����� �����
//
////int main()
////{
////    int n = 500;
////    test_rand(n);
////    cout << "----------------------------------------------------------------------" << endl;
////    test_ord(n);
////}

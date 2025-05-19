﻿//ex14_2.cpp
//реализует очередь как шаблон
#include <iostream>
using namespace std;
const int MAX = 3;
template <class Type>
class Queue
{
private:
	Type qu[MAX]; //массив произвольного типа
	int head; //индекс начала очереди (отсюда — удаление элементов)
	int tail; //индекс хвоста очереди (сюда вставлять
	//новые элементы)

public:
	Queue() //конструктор
	{
		head = -1;tail = -1;
	}
	void put(Type var) //вставка элемента в хвост
	{
		qu[++tail] = var;
		if (tail >= MAX - 1)//зациклить хвост
			tail = -1;
	}
	Type get() //удаление элемента из начала
	{
		Type temp = qu[++head];//сохранение элемента
		if (head >= MAX - 1) //зациклить начало
			head = -1;
		return temp; //вернуть временное значение
	}
};
int main()
{
	Queue<float>q1; //q1 – объект класса Queue<float>
	q1.put(1111.1F); //занести 3
	q1.put(2222.2F);
	q1.put(3333.3F);
	cout << "1:" << q1.get() << endl; //получить 2
	cout << "2:" << q1.get() << endl;
	q1.put(4444.4F); //занести 2
	q1.put(5555.5F);
	cout << "3:" << q1.get() << endl; //получить 1
	q1.put(6666.6F); //занести 1
	cout << "4:" << q1.get() << endl; //получить 3
	cout << "5:" << q1.get() << endl;
	cout << "6:" << q1.get() << endl;
	Queue<long>q2; //q2 – объект класса Queue<long>
	q2.put(123123123L);//занести 3 (long), получить 2
	q2.put(234234234L);
	q2.put(345345345L);
	cout << "1:" << q2.get() << endl;
	cout << "2:" << q2.get() << endl;
	cout << "3:" << q2.get() << endl;
	return 0;
}
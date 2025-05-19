// ex14_4.cpp
// Шаблон функции swaps() для обмена значений двух аргументов
#include <iostream>
using namespace std;

// Шаблон функции swaps()
template <class T>
void swaps(T& a, T& b) {
    T temp = a; // Сохраняем значение a во временной переменной
    a = b;      // Присваиваем a значение b
    b = temp;   // Присваиваем b сохранённое значение a
}

int main() {
    setlocale(LC_ALL, "ru"); // Поддержка русской локализации

    // Тестирование с типом int
    int x1 = 10, y1 = 20;
    cout << "До обмена (int): x1 = " << x1 << ", y1 = " << y1 << endl;
    swaps(x1, y1);
    cout << "После обмена (int): x1 = " << x1 << ", y1 = " << y1 << endl;

    // Тестирование с типом float
    float x2 = 3.14f, y2 = 2.718f;
    cout << "\nДо обмена (float): x2 = " << x2 << ", y2 = " << y2 << endl;
    swaps(x2, y2);
    cout << "После обмена (float): x2 = " << x2 << ", y2 = " << y2 << endl;

    // Тестирование с типом char
    char x3 = 'A', y3 = 'B';
    cout << "\nДо обмена (char): x3 = " << x3 << ", y3 = " << y3 << endl;
    swaps(x3, y3);
    cout << "После обмена (char): x3 = " << x3 << ", y3 = " << y3 << endl;

    // Тестирование с типом double
    double x4 = 1.234, y4 = 5.678;
    cout << "\nДо обмена (double): x4 = " << x4 << ", y4 = " << y4 << endl;
    swaps(x4, y4);
    cout << "После обмена (double): x4 = " << x4 << ", y4 = " << y4 << endl;

    return 0;
}
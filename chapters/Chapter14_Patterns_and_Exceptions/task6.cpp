// ex14_6.cpp
// Шаблонный класс safearray с безопасным доступом к массиву
#include <iostream>
using namespace std;
#include <process.h> // для функции exit

const int LIMIT = 100; // размер массива

template <class T>
class safearray {
private:
    T arr[LIMIT]; // массив произвольного типа T
public:
    // Оператор [] возвращает ссылку для чтения и записи
    T& operator[](int n) {
        if (n < 0 || n >= LIMIT) {
            cout << "\nОшибочный индекс!" << endl;
            exit(1);
        }
        return arr[n];
    }
};

int main() {
    setlocale(LC_ALL, "ru"); // Поддержка русской локализации

    // Тестирование с массивом типа int
    safearray<int> sa1;
    // Заполнение массива значениями
    for (int j = 0; j < LIMIT; j++) {
        sa1[j] = j * 10; // Присваивание через оператор []
    }
    // Вывод первых 5 элементов для краткости
    cout << "Массив int:" << endl;
    for (int j = 0; j < 5; j++) {
        int temp = sa1[j]; // Чтение через оператор []
        cout << "Элемент " << j << " равен " << temp << endl;
    }

    // Тестирование с массивом типа double
    safearray<double> sa2;
    // Заполнение массива значениями
    for (int j = 0; j < LIMIT; j++) {
        sa2[j] = j * 1.5; // Присваивание через оператор []
    }
    // Вывод первых 5 элементов для краткости
    cout << "\nМассив double:" << endl;
    for (int j = 0; j < 5; j++) {
        double temp = sa2[j]; // Чтение через оператор []
        cout << "Элемент " << j << " равен " << temp << endl;
    }

    // Тестирование некорректного индекса (для демонстрации)
    cout << "\nПопытка доступа к некорректному индексу:" << endl;
    // sa1[100]; // Раскомментировать для проверки ошибки

    return 0;
}
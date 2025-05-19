// ex14_8.cpp
// Класс safearray с обработкой исключений для некорректных индексов
#include <iostream>
#include <process.h> // для функции exit
using namespace std;

const int LIMIT = 100; // размер массива

class safearray {
private:
    int arr[LIMIT]; // массив фиксированного размера

public:
    // Класс исключения для некорректного индекса
    class IndexError {
    public:
        int index; // индекс, вызвавший ошибку
        IndexError(int n) : index(n) {}
    };

    // Установка значения элемента массива
    void putel(int n, int elvalue) {
        if (n < 0 || n >= LIMIT) {
            throw IndexError(n); // Генерируем исключение
        }
        arr[n] = elvalue;
    }

    // Получение значения элемента массива
    int getel(int n) const {
        if (n < 0 || n >= LIMIT) {
            throw IndexError(n); // Генерируем исключение
        }
        return arr[n];
    }
};

int main() {
    setlocale(LC_ALL, "ru"); // Поддержка русской локализации
    safearray sa1;

    // Заполнение массива
    try {
        for (int j = 0; j < LIMIT; j++) {
            sa1.putel(j, j * 10); // Устанавливаем значения
        }
    }
    catch (safearray::IndexError& e) {
        cout << "Ошибка: Некорректный индекс " << e.index << "!" << endl;
        return 1;
    }

    // Вывод элементов
    try {
        cout << "Элементы массива:" << endl;
        for (int j = 0; j < 5; j++) { // Выводим первые 5 элементов для краткости
            int temp = sa1.getel(j);
            cout << "Элемент " << j << " равен " << temp << endl;
        }

        // Тестирование некорректного индекса
        cout << "\nПопытка доступа к некорректному индексу:" << endl;
        int temp = sa1.getel(LIMIT); // Должно вызвать исключение
    }
    catch (safearray::IndexError& e) {
        cout << "Ошибка: Некорректный индекс " << e.index << "!" << endl;
    }

    return 0;
}
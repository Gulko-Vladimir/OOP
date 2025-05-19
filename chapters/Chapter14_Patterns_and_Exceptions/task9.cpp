// ex14_9.cpp
// Класс safearray с обработкой исключений и информативными сообщениями об ошибке
#include <iostream>
#include <process.h> // для функции exit
#include <string>    // для std::string
using namespace std;

const int LIMIT = 100; // размер массива

class safearray {
private:
    int arr[LIMIT]; // массив фиксированного размера

public:
    // Класс исключения для некорректного индекса
    class IndexError {
    public:
        int index;           // индекс, вызвавший ошибку
        string method;       // метод, вызвавший исключение
        IndexError(int n, const string& m) : index(n), method(m) {}
    };

    // Установка значения элемента массива
    void putel(int n, int elvalue) {
        if (n < 0 || n >= LIMIT) {
            throw IndexError(n, "putel"); // Генерируем исключение с указанием метода
        }
        arr[n] = elvalue;
    }

    // Получение значения элемента массива
    int getel(int n) const {
        if (n < 0 || n >= LIMIT) {
            throw IndexError(n, "getel"); // Генерируем исключение с указанием метода
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
        cout << "Ошибка в методе " << e.method << ": Некорректный индекс " << e.index << "!" << endl;
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
        cout << "Ошибка в методе " << e.method << ": Некорректный индекс " << e.index << "!" << endl;
    }

    return 0;
}
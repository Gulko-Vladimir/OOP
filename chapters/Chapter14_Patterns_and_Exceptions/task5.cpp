// ex14_5.cpp
// Шаблон функции amax() для нахождения максимального элемента массива
#include <iostream>
using namespace std;

// Шаблон функции amax()
template <class T>
T amax(T* array, int size) {
    if (size <= 0) {
        return T(); // Возвращаем значение по умолчанию для типа T при неверном размере
    }
    T max = array[0]; // Инициализируем максимум первым элементом
    for (int i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i]; // Обновляем максимум, если текущий элемент больше
        }
    }
    return max;
}

int main() {
    setlocale(LC_ALL, "ru"); // Поддержка русской локализации

    // Тестирование с массивом типа int
    int intArray[] = { 4, 2, 9, 7, 5, 6 };
    cout << "Максимум в intArray: " << amax(intArray, 6) << endl;

    // Тестирование с массивом типа float
    float floatArray[] = { 3.14f, 2.718f, 1.414f, 9.8f };
    cout << "Максимум в floatArray: " << amax(floatArray, 4) << endl;

    // Тестирование с массивом типа double
    double doubleArray[] = { 1.234, 5.678, 3.333, 9.999 };
    cout << "Максимум в doubleArray: " << amax(doubleArray, 4) << endl;

    // Тестирование с массивом типа char
    char charArray[] = { 'A', 'Z', 'B', 'Y' };
    cout << "Максимум в charArray: " << amax(charArray, 4) << endl;

    return 0;
}
// ex14_10.cpp
// Класс Distance с обработкой ошибок ввода через исключения
#include <iostream>
#include <string>
#include <cstdlib> // для atoi(), atof()
using namespace std;

// Класс исключения для ошибок ввода расстояния
class DistanceError {
public:
    string message; // Причина ошибки
    DistanceError(const string& msg) : message(msg) {}
};

// Функция проверки строки футов (независимая)
int isFeet(const string& str) {
    int slen = str.size();
    if (slen == 0) {
        throw DistanceError("Пустой ввод футов");
    }
    if (slen > 5) {
        throw DistanceError("Слишком длинный ввод футов (>5 символов)");
    }
    for (int j = 0; j < slen; j++) {
        if ((str[j] < '0' || str[j] > '9') && str[j] != '-') {
            throw DistanceError("Футы должны содержать только цифры или минус");
        }
    }
    double n = atof(str.c_str());
    if (n < -999.0 || n > 999.0) {
        throw DistanceError("Футы должны быть в диапазоне -999..999");
    }
    return 1; // Корректный ввод
}

class Distance {
private:
    int feet;
    float inches;

public:
    Distance() : feet(0), inches(0.0) {} // Конструктор по умолчанию

    Distance(int ft, float in) : feet(ft), inches(in) { // Конструктор с аргументами
        if (ft < -999 || ft > 999) {
            throw DistanceError("Футы в конструкторе вне диапазона -999..999");
        }
        if (in < 0.0 || in >= 12.0) {
            throw DistanceError("Дюймы в конструкторе вне диапазона [0.0, 12.0)");
        }
    }

    void showdist() const { // Вывод расстояния
        cout << feet << "\'-" << inches << '\"';
    }

    void getdist() { // Запрос расстояния у пользователя
        string instr;
        cout << "\n\nВведите футы: ";
        cin.unsetf(ios::skipws);
        cin >> instr;
        if (!isFeet(instr)) { // isFeet() теперь кидает исключение, эта ветка не нужна
            cin.ignore(10, '\n');
        }
        cin.ignore(10, '\n');
        feet = atoi(instr.c_str());

        cout << "Введите дюймы: ";
        cin.unsetf(ios::skipws);
        cin >> inches;
        if (inches < 0.0 || inches >= 12.0) {
            throw DistanceError("Дюймы должны быть в диапазоне [0.0, 12.0)");
        }
        if (!cin.good()) {
            cin.clear();
            cin.ignore(10, '\n');
            throw DistanceError("Неверный формат дюймов (не число)");
        }
        cin.ignore(10, '\n');
    }
};

int main() {
    setlocale(LC_ALL, "ru"); // Поддержка русской локализации
    Distance d;
    char ans;

    do {
        try {
            d.getdist(); // Запрос расстояния
            cout << "\nРасстояние = ";
            d.showdist();
            cout << "\nЕще раз (y/n)? ";
            cin >> ans;
            cin.ignore(10, '\n');
        }
        catch (const DistanceError& e) {
            cout << "Ошибка: " << e.message << endl;
            cout << "Попробуйте ввести данные снова." << endl;
            cin.clear();
            cin.ignore(10, '\n');
            continue; // Повторяем цикл для нового ввода
        }
    } while (ans != 'n');

    // Тестирование конструктора
    try {
        cout << "\nТестирование конструктора с некорректными данными:" << endl;
        Distance d2(1000, 5.0); // Должно вызвать исключение
    }
    catch (const DistanceError& e) {
        cout << "Ошибка в конструкторе: " << e.message << endl;
    }

    return 0;
}
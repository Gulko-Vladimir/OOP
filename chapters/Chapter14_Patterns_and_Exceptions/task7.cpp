// ex14_7.cpp
// Шаблонный класс fraction для работы с дробями целочисленных типов
#include <iostream>
#include <cstdlib> // для abs и exit
using namespace std;

template <class T>
class fraction {
private:
    T num; // числитель
    T den; // знаменатель

public:
    // Конструктор по умолчанию
    fraction() : num(0), den(1) {}

    // Конструктор с двумя аргументами
    fraction(T n, T d) : num(n), den(d) {
        if (d == 0) {
            cout << "Недопустимый знаменатель!" << endl;
            exit(1);
        }
    }

    // Метод ввода дроби
    void input() {
        char dummy;
        cout << "Введите дробь (a/b): ";
        cin >> num >> dummy >> den;
        if (den == 0) {
            cout << "Недопустимый знаменатель!" << endl;
            exit(1);
        }
        *this = lowterms(); // Сокращаем дробь после ввода
    }

    // Метод вывода дроби
    void display() const {
        cout << static_cast<int>(num) << "/" << static_cast<int>(den);
    }

    // Перегрузка операторов арифметики
    fraction operator+(const fraction& f) const {
        fraction result;
        result.num = num * f.den + den * f.num;
        result.den = den * f.den;
        return result.lowterms();
    }

    fraction operator-(const fraction& f) const {
        fraction result;
        result.num = num * f.den - den * f.num;
        result.den = den * f.den;
        return result.lowterms();
    }

    fraction operator*(const fraction& f) const {
        fraction result;
        result.num = num * f.num;
        result.den = den * f.den;
        return result.lowterms();
    }

    fraction operator/(const fraction& f) const {
        fraction result;
        if (f.num == 0) {
            cout << "Ошибка: деление на ноль!" << endl;
            exit(1);
        }
        result.num = num * f.den;
        result.den = den * f.num;
        return result.lowterms();
    }

    // Перегрузка операторов сравнения
    bool operator==(const fraction& f) const {
        fraction temp1 = *this;
        fraction temp2 = f;
        temp1 = temp1.lowterms();
        temp2 = temp2.lowterms();
        return temp1.num == temp2.num && temp1.den == temp2.den;
    }

    bool operator!=(const fraction& f) const {
        return !(*this == f);
    }

    // Модифицированная функция lowterms
    fraction lowterms() const {
        fraction result = *this;
        T tnum, tden, temp, gcd;
        tnum = abs(result.num); // Используем abs вместо labs
        tden = abs(result.den);

        if (tden == 0) {
            cout << "Недопустимый знаменатель!" << endl;
            exit(1);
        }
        else if (tnum == 0) {
            result.num = 0;
            result.den = 1;
            return result;
        }

        while (tnum != 0) {
            if (tnum < tden) {
                temp = tnum;
                tnum = tden;
                tden = temp;
            }
            tnum = tnum - tden;
        }
        gcd = tden;
        result.num = result.num / gcd;
        result.den = result.den / gcd;

        // Убедимся, что знаменатель положительный
        if (result.den < 0) {
            result.num = -result.num;
            result.den = -result.den;
        }
        return result;
    }
};

int main() {
    setlocale(LC_ALL, "ru"); // Поддержка русской локализации
    char continueCalc = 'n';
    fraction<char> zero_one(0, 1); // Для сравнения с 0/1

    do {
        fraction<char> f1, f2, result;
        char op;

        // Ввод первой дроби
        f1.input();
        // Проверка на 0/1
        if (f1 == zero_one) {
            cout << "Программа завершена (введено 0/1)" << endl;
            break;
        }

        // Ввод операции
        cout << "Введите операцию (+, -, *, /):";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> op;

        // Ввод второй дроби
        f2.input();
        // Проверка на 0/1
        if (f2 == zero_one) {
            cout << "Программа завершена (введено 0/1)" << endl;
            break;
        }

        // Выполнение операции
        bool validOp = true;
        switch (op) {
        case '+':
            result = f1 + f2;
            break;
        case '-':
            result = f1 - f2;
            break;
        case '*':
            result = f1 * f2;
            break;
        case '/':
            result = f1 / f2;
            break;
        default:
            cout << "Ошибка: неверная операция!" << endl;
            validOp = false;
            continue;
        }

        if (validOp) {
            // Вывод результата
            cout << "Результат: ";
            result.display();
            cout << endl;
        }

        // Запрос на продолжение
        cout << "Хотите выполнить еще одну операцию? (y/n):";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> continueCalc;
    } while (continueCalc == 'y' || continueCalc == 'Y');

    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h> // для strcpy, strcat, strlen
#include <stdlib.h> // для exit
#include <string>   // для std::string в исключении
using namespace std;

class String {
private:
    enum { SZ = 80 };
    char str[SZ];

public:
    class StringError {
    public:
        string message;
        StringError(const string& msg) : message(msg) {}
    };

    String() {
        strcpy(str, "");
    }

    // ✅ конструктор принимает const char[]
    String(const char s[]) {
        if (strlen(s) >= SZ) {
            throw StringError("Слишком длинная строка в конструкторе");
        }
        strcpy(str, s);
    }

    void display() const {
        cout << str;
    }

    String operator+(const String& ss) const {
        String temp;
        if (strlen(str) + strlen(ss.str) >= SZ) {
            throw StringError("Переполнение при конкатенации строк");
        }
        strcpy(temp.str, str);
        strcat(temp.str, ss.str);
        return temp;
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    try {
        String s1 = "\nС Рождеством! ";
        String s2 = "С Новым годом!";
        String s3;

        s1.display();
        s2.display();
        s3.display();

        s3 = s1 + s2;
        s3.display();
        cout << endl;

        cout << "\nТестирование длинной строки в конструкторе:" << endl;
        char longStr[100];
        memset(longStr, 'A', 80);
        longStr[80] = '\0';
        String s4(longStr); // вызовет исключение
    }
    catch (const String::StringError& e) {
        cout << "Ошибка: " << e.message << endl;
    }

    return 0;
}

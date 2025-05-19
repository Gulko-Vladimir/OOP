// ex14_12.cpp
// Класс dofile с обработкой файловых ошибок через исключения
#include <fstream>
#include <iostream>
#include <process.h> // для exit()
#include <string>    // для std::string в исключении
using namespace std;

const int MAX = 1000;
int buff[MAX];

class dofile {
private:
    fstream file; // Поток для чтения и записи
    string filename; // Имя файла

public:
    // Класс исключения для файловых ошибок
    class FileError {
    public:
        string message; // Причина ошибки
        FileError(const string& msg) : message(msg) {}
    };

    // Конструктор: открывает файл в указанном режиме
    dofile(const string& fname, ios::openmode mode) : filename(fname) {
        file.open(fname.c_str(), mode);
        if (!file) {
            throw FileError("Невозможно открыть файл: " + fname);
        }
        file.seekg(0, ios::beg); // Устанавливаем указатель в начало
    }

    // Деструктор: закрывает файл
    ~dofile() {
        if (file.is_open()) {
            file.close();
        }
    }

    // Метод записи в файл
    void write(const char* data, streamsize size) {
        file.write(data, size);
        cout << "Записано байт: " << size << endl;
        if (!file) {
            throw FileError("Ошибка записи в файл: " + filename);
        }
    }

    // Метод чтения из файла
    void read(char* data, streamsize size) {
        file.read(data, size);
        cout << "Прочитано байт: " << file.gcount() << endl;
        if (!file) {
            throw FileError("Ошибка чтения из файла: " + filename);
        }
    }


    // Метод для установки указателя в начало
    void rewind() {
        file.seekg(0, ios::beg);
        if (!file) {
            throw FileError("Ошибка при установке указателя в начало файла: " + filename);
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru"); // Поддержка русской локализации

    // Заполняем буфер
    for (int j = 0; j < MAX; j++) {
        buff[j] = j;
    }

    try {
        // Запись в файл
        cout << "Идет запись...\n";
        dofile outfile("C:\\edata.dat", ios::out | ios::trunc | ios::binary);
        outfile.write(reinterpret_cast<char*>(buff), MAX * sizeof(int));

        // Очистка буфера
        for (int j = 0; j < MAX; j++) {
            buff[j] = 0;
        }

        // Чтение из файла
        cout << "Идет чтение...\n";
        dofile infile("C:\\edata.dat", ios::in | ios::binary);
        infile.read(reinterpret_cast<char*>(buff), MAX * sizeof(int));

        // Проверка данных
        for (int j = 0; j < MAX; j++) {
            if (buff[j] != j) {
                throw dofile::FileError("Данные некорректны");
            }
        }
        cout << "Данные в порядке\n";
    }
    catch (const dofile::FileError& e) {
        cerr << "Ошибка: " << e.message << endl;
        return 1;
    }

    return 0;
}
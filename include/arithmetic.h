// Объявление функций и классов для вычисления арифметических выражений
#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#include <iostream>
#include <string>
using namespace std;

class Tlexeme
{
protected:
    int Size; // Размер массива лексем
    string* mLexeme; // Массив строк, представляющих лексемы (части выражения)
    int* priority; // Массив приоритетов для каждой лексемы
    int Flag = -1; // Флаг состояния проверки корректности

public:
    // Конструктор и деструктор
    Tlexeme(string a = "0"); // Конструктор, инициализирующий лексему
    ~Tlexeme(); // Деструктор для освобождения памяти

    // Методы
    void Fill(string a); // Заполняет объект новой строкой
    int Check_correct(); // Проверяет корректность введенного выражения
    string Pol(); // Возвращает выражение в польской нотации
    double Calculation(int x = 0); // Вычисляет значение выражения
     
    // Перегрузка операторов ввода/вывода
    friend istream& operator>>(istream& in, Tlexeme& l)
    {
        in >> l.mLexeme[0]; // Чтение строки из потока
        string a = l.mLexeme[0]; // Сохраняем считанную строку
        l.Size = (l.mLexeme[0]).length(); // Определяем размер строки
        l.mLexeme = new string[l.Size]; // Выделяем память для массива лексем
        l.priority = new int[l.Size]; // Выделяем память для массива приоритетов
        l.mLexeme[0] = a; // Сохраняем строку в массиве лексем
        return in; // Возвращаем поток
    }

    friend ostream& operator<<(ostream& out, const Tlexeme& l)
    {
        for (int i = 0; i < l.Size; i++)
        {
            out << l.mLexeme[i] << ' '; // Выводим каждую лексему
        }
        cout << endl; // Переход на новую строку
        /*for (int i = 0; i < l.Size; i++)
        { out << l.priority[i] << ' ';} // Комментарий: вывод приоритетов
        cout << endl;*/
        return out; // Возвращаем поток
    }

private:
    // Скрытые функции
    void Divide(); // Разделяет строку на лексемы
    void Pol_1(); // Преобразует выражение в польскую нотацию
    int Check_brack(); // Проверяет корректность скобок
    int Check_sign(); // Проверяет корректность знаков операций
    int Check_point(); // Проверяет корректность точек в дробных числах
    int Check_variable(); // Проверяет корректность переменных
    int Check_function(); // Проверяет корректность функций
};

#endif // Защита от повторного включения
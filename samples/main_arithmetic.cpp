﻿// Реализация пользовательского приложения для вычисления арифметических выражений
#include <iostream>
#include <string>
#include "arithmetic.h"
#include "stack.h"
#include <clocale> 
using namespace std;

void menu()
{
    setlocale(LC_ALL, "rus");
    cout << "\n\t1. Проверка выражения на корректность \n\t2. Перевод выражения в польскую нотацию \n\t3. Вычисление выражения \n\t0. Ввести новое выражение\n\tВвод:";
}

int main()
{
    setlocale(LC_ALL, "rus");
    int entry1 = 1, entry2 = 1; // Переменные для ввода пользователя
    while (entry1 != 0) // Основной цикл программы
    {
        cout << "ВЫЧИСЛЕНИЕ АРИФМЕТИЧЕСКИХ ВЫРАЖЕНИЙ:" << endl << endl;
        cout << "\tВведите выражение:\n\tВвод: ";
        Tlexeme A; // Создание объекта Tlexeme для хранения выражения
        cin >> A; // Ввод выражения от пользователя
        entry2 = 1; // Сброс переменной для выбора действия
        while (entry2 != 0) // Цикл для выбора действия
        {
            menu(); // Отображение меню
            cin >> entry2; // Ввод выбора действия
            system("cls"); // Очистка консоли
            cout << "ВЫЧИСЛЕНИЕ АРИФМЕТИЧЕСКИХ ВЫРАЖЕНИЙ:" << endl << endl;
            cout << "\t" << A; // Отображение текущего выражения
            if (entry2 == 0) {
                system("cls"); // Очистка консоли, если выбрано новое выражение
            }
            else
            {
                // Проверка корректности выражения
                if (!A.Check_correct())
                {
                    cout << "\t- Введенное выражение некорректно.\n\tДальнейшие вычисления с ним невозможны. Введите новое выражение\n\n\tВведите выражение:\n\tВвод: ";
                    string a1; cin >> a1; A.Fill(a1); // Ввод нового выражения
                    system("cls"); // Очистка консоли
                    cout << "ВЫЧИСЛЕНИЕ АРИФМЕТИЧЕСКИХ ВЫРАЖЕНИЙ:" << endl << endl;
                    cout << "\tВведите выражение:\n\tВвод: " << A; // Отображение нового выражения
                }
                else
                {
                    // Выбор действия в зависимости от ввода пользователя
                    switch (entry2)
                    {
                    case 1:
                        cout << "\t- Введенное выражение корректно. Выберите следующее действие\n";
                        break;
                    case 2:
                        cout << "\tПольская нотация выражения: " << A.Pol(); // Вывод польской нотации
                        break;
                    case 3:
                        cout << "\t- Результат вычисления: " << A.Calculation() << endl; // Вывод результата вычисления
                        break;
                    }
                }
            }
        }
    }
}

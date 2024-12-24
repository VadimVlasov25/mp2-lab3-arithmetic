// Реализация функций и классов для вычисления арифметических выражений
#include "..\include\arithmetic.h"
#include "..\include\stack.h"
#include <cmath>   // Для математических функций
#include <cstdlib> // Для конвертации строк в числа

// Функция для определения приоритета операций
int PR(string a)
{
    if (a == "(") { return(0); } // Открывающая скобка имеет наименьший приоритет
    if (a == "+") { return(1); } // Сложение
    if (a == "-") { return(1); } // Вычитание
    if (a == "*") { return(2); } // Умножение
    if (a == "/") { return(2); } // Деление
    if (a == "^") { return(3); } // Возведение в степень
    if (a == "sin") { return(4); } // Функция синуса
}

// Функция для конвертации строки в число с плавающей запятой
double Convert(string a)
{
    string::size_type sz = 0; // Переменная для хранения позиции
    string a1 = a; // Копия входной строки
    double res = stoll(a1, &sz, 0); // Конвертация целой части строки
    a1 = a1.substr(sz); // Удаляем целую часть из строки
    if (!a1.empty())
    {
        a1 = a1.substr(1); // Удаляем точку
        res = res + (stoll(a1, NULL)) / (pow(10, a1.length())); // Добавляем дробную часть
    }
    return res; // Возвращаем результат
}

// Конструктор класса Tlexeme
Tlexeme::Tlexeme(string a)
{
    Size = a.length(); // Определяем размер входной строки
    mLexeme = new string[Size]; // Выделяем память для массива лексем
    priority = new int[Size]; // Выделяем память для массива приоритетов
    TStack <char> S1; // Создаем стек для символов
    for (int i = 0; i < Size; i++)
    {
        mLexeme[i] = ' '; // Инициализируем лексемы пробелами
        priority[i] = -1; // Инициализируем приоритеты значением -1
    }
    mLexeme[0] = a; // Сохраняем входную строку в массив лексем
}

// Деструктор класса Tlexeme
Tlexeme::~Tlexeme()
{
    delete[] mLexeme; // Освобождаем память для массива лексем
    delete[] priority; // Освобождаем память для массива приоритетов
}

// Метод для заполнения объекта Tlexeme
void Tlexeme::Fill(string a)
{
    Size = a.length(); // Определяем размер входной строки
    mLexeme = new string[Size]; // Выделяем память для массива лексем
    priority = new int[Size]; // Выделяем память для массива приоритетов
    TStack <char> S1; // Создаем стек для символов
    for (int i = 0; i < Size; i++)
    {
        mLexeme[i] = ' '; // Инициализируем лексемы пробелами
        priority[i] = -1; // Инициализируем приоритеты значением -1
    }
    mLexeme[0] = a; // Сохраняем входную строку в массив лексем
    Flag = -1; // Инициализируем флаг
}

// Метод для разделения входной строки на лексемы
void Tlexeme::Divide()
{
    string a = mLexeme[0]; // Получаем входную строку
    int j = 0; // Индекс для массива лексем
    string S1 = ""; // Временная строка для хранения текущей лексемы
    string* mLexeme1 = new string[Size]; // Временный массив лексем
    int* priority1 = new int[Size]; // Временный массив приоритетов
    for (int i = 0; i < Size; i++)
    {
        // Проверяем символы и разделяем их на лексемы
        if ((a[i] == '+') || (a[i] == '*') || (a[i] == '/') || (a[i] == '^'))
        {
            if (S1 != "") { mLexeme1[j] = S1; priority1[j] = 2; j++; S1 = ""; } // Сохраняем предыдущую лексему
            mLexeme1[j] = a[i]; // Сохраняем текущую операцию
            priority1[j] = 1; j++; // Устанавливаем приоритет
        }
        else // Если символ не операция
        {
            if (a[i] == '-')
            {
                // Обрабатываем случай с отрицательным числом
                if ((i == 0) || (((priority1[j - 1] == 4) || (priority1[j - 1] == 1))) && (S1 == "")) { S1 = S1 + '-'; }
                else {
                    if (S1 != "") { mLexeme1[j] = S1; priority1[j] = 2; j++; S1 = ""; }
                    mLexeme1[j] = a[i];
                    priority1[j] = 1; j++;
                }
            }
            else // Если символ не операция и не скобка
            {
                if ((a[i] == '(') || (a[i] == ')'))
                {
                    if (S1 != "") { mLexeme1[j] = S1; priority1[j] = 2; j++; S1 = ""; }
                    mLexeme1[j] = a[i];
                    priority1[j] = 4; j++;
                }
                else // Если символ - функция (например, sin)
                {
                    if ((a[i] == 's') && (a[i + 1] == 'i') && (a[i + 2] == 'n'))
                    {
                        if (S1 != "") { mLexeme1[j] = S1; priority1[j] = 2; j++; S1 = ""; }
                        mLexeme1[j] = "sin"; i = i + 2; // Сохраняем функцию "sin"
                        priority1[j] = 5; j++;
                    }
                    else // Если символ - переменная или число
                    {
                        if (((a[i] >= 'A') && (a[i] <= 'Z')) || ((a[i] >= 'a') && (a[i] <= 'z')))
                        {
                            if (S1 != "") { mLexeme1[j] = S1; priority1[j] = 2; j++; S1 = ""; }
                            mLexeme1[j] = a[i]; // Сохраняем переменную
                            priority1[j] = 3; j++;
                        }
                        else // Если символ - число
                        {
                            if (((a[i] >= '0') && (a[i] <= '9')) || (a[i] == '.'))
                            {
                                S1 = S1 + a[i]; // Сохраняем цифру в текущей лексеме
                            }
                            else { Flag = 0; } // Устанавливаем флаг ошибки
                        }
                    }
                }
            }
        }
    }
    // Сохраняем последнюю лексему, если она не пустая
    if (S1 != "") { mLexeme1[j] = S1; priority1[j] = 2; S1 = ""; j++; }
    Size = j; // Обновляем размер
    mLexeme = new string[Size]; // Выделяем память для окончательного массива лексем
    priority = new int[Size]; // Выделяем память для окончательного массива приоритетов
    for (int i = 0; i < Size; i++)
    {
        mLexeme[i] = mLexeme1[i]; // Копируем лексемы
        priority[i] = priority1[i]; // Копируем приоритеты
    }
    if (Flag == -1) { Flag = 1; } // Устанавливаем флаг успешного завершения
}

// Метод для проверки корректности введенного выражения
int Tlexeme::Check_correct()
{
    if (Flag == 2) { return 1; } // Если выражение уже проверено
    if (Flag == -1) { Divide(); } // Если выражение не было разделено, разделяем его
    if (Flag == 0) { cout << "\tInput error: incorrect character is entered" << endl; } // Ошибка ввода
    int a = -1;
    a = Check_brack(); // Проверяем скобки
    if (a != -1) { cout << "\tInput error: brackets are entered incorrectly" << endl; Flag = 0; }
    a = Check_sign(); // Проверяем знаки операций
    if (a != -1) { cout << "\tInput error: signs of operations are entered incorrectly in place " << a << endl; Flag = 0; }
    a = Check_point(); // Проверяем точки в числах
    if (a != -1) { cout << "\tInput error: points of real numbers are entered incorrectly in place " << a << endl; Flag = 0; }
    a = Check_variable(); // Проверяем переменные
    if (a != -1) { cout << "\tInput error: variables are entered incorrectly in place " << a << endl; Flag = 0; }
    a = Check_function(); // Проверяем функции
    if (a != -1) { cout << "\tInput error: function are entered incorrectly in place " << a << endl; Flag = 0; }
    return  Flag; // Возвращаем флаг
}

// Метод для проверки корректности скобок
int Tlexeme::Check_brack()
{
    int a = -1, i = 0;
    while ((i < Size) && (a == -1))
    {
        if ((mLexeme[i] == "(") && (mLexeme[i + 1] != "(") && (mLexeme[i + 2] == "(")) { a = i; } // Проверка на открывающие скобки
        if ((mLexeme[i] == ")") && (mLexeme[i + 1] != ")") && (mLexeme[i + 2] == ")")) { a = i; } // Проверка на закрывающие скобки
        i++;
    }
    if (a == -1) // Если скобки не найдены
    {
        TStack <int> S1; i = 0;
        while ((i < Size) && (a == -1))
        {
            if (priority[i] == 4) // Если текущий элемент - скобка
            {
                if (mLexeme[i] == "(") { S1.Push(1); } // Если открывающая скобка, добавляем в стек
                else
                {
                    if (S1.Empty()) { a = i; } // Если стек пуст, ошибка
                    else { S1.Pop(); } // Убираем из стека
                }
            } i++;
        }
        if (!(S1.Empty())) { a = 11; } // Если остались открывающие скобки, ошибка
    }

    return a; // Возвращаем индекс ошибки или -1
}

// Метод для проверки корректности знаков операций
int Tlexeme::Check_sign()
{
    int a = -1, i = 1;
    if (priority[0] == 1) { a = 0; } // Если первый элемент - операция, ошибка
    while ((i < Size) && (a == -1))
    {
        if (priority[i] == 1) // Если текущий элемент - операция
        {
            if ((priority[i + 1] == 1) || (mLexeme[i - 1] == "(") || (mLexeme[i + 1] == ")")) { a = i; } // Если два знака подряд, ошибка
        } i++;
    }
    if (mLexeme[0] == "-") { a = 0; } // Если выражение начинается с '-', ошибка
    return a; // Возвращаем индекс ошибки или -1
}

// Метод для проверки корректности точек в числах
int Tlexeme::Check_point()
{
    int a = -1, i = 0;
    while ((i < Size) && (a == -1))
    {
        if (priority[i] == 2) // Если текущий элемент - число
        {
            string f = mLexeme[i];
            int  k = count(f.begin(), f.end(), '.'); // Считаем количество точек
            if (k > 1) { a = i; } // Если точек больше одной, ошибка
        } i++;
    }
    return a; // Возвращаем индекс ошибки или -1
}

// Метод для проверки корректности переменных
int Tlexeme::Check_variable()
{
    int a = -1, i = 0;
    while ((i < Size) && (a == -1))
    {
        if ((priority[i] == 3) && (priority[i + 1] == 3)) { a = i; } // Если две переменные подряд, ошибка
        i++;
    }
    return a; // Возвращаем индекс ошибки или -1
}

// Метод для проверки корректности функций
int Tlexeme::Check_function()
{
    int a = -1, i = 0;
    while ((i < Size) && (a == -1))
    {
        if ((priority[i] == 5) && (priority[i + 1] == 1)) { a = i; } // Если функция идет перед знаком операции, ошибка
        if ((priority[i] == 5) && (priority[i - 1] == 3)) { a = i; } // Если функция идет после переменной, ошибка
        if ((priority[i] == 5) && (priority[i - 1] == 2)) { a = i; } // Если функция идет после числа, ошибка
        if ((priority[i] == 5) && (i == Size - 1)) { a = i; } // Если функция в конце выражения, ошибка
        i++;
    }
    return a; // Возвращаем индекс ошибки или -1
}

// Метод для преобразования выражения в польскую нотацию
void Tlexeme::Pol_1()
{
    if (!Check_correct()) { throw 1; } // Если выражение некорректно, выбрасываем исключение
    else {
        if (Flag != 2) // Если выражение еще не преобразовано
        {
            int Nbrack = 0; // Счетчик для открывающих скобок
            for (int i = 0; i < Size; i++)
            {
                if (priority[i] == 4) { Nbrack++; }; // Увеличиваем счетчик для каждой открывающей скобки
                if (priority[i] == 5) { priority[i] = 1; }; // Устанавливаем приоритет функции как 1
            }
            string* mLexeme1; mLexeme1 = mLexeme; mLexeme = new string[Size - Nbrack]; // Создаем новый массив без скобок
            int* priority1; priority1 = priority; priority = new int[Size - Nbrack]; // Создаем новый массив приоритетов без скобок
            TStack <int> S1; // Создаем стек для хранения индексов
            int j = 0; // Индекс для нового массива
            for (int i = 0; i < Size; i++)
            {
                if ((priority1[i] == 2) || (priority1[i] == 3)) // Если это число или переменная
                {
                    mLexeme[j] = mLexeme1[i]; // Сохраняем в новый массив
                    priority[j] = priority1[i]; // Сохраняем приоритет
                    j++;
                }
                else
                {
                    if (priority1[i] == 1) // Если это операция
                    {
                        if (S1.Empty()) { S1.Push(i); } // Если стек пуст, добавляем операцию
                        else
                        {
                            int pr1 = PR(mLexeme1[i]), pr2 = PR(mLexeme1[S1.Top()]); // Получаем приоритеты
                            if (pr1 > pr2) { S1.Push(i); } // Если текущий приоритет больше, добавляем в стек
                            else
                            {
                                while ((pr1 <= pr2) && (!S1.Empty())) // Пока текущий приоритет меньше или равен верхнему элементу стека
                                {
                                    int q = S1.Pop(); // Убираем верхний элемент стека
                                    mLexeme[j] = mLexeme1[q]; // Сохраняем его в новый массив
                                    priority[j] = priority1[q]; // Сохраняем приоритет
                                    j++;
                                    if (!S1.Empty()) { pr2 = PR(mLexeme1[S1.Top()]); } // Обновляем верхний элемент стека
                                } S1.Push(i); // Добавляем текущий элемент в стек
                            }
                        }
                    }
                    else
                    {
                        if (mLexeme1[i] == "(") { S1.Push(i); } // Если это открывающая скобка, добавляем в стек
                        else
                        {
                            if (mLexeme1[i] == ")") // Если это закрывающая скобка
                            {
                                int w = 0; // Флаг для выхода из цикла
                                while ((!S1.Empty()) && (w == 0))
                                {
                                    int q = S1.Top();
                                    if (mLexeme1[q] == "(") { w = 1; } // Если нашли открывающую скобку, выходим
                                    else
                                    {
                                        q = S1.Pop(); // Убираем элемент из стека
                                        mLexeme[j] = mLexeme1[q]; // Сохраняем в новый массив
                                        priority[j] = priority1[q]; // Сохраняем приоритет
                                        j++;
                                    }
                                }
                                S1.Pop(); // Убираем открывающую скобку из стека
                            }
                        }
                    }
                }
            }
            while (!S1.Empty()) // Убираем оставшиеся элементы из стека
            {
                int q = S1.Pop(); mLexeme[j] = mLexeme1[q]; priority[j] = priority1[q]; j++;
            }
            Size = Size - Nbrack; // Обновляем размер
            Flag = 2; // Устанавливаем флаг, что преобразование завершено
        }
    }
}

// Метод для получения выражения в польской нотации
string Tlexeme::Pol()
{
    Pol_1(); // Преобразуем в польскую нотацию
    if (Flag == 2) // Если преобразование завершено
    {
        string a;
        for (int i = 0; i < Size; i++)
        {
            a = a + mLexeme[i] + " "; // Формируем строку с результатом
        }
        return a; // Возвращаем строку
    }
}

// Метод для вычисления значения выражения
double Tlexeme::Calculation(int x)
{
    if (Flag != 2) { Pol_1(); } // Если выражение еще не преобразовано, преобразуем
    TStack <double> S1; // Создаем стек для хранения чисел
    int s = Size, j = 0; // Размер и индекс
    double* M1 = new double[Size]; // Массив для хранения значений переменных
    string* M2 = new string[Size]; // Массив для хранения переменных
    for (int i = 0; i < Size; i++)
    {
        if (priority[i] == 2) { S1.Push(Convert(mLexeme[i])); } // Если это число, конвертируем и добавляем в стек
        if (priority[i] == 3) // Если это переменная
        {
            int w = 0, f = -1;
            while ((w < j) && (f == -1))
            {
                if (M2[j] == mLexeme[i]) { f = i; S1.Push(f); } w++;
            }
            if (f == -1) // Если переменная не найдена
            {
                double q;
                cout << "\tEnter the value of the variable " << mLexeme[i] << ":\n\t"; // Запрашиваем значение переменной
                if (x == 0) { cin >> q; } // Если x равно 0, запрашиваем у пользователя
                else { q = x; } // Иначе используем заданное значение
                S1.Push(q); M1[j] = q; M2[j] = mLexeme[i]; // Сохраняем значение переменной
            }
        }
        if (priority[i] == 1) // Если это операция
        {
            double x, y;
            x = S1.Pop(); // Извлекаем верхний элемент стека
            if (mLexeme[i] == "sin") { S1.Push(sin(x)); } // Если операция - синус, вычисляем и добавляем обратно в стек
            else
            {
                y = S1.Pop(); // Извлекаем следующий элемент
                if (mLexeme[i] == "+") { S1.Push(x + y); } // Сложение
                if (mLexeme[i] == "-") { S1.Push(y - x); } // Вычитание
                if (mLexeme[i] == "*") { S1.Push(x * y); } // Умножение
                if (mLexeme[i] == "/") { S1.Push(y / x); } // Деление
                if (mLexeme[i] == "^") { S1.Push(pow(y, x)); } // Возведение в степень
            }
        }
    }
    return S1.Pop(); // Возвращаем результат вычисления
}

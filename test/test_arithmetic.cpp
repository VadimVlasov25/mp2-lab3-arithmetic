// Тесты для вычисления арифметических выражений
#include "..\include\arithmetic.h"
#include <gtest.h>

// Тест для проверки возможности создания объекта Tlexeme
TEST(Tlexeme, can_create_Tlexeme)
{
    ASSERT_NO_THROW(Tlexeme L); // Проверяем, что создание объекта не вызывает исключений
}

// Тест для проверки создания Tlexeme из строки с выражением
TEST(Tlexeme, can_create_Tlexeme_by_string_1)
{
    string a = ")((2+(2-3+1))"; // Строка с неправильным выражением
    ASSERT_NO_THROW(Tlexeme L(a)); // Проверяем, что создание не вызывает исключений
}

// Тест для проверки создания Tlexeme из корректной строки
TEST(Tlexeme, can_create_Tlexeme_by_string_2)
{
    string a = " ((2 + (2 - 3 + 1)))"; // Корректное выражение
    ASSERT_NO_THROW(Tlexeme L(a)); // Проверяем, что создание не вызывает исключений
}

// Тест для проверки заполнения Tlexeme
TEST(Tlexeme, can_fill_Tlexeme_1)
{
    Tlexeme L1;
    string a = ")((2+(2-3+1))"; // Неправильное выражение
    ASSERT_NO_THROW(L1.Fill(a)); // Проверяем, что заполнение не вызывает исключений
}

// Тест для проверки заполнения Tlexeme с корректной строкой
TEST(Tlexeme, can_fill_Tlexeme_2)
{
    Tlexeme L1;
    string a = " ((2 + (2 - 3 + 1)))"; // Корректное выражение
    ASSERT_NO_THROW(L1.Fill(a)); // Проверяем, что заполнение не вызывает исключений
}

// Тест для проверки обнаружения недопустимого символа
TEST(Tlexeme, correctness_check_unidentified_character)
{
    Tlexeme L("3&+2"); // Выражение с недопустимым символом '&'
    EXPECT_EQ(0, L.Check_correct()); // Ожидаем, что проверка вернет 0 (некорректно)
}

// Тесты для проверки корректности скобок
TEST(Tlexeme, correctness_check_brackets_1)
{
    Tlexeme L("(3+2"); // Неправильное выражение с открывающей скобкой
    EXPECT_EQ(0, L.Check_correct()); // Ожидаем, что проверка вернет 0
}

TEST(Tlexeme, correctness_check_brackets_2)
{
    Tlexeme L("3+2)"); // Неправильное выражение с закрывающей скобкой
    EXPECT_EQ(0, L.Check_correct()); // Ожидаем, что проверка вернет 0
}

TEST(Tlexeme, correctness_check_brackets_3)
{
    Tlexeme L("(3+2)7)"); // Неправильное выражение с лишней закрывающей скобкой
    EXPECT_EQ(0, L.Check_correct()); // Ожидаем, что проверка вернет 0
}

TEST(Tlexeme, correctness_check_brackets_4)
{
    Tlexeme L("(*(3+2)"); // Неправильное выражение с открывающей скобкой
    EXPECT_EQ(0, L.Check_correct()); // Ожидаем, что проверка вернет 0
}

// Тесты для проверки корректности знаков операций
TEST(Tlexeme, correctness_check_signs_ofoperations_1)
{
    Tlexeme L("+3+2"); // Неправильное выражение с ведущим знаком '+'
    EXPECT_EQ(0, L.Check_correct()); // Ожидаем, что проверка вернет 0
}

TEST(Tlexeme, correctness_check_signs_ofoperations_2)
{
    Tlexeme L("-3+2"); // Правильное выражение с ведущим знаком '-'
    EXPECT_EQ(1, L.Check_correct()); // Ожидаем, что проверка вернет 1 (корректно)
}

TEST(Tlexeme, correctness_check_signs_ofoperations_3)
{
    Tlexeme L("3*+2"); // Неправильное выражение с ведущим знаком '+'
    EXPECT_EQ(0, L.Check_correct()); // Ожидаем, что проверка вернет 0
}

// Тест для проверки корректности чисел с несколькими точками
TEST(Tlexeme, correctness_check_points_of_numbers)
{
    Tlexeme L("3.0.99+2"); // Неправильное выражение с несколькими точками
    EXPECT_EQ(0, L.Check_correct()); // Ожидаем, что проверка вернет 0
}

// Тест для проверки корректности переменных
TEST(Tlexeme, correctness_check_variable)
{
    Tlexeme L("xy+2"); // Неправильное выражение с переменной 'xy'
    EXPECT_EQ(0, L.Check_correct()); // Ожидаем, что проверка вернет 0
}

// Тесты для проверки корректности функций
TEST(Tlexeme, correctness_check_function_1)
{
    Tlexeme L("10sin3"); // Неправильное выражение с функцией
    EXPECT_EQ(0, L.Check_correct()); // Ожидаем, что проверка вернет 0
}

TEST(Tlexeme, correctness_check_function_2)
{
    Tlexeme L("sin+9"); // Неправильное выражение с функцией
    EXPECT_EQ(0, L.Check_correct()); // Ожидаем, что проверка вернет 0
}

TEST(Tlexeme, correctness_check_function_3)
{
    Tlexeme L("sin+9"); // Повторный тест с тем же выражением
    EXPECT_EQ(0, L.Check_correct()); // Ожидаем, что проверка вернет 0
}

TEST(Tlexeme, correctness_check_function_4)
{
    Tlexeme L("sin"); // Неправильное выражение только с функцией
    EXPECT_EQ(0, L.Check_correct()); // Ожидаем, что проверка вернет 0
}

// Тесты для проверки преобразования в польскую нотацию
TEST(Tlexeme, can_convert_in_Polish_entry)
{
    Tlexeme L("(2+3)*6");
    ASSERT_NO_THROW(L.Pol()); // Проверяем, что преобразование не вызывает исключений
}

TEST(Tlexeme, can_convert_empty_string_in_Polish_entry)
{
    Tlexeme L;
    ASSERT_NO_THROW(L.Pol()); // Проверяем, что преобразование пустой строки не вызывает исключений
}

TEST(Tlexeme, cant_convert_incorrect_in_Polish_entry)
{
    Tlexeme L("(2+3)*6)");
    ASSERT_ANY_THROW(L.Pol()); // Ожидаем исключение при попытке преобразовать некорректное выражение
}


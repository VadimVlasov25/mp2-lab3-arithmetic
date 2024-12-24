
#include "stack.h"
#include <gtest.h>

// Тест для проверки возможности создания стека
TEST(TStack, can_create_TStack)
{
    ASSERT_NO_THROW(TStack<int> s); // Проверяем, что создание стека не вызывает исключений
}

// Тест для проверки, что стек пуст
TEST(TStack, checking_for_TStack_emptiness)
{
    TStack<int> s;
    EXPECT_EQ(1, s.Empty()); // Ожидаем, что стек будет пуст (возвращает 1)
}

// Тест для проверки вставки элемента в стек
TEST(TStack, can_insert_element_into_TStack)
{
    TStack<int> s;
    s.Push(7); // Вставляем элемент 7 в стек
    EXPECT_EQ(0, s.Empty()); // Ожидаем, что стек не пуст (возвращает 0)
}

// Тест для проверки попытки просмотра элемента из пустого стека
TEST(TStack, cant_view_element_from_empty_TStack)
{
    TStack<int> s;
    ASSERT_ANY_THROW(s.Top()); // Ожидаем исключение при попытке получить верхний элемент из пустого стека
}

// Тест для проверки просмотра элемента в стеке
TEST(TStack, view_element_into_TStack)
{
    TStack<int> s;
    s.Push(7); // Вставляем элемент 7
    EXPECT_EQ(7, s.Top()); // Ожидаем, что верхний элемент стека равен 7
    EXPECT_EQ(0, s.Empty()); // Ожидаем, что стек не пуст
}

// Тест для проверки добавления элементов, превышающих размер стека
TEST(TStack, can_put_element_larger_size_TStack)
{
    TStack<int> s;
    for (int i = 0; i < STACK_SIZE + 2; i++)
    {
        s.Push(i); // Добавляем элементы в стек
    }
    ASSERT_NO_THROW(s.Top()); // Проверяем, что получение верхнего элемента не вызывает исключений
    EXPECT_EQ(STACK_SIZE + 1, s.Top()); // Ожидаем, что верхний элемент равен STACK_SIZE + 1
}

// Тест для проверки попытки извлечения элемента из пустого стека
TEST(TStack, cant_take_element_from_empty_TStack)
{
    TStack<int> s;
    ASSERT_ANY_THROW(s.Pop()); // Ожидаем исключение при попытке извлечь элемент из пустого стека
}

// Тест для проверки извлечения элемента из стека
TEST(TStack, take_element_from_empty_TStack)
{
    TStack<int> s;
    s.Push(7); // Вставляем элемент 7
    EXPECT_EQ(7, s.Pop()); // Ожидаем, что извлеченный элемент равен 7
    EXPECT_EQ(1, s.Empty()); // Ожидаем, что стек теперь пуст
}

// Тест для проверки количества элементов в стеке
TEST(TStack, get_the_number_of_elements_in_TStack)
{
    TStack<int> s;
    EXPECT_EQ(0, s.Count()); // Ожидаем, что изначально количество элементов равно 0
    for (int i = 0; i < 10; i++)
    {
        s.Push(i); // Добавляем 10 элементов
    }
    EXPECT_EQ(10, s.Count()); // Ожидаем, что количество элементов равно 10
}

// Тест для проверки очистки стека
TEST(TStack, clean_TStack)
{
    TStack<int> s;
    for (int i = 0; i < 10; i++)
    {
        s.Push(i); // Добавляем 10 элементов
    }
    s.Clear(); // Очищаем стек
    EXPECT_EQ(1, s.Empty()); // Ожидаем, что стек теперь пуст
}

// Объявление и реализация шаблонного стека
// Стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// При вставке в полный стек должна перевыделяться память

#ifndef __TSTACK_H__
#define __TSTACK_H__

#define STACK_SIZE (1000) // Начальный размер стека

#include <vector>

template <class StackType>
class TStack
{
protected:
    int Head; // Указатель на верхний элемент стека
    int Size; // Текущий размер стека
    StackType* mStack; // Массив, представляющий стек

    void Overcrowded(); // Проверка на переполнение стека

public:
    // Конструктор и деструктор
    TStack(); // Конструктор
    ~TStack(); // Деструктор

    // Операции со стеком
    void Push(StackType i); // Вставка элемента в стек
    StackType Pop(); // Извлечение элемента из стека
    StackType Top(); // Просмотр верхнего элемента стека (без удаления)
    bool Empty(); // Проверка на пустоту стека
    int Count(); // Получение количества элементов в стеке
    void Clear(); // Очистка стека
};

// Реализация методов класса TStack

// Конструктор
template <class StackType>
TStack<StackType>::TStack()
{
    Head = 0; // Инициализация указателя на верхний элемент
    Size = STACK_SIZE; // Установка начального размера стека
    mStack = new StackType[Size]; // Выделение памяти для стека
}

// Деструктор
template <class StackType>
TStack<StackType>::~TStack()
{
    delete[] mStack; // Освобождение выделенной памяти
}

// Вставка элемента в стек
template <class StackType>
void TStack<StackType>::Push(StackType i)
{
    Overcrowded(); // Проверка на переполнение
    mStack[Head] = i; // Добавление элемента
    Head++; // Увеличение указателя на верхний элемент
}

// Извлечение элемента из стека
template <class StackType>
StackType TStack<StackType>::Pop()
{
    if (!Empty()) // Проверка на пустоту
    {
        Head--; // Уменьшение указателя на верхний элемент
        return mStack[Head]; // Возврат верхнего элемента
    }
    else
    {
        throw 1; // Исключение в случае пустого стека
    }
}

// Просмотр верхнего элемента стека (без удаления)
template <class StackType>
StackType TStack<StackType>::Top()
{
    if (!Empty())
    {
        return mStack[Head - 1]; // Возврат верхнего элемента
    }
    else
    {
        throw 1; // Исключение в случае пустого стека
    }
}

// Проверка на пустоту стека
template <class StackType>
bool TStack<StackType>::Empty()
{
    return Head == 0; // Возвращает true, если стек пуст
}

// Получение количества элементов в стеке
template <class StackType>
int TStack<StackType>::Count()
{
    return Head; // Возвращает количество элементов
}

// Очистка стека
template <class StackType>
void TStack<StackType>::Clear()
{
    Head = 0; // Сбрасывает указатель на верхний элемент
}

// Проверка на переполнение стека
template <class StackType>
void TStack<StackType>::Overcrowded()
{
    if (Head == Size) // Если стек полон
    {
        StackType* mStack1 = mStack; // Сохраняем старый стек
        Size = Size * 2; // Увеличиваем размер стека вдвое
        mStack = new StackType[Size]; // Выделяем новую память
        for (int i = 0; i < Size / 2; i++)
        {
            mStack[i] = mStack1[i]; // Копируем старые элементы в новый стек
        }
        delete[] mStack1; // Освобождаем старую память
    }
}

#endif // Защита от повторного включения


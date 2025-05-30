
#ifndef POLYNOM_H
#define POLYNOM_H

#include <vector>
#include <iostream>

class Polynom {
public:
    std::vector<double> coefficients; // Коэффициенты полинома

    Polynom() : coefficients(1, 0) {} // Конструктор по умолчанию (нулевой полином)
    Polynom(double value) : coefficients(1, value) {} // Конструктор из числа

    Polynom operator+(const Polynom& other);
    Polynom operator-(const Polynom& other);
    Polynom operator*(const Polynom& other);
    Polynom operator/(const Polynom& other);
    Polynom Pow(int degree);
    Polynom Sin(); // Метод для вычисления синуса полинома

    friend std::ostream& operator<<(std::ostream& os, const Polynom& p);
};

#endif // POLYNOM_H
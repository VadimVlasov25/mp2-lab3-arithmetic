#include "polynom.h"

Polynom Polynom::operator+(const Polynom& other) {
    Polynom result;
    size_t maxSize = std::max(coefficients.size(), other.coefficients.size());
    result.coefficients.resize(maxSize);
    for (size_t i = 0; i < maxSize; ++i) {
        double a = (i < coefficients.size()) ? coefficients[i] : 0;
        double b = (i < other.coefficients.size()) ? other.coefficients[i] : 0;
        result.coefficients[i] = a + b;
    }
    return result;
}

Polynom Polynom::operator-(const Polynom& other) {
    Polynom result;
    size_t maxSize = std::max(coefficients.size(), other.coefficients.size());
    result.coefficients.resize(maxSize);
    for (size_t i = 0; i < maxSize; ++i) {
        double a = (i < coefficients.size()) ? coefficients[i] : 0;
        double b = (i < other.coefficients.size()) ? other.coefficients[i] : 0;
        result.coefficients[i] = a - b;
    }
    return result;
}

Polynom Polynom::operator*(const Polynom& other) {
    Polynom result;
    result.coefficients.resize(coefficients.size() + other.coefficients.size() - 1);
    for (size_t i = 0; i < coefficients.size(); ++i) {
        for (size_t j = 0; j < other.coefficients.size(); ++j) {
            result.coefficients[i + j] += coefficients[i] * other.coefficients[j];
        }
    }
    return result;
}

Polynom Polynom::operator/(const Polynom& other) {
    // Реализация деления полиномов (можно оставить для доработки)
    return Polynom(0); // Заглушка
}

Polynom Polynom::Pow(int degree) {
    Polynom result(1); // Начинаем с единицы
    for (int i = 0; i < degree; ++i) {
        result = result * (*this);
    }
    return result;
}

Polynom Polynom::Sin() {
    // Реализация синуса полинома (можно оставить для доработки)
    return Polynom(0); // Заглушка
}

std::ostream& operator<<(std::ostream& os, const Polynom& p) {
    for (size_t i = 0; i < p.coefficients.size(); ++i) {
        if (p.coefficients[i] != 0) {
            os << p.coefficients[i] << "x^" << i << " ";
        }
    }
    return os;
}

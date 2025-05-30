
#ifndef POLYNOM_H
#define POLYNOM_H

#include <vector>
#include <iostream>

class Polynom {
public:
    std::vector<double> coefficients; // ������������ ��������

    Polynom() : coefficients(1, 0) {} // ����������� �� ��������� (������� �������)
    Polynom(double value) : coefficients(1, value) {} // ����������� �� �����

    Polynom operator+(const Polynom& other);
    Polynom operator-(const Polynom& other);
    Polynom operator*(const Polynom& other);
    Polynom operator/(const Polynom& other);
    Polynom Pow(int degree);
    Polynom Sin(); // ����� ��� ���������� ������ ��������

    friend std::ostream& operator<<(std::ostream& os, const Polynom& p);
};

#endif // POLYNOM_H
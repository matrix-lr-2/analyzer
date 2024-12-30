#include <complex_num.h>
#include <stdexcept>
#include <limits>

Complex& Complex::operator+=(const Complex& other) noexcept {
    re += other.re;
    im += other.im;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) noexcept {
    re -= other.re;
    im -= other.im;
    return *this;
}

Complex& Complex::operator*=(const Complex& other) noexcept {
    double temp_re = re;
    re = re * other.re - im * other.im;
    im = temp_re * other.im + im * other.re;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    if (other.re == 0 && other.im == 0) { throw std::runtime_error("Division by zero"); }
    double temp_re = re;
    re = (re * other.re + im * other.im) / (other.re * other.re + other.im * other.im);
    im = (im * other.re - temp_re * other.im) / (other.re * other.re + other.im * other.im);
    return *this;
}

Complex operator+(Complex& lhs, const Complex& rhs) noexcept {
    Complex tmp(lhs.re, lhs.im);
    tmp += rhs;
    return tmp;
}

Complex operator-(Complex& lhs, const Complex& rhs) noexcept {
    Complex tmp(lhs.re, lhs.im);
    tmp -= rhs;
    return tmp;
}

Complex operator*(Complex& lhs, const Complex& rhs) noexcept {
    Complex tmp(lhs.re, lhs.im);
    tmp *= rhs;
    return tmp;
}

Complex operator/(Complex& lhs, const Complex& rhs) {
    Complex tmp(lhs.re, lhs.im);
    tmp /= rhs;
    return tmp;
}

bool operator==(const Complex& lhs, const Complex& rhs) noexcept {
    return std::abs(lhs.re - rhs.re) <= std::numeric_limits<double>::epsilon() * 10000 &&
           std::abs(lhs.im - rhs.im) <= std::numeric_limits<double>::epsilon() * 10000;
}

bool operator!=(const Complex& lhs, const Complex& rhs) noexcept {
    return !(lhs == rhs);
}
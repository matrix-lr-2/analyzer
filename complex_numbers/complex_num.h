#pragma once

class Complex {
    public: // Constructors
        Complex() noexcept = default;
        Complex(double r) noexcept : re(r) {};
        Complex(double r, double i) noexcept : re(r), im(i) {};
    public: // Math operators
        Complex& operator+=(const Complex& other) noexcept;
        Complex& operator-=(const Complex& other) noexcept;
        Complex& operator*=(const Complex& other) noexcept;
        Complex& operator/=(const Complex& other);
    public:
        double re = 0; // real part of complex number
        double im = 0; // image part of complex number
};

// Math operators
Complex operator+(Complex& lhs, const Complex& rhs) noexcept;
Complex operator-(Complex& lhs, const Complex& rhs) noexcept;
Complex operator*(Complex& lhs, const Complex& rhs) noexcept;
Complex operator/(Complex& lhs, const Complex& rhs);
// Comparison operators
bool operator==(const Complex& lhs, const Complex& rhs) noexcept;
bool operator!=(const Complex& lhs, const Complex& rhs) noexcept;
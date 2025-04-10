#include <complex_num.h>
#include <limits>
#include <sstream>

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

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept {
    Complex tmp(lhs.re, lhs.im);
    tmp += rhs;
    return tmp;
}

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept {
    Complex tmp(lhs.re, lhs.im);
    tmp -= rhs;
    return tmp;
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept {
    Complex tmp(lhs.re, lhs.im);
    tmp *= rhs;
    return tmp;
}

Complex operator/(const Complex& lhs, const Complex& rhs) {
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

std::ostream& operator<<(std::ostream& out, const Complex& num) {
    std::stringstream sout;
    if (num.im == 0) {
        sout << num.re;
    }
    else if (num.re == 0) {
        if (num.im == 1) { sout << "i"; }
        else if (num.im == -1) { sout << "-i"; }
        else sout << num.im << "i";
    }
    else {
        sout << num.re;
        if (num.im > 0) { sout << "+" << num.im << "i"; }
        else sout << num.im << "i";
    }
    out << sout.str();
    return out;
}

static size_t find_sign_pos(const std::string& input) {
    size_t pos = std::string::npos;
    for (size_t i = 1; i < input.size(); ++i) {
        if (input[i] == '+' || input[i] == '-') {
            pos = i;
            break;
        }
    }
    return pos;
}

static bool string_to_complex_num(Complex& num, const std::string& input, const size_t& pos) {
    Complex tmp;
    tmp.re = std::stod(input.substr(0, pos));
    std::string sub_str_im = input.substr(pos);
    if (sub_str_im.find_first_of("+-",  1) != std::string::npos) { return false; }
    if (sub_str_im == "+" || sub_str_im == "-") { tmp.im = std::stod(sub_str_im + "1"); }
    else if (sub_str_im == "-0") { tmp.im = 0; }
    else { tmp.im = std::stod(sub_str_im); }
    num = tmp;
    return true;
}

std::istream& operator>>(std::istream& in, Complex& num) {
    try {
        std::string input;
        in >> input;
        if (input.empty() || input.find_first_not_of(".+-0123456789i") != std::string::npos) { throw std::runtime_error(""); }
        size_t pos = input.find('i');
        if (pos == std::string::npos) {
            if (input.find_first_of("+-",  1) != std::string::npos) { throw std::runtime_error(""); }
            double re = std::stod(input);
            num.im = 0;
            num.re = re;
            return in;
        }
        if (pos != input.length() -1) { throw std::runtime_error(""); }
        input.pop_back();
        if (input.empty() || input == "+" || input == "-") {
            double im = std::stod(input + "1");
            num.re = 0;
            num.im = im;
            return in;
        }
        pos = find_sign_pos(input);
        if (pos == std::string::npos) {
            double im = std::stod(input);
            num.re = 0;
            num.im = im;
            return in;
        }
        if (!string_to_complex_num(num, input, pos)) { throw std::runtime_error(""); }
    } catch (...) {
        in.setstate(std::ios::failbit);
    }
    return in;
}
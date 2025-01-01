#include "procedure.h"
#include <iostream>

int main() {
    Complex v1;
    std::cout << "Введите комплексное число: ";
    std::cin >> v1;
    if (std::cin) {
        std::cout << "Вы ввели: " << v1 << std::endl;
    } else {
        std::cerr << "Ошибка ввода!" << std::endl;
    }
    return 0;
}
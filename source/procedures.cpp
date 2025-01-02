#include "procedures.h"
#include <iostream>

const char* parse_arguments(int arg_count, char* arg_vars[]) {
    if (arg_count != 2) {
        throw std::runtime_error("Invalid arguments: the program requires exactly one argument specifying the file path.");
    }
    return arg_vars[1];
}

linalg::Matrix<Complex> load_matrix(const char* file_name) {
    linalg::Matrix<Complex> matrix = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    std::cout << "The original matrix was read from file " << file_name << ":\n";
    std::cout << matrix << std::endl;
    return matrix;
}

void analyze(const linalg::Matrix<Complex>& matrix) {
    std::cout << "Transposed matrix:\n" << transpose(matrix) << std::endl;
    std::cout << "Row reduced echelon form:\n" << matrix.reduced_row_echelon_form() << std::endl;
    std::cout << "Rank: " << matrix.rank() << std::endl;
    if (matrix.rows() != matrix.columns()) {
        std::cout << "Other analysis is not available for non-square matrices!" << std::endl;
        return;
    }
    std::cout << "Trace: " << matrix.trace() << std::endl;
    Complex determinant = matrix.det();
    std::cout << "Determinant: " << determinant << std::endl;
    if (determinant == 0) {
        std::cout << "Matrix can not be inverted due to zero determinant!" << std::endl;
        return;
    }
    std::cout << "\nInverted matrix:\n" << invert(matrix) << std::endl;
}

void handle(const std::exception& exception) {
    std::cerr << exception.what() << std::endl;
}
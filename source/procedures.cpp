#include "procedures.h"
#include <iostream>
#include <fstream>

const char* parse_arguments(int arg_count, char* arg_vars[]) {
    if (arg_count != 2) {
        throw std::invalid_argument("Invalid arguments: the program requires exactly one argument specifying the file path.");
    }
    return arg_vars[1];
}

size_t count_rows_num(const char* file_path) {
    using namespace std::string_literals;
    std::ifstream file(file_path);
    if (!file.is_open()) { throw std::runtime_error("Can't open file: "s + file_path); }
    std::string line;
    size_t count = 0;
    while (std::getline(file, line)) {
        if (line[0] != '|' || line[line.length()-1] != '|') {
            throw std::invalid_argument("Invalid format: each row of the matrix must starts and ends with \"|\"!");
        }
        count++;
    }
    return count;
}

size_t count_column_num(const char* file_path) {
    using namespace std::string_literals;
    std::ifstream file(file_path);
    if (!file.is_open()) { throw std::runtime_error("Can't open file: "s + file_path); }
    std::string line;
    size_t count = 0;
    std::getline(file, line);
    size_t start_pos = line.find('|') + 1;
    size_t end_pos = line.rfind('|');
    line = line.substr(start_pos, end_pos - start_pos);
    std::stringstream ss(line);
    std::string element;
    while (std::getline(ss, element, ' ')) {
        if (element.empty()) { continue; }
        count++;
    }
    return count;
}

linalg::Matrix<Complex> load_matrix(const char* file_path) {
    linalg::Matrix<Complex> matrix(count_rows_num(file_path), count_column_num(file_path));
    using namespace std::string_literals;
    std::ifstream file(file_path);
    if (!file.is_open()) { throw std::runtime_error("Can't open file: "s + file_path); }
    std::string line;
    size_t current_rows_num = 0;
    while (std::getline(file, line)) {
        size_t start_pos = line.find('|') + 1;
        size_t end_pos = line.rfind('|');
        line = line.substr(start_pos, end_pos - start_pos);
        std::stringstream ss(line);
        std::string element;
        size_t current_columns_num = 0;
        while (std::getline(ss, element, ' ')) {
            if (element.empty()) { continue; }
            std::stringstream element_stream(element);
            Complex value;
            element_stream >> value;
            if (current_columns_num + 1 > matrix.columns()) { throw std::invalid_argument("All rows should have the same number of columns!"); }
            if (element_stream.fail()) { throw std::invalid_argument("Failed to parse matrix element!"); }
            matrix(current_rows_num, current_columns_num) = value;
            current_columns_num++;
        }
        if (current_columns_num < matrix.columns()) { throw std::invalid_argument("All rows should have the same number of columns!"); }
        current_rows_num++;
    }
    std::cout << "The original matrix was read from file " << file_path << ":\n";
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
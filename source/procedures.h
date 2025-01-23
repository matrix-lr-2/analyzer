#pragma once
#include <complex_num.h>
#include <matrix.h>

const char* parse_arguments(int arg_count, char* arg_vars[]);
linalg::Matrix<Complex> load_matrix(const char* file_path);
void analyze(const linalg::Matrix<Complex>& matrix);
void handle(const std::exception& exception);
linalg::Matrix<double> is_double(const linalg::Matrix<Complex>& mat);
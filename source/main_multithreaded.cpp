#include "multithreaded.h"

int main(int arg_count, char* arg_vars[]) {
    try {
        const char* file_path = parse_arguments(arg_count, arg_vars);
        linalg::Matrix<Complex> matrix = load_matrix(file_path);
        analyzer_benchmark(matrix);
    }
    catch (const std::exception& exception) {
        handle(exception);
        return 1;
    }
    return 0;
}
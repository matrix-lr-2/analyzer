#include "multithreaded.h"
#include <chrono>
#include <iostream>
#include <future>
#define M_PI        3.14159265358979323846264338327950288

void analyze_multithreaded(const linalg::Matrix<Complex>& matrix) {
    auto transpose_future = std::async(std::launch::async, [&matrix]() {
        return transpose(matrix);
    });
    auto rref_future = std::async(std::launch::async, [&matrix]() {
        return matrix.reduced_row_echelon_form();
    });
    auto rank_future = std::async(std::launch::async, [&matrix]() {
        return matrix.rank();
    });
    std::cout << "Transposed matrix:\n" << transpose_future.get() << std::endl;
    std::cout << "Row reduced echelon form:\n" << rref_future.get() << std::endl;
    std::cout << "Rank: " << rank_future.get() << std::endl;
    if (matrix.rows() != matrix.columns()) {
        std::cout << "\nOther analysis is not available for non-square matrices!" << std::endl;
        return;
    }
    auto trace_future = std::async(std::launch::async, [&matrix]() {
        return matrix.trace();
    });
    auto determinant_future = std::async(std::launch::async, [&matrix]() {
        return matrix.det();
    });
    std::cout << "Trace: " << trace_future.get() << std::endl;
    Complex determinant = determinant_future.get();
    std::cout << "Determinant: " << determinant << std::endl;
    if (determinant == 0) {
        std::cout << "\nOther analysis is not available due to zero determinant!" << std::endl;
        return;
    }
    auto invert_future = std::async(std::launch::async, [&matrix]() {
        return invert(matrix);
    });
    std::cout << "\nInverted matrix:\n" << invert_future.get() << std::endl;
    auto rotation_future = std::async(std::launch::async, [&matrix]() -> std::tuple<std::string, double, double, double, double> {
        return is_double(matrix).rotation_3d();
    });
    try {
        auto result = rotation_future.get();
        std::cout << "Orthogonal transformations:\n";
        std::cout << "Transformation type: " << std::get<0>(result) << std::endl;
        std::cout << "Rotation axis: [" << std::get<1>(result) << ", " << std::get<2>(result) << ", " << std::get<3>(result) << "]" << std::endl;
        std::cout << "Rotation angle (degrees): " << (std::get<4>(result) * 180) / M_PI << std::endl;
    }
    catch (const std::exception& exception) {
        std::cout << std::endl << exception.what() << std::endl;
    }
}

void analyzer_benchmark(const linalg::Matrix<Complex>& test_matrix) {
    std::cout << "The result of single threaded analyze: \n\n";
    auto start_single = std::chrono::high_resolution_clock::now();
    analyze(test_matrix);
    auto end_single = std::chrono::high_resolution_clock::now();
    std::cout << "--------------------------------------------------------------------\n";
    std::cout << "The result of multy threaded analyze: \n\n";
    auto start_multy= std::chrono::high_resolution_clock::now();
    analyze_multithreaded(test_matrix);
    auto end_multy = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_single = end_single - start_single;
    std::chrono::duration<double> elapsed_multy = end_multy - start_multy;
    std::cout << "-----------------------------Statistics-----------------------------\n";
    std::cout << "Spent time in single thread mode: " << elapsed_single.count() << "\n";
    std::cout << "Spent time in multy thread mode: " << elapsed_multy.count() << "\n";
    std::cout << "Difference between multy thread and single thread (multy - single): " << elapsed_single.count() - elapsed_multy.count() << "\n";
    std::cout << "Multy threaded analyze was " << elapsed_single.count()/elapsed_multy.count() << " times faster that single one.\n";
}
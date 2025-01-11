#include "multhithreaded.h"
#include <chrono>
#include <iostream>

void analyze_multithreaded(const linalg::Matrix<Complex>& matrix) {
    return;
}

void analyzer_benchmark(const linalg::Matrix<Complex>& test_matrix) {
    std::cout << "The result of single threaded analyze: \n";
    auto start_single = std::chrono::high_resolution_clock::now();
    analyze(test_matrix);
    auto end_single = std::chrono::high_resolution_clock::now();
    std::cout << "The result of multy threaded analyze: \n";
    auto start_multy= std::chrono::high_resolution_clock::now();
    analyze_multithreaded(test_matrix);
    auto end_multy = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_single = end_single - start_single;
    std::chrono::duration<double> elapsed_multy = end_multy - start_multy;
    std::cout << "-----------------------------Statistics-----------------------------\n";
    std::cout << "Spent time in single thread mode: " << elapsed_single.count() << "\n";
    std::cout << "Spent time in multy thread mode: " << elapsed_multy.count() << "\n";
    std::cout << "Difference between multy thread and single thread (multy - single): " << elapsed_multy.count() - elapsed_single.count() << "\n";
    std::cout << "Multy threaded analyze was " << elapsed_multy.count()/elapsed_single.count() << " times faster that single one.\n";
}
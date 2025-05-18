#include <iostream>
#include <chrono>
#include <vector>
#include "customCodeBenchmark.hpp"

void testCustomCode() {
    long long sum = 0;
    for (int i = 0; i < 1e7; ++i) {
        sum += i;
    }
}

long long runCustomBenchmark(int optLevel) {
    std::cout << "Running with optLevel: " << optLevel << "\n";

    auto start = std::chrono::high_resolution_clock::now();

    testCustomCode();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<long long, std::nano> elapsed = end - start;

    long long elapsed_ns = elapsed.count();

    std::cout << "Execution time: " << elapsed_ns / 1e6 << " ms\n";

    return elapsed_ns;
}

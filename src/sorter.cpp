
#include "sorter.hpp"
#include <algorithm>
#include <iostream>
#include <chrono> 


void runSort(const std::string& algo, std::vector<int>& arr) {
    std::cout << "Running: " << algo << " on array of size " << arr.size() << "\n";

    if (algo == "STLSort") {
        std::sort(arr.begin(), arr.end());
    } else {
        std::cout << "Sorting algorithm '" << algo << "' not implemented yet.\n";
    }
}

long long benchmark(const std::string& algo, std::vector<int>& arr) {
   
    std::vector<int> copyArr = arr;

    auto start = std::chrono::high_resolution_clock::now();

    runSort(algo, copyArr);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << algo << " took " << duration << " microseconds\n";

    return duration;
}

#include "sorter.hpp"
#include <algorithm>
#include <iostream>


void runSort(const std::string& algo, std::vector<int>& arr) {
    std::cout << "Running: " << algo << " on array of size " << arr.size() << "\n";

    if (algo == "STLSort") {
        std::sort(arr.begin(), arr.end());
    } else {
        std::cout << "Sorting algorithm '" << algo << "' not implemented yet.\n";
    }
}

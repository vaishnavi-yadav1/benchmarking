
#include "utils.hpp"
#include <vector>
#include <algorithm>
#include <random>

std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100000);

    for (int& val : arr) val = dis(gen);
    return arr;
}

std::vector<int> generateSortedArray(int size) {
    std::vector<int> arr = generateRandomArray(size);
    std::sort(arr.begin(), arr.end());
    return arr;
}

std::vector<int> generateReversedArray(int size) {
    std::vector<int> arr = generateSortedArray(size);
    std::reverse(arr.begin(), arr.end());
    return arr;
}

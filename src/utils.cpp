
#include "utils.hpp"
#include <vector>
#include <algorithm>
#include <random>
#include <cstddef> 

// Generate a random array of given size with values between 1 and 100000
std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100000);

    for (int& val : arr) val = dis(gen);
    
    return arr;
}

// Generate a sorted array by first creating a random array and sorting it
std::vector<int> generateSortedArray(int size) {
    std::vector<int> arr = generateRandomArray(size);
    std::sort(arr.begin(), arr.end());
    return arr;
}

// Generate a reversed sorted array by creating a sorted array and reversing it
std::vector<int> generateReversedArray(int size) {
    std::vector<int> arr = generateSortedArray(size);
    std::reverse(arr.begin(), arr.end());
    return arr;
}

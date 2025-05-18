#include <iostream>
#include <vector>
#include <algorithm>
#include "utils.hpp"
#include "sorter.hpp"

// Helper function to calculate median of a vector of longs
long long median(std::vector<long long> &times) {
    std::sort(times.begin(), times.end());
    size_t n = times.size();
    if (n % 2 == 0) {
        return (times[n/2 - 1] + times[n/2]) / 2;
    } else {
        return times[n/2];
    }
}

int main()
{
    std::string algorithm;
    int sizeChoice, typeChoice;
    int size;
    std::vector<int> arr;

    std::cout << "===== goBench++ CLI =====\n";
    std::cout << "Choose Sorting Algorithm:\n";
    std::cout << "1. BubbleSort\n2. InsertionSort\n3. MergeSort\n4. QuickSort\n5. HeapSort\n6. std::sort\n";
    std::cout << "Enter choice (1-6): ";
    int algoChoice;
    std::cin >> algoChoice;

    switch (algoChoice)
    {
        case 1: algorithm = "BubbleSort"; break;
        case 2: algorithm = "InsertionSort"; break;
        case 3: algorithm = "MergeSort"; break;
        case 4: algorithm = "QuickSort"; break;
        case 5: algorithm = "HeapSort"; break;
        case 6: algorithm = "STLSort"; break;
        default:
            std::cout << "Invalid choice.\n";
            return 1;
    }

    std::cout << "\nSelect Input Size:\n1. 1,000\n2. 10,000\n3. 100,000\nChoice: ";
    std::cin >> sizeChoice;
    if (sizeChoice == 1) size = 1000;
    else if (sizeChoice == 2) size = 10000;
    else if (sizeChoice == 3) size = 100000;
    else {
        std::cout << "Invalid size choice.\n";
        return 1;
    }

    std::cout << "\nSelect Input Type:\n1. Random\n2. Sorted\n3. Reversed\nChoice: ";
    std::cin >> typeChoice;

    if (typeChoice == 1)
        arr = generateRandomArray(size);
    else if (typeChoice == 2)
        arr = generateSortedArray(size);
    else if (typeChoice == 3)
        arr = generateReversedArray(size);
    else {
        std::cout << "Invalid input type.\n";
        return 1;
    }

    std::cout << "\nRunning " << algorithm << " on " << size << " elements...\n";

    const int runs = 5;
    std::vector<long long> runTimes;
    runTimes.reserve(runs);

    for (int i = 0; i < runs; ++i) {
        long long time = benchmark(algorithm, arr);
        runTimes.push_back(time);
    }

    // Calculate statistics
    long long sum = 0;
    for (auto t : runTimes) sum += t;
    double average = static_cast<double>(sum) / runs;
    long long med = median(runTimes);
    long long minTime = *std::min_element(runTimes.begin(), runTimes.end());
    long long maxTime = *std::max_element(runTimes.begin(), runTimes.end());

    // Print results
    std::cout << "\nRuns (nanoseconds): [";
    for (size_t i = 0; i < runTimes.size(); ++i) {
        std::cout << runTimes[i];
        if (i != runTimes.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";

    std::cout << "Average: " << average << " ns\n";
    std::cout << "Median: " << med << " ns\n";
    std::cout << "Min: " << minTime << " ns\n";
    std::cout << "Max: " << maxTime << " ns\n";

    return 0;
}

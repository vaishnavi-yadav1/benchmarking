#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include "utils.hpp"
#include "sorter.hpp"

long long median(std::vector<long long> &times) {
    std::sort(times.begin(), times.end());
    size_t n = times.size();
    if (n % 2 == 0)
        return (times[n / 2 - 1] + times[n / 2]) / 2;
    else
        return times[n / 2];
}

void printStats(const std::vector<long long> &runTimes) {
    long long sum = 0;
    for (auto t : runTimes) sum += t;
    double average = static_cast<double>(sum) / runTimes.size();
    long long med = median(const_cast<std::vector<long long> &>(runTimes));
    long long minTime = *std::min_element(runTimes.begin(), runTimes.end());
    long long maxTime = *std::max_element(runTimes.begin(), runTimes.end());

    std::cout << "Runs (nanoseconds): [";
    for (size_t i = 0; i < runTimes.size(); ++i) {
        std::cout << runTimes[i];
        if (i != runTimes.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    std::cout << "Average: " << average << " ns\n";
    std::cout << "Median: " << med << " ns\n";
    std::cout << "Min: " << minTime << " ns\n";
    std::cout << "Max: " << maxTime << " ns\n";
}

void createCSVWithHeader(const std::string &filename) {
    std::ofstream file(filename);
    file << "Algorithm,Size,InputType,Time(us)\n";
    file.close();
}

void exportResultToCSV(const std::string &filename,
                       const std::string &algorithm,
                       int size,
                       const std::string &inputType,
                       long long time_ns) {
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error opening file for CSV output.\n";
        return;
    }
    double time_us = time_ns / 1000.0;
    file << algorithm << "," << size << "," << inputType << "," << time_us << "\n";
    file.close();
}

void runInteractiveBenchmark(int optLevel) {
    std::string algorithm;
    int sizeChoice, typeChoice;
    int size;
    std::vector<int> arr;

    std::cout << "\n=========================\n";
    std::cout << "     Choose Algorithm     \n";
    std::cout << "-------------------------\n";
    std::cout << " 1. BubbleSort\n 2. InsertionSort\n 3. MergeSort\n 4. QuickSort\n 5. HeapSort\n 6. std::sort\n 7. ThreadedMergeSort\n";
    std::cout << "-------------------------\n";
    std::cout << "Enter choice (1-7): ";

    int algoChoice;
    std::cin >> algoChoice;

    switch (algoChoice) {
    case 1: algorithm = "BubbleSort"; break;
    case 2: algorithm = "InsertionSort"; break;
    case 3: algorithm = "MergeSort"; break;
    case 4: algorithm = "QuickSort"; break;
    case 5: algorithm = "HeapSort"; break;
    case 6: algorithm = "STLSort"; break;
    case 7: algorithm = "ThreadedMergeSort"; break;
    default: 
        std::cout << "\nInvalid choice.\n";
        return;
    }

    std::cout << "\n=========================\n";
    std::cout << "      Select Size         \n";
    std::cout << "-------------------------\n";
    std::cout << " 1. 1,000\n 2. 10,000\n 3. 100,000\n";
    std::cout << "-------------------------\n";
    std::cout << "Choice: ";
    std::cin >> sizeChoice;
    if (sizeChoice == 1) size = 1000;
    else if (sizeChoice == 2) size = 10000;
    else if (sizeChoice == 3) size = 100000;
    else {
        std::cout << "\nInvalid size choice.\n";
        return;
    }

    if ((algorithm == "BubbleSort" || algorithm == "InsertionSort") && size == 100000) {
        std::cout << "\nWarning: " << algorithm << " on 100,000 elements may take a LONG time.\n";
        std::cout << "Proceed? (y/n): ";
        char proceed;
        std::cin >> proceed;
        if (proceed != 'y' && proceed != 'Y') {
            std::cout << "Benchmark cancelled.\n";
            return;
        }
    }

    std::cout << "\n=========================\n";
    std::cout << "      Select Input Type    \n";
    std::cout << "-------------------------\n";
    std::cout << " 1. Random\n 2. Sorted\n 3. Reversed\n";
    std::cout << "-------------------------\n";
    std::cout << "Choice: ";
    std::cin >> typeChoice;

    std::string inputType;
    if (typeChoice == 1) {
        inputType = "Random";
        arr = generateRandomArray(size);
    } else if (typeChoice == 2) {
        inputType = "Sorted";
        arr = generateSortedArray(size);
    } else if (typeChoice == 3) {
        inputType = "Reversed";
        arr = generateReversedArray(size);
    } else {
        std::cout << "\nInvalid input type.\n";
        return;
    }

    std::cout << "\nRunning " << algorithm << " on " << size << " elements (" << inputType 
              << " input) with -O" << optLevel << "...\n";

    const int runs = 5;
    std::vector<long long> runTimes;
    runTimes.reserve(runs);

    for (int i = 0; i < runs; ++i) {
        long long time = benchmark(algorithm, arr);
        runTimes.push_back(time);
    }

    printStats(runTimes);

    std::string filename = "SingleBenchmark_O" + std::to_string(optLevel) + "_" + algorithm + "_" + inputType + "_" + std::to_string(size) + ".csv";
    createCSVWithHeader(filename);
    for (int i = 0; i < runs; ++i) {
        exportResultToCSV(filename, algorithm, size, inputType, runTimes[i]);
    }

    std::cout << "Results saved to " << filename << "\n";
}

void runFullBenchmarkMatrix(int optLevel) {
    const std::vector<std::string> algorithms = {
        "BubbleSort", "InsertionSort", "MergeSort", "QuickSort", "HeapSort", "STLSort", "ThreadedMergeSort"
    };

    const std::vector<int> sizes = {1000, 10000, 100000};
    const std::vector<std::string> inputTypes = {"Random", "Sorted", "Reversed"};

    const int runs = 5;
    std::string optStr = "O" + std::to_string(optLevel);
    const std::string csvFile = "FullBenchmark_" + optStr + ".csv";

    createCSVWithHeader(csvFile);

    for (const auto &algo : algorithms) {
        for (int size : sizes) {
            if ((algo == "BubbleSort" || algo == "InsertionSort") && size == 100000) {
                std::cout << "\nSkipping " << algo << " with " << size << " elements\n";
                continue;
            }

            for (const auto &inputType : inputTypes) {
                std::cout << "\nBenchmarking " << algo << " with " << size
                          << " elements (" << inputType << "):\n";

                std::vector<int> arr;
                if (inputType == "Random") arr = generateRandomArray(size);
                else if (inputType == "Sorted") arr = generateSortedArray(size);
                else if (inputType == "Reversed") arr = generateReversedArray(size);

                std::vector<long long> runTimes;
                runTimes.reserve(runs);

                for (int i = 0; i < runs; ++i) {
                    long long time = benchmark(algo, arr);
                    runTimes.push_back(time);
                    exportResultToCSV(csvFile, algo, size, inputType, time);
                }

                printStats(runTimes);
            }
        }
    }
}

int main() {
    int optLevel;
    std::cout<<"Enter OptLevel";
    std::cin>>optLevel;

    std::cout << "===== goBench++ CLI =====\n";
    std::cout << "1. Run single benchmark (interactive)\n";
    std::cout << "2. Run full benchmark matrix (auto)\n";
    std::cout << "Choose option: ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        runInteractiveBenchmark(optLevel);
    } else if (choice == 2) {
        runFullBenchmarkMatrix(optLevel);
    } else {
        std::cout << "Invalid option.\n";
    }

    return 0;
}

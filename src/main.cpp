#include <iostream>
#include <vector>
#include "utils.hpp"
#include "sorter.hpp"

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
    case 1:
        algorithm = "BubbleSort";
        break;
    case 2:
        algorithm = "InsertionSort";
        break;
    case 3:
        algorithm = "MergeSort";
        break;
    case 4:
        algorithm = "QuickSort";
        break;
    case 5:
        algorithm = "HeapSort";
        break;
    case 6:
        algorithm = "STLSort";
        break;
    default:
        std::cout << "Invalid choice.\n";
        return 1;
    }

    std::cout << "\nSelect Input Size:\n1. 1,000\n2. 10,000\n3. 100,000\nChoice: ";
    std::cin >> sizeChoice;
    size = (sizeChoice == 1) ? 1000 : (sizeChoice == 2) ? 10000
                                                        : 100000;

    std::cout << "\nSelect Input Type:\n1. Random\n2. Sorted\n3. Reversed\nChoice: ";
    std::cin >> typeChoice;

    if (typeChoice == 1)
        arr = generateRandomArray(size);
    else if (typeChoice == 2)
        arr = generateSortedArray(size);
    else if (typeChoice == 3)
        arr = generateReversedArray(size);
    else
    {
        std::cout << "Invalid input type.\n";
        return 1;
    }

    std::cout << "\nRunning " << algorithm << " on " << size << " elements...\n";
    long long timeTaken = benchmark(algorithm, arr);

    std::cout << " Completed in " << timeTaken << " microseconds.\n";

    return 0;
}

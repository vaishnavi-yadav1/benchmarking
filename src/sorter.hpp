#pragma once
#include <vector>
#include <string>

void bubbleSort(std::vector<int>& arr);
void insertionSort(std::vector<int>& arr);
void mergeSort(std::vector<int>& arr);
void quickSort(std::vector<int>& arr);
void heapSort(std::vector<int>& arr);
void stlSort(std::vector<int>& arr);
void runSort(const std::string &algo, std::vector<int> &arr);

long long benchmark(const std::string &algo, std::vector<int> &arr);
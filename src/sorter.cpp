#include "sorter.hpp"
#include <algorithm>
#include <iostream>
#include <chrono>
#include<thread>

void bubbleSort(std::vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n; ++i) {
        bool swapped = false;
        for (size_t j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

void insertionSort(std::vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            if (j == 0) break; else j--;
        }
        if (j == 0 && arr[0] > key) {
            arr[0] = key;
        } else {
            arr[j + 1] = key;
        }
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSortHelper(std::vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid);
    mergeSortHelper(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void mergeSort(std::vector<int>& arr) {
    if (!arr.empty()) {
        mergeSortHelper(arr, 0, arr.size() - 1);
    }
}



int partition(std::vector<int>& arr, int low, int high) {
    // Pick a random pivot and move it to the end
    int randomPivotIndex = low + rand() % (high - low + 1);
    std::swap(arr[randomPivotIndex], arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Recursive QuickSort helper
void quickSortHelper(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

// Public interface
void quickSort(std::vector<int>& arr) {
    if (!arr.empty()) {
        quickSortHelper(arr, 0, arr.size() - 1);
    }
}


void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = (int)arr.size();

    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}


void threadedmerge(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while(i <= mid && j <= right) {
        if(arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while(i <= mid) temp[k++] = arr[i++];
    while(j <= right) temp[k++] = arr[j++];
    for(int i = 0; i < temp.size(); ++i) arr[left + i] = temp[i];
}

void mergeSortThreaded(std::vector<int>& arr, int left, int right, int depth = 0) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    if (depth <= 2) { // limit depth to prevent too many threads
        std::thread t1(mergeSortThreaded, std::ref(arr), left, mid, depth + 1);
        std::thread t2(mergeSortThreaded, std::ref(arr), mid + 1, right, depth + 1);
        t1.join();
        t2.join();
    } else {
        mergeSortThreaded(arr, left, mid, depth + 1);
        mergeSortThreaded(arr, mid + 1, right, depth + 1);
    }

    threadedmerge(arr, left, mid, right);
}

void threadedMergeSort(std::vector<int>& arr) {
    mergeSortThreaded(arr, 0, arr.size() - 1);
}

void stlSort(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());
}

void runSort(const std::string &algo, std::vector<int> &arr) {
    if (algo == "BubbleSort")
        bubbleSort(arr);
    else if (algo == "InsertionSort")
        insertionSort(arr);
    else if (algo == "MergeSort")
        mergeSort(arr);
    else if (algo == "QuickSort")
        quickSort(arr);
    else if (algo == "HeapSort")
        heapSort(arr);
    else if (algo == "STLSort")
        stlSort(arr);
        else if(algo=="ThreadedMergeSort"){
          threadedMergeSort(arr)  ;
        }
    else
        std::cout << "Sorting algorithm '" << algo << "' not implemented yet.\n";
}

long long benchmark(const std::string &algo, std::vector<int> &arr)
{
    std::vector<int> copyArr = arr;  
    auto start = std::chrono::high_resolution_clock::now();
    runSort(algo, copyArr);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << algo << " took " << duration << " nanoseconds\n";

    return duration;
}
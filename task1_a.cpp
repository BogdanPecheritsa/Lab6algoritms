#include <iostream>
#include <vector>
#include <chrono>
#include <random>

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    std::vector<int> sizes = { 10, 100, 500, 1000, 2000, 5000, 10000 };
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);

    for (int size : sizes) {
        std::vector<int> data(size);
        for (int& d : data) {
            d = dis(gen);
        }

        auto start = std::chrono::high_resolution_clock::now();
        heapSort(data);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        std::cout << "Час, витрачений на пірамідальне сортування для " << size << " елементів: " << duration.count() << " ms\n";
    }

    return 0;
}
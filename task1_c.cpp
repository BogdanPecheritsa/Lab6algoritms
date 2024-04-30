#include <iostream>
#include <vector>
#include <chrono>
#include <random>

void countSort(std::vector<char>& arr) {
    int count[256] = { 0 };
    std::vector<char> output(arr.size());

    for (int i = 0; i < arr.size(); i++)
        count[(unsigned char)arr[i]]++;

    for (int i = 1; i <= 255; i++)
        count[i] += count[i - 1];

    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[(unsigned char)arr[i]] - 1] = arr[i];
        count[(unsigned char)arr[i]]--;
    }

    for (int i = 0; i < arr.size(); i++)
        arr[i] = output[i];
}

int main() {
    std::vector<int> sizes = { 10, 100, 500, 1000, 2000, 5000, 10000 };
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-200, 10);

    for (int size : sizes) {
        std::vector<char> data(size);
        for (char& d : data) {
            d = dis(gen);
        }

        auto start = std::chrono::high_resolution_clock::now();
        countSort(data);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        std::cout << "Час, витрачений на сортування підрахунком для " << size << " елементів: " << duration.count() << " ms\n";
    }

    return 0;
}
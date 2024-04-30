#include <iostream>
#include <vector>
#include <chrono>
#include <random>

int nextGap(int gap) {
    if (gap <= 1)
        return 0;
    return (gap / 2) + (gap % 2);
}

void shellSort(std::vector<float>& arr) {
    int n = arr.size();
    int gap = n / 2;

    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            float temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
        gap = nextGap(gap);
    }
}

int main() {
    std::vector<int> sizes = { 10, 100, 500, 1000, 2000, 5000, 10000 };
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 300.0);

    for (int size : sizes) {
        std::vector<float> data(size);
        for (float& d : data) {
            d = dis(gen);
        }

        auto start = std::chrono::high_resolution_clock::now();
        shellSort(data);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        std::cout << "Час, витрачений на сортування Шелла для " << size << " елементів: " << duration.count() << " ms\n";
    }

    return 0;
}
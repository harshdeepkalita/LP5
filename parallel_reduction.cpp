#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

// Function to find the minimum value in an array sequentially
double sequential_min(const vector<double>& arr) {
    double min_val = arr[0];
    for (double num : arr) {
        if (num < min_val) {
            min_val = num;
        }
    }
    return min_val;
}

// Function to find the maximum value in an array sequentially
double sequential_max(const vector<double>& arr) {
    double max_val = arr[0];
    for (double num : arr) {
        if (num > max_val) {
            max_val = num;
        }
    }
    return max_val;
}

// Function to compute the sum of values in an array sequentially
double sequential_sum(const vector<double>& arr) {
    double sum = 0.0;
    for (double num : arr) {
        sum += num;
    }
    return sum;
}

// Function to compute the average of values in an array sequentially
double sequential_average(const vector<double>& arr) {
    double sum = sequential_sum(arr);
    return sum / arr.size();
}
// Function to find the minimum value in an array using parallel reduction
double parallel_min(const vector<double>& arr) {
    double min_val = arr[0];

    #pragma omp parallel for reduction(min:min_val)
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }

    return min_val;
}

// Function to find the maximum value in an array using parallel reduction
double parallel_max(const vector<double>& arr) {
    double max_val = arr[0];

    #pragma omp parallel for reduction(max:max_val)
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    return max_val;
}

// Function to compute the sum of values in an array using parallel reduction
double parallel_sum(const vector<double>& arr) {
    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); ++i) {
        sum += arr[i];
    }

    return sum;
}

// Function to compute the average of values in an array using parallel reduction
double parallel_average(const vector<double>& arr) {
    double sum = parallel_sum(arr);
    return sum / arr.size();
}

int main() {
    vector<double> arr;
    for (int i = 1; i <= 100000; ++i) {
    arr.push_back(i);
    }

    auto start = high_resolution_clock::now();
    double min_val = sequential_min(arr);
    auto end = high_resolution_clock::now();
    cout << "Sequential Minimum value: " << min_val << " (Time: " << duration_cast<microseconds>(end - start).count() << " microseconds)" << endl;

    start = high_resolution_clock::now();
    double max_val = sequential_max(arr);
    end = high_resolution_clock::now();
    cout << "Sequential Maximum value: " << max_val << " (Time: " << duration_cast<microseconds>(end - start).count() << " microseconds)" << endl;

    start = high_resolution_clock::now();
    double sum = sequential_sum(arr);
    end = high_resolution_clock::now();
    cout << "Sequential Sum: " << sum << " (Time: " << duration_cast<microseconds>(end - start).count() << " microseconds)" << endl;

    start = high_resolution_clock::now();
    double avg = sequential_average(arr);
    end = high_resolution_clock::now();
    cout << "Sequential Average: " << avg << " (Time: " << duration_cast<microseconds>(end - start).count() << " microseconds)" << endl;

    // Parallel computations
    start = high_resolution_clock::now();
    min_val = parallel_min(arr);
    end = high_resolution_clock::now();
    cout << "Parallel Minimum value: " << min_val << " (Time: " << duration_cast<microseconds>(end - start).count() << " microseconds)" << endl;

    start = high_resolution_clock::now();
    max_val = parallel_max(arr);
    end = high_resolution_clock::now();
    cout << "Parallel Maximum value: " << max_val << " (Time: " << duration_cast<microseconds>(end - start).count() << " microseconds)" << endl;

    start = high_resolution_clock::now();
    sum = parallel_sum(arr);
    end = high_resolution_clock::now();
    cout << "Parallel Sum: " << sum << " (Time: " << duration_cast<microseconds>(end - start).count() << " microseconds)" << endl;

    start = high_resolution_clock::now();
    avg = parallel_average(arr);
    end = high_resolution_clock::now();
    cout << "Parallel Average: " << avg << " (Time: " << duration_cast<microseconds>(end - start).count() << " microseconds)" << endl;

    return 0;
}

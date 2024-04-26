#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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
    vector<double> arr = {1,2};

    // Find minimum value
    double min_val = parallel_min(arr);
    cout << "Minimum value: " << min_val << endl;

    // Find maximum value
    double max_val = parallel_max(arr);
    cout << "Maximum value: " << max_val << endl;

    // Compute sum
    double sum = parallel_sum(arr);
    cout << "Sum: " << sum << endl;

    // Compute average
    double avg = parallel_average(arr);
    cout << "Average: " << avg << endl;

    return 0;
}

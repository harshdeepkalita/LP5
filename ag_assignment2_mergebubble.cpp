#include<iostream>
#include<vector>
#include<omp.h>
using namespace std;

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arr[m + 1 + i];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2; 
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void parallel_merge_sort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2; 
        #pragma omp parallel sections
        {
            #pragma omp section
            parallel_merge_sort(arr, l, m);

            #pragma omp section
            parallel_merge_sort(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

void bubble_sort(vector<int>& arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void parallel_bubble_sort(vector<int>& arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        #pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                #pragma omp critical
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6, 7,32,34,65,23,8,1};
    int n = arr.size();


    // Sort using normal merge sort
    vector<int> arr_normal_merge = arr;
    double start_normal_merge = omp_get_wtime();
    merge_sort(arr_normal_merge, 0, n - 1);
    double end_normal_merge = omp_get_wtime();

    // Sort using parallel merge sort
    vector<int> arr_parallel_merge = arr;
    double start_parallel_merge = omp_get_wtime();
    parallel_merge_sort(arr_parallel_merge, 0, n - 1);
    double end_parallel_merge = omp_get_wtime();

    // Sort using normal bubble sort
    vector<int> arr_normal_bubble = arr;
    double start_normal_bubble = omp_get_wtime();
    bubble_sort(arr_normal_bubble, n);
    double end_normal_bubble = omp_get_wtime();

    // Sort using parallel bubble sort
    vector<int> arr_parallel_bubble = arr;
    double start_parallel_bubble = omp_get_wtime();
    parallel_bubble_sort(arr_parallel_bubble, n);
    double end_parallel_bubble = omp_get_wtime();

    // Compare the performance
    double time_normal_merge = end_normal_merge - start_normal_merge;
    double time_parallel_merge = end_parallel_merge - start_parallel_merge;
    double time_normal_bubble = end_normal_bubble - start_normal_bubble;
    double time_parallel_bubble = end_parallel_bubble - start_parallel_bubble;

    cout << "Normal Merge Sort Time: " << time_normal_merge << " seconds" << endl;
    cout << "Parallel Merge Sort Time: " << time_parallel_merge << " seconds" << endl;
    cout << "Normal Bubble Sort Time: " << time_normal_bubble << " seconds" << endl;
    cout << "Parallel Bubble Sort Time: " << time_parallel_bubble << " seconds" << endl;
}
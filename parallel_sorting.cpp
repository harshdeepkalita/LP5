#include<iostream>
#include<omp.h>
#include<bits/stdc++.h>

using namespace std;



void merge(int arr[], int l, int m, int r) {
  int n1 = m - l + 1;
  int n2 = r - m;

  int L[n1], R[n2];

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

void parallel_merge_sort(int arr[], int l, int r) {
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

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void parallel_bubble_sort(int arr[], int size){
    int array[size];
    
    for(int i = 0; i < size; i++){
        array[i] = arr[i];
    }
    

    for(int k = 0; k < size; k++){
        if(k % 2 == 0){
            #pragma omp parallel for
            for(int i = 1; i < size - 1; i += 2){
                if(array[i] > array[i+1]){
                    swap(array[i], array[i+1]);
                }
            }
            
        } else {
            #pragma omp parallel for
            for(int i = 0; i < size - 1; i += 2){
                if(array[i] > array[i+1]){
                    swap(array[i], array[i+1]);
                }
            }
        }
    }

    
    cout << "Parallel Bubble Sort Result: ";
    for(int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}


int main() {
    int size = 5;
    int array[size] = {9, 3, 1, 5, 13};
    parallel_bubble_sort(array, size);
    
    parallel_merge_sort(array, 0, size - 1);
    cout << "Parallel Merge Sort Result: ";
  
    for (int i = 0; i < size; i++) {
    cout << array[i] << " ";
    }
  
    cout << endl;
  
    return 0;
}


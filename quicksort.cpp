#include <iostream>
#include <stdlib.h>
#include <omp.h>

using namespace std;

#define SIZE 100

void generateRandomBySwap(int *arr, int n) {
    for(int i = 0; i < n; i++) {
        arr[i] = i;
    }
    for(int i = 0; i < n; i++) {
        int j = rand() % n;
        int t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}

void display(int *arr, int n) {
    for(int i = 0; i < n; i++) {
        cout<<arr[i]<<"|";
    }
    cout<<"\n";
}

int partition(int arr[], int start, int end) {
    int pivot = arr[end];
    int i = start - 1;

    for(int j = start; j <= end - 1; j++) {
        if(arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[end];
    arr[end] = temp;

    return (i + 1);
}

void quicksort(int arr[], int start, int end) {
    int index;
    if(start < end) {
        index = partition(arr, start, end);

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                quicksort(arr, start, index - 1);
            }
            #pragma omp section
            {
                quicksort(arr, index + 1, end);
            }
        }
    }
}

int main() {
    int n = SIZE;
    int arr[n];
    generateRandomBySwap(arr, n);

    cout<<"List before sorting:\n";
    display(arr, n);

    double start = omp_get_wtime();

    quicksort(arr, 0, n - 1);

    double stop = omp_get_wtime();

    cout<<"List after sorting:\n";
    display(arr, n);
    cout<<"Time: "<<stop - start<<"\n";
}

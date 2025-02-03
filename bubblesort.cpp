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

int main() {
    int n = SIZE;
    int arr[n];
    generateRandomBySwap(arr, n);

    cout<<"List before sorting:\n";
    display(arr, n);

    double start = omp_get_wtime();

    for(int i = 0; i < n - 1; i++) {
        int first = i % 2;
        #pragma omp parallel for default(none), shared(arr, first, n)
        for(int j = first; j < n - 1; j++) {
            if(arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    double stop = omp_get_wtime();

    cout<<"List after sorting:\n";
    display(arr, n);
    cout<<"Time: "<<stop - start<<"\n";
}

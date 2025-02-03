#include <iostream>
#include <stdlib.h>
#include <omp.h>

#define MAX_SIZE 100

using namespace std;

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

void merge(int *arr, int n, int *temp) {
    int i = 0, j = n / 2, t = 0;
    while(i < n / 2 && j < n) {
        if(arr[i] < arr[j]) {
            temp[t] = arr[i];
            t++;
            i++;
        } else {
            temp[t] = arr[j];
            t++;
            j++;
        }
    }
    while(i < n / 2) {
        temp[t] = arr[i];
        t++;
        i++;
    }
    while(j < n) {
        temp[t] = arr[j];
        t++;
        j++;
    }

    memcpy(arr, temp, n * sizeof(int));
}

void mergesort(int *arr, int n, int *temp) {
    if (n < 2) {
        return;
    }

    #pragma omp task firstprivate (arr, n, temp)
    mergesort(arr, n / 2, temp);

    #pragma omp task firstprivate (arr, n, temp)
    mergesort(arr + (n / 2), n - (n / 2), temp);

    #pragma omp taskwait

    merge(arr, n, temp);
}

int main() {
    int n = MAX_SIZE;
    int data[MAX_SIZE], temp[MAX_SIZE];

    generateRandomBySwap(data, n);
    cout<<"List before sorting:\n";
    display(data, n);
    double start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        mergesort(data, n, temp);
    }
    double stop = omp_get_wtime();
    cout<<"List after sorting:\n";
    display(data, n);
    cout<<"Time: "<<stop - start<<"\n";
}

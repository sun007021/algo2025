#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findPivot(int l, int r) {
    int pivot = rand()%(r-l+1) + l;
    return pivot;
}

void swap(int *arr, int a, int b) {
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

int partition(int *arr, int l, int r, int k) {
    swap(arr, k, r);
    int i = l;
    int j = r-1;
    while (i<=j) {
        while (arr[i]<arr[r] && i<r) {
            i++;
        }
        while (arr[j]>=arr[r] && j>l) {
            j--;
        }
        if (i<j) {
            swap(arr, i,j);
        }
    }
    swap(arr, i, r);
    return i;
}

void quickSort(int *arr, int l, int r) {
    if (l>=r) {
        return;
    }
    int pivotIndex = findPivot(l, r);
    int partitionIndex = partition(arr, l, r, pivotIndex);
    quickSort(arr, l, partitionIndex-1);
    quickSort(arr, partitionIndex+1, r);
}
int main() {
    srand(time(NULL));
    //input
    int n;
    scanf("%d", &n);
    int *arr = malloc(sizeof(int)*n);
    for (int i=0; i<n; i++) {
        scanf("%d",&arr[i]);
    }

    quickSort(arr, 0, n-1);

    //print
    for (int i=0; i<n; i++) {
        printf(" %d",arr[i]);
    }
    free(arr);
    return 0;
}
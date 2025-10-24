#include <stdio.h>
#include <stdlib.h>
void swap (int *arr, int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}
int main() {
    int n;
    scanf("%d", &n);

    int *arr = malloc(n*sizeof(*arr));
    if (!arr) {
        return 1;
    }

    // input
    for (int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }

    // 삽입 정렬
    for (int i=1; i<n; i++) {
        for (int j = i-1; j >= 0 && arr[j+1] < arr[j]; j--) {
            swap(arr,j+1,j);
        }
    }

    // print arr
    for (int i=0; i<n; i++) {
        printf(" %d", arr[i]);
    }

    // free memory
    free(arr);
    return 0;
}
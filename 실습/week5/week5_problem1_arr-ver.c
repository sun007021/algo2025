#include <stdio.h>
#include <stdlib.h>
void merge(int *arr, int l, int m, int r) {
    int *l1 = malloc(sizeof(int)*(m-l+1));
    int *l2 = malloc((sizeof(int)*(r-m)));
    for (int i=l; i<=m; i++) {
        l1[i-l] = arr[i];
    }
    for (int i=m+1; i<=r; i++) {
        l2[i-m-1] = arr[i];
    }
    int l1i, l2i;
    l1i=0;
    l2i=0;
    int arri=l;
    while (l1i<=m-l && l2i<=r-m-1) {
        if (l1[l1i]<l2[l2i]) {
            arr[arri] = l1[l1i];
            arri++;
            l1i++;
        }
        else {
            arr[arri] = l2[l2i];
            arri++;
            l2i++;
        }
    }
    while (l1i<=m-l) {
        arr[arri] = l1[l1i];
        arri++;
        l1i++;
    }
    while (l2i<=r-m-1) {
        arr[arri] = l2[l2i];
        arri++;
        l2i++;
    }

    free(l1);
    free(l2);
}
void mergeSort(int *arr, int l, int r) {
    if (l>=r) {
        return;
    }
    mergeSort(arr, l, (l+r)/2);
    mergeSort(arr, (l+r)/2+1, r);//m+1로 넣어주어야함
    merge(arr, l, (l+r)/2, r);
}

void printList(int *arr, int n) {
    for (int i=0; i<n; i++) {
        printf(" %d",arr[i]);
    }
    printf("\n");
}
int main() {
    int n;
    scanf("%d", &n);
    int *arr = malloc(sizeof(int)*n);
    for (int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }

    mergeSort(arr, 0, n-1);
    printList(arr, n);
    free(arr);
    return 0;
}
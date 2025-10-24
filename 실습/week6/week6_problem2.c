#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int search(int* arr, int n, int k) {
    int l = 0;
    int r = n-1;
    int mid;
    while (l<=r) {
        mid = (l+r)/2;
        if (arr[mid]==k) {
            return mid;
        }
        else if (arr[mid]>k) {
            r = mid-1;
        }
        else {
            l = mid+1;
        }
    }
    if (arr[l]>=k) {
        return l;
    }
    else {
        return n;
    }

}
int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int* arr = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf(" %d", search(arr, n, k));

    free(arr);
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int search(int* arr, int l, int r, int k) {
    if (l > r) {
        return -1;
    }
    int mid = (l + r) / 2;
    if (arr[mid] == k) {
        return mid;
    }

    if (k < arr[mid]) {
        return search(arr, l, mid - 1, k);
    }
    else {
        int p = search(arr, mid + 1, r, k);
        if (p == -1){
            if (arr[mid]< k) {
                return mid;
            }
            else {
                return -1;
            }
        }
        else {
            return p;
        }
    }

}
int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int* arr = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf(" %d", search(arr, 0, n - 1, k));

    free(arr);
    return 0;
}
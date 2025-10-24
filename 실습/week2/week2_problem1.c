#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int *arr = malloc(n*sizeof( *arr));
    if (!arr) {
        return 1;
    }
    for (int i=0; i<n; i++) { // 입력
        scanf("%d", &arr[i]);
    }

    // 제자리 선택 정렬
    int max_index;
    int temp;
    for (int i=n-1; i>=0; i--) {
        max_index = 0;
        for (int j=0; j<=i; j++) {
            if (arr[j]>arr[max_index]) {
                max_index = j;
            }
        }
        // swap
        temp = arr[i];
        arr[i] = arr[max_index];
        arr[max_index] = temp;
    }

    //출력
    for (int i=0; i<n; i++) {
        printf(" %d", arr[i]);
    }

    free(arr);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h> //mac이라 clock_gettime함수 이용해 시간 측정
#include <string.h>

void swap(int *arr, int a, int b) {// 교환 함수
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void selection_sort(int *arr, int n) { // 선택 정렬
    int min_index;
    for (int i = 0; i < n - 1; i++) { // 앞부터 탐색 시작
        min_index = i;
        for (int j = i + 1; j < n; j++) { // 해당 칸의 뒤쪽 원소들 중 가장 작은 값을 찾음
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        swap(arr, i, min_index); // 찾은 최소값과 현재 인덱스 위치의 값을 교환
    }
}

void insertion_sort(int *arr, int n) {
    // 삽입 정렬
    for (int i = 1; i < n; i++) {
        for (int j = i - 1; j >= 0 && arr[j + 1] < arr[j]; j--) {// 바로 뒤의 값을 앞 원소들과 비교해 순서상 들어갈 위치에 넣는다.
            swap(arr, j + 1, j); // 이를 위해서 뒤쪽 값들을 한칸씩 뒤로 이동시키고 빈 자리에 삽입
        }
    }
}
// 시간 측정 함수
double measure_time(void (*sort_func)(int*, int), int *arr, int n) {// mac환경에서 진행하기에 clock_gettime함수 이용
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);//시작 시간
    sort_func(arr, n);
    clock_gettime(CLOCK_MONOTONIC, &end);//종료시간
    return (end.tv_sec - start.tv_sec) * 1000.0 + //시작과 종료시간의 차를 통해 ms단위로 함수 실행 속도 계산
           (end.tv_nsec - start.tv_nsec) / 1e6;
}

// 배열 생성 함수
void make_random_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }
}

void reverse_array(int *arr, int n) { // 배열 역순으로 뒤집는 함수
    for (int i = 0; i < n / 2; i++) {
        swap(arr, i, n - 1 - i);
    }
}

int main() {
    srand(time(NULL));// 랜덤 값을 위해 srand 설정
    int n;
    scanf("%d", &n);

    int *base = malloc(n * sizeof(int));
    int *arr_selection = malloc(n * sizeof(int));
    int *arr_insertion = malloc(n * sizeof(int));
    if (!base || !arr_selection || !arr_insertion) return 1;

    // A: 랜덤 input
    make_random_array(base, n);
    memcpy(arr_selection, base, n * sizeof(int));//배열 동일하게 초기화
    memcpy(arr_insertion, base, n * sizeof(int));// 배열 동일하게 초기화
    printf("[랜덤 입력]\n");
    printf("선택 정렬: %f ms\n", measure_time(selection_sort, arr_selection, n));
    printf("삽입 정렬: %f ms\n\n", measure_time(insertion_sort, arr_insertion, n));

    // B: 정렬 input
    memcpy(base, arr_selection, n * sizeof(int)); // 이미 정렬된 상태 활용
    memcpy(arr_selection, base, n * sizeof(int));
    memcpy(arr_insertion, base, n * sizeof(int));
    printf("[정렬된 입력]\n");
    printf("선택 정렬: %f ms\n", measure_time(selection_sort, arr_selection, n));
    printf("삽입 정렬: %f ms\n\n", measure_time(insertion_sort, arr_insertion, n));

    // ----------- 실험 3: 역순 입력 -----------
    reverse_array(base, n);
    memcpy(arr_selection, base, n * sizeof(int));
    memcpy(arr_insertion, base, n * sizeof(int));
    printf("[역순 입력]\n");
    printf("선택 정렬: %f ms\n", measure_time(selection_sort, arr_selection, n));
    printf("삽입 정렬: %f ms\n\n", measure_time(insertion_sort, arr_insertion, n));

    free(base);
    free(arr_selection);
    free(arr_insertion);
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


void swap(int* arr, int i, int j) {
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void downHeap(int* heap, int v, int n) {
	int greater;
	while (v*2 <= n) {
		greater = v * 2;
		if (v * 2 + 1 <= n) {
			if (heap[greater] < heap[v * 2 + 1]) {
				greater = v * 2 + 1;
			}
		}
		if (heap[v] < heap[greater]) {
			swap(heap, v, greater);
			v = greater;
		}
		else {
			break;
		}
	}
}

void rBuildHeap(int* heap, int v, int n) {
	if (v > n/2) {
		return;
	}
	if (v < 1) return;
	rBuildHeap(heap, v*2, n);
	rBuildHeap(heap, v * 2 + 1, n);
	downHeap(heap, v, n);
}

void buildHeap(int* heap, int v, int n) {
	for (int i = n / 2; i >= 1; i--) {
		downHeap(heap, i, n);
	}
}

void printHeap(int* heap, int n) {
	for (int i = 1; i <= n; i ++ ) {
		printf(" %d", heap[i]);
	}
	printf("\n");
}
int main() {
	int heap[100];
	int n = 0; //heap size
	int k;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &heap[i]);
	}
	rBuildHeap(heap, 1, n);
	printHeap(heap, n);
	return 0;
}
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

void upHeap(int* heap, int v, int n) {
	if (v <= 1 || v > n) {
		return;
	}
	int parent = v / 2;
	if (heap[parent] < heap[v]) {
		swap(heap, parent, v);
		upHeap(heap, parent, n);
	}
	else{
		return;
	}
}

void upHeap(int* heap, int v, int n) {
	while (v > 1 && heap[v / 2] < heap[v]) {
		swap(heap, v, v / 2);
		v /= 2;
	}
}

int delete(int* heap, int n) {
	int k = heap[1];
	heap[1] = heap[n];
	n -= 1;
	downHeap(heap, 1, n);
	return  k;
}

void insert(int* heap, int k, int n) {
	heap[n] = k;
	upHeap(heap, n, n);
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
	char cmd;
	int k;
	while (1) {
		scanf(" %c", &cmd);
		if (cmd == 'i') {
			scanf("%d", &k);
			n += 1;
			insert(heap, k, n);
			printf("0\n");
		}
		else if (cmd == 'd') {
			printf("%d\n", delete(heap, n));
			n -= 1;
		}
		else if (cmd == 'p') {
			printHeap(heap, n);
		}
		else {
			break;
		}
	}

	return 0;
}
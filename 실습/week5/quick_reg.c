#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 1. 단일 연결 리스트 노드 구조체 정의
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 노드 생성
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 리스트 메모리 해제
void freeList(Node* head) {
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

// 리스트 출력
void printList(Node* head) {
    while (head != NULL) {
        printf(" %d", head->data);
        head = head->next;
    }
    printf("\n");
}

// 노드 a와 b의 '데이터'를 교환
void swapData(Node* a, Node* b) {
    int tmp = a->data;
    a->data = b->data;
    b->data = tmp;
}

// 2. findPivot (연결 리스트 버전)
// l부터 r까지 노드 개수를 세고(O(n)), k번째 노드를 찾아 반환(O(n))
Node* findPivot(Node* l, Node* r) {
    if (l == r) return l;

    // 1. 개수 세기
    int count = 0;
    Node* curr = l;
    while (curr != r && curr != NULL) {
        count++;
        curr = curr->next;
    }
    count++; // r 노드 포함

    // 2. 임의의 인덱스 선택
    int k = rand() % count;

    // 3. k번째 노드 찾기
    curr = l;
    while (k-- > 0) {
        curr = curr->next;
    }
    return curr;
}

// 3. partition (연결 리스트 버전 - Lomuto 파티션)
// l부터 r까지의 범위를 정렬하고 '피벗 노드'를 반환
// 원본 코드와 달리, pivot을 정하고 Lomuto 스킴을 사용
Node* partition(Node* l, Node* r, Node* pivot) {
    // 피벗을 맨 끝(r)으로 보냄
    swapData(pivot, r);
    int pivotVal = r->data;

    // i는 'pivotVal보다 작은 값'들의 마지막 위치를 추적
    Node* i = l;

    // j는 l부터 r 직전까지 순회
    for (Node* j = l; j != r; j = j->next) {
        if (j->data < pivotVal) {
            swapData(i, j);
            i = i->next;
        }
    }
    
    // 피벗(r)을 올바른 위치(i)로 가져옴
    swapData(i, r);
    return i; // 피벗의 최종 위치 노드 반환
}

// 4. quickSort (연결 리스트 재귀 함수)
void quickSort(Node* l, Node* r) {
    // 0개 또는 1개의 노드만 있거나, 범위가 유효하지 않으면 종료
    if (l == NULL || r == NULL || l == r) {
        return;
    }
    
    // l이 r보다 뒤에 있는 경우 (재귀 호출 시 발생 가능)
    Node* check = l;
    while(check != r && check != NULL) check = check->next;
    if (check == NULL) return;


    // 1. 피벗 선택 (O(n))
    Node* pivotNode = findPivot(l, r);
    
    // 2. 파티션 (O(n))
    Node* partitionNode = partition(l, r, pivotNode);

    // 3. 재귀 호출 (왼쪽 부분)
    // partitionNode의 '이전 노드'를 찾아야 함 (O(n))
    if (partitionNode != l) {
        Node* prevPivot = l;
        while (prevPivot->next != partitionNode) {
            prevPivot = prevPivot->next;
        }
        quickSort(l, prevPivot);
    }
    
    // 4. 재귀 호출 (오른쪽 부분)
    quickSort(partitionNode->next, r);
}

int main() {
    srand(time(NULL));
    
    int n, data;
    scanf("%d", &n);
    
    if (n <= 0) return 0;

    // 1. 연결 리스트로 입력받기
    Node* head = NULL;
    Node* tail = NULL;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        Node* newNode = createNode(data);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // 2. 퀵 정렬 호출 (head와 tail 전달)
    quickSort(head, tail);

    // 3. 결과 출력
    printList(head);
    
    // 4. 메모리 해제
    freeList(head);
    
    return 0;
}

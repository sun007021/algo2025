#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

typedef struct MaxResult {
    int max1; // 서브트리의 루트에서 가장 깊은 잎까지의 최대 경로 합
    int max2; // 서브트리 내에서 찾은 f(a,b)의 최대값
} MaxResult;

Node *create_node(int key); // node 생성
Node *buildCompleteBinaryTree(int arr[], int n); // 입력받은 배열을 완전이진 연결트리로 변환
void swap(Node *a, Node *b); // node key값 교환
void downHeap(Node *node); // downheap
void rBuildHeap(Node *node); // 상향식 힙생성 (재귀)
MaxResult max(Node *v, int ancestors_sum); // f(a,b) 계산
void free_tree(Node *root); // 트리 노드들 메모리 할당 해제

int main() {
    // 입력
    int n;
    scanf("%d", &n);
    int *values = malloc(n * sizeof(int));
    if (!values) return 1; // 메모리 할당 검사
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }

    Node *root = buildCompleteBinaryTree(values, n); // 입력값 완전이진트리 연결트리로 변환
    rBuildHeap(root); // 상향식 최소힙 생성

    // f(a,b)의 최댓값 계산
    // 최초 호출 시 조상의 합은 0
    MaxResult result = max(root, 0);
    printf("%d\n", result.max2);

    // 동적할당 메모리 해제
    free(values);
    free_tree(root);
    return 0;
}

Node *create_node(int key) { // 노드 생성
    Node *node = malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

Node *buildCompleteBinaryTree(int arr[], int n) { // 배열 이진 연결 트리로 변환
    if (n==0) return NULL;
    Node **nodes = malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        nodes[i] = create_node(arr[i]);
    }
    for (int i = 0; i < n; i++) {// 배열에서 각 노드의 자식노드들을 찾아 연결리스트 노드 구조체의 자식들 포인터에 연결시켜줌
        int left_idx = 2 * i + 1;
        int right_idx = 2 * i + 2;

        if (left_idx < n) {
            nodes[i]->left = nodes[left_idx];
            nodes[left_idx]->parent = nodes[i];
        }
        if (right_idx < n) {
            nodes[i]->right = nodes[right_idx];
            nodes[right_idx]->parent = nodes[i];
        }
    }

    Node *root = nodes[0];
    free(nodes);
    return root; // 연결트리의 루트 노드 반환
}

void swap(Node *a, Node *b) {// a, b노드의 key값 교환, 원소가 key값 하나라 key값만 교환해도 실제 노드를 교환한 것과 같은 역할을 함
    int temp = a->key;
    a->key = b->key;
    b->key = temp;
}

void downHeap(Node *node) {// 최소힙을 위한 downheap
    if (!node || (!node->left && !node->right)) return;

    Node *smaller = node;
    if (node->left && node->left->key < smaller->key) {
        smaller = node->left;
    }
    if (node->right && node->right->key < smaller->key) {
        smaller = node->right;
    }
    if (smaller != node) { // 자식중 더 작은 값을 가진 노드와 위치 swap
        swap(node, smaller);
        downHeap(smaller); // 재귀적으로 최소힙 구조를 유지하도록 갱신
    }
}

void rBuildHeap(Node *node) { // 재귀를 통한 상향식 힙 생성
    if (!node) return;
    rBuildHeap(node->left);
    rBuildHeap(node->right);
    downHeap(node);
}

MaxResult max(Node *v, int ancestors_sum) { // f(a,b) 계산
    MaxResult result;
    // 베이스 케이스: 잎 노드
    if (!v->left && !v->right) {
        result.max1 = v->key;
        result.max2 = 0;
        return result;
    }

    // 재귀 호출
    MaxResult left = max(v->left, ancestors_sum + v->key);
    MaxResult right = max(v->right, ancestors_sum + v->key);

    // max1 계산
    if (left.max1 > right.max1) {
        result.max1 = v->key + left.max1;
    } else {
        result.max1 = v->key + right.max1;
    }


    // cross: v가 a,b의 최소공통조상일 때의 f(a,b) 값
    // (왼쪽 경로 합) + (오른쪽 경로 합) + (현재 노드 값) + (조상 경로 합)
    int cross = left.max1 + right.max1 + v->key + ancestors_sum;

    // submax: 자식 서브트리 내에서 찾은 f(a,b)의 최대값
    int submax = (left.max2 > right.max2 ? left.max2 : right.max2);

    // 둘 중 더 큰 값을 현재 서브트리의 f(a,b) 최대값으로 설정
    if (cross > submax) {
        result.max2 = cross;
    } else {
        result.max2 = submax;
    }
    return result;
}

void free_tree(Node *root) {// 메모리 할당 해제
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

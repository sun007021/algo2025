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

Node *create_node(int key);
void swap(Node *a, Node *b);
Node *buildCompleteBinaryTree(int arr[], int n);
void downHeap(Node *node);
void rBuildHeap(Node *node);
void free_tree(Node *root);
MaxResult max(Node *v, int ancestors_sum);

int main() {
    // 입력
    int n;
    scanf("%d", &n);
    int *values = malloc(n * sizeof(int));
    if (!values) return 1;
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }

    // 상향식으로 최소힙 생성
    Node *root = buildCompleteBinaryTree(values, n);
    rBuildHeap(root);

    // f(a,b)의 최댓값 계산
    // 최초 호출 시 조상의 합은 0
    MaxResult result = max(root, 0);
    printf("%d\n", result.max2);
    
    free(values);
    free_tree(root);
    return 0;
}

MaxResult max(Node *v, int ancestors_sum) {
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
    
    // max1 계산 (기존 로직과 동일)
    if (left.max1 > right.max1) {
        result.max1 = v->key + left.max1;
    } else {
        result.max1 = v->key + right.max1;
    }

    // *** 여기가 핵심 수정 부분 ***
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

void swap(Node *a, Node *b) {
    int temp = a->key;
    a->key = b->key;
    b->key = temp;
}

void downHeap(Node *node) {
    if (!node || (!node->left && !node->right)) return;

    Node *smaller = node;
    if (node->left && node->left->key < smaller->key) {
        smaller = node->left;
    }
    if (node->right && node->right->key < smaller->key) {
        smaller = node->right;
    }
    if (smaller != node) {
        swap(node, smaller);
        downHeap(smaller);
    }
}

void rBuildHeap(Node *node) {
    if (!node) return;
    rBuildHeap(node->left);
    rBuildHeap(node->right);
    downHeap(node);
}

Node *create_node(int key) {
    Node *node = malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

Node *buildCompleteBinaryTree(int arr[], int n) {
    if (n==0) return NULL;
    Node **nodes = malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        nodes[i] = create_node(arr[i]);
    }
    for (int i = 0; i < n; i++) {
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
    return root;
}

void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
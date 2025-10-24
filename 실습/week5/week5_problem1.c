#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* next;
}Node;

Node *createNode(int key) {
    Node *node = malloc(sizeof(Node));
    node->next = NULL;
    node->key = key;
    return node;
}
Node *partition(Node *v, int p) {
    for (int i=1; i<p && v->next!=NULL; i++) {//1로 시작하는거 중요
        v = v->next;
    }
    //v전까지는 next = NULL로 연결 끊어줘야함 따라서 반복 하나 줄이고 여기서 전노드 처리후 next노드 반환
    Node *L2 = v->next;
    v->next = NULL;
    return L2;
}
Node *merge(Node *L1, Node *L2) {
    Node start;
    Node *v = &start;
    while (L1 && L2) {
        if (L1->key > L2->key) {
            v->next=L2;
            L2 = L2->next;
            v = v->next;
        }
        else {
            v->next=L1;
            L1=L1->next;
            v = v->next;
        }
    }
    v->next = (L1)?L1:L2;
    /*while (L1!=NULL) { // 이렇게 반복문처리하는게 아니라 L1혹은 L2중에 남은걸 통으로 첫 노드만 v에 연결하면 됨
        v->next = L1;
        v = v->next;
        L1 = L1->next;
    }
    while (L2!=NULL) {
        v->next = L2;
        v = v->next;
        L2 = L2->next;
    }*/
    return start.next;
}

Node *mergeSort(Node *v, int p) {
    if (p<=1) {
        return v;
    }
    // p연산 따로 하면안되고 함수 호출시 /2해줘야 L2에서는 홀수개일때 p-p/n으로 남은 개수 채워줄 수 있음
    Node *pivot = partition(v, p/2);
    Node *L1 = mergeSort(v, p/2);
    Node *L2 = mergeSort(pivot, p-p/2);// 여기서 p라고 써서 틀림 ex) n=3이면 p=1인데 그럼 왼쪽 오른쪽 모두 1만 됨 따라서 p는 전체에서 뺀 값으로
    return merge(L1,L2);
}

void freeAll(Node *v) { // 암기
    Node *cur = v;
    Node *next;
    while (cur !=NULL) {
        next=cur->next;
        free(cur);
        cur = next;
    }
}

void printList(Node *root) {
    while (root!=NULL) {
        printf(" %d",root->key);
        root = root->next;
    }
    printf("\n");
}
int main() {
    int n;
    scanf("%d", &n);
    int k;
    scanf("%d", &k);
    Node *root = createNode(k);
    Node *v = root;
    for (int i=1; i<n; i++) {
        scanf("%d", &k);
        Node *new = createNode(k);
        v->next = new;
        v = new;
    }

    root = mergeSort(root, n);
    printList(root);
    freeAll(root);
    return 0;
}
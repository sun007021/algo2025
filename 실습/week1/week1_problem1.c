#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char e;
    struct Node* prev;
    struct Node* next;
}Node;

typedef struct {
    Node *header;
    Node *trailer;
    int size;
}DList;

void initList(DList *list) {
    list->header = malloc(sizeof(Node));
    list->trailer = malloc(sizeof(Node));
    list->header->next = list->trailer;
    list->trailer->prev = list->header;
    list->header->prev = NULL;
    list->trailer->next = NULL;
    list->size = 0;
}
void add(DList *list, int r, char e) {
    if (r < 1 || r >list->size+1) {
        printf("invalid position\n");
        return;
    }
    // 새 노드 생성 및 e 할당
    Node *newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("memory error");
        return;
    }
    newNode->e = e;

    Node *p = list->header; // 리스트 탐색용 포인터
    for (int i = 1; i < r; i++) { // r번째 위치까지 포인터 이동
        p = p->next;
    }
    Node *succ = p->next;

    newNode->next = succ;
    newNode->prev = p;
    p->next = newNode;
    succ->prev = newNode;

    list->size++;
}

void delete(DList *list, int r){
    if (r<1 || r>list->size) {
        printf("invalid position\n");
        return;
    }
    Node *p = list->header->next;
    for (int i=1; i<r; i++) {
        p = p->next;
    }
    Node *pred = p->prev;
    Node *succ = p->next;

    pred->next = succ;
    succ->prev = pred;
    free(p);

    list->size--;
}

void get(DList *list, int r) {
    if (r<1 || r>list->size) {
        printf("invalid position\n");
        return;
    }
    Node *p = list->header->next;
    for (int i=1; i<r; i++) {
        p = p->next;
    }
    printf("%c\n",p->e);
}

void print(DList *list) {
    Node *p = list->header;
    for (int i=0; i<list->size; i++) {
        p = p->next;
        printf("%c",p->e);
    }
    printf("\n");
}

void freeAll(DList *list) {
    Node *p = list->header;
    while (p!=list->trailer) {
        Node *succ = p->next;
        free(p);
        p = succ;
    }
    free(p);
}
int main(void) {
    //초기 선언
    DList list;
    initList(&list);

    int n; // 연산의 개수
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char command, element;
        int r;
        getchar(); //개행 버퍼 제거
        scanf("%c", &command);
        if (command=='A') {
            scanf("%d %c", &r, &element);
            add(&list, r, element);
        }
        else if (command=='D') {
            scanf("%d", &r);
            delete(&list, r);
        }
        else if (command=='G') {
            scanf("%d", &r);
            get(&list, r);
        }
        else if (command=='P') {
            print(&list);
        }
        else {
            printf("not supported command.");
        }
    }

    freeAll(&list);
    return 0;
}

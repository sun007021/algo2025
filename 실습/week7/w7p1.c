#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* lChild;
    struct Node* rChild;
    struct Node* parent;
    int key;
}Node;

Node *createNode(int key) {
    Node *node = malloc(sizeof(Node));
    node->lChild=NULL;
    node->rChild=NULL;
    node->parent=NULL;
    node->key = key;

    return node;
}
int isExternal(Node *w) {
    if (w->lChild == NULL && w->rChild==NULL) {
        return 1;
    }
    return 0;
}

int isInternal(Node *w) {
    if (isExternal(w)) {
        return 0;
    }
    return 1;
}
Node* findElement(Node* root, int k) {
    Node* v = root;
    while (isInternal(v)) {
        if (k==v->key) {
            return v;
        }
        else if (k< v->key) {
            v = v->lChild;
        }
        else
            v = v->rChild;
    }
    return v;// leaf
}
Node *sibling(Node *z) {
    if (z->parent==NULL) {
        return NULL;
    }
    Node *w = z->parent;
    if (z==w->lChild) {
        return w->rChild;
    }
    else {
        return w->lChild;
    }
}
void insertNode(Node* root, int k) {
    Node *v = findElement(root, k);
    if (isInternal(v)) {
        return;
    }
    v->lChild = createNode(0);
    v->rChild = createNode(0);
    v->lChild->parent = v;
    v->rChild->parent = v;
    v->key = k;
}
void reduceExternal(Node **root, Node* z) {
    Node *w = z->parent;
    Node *zs = sibling(z);
    if (w->parent==NULL) {
        zs->parent = NULL;
        *root = zs;
    }
    else {
        Node *g = w->parent;
        zs->parent = g;
        if (g!=NULL) {
            if (w==g->lChild) {
                g->lChild=zs;
            }
            else {
                g->rChild=zs;
            }
        }
    }
    free(w);
    free(z);
}
Node *inOrderSucc(Node *w) {
    w = w->rChild;
    if (isExternal(w)) return NULL;
    while (isInternal(w->lChild)) {
        w = w->lChild;
    }
    return w;
}
int delete(Node **root, int k){
    Node *v = findElement(*root, k);
    if (isExternal(v)) {
        return 0;
    }
    if (isExternal(v->lChild)) {
        reduceExternal(root, v->lChild);
    }
    else if (isExternal((v->rChild))) {
        reduceExternal(root, v->rChild);
    }
    else {
        Node *y = inOrderSucc(v);
        v->key= y->key;
        reduceExternal(root, y->lChild);
    }
    return 1;
}
void printTree(Node *root) {
    if (isExternal(root)) {
        return;
    }
    else {
        printf(" %d", root->key);
        printTree(root->lChild);
        printTree(root->rChild);
    }
}
void freeAll(Node* w) {// 트리 동적할당 해제

    if (w == NULL) return;
    if (isExternal(w)) {free(w); return;}
    freeAll(w->lChild);
    freeAll(w->rChild);
    free(w);
}
int main() {
    char cmd;
    int k;
    Node *root = createNode(0);

    while (1) {
        scanf(" %c",&cmd);
        if (cmd == 'i') {
            scanf("%d", &k);
            insertNode(root, k);
        }
        else if (cmd =='s') {
            scanf("%d", &k);
            Node *node = findElement(root, k);
            if (isExternal(node)) {
                printf("X\n");
            }
            else {
                printf("%d\n", node->key);
            }
        }
        else if (cmd =='d') {
            scanf("%d", &k);
            if (delete(&root, k)) {
                printf("%d\n",k);
            }
            else {
                printf("X\n");
            }
        }
        else if (cmd =='p') {
            printTree(root);
            printf("\n");
        }
        else {
            break;
        }
    }
    freeAll(root);
    return 0;
}
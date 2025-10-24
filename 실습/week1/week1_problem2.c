#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int x;
    struct Node* left_child;
    struct Node* right_child;
}Node;
Node *create_node(int x) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        printf("memory allocate error.");
        return NULL;
    }

    node->x = x;
    node->left_child = NULL;
    node->right_child = NULL;
    return node;
}

void insert_node(Node *root, int parent, int left_child, int right_child) {
    if (root==NULL) return;

    if (root->x == parent) {// 삽입하고자 하는 노드 도달시
        if (left_child!=0 && !root->left_child) {
            root->left_child = create_node(left_child);
        }
        if (right_child!=0 &&!root->right_child) {
            root->right_child = create_node(right_child);
        }
        return;
    }
    else{ // root-x != parent
        if (root->left_child != NULL) {
            insert_node(root->left_child, parent, left_child, right_child);
        }
        if (root->right_child != NULL) {
            insert_node(root->right_child, parent, left_child, right_child);
        }
    }
}
Node *build_tree(int n) {
    //최초 루트 노드는 먼저 입력받음
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    Node *root = create_node(x);
    if (!root) {
        return 0;
    }
    insert_node(root,x,y,z);

    for (int i=1; i<n; i++) {
        scanf("%d %d %d", &x, &y, &z);
        insert_node(root,x,y,z);
    }
    return root;
}

void search_tree(Node *root, char *tree_search_input) {
    Node *current_node = root;
    unsigned int tree_search_input_len = strlen(tree_search_input) + 1;
    for (int i=0; i<tree_search_input_len; i++) {
        if (current_node == NULL) break;

        printf(" %d",current_node->x);

        if (tree_search_input[i]=='L') {
            current_node = current_node->left_child;
        }
        else if (tree_search_input[i]=='R') {
            current_node = current_node->right_child;
        }
    }
    printf("\n");
}

/* 후위 순회로 모든 노드 해제 */
static void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left_child);
    free_tree(root->right_child);
    free(root);
}

int main() {
    int n;
    scanf("%d", &n);
    Node *root = build_tree(n);

    int s; // 탐색횟수
    scanf("%d", &s);
    for (int i=0; i<s; i++) {
        char tree_search_input[101];
        scanf("%s",tree_search_input);
        search_tree(root,tree_search_input);
    }
    free_tree(root);
    return 0;
}
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
	int key;
	struct Node *parent;
	struct Node *lChild;
	struct Node *rChild;
}Node;

Node* getNode() {// 노드 동적할당
	Node* new = malloc(sizeof(Node));
	if (new == NULL) {
		return NULL;
	}
	new->parent = NULL;
	new->lChild = NULL;
	new->rChild = NULL;
	return new;
}
int isRoot(Node* w) {// root인지 확인후 맞으면 1 반환 아니면 0 반환
	if (w->parent == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
int isExternal(Node* w) {// 외부노드인지 확인 참이면 1, 거짓은 0 반환
	if (w == NULL) {return 0;}
	if ((w->lChild == NULL) && (w->rChild == NULL)) {
		return 1;
	}
	else{//w.lChild != NULL or w.rChild != NULL
		return 0;
	}
}
int isInternal(Node* w) {// 내부노드인지 확인 참은 1, 거짓은 0 반환 (isExternal의 반대로 반환 즉 둘중 하나만 사용해도 상관은 없음
	if ((w->lChild != NULL) || (w->rChild != NULL)) {
		return 1;
	}
	else {
		return 0;
	}
}

Node* sibling(Node* w) {// 형제 node 반환
	if (isRoot(w)) {
		return NULL; // invalidNodeException
	}
	if (w->parent->lChild == w) {
		return w->parent->rChild;
	}
	else {
		return w->parent->lChild;
	}
}

Node* inOrderSucc(Node* w) {// 중위순회 후계자 반환
	w = w->rChild;
	if (isExternal(w)) {
		return NULL; // invalidNodeException
	}

	while (isInternal(w->lChild)) {
		w = w->lChild;
	}
	return w;
}

Node* reduceExternal(Node* z, Node** rootPtr) {
	if (z == NULL) return NULL;  // z가 NULL이면 바로 리턴

	Node* w = z->parent;
	if (w == NULL) return NULL;  // parent 없는 경우 방어

	Node* zs = sibling(z);
	if (zs == NULL) {  // 형제가 없을 경우
		free(z);
		free(w);
		return NULL;
	}

	if (isRoot(w)) {
		*rootPtr = zs;
		zs->parent = NULL;
	} else {
		Node* g = w->parent;
		zs->parent = g;
		if (w == g->lChild)
			g->lChild = zs;
		else
			g->rChild = zs;
	}

	free(z);
	free(w);
	return zs;
}

Node* treeSearch(Node *v, int key) {// key 저장한 내부 노드 반환
	if (isExternal(v)) {
		return v;
	}

	if (v->key == key) {
		return v;
	}
	if (key < v->key) {
		return treeSearch(v->lChild, key);
	}
	else {
		return treeSearch(v->rChild, key);
	}
}

void insertItem(int key, Node* v) {// 삽입
	Node* w = treeSearch(v, key);
	if(isInternal(w)){
		return;
	}
	Node* lChildNode = getNode();
	Node* rChildNode = getNode();
	w->key = key;
	lChildNode->parent = w;
	rChildNode->parent = w;
	w->lChild = lChildNode;
	w->rChild = rChildNode;
}

void printTree(Node* v) {//트리 전위순회 인쇄
	if (isExternal(v)) {
		return;
	}
	else {
		printf(" %d", v->key);
		printTree(v->lChild);
		printTree(v->rChild);
	}
}


int removeElement(Node** rootPtr, int key) {
	Node* w = treeSearch(*rootPtr, key);
	if (isExternal(w)) return -1;

	int e = w->key;
	Node* z;
	if (isExternal(w->lChild)) z = w->lChild;
	else if (isExternal(w->rChild)) z = w->rChild;
	else {
		Node* y = inOrderSucc(w);
		w->key = y->key;
		z = y->lChild;
	}

	reduceExternal(z, rootPtr);  // rootPtr 사용
	return e;
}

void freeAll(Node* w) {// 트리 동적할당 해제

	if (w == NULL) return;
	if (isExternal(w)) {free(w); return;}
	freeAll(w->lChild);
	freeAll(w->rChild);
	free(w);
}
int main() {
	char command;// 명령어 입력
	int key;
	Node* w = getNode(); // root node 할당
	while (1) {
		scanf("%c", &command);

		if (command == 'q') {
			break;
		}
		else if (command == 'p') {// 전위순회 인쇄
			getchar();
			printTree(w);
			printf("\n");
		}
		else if (command=='i') {// key 삽입
			scanf("%d", &key);
			getchar();
			insertItem(key, w);
		}
		else if (command == 's') {// key 조회
			scanf("%d", &key);
			getchar();
			Node *t = treeSearch(w, key);
			if (isExternal(t)) {
				printf("X\n");
			}
			else {
				printf("%d\n", t->key);
			}
		}
		else if (command == 'd') {// key 삭제
			scanf("%d", &key);
			getchar();
			int result = removeElement(&w, key);// 제거함수 결과
			if (result == -1) {// 없으면 반환하는 -1 확인
				printf("X\n");
			}
			else {
				printf("%d\n", result);
			}

		}
	}

	freeAll(w);
	return 0;
}

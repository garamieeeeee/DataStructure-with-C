//complete binary tree의 일차원 배열 표현방식으로 표현된 이진트리를, explicit with link 방식으로 동적할당을 사용하여 구현하는 문제
//레벨 순회를 사용하여 트리를 구성함
//레벨 순회를 위해 추가한 BinaryTreeTraversal_level.h 헤더파일에 들어있는 원형큐를 이용함.
//즉 큐를 사용하여 레벨순서로 트리를 구성하였다(재귀적인 방식x)

#include "BinaryTreeTraversal_level.h"

typedef struct {
	BinTreeNode* rootNode;
}BinTree;

ElementType array[] = { 0, '+', '*', 'E', '*', 'D',0,0,'/', 'C', 0, 0, 0, 0, 0, 0, 'A', 'B' };

void Error(char* message);
BinTreeNode* CreateNode(ElementType data);
BinTree* Create_BinTree();
void DeleteNode(BinTreeNode* node);
void Delete_BinTree(BinTree** tree);
void PreOrder(BinTreeNode* root);
void InOrder(BinTreeNode* root);
void PostOrder(BinTreeNode* root);
BinTree* BuildTree();

int main() {

	//array에 저장한 노드 정보를 읽고 트리 생성
	BinTree* tree = BuildTree();

	//순회
	printf("inorder traversal: "); InOrder(tree->rootNode); printf("\n");
	printf("preorder traversal: "); PreOrder(tree->rootNode); printf("\n");
	printf("postorder traversal: "); PostOrder(tree->rootNode); printf("\n");
	printf("level order traversal: "); LevelOrder(tree->rootNode); printf("\n");

	//트리삭제
	Delete_BinTree(&tree);

	return 0;
}

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

BinTreeNode* CreateNode(ElementType data) {
	if (data == 0) return NULL; //읽은 data가 0이면,즉 비어있는 노드이면 노드를 생성하지 않고 NULL 포인터 반환
	BinTreeNode* newNode = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	if (!newNode) Error("memory allocation failed.");
	newNode->data = data;
	newNode->leftChild = newNode->rightChild = NULL;
	return newNode;
}

BinTree* Create_BinTree() {
	BinTree* tree = (BinTree*)malloc(sizeof(BinTree));
	if (!tree) Error("memory allocation failed.");
	tree->rootNode = NULL;
	return tree;
}

void DeleteNode(BinTreeNode* node) { //node의 서브트리를 포함하여 모두 삭제
	if (node == NULL) return;
	//L->R->V순으로 메모리 해제
	DeleteNode(node->leftChild);
	DeleteNode(node->rightChild);
	free(node);
}

void Delete_BinTree(BinTree** tree) { //tree의 모든 노드 삭제 후 트리의 메모리도 해제
	if (*tree == NULL) return;
	//루트노드부터 모든 노드 삭제
	DeleteNode((*tree)->rootNode);
	free(*tree);
	*tree = NULL;
}

void PreOrder(BinTreeNode* root) {
	if (root) {
		if (root->data != 0) printf("%c ", root->data);
		PreOrder(root->leftChild);
		PreOrder(root->rightChild);
	}
}

void InOrder(BinTreeNode* root) {
	if (root) {
		InOrder(root->leftChild);
		if (root->data != 0) printf("%c ", root->data);
		InOrder(root->rightChild);
	}
}

void PostOrder(BinTreeNode* root) {
	if (root) {
		PostOrder(root->leftChild);
		PostOrder(root->rightChild);
		if (root->data != 0) printf("%c ", root->data);
	}
}

BinTree* BuildTree() {
	int n = sizeof(array) / sizeof(ElementType);//n:배열 array의 크기
	int last = n - 1; //last: 마지막 노드의 노드번호

	//예외 처리(트리에 노드가 하나도 없는 경우)
	if (array[1] == 0) return NULL;

	//트리 생성
	BinTree* tree = Create_BinTree();

	//array[]의 1번 데이터로 루트 노드 생성
	tree->rootNode = CreateNode(array[1]);

	//노드를 담을 큐 생성(BinTreeNode* 타입의 원형 큐)
	QueueType* q = CreateQueue();

	//먼저 루트노드를 삽입해놓는다.
	Enqueue(q, tree->rootNode);

	int i = 2; //index 1번(루트노드)는 이미 삽입했으니 2번부터 시작
	while (!IsEmptyQueue(q) && i <= last) { //큐가 비거나, 아니면 i가 last를 넘어가면 while문 종료
		//큐에서 노드를 하나 꺼내서 parent로 설정
		BinTreeNode* parent = Dequeue(q);

		//꺼낸 노드가 NULL이면, 즉 비어있는 노드라면 자식 노드 역시 NULL 일테니, 스텍에 NULL을 두번 삽입한다.
		if (parent == NULL) {
			Enqueue(q, NULL); i++;
			Enqueue(q, NULL); i++;
		}
		else {
			parent->leftChild = CreateNode(array[i]);
			Enqueue(q, parent->leftChild);
			i++;

			parent->rightChild = CreateNode(array[i]);
			Enqueue(q, parent->rightChild);
			i++;
		}
	}

	//큐 삭제
	FreeQueue(&q);

	return tree;
}

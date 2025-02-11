#include "BinarySearchTree_ver2.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

BSTNode* CreateNode(ElementType key) {
	BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
	if (!newNode) Error("memeory allocation failed.");
	newNode->key = key;
	newNode->leftChild = newNode->rightChild = NULL;

	return newNode;
}

BST* CreateBST() {
	BST* tree = (BST*)malloc(sizeof(BST));
	if (!tree) Error("memeory allocation failed.");
	tree->rootNode = NULL;

	return tree;
}

BSTNode* SearchNode(BSTNode* root, ElementType key) {
	//해당 키를 가진 노드가 트리에 있는지 탐색
	//탐색에 성공하면 해당 노드를 반환
	//탐색에 실패하면 NULL값 반환

	//트리에 노드가 하나도 없는 경우
	//또는 트리의 끝까지 내려오면서 탐색하다가 NULL값에 도달할때까지 동일한 키의 노드를 못찾은 경우
	//탐색에 실패했으므로 NULL값 반환 후 종료(종료 조건1)
	if (root == NULL) return NULL;

	if (key == root->key) //탐색 성공: 해당 노드를 반환하고 종료(종료 조건2)
		return root;
	else if (key < root->key) //왼쪽 서브트리에서부터 다시 탐색 시작
		return SearchNode(root->leftChild, key);
	else //key > root->key: 오른쪽 서브트리에서부터 다시 탐색 시작
		return SearchNode(root->rightChild, key);
}

BSTNode* InsertNode(BSTNode* root, ElementType key) {
	//해당 키를 가진 노드가 트리에 있는지 탐색
	//탐색에 성공하면: 노드를 삽입하지 않고, 루트노드 포인터를 반환하고 함수를 차례로 종료
	//탐색에 실패하면: 노드를 삽입하고 변경된 루트 노드 포인터를 반환하고 차례로 종료

	//트리에 노드가 하나도 없는 경우: 새로운 노드를 생성하여 반환한다.(새로운 노드가 곧 루트노드이기 때문)
	//또는 트리의 끝까지 탐색하였는데 중복된 키를 탐색하지 못한 경우: 새로운 노드를 생성하여 반환한다.
	//종료조건 1
	if (root == NULL)
		return CreateNode(key);

	//순환적으로 트리를 내려가며 탐색. 한번 순환호출 될때마다 위에서 if(root==NULL)인지를 확인한다
	//만약 단말노드를 거쳐 root가 NULL이 될때까지 탐색에 실패한다면, 새로운 노드를 생성하여 반환한다.
	//노드가 삽입되었다면 새로운 노드를 가리키는 포인터를 반환 할 것이므로, 부모노드의 링크로 받아줘야한다.

	//만약 탐색 도중에 key == root->key가 된다면, 즉 탐색에 성공한다면 :
	//위의 if(root == NULL) 문에 걸리지 않기 때문에 새로운 노드를 삽입하지 않고
	//변경되지 않은 루트노드 포인터를 반환하며 순환호출 했던 함수들을 차례로 종료한다.

	if (key < root->key) //왼쪽 서브트리부터 다시 탐색 시작
		root->leftChild = InsertNode(root->leftChild, key);
	else if (key > root->key) //오른쪽 서브트리부터 다시 탐색 시작
		root->rightChild = InsertNode(root->rightChild, key);

	return root; //종료 조건2
}

BSTNode* DeleteNode(BSTNode* root, ElementType key) {
	//해당 키를 가진 노드가 트리에 있는지 탐색
	//탐색에 실패하면: 삭제할 노드가 없다는 것이므로, 삭제하지않고 root 포인터를 그대로 반환하고 종료
	//탐색에 성공하면: 노드를 삭제하고, 삭제한 노드의 자식 노드를 가리키는 포인터를 반환하고 종료(삭제한 노드의 자식노드가 없다면 NULL값 반환)
	//삭제한 노드의 부모노드의 링크로 반환 값을 받는다. 즉 삭제한 노드의 부모노드와 삭제한 노드의 자식노드를 연결해준다.

	//트리에 노드가 하나도 없다면: 삭제하지 않고 그냥 루트 포인터를 그대로 반환
	//종료 조건1
	if (root == NULL) return root;

	//탐색
	if (key < root->key) //왼쪽 서브트리부터 다시 탐색 시작
		root->leftChild = DeleteNode(root->leftChild, key);
	else if (key > root->key) //오른쪽 서브트리부터 다시 탐색 시작
		root->rightChild = DeleteNode(root->rightChild, key);
	else { //키가 같아지면, 즉 탐색에 성공하면 이 노드를 삭제하면 됨 (root: 삭제하려는 노드를 가리키는 상태)
		if (root->leftChild == NULL && root->rightChild == NULL) { //삭제하려는 노드가 단말노드인 경우
			//해당 노드를 삭제하고 NULL값을 반환
			free(root);
			return NULL; //종료조건2
		}
		else if (root->leftChild == NULL || root->rightChild == NULL) { //삭제하려는 노드가 한쪽 서브트리만 갖는 경우
			//삭제하려는 노드의 자식노드를 저장해놓고
			//노드를 삭제
			//자식 노드를 가리키는 포인터를 반환
			BSTNode* child = (root->leftChild != NULL) ? root->leftChild : root->rightChild;
			free(root);
			return child; //종료조건3
		}
		else { //삭제하려는 노드가 양쪽 서브트리를 모두 갖는 경우
			//여기서는 삭제하려는 노드의 오른쪽 서브트리에서 후계자를 찾는 것으로한다.
			BSTNode* succ = root->rightChild; //삭제하려는 노드(root)의 오른쪽 자식부터 시작
			while (succ->leftChild != NULL) { //오른쪽 서브트리의 맨 왼쪽노드까지 내려간다
				succ = succ->leftChild;
			}
			//succ은 삭제하려는 노드(root)의 오른쪽 서브트리에서의 최솟값 노드를 가리킴
			//즉 succ은 후계자 노드를 가리킴

			root->key = succ->key; //삭제하려는 노드의 키 값에 후계자 노드의 키 값을 복사한다.

			//실제로 삭제되는 것은 후계자 노드
			//root의 오른쪽 서브트리에서 후계자 노드를 찾아 삭제
			//후계자 노드는 왼쪽 자식은 확실히 없다. 오른쪽 자식이 있다면 오른쪽 자식을 가리키는 포인터를 반환하고, 없다면 NULL값 반환
			//후계자 노드의 부모노드의 링크와, 후계자의 오른쪽 자식 링크(또는 NULL값)이 연결됨
			root->rightChild = DeleteNode(root->rightChild, succ->key);
		}
	}
	return root; //종료조건4
}

//순회
void PreOrder(BSTNode* root) {
	if (root) {
		printf("%d ", root->key);
		PreOrder(root->leftChild);
		PreOrder(root->rightChild);
	}
}

void InOrder(BSTNode* root) {
	if (root) {
		InOrder(root->leftChild);
		printf("%d ", root->key);
		InOrder(root->rightChild);
	}
}

void PostOrder(BSTNode* root) {
	if (root) {
		PostOrder(root->leftChild);
		PostOrder(root->rightChild);
		printf("%d ", root->key);
	}
}

void FreeBST(BSTNode* root) {//트리의 모든 노드를 메모리 해제하는 함수
	if (root) {//L->R->V순으로 순회하며 free
		FreeBST(root->leftChild);
		FreeBST(root->rightChild);
		free(root);
	}
}

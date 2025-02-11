//반복문을 사용하여 이진탐색트리 구현

#include "BinarySearchTree_ver1.h"

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

//탐색 함수
BSTNode* SearchNode(BSTNode* root, ElementType key) {
	//트리에 해당 키를 가진 노드가 있는지 탐색
	//탐색에 성공하면 찾는 노드를 반환하고 종료
	//탐색에 실패하면 실패했다는 메시지를 출력하고 NULL값 반환 후 종료

	//p: 루트노드부터 트리를 끝까지 순회할 포인터
	BSTNode* p = root;
	while (p != NULL) { //끝까지 순회
		if (key == p->key) //탐색 성공: p를 반환하고 종료
			return p;
		else if (key < p->key) //왼쪽 서브트리에서 다시 탐색 시작
			p = p->leftChild;
		else //key > p->key: 오른쪽 서브트리에서 다시 탐색 시작
			p = p->rightChild;
	}

	//while문이 끝날때까지 함수가 종료되지 않았다면, 탐색에 실패한 것
	//NULL 값을 반환하고 종료한다.
	printf("찾으시는 키 [%d]가 트리에 없습니다.\n", key);
	return NULL;
}

//삽입 함수
int InsertNode(BSTNode** root, ElementType key) {
	//트리에 해당 키를 가진 노드가 있는지 탐색
	//탐색에 성공하면: 삽입할 수 없으므로 실패 메시지 출력하고 FALSE 반환 후 종료
	//탐색에 실패하면: 실패한 위치에서 삽입하고 TRUE 반환하고 종료
	//삽입 성공 여부를 반환

	//p: 루트노드부터 트리를 끝까지 순회할 포인터
	//parent: p의 부모노드를 가리키는 포인터
	//트리에 노드가 하나도 없는 상태에서 삽입하는 경우에는 루트를 갱신해줘야 함
	//따라서 트리에 노드가 하나도 없는 경우를 구분하기 위해서, parent의 초기값은 NULL로 설정
	BSTNode* p = *root;
	BSTNode* parent = NULL;

	////해당 키가 트리에 있는지 우선 탐색
	while (p != NULL) { //끝까지 순회
		parent = p; //p를 이동시키기 전에 parent에 저장해둠
		if (key == p->key) { //탐색 성공: 삽입 실패 메시지 출력하고 FALSE 반환 후 종료
			printf("키 [%d]가 이미 트리에 있어 삽입할 수 없습니다.\n", key);
			return FALSE;
		}
		else if (key < p->key) //왼쪽 서브트리에서 다시 탐색 시작
			p = p->leftChild;
		else //key > p->key: 오른쪽 서브트리에서 다시 탐색 시작
			p = p->rightChild;
	}

	////탐색 종료
	//while문이 끝날때까지 함수가 종료되지 않았다면, 탐색에 실패한 것
	//새로운 노드를 생성하여 삽입한다.
	BSTNode* newNode = CreateNode(key);
	if (parent == NULL) //비어있는 트리에 새로운 노드를 삽입하는 경우(이때는 p도 parent도 둘다 NULL)
		*root = newNode; //루트를 새로운 노드로 변경해준다
	else { //parent가 존재하는 경우
		//parent는 단말노드를 가리킴
		//p는 parent의 링크인 NULL값을 가짐
		//parent의 자식노드로 newNode를 삽입한다
		if (key < parent->key) //삽입하려는 키가 parent의 키보다 작다면: 왼쪽 자식으로 삽입해야 함
			parent->leftChild = newNode;
		else //삽입하려는 키가 parent의 키보다 크다면: 오른쪽 자식으로 삽입해야 함
			parent->rightChild = newNode;
	}

	//삽입에 성공하였다는 메시지 출력 후, TRUE를 반환하고 종료
	printf("키 [%d]를 삽입\n", key);
	return TRUE;
}

//삭제 함수
int DeleteNode(BSTNode** root, ElementType key) {
	//트리에 해당 키를 가진 노드가 있는지 탐색
	//탐색에 성공하면: 해당 노드를 삭제하고 TRUE 반환 후 종료
	//탐색에 실패하면: 삭제할 수 없으므로 실패 메시지 출력하고 FALSE 반환 후 종료
	//삭제 성공 여부를 반환

	//p: 루트노드부터 트리를 끝까지 순회할 포인터
	//parent: p의 부모노드를 가리키는 포인터
	//트리에 노드가 하나도 없는 경우를 구분하기 위해서, parent의 초기값은 NULL로 설정
	BSTNode* p = *root;
	BSTNode* parent = NULL;

	////해당 키가 트리에 있는지 우선 탐색
	while ((p != NULL) && (key != p->key)) { //끝까지 탐색 && 삭제할 노드를 발견하면 while문 종료
		parent = p; //p를 이동시키기 전에 parent에 저장해둠
		if (key < p->key) //왼쪽 서브트리에서 다시 탐색 시작
			p = p->leftChild;
		else //key > p->key: 오른쪽 서브트리에서 다시 탐색 시작
			p = p->rightChild;
	}

	//while문이 끝나면
	//1) p==NULL이거나 2) key == p->key

	////1) p==NULL인 경우: 트리에 해당 노드가 없다는 뜻
	if (p == NULL) { //삭제 실패 메시지 출력하고 FALSE 반환 후 종료
		printf("키 [%d]가 트리에 없어 삭제할 수 없습니다.\n", key);
		return FALSE;
	}

	/*
	* 삭제하려는 노드가 단말노드인 경우: 해당 노드만 삭제하고 부모 노드의 링크를 NULL로 바꿔주면 끝
	* 삭제하려는 노드가 한쪽 서브트리만 갖는 경우: 해당 노드를 삭제하고, 삭제한 자리에 삭제한 노드의 왼쪽 또는 오른쪽 자식을 연결해주면 됨
	* 삭제하려는 노드가 양쪽 서브트리를 모두 갖는 경우: 삭제할 노드의 왼쪽 서브트리 / 오른쪽 서브트리 둘중에 한곳을 골라 그 중에서 후계자(삭제한 자리에 들어갈)를 골라야함
	* 왼쪽 서브트리에서 후계자를 고른다면 - 왼쪽 서브트리에서 가장 큰 값을 선택해야함
	* 오른쪽 서브트리에서 후계자를 고른다면 - 오른쪽 서브트리에서 가장 작은 값을 선택해야 함
	* 여기서는 오른쪽 서브트리에서 후계자를 고르는 것으로 함
	*/

	////2) key == p-> key인 경우: p는 삭제하려는 노드를 가리키고, parent는 p의 부모노드를 가리킴
	if (p->leftChild == NULL && p->rightChild == NULL) {//삭제하려는 노드의 차수가 0인 경우(단말노드)
		if (parent == NULL) //삭제하려는 노드가 루트노드인 경우: 루트를 NULL로 만들어줘야함
			*root = NULL;
		else { //삭제하려는 노드가 루트노드가 아닌 경우: parent의 링크를 수정해줘야 함
			if (parent->leftChild == p) //삭제하려는 노드가 parent의 왼쪽 자식인 경우: parent의 왼쪽 링크를 NULL로 변경
				parent->leftChild = NULL;
			else //삭제하려는 노드가 parent의 오른쪽 자식인 경우: parent의 오른쪽 링크를 NULL로 변경
				parent->rightChild = NULL;
		}
	}
	else if (p->leftChild == NULL || p->rightChild == NULL) {//삭제하려는 노드의 차수가 1인 경우(왼쪽 또는 오른쪽 서브트리만 가짐)
		//p의 왼쪽 자식 또는 오른쪽 자식을 parent의 링크에 연결
		BSTNode* child = (p->leftChild != NULL) ? p->leftChild : p->rightChild;

		if (parent == NULL) //삭제하려는 노드가 루트노드인 경우: root를 갱신해줘야 함
			*root = child; //삭제한 노드의 왼쪽 또는 오른쪽 자식이 루트노드가 됨
		else {//삭제하려는 노드가 루트노드가 아닌 경우: parent의 링크를 수정해줘야 함
			if (parent->leftChild == p) //삭제할 노드가 parent의 왼쪽 자식인 경우: parent의 왼쪽 링크에 child 연결
				parent->leftChild = child;
			else //삭제할 노드가 parent의 오른쪽 자식인 경우: parent의 오른쪽 링크에 child 연결
				parent->rightChild = child;
		}
	}
	else {//삭제하려는 노드의 차수가 2인 경우(왼쪽, 오른쪽 서브트리를 둘다 가짐)
		//이 경우엔, 삭제하려는 노드가 아닌, 후계자가 삭제된다.
		//후계자의 키값을 삭제하려는 노드에 복사하고, 후계자 노드를 삭제하는 방식

		//오른쪽 서브트리에서 후계자 노드 찾기
		BSTNode* succ_parent = p; //p: 삭제하려는 노드!!
		BSTNode* succ = p->rightChild; //succ: 삭제할 노드의 자리에 들어갈 후계자 노드

		while (succ->leftChild != NULL) { //오른쪽 서브트리에서 가장 작은 값을 찾아 내려감
			succ_parent = succ; //succ 이동하기 전에 succ_parent에 저장
			succ = succ->leftChild;
		}

		//while문이 끝나면, succ은 후계자 노드를, succ_parent는 후계자 노드의 부모노드를 가리킴
		//p: 삭제하려는 노드
		p->key = succ->key; //후계자 노드의 키값을 복사해 p의 키로 저장

		//후계자 노드를 삭제할 것이므로, succ_parent와 succ의 오른쪽 자식 노드를 연결해준다.
		//succ은 오른쪽 서브트리에서 가장 작은 값이므로, 왼쪽 자식은 확실히 없다
		//오른쪽 자식은 있거나 없을 수도 있음(NULL)
		if (succ_parent->leftChild == succ) //succ이 succ_parent의 왼쪽 자식이라면
			succ_parent->leftChild = succ->rightChild; //succ_parent의 왼쪽 링크에 succ의 자식 연결
		else //succ이 succ_parent의 오른쪽 자식이라면
			succ_parent->rightChild = succ->rightChild; //succ_parent의 오른쪽 링크에 succ의 자식 연결

		//함수의 끝에서 일괄적으로 p를 메모리 해제 할 것이므로
		//p가 succ을 가리키도록 바꿔준다.(여기서 실질적으로 삭제되는 것은 후계자 노드임)
		p = succ;
	}

	//링크 연결 작업을 끝냈으니 노드 삭제하고 TRUE 반환 후 종료
	printf("키 [%d]를 삭제합니다.\n", key);
	free(p);
	return TRUE;
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
	if (root) { //L->R->V순으로 순회하며 free
		FreeBST(root->leftChild);
		FreeBST(root->rightChild);
		free(root);
	}
}

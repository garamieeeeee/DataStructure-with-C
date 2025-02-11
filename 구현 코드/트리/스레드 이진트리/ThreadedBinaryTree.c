#include "ThreadedBinaryTree.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

thrBTNode* CreateNode(ElementType data) {
	thrBTNode* newNode = (thrBTNode*)malloc(sizeof(thrBTNode));
	if (!newNode) Error("memory allocation failed.");
	newNode->data = data;
	newNode->leftChild = newNode->rightChild = NULL;
	newNode->leftThread = newNode->rightThread = FALSE;

	return newNode;
}

thrBT* Create_thrBT() {
	thrBT* tree = (thrBT*)malloc(sizeof(thrBT));
	if (!tree) Error("memory allocation failed.");

	//헤드 노드 생성
	tree->headNode = (thrBTNode*)malloc(sizeof(thrBTNode));
	if (!tree->headNode) Error("memory allocation failed.");

	//헤드노드 초기화
	(tree->headNode)->leftChild = tree->headNode;
	(tree->headNode)->leftThread = TRUE; //루트노드가 삽입되면 FALSE로 바뀜. 트리가 비어있을때는 TRUE
	(tree->headNode)->rightChild = tree->headNode;
	(tree->headNode)->rightThread = FALSE;

	return tree;
}

thrBTNode* Find_InOrder_Predecessor(thrBTNode* node) { //node의 중위선행자 노드를 찾아서 반환해준다.
	thrBTNode* temp = node->leftChild; //node의 중위선행자 노드는 node의 왼쪽 서브트리에 있을 것이므로, 왼쪽 자식부터 탐색
	if (!node->leftThread) { //만약 node->leftThread == TRUE라면, node의 leftChild가 곧 중위선행자 노드이므로, if문을 건너뛰고 바로 temp 반환 후 종료
		while (!temp->rightThread) { //temp->rightThread == TRUE가 될때까지, 즉 맨 오른쪽 노드까지 내려감
			temp = temp->rightChild;
		}
	}
	//이제 temp는 node의 중위선행자 노드를 가리킴
	return temp;
}

thrBTNode* Find_InOrder_Successor(thrBTNode* node) { //node의 중위후속자 노드를 찾아서 반환해준다.
	thrBTNode* temp = node->rightChild; //node의 중위후속자 노드는 node의 오른쪽 서브트리에 있을 것이므로, 오른쪽 자식부터 탐색
	if (!node->rightThread) { //만약 node->rightThread == TRUE라면, node의 rightChild가 곧 중위후속자 노드이므로, if문을 건너뛰고 바로 temp 반환 후 종료
		while (!temp->leftThread) { //temp->leftThread == TRUE가 될때까지, 즉 맨 왼쪽 노드까지 내려감
			temp = temp->leftChild;
		}
	}
	//이제 temp는 node의 중위후속자 노드를 가리킴
	return temp;
}

void Insert_LeftChild(thrBTNode* node, ElementType data) { //node의 왼쪽 자식 삽입
	thrBTNode* newNode = CreateNode(data);

	//node의 왼쪽 자식을 newNode의 왼쪽 자식으로 달아줌
	//만약 node의 왼쪽 자식이 원래 있었다면: newNode의 leftChild에는 원래의 왼쪽 자식이 들어가고
	//만약 node의 왼쪽 자식이 원래 없었다면: newNode의 leftChild에는 node의 원래의 중위선행자 노드가 들어갈 것
	newNode->leftChild = node->leftChild;

	//만약 node의 왼쪽 자식이 원래 있었다면: newNode의 leftThread는 FALSE -> FALSE
	//만약 node의 왼쪽 자식이 원래 없었다면: newNode의 leftThread는 FALSE -> TRUE
	newNode->leftThread = node->leftThread;

	//newNode가 node의 왼쪽 자식으로 들어갔으므로, 이제 node는 newNode의 중위후속자 노드임
	newNode->rightChild = node;
	newNode->rightThread = TRUE;
	node->leftChild = newNode;
	node->leftThread = FALSE;

	//만약 newNode의 leftThread == TRUE라면: newNode는 왼쪽 자식이 없고, 중위선행자 노드를 가리키는 상태
	//만약 newNode의 leftThread == FALSE라면: newNode는 왼쪽 자식 및 서브트리가 있다.
	//이제 왼쪽 자식의 서브트리에서 맨 오른쪽 노드의 중위후속자 노드는 newNode이므로, rightChild를 변경해줘야함
	if (!newNode->leftThread) { //newNode의 중위선행자 노드, 즉 왼쪽 서브트리에서 맨 오른쪽 노드를 찾는다
		thrBTNode* temp = Find_InOrder_Predecessor(newNode);
		temp->rightChild = newNode;
	}
}

void Insert_RightChild(thrBTNode* node, ElementType data) { //node의 오른쪽 자식 삽입
	thrBTNode* newNode = CreateNode(data);

	//node의 오른쪽 자식을 newNode의 오른쪽 자식으로 달아줌
	//만약 node의 오른쪽 자식이 원래 있었다면: newNode의 rightChild에는 원래의 오른쪽 자식이 들어가고
	//만약 node의 오른쪽 자식이 원래 없었다면: newNode의 rightChild에는 node의 원래의 중위후속자 노드가 들어갈 것
	newNode->rightChild = node->rightChild;

	//만약 node의 오른쪽 자식이 원래 있었다면: newNode의 rightThread는 FALSE -> FALSE
	//만약 node의 오른쪽 자식이 원래 없었다면: newNode의 rightThread는 FALSE -> TRUE
	newNode->rightThread = node->rightThread;

	//newNode가 node의 오른쪽 자식으로 들어갔으므로, 이제 node는 newNode의 중위선행자 노드임
	newNode->leftChild = node;
	newNode->leftThread = TRUE;
	node->rightChild = newNode;
	node->rightThread = FALSE;

	//만약 newNode의 rightThread == TRUE라면: newNode는 오른쪽 자식이 없고, 중위후속자 노드를 가리키는 상태
	//만약 newNode의 rightThread == FALSE라면: newNode는 오른쪽 자식 및 서브트리가 있다.
	//이제 오른쪽 자식의 서브트리에서 맨 왼쪽 노드의 중위선행자 노드는 newNode이므로, leftChild를 변경해줘야함
	if (!newNode->rightThread) { //newNode의 중위후속자 노드, 즉 오른쪽 서브트리에서 맨 왼쪽 노드를 찾는다
		thrBTNode* temp = Find_InOrder_Successor(newNode);
		temp->leftChild = newNode;
	}
}

thrBTNode* Get_LeftChild(thrBTNode* node) {
	return node->leftChild;
}

thrBTNode* Get_rightChild(thrBTNode* node) {
	return node->rightChild;
}

void thrBT_InOrder_Traversal(thrBT* tree) { //트리의 맨 왼쪽 노드부터 시작해서 중위순회 순서로 차례로 방문하며 출력
	thrBTNode* temp = (tree->headNode)->leftChild; //루트노드부터 시작
	while (!temp->leftThread) { //맨 왼쪽 노드까지 간다
		temp = temp->leftChild;
	}

	for (;;) {
		printf("%c ", temp->data); //현재 노드를 방문하고
		temp = Find_InOrder_Successor(temp); //현재 노드의 중위후속자 노드로 이동
		if (temp == tree->headNode) break; //중위 순회에서의 맨 마지막 노드를 거쳐 headNode로 돌아오게 되면, 방문이 다 끝난 것
	}
}

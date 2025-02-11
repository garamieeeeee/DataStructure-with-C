#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE_COUNT 20 //노드 개수: 20개 이하

typedef char ElementType;

void Error(char* message) { //에러 메시지 출력 후 종료
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

int ReadFile(char* fileName, ElementType tree[]) { //input파일을 읽어 (트리) 배열에 저장한다. 트리의 마지막 노드의 노드번호를 반환
	FILE* file = fopen(fileName, "r");
	if (!file) Error("file open failed.");

	int validNodeCount; //유효한 노드의 수(null이 아닌)
	fscanf(file, " %d", &validNodeCount);
	if (validNodeCount > MAX_NODE_COUNT) Error("The maximum number of nodes is 20.");

	int i = 1;
	int count = 0;
	ElementType data;
	while (fscanf(file, " %c", &data) != EOF) {
		if (data != 'N') tree[i] = data;
		i++;
		count++;
	}

	fclose(file);

	return count;
}

void PreOrder(ElementType tree[], int index, int n) {
	if (index <= n) {
		if (tree[index] != 0) printf("%c ", tree[index]);
		PreOrder(tree, index * 2, n);
		PreOrder(tree, index * 2 + 1, n);
	}
}

void InOrder(ElementType tree[], int index, int n) {
	if (index <= n) {
		InOrder(tree, index * 2, n);
		if (tree[index] != 0) printf("%c ", tree[index]);
		InOrder(tree, index * 2 + 1, n);
	}
}

void PostOrder(ElementType tree[], int index, int n) {
	if (index <= n) {
		PostOrder(tree, index * 2, n);
		PostOrder(tree, index * 2 + 1, n);
		if (tree[index] != 0) printf("%c ", tree[index]);
	}
}

int main(int argc, char* argv[]) {
	//(배열) 트리 생성. 0(null)로 초기화(노드는 1~20번에 들어감)
	ElementType tree[MAX_NODE_COUNT + 1];
	for (int i = 0; i <= MAX_NODE_COUNT; i++) {
		tree[i] = 0;
	}

	//input 파일을 읽어 트리 구성. n: 트리의 마지막 노드의 노드 번호
	int n = ReadFile(argv[1], tree);

	//배열에 노드가 제대로 들어갔는지 확인
	/*for (int i = 1; i <= MAX_NODE_COUNT; i++) {
		printf("[%d]: %c ", i, tree[i]);
	}
	printf("\n");*/

	printf("inorder traversal: "); InOrder(tree, 1, n); printf("\n");
	printf("preorder traversal: "); PreOrder(tree, 1, n); printf("\n");
	printf("postorder traversal: "); PostOrder(tree, 1, n); printf("\n");

	return 0;
}

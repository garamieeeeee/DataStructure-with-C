#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1

typedef struct Node {
	int data;
	struct Node* link;
}Node;

int compare(const void* a, const void* b) {
	return(*(int*)a - *(int*)b);
}

int main(int argc, char* argv[]) {

	//인자 검사
	if (argc < 3) { //argv[0]:파일 경로, argv[1]: input.txt, argv[2]: output.txt
		fprintf(stderr, "[Usage] %s <input.txt> <output.txt> \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	short int out[MAX_SIZE]; //i노드를 출력했는지 여부. out[TRUE]: 출력 가능 / out[FALSE]: 이미 출력해서 출력 불가
	Node* seq[MAX_SIZE]; //seq[i]: i노드와 직접적으로 동치관계에 있는 모든 노드들의 연결리스트의 시작점
	int Class[MAX_SIZE][MAX_SIZE]; //같은 클래스의 동치 부류를 저장할 배열
	int node[MAX_SIZE]; //노드(객체)를 저장할 배열
	Node* x, * y, * top; //포인터 x,y,top: 동치관계에 있는 노드들을 찾아다니며 스택에 삽입 / 삭제
	int pairs, i, j, k, n;

	//Class 배열 초기화(-1)
	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			Class[i][j] = -1;
		}
	}
	
	//node 배열 초기화(-1)
	for (i = 0; i < MAX_SIZE; i++) {
		node[i] = -1;
	}

	//input 파일 열기
	FILE* Ifile = fopen(argv[1], "r");
	if (!Ifile) {
		fprintf(stderr, "file open failed.\n");
		exit(EXIT_FAILURE);
	}

	fscanf(Ifile, "%d", &pairs); //동치쌍의 개수 저장

	for (i = 0; i < MAX_SIZE; i++) { //seq[], out[] 초기화
		out[i] = TRUE;
		seq[i] = NULL;
	}

	int maxNode = -1;
	int l = 0;
	//input파일의 동치쌍을 읽음
	while (fscanf(Ifile, "%d = %d", &i, &j) != EOF) {
		int flag = 0;
		for (k = 0; k < MAX_SIZE; k++) {
			if (node[k] == i) {
				flag = 1; //i가 이미 저장된 노드인 경우
			}
		}
		if (flag == 0) { //중복이 아닌 경우에만 저장
			node[l++] = i;
		}

		flag = 0;
		for (k = 0; k < MAX_SIZE; k++) {
			if (node[k] == j) {
				flag = 1; //j가 이미 저장된 노드인 경우
			}
		}
		if (flag == 0) { //중복이 아닌 경우에만 저장
			node[l++] = j;
		}

		if (i > maxNode) maxNode = i; //최댓값 갱신
		if (j > maxNode) maxNode = j; //최댓값 갱신

		x = (Node*)malloc(sizeof(Node));
		x->data = j; x->link = seq[i]; seq[i] = x; //노드 i의 연결리스트에 j추가
		x = (Node*)malloc(sizeof(Node));
		x->data = i; x->link = seq[j]; seq[j] = x; //노드 j의 연결리스트에 i추가
	}
	n = maxNode + 1; //n은 최댓값 + 1 로 설정(정점 번호가 전체 노드 개수보다 클 경우 에러가 나는 것을 방지)

	fclose(Ifile);

	/*노드 확인
	for (i = 0; i < l; i++) {
		printf("%d ", node[i]);
	}
	printf("\n\n");
	*/

	int totalClass = 0; //totalClass: 총 클래스 개수
	//out[]배열을 사용해 방문 여부를 확인하며, 스택으로 연결리스트를 순회
	for (i = 0; i < n; i++) {//DFS 탐색: 새로운 노드를 발견할때마다 스택을 사용해 탐색 상태를 저장한다.
		
		//비어있는 번호는 건너뛰어야하므로, 비어있는 번호인지 실제로 노드가 있는 번호인지 확인한다
		int flag = 0;
		for (k = 0; k < l;k++) {
			if (i == node[k]) {
				flag = 1;
			}
		}
		if(flag!=0) { //실제로 있는 노드인 경우에만 처리한다.
			if (out[i]) {//방문하지 않았다면
				int num = 0;
				Class[totalClass][num++] = i; out[i] = FALSE;//동치 부류 저장 후 방문 표시
				x = seq[i]; top = NULL; //스택 초기화
				for (;;) {
					while (x) {
						j = x->data; //스택에서 꺼낸 노드로 이동
						if (out[j]) { //방문하지 않았다면 
							Class[totalClass][num++] = j; out[j] = FALSE; //동치 부류 저장 후 방문 표시
							y = x->link;
							x->link = top;
							top = x; //스택 갱신(Push)
							x = y; //다음노드로 이동
						}
						else {
							x = x->link; //방문한 노드라면 다음 노드로 이동
						}
					}
					if (top == NULL) { //스택이 비었으면(즉 i노드와 동치관계인 모든 노드들을 방문하여 출력하였으면) 종료
						break;
					}
					x = seq[top->data]; //스택에서 꺼내기(Pop)
					top = top->link;//스택갱신
				}
				totalClass++;
			}
		}
	}

	FILE* Ofile = fopen(argv[2], "w"); //output파일 열기
	if (!Ofile) {
		fprintf(stderr, "file open failed.\n");
		exit(EXIT_FAILURE);
	}

	printf("total Number of equivalence Classes: %d\n\n", totalClass);
	fprintf(Ofile, "total Number of equivalence Classes: %d\n\n", totalClass);

	for (i = 0; i < totalClass; i++) {
		//Class 배열의 유효한 값만 qsort로 전달
		int size = 0;
		while (Class[i][size] != -1) {
			size++;
		}
		qsort(Class[i], size, sizeof(int), compare); //Class[i]의 요소들 정렬 완료
		
		printf("{ ");
		fprintf(Ofile, "{ ");
		for (j = 0; j < size; j++) {
			printf("%d", Class[i][j]);
			fprintf(Ofile, "%d", Class[i][j]);
			if (j < size - 1) { //마지막이 아닌 경우에만 쉼표 출력
				printf(", ");
				fprintf(Ofile, ", ");
			}
		}
		printf(" }\n");
		fprintf(Ofile, " }\n");
	}

	fclose(Ofile);

	return 0;
}

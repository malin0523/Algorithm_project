#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#define MAX 100		//최대 아이템의 수 

using namespace std;

typedef struct {		//아이템을 저장할 구조체
	char  key[10];
	float  p, q;
}b_tree;

struct nodetype {		//트리를 만들 때 노드를 구성할 구조체
	char key[10];
	nodetype* left;
	nodetype* right;
};

typedef nodetype* node_pointer;	//노드 포인터 구조체

int  n;				//노드의 개수
b_tree key[MAX + 1];		//입력 받을 키 구조체
int r[MAX + 2][MAX + 1];		//배열 R이 저장될 배열
float a[MAX + 2][MAX + 1];		//배열 A가 저장될 배열
float w[MAX + 2][MAX + 1];      //배열 W가 저장될 배열
node_pointer n_root;		//트리의 루트를 가리키는 구조체 포인터 변수
float min_timeavg;			//최소 평균 검색 시간을 저장할 변수

node_pointer tree_node(int i, int j);	//최적 이진 트리를 생성하는 함수
void init_b_tree();			//key값 & 확률값 입력 받음
float minimum(float a[MAX + 2][MAX + 1], int i, int j, int* k);	//최소값을 반환하는 함수
float index_sum(int i, int j);	//배열 index i 부터 j 까지 합을 구하여 값을 반환하는 함수
void opttree_arr();		//최적 이진 검색 트리 생성을 위한 배열 R & A 계산
void make_opttree();		//최적 이진 탐색 트리 생성 시작 함수
void print_arr_R();		//배열 R 출력
void print_arr_A();		//배열 A 출력
void print_min_timeavg();		//최소 평균 탐색 시간 출력 
void print_root();			//최적 이진 탐색 트리 최상위 root 출력
void print_tree(node_pointer n_root);	//최적 이진 탐색 트리 출력
void print_arr_W();

int main() {
	init_b_tree();		//key & 확률 입력
	opttree_arr();		//a배열과 r배열 구성
	print_arr_R();		//r배열 출력
	print_arr_A();		//r배열 출력
	print_arr_W();		//w배열 출력
	print_min_timeavg();	//최소 평균 탐색 시간 출력 
	make_opttree();		//최적 이진 탐색 트리 생성 
	print_root();		//최적 이진 탐색 트리 최상위 root 출력
	print_tree(n_root);	//최적 이진 탐색 트리 출력
}

/* key와 각 key에 할당될 확률 입력 받음 */
void init_b_tree() {
	FILE* fp = fopen("input.txt", "rt");

	n = 7;
	for (int i = 0; i <= n; i++) {
		fscanf(fp, "%s %f %f", &key[i].key, &key[i].p, &key[i].q);
		//key[i].p = key[i].p / 100;
		//key[i].q = key[i].q / 100;
	}
	fclose(fp);
}

/* i<=k<=j 일때 a[i][k-1]+a[k+1][j]값 중 최소값 반환 */
float minimum(float a[MAX + 2][MAX + 1], int i, int j, int* k) {
	int min_k;
	float min_value1;
	float min_value2;

	min_k = i;
	min_value2 = 10000;
	*k = min_k;

	for (min_k = i + 1; min_k <= j; min_k++) {
		min_value1 = a[i][min_k - 1] + a[min_k][j];

		if (min_value1 < min_value2) {	//최소값인지 비교 후 최소값  저장 
			min_value2 = min_value1;	//min_value2에 최소값을 넣음
			*k = min_k;		//최소값일때의  k  값  저장
		}
	}
	return min_value2;				//최소값 반환
}

/*배열 index i 부터 j 까지 합을 구하여 값을 반환하는 함수*/
float index_sum(int i, int j) {
	float sum_value = 0;
	int m;

	for (m = i; m <= j; m++)			//index i부터 j까지 합 구하기
		sum_value += key[m].p;

	return sum_value;
}

/*최적 이진 검색 트리 생성을 위한 r배열 &a배열 구성*/
void opttree_arr() {
	int i, j, k, diagonal;

	for (i = 0; i <= n; i++) {   //a배열과 r배열에 초기값 입력s
		w[i][i] = key[i].q;
		a[i][i] = 0;
		r[i][i] = i;
	}
	for (diagonal = 1; diagonal <= n; diagonal++) {
		for (i = 0; i <= n - diagonal; i++) {
			j = i + diagonal;
			w[i][j] = w[i][j - 1] + key[j].p + key[j].q;
			a[i][j] = minimum(a, i, j, &k) + w[i][j];   //일반식 구현
			r[i][j] = k;      //최소 값을 주는 k 값 저장
		}
		min_timeavg = a[1][n];      //최소 평균 검색 시간을 구함
	}
}

/* 배열 R 출력 */
void print_arr_R() {
	int i, j;
	cout << endl << "		***  배열  R  출력  ***   " << endl;
	for (i = 0; i <= n ; i++) {
		for (j = 0; j <= n; j++) {
			cout.width(7);
			cout << r[i][j];
		}
		cout << endl;
	}
}

/* 배열 A 출력 */
void print_arr_A() {
	int i, j;
	cout << endl << "		***  배열  A  출력   ***   " << endl;
	for (i = 0; i <= n; i++) {
		for (j = 0; j <= n; j++) {
			cout.width(7);
			cout << a[i][j];
		}
		cout << endl;
	}
}

void print_arr_W() {
	int i, j;
	cout << endl << "      ***  배열  W  출력  ***   " << endl;
	for (i = 0; i <= n+1; i++) {
		for (j = 0; j <= n; j++) {
			cout.width(7);
			cout << w[i][j];
		}
		cout << endl;
	}
}

/* 최소 평균 검색 시간 출력 */
void print_min_timeavg() {
	cout << endl << " * 최소 평균 검색 시간 : " << min_timeavg << endl;
}

/* 최적 이진 트리를 생성 */
void make_opttree() {
	n_root = tree_node(1, n);		//root 노드의 포인터 저장
}

/* 최적 이진 탐색 트리를 생성 */
node_pointer tree_node(int i, int j) {
	int k;
	node_pointer p;

	k = r[i][j];
	if (k == 0) {
		return NULL;
	}
	else {
		p = new nodetype;		// 새로운 노드를 위한 메모리 할당
		strcpy(p->key, key[k].key);		// key 값을 노드로 복사
		p->left = tree_node(i, k - 1);	// 왼쪽 서브 트리 생성
		p->right = tree_node(k + 1, j);	// 오른쪽 서브 트리 생성
		return p;				// 노드의 포인터 반환
	}
}

/* 최적 이진 탐색 트리 최상위 root 출력 */
void print_root() {
	node_pointer p;
	p = n_root;
	cout << endl << " * 최적 이진 탐색 트리의 최상위 node : " << p->key << endl;
}

/* 최적 이진 탐색 트리 출력 */
void print_tree(node_pointer n_root) {
	if (n_root != NULL) {
		print_tree(n_root->left);
		cout << "   " << n_root->key << '\t';
		print_tree(n_root->right);
	}
}

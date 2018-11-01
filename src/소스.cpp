/* C/C++ program to solve N Queen Problem using
   backtracking and minimum attacked board*/
#include<stdio.h> 
#include<malloc.h>
#include<time.h>

//#define DEBUG

int N;
int **attackedBoard;
int *qIndex;
clock_t startTimeBeforeMemoryAllocation, startTimeAfterMemoryAllocation, end;

void printSolution(){
	printf("----------- 충돌 판 -----------\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf(" %d ", attackedBoard[i][j]);
		printf("\n");
	}
	printf("\n");
}

void printSolution2(){
	printf("----------- 실제 판 -----------\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) {
			if (j == qIndex[i]) {
				printf(" 1 ");
			}
			else {
				printf(" 0 ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

int isNoMoreRows() {
	for (int i = 0; i < N; i++) { 
		if (qIndex[i] == -1) /* 선택받지 않은 행이 있으면 false */
			return 0; 
	}
	return 1; /* 모든 행이 선택되었으면 true */
}

int selectRowMinimumAttacked() {
	int counter, min = N + 1, row = -1;
	for (int i = 0; i < N; i++) {
		counter = 0;
		if (qIndex[i] == -1) {
			for (int j = 0; j < N; j++) {
				if (attackedBoard[i][j] == 0) /* 공격받은 회수가 0인 i행 j열 */
					counter++; /* i행의 열 중 공격받는 회수가 0인 개수 counter*/
			}
			if (counter < min) { /* counter의 최소값 선택 */
				min = counter;
				row = i;
			}
		}
	}

	return row;
}

void calcAttackedCountExceptSelectedRow(int i, int j, int value) {
	for (int k = 0; k < N; k++, i--) {
		if (qIndex[k] == -1) { /* 선택되지 않은 행만 계산한다. */
			attackedBoard[k][j] += value; /* 선택되지 않은 행의 모든 j열을 공격한다.  */
			if (j + i >= 0 && j + i < N) 
				attackedBoard[k][j + i] += value; /* 선택되지 않은 행의 우측 하단 방향 대각선으로 공격한다. */
			if (j - i >= 0 && j - i < N)
				attackedBoard[k][j - i] += value; /* 선택되지 않은 행의 좌측 하단 방향 대각선으로 공격한다. */
		}
	}
}
int solveNQWithMinimumAttackedSolution() {

	if (isNoMoreRows()) {
		end = clock(); /* 종료 시간 기록 */
		for (int i = 0; i < N; i++) {
			printf("( %d, %d )", i, qIndex[i]);
			if (i != N - 1)
				printf(", ");
		}
		printf("\n");

		return 1; /* 정답을 찾음 */
	}
	/* 각 행별로 공격받는 회수가 0인 열의 개수가
	 * 가장적은 행을 선택하여 반환한다. */
	int i = selectRowMinimumAttacked();
#ifdef DEBUG
	printf("i 선택 : %d\n", i);
#endif
	for (int j = 0; j < N; j++) {
		if (attackedBoard[i][j] == 0) { 
			qIndex[i] = j; /* i번째 행의 퀸의 위치로 j를 선택했다. */
			calcAttackedCountExceptSelectedRow(i, j, -1); /* i, j에 퀸을 뒀으니 선택된 행을 제외한 행의 공격받는 열들에 회수를 더한다. */
#ifdef DEBUG
			printf("%d, %d 선택 \n", i, j);
			printSolution2();
			printSolution();
#endif
			if (solveNQWithMinimumAttackedSolution()) {/* 재귀호출 */
				return 1; /* 정답을 찾음 */
			}
			/* BackTracking */
			calcAttackedCountExceptSelectedRow(i, j, 1); /* i, j에 퀸을 지웠으니 선택된 행을 제외한 행의 공격받는 열들에 회수를 뺀다. */
			qIndex[i] = -1; /* i번째 행의 j열 퀸의 위치 선택을 취소했다. */
#ifdef DEBUG
			printf("%d, %d 선택 취소\n", i, j);
			printSolution2();
			printSolution();
#endif
		}
	}
	return 0; /* 해당 선택지에서는 정답을 찾지 못함 -> BackTracking 
			   * 혹은 
			   * 정답이 존재하지 않음 */ 

}

int main() {
	printf("Type the number of queens for N-queen problem: ");
	scanf_s("%d", &N);
	startTimeBeforeMemoryAllocation = clock(); /* 프로그램이 시작되는 시간 */
	qIndex = (int *)malloc(sizeof(int) * N); /* 각 행의 열 선택지 */
	attackedBoard = (int **)malloc(sizeof(int*) * N); /* 공격보드 */
	for (int i = 0; i < N; i++) {
		attackedBoard[i] = (int *)malloc(sizeof(int) * N);
		for (int j = 0; j < N; j++)
			attackedBoard[i][j] = 0;
		qIndex[i] = -1; /* -1은 선택되지 않음을 의미 */
	}
	startTimeAfterMemoryAllocation = clock(); /* 메모리 할당 이후 순수 탐색 시작 시간 */
	if (solveNQWithMinimumAttackedSolution()) { /* 최소 공격 방법을 이용한 NQueens 문제 해결 */
#ifdef DEBUG
		printSolution();
#endif
		//printSolution2();
		printf("총 실행시간: %.3lf\n", (end - startTimeBeforeMemoryAllocation) / (double)1000);
		printf("메모리 할당 이후 실행시간: %.3lf\n", (end - startTimeAfterMemoryAllocation) / (double)1000);
	}else { /* 정답이 존재하지 않음 */
		printf("Solution does not exist.\n");
	}

	for (int i = 0; i < N; i++) {
		free(attackedBoard[i]);
	}
	free(attackedBoard);
	free(qIndex);
	return 0;
}
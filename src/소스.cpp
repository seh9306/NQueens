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
	printf("----------- �浹 �� -----------\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf(" %d ", attackedBoard[i][j]);
		printf("\n");
	}
	printf("\n");
}

void printSolution2(){
	printf("----------- ���� �� -----------\n");
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
		if (qIndex[i] == -1) /* ���ù��� ���� ���� ������ false */
			return 0; 
	}
	return 1; /* ��� ���� ���õǾ����� true */
}

int selectRowMinimumAttacked() {
	int counter, min = N + 1, row = -1;
	for (int i = 0; i < N; i++) {
		counter = 0;
		if (qIndex[i] == -1) {
			for (int j = 0; j < N; j++) {
				if (attackedBoard[i][j] == 0) /* ���ݹ��� ȸ���� 0�� i�� j�� */
					counter++; /* i���� �� �� ���ݹ޴� ȸ���� 0�� ���� counter*/
			}
			if (counter < min) { /* counter�� �ּҰ� ���� */
				min = counter;
				row = i;
			}
		}
	}

	return row;
}

void calcAttackedCountExceptSelectedRow(int i, int j, int value) {
	for (int k = 0; k < N; k++, i--) {
		if (qIndex[k] == -1) { /* ���õ��� ���� �ุ ����Ѵ�. */
			attackedBoard[k][j] += value; /* ���õ��� ���� ���� ��� j���� �����Ѵ�.  */
			if (j + i >= 0 && j + i < N) 
				attackedBoard[k][j + i] += value; /* ���õ��� ���� ���� ���� �ϴ� ���� �밢������ �����Ѵ�. */
			if (j - i >= 0 && j - i < N)
				attackedBoard[k][j - i] += value; /* ���õ��� ���� ���� ���� �ϴ� ���� �밢������ �����Ѵ�. */
		}
	}
}
int solveNQWithMinimumAttackedSolution() {

	if (isNoMoreRows()) {
		end = clock(); /* ���� �ð� ��� */
		for (int i = 0; i < N; i++) {
			printf("( %d, %d )", i, qIndex[i]);
			if (i != N - 1)
				printf(", ");
		}
		printf("\n");

		return 1; /* ������ ã�� */
	}
	/* �� �ະ�� ���ݹ޴� ȸ���� 0�� ���� ������
	 * �������� ���� �����Ͽ� ��ȯ�Ѵ�. */
	int i = selectRowMinimumAttacked();
#ifdef DEBUG
	printf("i ���� : %d\n", i);
#endif
	for (int j = 0; j < N; j++) {
		if (attackedBoard[i][j] == 0) { 
			qIndex[i] = j; /* i��° ���� ���� ��ġ�� j�� �����ߴ�. */
			calcAttackedCountExceptSelectedRow(i, j, -1); /* i, j�� ���� ������ ���õ� ���� ������ ���� ���ݹ޴� ���鿡 ȸ���� ���Ѵ�. */
#ifdef DEBUG
			printf("%d, %d ���� \n", i, j);
			printSolution2();
			printSolution();
#endif
			if (solveNQWithMinimumAttackedSolution()) {/* ���ȣ�� */
				return 1; /* ������ ã�� */
			}
			/* BackTracking */
			calcAttackedCountExceptSelectedRow(i, j, 1); /* i, j�� ���� �������� ���õ� ���� ������ ���� ���ݹ޴� ���鿡 ȸ���� ����. */
			qIndex[i] = -1; /* i��° ���� j�� ���� ��ġ ������ ����ߴ�. */
#ifdef DEBUG
			printf("%d, %d ���� ���\n", i, j);
			printSolution2();
			printSolution();
#endif
		}
	}
	return 0; /* �ش� ������������ ������ ã�� ���� -> BackTracking 
			   * Ȥ�� 
			   * ������ �������� ���� */ 

}

int main() {
	printf("Type the number of queens for N-queen problem: ");
	scanf_s("%d", &N);
	startTimeBeforeMemoryAllocation = clock(); /* ���α׷��� ���۵Ǵ� �ð� */
	qIndex = (int *)malloc(sizeof(int) * N); /* �� ���� �� ������ */
	attackedBoard = (int **)malloc(sizeof(int*) * N); /* ���ݺ��� */
	for (int i = 0; i < N; i++) {
		attackedBoard[i] = (int *)malloc(sizeof(int) * N);
		for (int j = 0; j < N; j++)
			attackedBoard[i][j] = 0;
		qIndex[i] = -1; /* -1�� ���õ��� ������ �ǹ� */
	}
	startTimeAfterMemoryAllocation = clock(); /* �޸� �Ҵ� ���� ���� Ž�� ���� �ð� */
	if (solveNQWithMinimumAttackedSolution()) { /* �ּ� ���� ����� �̿��� NQueens ���� �ذ� */
#ifdef DEBUG
		printSolution();
#endif
		//printSolution2();
		printf("�� ����ð�: %.3lf\n", (end - startTimeBeforeMemoryAllocation) / (double)1000);
		printf("�޸� �Ҵ� ���� ����ð�: %.3lf\n", (end - startTimeAfterMemoryAllocation) / (double)1000);
	}else { /* ������ �������� ���� */
		printf("Solution does not exist.\n");
	}

	for (int i = 0; i < N; i++) {
		free(attackedBoard[i]);
	}
	free(attackedBoard);
	free(qIndex);
	return 0;
}
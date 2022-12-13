#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int m[17][17];
int L[17][17];

int min(int x, int y) {
	if (x > y) {
		return y;
	}
	else {
		return x;
	}
}

int mat(int i, int j) {
	if (i == 1 && j == 1) {
		return m[i][j];
	}
	else if (i == 1) {
		return mat(i, j - 1) + m[i][j];
	}
	else if (j == 1) {
		return mat(i - 1, j) + m[i][j];
	}
	else {
		return min(mat(i - 1, j), mat(i, j - 1)) + m[i][j];
	}
}

int mat_memo(int i, int j) {
	if (L[i][j] != -1) return L[i][j];
	
	if (i == 1 && j == 1) {
		L[i][j] = m[i][j];
	}
	else if (i == 1) {
		L[i][j] = mat_memo(i, j - 1) + m[i][j];
	}
	else if (j == 1) {
		L[i][j] = mat_memo(i - 1, j) + m[i][j];
	}
	else {
		L[i][j] = min(mat_memo(i - 1, j), mat_memo(i, j - 1)) + m[i][j];
	}
	return L[i][j];
}

int mat_DP(int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == 1 && j == 1) {
				L[i][j] = m[1][1];
			}
			else if (i == 1) {
				L[i][j] = L[i][j - 1] + m[i][j];
			}
			else if (j == 1) {
				L[i][j] = L[i - 1][j] + m[i][j];
			}
			else {
				L[i][j] = min(L[i - 1][j], L[i][j - 1]) + m[i][j];
			}
		}
	}
	return L[n][n];
}

int main() {
	clock_t start1, start2, start3, end1, end2, end3;
	float time1, time2, time3;

	for (int n = 10; n <= 16; n += 3) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				m[i][j] = rand();
				L[i][j] = -1;
				printf("%d\t", m[i][j]);
			}
			printf("\n");
		}

		start1 = clock();
		int result1 = mat(n, n);
		end1 = clock();
		time1 = (float)(end1 - start1) / CLOCKS_PER_SEC;

		start2 = clock();
		int result2 = mat_memo(n, n);
		end2 = clock();
		time2 = (float)(end2 - start2) / CLOCKS_PER_SEC;

		start3 = clock();
		int result3 = mat_DP(n);
		end3 = clock();
		time3 = (float)(end3 - start3) / CLOCKS_PER_SEC;

		printf("Recursive:%d(%f sec)\tMemoization:%d(%f sec)\tDP:%d(%f sec)\n", result1, time1, result2, time2, result3, time3);
	}
	return 0;
}
//https://www.acmicpc.net/problem/1720//
//problem solved by hzw 
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MX 31
int dp1[MX], dp2[MX];
int N, temp;
int main() {
	scanf("%d", &N);
	dp1[1] = 1, dp1[2] = 3;
	for (int i = 3; i <= N; i++) {
		dp1[i] = dp1[i - 1] + dp1[i - 2] * 2;
	}
	dp2[1] = 1, dp2[2] = 3;
	for (int i = 3; i <= N; i++) {
		if (i & 1) {
			temp = dp1[(i - 1) / 2];
		}
		else
			temp = dp1[i / 2] + (2 * dp1[(i - 2) / 2]);
		dp2[i] = dp1[i] + temp;
		dp2[i] /= 2;
	}
	printf("%d\n", dp2[N]);
	return 0;
}

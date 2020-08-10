#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#define MX 201
#define INF 987654321
int dp[MX][MX];
int arr[MX];
int N, K;
int min(int r, int l) {
	if (l < r)
		return l;
	return r;
}
int dip(int l, int r) {
	if (l == r)
		return 0;
	if (dp[l][r] != -1)
		return dp[l][r];
	dp[l][r] = INF;
	for (int i = l; i < r; i++) {
		int tmp = 0;
		if (arr[l] != arr[i + 1]) {
			tmp = 1;
		}
		dp[l][r] = min(dp[l][r], dip(l, i) + dip(i + 1, r) + tmp);
	}
	return dp[l][r];
}
int main() {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &arr[i]);
	}
	memset(dp, -1, sizeof(dp));

	printf("%d", dip(1, N));
	return 0;
}
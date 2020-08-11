//https://www.acmicpc.net/problem/17144
//problem Solved by HZW
#include<stdio.h>
struct posi {
	int first, second;
};
int R, C, T;
int MAP[50][50];
int tp[50][50];
int dx[] = { 0,0,1,-1 }, dy[] = { 1,-1,0,0 };
struct posi cleaner[2];
int cptr;
void spread(int x, int y) {
	int val = MAP[x][y];
	int rot = 0;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i]; int ny = y + dy[i];
		if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
		if (MAP[nx][ny] == -1) continue;
		tp[nx][ny] += val / 5;
		rot += 1;
	}
	MAP[x][y] -= rot * (val / 5);
}

void rot() {
	int x = cleaner[0].first; int y = cleaner[0].second;
	for (int i = cleaner[0].first - 1; i >= 1; i--) {
		MAP[i][y] = MAP[i - 1][y];
	}
	for (int i = 0; i < C - 1; i++) {
		MAP[0][i] = MAP[0][i + 1];
	}
	for (int i = 0; i < x; i++) {
		MAP[i][C - 1] = MAP[i + 1][C - 1];
	}
	for (int i = C - 1; i >= 2; i--) {
		MAP[x][i] = MAP[x][i - 1];
	}
	MAP[x][y + 1] = 0;
	x = cleaner[1].first; y = cleaner[1].second;
	for (int i = x + 1; i < R - 1; i++) {
		MAP[i][0] = MAP[i + 1][0];
	}
	for (int i = 0; i < C - 1; i++) {
		MAP[R - 1][i] = MAP[R - 1][i + 1];
	}
	for (int i = R - 1; i > x; i--) {
		MAP[i][C - 1] = MAP[i - 1][C - 1];
	}
	for (int i = C - 1; i >= 2; i--) {
		MAP[x][i] = MAP[x][i - 1];
	}
	MAP[x][y + 1] = 0;
}

void simul() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (MAP[i][j] >= 5) {
				spread(i, j);
			}
			else continue;
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			MAP[i][j] += tp[i][j];
			tp[i][j] = 0;
		}
	}
	rot();
}
int main() {
	scanf("%d %d %d", &R, &C, &T);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf("%d", &MAP[i][j]);
			if (MAP[i][j] == -1) {
				cleaner[cptr].first = i; cleaner[cptr].second = j;
				cptr += 1;
			}
		}
	}
	for (int t = 0; t < T; t++) {
		simul();
	}
	int ans = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (MAP[i][j] > 0) ans += MAP[i][j];
		}
	}
	printf("%d\n", ans);
	return 0;
}

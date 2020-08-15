//https://www.acmicpc.net/problem/17141
//prolbem solved hzw94
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#define MAX 50
#define QS 10000
#define INF 987654321
typedef struct {
	int first, second;
}pair;
int N, M, ans = INF;
int map[MAX][MAX];
int d[MAX][MAX];
pair virus[10];
pair q[QS];
int vpick[10];
int vptr, wall;
int dx[] = { 0,0,1,-1 }, dy[] = { 1,-1,0,0 };

int bfs(pair vir[], int ptr) {
	memset(d, -1, sizeof(d));
	int vcnt = 0;
	int front = 0, rear = 0;
	for (int i = 0; i < ptr; i++) {
		q[rear].first = vir[i].first, q[rear].second = vir[i].second;
		rear += 1;
		d[vir[i].first][vir[i].second] = 0;
		vcnt += 1;
	}
	int ret = 0;
	while (front != rear) {
		int x = q[front].first; int y = q[front].second;
		front += 1;
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i]; int ny = y + dy[i];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			if (map[nx][ny] == 1) continue;
			if (d[nx][ny] != -1) continue;
			q[rear].first = nx; q[rear].second = ny;
			rear += 1;
			d[nx][ny] = d[x][y] + 1;
			vcnt += 1;
			if (d[nx][ny] > ret)
				ret = d[nx][ny];
		}			
	}
	//printf("FUCK%d\n", ret);
	if (vcnt != N*N - wall)
		return INF;
	return ret;
}

void choice(int v, pair vir[], int ptr) {
	if (ptr > vptr)
		return;
	if (v == M) {
		int result = bfs(vir, v);
		//printf("%d,\n", result);
		if (result < ans)
			ans = result;
		return;
	}
	vir[v] = virus[ptr];
	choice(v + 1, vir, ptr + 1);
	vir[v].first = 0, vir[v].second = 0;
	choice(v, vir, ptr + 1);
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2) {
				virus[vptr].first = i; virus[vptr].second = j;
				vptr += 1;
			}
			if (map[i][j] == 1) {
				wall += 1;
			}
		}
	}
	pair pi[10];
	choice(0, pi, 0);
	if (ans == INF)
		printf("%d\n", -1);
	else printf("%d\n", ans);
	return 0;
}

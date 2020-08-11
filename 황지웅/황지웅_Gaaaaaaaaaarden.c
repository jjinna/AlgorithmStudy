//https://www.acmicpc.net/problem/18809
//problem solved by Hzw
#include<stdio.h>
#include<string.h>
#define MAX 5000
struct pair {
	int first, second;
};
int N, M, G, R;
struct pair mp[12];
int ptrm;
int ans;
int map[50][50];
int d[50][50][2];
struct pair q1[MAX];
struct pair q2[MAX];
int dx[] = { 0,0,1,-1 }, dy[] = { 1,-1,0,0 };
int fr, rr, fg, rg;
int bfs(int g[], int r[], int gp, int rp) {
	memset(d, -1, sizeof(d));
	fr = 0, rr = 0, fg = 0, rg = 0;
	for (int i = 0; i < gp; i++) {
		q1[rg].first = mp[g[i]].first; q1[rg].second = mp[g[i]].second;
		d[q1[rg].first][q1[rg].second][1] = 0;
		rg += 1;
	}
	for (int i = 0; i < rp; i++) {
		q2[rr].first = mp[r[i]].first; q2[rr].second = mp[r[i]].second;
		d[q2[rr].first][q2[rr].second][0] = 0;
		rr += 1;
	}
	int ret = 0;
	while (1) {
		int st = fr; int ed = rr;
		for (int i = st; i < ed; i++) {
			int x = q2[i].first; int y = q2[i].second;
			fr += 1;
			if (d[x][y][0] == d[x][y][1]) {
				ret += 1;
				continue;
			}
			for (int j = 0; j < 4; j++) {
				int nx = x + dx[j]; int ny = y + dy[j];
				if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
				if (map[nx][ny] == 0) continue;
				if (d[nx][ny][0] >= 0 || d[nx][ny][1] >= 0) continue;
				d[nx][ny][0] = d[x][y][0] + 1;
				q2[rr].first = nx; q2[rr].second = ny;
				rr += 1;
			}
		}
		st = fg; ed = rg;
		for (int i = st; i < ed; i++) {
			int x = q1[i].first; int y = q1[i].second;
			fg += 1;
			for (int j = 0; j < 4; j++) {
				int nx = x + dx[j]; int ny = y + dy[j];
				if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
				if (map[nx][ny] == 0) continue;
				if (d[nx][ny][0] == -1) {
					if (d[nx][ny][1] >= 0)continue;
					d[nx][ny][1] = d[x][y][1] + 1;
					q1[rg].first = nx; q1[rg].second = ny;
					rg += 1;
				}
				else {
					if (d[nx][ny][0] == d[x][y][1] + 1) {
						d[nx][ny][1] = d[x][y][1] + 1;
					}
				}
			}
		}
		if (fr == rr && fg == rg) break;
	}
	return ret;
}
void choiceG(int g[], int r[], int gp, int rp, int cnt) {
	if (cnt > ptrm) {
		return;
	}
	if (gp == G && rp == R) {
		int sum = bfs(g, r, gp, rp);
		if (sum > ans)
			ans = sum;
		return;
	}
	if (gp < G) {
		g[gp] = cnt;
		choiceG(g, r, gp + 1, rp, cnt + 1);
		g[gp] = 0;
	}
	if (rp < R) {
		r[rp] = cnt;
		choiceG(g, r, gp, rp + 1, cnt + 1);
		r[rp] = 0;
	}
	choiceG(g, r, gp, rp, cnt + 1);
}
int main() {
	scanf("%d %d %d %d", &N, &M, &G, &R);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2) {
				mp[ptrm].first = i; mp[ptrm].second = j;
				ptrm += 1;
			}
		}
	}
	int r[6] = { 0,0,0,0,0,0 };
	int g[6] = { 0,0,0,0,0,0 };
	choiceG(g, r, 0, 0, 0);
	printf("%d\n", ans);
	return 0;
}

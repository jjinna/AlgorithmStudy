//https://www.acmicpc.net/problem/16236//
//pb solved by hzw
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX 500
struct shark {
	int first, second, size, feed;
};
struct pair {
	int first, second;
};
struct shark sk;
struct pair q[MAX];
int N,rear,front;
int map[20][20];
int d[20][20];
int dx[] = { 0,0,1,-1 }, dy[] = { 1,-1,0,0 };
int ans = 0;
void gofeed() {
	rear = 0, front = 0;
	q[rear].first = sk.first; q[rear].second = sk.second;
	d[sk.first][sk.second] = 1;
	rear += 1;
	int ok = 0;
	int gx = 987, gy = 987;
	int ret = 0;
	int ct = 1;
	int val = 0;
	while (front != rear) {
		int st = front, ed = rear;
		val += 1;
		for (int i = st; i < ed; i++) {
			int x = q[front].first; int  y = q[front].second;
			front += 1;
			for (int j = 0; j < 4; j++) {
				int nx = x + dx[j]; int ny = y + dy[j];
				if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
				if (d[nx][ny] >= ct) continue;
				if (map[nx][ny] <= sk.size) {
					if (map[nx][ny] > 0 && map[nx][ny] < sk.size) {
						if (gx > nx) {
							gx = nx; gy = ny;
						}
						else if (gx == nx) {
							if (gy > ny)
								gy = ny;
						}
						ok = 1;
					}
					else if(map[nx][ny] == 0 || map[nx][ny] == sk.size){
						d[nx][ny] = ct;
						q[rear].first = nx; q[rear].second = ny;
						rear += 1;
					}
				}
			}
		}
		if (ok) {
			sk.feed += 1;
			ct += 1;
			if (sk.feed == sk.size) {
				sk.feed = 0; sk.size += 1;
			}
			ans += val;
			val = 0;
			sk.first = gx; sk.second = gy;
			front = 0, rear = 0;
			q[rear].first = gx; q[rear].second = gy;
			d[gx][gy] = ct;
			rear += 1;
			map[gx][gy] = 0;
			gx = 987, gy = 987;
			ok = 0;
		}
	}
}
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9) {
				sk.first = i; sk.second = j;
				sk.size = 2;
				map[i][j] = 0;
			}
		}
	}gofeed();
	printf("%d\n",ans);
}

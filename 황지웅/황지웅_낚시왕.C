//https://www.acmicpc.net/problem/17143
//ps by hzw94
#include <stdio.h>
#include <string.h>

struct shark {
	int s, d, z;
};

int r, c, m, ans;
struct shark map[100][100];
const int dx[] = { -1, 1, 0, 0 }, dy[] = { 0, 0, 1, -1 };
void input(int x, int y, int s, int d, int z) {
	map[x - 1][y - 1].s = s;
	map[x - 1][y - 1].d = d;
	map[x - 1][y - 1].z = z;
}
void Eaten(int x, int y) {
	map[x][y].s = 0;
	map[x][y].d = 0;
	map[x][y].z = 0;
}
void solve() {
	for (int t = 0; t < c; t++) {
		struct shark temp[100][100] = { 0 };
		// Fishing a shark
		for (int i = 0; i < r; i++) {
			if (map[i][t].z) {
				ans += map[i][t].z;
				map[i][t].s = 0; map[i][t].d = 0; map[i][t].z = 0;
				break;
			}
		}
		// Sharks move
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (map[i][j].z) {
					if (map[i][j].d < 2) { // Up, Down
						int s = map[i][j].s % ((r - 1) * 2);
						int d = map[i][j].d;
						int ni = i;
						while (s--) {
							if (ni == 0 && d == 0) d = 1;
							if (ni == r - 1 && d == 1) d = 0;
							ni += dx[d];
						}
						if (map[i][j].z > temp[ni][j].z) {
							temp[ni][j].s = map[i][j].s; temp[ni][j].d = d; temp[ni][j].z = map[i][j].z;
						}
					}
					else { // Right, Left
						int s = map[i][j].s % ((c - 1) * 2);
						int d = map[i][j].d;
						int nj = j;
						while (s--) {
							if (nj == 0 && d == 3) d = 2;
							if (nj == c - 1 && d == 2) d = 3;
							nj += dy[d];
						}
						if (map[i][j].z > temp[i][nj].z) {
							temp[i][nj].s = map[i][j].s; temp[i][nj].d = d; temp[i][nj].z = map[i][j].z;
						}
					}
					Eaten(i, j);
				}
			}
		}
		memcpy(map, temp, sizeof(temp));
	}
}

int main() {
	scanf("%d %d %d", &r, &c, &m);
	for (int i = 0; i < m; i++) {
		int x, y, s, d, z;
		scanf("%d %d %d %d %d", &x, &y, &s, &d, &z);
		input(x, y, s, d-1, z);
	}
	solve();
	printf("%d\n", ans);
	return 0;
}

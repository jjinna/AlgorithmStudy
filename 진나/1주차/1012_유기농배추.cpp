#include<iostream>
#include<memory.h>
#define MAX 50

using namespace std;

int M, N, K;
int input[MAX][MAX];
int visited[MAX][MAX];

int dx[4] = { 0,0,- 1,1 };	//»óÇÏÁÂ¿ì
int dy[4] = {-1,1,0,0};//»óÇÏÁÂ¿ì

void dfs(int height,int width) {
	visited[height][width] = 1;

	for (int i = 0; i < 4; i++) {
		int nexty = height + dy[i];
		int nextx = width + dx[i];

		if (nexty < 0 || nextx < 0 || nexty >= N || nextx >= M)	continue;
		if (input[nexty][nextx] && !visited[nexty][nextx])  dfs(nexty, nextx);
	}
}

int main() {
	int t_case;
	cin >> t_case;

	int yindex,xindex;
	while (t_case--) {
		int cnt = 0;
		memset(input, 0, sizeof(input));
		memset(visited, 0, sizeof(visited));

		cin >> M >> N >> K;

		while (K--) {
			cin >> xindex >> yindex;
			input[yindex][xindex] = 1;
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (input[i][j] && !visited[i][j]) {
					dfs(i, j);
					cnt++;
				}
			}
		}

		cout << cnt << endl;	
	}
}
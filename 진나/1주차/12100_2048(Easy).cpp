//12100번 2048(Easy)
//https://www.acmicpc.net/problem/12100

#include<iostream>
#include<vector>
#include<algorithm>
#define NMAX 21
using namespace std;

int N, board[NMAX][NMAX];
int ans = 0;
void init() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
}

//a에서 b로 복사
void map_cpy(int a[NMAX][NMAX],int b[NMAX][NMAX]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			b[i][j] = a[i][j];
		}
	}
}

void dfs(int idx) {
	if (idx == 5) {
		int res = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (board[i][j] > res)	res = board[i][j];
			}
		}
		if (res > ans)	ans = res;
		return;
	}

	//0좌, 1우, 2상, 3하
	for (int k = 0; k < 4; k++) {
		//맵 복사
		int temp[NMAX][NMAX];
		map_cpy(board, temp);
		
		for (int i = 0; i < N; i++) {
			vector<int> q;
			for (int j = 0; j < N; j++) {
				if (k < 2&&board[i][j]!=0) q.push_back(board[i][j]);
				else if(k>=2 &&board[j][i]!=0) q.push_back(board[j][i]);
			}

			if (k == 1 || k == 3) reverse(q.begin(), q.end());

			vector<int> merge;
			for (int j = 0; j < q.size(); j++) {
				if (j+1<q.size()&&q[j] == q[j + 1]) { 
					merge.push_back(q[j] * 2);
					j++;
				}
				else {
					merge.push_back(q[j]);
				}
			}

			for (int j = merge.size(); j < N; j++) {
				merge.push_back(0);
			}

			if (k == 1 || k == 3) reverse(merge.begin(), merge.end());

			for (int j = 0; j < N; j++) {
				if (k < 2) { board[i][j] = merge[j]; }
				else { board[j][i] = merge[j]; }
			}
		}

		dfs(idx + 1);

		//맵 돌려두기
		map_cpy(temp, board);
	}
}

int main() {
	init();
	dfs(0);
	cout << ans;
}
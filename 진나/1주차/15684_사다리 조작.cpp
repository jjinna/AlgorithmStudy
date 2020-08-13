//https://www.acmicpc.net/problem/15684
//15684_사다리조작

#include<iostream>
#define scanf scanf_s
#define MAX 31
using namespace std;

int N, M, H;	//세로선 N개, 가로선 M개, 가로선 놓을 수 있는 위치 H개
int a, b;	//b번 세로선과 b+1번 세로선을 a번 점선 위치에서 연결
int input[MAX][MAX];
int ans = -1,ladder_num;
void init() {
	scanf("%d %d %d", &N, &M, &H);

	int yindex, xindex;
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &yindex, &xindex);
		input[yindex][xindex] = 1;
	}
}

bool ladder() {
	for (int i = 1; i <= N; i++) {	//시작점
		int cur = i;
		for (int j = 1; j <= H; j++) {
			if (input[j][cur])	cur+=1;	//오른쪽으로 이동
			else if (input[j][cur - 1])	cur -= 1;	//왼쪽으로 이동
		}
		if (i != cur)	return false;
	}

	return true;
}

void dfs(int x,int cnt) {
	if (cnt > 3)	return;	//3개 이상 놓는경우
	//정답을 찾은 경우
	if (ladder()) { ans = cnt;}
	if (ans != -1)	return;

	//조합 탐색
	for (int i = x; i <= H; i++) {
		for (int j = 1; j <= N; j++) {
			if (input[i][j - 1]||input[i][j+1]||input[i][j])	continue;	//가로선이 연속하면 안됨
			input[i][j] = 1;
			dfs(i,cnt + 1);
			input[i][j] = 0;
		}
	}
}

int main() {
	init();
	dfs(1, 0);
	cout << ans;
}
#include<iostream>
#include<vector>

using namespace std;

int board[101][101];
int dy[4] = { 0,-1,0,1 }, dx[4] = { 1,0,-1,0 };	//0:x증가,1:y감소,2:x감소,3:y증가

vector<int> direction;
void makeDrg(int y,int x,int g,int step) {
	//base case(저장된 방향정보 토대로 좌표 움직임)
	if (step == g) { 
		for (int i = 0; i < direction.size(); i++) {
			y = y+dy[direction[i]]; x = x+dx[direction[i]];
			board[y][x] = 1;
		}
		return; 
	}
	
	//방향정보 저장
	int cur = direction.size() - 1;
	while (cur >= 0) {
		int movedir = direction[cur];
		if (movedir == 3)	direction.push_back(0);
		else direction.push_back(movedir + 1);
		cur--;
	}

	makeDrg(y,x, g, step + 1);
}

void init() {
	int N, x, y, d, g;
	cin >> N;
	for (int i = 0; i < N; i++) {
		direction.clear();
		cin >> x >> y >> d >> g;

		direction.push_back(d);
		board[y][x] = 1;

		makeDrg(y,x,g,0);
	}
}

int main() {
	init();

	int ans = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (board[i][j] && board[i + 1][j] && board[i][j + 1] && board[i + 1][j + 1])	ans++;
		}
	}
	cout << ans;
}
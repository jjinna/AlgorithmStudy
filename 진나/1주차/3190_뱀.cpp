#include<iostream>
#include<queue>

#define MAX 102
using namespace std;

int N, K,L;	//N:보드의 크기, K:사과의 개수, L:뱀의 방향 변환 횟수
int board[MAX][MAX];
queue<pair<int, int>> turnInfo;	//<X초,방향(1:오른쪽,-1:왼쪽)>
queue<pair<int, int>> tailInfo;
int nexty[4] = {0,1,0,-1},nextx[4] = {1,0,-1,0};	//이동방향(오른쪽,아래,왼쪽,위)

void init() {
	cin >> N;
	cin >> K;

	int temp1, temp2;
	for (int i = 0; i < K; i++) {
		cin >> temp1 >> temp2;
		board[temp1][temp2] = 2;
	}

	cin >> L;

	int temp3; char temp4;
	for (int i = 0; i < L; i++) {
		cin >> temp3 >> temp4;
		if (temp4 == 'D') {	//오른쪽
			turnInfo.push({ temp3,1 });
		}else {	//왼쪽
			turnInfo.push({ temp3,-1 });
		}
	}

	board[1][1] = 1;	//뱀의 시작 위치 : (1,1)
}

int bfs() {
	int curMovedir = 0, curTime = 0, turnTime;
	int taily = 1, tailx = 1, heady = 1, headx = 1;
	int temp1, temp2;
	while (1) {
		curTime++;

		//머리 이동
		heady += nexty[curMovedir];
		headx += nextx[curMovedir];

		tailInfo.push({ heady,headx });

		if (heady<1 || headx<1 || heady>N || headx>N) { return curTime; }	//보드 벗어남
		if (board[heady][headx] == 1) { return curTime; }

		if (board[heady][headx] == 0) {	//사과없으면, 몸 움직임
			board[taily][tailx] = 0;
			board[heady][headx] = 1;

			taily = tailInfo.front().first;
			tailx = tailInfo.front().second;
			tailInfo.pop();
		}
		else if (board[heady][headx] == 2) {	//사과있으면 몸 늘림
			board[heady][headx] = 1;
		}

		if (!turnInfo.empty()) {
			turnTime = turnInfo.front().first;

			//방향전환시간
			if (curTime == turnTime) {
				curMovedir += turnInfo.front().second;
				turnInfo.pop();

				if (curMovedir == -1)	curMovedir = 3;
				else if (curMovedir == 4)	curMovedir = 0;
			}
		}
	}
}
int main() {
	init();
	cout<<bfs();
}
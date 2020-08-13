//14888 ¿¬»êÀÚ ³¢¿ö³Ö±â
//https://www.acmicpc.net/problem/14888

#include<iostream>
#include<limits.h>
#include<algorithm>
#include<vector>

#define NMAX 12
using namespace std;

int N, inputNum[NMAX];
vector<int> op;	//0:µ¡¼À, 1:»¬¼À, 2:°ö¼À, 3:³ª´°¼À
int result[NMAX];
int visited[NMAX];

int maxx =INT_MIN, minn = INT_MAX;
void init() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> inputNum[i];
	}
	int temp;
	for (int i = 0; i < 4; i++) {
		cin >> temp;
		
		for (int j = 0; j < temp; j++) {
			op.push_back(i);
		}
	}
}

void permu(int depth) {
	if (depth == N-1) {
		int res=0,temp=inputNum[0];
		for (int i = 0; i < N-1; i++) {
			if (result[i] == 0) {
				temp=temp + inputNum[i + 1];
			}
			else if (result[i] == 1) {
				temp= temp - inputNum[i + 1];
			}
			else if (result[i] == 2) {
				temp= temp * inputNum[i + 1];
			}
			else if (result[i] == 3) {
				if (temp < 0) {
					temp = -(abs(temp) / inputNum[i + 1]);
				}
				else {
					temp = temp / inputNum[i + 1];
				}
			}
		}
		maxx = max(temp, maxx); minn = min(temp, minn);
		return;
	}

	for (int i = 0; i < N-1; i++) {
		if (visited[i] == 0) {
			visited[i] = 1;
			result[depth] = op[i];
			permu(depth + 1);
			visited[i] = 0;
		}
	}
}

int main() {
	init();
	permu(0);
	cout << maxx << endl;
	cout<<minn << endl;
}
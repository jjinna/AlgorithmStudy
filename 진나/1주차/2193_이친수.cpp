#include<iostream>
#define NMAX 91
using namespace std;

int main() {
	int N;
	cin >> N;

	long long DP[NMAX][2];
	DP[1][0] = 0; DP[1][1] = 1;
	for (int i = 2; i <= N; i++) {
		DP[i][0] = DP[i - 1][1]+DP[i-1][0];
		DP[i][1] = DP[i - 1][0];
	}

	cout << DP[N][0] + DP[N][1]<<endl;
}
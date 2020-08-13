//https://www.acmicpc.net/problem/14501
//Åğ»ç

#include<iostream>
#include<vector>

#define NMAX 16

using namespace std;

int N,  input_t[NMAX], input_p[NMAX];
int maxSum;

vector<int> pick;
void init() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> input_t[i] >> input_p[i];
	}
}

void bf(int idx) {
	if (idx + input_t[idx] > N)	return;	//Åğ»çÀÏ ÀÌÈÄ
	pick.push_back(idx);

	int sum = 0;
	for (int i = 0; i < pick.size(); i++) {
		sum += input_p[pick[i]];
	}
	if (maxSum < sum)	maxSum = sum;

	int nextidx = idx + input_t[idx];
	for (int i = nextidx; i < N; i++) {
		bf(i);
	}
	pick.pop_back();
}

int main() {
	init();
	for (int i = 0; i < N; i++) {
		if (i + input_t[i] > N)	continue;
		pick.clear();
		bf(i);
	}
	cout << maxSum;
}
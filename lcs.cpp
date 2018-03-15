#include <bits/stdc++.h>
#define INF 1000000000
#define MAX 1000

using namespace std;

int PD[MAX][MAX];
string a, b;

int pd(int i, int j){
	int resp = -INF;
	if(i < 0 || j < 0) return 0;
	if(PD[i][j] != -1) return PD[i][j];
	if(a[i] == b[j]){
		resp = max(resp, pd(i-1, j-1) + 1);
	}
	resp = max(resp, pd(i, j-1));
	resp = max(resp, pd(i-1, j));
	return PD[i][j] = resp;
}

int main(){
	cin >> a;
	cin >> b;
	int n = a.size(), m = b.size();
	memset(PD, -1, sizeof(PD));
	cout << pd(n-1, m-1) << endl;
	
	int prevScore = 0;
	stack<char> result;

	int i = n - 1, j = m - 1;
	while(i >= 0 && j >= 0){
		if(a[i] == b[j]){
			result.push(a[i]);
			i--; j--;
		}
		else if(PD[i-1][j] > PD[i][j-1]){
			i--;
		} else {
			j--;
		}
	}
	while(!result.empty()){
		cout << result.top();
		result.pop();
	}
	cout << endl;

	return 0;

}
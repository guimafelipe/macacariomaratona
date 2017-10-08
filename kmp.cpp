#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

#define INF 1000000000
#define EPS 10e-9
#define MAXN 100010


//Estuturas do kmp
int pa[MAXN], n, m;
char T[MAXN], P[MAXN];

void preProcess1(){ //minha
	int i = 1, j = 0;
	pa[0] = 0;
	while(i < m){
		if(P[i] == P[j]){
			pa[i] = j + 1;
			i++;
			j++;
		} else if(j == 0){
			pa[i] = 0;
			i++;
		} else {
			j = pa[j-1];
		}
	}

}

void preProcess2(){ //CP
	int i=0, j = -1;
	pa[0] = -1;
	while(i < m){
		while(j >= 0 && P[i] != P[j]) j = pa[j];
		i++; j++;
		pa[i] = j;
	}
}

int kmpSearch(){
	int i = 0, j = 0, resp = -1;
	while(i < n){
		if(P[j] != T[i] && j > 0){
			j = pa[j-1];
		} else if(P[j] == T[i]){
			i++; j++;
		} else {
			i++; 
		}

		if(j == m){
			resp = i - j;
			break;
		}
		//printf("%d\n", j);
	}
	return resp;

}


int main(){

	scanf("%s", P);
	m=strlen(P);
	scanf("%s", T);
	n=strlen(T);
	preProcess1();
	printf(" ");
	for(int i = 0; i < strlen(P);i++){
		printf("%d ", pa[i]);
	}
	printf("\n");
	kmpSearch();
	/*	preProcess2();
	for(int i = 0; i < strlen(P);i++){
		printf("%d ", pa[i]);
	}
	printf("\n");*/
	printf("%d\n", kmpSearch());


}
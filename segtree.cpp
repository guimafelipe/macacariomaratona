#include <bits/stdc++.h>

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> ii;

#define INF 1000000000
#define EPS 10e-9
#define f(i, a, b) for(int i = a; i < b; i++)

//Nesse exemplo, segment tree pode ser usada para mín, max, sum, freq...
//

#define left(pos) (2*pos + 1)
#define right(pos) (2*pos + 2)


int comp(int a, int b){
	return min(a,b);
}

/*Regras de query da segment tree

Regra 1) Query(a,b)

*/


vi segTree;

void constructTree(vi input, int low, int high, int pos){ //Complexidade O(n), n = sz(input)
	if(low == high){
		segTree[pos] = input[low]; //low == high, tanto faz. Detalhe: aqui estou guardando o VALOR mas poderia guardar o Índice!
		return;
	}
	int mid = (low + high)/2;
	constructTree(input, low, mid, left(pos)); //Arvore indexada em 0. Se for indexada em 1, é 2*pos e 2*pos + 1
	constructTree(input, mid + 1, high, right(pos)); 

	segTree[pos] = comp(segTree[left(pos)], right(pos)); //função que depende se é seg tree de min,max, fres, rsq...

}



int main(){
	int n;
	cin >> n;
	vi input;
	segTree.reserve(4*n);
	f(i, 0, n){
		int x;
		scanf("%d", &x);
		input.pb(x);
	}

}

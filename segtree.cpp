#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

#define INF 1000000000
#define EPS 10e-9
#define f(i, a, b) for(int i = a; i < b; i++)

//Nesse exemplo, segment tree pode ser usada para mín, max, sum, freq...
//

#define left(pos) (2*pos + 1)
#define right(pos) (2*pos + 2)

int neutro = 0;

int comp(int a, int b){
	return a + b;
}

/*Regras de query da segment tree

Regra 1) Query(a,b)

*/


vi segTree;
vi lazy;

void constructTree(vi input, int low, int high, int pos){ //Complexidade O(n), n = sz(input)
	cout << "Construiu um pedaço: low = " << low << ", high = " << high << endl;
	if(low == high){
		segTree[pos] = 0; //low == high, tanto faz. Detalhe: aqui estou guardando o VALOR mas poderia guardar o Índice!
		return;
	}
	int mid = (low + high)/2;
	constructTree(input, low, mid, left(pos)); //Arvore indexada em 0. Se for indexada em 1, é 2*pos e 2*pos + 1
	constructTree(input, mid + 1, high, right(pos)); 

	segTree[pos] = comp(segTree[left(pos)], segTree[right(pos)]); //função que depende se é seg tree de min,max, fres, rsq...

	cout << "seg tree" << pos << " = " << segTree[pos] << endl;
}

void updateTree(int node, int low, int high, int i, int j, int value){
	cout << "updating: node = " << node << "; low = " << low << ", high = " << high << ", i  = " << i << ", j = " << j << endl;
	if(lazy[node] != 0){
		segTree[node] += lazy[node];
	
		if(low != high){
			lazy[left(node)] += lazy[node];
			lazy[right(node)] += lazy[node];
		}

		lazy[node] = 0;
	}

	if(low > high || low > j || high < i) return;

	if(low >= i && high <= j){
		segTree[node] += value;

		if(low != high){
			lazy[left(node)] += value;
			lazy[right(node)] += value;
		}

		return;
	}
	int mid = (low + high)/2;
	updateTree(left(node), low, mid, i, j, value);
	updateTree(right(node), mid + 1, high, i, j, value);

	segTree[node] = comp(segTree[left(node)], segTree[right(node)]);
}

int queryTree(int node, int low, int high, int i, int j){
	cout << "query: low = " << low << ", high = " << high <<  ", i  = " << i << ", j = " << j << endl;  
	if(low > high || low > j || high < i) return neutro;

	if(lazy[node] != 0){
		segTree[node] += lazy[node];

		if(low != high){
			lazy[left(node)] += lazy[node];
			lazy[right(node)] += lazy[node];
		}

		lazy[node] = 0;
	}

	if(low >= i && high <= j) return segTree[node];

	int q1, q2;
	int mid = (low + high)/2;
	q1 = queryTree(left(node), low, mid, i, j);
	q2 = queryTree(right(node), mid + 1, high, i, j);

	int res = comp(q1, q1);

	return res;
}

int main(){
	int n;
	cin >> n;
	vi A, B;
	vi aux (4*n, 0), aux2(4*n, 0);
	segTree = aux;
	lazy = aux2;
	f(i, 0, n){
		int x;
		scanf("%d", &x);
		A.push_back(x);
	}
	f(i, 0, n){
		int x;
		scanf("%d", &x);
		B.push_back(x);
	}

	vector<int> alturas = A;

	// int n = A.size();
    sort(alturas.begin(), alturas.end());
    segTree.reserve(4*n);
    vector<int> resposta;
    // cout << segTree.size();
    constructTree(aux, 0, n-1, 0);
    cout << "construiu\n";
    for(int i = 0; i < segTree.size(); i++){
    	cout << segTree[i] << " ";
    }
    cout << endl;
    int ind;
    for(int i = B.size() - 1; i >= 0; i--){
        ind = B.size() - B[i] - 1;
        cout << "Ind = " << ind << endl;
        int q = queryTree(0, 0, n-1, ind, n-1);
        cout << "q = " << q << endl;
        int resp = ind - q;
        cout << "resp= " << resp << endl;
        updateTree(0, 0, n-1, resp, resp, 1);
        resposta.push_back(alturas[resp]);
    }

    for(int i = resposta.size() - 1 ; i >= 0; i--){
    	cout << resposta[i] << " ";
    }
    cout << endl;

}

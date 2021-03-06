#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#define mod 1000000009ll
#define MAXN 1500000
#define MAXR 15000
#define rep(i, n) for(int i = 1; i <= n; ++i)
#define repd(i, n) for(int i = n; i; --i)
using namespace std;

struct Point{
	int x, y;
	bool t;
	Point(){}
	Point(int _x, int _y, bool _t): x(_x), y(_y), t(_t){}
	bool operator < (const Point &p) const{
		return x < p.x || (x == p.x && y < p.y);
	}
} zero[MAXN], p[MAXN];

int r, c, n, pn(0);
int U[MAXN], D[MAXN], L[MAXN], R[MAXN];
long long ans(0);

int coor(int x, int y){
	if(x < 1 || x > r || y < 1 || y > c) return 0;
	return (x - 1) * c + y;
}

void dp(){
	int coo;
	memset(U, 0, sizeof(U));
	memset(D, 0, sizeof(D));
	memset(L, 0, sizeof(L));
	memset(R, 0, sizeof(R));
	rep(i, r)
		rep(j, c){
			coo = coor(i, j);
			if(p[coo].t){
				U[coo] = U[coor(i - 1, j)] + 1;
				L[coo] = L[coor(i, j - 1)] + 1;
			}
			else
				U[coo] = L[coo] = 0;
		}
	repd(i, r)
		repd(j, c){
			coo = coor(i, j);
			if(p[coo].t){
				D[coo] = D[coor(i + 1, j)] + 1;
				R[coo] = R[coor(i, j + 1)] + 1;
			}
			else
				D[coo] = R[coo] = 0;
		}
}

void add(int c1, int c2){
	long long a = U[c1] - 1, b = D[c2] - 1, x = min(L[c1] - 1, R[c1] - 1), y = min(L[c2] - 1, R[c2] - 1);
	if(min(x, y) & 1)
		ans = (ans + a * b % mod * (y - (min(x, y) + 1) / 2) % mod * min(x, y) % mod) % mod;
	else
		ans = (ans + a * b % mod * (2 * y - min(x, y) - 1) % mod * (min(x, y) / 2) % mod) % mod;
}

void buforce(){
	int coo, co;
	rep(i, r)
		rep(j, c){
			coo = coor(i, j);
			if(p[coo].t && D[coo] >= 4 && U[coo] >= 2 && L[coo] >= 2 && R[coo] >= 2)
				for(int k = 2; k < D[coo]; ++k){
					co = coor(i + k, j);
					if(D[co] >= 2 && L[co] >= 3 && R[co] >= 3)
						add(coo, co);
				}
		}
	cout << ans << endl;
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d%d", &r, &c, &n);
	rep(i, n) scanf("%d%d", &zero[i].x, &zero[i].y), zero[i].t = 0;
	sort(zero + 1, zero + 1 + n); zero[++n] = Point(r, c + 1, 0);
	int x = 1, y = 1;
	rep(i, n){
		while(x < zero[i].x){
			for(int j = y; j <= c; ++j)
				p[++pn] = Point(x, j, 1);
			y = 1;
			x++;
		}
		if(y < zero[i].y)
			for(int j = y; j < zero[i].y; ++j)
				p[++pn] = Point(x, j, 1);

		p[++pn] = zero[i];
		y = zero[i].y + 1;
	}
	pn--;
	p[0] = Point(0, 0, 0);
	dp();
	buforce();
	return 0;
}

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <deque>
#include <queue>
#include <utility>

//#include "segment_tree.h"
//#include "fenwick_tree.h"
//#include "union_find.h"
//#include "geometry.h"
using namespace std;

#define FOR(i,a,b) for(int i = (a); i <= (b); i++)
#define DOW(i,a,b) for(int i = (a); i >= (b); i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; ++i)
#define FORI(it, x) for (__typeof((x).begin()) it = (x).begin(); it != (x).end(); it++)
#define RESET(c,val) memset(c,val,sizeof(c))

#define ALL(x) x.begin(), x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())

#define sz(a) int(a.size())
#define pb push_back
#define mp make_pair
#define fi first
#define se second

// bitmask
#define isOn(S, j) (S & (1 << j))
#define setBit(S, j) (S |= (1 << j))
#define clearBit(S, j) (S &= ~(1 << j))
#define toggleBit(S, j) (S ^= (1 << j))
#define lowBit(S) (S & (-S))
#define setAll(S, n) (S = (1 << n) - 1)

// other manipulation
#define modulo(S, N) ((S) & (N - 1)) // return S % N, where N = 2^k
#define isPowerOfTwo(S) (!(S & (S - 1))
#define nearestPowerOfTwo(S) ((int)pow(2.0, (int)((log((double)S) / log(2.0)) + 0.5)))
#define turnOffLastBit(S) ((S) & (S-1))
#define turnOnLastZero(S) ((S) | (S+1))
#define turnOffLastConsecutiveBits(S) ((S) & (S + 1))
#define turnOnLastConsecutiveZeroes(S) ((S) & (S - 1))

#include "BigIntegerVector.h"

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;

/*---------------------------*/

long long  t[2][2]= { {1, 1}, {1, 0} };
long long tg[2][2]= { {1, 1}, {1, 0} };
long long dv[2][2]= { {1, 1}, {1, 0} };
long long T[2][2];

void copyT( long long a[2][2], long long b[2][2])
{
		for(int i = 0; i < 2; i++)
			for(int j = 0; j < 2; j++)
			{
				b[i][j]= a[i][j];
			}
}

void resetT()
{
	for(int i= 0; i < 2; i++)
		for(int j= 0; j < 2; j++)
        {
            t[i][j]= 0;
        }
}

void coutT( long long t[2][2])
{
	for(int i= 0; i < 2; i++)
    {
		for(int j= 0; j < 2; j++)
        {
            cout << t[i][j] << " ";
        }
        cout << endl;
    }
}

void anhNhan( long long a[2][2] , long long b[2][2])
{
    resetT();
	for(int i= 0; i < 2; i++)
		for(int j= 0; j < 2; j++)
        {
			for(int x= 0; x < 2; x++)
			{
				t[i][j]+= ( a[i][x] * b[x][j] ) % 10007;
//				cout << a[i][x] << " + " << b[x][j] << " + ";
			}
//            cout << " = " << t[i][j] << endl;
        }
//    cout << endl;
}

void taoMang( long long a[2][2], vector<int> n)
{
//    coutT();
	if( n.empty() )
	{
		copyT( t, tg);
	}
	else if( n[ n.size() - 1 ] )
	{
		anhNhan(a, a);
		copyT( t, tg);
		anhNhan(tg, dv);
//		coutT(t);
		copyT(t, T);
		n.erase( n.end() - 1 );
		taoMang( T, n );
	}
	else
	{
		anhNhan(a, a);
//		coutT(t);
		copyT(t, T);
		n.erase( n.end() - 1 );
		taoMang( T, n );
	}
}

int main()
{
	long long a[2][2]= { {1, 1}, {1, 0} }, n, T;
	vector<int> nhiphan;

	cin >> n;
	n-= 2;
	if( n < 1 )
    {
        cout << 1 << endl;
    }
    else
    {
        while(n != 1)
        {
            nhiphan.push_back(n&1);
            n>>= 1;
        }
/*
        for(int i= 0; i < nhiphan.size(); i++) cout << nhiphan[i] << " ";
        cout << endl;
*/
    //	coutT();
        taoMang(a, nhiphan);

        T= ( tg[0][0] + tg[0][1] ) % (long long)(10e7);
        cout << T;
    }
}















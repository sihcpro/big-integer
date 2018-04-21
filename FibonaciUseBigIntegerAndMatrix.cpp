#include "bigInteger.h"

typedef long long ll;
typedef struct
{
	bigInteger a, b, c, d;
} Mt;

Mt mtdv;

Mt nhanMt( Mt a, Mt b)
{
	Mt kq;
	bigInteger a1= a.a*b.a, a2= a.b*b.c;
	kq.a= a1 + a2;
	bigInteger b1= a.a*b.b, b2= a.b*b.d;
	kq.b= b1 + b2;
	bigInteger c1= a.c*b.a, c2= a.d*b.c;
	kq.c= c1 + c2;
	bigInteger d1= a.c*b.b, d2= a.d*b.d;
	kq.d= d1 + d2;
	return kq;
}

Mt muMt(ll i)
{
	if( i == 1 )	return mtdv;
	else
	{
		Mt kq= muMt(i/2);
		kq= nhanMt( kq, kq);
		if( i%2 == 0 )
			return kq;
		else
			return nhanMt( kq, mtdv);
	}
}

bigInteger Fibonaci(ll n)
{
	if( n < 2 )	return bigInteger("1");
	
	mtdv.a= bigInteger("0");
	mtdv.b= bigInteger("1");
	mtdv.c= bigInteger("1");
	mtdv.d= bigInteger("1");
	
	Mt mtKQ= muMt(n-1);
	bigInteger kq= mtKQ.c + mtKQ.d;
	return kq;
}

ll n;

int main()
{
//while(4000)
{
	cout << "Ban muon tim so Fibonaci thu : ";
	cin >> n;
	
	bigInteger numFi;
	
	{
		numFi= Fibonaci(n-1);
		cout << numFi << endl;
	}
	
}
	return 0;
}


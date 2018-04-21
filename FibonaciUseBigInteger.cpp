#include "bigInteger.h""

int main()
{
	long long n;
	
//while(4000)
{
	bigInteger num1("1"), num2("1"), num3("1");
	cout << "Ban muon tim so Fibonaci thu : ";
	n= 4000;
	
	for(long long i= 2; i < n; i++)
	{
		num3= num1 + num2;

		if( i%2 == 0 )			//	Vi viec gan cham nen thay phien nhau gan de giam so phep gan
			num1= num3;
		else
			num2= num3;
			
//		cout << num3 << endl;
	}
	
	cout << num3 << endl;
}
	return 0;
}


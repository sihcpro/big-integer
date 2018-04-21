#include "BigInteger.h"



int main()
{
	bigInteger num1, num2, num3;
	cin >> num1 >> num2;

	cout << endl << "Tong cua 2 so la : ";
	num3 = num1 + num2;
	cout << num3 << endl;

	cout << endl << "Hieu cua 2 so la : ";
	num3 = num1 - num2;
	cout << num3 << endl;

	cout << endl << "Tich cua 2 so la : ";
	num3 = num1 * num2;
	cout << num3 << endl;

	cout << endl << "Thuong cua 2 so la : ";
	num3 = num1 / num2;
	cout << num3;
	num3(phanDu);
	cout << endl << "      Phan du bang: ";
	cout << num3 << endl;

/*
	cout << "So thu 1 lon hon so thu 2 la : ";
	if( num1 > num2 )	cout << "dung" << endl;
	else				cout << "sai"  << endl;

	cout << "So thu 1 be hon so thu 2 la : ";
	if( num1 < num2 )	cout << "dung" << endl;
	else				cout << "sai"  << endl;
*/

	return 0;
}




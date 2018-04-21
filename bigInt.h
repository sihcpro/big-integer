#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <fstream>
#include <string.h>

#define Max 1000
using namespace std;

/***************************** Struct Big Int ******************************/

const int maxLeng= Max+5;
typedef unsigned char bigNum[maxLeng];
typedef unsigned char *bigNumP;

class Num
{
	private:
		bigNum numInt;
		bool negative;
		int leng;
		
	public:
		Num(string= "0");
		~Num();
};
Num::Num(string num):negative(0), leng(0)
{
	for(int i= 0; i < num.length(); i++)
		numInt[i]= num[i];
}
Num::~Num()
{
}


typedef struct
{
	bigNumP num= new bigNum;
	bool negative= false;
	int leng= 0;
} bigInt;

static bigInt phanDu;

	bool operator > (const bigInt&, const bigInt&);
	bool operator < (const bigInt&, const bigInt&);
	bool operator == (const bigInt&, const bigInt&);
	bool operator >= (const bigInt&, const bigInt&);
	bool operator <= (const bigInt&, const bigInt&);

	bigInt operator + (const bigInt&, const bigInt&);
	bigInt operator - (const bigInt&, const bigInt&);
	bigInt operator * (const bigInt&, const bigInt&);
	bigInt operator / (const bigInt&, const bigInt&);

	int compSameLeng(const bigNum, const bigNum, const int);//	So sanh khi cung do dai, cung dau

	bigNumP mul10X(const bigNum, const int&, const int&);	//	Gap so do len 10 mu X lan
	bigNumP addNum(const bigNum, const bigNum, int&);		//	Cong khong xet dau
	bigNumP subNum(const bigNum, const bigNum, int&);		//  Tru  khong xet dau
	bigNumP mulNum(const bigInt&, const bigInt&, int&);		//	Nhan khong xet dau
	bigNumP divNum(const bigInt&, const bigInt&, int&);		//	Chia khong xet dau

	void print(const bigInt);
    void print(const bigNum, const int&);
	void print(const bigNum, const bigNum, const int&);
	void printMatrix(bigInt, bigInt);
    void printMulti(bigInt, bigInt);


bool operator > (const bigInt& num1, const bigInt& num2){
	if( num1.negative == num2.negative )					//	Ca 2 cung dau
	{
		if( num1.leng > num2.leng )								//	So thu 1 > so thu 2
			return !num1.negative;
		if( num1.leng < num2.leng )								//	So thu 2 > so thu 1
			return num1.negative;
	}
	else													//	Ca 2 khac dau
	{
		if( !num1.negative )									//	So thu 1 la so duong
			return true;
		else													//	So thu 1 la so am
			return false;
	}

	int daiBangNhau= compSameLeng(num1.num, num2.num, num1.leng);

	if( ( daiBangNhau ==  1 && !num1.negative ) ||
		( daiBangNhau == -1 &&  num1.negative )	   )			//	 num1 > num2
		return true;

	return false;
}
bool operator < (const bigInt& num1, const bigInt& num2){
	if( num1.negative == num2.negative )					//	Ca 2 cung dau
	{
		if( num1.leng < num2.leng )								//	So thu 1 > so thu 2
			return !num1.negative;
		if( num1.leng > num2.leng )								//	So thu 2 > so thu 1
			return num1.negative;
	}
	else													//	Ca 2 khac dau
	{
		if( !num1.negative )									//	So thu 1 la so duong
			return false;
		else													//	So thu 1 la so am
			return true;
	}

	int daiBangNhau= compSameLeng(num1.num, num2.num, num1.leng);

	if( ( daiBangNhau ==  1 &&  num1.negative ) ||
		( daiBangNhau == -1 && !num1.negative )	   )				//	 num1 < num2
		return true;

	return false;
}
bool operator == (const bigInt& num1, const bigInt& num2){
	if( num1.leng != num2.leng )	return false;

	int daiBangNhau= compSameLeng(num1.num, num2.num, num1.leng);
	if( daiBangNhau == 0 )			return true;				//	num1 = num2

	return false;
}
bool operator >= (const bigInt& num1, const bigInt& num2){
	return !( num1 < num2 );
}
bool operator <= (const bigInt& num1, const bigInt& num2){
	return !( num1 > num2 );
}







bigInt operator + (const bigInt& num1, const bigInt& num2){
	bigInt num3;

	if( num1.negative == num2.negative )						//	Ca 2 so cung dau
	{
		num3.negative= num1.negative;
		num3.leng= max(num1.leng, num2.leng);
		num3.num= addNum(num1.num, num2.num, num3.leng);
	}
	else														//	2 so khac dau
	{
		num3.leng= max(num1.leng, num2.leng);
		int daiBangNhau= compSameLeng( num1.num, num2.num, num3.leng);
		if( daiBangNhau == 1 )
		{
			num3.negative= num1.negative;						//	Bang dau cua so lon hon
			num3.num= subNum(num1.num, num2.num, num3.leng);
		}
		else
		{
			num3.negative= num2.negative&&daiBangNhau;			//	Khi 1 + -1 thi daiBangNhau=0 se ra 0
			num3.num= subNum(num2.num, num1.num, num3.leng);	//	duong chu khong phai ra so 0 am
		}
	}

	return num3;
}
bigInt operator - (const bigInt& num1, const bigInt& num2){
	bigInt num3= num2;
	num3.negative= !num3.negative;
	return num1+num3;
}
bigInt operator * (const bigInt& num1, const bigInt& num2){
	if( num1.leng < num2.leng )		return num2 * num1;			//	De cho so 1 luon dai hon so 2
/*
	print(num1);
	print(num2);
	printMulti(num1, num2);
*/
	bigInt num3;

	if( num1.negative == num2.negative )	num3.negative= false;
	else									num3.negative= true;

	num3.num= mulNum(num1, num2, num3.leng);

	return num3;
}
bigInt operator / (const bigInt& num1, const bigInt& num2){
    bigInt num3;

    if( num2.leng == 1 && num2.num[0] == 0 )
	{
		cout << "vo cung";
		return num3;
	}
	num3.leng= max(num1.leng - num2.leng +1, 1);
	if( num1.leng < num2.leng )
	{
		phanDu= num1;
		return num3;
	}

	if( num1.negative == num2.negative )	num3.negative= false;
	else									num3.negative= true;

	num3.num= divNum( num1, num2, num3.leng);

	return num3;
}





int compSameLeng(const bigNum num1, const bigNum num2, const int leng){	//  1 la lon, 0 la bang, -1 be
	for(int i= leng-1 ; i >= 0; i--)
	{
			 if( num1[i] > num2[i] )		return 1;
		else if( num1[i] < num2[i] )		return -1;
	}
	return 0;
}



bigNumP copyNum(const bigNum num){
	bigNumP newNum= new bigNum;
	for(int i= 0; i < maxLeng; i++)		newNum[i]= num[i];

	return newNum;
}
bigNumP mul10X(const bigNum num, const int& leng, const int& x10){
	bigNumP newNum= copyNum(num);
	for(int i= leng - 1; i >= 0; i--)
        newNum[i+x10]= num[i];
	for(int i= x10-1; i >= 0; i--)
        newNum[i]= 0;

	return newNum;
}
bigNumP addNum(const bigNum num1, const bigNum num2, int& leng){
	bigNumP num3= new bigNum;
	int c= 0;

	for(int i= 0, S= 0; i < leng; i++)
	{
		S= num1[i] + num2[i] + c;
//		printf("%d + %d + %d = %d\n", num1[i], num2[i], c, S);
		num3[i]= S%10;
		c= S/10;
	}

	if( c )														 //  if vi 2 so cong toi da < 100
	{
		num3[leng]= c;
		leng++;
	}
	while( num3[leng-1] == 0 && leng > 1 )	leng--;

	return num3;
}
bigNumP subNum(const bigNum num1, const bigNum num2, int& leng){
	bigNumP num3= new bigNum;
	int c= 0;

	for(int i= 0, S= 0; i < leng; i++)
	{
		S= num1[i] - num2[i] + c;
		c= 0;
		if( S < 0 )
		{
			S+= 10;
			c--;
		}
		num3[i]= S;
	}
	while( num3[leng-1] == 0 && leng > 1 )	leng--;

	return num3;
}

bigNumP mulNum(const bigInt &num1, const bigInt &num2, int &leng)
{
	bigNumP num3= new bigNum;							//  Doi voi mang phai tra ve con tro
	int c= 0, S;										//	c la co nho, S la tong cheo

	for(; leng < num1.leng; leng++)						//	Ngoai tru phan tam giac phia duoi
	{
		S= c;
		for(int j= 0; j <= min(leng, num2.leng-1); j++)
		{
//			printf("%4d + ",num1.num[leng-j]*num2.num[j]);
			S+= num1.num[leng-j]*num2.num[j];
		}
//		cout << " = " << S << endl;
		num3[leng]= S%10;
		c= S/10;
	}

	for(; leng < num1.leng+num2.leng; leng++)		   //  Nhan luon phan tam giac phia duoi
	{
		S= c;
		for(int j= leng-num1.leng+1; j < num2.leng; j++)
		{
//			printf("%4d + ",num1.num[leng-j]*num2.num[j]);
			S+= num1.num[leng-j]*num2.num[j];
		}
//		cout << " = " << S << endl;
		num3[leng]= S%10;
		c= S/10;
	}

	while( c )											//	Bien nho van con
	{
		num3[leng]= c%10;
		leng++;
		c= c/10;
	}
	while( num3[leng-1] == 0 && leng > 1 )	leng--;	 	//  Xoa so 0 du
	leng= max(1, leng);

	return num3;
}

bigNumP divNum(const bigInt &num1, const bigInt &num2, int &leng){
	bigNumP num3= new bigNum;
	bigNumP numDiv= new bigNum;
	bigNumP num1New= copyNum(num1.num);

	for(int i= num1.leng, c= 0; i >= num2.leng; i--)
    {
		c= 0;
		numDiv= mul10X( num2.num, num2.leng, i-num2.leng);
//		print( num1New, numDiv, i+1);
		while( compSameLeng( num1New, numDiv, i+1) != -1 )
		{
		    int i2= i+1;
			num1New= subNum( num1New, numDiv, i2);
			c++;
		}
//		cout << " = " << c << endl << endl;
		num3[i-num2.leng]= c;
    }
	phanDu.num= copyNum(num1New);
	phanDu.leng= num2.leng;

	return num3;
}










/*********************************** Class Big Integer **********************************/

class bigInteger
{
	private:
		bigInt num;
		void readyNum();

	public:
		bigInteger();
		bigInteger(string);
		bigInteger(bigInt);
		bigInteger(bigInt&);

		bigInt thisNum();

		istream& operator >> (istream&);

		bool operator > (bigInteger&);
		bool operator < (bigInteger&);
		bool operator == (bigInteger&);
		bool operator >= (bigInteger&);
		bool operator <= (bigInteger&);

		bigInteger operator + (bigInteger&);
		bigInteger operator - (bigInteger&);
		bigInteger operator * (bigInteger&);
		bigInteger operator / (bigInteger&);
		bigInteger operator () (bigInt&);

		void printNum();
};

void bigInteger::readyNum(){
	for(int i= this->num.leng; i < maxLeng; i++)	this->num.num[i]= 0;
//	this->num.leng++;
	while( num.num[this->num.leng-1] == 0 && num.leng > 1 )	this->num.leng--;//  Xoa so 0 du
}

bigInteger::bigInteger(){
	bigInteger newNum= bigInteger("0");
	this->num= newNum.thisNum();
	readyNum();
}
bigInteger::bigInteger(bigInt num){
	this->num= num;
	readyNum();
}
bigInteger::bigInteger(string num){
	this->num.leng= num.length();
	if( num[0] == '-' )										//	Xet so am hay duong
	{
		this->num.negative= true;
		this->num.leng--;									//	Khong doc dau am
	}
	for(int i=0; i < this->num.leng; i++)
	{
		this->num.num[i]= num[num.length() - i - 1]-'0';	//	dang doc chu phai tru moi ra so
	}
	readyNum();
}


bool bigInteger::operator > (bigInteger& num2){
	return this->thisNum() > num2.thisNum();
}
bool bigInteger::operator < (bigInteger& num2){
	return this->thisNum() < num2.thisNum();
}
bool bigInteger::operator == (bigInteger& num2){
	return this->thisNum() == num2.thisNum();
}
bool bigInteger::operator >= (bigInteger& num2){
	return this->thisNum() >= num2.thisNum();
}
bool bigInteger::operator <= (bigInteger& num2){
	return this->thisNum() <= num2.thisNum();
}


bigInteger bigInteger::operator + (bigInteger& num2){
	return bigInteger(this->thisNum() + num2.thisNum());		//  Su dung dau cong cua bigInt
}
bigInteger bigInteger::operator - (bigInteger& num2){
	return bigInteger(this->thisNum() - num2.thisNum());		//  Su dung dau tru  cua bigInt
}
bigInteger bigInteger::operator * ( bigInteger& num2 ){
	return bigInteger(this->thisNum() * num2.thisNum());		//  Su dung dau nhan cua bigInt
}
bigInteger bigInteger::operator / ( bigInteger& num2 ){
	return bigInteger(this->thisNum() / num2.thisNum());		//  Su dung dau chia cua bigInt
}
bigInteger bigInteger::operator () (bigInt& newNum)
{
	num.num= copyNum(newNum.num);
	num.leng= newNum.leng;
	num.negative= newNum.negative;
	readyNum();
	return *this;
}


bigInt bigInteger::thisNum(){
	return num;
}
void bigInteger::printNum(){
	if( this->num.negative )	cout << "So am ";
	else						cout << "So duong ";
	for(int i= this->num.leng; i > 0; i--)
		printf("%i",this->num.num[i-1]);
	cout << endl;
}










/********************************** I/O ******************************/

bool checkIn(string number){
	unsigned int i= 0;
	if( number[i] == '-' )		i++;
	for(; i < number.length(); i++)
		if( number[i] < '0' || number[i] > '9' )	return false;
	return true;
}
istream& operator >> (istream &in, bigInteger& num){
	cout << "Nhap vao 1 so tu nhien : ";
	string number;
	in >> number;
	if( !checkIn(number) )
	{
		cout << "Ban vua nhap sai! Moi nhap lai!" << endl;
		in >> num;
	}
	else
        num= bigInteger(number);
	return in;
}
ostream& operator << (ostream &out, bigInteger& num)
{
	if( num.thisNum().negative )	cout << "-";
	print( num.thisNum().num, num.thisNum().leng );
    return out;
}








/********************************* Print Debug ********************************/

void print(const bigInt num){
	if( num.negative )				cout << "So am ";
	else							cout << "So duong ";
	for(int i= num.leng-1; i >= 0; i--)printf("%i",num.num[i]);
									cout << endl;
}
void print(const bigNum num, const int& leng){
	if( leng == 0 )						return;
	if( num[leng-1] != 0 || leng == 1)	printf("%i",num[leng-1]);
	for(int i= leng-2; i >= 0; i--)		printf("%i",num[i]);
}
void print(const bigNum num1, const bigNum num2, const int& leng){	//	Chi dung cho phep chia
	print(num1, leng);
	cout << " / ";
	print(num2, leng);
}

void printMulti(bigInt num1, bigInt num2)
{
	for(int i= -1; i < num1.leng; i++)
	{
		if( i == -1 )
		{
			printf("    ");
			for(int j= 0; j < num2.leng; j++)
				printf("%4d", num2.num[j]);
			cout << endl;
		}
		else
		{
			printf("%4d",num1.num[i]);
			for(int j= 0; j < num2.leng; j++)
				printf("%4d", num1.num[i]*num2.num[j]);
			cout << endl;
		}
	}
}






#endif // BIGINT_H

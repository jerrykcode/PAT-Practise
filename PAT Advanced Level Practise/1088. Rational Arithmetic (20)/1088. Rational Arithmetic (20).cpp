// 1088. Rational Arithmetic (20).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>

long long int gcd(long long int a, long long int b)
{
	return a == 0 ? abs(b) : gcd(b%a, a);
}

string fraction(long long int a, long long int b)
{
	if (b == 0) return "Inf";
	if (a == 0) return "0";
	string result = "";
	if (a < 0)result += "(";
	long long int integer = a / b;
	if (integer != 0) {
		result += to_string(integer);
		a -= b * integer;
		if (a != 0) result += " ";
		if (integer < 0 && a < 0) a *= -1;
	}
	if (a != 0) {
		result += to_string(a);
		if (b != 1)result += "/" + to_string(b);
	}
	if (a < 0 || integer < 0) result += ")";
	return result;
}

int main()
{
	long long int a1, b1, a2, b2;
	scanf("%lld/%lld %lld/%lld", &a1, &b1, &a2, &b2);
	long long int g = gcd(a1, b1);
	a1 /= g;
	b1 /= g;
	g = gcd(a2, b2);
	a2 /= g;
	b2 /= g;
	long long int a = a1 * b2 + a2 * b1;
	long long int b = b1 * b2;
	g = gcd(a, b);
	a /= g;
	b /= g;
	cout << fraction(a1, b1) << " + " << fraction(a2, b2) << " = " << fraction(a, b) << endl;
	a = a1 * b2 - a2 * b1;
	b = b1 * b2;
	g = gcd(a, b);
	a /= g;
	b /= g;
	cout << fraction(a1, b1) << " - " << fraction(a2, b2) << " = " << fraction(a, b) << endl;
	a = a1 * a2;
	b = b1 * b2;
	g = gcd(a, b);
	a /= g;
	b /= g;
	cout << fraction(a1, b1) << " * " << fraction(a2, b2) << " = " << fraction(a, b) << endl;
	a = a1 * b2 ;
	b = b1 * a2;
	if (b < 0) {
		b *= -1;
		a *= -1;
	}
	g = gcd(a, b);
	a /= g;
	b /= g;
	cout << fraction(a1, b1) << " / " << fraction(a2, b2) << " = " << fraction(a, b) << endl;
    return 0;
}


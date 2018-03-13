#include <iostream>
using namespace std;
#include <string>
#include <math.h>

int toInt(char c)
{
	if (isdigit(c)) return c - '0';
	return c - 'a' + 10;
}

long long toDec(string number, long long radix)
{
	long long result = 0;
	for (int i = 0; i < number.length(); i++)
		result += toInt(number[number.length() - i - 1])*pow(radix, i);
	return result;
}

long long max(long long a, long long b)
{
	return a > b ? a : b;
}

long long binarySearch(long long low, long long high, string n, long long a)
{
	while (low <= high) {
		long long mid = (low + high) / 2;
		long long value = toDec(n, mid);
		if (value < 0) high = mid - 1;
		else if (value < a) low = mid + 1;
		else if (value == a) return mid;
		else high = mid - 1;
	}
	return -1;
}

int main()
{
	string n1, n2;
	int tag, radix;
	cin >> n1 >> n2 >> tag >> radix;
	if (tag == 2) swap(n1, n2);
	long long a = toDec(n1, radix);
	int maxDigit = 0;
	for (int i = 0; i < n2.length(); i++) {
		if (toInt(n2[i]) > maxDigit)
			maxDigit = toInt(n2[i]);
	}
	long long low = maxDigit + 1;
	long long high = max(low, a) + 1;
	long long r = binarySearch(low, high, n2, a);
	if (r == -1) cout << "Impossible";
	else printf("%lld", r);
	return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include<stdlib.h>
using namespace std;

string alter(string message, int reversed_bit)
{
	cout << "Reversed bit = ";
	cin >> reversed_bit;
	if (reversed_bit != 0)
	{
		if (message[reversed_bit] == '0')
			message[reversed_bit] = '1';
		else
			message[reversed_bit] = '0';
	}
	else
	{

		cout << "0 is not accepted" << endl;
		message = alter(message, reversed_bit);
	}

	return message;

}

char Xor(char a, char b)
{
	if ((a == '0'&& b == '0') || (a == '1'&& b == '1'))
		return '0';
	else
		return '1';
}




string Remainder(string message, string crc)
{
	string remainder;
	int m = message.length();
	int n = crc.length();
	remainder += message;
	for (int i = 1; i <= n - 1; i++)
		remainder += '0';
	for (int i = 0; i <= remainder.length() - n; )
	{
		for (int j = 0; j<n; j++)
			remainder[i + j] = remainder[i + j] == crc[j] ? '0' : '1';
		while (i<remainder.length() && remainder[i] != '1')
			i++;
	}
	remainder = remainder.substr(remainder.length() - n + 1);

	return message + remainder;
}
string Generator(string message, string crc)
{
	string remainder1 = Remainder(message, crc);
	message += remainder1;
	return message;
}
void verifier(string msg, string y)
{
	string x = Remainder(msg, y);
	int flag = 0;
	for (int i = 0; i<x.length(); i++)
	{
		if (x[i] != '0')
		{
			flag++;

		}

	}
	if (flag>0)
		cout << "Error" << endl;
	else
		cout << "Message correct" << endl;

}
int main()
{
	string line;
	string message = "";
	string y = "";
	string mmin = "10101";
	string x = "";
	int bit = 0;
	ifstream myfile("in.txt");
	if (myfile.is_open())
	{
		getline(myfile, line);
		message = line;
		getline(myfile, line);
		y = line;
		myfile.close();
	}
	string test = Generator(message, y);
	x = alter(test, bit);

	verifier(x, y);

	system("pause");
	return 0;
}
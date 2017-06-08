// hamming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

string decimalToBinary(int n);
string toHammingFormat(string binaryNum);
string toHammingCode(int num, bool isEvenParity);
string correctDataBitsLength(string str);
bool numOfOnesIsEven(int parityBitIndex, string hammingCodedString);

int main()
{
	int num = -1;

	cout << "Number to Hamming code: ";
	cin >> num;

	cout << toHammingCode(num, true) << endl << endl;

	system("PAUSE");
	return 0;
}


string toHammingCode(int num, bool isEvenParity)
{
	bool evenParityBitCoding = isEvenParity;
	int parityBitIndex = 1;

	string hammingCodedString = toHammingFormat(decimalToBinary(num));

	while (parityBitIndex < hammingCodedString.length())
	{
		bool numOfOnesBool = numOfOnesIsEven(parityBitIndex, hammingCodedString);

		if (evenParityBitCoding)
		{
			if (numOfOnesBool)
			{
				hammingCodedString[parityBitIndex - 1] = '0';
			}
			else
			{
				hammingCodedString[parityBitIndex - 1] = '1';
			}

		}
		else
		{
			if (numOfOnesBool)
			{
				hammingCodedString[parityBitIndex - 1] = '1';
			}
			else
			{
				hammingCodedString[parityBitIndex - 1] = '0';
			}
		}

		parityBitIndex *= 2;
	}

	return hammingCodedString;
}

bool numOfOnesIsEven(int parityBitIndex, string hammingCodedString)
{
	int hammingCodeIndex = parityBitIndex - 1;
	int numberOfOnes = 0;

	while (hammingCodeIndex < hammingCodedString.length())
	{
		for (int i = 0; i < parityBitIndex; i++)
		{
			if (hammingCodeIndex + i >= hammingCodedString.length())
			{
				break;
			}

			if (hammingCodedString[hammingCodeIndex + i] == '1')
			{
				numberOfOnes++;
			}
		}

		hammingCodeIndex += 2 * parityBitIndex;
	}

	if (numberOfOnes % 2 == 0)
	{
		return true;
	}

	return false;
}

string toHammingFormat(string binaryNum)
{
	string hammingFormat;
	int nextPowIndex = 1;

	while (binaryNum.length() > 0)
	{
		if (hammingFormat.length() + 1 == nextPowIndex)
		{
			nextPowIndex *= 2;
			hammingFormat.push_back('_');
		}
		else
		{
			hammingFormat.push_back(binaryNum[0]);
			binaryNum.erase(0, 1);
		}
	}


	return hammingFormat;
}

string decimalToBinary(int n)
{
	string r;

	if (n == 0)
	{
		r = "0";
	}

	while (n != 0)
	{
		r = (n % 2 == 0 ? "0" : "1") + r;
		n /= 2;
	}

	return correctDataBitsLength(r);
}

string correctDataBitsLength(string str)
{
	int parityBits = 2;
	int dataBits = 0;

	while(true)
	{
		parityBits++;
		dataBits = pow(2, parityBits) - parityBits - 1;

		if (str.length() <= dataBits)
		{
			break;
		}
	}

	if (str.length() % dataBits > 0)
	{
		str = string(dataBits - (str.length() % dataBits), '0') + str;
	}
	
	return str;
}

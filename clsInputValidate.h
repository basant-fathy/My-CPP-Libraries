#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "clsString.h"
#include "clsDate.h"

class clsInputValidate
{
public:

	static bool IsNumberBetween(short Number, short From, short To) {
		return (Number >= From && Number <= To);
	}
	static bool IsNumberBetween(int Number, int From, int To) {
		return (Number >= From && Number <= To);
	}
	static bool IsNumberBetween(float Number, float From, float To) {
		return (Number >= From && Number <= To);
	}
	static bool IsNumberBetween(double Number, double From, double To) {
		return (Number >= From && Number <= To);
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To) {
		if (clsDate::IsDate1AfterDate2(From, To)) {
			clsDate::SwapDates(From, To);
		}
		return (Date.IsDate1AfterDate2(From) && Date.IsDate1BeforeDate2(To));
	}
	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To, bool IncludingEndDay) {
		if (IncludingEndDay)
			return (Date.IsDate1AfterDate2(From) && (Date.IsDate1BeforeDate2(To) || Date.IsDate1EqualsDate2(To)));
		return (Date.IsDate1AfterDate2(From) && Date.IsDate1BeforeDate2(To));
	}

	static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		short Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}


	static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		short Number = ReadShortNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadShortNumber();
		}
		return Number;
	}


	static int ReadIntNumber(string ErrorMessage = "Invalid number, Enter again!\n") {
		int Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}
	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Invalid number, Enter again!\n") {
		int Number = ReadIntNumber();
		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadIntNumber();
		}
		return Number;
	}

	static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		float Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}
	static float ReadFloatNumberBetween(float From, float To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		float Number = ReadFloatNumber();

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadFloatNumber();
		}
		return Number;
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid number, Enter again!\n") {
		double Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}
	static double ReadDNumberBetween(double From, double To, string ErrorMessage = "Invalid number, Enter again!\n") {
		double Number;
		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadDblNumber();
		};
		return Number;
	}

	static bool IsValideDate(clsDate Date) {
		return Date.IsValid();
	}

	static string ReadString()
	{
		string  S1 = "";
		// Usage of std::ws will extract allthe whitespace character
		getline(cin >> ws, S1);
		return S1;
	}

};


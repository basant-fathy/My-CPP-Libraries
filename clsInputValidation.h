#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "clsString.h"
#include "clsDate.h"

class clsInputValidate
{
public:
	template <typename T>
	static bool IsNumberBetween(T Number, T From, T To) {
		return (Number >= From && Number <= To);
	}

	static T ReadtNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		short Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static T ReadNumberBetween(T From, T To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		short Number = ReadShortNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadShortNumber();
		}
		return Number;
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


#pragma warning (disable:4996)
#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "clsString.h"
#include <vector>
using namespace std;

class clsDate
{
private:
	short _Year, _Month, _Day;
public:
	static clsDate GetSystemDate()
	{
		clsDate Date;

		std::time_t t = std::time(nullptr);
		std::tm now{};

		localtime_s(&now, &t);

		Date._Year = now.tm_year + 1900;
		Date._Month = now.tm_mon + 1;
		Date._Day = now.tm_mday;

		return Date;
	}

	static string GetSystemDateTimeString() {
		std::time_t t = std::time(nullptr);
		std::tm now{};

		localtime_s(&now, &t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now.tm_year + 1900;
		Month = now.tm_mon + 1;
		Day = now.tm_mday;
		Hour = now.tm_hour;
		Minute = now.tm_min;
		Second = now.tm_sec;

		return (to_string(Day) + "/"
			+ to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second));
	}

	clsDate() {
		std::time_t t = std::time(nullptr);
		std::tm now{};

		localtime_s(&now, &t);

		_Year = now.tm_year + 1900;
		_Month = now.tm_mon + 1;
		_Day = now.tm_mday;

	}
	clsDate(string Date_string) {
		vector <string> vDate;

		vDate = clsString::Split(Date_string, "/");

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}
	clsDate(short Day, short Month, short Year) {
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	clsDate(short DaysOrderInYear, short Year) {
		clsDate Date1
			= GetDateFromDayOrderInYear(DaysOrderInYear, Year);
		_Day = Date1._Day;
		_Month = Date1._Month;
		_Year = Date1._Year;
	}

	void SetDay(short Day) {
		_Day = Day;
	}
	short GetDay() {
		return _Day;
	}
	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month) {
		_Month = Month;
	}
	short GetMonth() {
		return _Month;
	}
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year) {
		_Year = Year;
	}
	short GetYear() {
		return _Year;
	}
	__declspec(property(get = GetYear, put = SetYear)) short Year;

	static clsDate StringToDate(string Date_string) {
		clsDate Date;
		vector <string> vDate;

		vDate = clsString::Split(Date_string, "/");

		if (vDate.size() != 3) {
			cout << "Invalid date format!\n";
			return { 0,0,0 };
		}

		Date._Day = stoi(vDate[0]);
		Date._Month = stoi(vDate[1]);
		Date._Year = stoi(vDate[2]);

		return Date;
	}

	static string DateToString(clsDate Date) {
		return to_string(Date._Day)
			+ "/" + to_string(Date._Month)
			+ "/" + to_string(Date._Year);

	}

	static bool IsLeapYear(int Year) {
		return (Year % 4 == 0 && Year % 100 != 0 || Year % 400 == 0);
	}
	bool IsLeapYear() {
		return IsLeapYear(_Year);
	}

	static short NumberOfDaysInAMonth(short Month, int Year) {
		if (Month < 1 || Month>12)
			return 0;

		int NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];

	}
	short NumberOfDaysInAMonth() {
		return NumberOfDaysInAMonth(_Month, _Year);
	}

	static short NumberOfDaysInYear(short Year) {
		return (IsLeapYear(Year)) ? 366 : 365;
	}
	short NumberOfDaysInYear() {
		return NumberOfDaysInYear(_Year);
	}

	static short NumberOfDaysFromBeginnigOfTheYear(short Day, short Month, short Year) {
		short TotalDays = 0;
		for (short i = 1; i < Month; i++) {
			TotalDays += NumberOfDaysInAMonth(i, Year);
		}
		TotalDays += Day;

		return TotalDays;
	}
	static short NumberOfDaysFromBeginnigOfTheYear(clsDate Date) {
		return NumberOfDaysFromBeginnigOfTheYear(Date._Day, Date._Month, Date._Year);
	}
	short NumberOfDaysFromBeginnigOfTheYear() {
		return NumberOfDaysFromBeginnigOfTheYear(*this);
	}

	static short NumberOfHoursInAYear(short Year)
	{
		return NumberOfDaysInYear(Year) * 24;
	}
	short NumberOfHoursInAYear()
	{
		return NumberOfHoursInAYear(_Year);
	}

	static int NumberOfMinutesInAYear(short Year)
	{
		return NumberOfHoursInAYear(Year) * 60;
	}
	int NumberOfMinutesInAYear()
	{
		return NumberOfMinutesInAYear(_Year);
	}

	static int NumberOfSecondsInAYear(short Year)
	{
		return NumberOfMinutesInAYear(Year) * 60;
	}
	int NumberOfSecondsInAYear()
	{
		return NumberOfSecondsInAYear(_Year);
	}

	static clsDate GetDateFromDayOrderInYear(short DaysOrderInYear, short Year) {
		clsDate Date;
		short RemaingDays = DaysOrderInYear;
		short MonthDays = 0;

		Date._Year = Year;
		Date._Month = 1;

		while (true) {
			MonthDays = NumberOfDaysInAMonth(Date._Month, Year);

			if (RemaingDays > MonthDays) {
				RemaingDays -= MonthDays;
				Date._Month++;
			}
			else
			{
				Date._Day = RemaingDays;
				break;
			}

		}

		return Date;
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static short ReadYear() {
		short Year;
		cout << "Enter a Year? ";
		cin >> Year;

		return Year;
	}
	static short ReadMonth() {
		short Month;
		cout << "Enter a Month? ";
		cin >> Month;

		return Month;
	}
	static short ReadDay() {
		short Day;
		cout << "\nEnter a Day? ";
		cin >> Day;

		return Day;
	}
	static clsDate ReadFullDate() {
		clsDate Date;
		Date._Day = ReadDay();
		Date._Month = ReadMonth();
		Date._Year = ReadYear();

		return Date;
	}
	static string ReadStringDate() {
		string S1;

		cout << "Enter Date dd/mm/yyyy? ";
		getline(cin, S1);

		return S1;
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2) {
		if (Date1._Year != Date2._Year)
			return (Date1._Year < Date2._Year);
		else if (Date1._Month != Date2._Month)
			return (Date1._Month < Date2._Month);

		return (Date1._Day < Date2._Day);
	}
	bool IsDate1BeforeDate2(clsDate Date2) {
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualsDate2(clsDate Date1, clsDate Date2) {
		return Date1._Year == Date2._Year &&
			Date1._Month == Date2._Month &&
			Date1._Day == Date2._Day;
	}
	bool IsDate1EqualsDate2(clsDate Date2) {
		return IsDate1EqualsDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2) {
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualsDate2(Date1, Date2));
	}
	bool IsDate1AfterDate2(clsDate Date2) {
		return IsDate1AfterDate2(*this, Date2);
	}

	void Print() {
		cout << _Day << "/" << _Month << "/" << _Year << endl;
	}

	static short DayOfWeekOrder(short Day, short Month, short Year) {
		short a = (14 - Month) / 12;
		short y = Year - a;
		short m = Month + (12 * a) - 2;

		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

	}
	static short DayOfWeekOrder(clsDate Date) {
		return DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
	}
	short DayOfWeekOrder() {
		return DayOfWeekOrder(*this);
	}

	static string DayShortName(short DayOfWeekOrder) {
		string arrNameDay[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrNameDay[DayOfWeekOrder];
	}
	string DayShortName() {
		return DayShortName(DayOfWeekOrder());
	}

	static string MonthShortName(short Month) {
		string arrNameDay[] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };

		return arrNameDay[Month - 1];
	}
	string MonthShortName() {
		return MonthShortName(_Month);
	}

	static void PrintMonthCalendar(short Month, short Year) {

		int NumberOfDays = NumberOfDaysInAMonth(Month, Year);

		int current = DayOfWeekOrder(1, Month, Year);

		printf("\n  _______________%s_______________\n\n", MonthShortName(Month).c_str());
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
		short i;
		for (i = 0; i < current; i++)
			printf("     ");

		for (int j = 1; j <= NumberOfDays; j++) {
			printf("%5d", j);

			if (++i == 7) {
				i = 0;
				printf("\n");
			}
		}

		printf("\n  _________________________________\n");
	}
	void PrintMonthCalendar() {
		PrintMonthCalendar(_Month, _Year);
	}

	static void PrintYearCalendar(short Year) {
		cout << "\n  _________________________________\n";
		cout << "          Calendar - " << Year;
		cout << "\n  _________________________________\n";
		for (int i = 1; i <= 12; i++) {
			PrintMonthCalendar(i, Year);
			cout << endl;
		}
	}
	void PrintYearCalendar() {
		PrintYearCalendar(_Year);
	}

	static clsDate DateAddDays(short Days, clsDate Date) {

		short RemaingDays = Days + NumberOfDaysFromBeginnigOfTheYear(Date._Day, Date._Month, Date._Year);
		short MonthDays = 0;

		Date._Month = 1;

		while (true) {
			MonthDays = NumberOfDaysInAMonth(Date._Month, Date._Year);

			if (RemaingDays > MonthDays)
			{
				RemaingDays -= MonthDays;
				Date._Month++;

				if (Date._Month > 12)
				{
					Date._Year++;
					Date._Month = 1;

				}
			}
			else
			{
				Date._Day = RemaingDays;
				break;
			}

		}

		return Date;
	}
	void AddDays(short Days) {
		*this = DateAddDays(Days, *this);
	}

	static bool IsLastMonthInYear(short Month) {
		return Month == 12;
	}
	bool IsLastMonthInYear() {
		return IsLastMonthInYear(_Month);
	}

	static bool IsLastDayInMonth(clsDate Date) {
		return Date._Day == NumberOfDaysInAMonth(Date._Month, Date._Year);
	}
	bool IsLastDayInMonth() {
		return IsLastDayInMonth(*this);
	}

	static clsDate IncreaseOneDay(clsDate Date) {
		if (IsLastDayInMonth(Date)) {
			if (IsLastMonthInYear(Date._Month)) {
				Date._Month = 1;
				Date._Day = 1;
				Date._Year++;
			}
			else
			{
				Date._Day = 1;
				Date._Month++;
			}
		}
		else
			Date._Day++;

		return Date;
	}
	void IncreaseOneDay() {
		*this = IncreaseOneDay(*this);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;

		TempDate._Year = Date1._Year;
		TempDate._Month = Date1._Month;
		TempDate._Day = Date1._Day;

		Date1._Year = Date2._Year;
		Date1._Month = Date2._Month;
		Date1._Day = Date2._Day;

		Date2._Year = TempDate._Year;
		Date2._Month = TempDate._Month;
		Date2._Day = TempDate._Day;
	}

	static short GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludingEndDay = false) {
		int Days = 0;
		short SawpFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2)) {
			SwapDates(Date1, Date2);
			SawpFlagValue = -1;
		}
		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseOneDay(Date1);
		}
		return IncludingEndDay ? (Days + 1) * SawpFlagValue : Days * SawpFlagValue;
	}
	short GetDifferenceInDays(clsDate Date2) {
		return GetDifferenceInDays(*this, Date2);
	}

	static short AgeInDays(clsDate DateOfBirth) {
		return GetDifferenceInDays(DateOfBirth, GetSystemDate());
	}

	static clsDate Increase_X_Days(short X, clsDate Date) {
		for (short i = 1; i <= X; i++) {
			Date = IncreaseOneDay(Date);
		}
		return Date;
	}
	void Increase_X_Days(short X) {
		*this = Increase_X_Days(X, *this);
	}

	static clsDate IncreaseOneWeek(clsDate Date) {
		for (short i = 1; i <= 7; i++) {
			Date = IncreaseOneDay(Date);
		}
		return Date;
	}
	void IncreaseOneWeek() {
		*this = IncreaseOneWeek(*this);
	}

	static clsDate Increase_X_Weeks(short X, clsDate Date) {
		for (short i = 1; i <= X; i++) {
			Date = IncreaseOneWeek(Date);
		}
		return Date;
	}
	void Increase_X_Weeks(short X) {
		*this = Increase_X_Weeks(X, *this);
	}

	static clsDate IncreaseOneMonth(clsDate Date) {
		if (IsLastMonthInYear(Date._Month)) {
			Date._Month = 1;
			Date._Year++;
		}
		else
		{
			Date._Month++;
		}

		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
		if (Date._Day > NumberOfDaysInCurrentMonth)
			Date._Day = NumberOfDaysInCurrentMonth;

		return Date;
	}
	void IncreaseOneMonth() {
		*this = IncreaseOneMonth(*this);
	}

	static clsDate Increase_X_Months(short X, clsDate Date) {
		for (short i = 1; i <= X; i++) {
			Date = IncreaseOneMonth(Date);
		}
		return Date;
	}
	void Increase_X_Months(short X) {
		*this = Increase_X_Months(X, *this);
	}

	static clsDate IncreaseOneYear(clsDate Date) {
		Date._Year++;
		return Date;
	}
	void IncreaseOneYear() {
		*this = IncreaseOneYear(*this);
	}

	static clsDate Increase_X_Years(short X, clsDate Date) {
		Date._Year += X;
		return Date;
	}
	void Increase_X_Years(short X) {
		*this = Increase_X_Years(X, *this);
	}

	static clsDate IncreaseOneDecade(clsDate Date) {
		Date._Year += 10;
		return Date;
	}
	void IncreaseOneDecade() {
		*this = IncreaseOneDecade(*this);
	}

	static clsDate Increase_X_Decades(short X, clsDate Date) {
		Date._Year += (X * 10);
		return Date;
	}
	void Increase_X_Decades(short X) {
		*this = Increase_X_Decades(X, *this);
	}

	static clsDate IncreaseOneCentury(clsDate Date) {
		Date._Year += 100;
		return Date;
	}
	void IncreaseOneCentury() {
		*this = IncreaseOneCentury(*this);
	}

	static clsDate IncreaseOneMillennium(clsDate Date) {
		Date._Year += 1000;
		return Date;
	}
	void IncreaseOneMillennium() {
		*this = IncreaseOneMillennium(*this);
	}

	static clsDate DecreaseOneDay(clsDate Date) {
		if (Date._Day == 1) {
			if (Date._Month == 1) {
				Date._Year--;
				Date._Month = 12;
				Date._Day = 31;
			}
			else {
				Date._Month--;
				Date._Day = NumberOfDaysInAMonth(Date._Month, Date._Year);
			}
		}
		else
			Date._Day--;

		return Date;
	}
	void DecreaseOneDay() {
		*this = DecreaseOneDay(*this);
	}

	static clsDate Decrease_X_Days(short X, clsDate Date) {
		for (short i = 1; i <= X; i++) {
			Date = DecreaseOneDay(Date);
		}
		return Date;
	}
	void Decrease_X_Days(short X) {
		*this = Decrease_X_Days(X, *this);
	}

	static clsDate DecreaseOneWeek(clsDate Date) {
		for (short i = 1; i <= 7; i++) {
			Date = DecreaseOneDay(Date);
		}
		return Date;
	}
	void DecreaseOneWeek() {
		*this = DecreaseOneWeek(*this);
	}

	static clsDate Decrease_X_Weeks(short X, clsDate Date) {
		for (short i = 1; i <= X; i++) {
			Date = DecreaseOneWeek(Date);
		}
		return Date;
	}
	void Decrease_X_Weeks(short X) {
		*this = Decrease_X_Weeks(X, *this);
	}

	static clsDate DecreaseOneMonth(clsDate Date) {
		if (Date._Month == 1) {
			Date._Month = 12;
			Date._Year--;
		}
		else
		{
			Date._Month--;
		}

		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
		if (Date._Day > NumberOfDaysInCurrentMonth)
			Date._Day = NumberOfDaysInCurrentMonth;

		return Date;
	}
	void DecreaseOneMonth() {
		*this = DecreaseOneMonth(*this);
	}

	static clsDate Decrease_X_Months(short X, clsDate Date) {
		for (short i = 1; i <= X; i++) {
			Date = DecreaseOneMonth(Date);
		}
		return Date;
	}
	void Decrease_X_Months(short X) {
		*this = Decrease_X_Months(X, *this);
	}

	static clsDate DecreaseOneYear(clsDate Date) {
		Date._Year--;
		return Date;
	}
	void DecreaseOneYear() {
		*this = DecreaseOneYear(*this);
	}

	static clsDate Decrease_X_Years(short X, clsDate Date) {
		Date._Year -= X;
		return Date;
	}
	void Decrease_X_Years(short X) {
		*this = Decrease_X_Years(X, *this);
	}

	static clsDate DecreaseOneDecade(clsDate Date) {
		Date._Year -= 10;
		return Date;
	}
	void DecreaseOneDecade() {
		*this = DecreaseOneDecade(*this);
	}

	static clsDate Decrease_X_Decades(short X, clsDate Date) {
		Date._Year -= (X * 10);
		return Date;
	}
	void Decrease_X_Decades(short X) {
		*this = Decrease_X_Decades(X, *this);
	}

	static clsDate DecreaseOneCentury(clsDate Date) {
		Date._Year -= 100;
		return Date;
	}
	void DecreaseOneCentury() {
		*this = DecreaseOneCentury(*this);
	}

	static clsDate DecreaseOneMillennium(clsDate Date) {
		Date._Year -= 1000;
		return Date;
	}
	void DecreaseOneMillennium() {
		*this = DecreaseOneMillennium(*this);
	}

	static bool IsEndOfWeek(clsDate Date) {
		return DayOfWeekOrder(Date) == 6;
	}
	bool IsEndOfWeek() {
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date) {
		return DayOfWeekOrder(Date) == 5;
	}
	bool IsWeekEnd() {
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date) {
		return !IsWeekEnd(Date);
	}
	bool IsBusinessDay() {
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date) {
		return 6 - DayOfWeekOrder(Date);
	}
	short DaysUntilTheEndOfWeek() {
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date) {
		return NumberOfDaysInAMonth(Date._Month, Date._Year) - Date._Day + 1;
	}
	short DaysUntilTheEndOfMonth() {
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date) {
		return NumberOfDaysInYear(Date._Year) - NumberOfDaysFromBeginnigOfTheYear(Date) + 1;
	}
	short DaysUntilTheEndOfYear() {
		return DaysUntilTheEndOfYear(*this);
	}

	static short VacationDays(clsDate Date1, clsDate Date2) {
		short Days = 0;

		while (IsDate1BeforeDate2(Date1, Date2)) {
			if (IsBusinessDay(Date1))
				Days++;
			Date1 = IncreaseOneDay(Date1);
		}

		return Days;
	}

	static clsDate CalculateVacationReturnDate(short VacationDays, clsDate DateFrom) {
		short WeekEndCounter = 0;

		while (IsWeekEnd(DateFrom)) {
			DateFrom = IncreaseOneDay(DateFrom);
		}

		for (short i = 1; i <= VacationDays + WeekEndCounter; i++) {
			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			DateFrom = IncreaseOneDay(DateFrom);
		}

		while (IsWeekEnd(DateFrom)) {
			DateFrom = IncreaseOneDay(DateFrom);
		}

		return DateFrom;
	}
	clsDate CalculateVacationReturnDate(short VacationDays) {
		return CalculateVacationReturnDate(VacationDays, *this);
	}

	static enDateCompare CompareDates(clsDate Date1, clsDate Date2) {
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		else if (IsDate1EqualsDate2(Date1, Date2))
			return enDateCompare::Equal;

		return enDateCompare::After;
	}
	enDateCompare CompareDates(clsDate Date2) {
		return CompareDates(*this, Date2);
	}

	static bool IsValid(clsDate Date) {
		return (Date._Day <= NumberOfDaysInAMonth(Date._Month, Date._Year)
			&& Date._Month < 13 && Date._Year >= 0 && Date._Day > 0 && Date._Month > 0);
	}
	bool IsValid() {
		return IsValid(*this);
	}

	static string FormatDate(clsDate Date, string Format = "dd/mm/yyyy") {
		string FormattedDateString = "";
		FormattedDateString = clsString::ReplaceWord(Format, "dd", to_string(Date._Day));
		FormattedDateString = clsString::ReplaceWord(FormattedDateString, "mm", to_string(Date._Month));
		FormattedDateString = clsString::ReplaceWord(FormattedDateString, "yyyy", to_string(Date._Year));
		return  FormattedDateString;
	}
	string FormatDate(string Format = "dd/mm/yyyy") {
		return FormatDate(*this, Format);
	}

	static clsDate MaxDate(clsDate D1, clsDate D2) {
		return clsDate::IsDate1BeforeDate2(D1, D2) ? D2 : D1;
	}

	static clsDate MinDate(clsDate D1, clsDate D2) {
		return clsDate::IsDate1BeforeDate2(D1, D2) ? D1 : D2;
	}

};

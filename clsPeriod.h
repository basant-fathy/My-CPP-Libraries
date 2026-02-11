#pragma once
#include "clsDate.h"

class clsPeriod
{

public:

    clsDate StartDate;
    clsDate EndDate;

    clsPeriod(clsDate StartDate, clsDate DateTo)
    {
        this->StartDate = StartDate;
        this->EndDate = DateTo;

    }

    static bool IsOverlapPeriods(clsPeriod Period1, clsPeriod Period2)
    {

        if (
            clsDate::CompareDates(Period2.EndDate, Period1.StartDate) == clsDate::enDateCompare::Before
            ||
            clsDate::CompareDates(Period2.StartDate, Period1.EndDate) == clsDate::enDateCompare::After
            )
            return false;
        else
            return true;

    }
    bool IsOverLapWith(clsPeriod Period2)
    {
        return IsOverlapPeriods(*this, Period2);
    }

    void Print()
    {
        cout << "Period Start: ";
        StartDate.Print();


        cout << "Period End: ";
        EndDate.Print();


    }

    static short PeriodLengthInDays(clsPeriod Period, bool IncludeEndDay = false) {
        return clsDate::GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludeEndDay);
    }
    short PeriodLengthInDays(bool IncludeEndDay = false) {
        return PeriodLengthInDays(*this, IncludeEndDay);
    }

    static bool IsDateWithinPeriod(clsDate Date, clsPeriod Period) {
        return (clsDate::CompareDates(Date, Period.StartDate) == clsDate::After
            &&
            clsDate::CompareDates(Date, Period.EndDate) == clsDate::Before);
    }
    bool IsDateWithinPeriod(clsDate Date) {
        return IsDateWithinPeriod(Date, *this);
    }

    static short CountOverlapDays(clsPeriod P1, clsPeriod P2) {
        if (!IsOverlapPeriods(P1, P2))
            return 0;

        clsDate StartOverlap = clsDate::MaxDate(P1.StartDate, P2.StartDate);
        clsDate EndOverlap = clsDate::MinDate(P1.EndDate, P2.EndDate);

        return clsDate::GetDifferenceInDays(StartOverlap, EndOverlap, true);
    }
    short CountOverlapDaysWith(clsPeriod P2) {
        return CountOverlapDays(*this, P2);
    }
};

#include "MyCalendar.h"

// PreCondition: N/A
// PostCondition: sync the date with the current machine
MyCalendar::MyCalendar()
{
	// days in the months
	int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (isLeapYear())
	{
		daysInMonth[1] = 29;
	}

	// sync the time
	syncTime();

	// initialize the MyScheduleDay array
	// months
	for (int i = 0; i < 12; i++)
	{
		// days
		for (int j = 0; j < daysInMonth[i]; j++)
		{
			scheduleDays[i][j] = MyScheduleDay();
		}
	}
}

// PreCondition: year must be positive and an integer
// PostCondition: set currentYear to y
void MyCalendar::setCurrentYear(int y)
{
	currentYear = y;
}

// PreCondition: N/A
// PostCondition: return the current year
unsigned short MyCalendar::getCurrentYear() const
{
	return currentYear;
}

// PreCondition: month must be an integer Month must be between 1 and 12
// PostCondition: set currentMonth to m
void MyCalendar::setCurrentMonth(int m)
{
	currentMonth = m;
}

// PreCondition: N/A
// PostCondition: return the current month
unsigned short MyCalendar::getCurrentMonth() const
{
	return currentMonth;
}

// PreCondition: day must be an integer. Day must be a valid day between 1 and 31, depending on the month
// PostCondition: set currentDay to d
void MyCalendar::setCurrentDay(int d)
{
	currentDay = d;
}

// PreCondition: N/A
// PostCondition: return the current day
unsigned short MyCalendar::getCurrentDay() const
{
	return currentDay;
}

// PreCondition: type must be a char. Type can only be 'A', 'H', or 'P'. Month and Day must be valid dates and integers. 
// PostCondition: set type to t at the specified element
void MyCalendar::setType(int m, int d, char t)
{
	scheduleDays[m - 1][d - 1].setType(t);
}

// PreCondition: month and day must be valid dates and integers
// PostConditon: return the type and description of the day
char MyCalendar::getType(int m, int d) const
{
	return scheduleDays[m - 1][d - 1].getType();
}

// PreCondition: Description must be a string. Month and Day must be valid dates and must be integers
// PostCondition: set the description to newDescription at the specified element
void MyCalendar::setDescription(int m, int d, string newDescription)
{
	scheduleDays[m - 1][d - 1].setDescription(newDescription);
}

// PreCondition: month and day must be valid dates and integers
// PostCondition: return the description for the day
string MyCalendar::getDescription(int m, int d) const
{
	return scheduleDays[m - 1][d - 1].getDescription();
}

// PreCondition: N/A
// PostCondition: sync the time with the machine and set the members
void MyCalendar::syncTime()
{
	// Obtain the current time
	time_t now = time(0);

	// Create a tm structure to store the local time result
	tm localTime;

	// Use localtime_s to populate localTime
	if (localtime_s(&localTime, &now) == 0)
	{
		// Access the current year, month, and day components
		int year = 1900 + localTime.tm_year;
		int month = 1 + localTime.tm_mon;
		int day = localTime.tm_mday;

		// Use setter functions to set the class members
		setCurrentYear(year);
		setCurrentMonth(month);
		setCurrentDay(day);
	}
}

// PreCondition: N/A
// PostCondition: checks if the year is a leap year. return true if leap year or false if not leap year
bool MyCalendar::isLeapYear() const
{
	// check if the year is a leap year
	if (currentYear % 4 == 0)
	{
		if (currentYear % 100 == 0)
		{
			return currentYear % 400 == 0;
		}
		return true;
	}
	return false;
}

// PreCondition: day must be a valid day in a month and an integer
// PostCondition: return the corresponding suffix according to the day
string MyCalendar::getSuffix(int d) const
{
	string suffix = "na";
	
	// get suffix depending on the day
	switch (d)
	{
	case 1: case 21: case 31:
		suffix = "st";
		break;
	case 2: case 22:
		suffix = "nd";
		break;
	case 3: case 23:
		suffix = "rd";
		break;
	default:
		suffix = "th";
		break;
	}
	return suffix;
}

// PreCondition: N/A
// PostCondition: return the year in words
string MyCalendar::getStringYear() const
{
	string stringYear;
	int year = getCurrentYear();

	// ones digit
	const string ones[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve",
							"Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };

	// tens digit
	const string tens[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

	// convert the year into a string
	// thousands place
	if (year >= 1000)
	{
		stringYear += ones[year / 1000] + " Thousand ";
		year %= 1000;
	}

	// hundreds place
	if (year / 100 > 0)
	{
		stringYear += ones[year / 100] + " Hundred ";
		year %= 100;
	}

	// years less than 20
	if (year < 20)
	{
		stringYear += ones[year];
	}
	else
	{
		// years larger than 20
		stringYear += tens[year / 10];
		if (year % 10 > 0)
		{
			stringYear += " " + ones[year % 10];
		}
	}
	return stringYear;
}

// PreCondition: N/A
// PostCondition: return the day of the week
string MyCalendar::getDayOfWeek() const
{
	int day = currentDay;
	int month = currentMonth;
	int year = currentYear;
	if (month == 1)
	{
		month = 13;
		year--;
	}
	if (month == 2)
	{
		month = 14;
		year--;
	}

	int q = day;
	int m = month;
	int k = year % 100;
	int j = year / 100;
	int h = q + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j;
	h = h % 7;

	// get the day of the week
	switch (h)
	{
		case 0:
			return "Saturday";
		case 1:
			return "Sunday";
		case 2:
			return "Monday";
		case 3:
			return "Tuesday";
		case 4:
			return "Wednesday";
		case 5:
			return "Thursday";
		case 6:
			return "Friday";
		default:
			return "Invalid Day";
	}
}

// PreCondition: N/A
// PostCondition: return the first day of the month
int MyCalendar::getFirstDayOfMonth(int m) const
{
	int month = m;
	int year = currentYear;

	// Adjust for January and February as months 13 and 14 of the previous year
	if (month < 3) {
		month += 12;
		year -= 1;
	}

	int k = year % 100;            // Year within century
	int j = year / 100;            // Century
	int dayOfWeek = (1 + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;

	// Zeller's formula returns 0 = Saturday, 1 = Sunday, ..., 6 = Friday
	// To make Sunday = 0, shift result by 1.
	return (dayOfWeek + 6) % 7;
}

// PreCondition: N/A
// PostCondition: overload the ++ (pre-increment operator)
MyCalendar MyCalendar::operator++()
{
	int d = getCurrentDay();
	int m = getCurrentMonth();
	int y = getCurrentYear();

	switch (m)
	{
		case 2: // February
		{
			// increment to next month if its the last day
			if (d >= 28 && !isLeapYear())
			{
				setCurrentDay(1);
				setCurrentMonth(++m);
			}

			// increment to next month if its the last day
			else if (d >= 29 && isLeapYear())
			{
				setCurrentDay(1);
				setCurrentMonth(++m);
			}

			// increment the day
			else
				setCurrentDay(++d);
			break;
		}

		case 12: // December
		{
			// increment to January of next year if its the last day
			if (d >= 31)
			{
				setCurrentDay(1);
				setCurrentMonth(1);
				setCurrentYear(++y);
			}

			// increment the day
			else
				setCurrentDay(++d);
			break;
		}

		case 4: case 6: case 9: case 11: // days with 30 days
		{
			// increment the month if its the last day
			if (d >= 30)
			{
				setCurrentDay(1);
				setCurrentMonth(++m);
			}

			// increment the day
			else
				setCurrentDay(++d);
			break;
		}

		default: // days with 31 days
		{
			// increment the month if its the last day
			if (d >= 31)
			{
				setCurrentDay(1);
				setCurrentMonth(++m);
			}

			// increment the day
			else
				setCurrentDay(++d);
			break;
		}
	}
	return *this;
}

// PreCondition: N/A
// PostCondition: overload the ++ (post-increment operator)
MyCalendar MyCalendar::operator++(int)
{
	MyCalendar temp = *this;

	int d = getCurrentDay();
	int m = getCurrentMonth();
	int y = getCurrentYear();

	switch (m)
	{
		case 2: // February
		{
			// increment to next month if its the last day
			if (d >= 28 && !isLeapYear())
			{
				setCurrentDay(1);
				setCurrentMonth(++m);
			}

			// increment to next month if its the last day
			else if (d >= 29 && isLeapYear())
			{
				setCurrentDay(1);
				setCurrentMonth(++m);
			}

			// increment the day
			else
				setCurrentDay(++d);
			break;
		}

		case 12: // December
		{
			// increment to January of next year if its the last day
			if (d >= 31)
			{
				setCurrentDay(1);
				setCurrentMonth(1);
				setCurrentYear(++y);
			}

			// increment the day
			else
				setCurrentDay(++d);
			break;
		}

		case 4: case 6: case 9: case 11: // days with 30 days
		{
			// increment the month if its the last day
			if (d >= 30)
			{
				setCurrentDay(1);
				setCurrentMonth(++m);
			}

			// increment the day
			else
				setCurrentDay(++d);
			break;
		}

		default: // days with 31 days
		{
			// increment the month if its the last day
			if (d >= 31)
			{
				setCurrentDay(1);
				setCurrentMonth(++m);
			}

			// increment the day
			else
				setCurrentDay(++d);
			break;
		}
	}
	return temp;
}

// PreCondition: N/A
// PostCondition: overload the -- (pre-decrement operator)
MyCalendar MyCalendar::operator--()
{
	int d = getCurrentDay();
	int m = getCurrentMonth();
	int y = getCurrentYear();

	switch (m)
	{
		case 1: // January
		{
			// decrement to December of the previous year if its the first day
			if (d <= 1)
			{
				setCurrentDay(31);
				setCurrentMonth(12);
				setCurrentYear(--y);
			}

			// decrement the day
			else
				setCurrentDay(--d);
			break;
		}

		case 3: // March
		{
			// decrement the month if its the first day
			if (d <= 1 && !isLeapYear())
			{
				setCurrentDay(28);
				setCurrentMonth(--m);
			}

			// decrement the month if its the first day
			else if (d <= 1 && isLeapYear())
			{
				setCurrentDay(29);
				setCurrentMonth(2);
			}

			// decrement the day
			else
				setCurrentDay(--d);
			break;
		}

		case 2: case 4: case 6: case 8: case 9: case 11: // months that are in front of months with 31 days
		{
			// decrement the month if its the first day
			if (d <= 1)
			{
				setCurrentDay(31);
				setCurrentMonth(--m);
			}

			// decrement the day
			else
				setCurrentDay(--d);
			break;
		}

		default: // months that are in front of months with 30 days
		{
			// decrement the month if its the first day
			if (d <= 1)
			{
				setCurrentDay(30);
				setCurrentMonth(--m);
			}

			// decrement the day
			else
				setCurrentDay(--d);
			break;
		}
	}
	return *this;
}

// PreCondition: N/A
// PostCondition: overload the -- (post-decrement) operator
MyCalendar MyCalendar::operator--(int)
{
	MyCalendar temp = *this;

	int d = getCurrentDay();
	int m = getCurrentMonth();
	int y = getCurrentYear();

	switch (m)
	{
		case 1: // January
		{
			// decrement to December of the previous year if its the first day
			if (d <= 1)
			{
				setCurrentDay(31);
				setCurrentMonth(12);
				setCurrentYear(--y);
			}

			// decrement the day
			else
				setCurrentDay(--d);
			break;
		}

		case 3: // March
		{
			// decrement the month if its the first day
			if (d <= 1 && !isLeapYear())
			{
				setCurrentDay(28);
				setCurrentMonth(--m);
			}

			// decrement the month if its the first day
			else if (d <= 1 && isLeapYear())
			{
				setCurrentDay(29);
				setCurrentMonth(2);
			}

			// decrement the day
			else
				setCurrentDay(--d);
			break;
		}

		case 2: case 4: case 6: case 8: case 9: case 11: // months that are in front of months with 31 days
		{
			// decrement the month if its the first day
			if (d <= 1)
			{
				setCurrentDay(31);
				setCurrentMonth(--m);
			}

			// decrement the day
			else
				setCurrentDay(--d);
			break;
		}

		default: // months that are in front of months with 30 days
		{
			// decrement the month if its the first day
			if (d <= 1)
			{
				setCurrentDay(30);
				setCurrentMonth(--m);
			}

			// decrement the day
			else
				setCurrentDay(--d);
			break;
		}
	}
	return temp;
}

// PreCondition: jump number must be positive and an integer
// PostCondition: increment and return the MyCalendar object
MyCalendar MyCalendar::jumpForward(int jump)
{
	for (int i = 0; i < jump; i++)
	{
		++*this;
	}
	return *this;
}

// PreCondition: jump number must be positive and an integer
// PostCondition: decrement and return the MyCalendar object
MyCalendar MyCalendar::jumpBackward(int jump)
{
	for (int i = 0; i < jump; i++)
	{
		--*this;
	}
	return *this;
}

// PreCondition: N/A
// PostCondition: display the date. overload the << operator
ostream& operator <<(ostream& out, const MyCalendar& obj)
{
	const string months[] = { "January", "February", "March", "April", "May" ,"June" , "July", "August", "September", "October", "November", "December" };
	out << "\n\t" << obj.getDayOfWeek() << ", " << months[obj.getCurrentMonth() - 1] << " " << obj.getCurrentDay() << obj.getSuffix(obj.getCurrentDay()) << ", "
		<< obj.getCurrentYear();

	out << "\n\t" << obj.getCurrentMonth() << "/" << obj.getCurrentDay() << "/" << obj.getCurrentYear() << "\n";

	return out;
}
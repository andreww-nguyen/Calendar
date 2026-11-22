// Andrew Nguyen
// 10/28/24
// Exam 2


#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
#include <fstream>
#include <windows.h>
#include <map>


#include "input.h"
#include "MyUnit.h"
#include "MyScheduleDay.h"
#include "MyCalendar.h"

using namespace std;

// function prototypes
void setConsoleColor(int color);
void displayCalendar(MyCalendar& c);
char menuOption();
int setSubMenuOption(string choice);
int myCalendarMenu();
int scheduleDateMenu();

void setYear(MyCalendar& c);
void setMonth(MyCalendar& c);
void setDay(MyCalendar& c);
void setCalendar(MyCalendar& c);
void scheduleDates(MyCalendar& c);

int main(void)
{
	MyCalendar testC; // derived class
	do
	{
		system("cls");
		// display the calender
		displayCalendar(testC);
		switch (toupper(menuOption()))
		{
			case 'A': // set the year
			{
				setYear(testC);
				break;
			}

			case 'B': // set the momth
			{
				setMonth(testC);
				break;		
			}

			case 'C': // set the day
			{
				setDay(testC);
				break;		
			}

			case 'D': // set current calendar
			{
				setCalendar(testC);
				break;	
			}

			case 'E': // schedule and report days
			{
				scheduleDates(testC);
				break;
			}

			case 'F': // sync time
			{
				// sync time
				testC.syncTime();
				break;
			}

			case 'G': // save calendar to binary file
			{
				fstream outFile;

				// open the file
				string fileName = to_string(testC.getCurrentYear()) + ".DAT";
				outFile.open(fileName, ios::out | ios::binary);
				if (outFile.fail())
				{
					outFile.close();
					setConsoleColor(4);
					cout << "\n\tERROR: Binary Data file, " << fileName << ", cannot be found.\n";
					setConsoleColor(7);
					break;
				}

				// write to the file
				outFile.write(reinterpret_cast<char*>(&testC), sizeof(MyCalendar));
				outFile.close();

				setConsoleColor(2);
				cout << "\n\tSUCCESS: File, " << fileName << ", has been saved.\n";
				setConsoleColor(7);
				break;
			}

			case 'H': // read calendar from binary file
			{
				fstream inFile;
				// get the file name
				string fileName = (inputString("\n\tEnter a binary (DAT) calendar file name: ", false));

				// open the file
				inFile.open(fileName, ios::in | ios::binary);
				if (inFile.fail())
				{
					inFile.close();
					setConsoleColor(4);
					cout << "\n\tERROR: Binary Data File, " << fileName << ", cannot be found.\n";
					setConsoleColor(7);
					break;
				}

				// read from the file
				inFile.read(reinterpret_cast<char*> (&testC), sizeof(MyCalendar));
				inFile.close();

				setConsoleColor(2);
				cout << "\n\tSUCCESS: Restored Calendar from " << fileName << ".\n";
				setConsoleColor(7);
				break;
			}
			case 'X': exit(1); break;
			default: 
			{
				setConsoleColor(4);
				cout << "\n\tERROR: Invalid Option. Please re-enter"; 
				setConsoleColor(7);
				break;
			}
		}
		cout << "\n";
		system("pause");
	} while (true);
	return EXIT_SUCCESS;
}

// PreCondition: integer is a valid color
// PostCondition: set the color of the text
void setConsoleColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

// PreCondition: MyCalendar object is passed
// PostCondition: display the calendar and all the information
void displayCalendar(MyCalendar& c)
{
	// months
	const string months[] = { "unknown", "January", "February", "March", "April", "May" ,"June" , "July", "August", "September", "October", "November", "December" };
	
	// awareness
	const string awareness[] = { "unknown", "Thyroid Month", "Heart Failure Month", "Multiple Sclerosis Month", "Oral Cancer Month", 
								"Mental Health Month" ,"Migrane and Headache Month" , "Juvenile Arthrisis Month", "Immunization Month", 
								"September", "Breast Cancer Month", "Lung Cancer Month", "HIV Aids Month" };

	// days in months
	int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (c.isLeapYear())
		daysInMonth[1] = 29;

	// leap year
	const string leapYear[] = { " (Non-Leap Year)", " (Leap Year)" };

	// display the information
	// year
	cout << "\t" << string(1, 218) << string(84, 196) << string(1, 191);
	cout << "\n\t" << string(1, 179) << setw(16) << left << " Current Year  : "; 
	setConsoleColor(1);
	cout << setw(67) << to_string(c.getCurrentYear()) + " - " + c.getStringYear() + leapYear[c.isLeapYear()]; 
	setConsoleColor(7);
	cout << string(1, 179);
	
	// month
	cout << "\n\t" << string(1, 195) << string(84, 196) << string(1, 180);
	cout << "\n\t" << string(1, 179) << setw(16) << left << " Current Month : ";
	setConsoleColor(1);
	cout << setw(67) << to_string(c.getCurrentMonth()) + " - " + months[c.getCurrentMonth()];
	setConsoleColor(7);
	cout << string(1, 179);
	cout << "\n\t" << string(1, 179) << setw(16) << left << " Awareness     : ";
	setConsoleColor(1);
	cout << setw(67) << awareness[c.getCurrentMonth()];
	setConsoleColor(7);
	cout << string(1, 179);

	// day
	cout << "\n\t" << string(1, 195) << string(84, 196) << string(1, 180);
	cout << "\n\t" << string(1, 179) << setw(16) << left << " Current Day   : ";
	setConsoleColor(1);
	cout << setw(67) << to_string(c.getCurrentDay()) + c.getSuffix(c.getCurrentDay()) + " - " + c.getDayOfWeek();
	setConsoleColor(7);
	cout << string(1, 179);
	cout << "\n\t" << string(1, 179) << setw(16) << left << "               : "; 
	setConsoleColor(1);
	cout << setw(67) << c.getDescription(c.getCurrentMonth(), c.getCurrentDay());
	setConsoleColor(7);
	cout << string(1, 179);
	cout << "\n\t" << string(1, 195) << string(11, 196) << string(1, 194) << string(11, 196) << string(1, 194) << string(11, 196) << string(1, 194) << string(11, 196) <<
		string(1, 194) << string(11, 196) << string(1, 194) << string(12, 196) << string(1, 194) << string(11, 196) << string(1, 180);

	// display the header for the days
	cout << "\n\t" << string(1, 179) << "  Sunday   " << string(1, 179) << "  Monday   " << string(1, 179) << "  Tuesday  " << string(1, 179) << " Wednesday " << string(1, 179) <<
		" Thursday  " << string(1, 179) << "   Friday   " << string(1, 179) << " Saturday  " << string(1, 179);
	cout << "\n\t" << string(1, 195) << string(11, 196) << string(1, 193) << string(11, 196) << string(1, 193) << string(11, 196) << string(1, 193) << string(11, 196) << string(1, 193) <<
		string(11, 196) << string(1, 193) << string(12, 196) << string(1, 193) << string(11, 196) << string(1, 180);
	cout << "\n\t" << string(1, 179);

	// display the calendar
	int startDay = c.getFirstDayOfMonth(c.getCurrentMonth());
	int day = 1;

	// Fill initial empty days
	for (int i = 0; i < startDay; i++) 
		cout << right << setw(7) << string(2, 176) << setw(5) << "  ";

	// display the days of the month
	for (int i = startDay; i < 7; i++) 
		cout << right << setw(7) << day++ << setw(5) << "  ";
	cout << string(1, 179);
	cout << "\n\t" << string(1, 179);

	// display the rest of the days
	while (day <= daysInMonth[c.getCurrentMonth() - 1])
	{
		for (int i = 0; i < 7; i++)
		{
			if (day <= daysInMonth[c.getCurrentMonth() - 1])
			{
				if (day == c.getCurrentDay())
				{
					setConsoleColor(1);
					cout << right << setw(7) << day++ << setw(5) << "  ";
					setConsoleColor(7);
				}
				else
					cout << right << setw(7) << day++ << setw(5) << "  ";
			}
			else
				cout << right << setw(7) << string(2, 176) << setw(5) << "  ";
		}

		// End the current row
		cout << string(1, 179) << "\n\t" << string(1, 179);
	}
	cout << setw(85) << string(1, 179);
	cout << "\n\t" << string(1, 192) << string(84, 196) << string(1, 217);
	cout << "\n";
}

// PreCondition: N/A
// PostCondition: return the user's char option
char menuOption()
{
	cout << "\n\tCalendar Implementation";
	cout << "\n\t" << string(86, 205);
	cout << "\n\t\tA. Setting Current Year";
	cout << "\n\t\tB. Setting Current Month";
	cout << "\n\t\tC. Setting Current Day";
	cout << "\n\t\tD. Setting Current Calendar";
	cout << "\n\t\tE. Schedule and Report Dates";
	cout << "\n\t" << string(86, 196);
	cout << "\n\t\tF. Sync to System's Date";
	cout << "\n\t\tG. Save Calender to File";
	cout << "\n\t\tH. Restore Calendar from File";
	cout << "\n\t" << string(86, 196);
	cout << "\n\t\tX. Exit";
	cout << "\n\t" << string(86, 205);
	return inputChar("\n\t\tOption: ", "ABCDEFGHX");
}

// PreCondition: string is passed. String is either "Year", "Month", or "Day"
// PostCondition: return the user's integet option
int setSubMenuOption(string option)
{
	cout << "\n\tCalendar - Current " << option <<  " Menu";
	cout << "\n\t" << string(80, 205);
	cout << "\n\t1. Set Current " << option;
	cout << "\n\t" << string(80, 196);
	cout << "\n\t0. Return";
	cout << "\n\t" << string(80, 205);
	return inputInteger("\n\tOption: ", 0, 1);
}

// PreCondition: N/A
// PostCondition: return the user's integer option
int myCalendarMenu()
{
	cout << "\n\tMy Calendar Menu";
	cout << "\n\t" << string(80, 205);
	cout << "\n\t 1. ++ (pre-increment)";
	cout << "\n\t 2. ++ (post-increment)";
	cout << "\n\t 3. +n (jump forward)";
	cout << "\n\t" << string(80, 196);
	cout << "\n\t-1. -- (pre-decrement)";
	cout << "\n\t-2. -- (post-decrement)";
	cout << "\n\t-3. -n (jump backward)";
	cout << "\n\t" << string(80, 196);
	cout << "\n\t 0. Return";
	cout << "\n\t" << string(80, 205);
	return inputInteger("\n\tOption: ", -3, 3);
}

// PreCondition: N/A
// PostCondition: return the user's integer option
int scheduleDateMenu()
{
	cout << "\n\tScheduling Date";
	cout << "\n\t" << string(80, 205);
	cout << "\n\t1. Schedule a Date";
	cout << "\n\t2. Unschedule a Date";
	cout << "\n\t" << string(80, 196);
	cout << "\n\t3. Display Year Schedule";
	cout << "\n\t4. Display Month Schedule";
	cout << "\n\t5. Display Day Schedule";
	cout << "\n\t" << string(80, 196);
	cout << "\n\t0. Return";
	cout << "\n\t" << string(80, 205);
	return inputInteger("\n\tOption: ", 0, 5);
}

// PreCondition: MyCalendar object is passed
// PreCondition: allow the user to set the year
void setYear(MyCalendar& c)
{
	do
	{
		system("cls");
		// display current year
		cout << "\n\tCurrent Year: " << c.getCurrentYear() << "\n";

		// set the year
		switch (setSubMenuOption("Year"))
		{
			case 1: // set the year
			{
				c.setCurrentYear(inputInteger("\n\tEnter a year (1...9999): ", 1, 9999));
				cout << "\n";
				break;
			}
			case 0: return;
			default: 
			{
				setConsoleColor(4);
				cout << "\n\tERROR: Invalid Choice";
				setConsoleColor(7);
				break;
			}
		}

		system("pause");
	} while (true);
}

// PreCondition: MyCalendar object is passed
// PreCondition: allow the user to set the month
void setMonth(MyCalendar& c)
{
	// days in months
	int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (c.isLeapYear())
		daysInMonth[1] = 29;

	do
	{
		system("cls");
		// display current month
		cout << "\n\tCurrent Month: " << c.getCurrentMonth() << "\n";

		// set the month
		switch (setSubMenuOption("Month"))
		{
			case 1: // set the month
			{
				c.setCurrentMonth(inputInteger("\n\tEnter a month (1...12): ", 1, 12));
				// set the day to the last day if the day is outside of bounds
				if (c.getCurrentDay() > daysInMonth[c.getCurrentMonth() - 1])
					c.setCurrentDay(daysInMonth[c.getCurrentMonth() - 1]);

				cout << "\n";
				break;
			}
			case 0: return;
			default: 
			{
				setConsoleColor(4);
				cout << "\n\tERROR: Invalid Choice";
				setConsoleColor(7);
				break;
			}
		}

		system("pause");
	} while (true);
}

// PreCondition: MyCalendar object is passed
// PreCondition: allow the user to set the day
void setDay(MyCalendar& c)
{
	do
	{
		system("cls");
		// display current day
		cout << "\n\tCurrent Day: " << c.getCurrentDay() << c.getSuffix(c.getCurrentDay()) << "\n"; 

		// set the day
		switch (setSubMenuOption("Day"))
		{
			case 1: // set the day based on month
			{
				switch (c.getCurrentMonth())
				{
					case 1: case 3: case 5: case 7: case 8: case 10: case 12: // 31 days
					{
						c.setCurrentDay(inputInteger("\n\tEnter a day (1...31): ", 1, 31));
						break;
					}

					case 4: case 6: case 9: case 11: // 30 days
					{
						c.setCurrentDay(inputInteger("\n\tEnter a day (1...30): ", 1, 30));
						break;
					}

					case 2: // 28 or 29 days
					{
						// leap year
						if (c.isLeapYear())
							c.setCurrentDay(inputInteger("\n\tEnter a day (1...29): ", 1, 29));

						// non leap year
						else
							c.setCurrentDay(inputInteger("\n\tEnter a day (1...28): ", 1, 28));
						break;
					}
				}
				cout << "\n";
				break;
			}
			case 0: return;
			default: 
			{
				setConsoleColor(4);
				cout << "\n\tERROR: Invalid Choice";
				setConsoleColor(7);
				break;
			}
		}
		system("pause");
	} while (true);
}

// PreCondition: MyCalendar object is passed
// PreCondition: allow the user to set the calendar using pre and post increment/ decrement
void setCalendar(MyCalendar& c)
{
	do
	{
		system("cls");
		cout << c;
		switch (myCalendarMenu())
		{
			case 1: // pre-increment
			{
				cout << "\n\tPre-Increment: (++)";
				cout << "\n" << ++c << "\n";
				break;
			}

			case 2: // post-increment
			{
				cout << "\n\tPost-Increment: (++)";
				cout << "\n" << c++ << "\n";
				break;
			}

			case 3: // jump forwards
			{
				// get the jump number
				int jump = inputInteger("\n\tEnter an integer (n): ", 1, 9999);

				// jump forward
				c.jumpForward(jump);
				cout << "\n\tJump Forward (" << jump << ")" << "\n\n";
				break;
			}

			case -1: // pre-decrement
			{
				cout << "\n\tPre-Decrement: (--)";
				cout << "\n" << --c << "\n";
				break;
			}

			case -2: // post-decrement
			{
				cout << "\n\tPost-Decrement: (--)";
				cout << "\n" << c-- << "\n";
				break;
			}

			case -3: // jump backwards
			{
				// get the jump number
				int jump = inputInteger("\n\tEnter an integer (n): ", 1, 9999);

				// jump backward
				c.jumpBackward(jump);
				cout << "\n\tJump backward (" << jump << ")" << "\n\n";
				break;
			}
			case 0: return;
			default:
			{
				setConsoleColor(4);
				cout << "\n\tERROR: Invalid Choice";
				setConsoleColor(7);
				break;
			}
		}
		system("pause");
	} while (true);
}

// PreCondition: MyCalendar object is passed
// PreCondition: allow the user to schedule important dates
void scheduleDates(MyCalendar& c)
{
	const string months[] = { "January", "February", "March", "April", "May" ,"June" , "July", "August",
							  "September", "October", "November", "December" };

	int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (c.isLeapYear())
		daysInMonth[1] = 29;

	do
	{
		system("cls");
		// display current day and info
		cout << "\n\tMonth       : " << months[c.getCurrentMonth() - 1];
		cout << "\n\tDay         : " << c.getCurrentDay();
		cout << "\n\tType        : " << c.getType(c.getCurrentMonth(), c.getCurrentDay());
		cout << "\n\tDescription : " << c.getDescription(c.getCurrentMonth(), c.getCurrentDay()) << "\n";

		switch (scheduleDateMenu())
		{
			case 1: // schedule a date
			{
				// get the month
				int month = inputInteger("\n\tSpecify a month (1...12): ", 1, 12);
				int day;

				// get the day based on the month
				switch (month)
				{
					case 1: case 3: case 5: case 7: case 8: case 10: case 12: // 31 days
					{
						day = (inputInteger("\n\tEnter a day (1...31): ", 1, 31));
						break;
					}

					case 4: case 6: case 9: case 11: // 30 days
					{
						day = (inputInteger("\n\tEnter a day (1...30): ", 1, 30));
						break;
					}

					case 2: // 28 or 29 days days
					{
						// leap year
						if (c.isLeapYear())
							day = (inputInteger("\n\tEnter a day (1...29): ", 1, 29));

						// non leap year
						else
							day = (inputInteger("\n\tEnter a day (1...28): ", 1, 28));
						break;
					}
				}

				// temporary variable to hold the old type
				char oldType = c.getType(month, day);

				// get the description
				string description = inputString("\n\tEnter a description: ", true);
				char type;

				// get the type
				do
				{
					type = toupper(inputChar("\n\tSpecify a type (R-return, A-awareness, H-holiday, or P-personal): ", "RAPH"));

					// validate the type is valid
					if (type != 'R' && type != 'A' && type != 'H' && type != 'P')
					{
						setConsoleColor(4);
						cout << "\n\tERROR: Invalid Type\n";
						setConsoleColor(7);
					}
					else 
						break;
				} while (true);

				// return if R
				if (type == 'R')
				{
					cout << "\n\tDate has NOT been scheduled or rescheduled.\n\n";
					break;
				}

				// set the date and the description
				c.setType(month, day, type);
				c.setDescription(month, day, description);
				
				// display warning message if overwriting previous scheduled date
				if (toupper(oldType) != 'U')
				{
					string oldDescription;
					switch (toupper(oldType))
					{
						case 'A': oldDescription = "Awareness"; break;
						case 'H': oldDescription = "Holiday"; break;
						case 'P': oldDescription = "Personal"; break;
					}

					setConsoleColor(6);
					cout << "\n\tWARNING: overwrite the existing scheduled date to " << "'" << oldDescription << "'" << "\n";
					setConsoleColor(7);
				}

				setConsoleColor(2);
				cout << "\n\tSUCCESS: Date has been successfully scheduled.\n\n";
				setConsoleColor(7);
				break;
			}

			case 2: // unschedule a date
			{
				// get the month
				int month = inputInteger("\n\tSpecify a month (1...12): ", 1, 12);
				int day;

				// get the day based on the month
				switch (month)
				{
				case 1: case 3: case 5: case 7: case 8: case 10: case 12: // 31 days
					{
						day = (inputInteger("\n\tEnter a day (1...31): ", 1, 31));
						break;
					}

					case 4: case 6: case 9: case 11: // 30 days
					{
						day = (inputInteger("\n\tEnter a day (1...30): ", 1, 30));
						break;
					}

					case 2: // 28 or 29 days
					{
						// leap year
						if (c.isLeapYear())
							day = (inputInteger("\n\tEnter a day (1...29): ", 1, 29));

						// non leap year
						else
							day = (inputInteger("\n\tEnter a day (1...28): ", 1, 28));
						break;
					}
				}

				// unschedule the date
				c.setType(month, day, 'U');
				c.setDescription(month, day, "unschedule");

				setConsoleColor(2);
				cout << "\n\tSUCCESS: Date has sucessfully been unscheduled.\n\n";
				setConsoleColor(7);
				break;
			}

			case 3: // display year schedule
			{
				bool isYearScheduled = false;
				
				// iterate through the months
				for (int i = 0; i < 12; i++)
				{
					bool isMonthScheduled = false;
					cout << "\n\t" << left << setw(11) << months[i] << ": ";
					
					// iterate through the days of the month
					for (int j = 0; j < daysInMonth[i]; j++)
					{
						// display any dates that are scheduled
						if (c.getType(i + 1, j + 1) != 'U')
						{
							cout << "\n\t" << right << setw(11);
							setConsoleColor(1);
							cout << j + 1 << c.getSuffix(j + 1) << " - " << c.getDescription(i + 1, j + 1);
							setConsoleColor(7);
							cout << "\n";
							isYearScheduled = true;
							isMonthScheduled = true;
						}
					}

					if (!isMonthScheduled)
					{
						cout << "No scheduled dates for the month.\n";
					}
				}

				cout << "\n";
				// no dates scheduled for the year
				if (!isYearScheduled)
				{
					setConsoleColor(2);
					cout << "\t* No scheduled dates for the current year.";
					setConsoleColor(7);
					cout << "\n\n";
				}
				break;
			}
			case 4: // display month schedule
			{
				int month = inputInteger("\n\tSpecify a month (1...12): ", 1, 12);
				cout << "\n\t" << left << setw(11) << months[month - 1] << ": ";

				bool isScheduled = false;
				// iterate through the days of the month
				for (int j = 0; j < daysInMonth[month - 1]; j++)
				{
					// display any dates that are scheduled
					if (c.getType(month, j + 1) != 'U')
					{
						cout << "\n\t" << right << setw(11);
						setConsoleColor(1);
						cout << j + 1 << c.getSuffix(j + 1) << " - " << c.getDescription(month, j + 1);
						setConsoleColor(7);
						cout << "\n";
						isScheduled = true;
					}
				}

				// no dates scheduled for the month
				if (!isScheduled)
				{
					cout << "No scheduled dates for the month.\n";
					cout << "\n";
				}
				break;
			}
			case 5: // display day schedule
			{
				// get the month
				int month = inputInteger("\n\tSpecify a month (1...12): ", 1, 12);
				int day;

				// get the day based on the month
				switch (month)
				{
					case 1: case 3: case 5: case 7: case 8: case 10: case 12: // 31 days
					{
						day = (inputInteger("\n\tEnter a day (1...31): ", 1, 31));
						break;
					}

					case 4: case 6: case 9: case 11: // 30 days
					{
						day = (inputInteger("\n\tEnter a day (1...30): ", 1, 30));
						break;
					}

					case 2: // 28 or 29 days
					{
						// leap year
						if (c.isLeapYear())
							day = (inputInteger("\n\tEnter a day (1...29): ", 1, 29));

						// non leap year
						else
							day = (inputInteger("\n\tEnter a day (1...28): ", 1, 28));
						break;
					}
				}

				// display any scheduled dates for the day
				cout << "\n\t" << left << setw(11) << months[month - 1] << ": ";
				if (c.getType(month, day) != 'U')
				{
					cout << "\n\t" << right << setw(11);
					setConsoleColor(1);
					cout << day << c.getSuffix(day) << " - " << c.getDescription(month, day);
					setConsoleColor(7);
					cout << "\n\n";
				}

				// no dates scheduled for the day
				else
					cout << "No scheduled dates for the day.\n";
				break;
			}
			case 0: return;
		}
		system("pause");
	} while (true);
}
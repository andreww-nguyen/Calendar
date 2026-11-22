#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <Windows.h>
#include "MyScheduleDay.h"

class MyCalendar
{
private:
	unsigned short currentYear;
	unsigned short currentMonth;
	unsigned short currentDay;
	MyScheduleDay scheduleDays[12][31];

public:
	MyCalendar(); // need to finish

	// setters and getters
	void setCurrentYear(int y);
	unsigned short getCurrentYear() const;	
	void setCurrentMonth(int m);
	unsigned short getCurrentMonth() const;
	void setCurrentDay(int d);
	unsigned short getCurrentDay() const;
	
	void setType(int m, int d, char t);
	char getType(int m, int d) const;
	void setDescription(int m, int d, string newDescription);
	string getDescription(int m, int d) const;

	// extra helper members
	void syncTime();
	bool isLeapYear() const;
	string getSuffix(int d) const;
	string getStringYear() const;
	int getFirstDayOfMonth(int m) const;
	string getDayOfWeek() const;

	// overloaded operators
	MyCalendar operator++();
	MyCalendar operator++(int);
	MyCalendar operator--();
	MyCalendar operator--(int);

	MyCalendar jumpForward(int jump);
	MyCalendar jumpBackward(int jump);

	friend ostream& operator <<(ostream& out, const MyCalendar& obj);
};
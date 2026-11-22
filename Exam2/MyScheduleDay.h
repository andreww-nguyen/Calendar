#pragma once
#include "MyUnit.h"

class MyScheduleDay : public MyUnit
{
private:
	char type;

public:
	MyScheduleDay();

	// setters and getters
	void setType(char t);
	char getType() const;

	friend ostream& operator<< (ostream&, const MyScheduleDay&);

};
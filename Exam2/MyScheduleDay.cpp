#include "MyScheduleDay.h"

// PreCondition: N/A
// PostCondition: set the member to default
MyScheduleDay::MyScheduleDay() : MyUnit()
{
	type = 'U';
}

// PreCondition: type must be a char. Type can only be 'A', 'H', or 'P'
// PostCondition: set type to t
void MyScheduleDay::setType(char t)
{
	type = t;
}

// PreCondition: N/A
// PostCondition: return the type
char MyScheduleDay::getType() const
{
	return type;
}

// PreCondition: N/A
// PostCondition: overload the << operator
ostream& operator<< (ostream& out, const MyScheduleDay& obj)
{
	out << static_cast <MyUnit> (obj);
	out << "\n\tType            : " << obj.getType();
	return out;
}

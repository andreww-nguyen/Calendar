#include "MyUnit.h"

// PreCondition: N/A
// PostCondition: set the members to default
MyUnit::MyUnit()
{
	value = 0;
	strncpy_s(description, "unschedule", 99);
}

// PreCondition: value must be positive and an integer
// PostCondition: set value to v
void MyUnit::setValue(int v)
{
	value = v;
}

// PreCondition: N/A
// PostCondition: return the value
unsigned short MyUnit::getValue() const
{
	return value;
}

// PreCondition: description must be a string
// PostCondition: set description to d
void MyUnit::setDescription(string d)
{
	strncpy_s(description, d.c_str(), 99);
}

// PreCondition: N/A
// PostCondition: return the description
string MyUnit::getDescription() const
{
	return description;
}

// PreCondition: N/A
// PostCondition: overload the << operator
ostream& operator<< (ostream& out, const MyUnit& obj)
{
	out << "\n\tValue           : " << obj.getValue();
	out << "\n\tDescription     : " << obj.getDescription();

	return out;
}

#pragma once
#include <iostream>
#include <cstring>
#include <string>

using namespace std;
class MyUnit
{
private:
	unsigned short value;
	char description[100];

public:
	MyUnit();
	
	// setters and getters
	void setValue(int v);
	unsigned short getValue() const;
	void setDescription(string d);
	string getDescription() const;

	friend ostream& operator<< (ostream&, const MyUnit&);
};


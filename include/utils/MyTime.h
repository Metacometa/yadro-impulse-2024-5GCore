#pragma once
#include <string>
#include "MyException.h"

class MyTime
{
public:
	int hours;
	int minutes;

	MyTime(int hours_, int minutes_);
	MyTime(int minutes);
	MyTime(std::string time);
	MyTime();

	bool IsLater(MyTime time);
	bool IsEarlier(MyTime time);

	static MyTime Difference(MyTime yearlier_time, MyTime later_time);

	std::string ToString();
	int ToMinutes();
};


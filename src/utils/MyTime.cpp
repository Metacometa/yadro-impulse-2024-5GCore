#include "MyTime.h"

MyTime::MyTime(int hours_, int minutes_) : hours(hours_), minutes(minutes_) {}

MyTime::MyTime(int minutes) : MyTime(minutes / 60, minutes % 60)
{

}

MyTime::MyTime(std::string time)
{
	if (time.length() != 5)
	{
		throw MyException("Wrong time format");
	}

	for (size_t i = 0; i < 5; ++i)
	{
		if (i == 2)
		{
			if (time[i] != ':')
			{
				throw MyException("Wrong time format");
			}

			continue;
		}
		if (time[i] < '0' || time[i] > '9')
		{
			throw MyException("Wrong time format");
		}
	}

	hours = std::stoi(time.substr(0, 2));
	minutes = std::stoi(time.substr(3, 2));

	if (hours > 23 || minutes > 59)
	{
		throw MyException("Wrong time format");
	}

}

MyTime::MyTime()
{
	hours = 0;
	minutes = 0;
}

bool MyTime::IsLater(MyTime time)
{
	return this->ToMinutes() > time.ToMinutes();
}

bool MyTime::IsEarlier(MyTime time)
{
	return this->ToMinutes() < time.ToMinutes();
}

MyTime MyTime::Difference(MyTime yearlier_time, MyTime later_time)
{
	if (yearlier_time.IsLater(later_time))
	{
		throw MyException("Wrong time difference");
	}

	return MyTime(later_time.ToMinutes() - yearlier_time.ToMinutes());
}

std::string MyTime::ToString()
{
	std::string s_hours = std::to_string(hours);
	if (hours < 10)
	{
		s_hours = "0" + s_hours;
	}

	std::string s_minutes = std::to_string(minutes);
	if (minutes < 10)
	{
		s_minutes = "0" + s_minutes;
	}
	return s_hours + ":" + s_minutes;
}

int MyTime::ToMinutes()
{
	return hours * 60 + minutes;
}

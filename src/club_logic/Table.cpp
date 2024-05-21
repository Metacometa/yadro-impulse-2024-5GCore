#include "Table.h"

#include <iostream>
int Table::TimeToRevenuedHours(MyTime time)
{
	int additionalHour = 0;
	if (time.minutes > 0)
	{
		additionalHour = 1;
	}

	return time.hours + additionalHour;
}
Table::Table(int id_) : id(id_)
{
	busyTime = 0;
	revenuedHours = 0;
	state = TableState::Free;
	
	startTimeOfLastClient = MyTime(0);
}

Table::Table()
{
	id = 0;
	busyTime = 0;
	revenuedHours = 0;

	startTimeOfLastClient = MyTime(0);
	state = TableState::None;
}

void Table::ReleaseTable(MyTime releaseTime)
{
	MyTime busyTime_My_time = MyTime::Difference(startTimeOfLastClient, releaseTime).ToMinutes();
	busyTime += busyTime_My_time.ToMinutes();
	state = TableState::Free;

	revenuedHours += TimeToRevenuedHours(busyTime_My_time);
}

void Table::Take(MyTime takeTime)
{
	startTimeOfLastClient = takeTime;
	state = TableState::Busy;
}

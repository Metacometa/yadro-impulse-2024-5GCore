#pragma once
#include "MyTime.h"

class Table
{
	MyTime startTimeOfLastClient;

public:
	Table(int id_);
	Table();

	enum class TableState { None, Free, Busy };
	TableState state;

	void ReleaseTable(MyTime releaseTime);
	void Take(MyTime takeTime);
	int TimeToRevenuedHours(MyTime time);

	int id;
	int busyTime;
	int revenuedHours;
};


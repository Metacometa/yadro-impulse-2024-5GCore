#pragma once
#include "MyTime.h"
#include "MyException.h"

#include <string>
#include <sstream>

class EventValidator
{
public:
	MyTime time;
	int id;
	std::string client_name;

	int table_id;

	EventValidator(std::string event, int tables, MyTime LastEventTime, bool isFirstEvent = false);
	EventValidator();
};


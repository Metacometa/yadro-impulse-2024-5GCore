#include "EventValidator.h"

EventValidator::EventValidator(std::string event, int tables, MyTime LastEventTime, bool isFirstEvent)
{
	std::stringstream ss;
	ss << event;

	std::string s_time;

	ss >> s_time >> id >> client_name;
	time = MyTime(s_time);

	std::string s_table_id;
	ss >> s_table_id;

	if (s_table_id != "")
	{
		table_id = std::stoi(s_table_id);
	}
	else
	{
		table_id = -1;
	}

	for (auto& c : client_name)
	{
		if (!(c >= 'a' && c <= 'z') && !(c >= '0' && c <= '9'))
		{
			throw MyException(event); 
		}
	}

	if (!(1 <= id && id <= 4))
	{
		throw MyException(event);
	}
	
	if (isFirstEvent == false)
	{
		if (time.IsEarlier(LastEventTime))
		{
			throw MyException(event);
		}
	}

	if (table_id == -1)
	{
		return;
	}

	if (!(1 <= table_id && table_id <= tables))
	{
		throw MyException(event);
	}
}

EventValidator::EventValidator()
{
	time = MyTime(0);

	id = 0;
	client_name = "";
	table_id = 0;
}

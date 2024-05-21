#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "MyTime.h"
#include "MyException.h"
#include "ComputerClub.h"
#include "EventValidator.h"

void ReadEvents(ComputerClub& club, const int& tables, std::ifstream  &file)
{
	std::string temp;
	std::stringstream ss;

	bool isFirstEvent = true;
	MyTime LastEventTime(0, 0);

	std::getline(file, temp);

	EventValidator eventValidator;
	if (!file.is_open())
	{
		return;
	}

	while (std::getline(file, temp))
	{
		if (temp.empty())
		{
			break;
		}

		if (temp == "")
		{
			break;
		}

		try
		{
			if (isFirstEvent)
			{
				eventValidator = EventValidator(temp, tables, LastEventTime, isFirstEvent);;
				isFirstEvent = false;
			}
			else
			{
				eventValidator = EventValidator(temp, tables, LastEventTime);
			}
		}
		catch (MyException exception)
		{
			club.ClearLog();
			std::cout << temp << std::endl;
			return;
		}

		try
		{
			club.CallEvent(eventValidator.time, eventValidator.id, eventValidator.client_name, eventValidator.table_id);
		}
		catch (EmittedEvent event)
		{
			//std::cout << event.GetText() << std::endl;
		}

		LastEventTime = eventValidator.time;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Wrong arguments" << std::endl;
		return 0;
	}

	int tables;
	std::string temp;
	int costPerHour;

	std::ifstream in(argv[1]);

	if (!in.is_open())
	{
		return 0;
	}

	in >> tables;

	in >> temp;
	MyTime startTime(temp);

	in >> temp;
	MyTime endTime(temp);

	in >> costPerHour;

	ComputerClub club(tables, startTime, endTime, costPerHour);

	ReadEvents(club, tables, in);

	in.close();
	return 0;
}
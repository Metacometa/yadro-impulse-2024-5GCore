#include "ComputerClub.h"
#include <iostream>

void ComputerClub::ClientComes(MyTime time, std::string client_name)
{
	log.emplace_back(time.ToString() + " 1 " + client_name);

	if (this->startTime.IsLater(time))
	{
		this->CallEvent(time, 13, "NotOpenYet");
	}

	if (clients.find(client_name) != clients.end())
	{
		this->CallEvent(time, 13, "YouShallNotPass");
	}

	clients[client_name] = Client(client_name);
}

void ComputerClub::ClientSitsDown(MyTime time, std::string client_name, int table_id)
{
	log.emplace_back(time.ToString() + " 2 " + client_name + " " + std::to_string(table_id));

	if (clients.find(client_name) == clients.end())
	{
		this->CallEvent(time, 13, "ClientUnknown");
	}

	if (tables[table_id].state != Table::TableState::Free)
	{
		this->CallEvent(time, 13, "PlaceIsBusy");
	}

	if (clients[client_name].state == Client::ClientState::Sat)
	{
		tables[clients[client_name].table_id].ReleaseTable(time);
	}
	
	clients[client_name].TakeTable(table_id);
	tables[table_id].Take(time);
}

void ComputerClub::ClientLeaves(MyTime time, std::string client_name)
{
	log.emplace_back(time.ToString() + " 4 " + client_name);

	if (clients.find(client_name) == clients.end())
	{
		this->CallEvent(time, 13, "ClientUnknown");
	}

	if (clients[client_name].state == Client::ClientState::Sat)
	{
		int freeTableId = clients[client_name].table_id;
		tables[freeTableId].ReleaseTable(time);

		if (!clientsQueue.empty())
		{
			this->CallEvent(time, 12, clientsQueue.front(), freeTableId);

			clientsQueue.pop();
		}
	}
	removeFromQueue(client_name);
	clients.erase(client_name);
}

void ComputerClub::ClientWaits(MyTime time, std::string client_name)
{
	log.emplace_back(time.ToString() + " 3 " + client_name);

	if (clients.find(client_name) == clients.end())
	{
		this->CallEvent(time, 13, "ClientUnknown");
	}

	for (auto& table : tables)
	{
		if (table.second.state == Table::TableState::Free)
		{
			this->CallEvent(time, 13, "ICanWaitNoLonger");
		}
	}

	if (clientsQueue.size() == this->tablesNum)
	{
		this->CallEvent(time, 11, client_name);
		return;
	}

	clientsQueue.push(client_name);
	clients[client_name].state = Client::ClientState::Waitng;
}

void ComputerClub::removeFromQueue(std::string client_name)
{
	std::queue<std::string> temp;

	while (!clientsQueue.empty())
	{
		if (clientsQueue.front() != client_name)
		{
			temp.push(clientsQueue.front());
		}
		clientsQueue.pop();
	}

	while (!temp.empty())
	{
		clientsQueue.push(temp.front());
		temp.pop();
	}
}

void ComputerClub::OutcomingEventClientLeaves(MyTime time, std::string client_name)
{
	if (clients.find(client_name) != clients.end())
	{
		if (clients[client_name].state == Client::ClientState::Sat)
		{
			tables[clients[client_name].table_id].ReleaseTable(time);
		}

		clients.erase(client_name);
	}

	log.emplace_back(time.ToString() + " 11 " + client_name);
}

void ComputerClub::OutcomingEventClientSitsDown(MyTime time, std::string client_name, int table_id)
{
	clients[client_name].TakeTable(table_id);
	tables[table_id].Take(time);

	log.emplace_back(time.ToString() + " 12 " + client_name + " " + std::to_string(table_id));
}

void ComputerClub::Error(MyTime time, std::string error_mistake)
{
	log.emplace_back(time.ToString() + " 13 " + error_mistake);
	throw EmittedEvent("");
}

ComputerClub::ComputerClub(int tables_num_, MyTime start_time_, MyTime end_time_, int cost_per_hour_) :
	tablesNum(tables_num_), startTime(start_time_), endTime(end_time_), costPerHour(cost_per_hour_)
{
	log.emplace_back(startTime.ToString());

	for (size_t i = 0; i < this->tablesNum; ++i)
	{
		tables[i + 1] = Table(i + 1);
	}
}

ComputerClub::~ComputerClub()
{
	if (log.empty())
	{
		return;
	}

	for (auto it = clients.cbegin(); it != clients.cend();)
	{
		this->CallEvent(endTime, 11, (it++)->first);
	}

	log.emplace_back(endTime.ToString());
	for (auto& table : tables)
	{
		log.emplace_back(std::to_string(table.second.id) + " " + std::to_string(table.second.revenuedHours * costPerHour) + " " + MyTime(table.second.busyTime).ToString());
	}

	for (auto& line : log)
	{
		std::cout << line << std::endl;
	}
}

void ComputerClub::CallEvent(MyTime time, int eventId, std::string client_name, int table_id)
{
	switch (eventId)
	{
		case 1:
		{
			ClientComes(time, client_name);
			break;
		}
		case 2:
		{
			ClientSitsDown(time, client_name, table_id);
			break;
		}
		case 3:
		{
			ClientWaits(time, client_name);
			break;
		}
		case 4:
		{
			ClientLeaves(time, client_name);
			break;
		}
		case 11:
		{
			OutcomingEventClientLeaves(time, client_name);
			break;
		}
		case 12:
		{
			OutcomingEventClientSitsDown(time, client_name, table_id);
			break;
		}
		case 13:
		{
			Error(time, client_name);
			break;
		}
		default:
		{
			break;
		}
	}
}

void ComputerClub::ClearLog()
{
	log.clear();
}

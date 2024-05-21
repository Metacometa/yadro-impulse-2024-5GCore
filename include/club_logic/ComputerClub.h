#pragma once
#include "MyTime.h"
#include "Client.h"
#include "Table.h"
#include "EmittedEvent.h"
#include "MyException.h"

#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <queue>

class ComputerClub
{
	enum class TableState { None, Free, Busy };

	int tablesNum;
	MyTime startTime;
	MyTime endTime;
	int costPerHour;

	std::map<int, Table> tables;
	std::map<std::string, Client> clients;
	std::queue<std::string> clientsQueue;

	std::vector<std::string> log;

	void removeFromQueue(std::string client_name);

	void ClientComes(MyTime time, std::string client_name);
	void ClientSitsDown(MyTime time, std::string client_name, int table_id);
	void ClientLeaves(MyTime time, std::string client_name);
	void ClientWaits(MyTime time, std::string client_name);

	void OutcomingEventClientLeaves(MyTime time, std::string client_name);
	void OutcomingEventClientSitsDown(MyTime time, std::string client_name, int table_id);
	void Error(MyTime time, std::string error_text);
public:
	ComputerClub(int tables_num_, MyTime start_time_, MyTime end_time_, int cost_per_hour_);
	~ComputerClub();

	void CallEvent(MyTime time, int eventId, std::string client_name = "", int table_id = 0);
	void ClearLog();
};


#pragma once
#include <string>


class Client
{
	std::string name;

public:
	Client(std::string name_);
	Client();

	enum class ClientState { None, Come, Sat, Waitng };
	ClientState state;

	int table_id;

	void TakeTable(int table_id);
};


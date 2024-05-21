#include "Client.h"

Client::Client(std::string name_) : name(name_)
{
	state = ClientState::None;
	table_id = 0;
}

Client::Client()
{
	name = "";
	state = ClientState::Come;
	table_id = 0;
}

void Client::TakeTable(int table_id)
{
	this->table_id = table_id;
	state = ClientState::Sat;
}

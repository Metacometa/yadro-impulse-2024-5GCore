#pragma once
#include "MyException.h"

class EmittedEvent : public MyException
{
public:
	EmittedEvent(std::string text);
};


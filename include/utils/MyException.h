#pragma once
#include <string>

class MyException
{
	std::string text;

public:
	MyException(std::string text_);
	std::string GetText();
};


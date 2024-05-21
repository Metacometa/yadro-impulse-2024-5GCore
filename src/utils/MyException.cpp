#include "MyException.h"

MyException::MyException(std::string text_) : text(text_)
{
}

std::string MyException::GetText()
{
	return this->text;
}

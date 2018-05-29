#include "ServerMsgItem.h"

#include <sstream>

ServerMsgItem::ServerMsgItem(int x, int y)
{
	operation = OperationType::WALK;
	this->x = x;
	this->y = y;
}

ServerMsgItem::ServerMsgItem(int operation)
{
	this->operation = operation;
}

ServerMsgItem::~ServerMsgItem()
{
}

std::string ServerMsgItem::convertToString()
{
	std::stringstream ss;
	ss << "{{OperationType:" << operation << "}";
	switch (operation)
	{
	case OperationType::WALK:
		ss << "{x:";
		if (x < 10)
			ss << "0";
		ss << x << "}{y:";
		if (y < 10)
			ss << "0";
		ss << y << "}";
		break;
	default:
		break;
	}
	ss << "}";
	return ss.str();
}

int ServerMsgItem::getOperationFromString(std::string str)
{
	return str[16] - '0';
}

int ServerMsgItem::getXFromString(std::string str)
{
	if (OperationType::WALK != ServerMsgItem::getOperationFromString(str))
		throw "Error in conerting";
	return (str[21] - '0') * 10 + (str[22] - '0');
}

int ServerMsgItem::getYFromString(std::string str)
{
	if (OperationType::WALK != ServerMsgItem::getOperationFromString(str))
		throw "Error in conerting";
	return (str[27] - '0') * 10 + (str[28] - '0');
}
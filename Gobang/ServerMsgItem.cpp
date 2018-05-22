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
		ss << "{x:" << x << "}{y:" << y << "}";
		break;
	default:
		break;
	}
	ss << "}";
	return ss.str();
}
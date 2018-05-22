#ifndef SERVERMSGITEM_H
#define SERVERMSGITEM_H

#include <string>

class ServerMsgItem
{
public:
	ServerMsgItem(int x, int y);
	ServerMsgItem(int operation);
	~ServerMsgItem();

	std::string convertToString();

private:
	int operation;
	int x;
	int y;

};

const enum OperationType
{
	WALK,
	TIPS,
	RESTART,
	CHEAT,
	GIVEUP,
	ERROR,
	AGREE,
	DISAGREE
};

#endif // !SERVERMSGITEM_H
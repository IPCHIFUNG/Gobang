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
	static int getOperationFromString(std::string str);

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
	ERRORR,
	AGREE,
	DISAGREE
};

#endif // !SERVERMSGITEM_H
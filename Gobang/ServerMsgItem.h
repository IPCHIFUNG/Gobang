#ifndef SERVERMSGITEM_H
#define SERVERMSGITEM_H

#include <string>

class ServerMsgItem
{
public:
	ServerMsgItem(int x, int y);
	ServerMsgItem(int operation, int x, int y);
	~ServerMsgItem();

	std::string convertToString();
	static int getOperationFromString(std::string str);
	static int getXFromString(std::string str);
	static int getYFromString(std::string str);
	static int getxFromString(std::string str);
	static int getyFromString(std::string str);

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
	ERR,
	AGREE,
	DISAGREE
};

#endif // !SERVERMSGITEM_H
#ifndef QQFRIEND_H
#define QQFRIEND_H

#include"friend.h"
#include<string>
using namespace std;

class qqFriendNodeLA :public friendNodeLA {
private:
	int m_qqFriendId;
	string m_qqFriendNickName;

};


class qqFriendListLA {
private:
	qqFriendNodeLA* m_sentinel;

public:
	qqFriendListLA();
	virtual ~qqFriendListLA();
	
};
#endif // !QQFRIEND_H

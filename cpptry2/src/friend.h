#ifndef FRIEND_H
#define FRIEND_H

#include<string>
#include<vector>
#include"user.h"

class friendNodeLA {
protected:
	string m_commentName;//±¸×¢Ãû

public:
	friendNodeLA();
	virtual ~friendNodeLA();

};

class friendListLA {
private:
	friendNodeLA* m_sentinel;//ÉÚ±ø

public:
	friendListLA();
	virtual ~friendListLA();


	void addFriend(friendListLA* next);
	void deleteFriend(friendListLA* next);
	string getCommentName(userListLA* friendUser);
	void setCommentName(userListLA* friendUser, string commentName);

};
#endif // !FRIEND_H

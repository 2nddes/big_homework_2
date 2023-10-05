#ifndef QQUSER_H
#define QQUSER_H

#include<vector>
#include"user.h"

typedef struct userInfo{
	int friendId;
	string friendName;
}userInfo;

class qqUserNodeLA:public userOfApp {
public:
	qqUserNodeLA();
	qqUserNodeLA(int QQId, string name, string password,qqUserNodeLA* next);
	~qqUserNodeLA();

	bool isFriend(int friendId)const;
	bool isFriend(qqUserNodeLA* friendPtr)const;

	int getPlatformId()const override;
	vector<userInfo> getQQFriendInfo()const;
	vector<int> getQQGroupId()const;

	int getAppUserId()const override;
	string getUserName()const override;
	string getUserPasswd()const override;

	void setPlatformId(int platformId)override;
	void setAppUserId(int qqId)override;
	void setUserName(string qqName)override;
	void setUserPasswd(string qqPassword)override;

	void addQQFriendId(int friendId);//TODO:点对点通信
	void addQQGroupId(int groupId);

	void deleteQQFriendId(int friendId);//TODO:点对点通信
	void deleteQQGroupId(int groupId);

	void setNext(qqUserNodeLA* next);
	qqUserNodeLA* getNext()const;
private:
	int              m_qqId;//QQnumble
	string           m_qqName;
	string           m_qqPassword;

	vector<userInfo> m_qqFriendId;
	vector<int>      m_qqGroupId;


	qqUserNodeLA*    m_next;
};

class qqUserListLA {
public:
	qqUserListLA();
	~qqUserListLA();
	
	static qqUserNodeLA* findByQQId(int id);
	static qqUserNodeLA* findBySuperId(int id);
	static qqUserNodeLA* findBySuperPointer(userNodeLA* userToFind);

	qqUserNodeLA* addQQUser(string qqName,string qqPassword);
	void deleteQQUser(qqUserNodeLA* qqUserToDelete);
	void deleteQQUserByQQId(int qqId);
	void saveQQUserListData();
private:
	int                  m_qqUserCount;
	static qqUserNodeLA* m_sentinel;
};

#endif // !QQUSER_H
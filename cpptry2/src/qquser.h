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

	int getPlatformId()const override;
	int getAppUserId()const override;
	string getUserName()const override;
	string getUserPasswd()const override;

	void setPlatformId(int platformId)override;
	void setAppUserId(int qqId)override;
	void setUserName(string qqName)override;
	void setUserPasswd(string qqPassword)override;

	vector<userInfo> getQQFriendInfo()const;
	vector<int> getQQGroupId()const;

	void addQQFriendId(int friendId);//TODO:点对点通信
	void addQQGroupId(int groupId);

	void deleteQQFriendId(int friendId);//TODO:点对点通信
	void deleteQQGroupId(int groupId);

	void setNext(qqUserNodeLA* next);
	qqUserNodeLA* getNext()const;
private:
	int m_qqId;//QQnumble
	string m_qqName;
	string m_qqPassword;

	vector<userInfo> m_qqFriendId;
	vector<int> m_qqGroupId;

	qqUserNodeLA* m_next;
};

class qqUserListLA {
public:
	qqUserListLA();
	~qqUserListLA();
	
	static qqUserNodeLA* findByQQId(int id);
	static qqUserNodeLA* findBySuperId(int id);
	static qqUserNodeLA* findBySuperPointer(userNodeLA* userToFind);

	static qqUserNodeLA* addQQUser(string qqName,string qqPassword);
	static void deleteQQUser(qqUserNodeLA* qqUserToDelete);
	static void deleteQQUserByQQId(int qqId);
	static void saveQQUserList();
private:
	static qqUserNodeLA* m_sentinel;
	static int m_qqUserCount;
};

#endif // !QQUSER_H
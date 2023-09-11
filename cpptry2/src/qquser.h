#ifndef QQUSER_H
#define QQUSER_H

#include"user.h"

class qqUserNodeLA {
private:
	int m_platformId;//平台ID
	int m_qqId;
	string m_qqName;
	string m_qqPassword;

	vector<int> m_qqFriendId;
	vector<int> m_qqGroupId;

	qqUserNodeLA* m_next;
public:
	qqUserNodeLA();
	qqUserNodeLA(int QQId, string name, string password,qqUserNodeLA* next);
	~qqUserNodeLA();

	int getPlatformId();
	int getQQId(); 
	string getQQName();
	string getQQPassword();

	vector<int> getQQFriendId();
	vector<int> getQQGroupId();

	void addQQFriendId(int friendId);
	void addQQGroupId(int groupId);

	void deleteQQFriendId(int friendId);
	void deleteQQGroupId(int groupId);


	void setPlatformId(int platformId);
	void setQQId(int qqId);
	void setQQName(string qqName);
	void setQQPassword(string qqPassword);


	void setNext(qqUserNodeLA* next);
	qqUserNodeLA* getNext();
};

class qqUserListLA {
private:
	qqUserNodeLA* m_sentinel = nullptr;
	static int m_qqUserCount;

public:
	qqUserListLA();
	~qqUserListLA();
	
	qqUserNodeLA* findByQQId(int id);
	qqUserNodeLA* findBySuperId(int id);
	qqUserNodeLA* findBySuperPointer(userNodeLA* userToFind);

	qqUserNodeLA* addQQUser(string qqName,string qqPassword);
	void deleteQQUser(qqUserNodeLA* qqUserToDelete);
	void deleteQQUserByQQId(int qqId);
	void saveQQUserList();
};

#endif // !QQUSER_H
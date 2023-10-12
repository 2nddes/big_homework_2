#ifndef WECHATUSER_H
#define WECHATUSER_H

#include<vector>
#include"/project/C++Project/cpptry2/cpptry2/src/user.h"

class WeChatUserNodeLA :public userOfApp {
public:
	WeChatUserNodeLA();
	WeChatUserNodeLA(int WeChatId, string name, string password, WeChatUserNodeLA* next);
	~WeChatUserNodeLA();

	bool isFriend(int friendId)const;
	bool isFriend(WeChatUserNodeLA* friendPtr)const;
	bool isAddedGroup(int groupId)const;

	int getPlatformId()const override;
	vector<userInfo> getWeChatFriendInfo()const;
	vector<int> getWeChatGroupId()const;

	int getAppUserId()const override;
	string getUserName()const override;
	string getUserPasswd()const override;

	void setPlatformId(int platformId)override;
	void setAppUserId(int WeChatId)override;
	void setUserName(string WeChatName)override;
	void setUserPasswd(string WeChatPassword)override;

	void addWeChatFriendInfo(userInfo friendInfo);
	void addWeChatGroupId(int groupId);

	void deleteWeChatFriendId(int friendId);//TODO:点对点通信
	void deleteWeChatGroupId(int groupId);

	void setNext(WeChatUserNodeLA* next);
	WeChatUserNodeLA* getNext()const;
private:
	int              m_WeChatId = 0;//WeChatnumble
	string           m_WeChatName = "无";
	string           m_WeChatPassword = "0";

	vector<userInfo> m_WeChatFriendId;
	vector<int>      m_WeChatGroupId;


	WeChatUserNodeLA* m_next = nullptr;
};

class WeChatUserListLA {
public:
	WeChatUserListLA();
	~WeChatUserListLA();

	WeChatUserNodeLA* findByWeChatId(int id);
	WeChatUserNodeLA* findBySuperId(int id);
	WeChatUserNodeLA* findBySuperPointer(userNodeLA* userToFind);

	WeChatUserNodeLA* addWeChatUser(string WeChatName, string WeChatPassword);
	void deleteWeChatUser(WeChatUserNodeLA* WeChatUserToDelete);
	void deleteWeChatUserByWeChatId(int WeChatId);
	void saveWeChatUserListData();
	int size()const;
private:
	int           m_WeChatUserCount = 0;
	WeChatUserNodeLA* m_sentinel = nullptr;
};

#endif // !WECHATUSER_H
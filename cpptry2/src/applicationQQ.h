#ifndef APPLICATIONQQ_H
#define APPLICATIONQQ_H

#include"application.h"
#include"qquser.h"
#include"qqgroup.h"
#include"utils.h"

#include<Windows.h>
#include<io.h>
#include<direct.h>

class applicationQQLA :public applicationLA {
public:
	applicationQQLA();
	applicationQQLA(platformLA* platform);
	virtual ~applicationQQLA();

	string getAppName()const override;
	int getAppVersion()const override;

	//参数为平台用户,登录后返回qq用户,同时登录平台用户
	qqUserNodeLA* loginPage(userNodeLA*& curPlatformUser);
	qqUserNodeLA* registerPage(userNodeLA*& curPlatformUser);
	
	//TODO: add member function here
	void mainPage();

	void friendPage();
	void searchFriendPage();
	void addFriendPage();
	void deleteFriendPage();

	void groupPage();
	void searchGroupPage();
	void createGroupPage();
	void joinGroupPage();
	void quitGroupPage();
	void quitGroupPage(qqGroupNodeLA* groupPtr);
	void setGroupConfigPage(qqGroupNodeLA* groupPtr);
	void inviteFriendInPage(qqGroupNodeLA* groupPtr);

	void chatInGroupPage(qqGroupNodeLA* groupPtr);
	void chatWithFriendPage(qqUserNodeLA* friendPtr);
	
	void showQQFriendList(vector<userInfo> friendlist);
	void showQQGroupList(vector<int> grouplist);
	void showGroupMemberPage(int groupId);
	void showGroupMemberPage(qqGroupNodeLA* groupPtr);
	//TODO:显示聊天记录

	void applyFriend(qqUserNodeLA* user,qqUserNodeLA* friendToAdd);

	bool sendMsgToFriend(qqUserNodeLA* friendPtr,const char* msg);
	bool sendMsgToGroup(qqGroupNodeLA* groupPtr,const char* msg);
	
	//加载数据和初始界面
	void init(userNodeLA*& curPlatformUser)override;
	//清理加载的数据
	void exit()override;

private:

	qqUserNodeLA*  m_currentUser = nullptr;

	qqGroupListLA* m_allQQGroupList = nullptr;

	qqUserListLA*  m_allQQUserList = nullptr;

	platformLA*    m_platform = nullptr;
};

#endif // !APPLICATIONQQ_H
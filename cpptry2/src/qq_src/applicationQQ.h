#ifndef APPLICATIONQQ_H
#define APPLICATIONQQ_H

#include"/project/C++Project/cpptry2/cpptry2/src/application.h"
#include"qquser.h"
#include"qqgroup.h"
#include"/project/C++Project/cpptry2/cpptry2/src/utils.h"

#include<Windows.h>
#include<io.h>
#include<direct.h>

typedef struct QQMsgNodeLA {
	int senderId{};
	string senderName{};
	string time{};
	string msg{};
}QMsg;

class applicationQQLA :public applicationLA {
public:
	applicationQQLA();
	applicationQQLA(platformLA* platform);
	virtual ~applicationQQLA();

	string getAppName()const override;//获取应用名
	int getAppVersion()const override;//获取应用版本

	//参数为平台用户,登录后返回qq用户,同时登录平台用户
	qqUserNodeLA* loginPage(userNodeLA*& curPlatformUser);
	qqUserNodeLA* registerPage(userNodeLA*& curPlatformUser);
	
	void mainPage();

	void setUserInfoPage();//设置用户信息

	void friendPage();//好友根界面
	void selectFriendPage();//选择好友
	void sendMsgPage(qqUserNodeLA* friendPtr);
	void addFriendPage();//添加好友
	void deleteFriendPage();//删除好友
	void friendRequestPage();//批阅好友申请
	void chatWithFriendPage(qqUserNodeLA* friendPtr);//好友聊天界面

	void groupPage();//群根界面
	void selectGroupPage();//选择群
	void searchGroupPage();//搜索群
	void sendMsgPage(qqGroupNodeLA* groupPtr);//发送群消息
	void createGroupPage();//创建群
	void joinGroupPage();//加入群,在里面输入群号
	bool disbandGroupPage(qqGroupNodeLA* groupPtr);//解散群
	bool quitGroupPage();//退出群,在里面输入群号
	bool quitGroupPage(qqGroupNodeLA* groupPtr);//退出群
	void setGroupConfigPage(qqGroupNodeLA* groupPtr);//设置群配置
	void inviteFriendInPage(qqGroupNodeLA* groupPtr);//邀请好友进群
	void kickMemberPage(qqGroupNodeLA* groupPtr);//踢出群成员
	void groupRequestPage(qqGroupNodeLA* groupPtr);//批阅群申请
	void chatInGroupPage(qqGroupNodeLA* groupPtr);//群聊天界面
	void setAdminPage(qqGroupNodeLA* groupPtr);//设置管理员
	void setGroupNickNamePage(qqGroupNodeLA* groupPtr);//设置群昵称

	//TODO:匿名聊天
	void makeUserFile(string path);//创建用户文件

	void showQQFriendList(vector<userInfo> friendlist);//显示好友列表
	void showQQGroupList(vector<int> grouplist);//显示群列表
	void showGroupMemberPage(int groupId);//显示群成员
	void showGroupMemberPage(qqGroupNodeLA* groupPtr);//显示群成员
	//申请好友
	void applyFriend(qqUserNodeLA* user,qqUserNodeLA* friendToAdd);
	//发送好友消息
	bool sendMsgToFriend(qqUserNodeLA* friendPtr,const char* msg);
	//发群消息
	bool sendMsgToGroup(qqGroupNodeLA* groupPtr,const char* msg);
	
	vector<QMsg> recvMsgFromFriend(qqUserNodeLA* friendPtr);//接收好友消息
	vector<QMsg> recvMsgFromGroup(qqGroupNodeLA* groupPtr);//接收群消息

	void showMsg(vector<QMsg> m);//显示消息
	//加载数据和初始界面
	bool init(userNodeLA*& curPlatformUser)override;
	//清理加载的数据
	void exit()override;

private:
	qqUserNodeLA*  m_currentUser = nullptr;//当前用户

	qqGroupListLA* m_allQQGroupList = nullptr;//所有群列表

	qqUserListLA*  m_allQQUserList = nullptr;//所有用户列表

	platformLA*    m_platform = nullptr;//所在平台
};

#endif // !APPLICATIONQQ_H
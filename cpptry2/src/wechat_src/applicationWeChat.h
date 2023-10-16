#ifndef APPLICATIONWECHAT_H
#define APPLICATIONWECHAT_H

#include"/project/C++Project/cpptry2/cpptry2/src/application.h"
#include"WeChatuser.h"
#include"WeChatgroup.h"
#include"/project/C++Project/cpptry2/cpptry2/src/utils.h"

#include<Windows.h>
#include<io.h>
#include<direct.h>

typedef struct WECHATMsgNodeLA {
	int senderId{};
	string senderName{};
	string time{};
	string msg{};
}WMsg;

class applicationWeChatLA :public applicationLA {
public:
	applicationWeChatLA();
	applicationWeChatLA(platformLA* platform);
	virtual ~applicationWeChatLA();

	bool init(userNodeLA*& curPlatformUser)override;//加载数据和初始界面
	void exit()override;//清理加载的数据
	void mainPage() override;//主界面
	void loadData() override;//加载数据
	void logOut() override;//注销

	string getAppName()const override;//获取应用名
	int getAppVersion()const override;//获取应用版本

	//参数为平台用户,登录后返回WeChat用户,同时登录平台用户
	WeChatUserNodeLA* loginPage(userNodeLA*& curPlatformUser);
	WeChatUserNodeLA* registerPage(userNodeLA*& curPlatformUser);

	WeChatUserNodeLA* findBySuperPtr(userNodeLA* superPtr)const override;//通过父指针查找用户
	WeChatUserNodeLA* findByWeChatId(int id)const;

	void showPersonalInfoPage(WeChatUserNodeLA* userPtr)const;//显示个人信息

	void setUserInfoPage();//设置用户信息

	void friendPage();//好友根界面
	void selectFriendPage();//选择好友
	void sendMsgPage(WeChatUserNodeLA* friendPtr);
	void addFriendPage();//添加好友
	void deleteFriendPage();//删除好友
	bool deleteFriendPage(WeChatUserNodeLA* friendPtr);//删除好友
	void friendRequestPage();//批阅好友申请
	void chatWithFriendPage(WeChatUserNodeLA* friendPtr);//好友聊天界面
	void addExternQQFriendPage();//添加外部QQ好友
	void addBySearchFriendNamePage();//搜索好友
	void addByWeChatIdPage();//通过微信号添加好友
	void searchChatRecordPage(WeChatUserNodeLA* friendPtr);//搜索聊天记录

	void groupPage();//群根界面
	void selectGroupPage();//选择群
	void searchGroupPage();//搜索群
	void sendMsgPage(WeChatGroupNodeLA* groupPtr);//发送群消息
	void createGroupPage();//创建群
	void joinGroupPage();//加入群,在里面输入群号
	bool disbandGroupPage(WeChatGroupNodeLA* groupPtr);//解散群
	bool quitGroupPage();//退出群,在里面输入群号
	bool quitGroupPage(WeChatGroupNodeLA* groupPtr);//退出群
	void setGroupConfigPage(WeChatGroupNodeLA* groupPtr);//设置群配置
	void inviteFriendInPage(WeChatGroupNodeLA* groupPtr);//邀请好友进群
	void kickMemberPage(WeChatGroupNodeLA* groupPtr);//踢出群成员
	void groupRequestPage(WeChatGroupNodeLA* groupPtr);//批阅群申请
	void chatInGroupPage(WeChatGroupNodeLA* groupPtr);//群聊天界面
	void setAdminPage(WeChatGroupNodeLA* groupPtr);//设置管理员
	void setGroupNickNamePage(WeChatGroupNodeLA* groupPtr);//设置群昵称
	void searchChatRecordPage(WeChatGroupNodeLA* groupPtr);//搜索群聊天记录

private:
	void makeUserFile(string path);//创建用户文件

	void clearChatRecord(WeChatUserNodeLA* friendPtr);//清空聊天记录

	void clearChatRecord(WeChatGroupNodeLA* groupPtr);//清空聊天记录

	void showWeChatFriendList(const vector<userInfo>& friendlist);//显示好友列表
	void showWeChatGroupList(const vector<int>& grouplist);//显示群列表
	void showGroupMemberList(int groupId);//显示群成员
	void showGroupMemberList(WeChatGroupNodeLA* groupPtr);//显示群成员
	//申请好友
	void applyFriend(WeChatUserNodeLA* user, WeChatUserNodeLA* friendToAdd);
	//发送好友消息
	bool sendMsgToFriend(WeChatUserNodeLA* friendPtr, const char* msg);
	//发群消息
	bool sendMsgToGroup(WeChatGroupNodeLA* groupPtr, const char* msg);

	vector<WMsg> recvMsgFromFriend(WeChatUserNodeLA* friendPtr);//接收好友消息
	vector<WMsg> recvMsgFromGroup(WeChatGroupNodeLA* groupPtr);//接收群消息
	void loadUserFile();//加载用户文件
	void loadGroupFile();//加载群文件

	void showMsg(const vector<WMsg>& m);//显示消息
	
protected:
	WeChatUserNodeLA* m_currentUser = nullptr;//当前用户

	WeChatGroupListLA* m_allWeChatGroupList = nullptr;//所有群列表

	WeChatUserListLA* m_allWeChatUserList = nullptr;//所有用户列表

	platformLA* m_platform = nullptr;//所在平台
};

#endif // !APPLICATIONWECHAT_H
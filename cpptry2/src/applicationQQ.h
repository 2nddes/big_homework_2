#ifndef APPLICATIONQQ_H
#define APPLICATIONQQ_H

#include"application.h"
#include"qqfriend.h"
#include"qquser.h"
#include"qqgroup.h"

class applicationQQLA :public applicationLA {
private:
	qqUserNodeLA* m_currentUser = nullptr;

	qqGroupListLA* m_allQQGroupList = nullptr;

	qqUserListLA* m_allQQUserList = nullptr;
public:
	applicationQQLA();
	virtual ~applicationQQLA();

	//TODO: add member function here
	string getAppName()const override;
	int getAppVersion()const override;

	//参数为平台用户,登录后返回qq用户,同时登录平台用户
	qqUserNodeLA* loginPage(userNodeLA*& curPlatformUser);
	qqUserNodeLA* registerPage(userNodeLA*& curPlatformUser);

	//加载数据和初始界面
	void init(userNodeLA*& curPlatformUser)override;
	//清理加载的数据
	void exit()override;

};

#endif // !APPLICATIONQQ_H
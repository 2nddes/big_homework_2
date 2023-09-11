#ifndef PLATFORM_H
#define PLATFORM_H

#include<vector>
#include"user.h"
#include"application.h"

class platformLA {
private:
	//应用列表
	applicationListLA* m_applicationList = nullptr;
	//平台用户列表
	userListLA* m_userList = nullptr;
	//当前平台登录用户
	userNodeLA* m_currentUser = nullptr;

public:
	platformLA();
	virtual ~platformLA();

	void run();

};
#endif // !PLATFORM_H
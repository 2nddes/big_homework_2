#ifndef PLATFORM_H
#define PLATFORM_H

#include"application.h"
#include"user.h"

class platformLA {
private:
	
	applicationListLA* m_applicationList = nullptr;//应用列表
	
	userListLA* m_userList = nullptr;//平台用户列表
	
	userNodeLA* m_currentUser = nullptr;//当前平台登录用户

public:
	platformLA();
	virtual ~platformLA();

	void run();
	void findPlatformUser(int id);
	userNodeLA* addPlatformUser();
};
#endif // !PLATFORM_H
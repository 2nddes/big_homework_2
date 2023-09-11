#ifndef PLATFORM_H
#define PLATFORM_H

#include<vector>
#include"user.h"
#include"application.h"

class platformLA {
private:
	//Ӧ���б�
	applicationListLA* m_applicationList = nullptr;
	//ƽ̨�û��б�
	userListLA* m_userList = nullptr;
	//��ǰƽ̨��¼�û�
	userNodeLA* m_currentUser = nullptr;

public:
	platformLA();
	virtual ~platformLA();

	void run();

};
#endif // !PLATFORM_H
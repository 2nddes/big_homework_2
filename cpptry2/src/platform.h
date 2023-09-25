#ifndef PLATFORM_H
#define PLATFORM_H

#include"application.h"
#include"user.h"

class platformLA {
private:
	
	applicationListLA* m_applicationList = nullptr;//Ӧ���б�
	
	userListLA* m_userList = nullptr;//ƽ̨�û��б�
	
	userNodeLA* m_currentUser = nullptr;//��ǰƽ̨��¼�û�

public:
	platformLA();
	virtual ~platformLA();

	void run();
	void findPlatformUser(int id);
	userNodeLA* addPlatformUser();
};
#endif // !PLATFORM_H
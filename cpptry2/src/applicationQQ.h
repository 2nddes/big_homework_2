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

	//����Ϊƽ̨�û�,��¼�󷵻�qq�û�,ͬʱ��¼ƽ̨�û�
	qqUserNodeLA* loginPage(userNodeLA*& curPlatformUser);
	qqUserNodeLA* registerPage(userNodeLA*& curPlatformUser);

	//�������ݺͳ�ʼ����
	void init(userNodeLA*& curPlatformUser)override;
	//������ص�����
	void exit()override;

};

#endif // !APPLICATIONQQ_H
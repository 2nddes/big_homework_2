#ifndef APPLICATIONWEIBO_H
#define APPLICATIONWEIBO_H

#include"/project/C++Project/cpptry2/cpptry2/src/application.h"
#include"/project/C++Project/cpptry2/cpptry2/src/utils.h"

#include<Windows.h>
#include<io.h>
#include<direct.h>

class applicationWeiboLA :public applicationLA {
public:
	applicationWeiboLA();
	applicationWeiboLA(platformLA* platform);
	virtual ~applicationWeiboLA();

	bool init(userNodeLA*& curPlatformUser)override;//�������ݺ͵�¼����
	void exit()override;//������ص�����
	void loadData()override;//��������
	void logOut()override;//�ǳ�
	void mainPage()override;//������

	string getAppName()const override;//��ȡӦ����
	int getAppVersion()const override;//��ȡӦ�ð汾


};



#endif // !APPLICATIONWEIBO_H

#ifndef APPLICATION_H
#define APPLICATION_H

#include"user.h"
class platformLA;


class applicationLA {
protected:
	string m_appName;//Ӧ������
	int m_appVersion = 1;//Ӧ�ð汾
public:
	applicationLA* m_next = nullptr;

	applicationLA();
	virtual ~applicationLA();

	bool hasNext();
	applicationLA* getNext();

	virtual string getAppName()const;
	virtual int getAppVersion()const;
	virtual bool init(userNodeLA * & curPlatformUser);//��ʼ��(�����ļ�)
	virtual void mainPage();//������
	virtual void exit();

};

class applicationListLA {
private:
	applicationLA* m_sentinel;

	
public:
	applicationListLA();
	applicationListLA(platformLA* platform);
	~applicationListLA();
	
	applicationLA* getSentinel();
	applicationLA* at(int index);
	void showAllApp();
	int appCount();
};
#endif // !APPLICATION_H
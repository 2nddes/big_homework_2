#ifndef APPLICATION_H
#define APPLICATION_H

#include"user.h"
class platformLA;


class applicationLA {
public:
	applicationLA* m_next = nullptr;

	applicationLA();
	virtual ~applicationLA();

	bool hasNext()const;
	applicationLA* getNext()const;

	virtual string getAppName()const;
	virtual int getAppVersion()const;
	virtual bool init(userNodeLA * & curPlatformUser);//��ʼ��(�����ļ�)
	virtual void mainPage();//������
	virtual void loadData();//��������
	virtual void logOut();//�ǳ�
	virtual userNodeLA* findBySuperPtr(userNodeLA* superPtr)const;//ͨ����ָ������û�
	virtual void exit();

protected:
	string m_appName;//Ӧ������
	int m_appVersion = 1;//Ӧ�ð汾
};

class applicationListLA {
private:
	applicationLA* m_sentinel;
	
public:
	applicationListLA();
	applicationListLA(platformLA* platform);
	~applicationListLA();
	
	applicationLA* getSentinel()const;
	applicationLA* at(int index)const;
	void showAllApp()const;
	int appCount()const;
};
#endif // !APPLICATION_H
#ifndef APPLICATION_H
#define APPLICATION_H

#include"user.h"
class platformLA;


class applicationLA {
protected:
	string m_appName;//应用名字
	int m_appVersion = 1;//应用版本
public:
	applicationLA* m_next = nullptr;

	applicationLA();
	virtual ~applicationLA();

	bool hasNext();
	applicationLA* getNext();

	virtual string getAppName()const;
	virtual int getAppVersion()const;
	virtual bool init(userNodeLA * & curPlatformUser);//初始化(比如文件)
	virtual void mainPage();//主界面
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
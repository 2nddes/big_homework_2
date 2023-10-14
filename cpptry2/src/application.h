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
	virtual bool init(userNodeLA * & curPlatformUser);//初始化(比如文件)
	virtual void mainPage();//主界面
	virtual void loadData();//加载数据
	virtual void logOut();//登出
	virtual userNodeLA* findBySuperPtr(userNodeLA* superPtr)const;//通过父指针查找用户
	virtual void exit();

protected:
	string m_appName;//应用名字
	int m_appVersion = 1;//应用版本
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
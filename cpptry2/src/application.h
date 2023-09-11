#ifndef APPLICATION_H
#define APPLICATION_H
//应用类基类

#include<string>
#include"user.h"
using namespace std;

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
	virtual void init(userNodeLA * & curPlatformUser);//初始化(比如文件)
	virtual void draw();
	virtual void exit();

};

class applicationListLA {
private:
	applicationLA* m_sentinel;

public:
	applicationListLA();
	~applicationListLA();
	
	applicationLA* getSentinel();
	applicationLA* at(int index);
};
#endif // !APPLICATION_H
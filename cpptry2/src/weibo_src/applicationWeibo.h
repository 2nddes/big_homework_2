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

	bool init(userNodeLA*& curPlatformUser)override;//加载数据和登录事宜
	void exit()override;//清理加载的数据
	void loadData()override;//加载数据
	void logOut()override;//登出
	void mainPage()override;//主界面

	string getAppName()const override;//获取应用名
	int getAppVersion()const override;//获取应用版本


};



#endif // !APPLICATIONWEIBO_H

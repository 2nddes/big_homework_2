#include "applicationWeibo.h"
#include<iostream>

using namespace std;

applicationWeiboLA::applicationWeiboLA() {}

applicationWeiboLA::applicationWeiboLA(platformLA* platform) {}

applicationWeiboLA::~applicationWeiboLA() {}

bool applicationWeiboLA::init(userNodeLA*& curPlatformUser)
{
	return true;
}

void applicationWeiboLA::exit()
{

}

void applicationWeiboLA::loadData()
{

}

void applicationWeiboLA::logOut()
{

}

void applicationWeiboLA::mainPage()
{
	system("cls");
	cout << "            Weibo" << endl;
	cout << "______________________________" << endl;
	system("pause");
	return;
}

string applicationWeiboLA::getAppName() const
{
	return "Weibo";
}

int applicationWeiboLA::getAppVersion() const
{
	return 0;
}

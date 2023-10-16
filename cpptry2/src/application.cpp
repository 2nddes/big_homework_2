#include"utils.h"
#include"application.h"
#include"/project/C++Project/cpptry2/cpptry2/src/qq_src/applicationQQ.h"
#include"/project/C++Project/cpptry2/cpptry2/src/wechat_src/applicationWeChat.h"
#include"/project/C++Project/cpptry2/cpptry2/src/weibo_src/applicationWeibo.h"
#include<iostream>
#include<iomanip>

using namespace std;

/////////////////appList///////////////
applicationListLA::applicationListLA() {
	m_sentinel = new applicationLA();
	applicationLA* app = m_sentinel;

	app->m_next = new applicationQQLA();
	app=app->m_next;
	
	app->m_next = new applicationWeChatLA();
	app=app->m_next;

}

applicationListLA::applicationListLA(platformLA* platform) {
	m_sentinel = new applicationLA();
	applicationLA* app = m_sentinel;

	app->m_next = new applicationQQLA(platform);
	app = app->m_next;

	app->m_next = new applicationWeChatLA(platform);
	app=app->m_next;

	app->m_next = new applicationWeiboLA(platform);
}

applicationListLA::~applicationListLA() {
	while (m_sentinel != nullptr) {
		applicationLA* appToDel = m_sentinel;
		m_sentinel = m_sentinel->m_next;
		delete appToDel;
	}
}

applicationLA* applicationListLA::at(int index)const {
	if (index == 0)return nullptr;
	applicationLA* app = m_sentinel;
	for (int i = 0; i < index&&app!=nullptr; ++i) {
		app = app->m_next;
	}

	return app;
}

void applicationListLA::showAllApp()const
{
	applicationLA* app = this->getSentinel();
	int i = 0;

	while (app->hasNext()) {
		app = app->getNext();
		cout << "| ";
		cout << setw(2)
			<< setfill('0')
			<< setiosflags(ios::right)
			<< ++i << " ||";
		cout << resetiosflags(ios::right);
		cout << setw(26)
			<< setfill(' ')
			<< setiosflags(ios::left)
			<< app->getAppName() << "|" << endl;
	}
	cout << resetiosflags(ios::left);
}

int applicationListLA::appCount()const {
	applicationLA* app = this->getSentinel();
	int i = 0;

	while (app->hasNext()) {
		app = app->getNext();
		++i;
	}
	return i;
}

applicationLA* applicationListLA::getSentinel()const {
	return m_sentinel;
}
///////////////appList/////////////////

///////////////appNode/////////////////
applicationLA::applicationLA() {
	m_appName = "application";
}

applicationLA::~applicationLA() {

}

bool applicationLA::hasNext()const {
	return m_next != nullptr;
}

applicationLA* applicationLA::getNext()const {
	if (this == nullptr) {
		return nullptr;
	}
	return m_next;
}

string applicationLA::getAppName()const {
	return m_appName;
}

int applicationLA::getAppVersion()const {
	return m_appVersion;
}

bool applicationLA::init(userNodeLA*& curPlatformUser) {
	throw "�Ƿ����û�application��init()";
}

void applicationLA::mainPage()
{
	throw "�Ƿ����û�application��mainPage()";
}

void applicationLA::loadData()
{
	throw "�Ƿ����û�application��loadData()";
}

void applicationLA::logOut()
{
	throw "�Ƿ����û�application��logOut()";
}

userNodeLA* applicationLA::findBySuperPtr(userNodeLA* superPtr)const
{
	return nullptr;
}

void applicationLA::exit() {
	throw "�Ƿ����û�application��exit()";
}
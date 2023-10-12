#include"utils.h"
#include"application.h"
#include"applicationQQ.h"
#include<iostream>
#include<iomanip>

using namespace std;

/////////////////appList///////////////
applicationListLA::applicationListLA() {
	m_sentinel = new applicationLA();
	applicationLA* app = m_sentinel;

	app->m_next = new applicationQQLA();
	app=app->m_next;
	
	//app->next = new applicationWeChatLA();
	//app=app->next;

}

applicationListLA::applicationListLA(platformLA* platform) {
	m_sentinel = new applicationLA();
	applicationLA* app = m_sentinel;

	app->m_next = new applicationQQLA(platform);
	app = app->m_next;

	//app->next = new applicationWeChatLA();
	//app=app->next;
}

applicationListLA::~applicationListLA() {
	while (m_sentinel != nullptr) {
		applicationLA* appToDel = m_sentinel;
		m_sentinel = m_sentinel->m_next;
		delete appToDel;
	}
}

applicationLA* applicationListLA::at(int index) {
	applicationLA* app = m_sentinel;
	for (int i = 0; i < index&&app!=nullptr; ++i) {
		app = app->m_next;
	}

	return app;
}

void applicationListLA::showAllApp()
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

int applicationListLA::appCount()
{
	applicationLA* app = this->getSentinel();
	int i = 0;

	while (app->hasNext()) {
		app = app->getNext();
		++i;
	}
	return i;
}

applicationLA* applicationListLA::getSentinel() {
	return m_sentinel;
}
///////////////appList/////////////////

///////////////appNode/////////////////
applicationLA::applicationLA() {
	m_appName = "application";
}

applicationLA::~applicationLA() {

}

bool applicationLA::hasNext() {
	return m_next != nullptr;
}

applicationLA* applicationLA::getNext() {
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
	throw "非法调用基application的init()";
}

void applicationLA::mainPage()
{
	throw "非法调用基application的mainPage()";
}

void applicationLA::exit() {
	throw "非法调用基application的exit()";
}
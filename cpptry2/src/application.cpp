#include"utils.h"
#include"application.h"
#include"applicationQQ.h"

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

void applicationLA::init(userNodeLA*& curPlatformUser) {
	throw "非法调用基application的init()";
}

void applicationLA::draw() {
	throw "非法调用基application的draw()";
}

void applicationLA::exit() {
	throw "非法调用基application的exit()";
}
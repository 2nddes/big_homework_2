#include<iostream>
#include"platform.h"
using namespace std;

platformLA::platformLA() {
	m_userList = new userListLA();
	m_userList->loadUserList();//(���ļ�)�����û��б�
	m_applicationList = new applicationListLA();//����Ӧ���б�
	
}

platformLA::~platformLA() {
	delete m_userList;
	delete m_applicationList;
}

void platformLA::run() {
	applicationLA* app = m_applicationList->getSentinel();
	
	while(1)
	{
		int i = 0;
		while (app->hasNext()) {
			app = app->getNext();
			cout << app->getAppName() << " ";
			cout << ++i << endl;
		}
		cout << "choose app to launch(input 0 to exit)" << endl;
		cin >> i;
		if (i == 0) {
			return;
		}
		m_applicationList->at(i)->init(m_currentUser);//��̬
	}


}
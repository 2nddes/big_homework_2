#include"utils.h"
#include<iostream>
#include"platform.h"
using namespace std;

platformLA::platformLA() {
	m_userList = new userListLA();
	m_userList->loadUserList();//(���ļ�)�����û��б�
	m_applicationList = new applicationListLA(this);//����Ӧ���б�
	
}

platformLA::~platformLA() {
	delete m_userList;
	delete m_applicationList;
}

void platformLA::run() {
	
	while(1){
		system("cls");
		applicationLA* app = m_applicationList->getSentinel();
		int i = 0;
		while (app->hasNext()) {
			app = app->getNext();
			cout << app->getAppName() << " ";
			cout << ++i << endl;
		}
		cout << "choose app to launch(input 0 to exit)" << endl;
		cin >> i;
		refreshInput();
		if (i == 0) {
			m_userList->saveUserList();
			return;
		}
		if (m_applicationList->at(i) != nullptr){
			m_applicationList->at(i)->init(m_currentUser);//��̬
		}
		else {
			cout << "no such app" << endl;
			system("pause");
		}
	}

}

void platformLA::findPlatformUser(int id) {
	m_currentUser = m_userList->findByUserId(id);

}

userNodeLA* platformLA::addPlatformUser() {
	return m_userList->addUser();
}
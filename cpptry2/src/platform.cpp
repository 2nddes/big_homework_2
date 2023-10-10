#include"utils.h"
#include<iomanip>
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
		cout << "        ��ӭʹ����Ѷƽ̨" << endl;
		cout << "_________________________________" << endl;
		m_applicationList->showAllApp();
		int count = m_applicationList->appCount();
		cout << "| ";
		cout << setw(2)
			<< setfill('0')
			<< setiosflags(ios::right)
			<< ++count;
		cout << resetiosflags(ios::right);
		cout << " ||���ø�������              |" << endl;
		cout << "| 00 ||�˳�                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "����ѡ��:";
		int i = -1;
		cin >> i;
		refreshInput();
		if (i == 0) {
			m_userList->saveUserList();
			return;
		}
		if (i <= m_applicationList->appCount()){
			//��̬
			bool flag = m_applicationList->at(i)->init(m_currentUser);
			m_userList->saveUserList();
			if (flag == true) 
				m_applicationList->at(i)->mainPage();
		}
		else if (i == m_applicationList->appCount() + 1) {
			setPlatformUserInfo();
		}
		else {
			cout << "ѡ�����" << endl;
			system("pause");
		}
		m_userList->saveUserList();
	}

}

void platformLA::findPlatformUser(int id) {
	m_currentUser = m_userList->findByUserId(id);
}

userNodeLA* platformLA::addPlatformUser() {
	return m_userList->addUser();
}

void platformLA::setPlatformUserInfo()
{
	if (m_currentUser == nullptr) {
		cout << "���ȵ�¼" << endl;
		system("pause");
		return;
	}
	while (1) {
		system("cls");
		cout << "1.�޸��û���" << endl;
		cout << "2.�޸�����" << endl;
		cout << "3.�޸ĵ绰" << endl;
		cout << "4.�޸�����" << endl;
		cout << "5.�޸ĵ�ַ" << endl;
		cout << "0.�˳�" << endl;
		int i = -1;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "���������û���,ֱ�ӻس�����:";
			string name;
			getline(cin, name);
			if (name == "") {
				continue;
			}
			m_currentUser->setUserName(name);
			m_userList->saveUserList();
		}
		else if (i == 2) {
			cout << "������������,��ʽ��:20200808,ֱ�ӻس�����:";
			int bday = dateInput();
			m_currentUser->setBirth(bday);
			m_userList->saveUserList();
		}
		else if (i == 3) {
			cout << "�������µ绰,ֱ�ӻس�����:";
			string phone;
			getline(cin, phone);
			if (phone == "") {
				continue;
			}
			m_currentUser->setPhone(phone);
			m_userList->saveUserList();
		}
		else if (i == 4) {
			cout << "������������,ֱ�ӻس�����:";
			string email;
			getline(cin, email);
			if (email == "") {
				continue;
			}
			m_currentUser->setEmail(email);
			m_userList->saveUserList();
		}
		else if (i == 5) {
			cout << "�������µ�ַ,ֱ�ӻس�����:";
			string address;
			getline(cin, address);
			if (address == "") {
				continue;
			}
			m_currentUser->setAddress(address);
			m_userList->saveUserList();
		}
		else if (i == 0) {
			return;
		}
		else {
			cout << "ѡ�����" << endl;
			system("pause");
		}
	}
}

void platformLA::logOut()
{
	m_currentUser = nullptr;
}
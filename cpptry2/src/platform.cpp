#include"utils.h"
#include<iomanip>
#include<iostream>
#include"platform.h"
using namespace std;

platformLA::platformLA() {
	m_userList = new userListLA();
	m_userList->loadUserList();//(从文件)加载用户列表
	m_applicationList = new applicationListLA(this);//加载应用列表
	
}

platformLA::~platformLA() {
	delete m_userList;
	delete m_applicationList;
}

void platformLA::run() {
	
	while(1){
		system("cls");
		cout << "        欢迎使用腾讯平台" << endl;
		cout << "_________________________________" << endl;
		m_applicationList->showAllApp();
		int count = m_applicationList->appCount();
		cout << "| ";
		cout << setw(2)
			<< setfill('0')
			<< setiosflags(ios::right)
			<< ++count;
		cout << resetiosflags(ios::right);
		cout << " ||设置个人资料              |" << endl;
		cout << "| 00 ||退出                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "输入选项:";
		int i = -1;
		cin >> i;
		refreshInput();
		if (i == 0) {
			m_userList->saveUserList();
			return;
		}
		if (i <= m_applicationList->appCount()){
			//多态
			bool flag = m_applicationList->at(i)->init(m_currentUser);
			m_userList->saveUserList();
			if (flag == true) 
				m_applicationList->at(i)->mainPage();
		}
		else if (i == m_applicationList->appCount() + 1) {
			setPlatformUserInfo();
		}
		else {
			cout << "选项不存在" << endl;
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
		cout << "请先登录" << endl;
		system("pause");
		return;
	}
	while (1) {
		system("cls");
		cout << "1.修改用户名" << endl;
		cout << "2.修改生日" << endl;
		cout << "3.修改电话" << endl;
		cout << "4.修改邮箱" << endl;
		cout << "5.修改地址" << endl;
		cout << "0.退出" << endl;
		int i = -1;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "请输入新用户名,直接回车返回:";
			string name;
			getline(cin, name);
			if (name == "") {
				continue;
			}
			m_currentUser->setUserName(name);
			m_userList->saveUserList();
		}
		else if (i == 2) {
			cout << "请输入新生日,格式例:20200808,直接回车返回:";
			int bday = dateInput();
			m_currentUser->setBirth(bday);
			m_userList->saveUserList();
		}
		else if (i == 3) {
			cout << "请输入新电话,直接回车返回:";
			string phone;
			getline(cin, phone);
			if (phone == "") {
				continue;
			}
			m_currentUser->setPhone(phone);
			m_userList->saveUserList();
		}
		else if (i == 4) {
			cout << "请输入新邮箱,直接回车返回:";
			string email;
			getline(cin, email);
			if (email == "") {
				continue;
			}
			m_currentUser->setEmail(email);
			m_userList->saveUserList();
		}
		else if (i == 5) {
			cout << "请输入新地址,直接回车返回:";
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
			cout << "选项不存在" << endl;
			system("pause");
		}
	}
}

void platformLA::logOut()
{
	m_currentUser = nullptr;
}
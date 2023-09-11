#include"applicationQQ.h"
#include<iostream>


applicationQQLA::applicationQQLA() {
	
}

applicationQQLA::~applicationQQLA() {
	
}

string applicationQQLA::getAppName()const {
	return "QQ";
}

int applicationQQLA::getAppVersion()const {
	return m_appVersion;
}

void applicationQQLA::init(userNodeLA*& curPlatformUser) {
	m_allQQGroupList = new qqGroupListLA();

	m_allQQUserList = new qqUserListLA();

	if (curPlatformUser == nullptr) {
		m_currentUser = loginPage(curPlatformUser);
	}
	else {
		if (curPlatformUser->isQQEnabled()) {
			m_currentUser = m_allQQUserList->findBySuperPointer(curPlatformUser);
		}
		else {
			cout << "平台用户 "
				<< curPlatformUser->getUserName() 
				<< " 未开通QQ服务,是否开通" << endl;
			cout << "1.开通" << endl;
			cout << "2.不开通" << endl;
			int i = 2;
			cin >> i;
			if (i == 1) {
				m_currentUser = registerPage(curPlatformUser);
				if(m_currentUser == nullptr) {
					exit();
					return;
				}
				else {
					curPlatformUser->setQQStatus(true);
				}
			}
			else {
				exit();
				return;

			}
		}
	}
	//TODO
	//载入所有群组信息
	//载入所有qq用户信息
	//qq个人好友信息和群组信息保存在个人结构体内
	//考虑封装好友信息和群组信息为容器再保存在qq用户结构体内

}

qqUserNodeLA* applicationQQLA::loginPage(userNodeLA*& curPlatformUser) {
	while(m_currentUser == nullptr)
	{
		cout << "QQ登录按1,注册QQ按2,退出按3" << endl;
		int i = 0;
		cin >> i;
		if (i == 2) {
			m_currentUser = registerPage(curPlatformUser);
		}
		else if (i == 3) {
			exit();
			return nullptr;
		}
	}

	cout << "请输入QQ号" << endl;
	int qqNumber;
	cin >> qqNumber;
	cout << "请输入密码" << endl;
	string password;
	cin >> password;

	qqUserNodeLA* qqUser = m_allQQUserList->findByQQId(qqNumber);
	if (qqUser == nullptr) {
		cout << "QQ号不存在" << endl;
		return nullptr;
	}
	else {
		if (qqUser->getQQPassword() == password) {
			cout << "登录成功" << endl;
			return qqUser;
		}
		else {
			cout << "密码错误" << endl;
			return nullptr;
		}
	}
}

qqUserNodeLA* applicationQQLA::registerPage(userNodeLA*& curPlatformUser) {
	cout << "QQ注册任意键(建议先登录其他已有服务再进行QQ注册) 退出1" << endl;
	int i = 0;
	cin >> i;
	if (i == 1)
		return nullptr;

	cout << "输入昵称" << endl;
	string userName;
	cin >> userName;
	cout << "输入密码" << endl;
	string password;
	cin >> password;
	cout << "确认注册按1" << endl;
	i = 0;
	cin >> i;
	if(i == 1) {
		return m_allQQUserList->addQQUser(userName,password);
	}
	else {
		cout << "取消注册" << endl;
		return nullptr;
	}
}

void applicationQQLA::exit() {
	cout << "正在退出QQ" << endl;

	delete m_allQQGroupList;
	delete m_allQQUserList;
}
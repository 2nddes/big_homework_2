#define _CRT_SECURE_NO_WARNINGS
#include"/project/C++Project/cpptry2/cpptry2/src/utils.h"
#include"applicationQQ.h"
#include"/project/C++Project/cpptry2/cpptry2/src/platform.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<random>

applicationQQLA::applicationQQLA() {
	My_mkdir("QQ");
	m_appVersion = 1;
	m_allQQGroupList = nullptr;
	m_allQQUserList = nullptr;
	m_currentUser = nullptr;
}

applicationQQLA::applicationQQLA(platformLA* platform) {
	My_mkdir("QQ");
	m_appVersion = 1;
	m_allQQGroupList = nullptr;
	m_allQQUserList = nullptr;
	m_currentUser = nullptr;
	this->m_platform = platform;
}

applicationQQLA::~applicationQQLA() {}

string applicationQQLA::getAppName()const {
	return "QQ";
}

int applicationQQLA::getAppVersion()const {
	return m_appVersion;
}

bool applicationQQLA::init(userNodeLA*& curPlatformUser) {
	system("cls");

	loadData();

	while(1)
	{
		if (curPlatformUser == nullptr) {
			m_currentUser = loginPage(curPlatformUser);
			if (m_currentUser == nullptr) {
				exit();
				return false;
			}
			else {
				makeUserFile("QQ\\" + to_string(m_currentUser->getAppUserId()));
				return true;
			}
		}
		else {
			if (curPlatformUser->isQQEnabled()) {
				m_currentUser = m_allQQUserList->findBySuperPointer(curPlatformUser);
				makeUserFile("QQ\\" + to_string(m_currentUser->getAppUserId()));
				return true;
			}
			else {
				cout << "平台用户" << curPlatformUser->getUserName() << " 未开通QQ服务" << endl;
				cout << "__________________________________" << endl;
				cout << "| 01 || 开通QQ服务                |" << endl;
				cout << "|其他|| 退出QQ                    |" << endl;
				cout << "__________________________________" << endl;
				int i = 2;
				cin >> i;
				refreshInput();
				if (i == 1) {
					m_currentUser = registerPage(curPlatformUser);
					if (m_currentUser == nullptr) {
						exit();
						return false;
					}
					else {
						curPlatformUser->setQQStatus(true);
						string path = "QQ\\" + to_string(m_currentUser->getAppUserId());
						makeUserFile(path);
						return true;
					}
				}
				else {
					exit();
					return false;
				}
			}
		}
	}
	return false;
}

void applicationQQLA::loadUserFile()
{
	m_allQQUserList = new qqUserListLA();
}

void applicationQQLA::loadGroupFile()
{
	m_allQQGroupList = new qqGroupListLA();
}

void applicationQQLA::loadData() {
	loadUserFile();
	loadGroupFile();
}

void applicationQQLA::logOut()
{
	m_currentUser = nullptr;
}

qqUserNodeLA* applicationQQLA::loginPage(userNodeLA*& curPlatformUser) {
	while(m_currentUser == nullptr)
	{
		system("cls");
		cout << "             QQ登录" << endl;
		cout << "___________________________________" << endl;
		cout << "| 01 || 登录QQ                    |" << endl;
		cout << "| 02 || 注册QQ                    |" << endl;
		cout << "| 00 || 退出QQ                    |" << endl;
		cout << "__________________________________" << endl;
		cout << "输入选项:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1)
		{
			cout << "请输入QQ号:";
			int qqNumber = -1;
			cin >> qqNumber;
			refreshInput();

			qqUserNodeLA* qqUser = m_allQQUserList->findByQQId(qqNumber);
			if (qqUser == nullptr) {
				cout << "QQ号不存在,请检查输入" << endl;
				system("pause");
				continue;
			}

			cout << "请输入密码:" ;
			string password;
			cin >> password;
			refreshInput();

			if (qqUser->getUserPasswd() == password) {
				curPlatformUser = m_platform->findPlatformUser(qqUser->getPlatformId());
				system("cls");
				cout << "登录成功!"<< endl
					<< "欢迎回来," << qqUser->getUserName() << endl;
				system("pause");
				return qqUser;
			}
			else {
				cout << "密码错误" << endl;
				system("pause");
				continue;
			}
		}
		else if (i == 2) {
			m_currentUser = registerPage(curPlatformUser);
			continue;
		}
		else if (i == 0) {
			return nullptr;
		}

		else {
			cout << "输入错误" << endl;
			system("pause");
			continue;
		}
	}
	return m_currentUser;
}

qqUserNodeLA* applicationQQLA::registerPage(userNodeLA*& curPlatformUser) {
	while(1)
	{
		system("cls");
		cout << "             QQ注册" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || 注册QQ                   |" << endl;
		cout << "| 00 || 退出QQ                   |" << endl;
		cout << "__________________________________" << endl;
		cout << "输入选项:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 0)
			return nullptr;

		cout << "输入昵称(不含空格等特殊字符):";
		string userName;
		cin >> userName;
		refreshInput();
		cout << "输入密码(不含空格等特殊字符):";
		string password;
		cin >> password;
		refreshInput();
		int id = m_allQQUserList->size() + 1;
		system("cls");
		cout << "             QQ注册" << endl;
		cout << "__________________________________" << endl;
		cout << "|QQ号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << id << "|" << endl;
		cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << userName << "|" << endl;
		cout << "|密码|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << password << "|" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || 确认注册                  |" << endl;
		cout << "| 00 || 取消注册                  |" << endl;
		cout << "__________________________________" << endl;
		cout << "输入选项:";

		i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			if (curPlatformUser == nullptr) {
				curPlatformUser = m_platform->addPlatformUser();
				curPlatformUser->setQQStatus(true);
				qqUserNodeLA* p = m_allQQUserList->addQQUser(userName, password);
				p->setPlatformId(curPlatformUser->getPlatformId());
				m_allQQUserList->saveQQUserListData();

				cout << "注册成功!" << endl;
				system("pause");
				return p;
			}
			else {
				qqUserNodeLA* p = m_allQQUserList->addQQUser(userName, password);
				p->setPlatformId(curPlatformUser->getPlatformId());
				curPlatformUser->setQQStatus(true);
				m_allQQUserList->saveQQUserListData();
				return p;
			}
		}
		else if (i == 0) {
			cout << "取消注册" << endl;
			system("pause");
			return nullptr;
		}
		else {
			cout << "输入错误" << endl;
			system("pause");
			continue;
		}
	}
}

void applicationQQLA::exit() {
	m_allQQGroupList->saveGroupListData();
	delete m_allQQGroupList;
	m_allQQUserList->saveQQUserListData();
	delete m_allQQUserList;
}

qqUserNodeLA* applicationQQLA::findBySuperPtr(userNodeLA* superPtr)const
{
	return m_allQQUserList->findBySuperPointer(superPtr);
}

qqUserNodeLA* applicationQQLA::findByQQId(int id)const
{
	return m_allQQUserList->findByQQId(id);
}

void applicationQQLA::mainPage() {
	while (1) {
		system("cls");
		cout << "             QQ" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || 好友                      |" << endl;
		cout << "| 02 || 群组                      |" << endl;
		cout << "| 03 || 个人资料设置              |" << endl;
		cout << "| 04 || 退出登录                  |" << endl;
		cout << "| 00 || 退出                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "输入选项:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			friendPage();
		}
		else if (i == 2) {
			groupPage();
		}
		else if (i == 3) {
			setUserInfoPage();
		}
		else if (i == 4) {
			m_platform->logOut();
			exit();
			return;
		}
		else if (i == 0) {
			exit();
			return;
		}
		else {
			cout << "输入错误" << endl;
			system("pause");
			continue;
		}
	}
}

void applicationQQLA::setUserInfoPage()
{
	while (1)
	{
		system("cls");
		cout << "             个人资料设置" << endl;
		cout << "__________________________________" << endl;
		cout << "|QQ号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_currentUser->getAppUserId() << "|" << endl;
		cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_currentUser->getUserName() << "|" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || 修改昵称                  |" << endl;
		cout << "| 02 || 修改密码                  |" << endl;
		cout << "| 00 || 返回                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "输入选项:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "输入新昵称(不含空格等特殊字符):" << endl;
			string name;
			cin >> name;
			refreshInput();

			m_currentUser->setUserName(name);
			m_allQQUserList->saveQQUserListData();
			system("cls");
			cout << "修改成功" << endl;
			cout << "新昵称为:" << m_currentUser->getUserName() << endl;
			system("pause");
			continue;
		}
		else if (i == 2) {
			cout << "输入旧密码(不含空格等特殊字符):";
			string password;
			cin >> password;
			refreshInput();
			if (password != m_currentUser->getUserPasswd()) {
				cout << "密码错误" << endl;
				system("pause");
				continue;
			}
			cout << "输入新密码(不含空格等特殊字符):";
			cin >> password;
			refreshInput();

			m_currentUser->setUserPasswd(password);
			m_allQQUserList->saveQQUserListData();
			system("cls");
			cout << "修改成功" << endl;
			cout << "新密码为:" << m_currentUser->getUserPasswd() << endl;
			system("pause");
			continue;
		}
		else if (i == 0) {
			return;
		}
		else {
			cout << "输入错误" << endl;
			system("pause");
			continue;
		}
	}
}

void applicationQQLA::makeUserFile(string path)const {
	//创建用户文件夹
	My_mkdir(path.c_str());

	//创建好友请求列表文件
	//文件存在则不覆盖原文件
	My_mkfile(path.c_str(), "friendrequest.dat");
	
	//创建好友聊天记录文件夹
	My_mkdir((path + "\\chatrecord").c_str());
	//创建群聊记录文件夹
	My_mkdir((path + "\\groupchatrecord").c_str());

}
//TODO:color
void applicationQQLA::showMsg(const vector<QMsg>& m) {
	if (m.size() == 0) {
		cout << "            目前无消息" << endl;
		cout << "__________________________________" << endl;
		return;
	}
	for (int i = 0; i < m.size(); i++) {
		if (m_currentUser->getAppUserId() == m[i].senderId) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
			cout << "我 " << "("<<m[i].time<<")" << endl;
			cout << m[i].msg << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
		}
		else {
			cout << m[i].senderName << "(" << m[i].time << ")" << endl
				<< m[i].msg << endl;

		}
		cout << "__________________________________" << endl;
	}
}
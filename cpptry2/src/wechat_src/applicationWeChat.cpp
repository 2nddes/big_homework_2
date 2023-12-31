#define _CRT_SECURE_NO_WARNINGS
#include"/project/C++Project/cpptry2/cpptry2/src/utils.h"
#include"applicationWeChat.h"
#include"/project/C++Project/cpptry2/cpptry2/src/platform.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<random>

applicationWeChatLA::applicationWeChatLA() {
	My_mkdir("WeChat");
	m_appVersion = 1;
	m_allWeChatGroupList = nullptr;
	m_allWeChatUserList = nullptr;
	m_currentUser = nullptr;
}

applicationWeChatLA::applicationWeChatLA(platformLA* platform) {
	My_mkdir("WeChat");
	m_appVersion = 1;
	m_allWeChatGroupList = nullptr;
	m_allWeChatUserList = nullptr;
	m_currentUser = nullptr;
	this->m_platform = platform;
}

applicationWeChatLA::~applicationWeChatLA() {}

string applicationWeChatLA::getAppName()const {
	return "WeChat";
}

int applicationWeChatLA::getAppVersion()const {
	return m_appVersion;
}

bool applicationWeChatLA::init(userNodeLA*& curPlatformUser) {
	system("cls");

	loadData();

	while (1)
	{
		if (curPlatformUser == nullptr) {
			m_currentUser = loginPage(curPlatformUser);
			if (m_currentUser == nullptr) {
				exit();
				return false;
			}
			else {
				makeUserFile("WeChat\\" + to_string(m_currentUser->getAppUserId()));
				return true;
			}
		}
		else {
			if (curPlatformUser->isWeChatEnabled()) {
				m_currentUser = m_allWeChatUserList->findBySuperPointer(curPlatformUser);
				makeUserFile("WeChat\\" + to_string(m_currentUser->getAppUserId()));
				return true;
			}
			else {
				cout << "平台用户" << curPlatformUser->getUserName() << " 未开通WeChat服务" << endl;
				cout << "__________________________________" << endl;
				cout << "| 01 || 开通WeChat服务           |" << endl;
				cout << "|其他|| 退出WeChat               |" << endl;
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
						curPlatformUser->setWeChatStatus(true);
						string path = "WeChat\\" + to_string(m_currentUser->getAppUserId());
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

void applicationWeChatLA::loadUserFile() {
	m_allWeChatUserList = new WeChatUserListLA();
}

void applicationWeChatLA::loadGroupFile() {
	m_allWeChatGroupList = new WeChatGroupListLA();
}

void applicationWeChatLA::loadData() {
	loadUserFile();
	loadGroupFile();
}

void applicationWeChatLA::logOut()
{
	m_currentUser = nullptr;
}

WeChatUserNodeLA* applicationWeChatLA::loginPage(userNodeLA*& curPlatformUser) {
	while (m_currentUser == nullptr)
	{
		system("cls");
		cout << "             WeChat登录" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || 登录WeChat                |" << endl;
		cout << "| 02 || 注册WeChat                |" << endl;
		cout << "| 00 || 退出WeChat                |" << endl;
		cout << "__________________________________" << endl;
		cout << "输入选项:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1)
		{
			cout << "请输入WeChat号:";
			int WeChatNumber = -1;
			cin >> WeChatNumber;
			refreshInput();

			WeChatUserNodeLA* WeChatUser = m_allWeChatUserList->findByWeChatId(WeChatNumber);
			if (WeChatUser == nullptr) {
				cout << "WeChat号不存在,请检查输入" << endl;
				system("pause");
				continue;
			}

			cout << "请输入密码:";
			string password;
			cin >> password;
			refreshInput();

			if (WeChatUser->getUserPasswd() == password) {
				curPlatformUser = m_platform->findPlatformUser(WeChatUser->getPlatformId());
				system("cls");
				cout << "登录成功!" << endl
					<< "欢迎回来," << WeChatUser->getUserName() << endl;
				system("pause");
				return WeChatUser;
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

WeChatUserNodeLA* applicationWeChatLA::registerPage(userNodeLA*& curPlatformUser) {
	while (1)
	{
		system("cls");
		cout << "             WeChat注册" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || 注册WeChat                |" << endl;
		cout << "| 00 || 退出WeChat                |" << endl;
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
		int id = m_allWeChatUserList->size() + 1;
		system("cls");
		cout << "             WeChat注册" << endl;
		cout << "__________________________________" << endl;
		cout << "|微号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << id << "|" << endl;
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
				curPlatformUser->setWeChatStatus(true);
				WeChatUserNodeLA* p = m_allWeChatUserList->addWeChatUser(userName, password);
				p->setPlatformId(curPlatformUser->getPlatformId());
				m_allWeChatUserList->saveWeChatUserListData();

				cout << "注册成功!" << endl;
				system("pause");
				return p;
			}
			else {
				WeChatUserNodeLA* p = m_allWeChatUserList->addWeChatUser(userName, password);
				p->setPlatformId(curPlatformUser->getPlatformId());
				curPlatformUser->setWeChatStatus(true);
				m_allWeChatUserList->saveWeChatUserListData();
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

WeChatUserNodeLA* applicationWeChatLA::findBySuperPtr(userNodeLA* superPtr)const
{
	return m_allWeChatUserList->findBySuperPointer(superPtr);
}

WeChatUserNodeLA* applicationWeChatLA::findByWeChatId(int id)const
{
	return m_allWeChatUserList->findByWeChatId(id);
}

void applicationWeChatLA::showPersonalInfoPage(WeChatUserNodeLA* user) const
{
	cout << "          个人信息" << endl;
	cout << "__________________________________" << endl;
	cout << "|微号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << user->getAppUserId() << "|" << endl;
	cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << user->getUserName() << "|" << endl;
	cout << "__________________________________" << endl;
	system("pause");
	return;
}

void applicationWeChatLA::exit() {
	m_allWeChatGroupList->saveGroupListData();
	delete m_allWeChatGroupList;
	m_allWeChatUserList->saveWeChatUserListData();
	delete m_allWeChatUserList;
}

void applicationWeChatLA::mainPage() {
	while (1) {
		system("cls");
		cout << "             WeChat" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || 好友                      |" << endl;
		cout << "| 02 || 群组                      |" << endl;
		cout << "| 03 || 个人资料设置              |" << endl;
		cout << "| 04 || 退出登录                  |" << endl;
		cout << "| 00 || 退出WeChat                |" << endl;
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
	}
}

void applicationWeChatLA::setUserInfoPage()
{
	while (1)
	{
		system("cls");
		cout << "             个人资料设置" << endl;
		cout << "__________________________________" << endl;
		cout << "|微号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_currentUser->getAppUserId() << "|" << endl;
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
			m_allWeChatUserList->saveWeChatUserListData();
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
			m_allWeChatUserList->saveWeChatUserListData();
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

void applicationWeChatLA::makeUserFile(string path) {
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

void applicationWeChatLA::clearChatRecord(WeChatUserNodeLA* friendPtr)
{
	string path = "WeChat\\" + to_string(m_currentUser->getAppUserId()) + "\\chatrecord\\" + to_string(friendPtr->getAppUserId()) + ".dat";
	//判断文件是否存在,不存在则创建
	if (_access(path.c_str(), 0) == -1) {
		ofstream outFile;
		outFile.open(path, ios::out);
		outFile.close();
	}
	ofstream ofs(path, ios::out);
	if (!ofs.is_open()) {
		cout << "打开文件失败" << endl;
		return;
	}
	ofs.close();
}

void applicationWeChatLA::clearChatRecord(WeChatGroupNodeLA* groupPtr)
{
	string path = "WeChat\\" + to_string(m_currentUser->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupPtr->getGroupId()) + ".dat";
	if (_access(path.c_str(), 0) != -1) {
		remove(path.c_str());
	}
	return;
}
//TODO:color
void applicationWeChatLA::showMsg(const vector<WMsg>& m) {
	if (m.size() == 0) {
		cout << "            目前无消息" << endl;
		return;
	}
	for (int i = 0; i < m.size(); i++) {
		if (m_currentUser->getAppUserId() == m[i].senderId) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
			cout << "我 " << "(" << m[i].time << ")" << endl;
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
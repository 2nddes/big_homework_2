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

	m_allWeChatGroupList = new WeChatGroupListLA();

	m_allWeChatUserList = new WeChatUserListLA();
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
				cout << "ƽ̨�û� "
					<< curPlatformUser->getUserName()
					<< " δ��ͨWeChat����,�Ƿ�ͨ" << endl;
				cout << "1.��ͨ" << endl;
				cout << "0.����ͨ" << endl;
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
				else if (i == 0) {
					exit();
					return false;
				}
				else {
					cout << "�������" << endl;
					system("pause");
					return false;
				}
			}
		}
	}
	return false;
}
//doing/////////////////////////////////////////////////
WeChatUserNodeLA* applicationWeChatLA::loginPage(userNodeLA*& curPlatformUser) {
	while (m_currentUser == nullptr)
	{
		system("cls");
		cout << "             WeChat��¼" << endl;
		cout << "_________________________________" << endl;
		cout << "| 01 || ��¼WeChat                |" << endl;
		cout << "| 02 || ע��WeChat                |" << endl;
		cout << "| 00 || �˳�WeChat                |" << endl;
		cout << "_________________________________" << endl;
		cout << "����ѡ��:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1)
		{
			cout << "������WeChat��:";
			int WeChatNumber = -1;
			cin >> WeChatNumber;
			refreshInput();

			WeChatUserNodeLA* WeChatUser = m_allWeChatUserList->findByWeChatId(WeChatNumber);
			if (WeChatUser == nullptr) {
				cout << "WeChat�Ų�����,��������" << endl;
				system("pause");
				continue;
			}

			cout << "����������(�����ո�������ַ�):";
			string password;
			cin >> password;
			refreshInput();

			if (WeChatUser->getUserPasswd() == password) {
				system("cls");
				cout << "��¼�ɹ�!" << endl
					<< "��ӭ����," << WeChatUser->getUserName() << endl;
				system("pause");
				return WeChatUser;
			}
			else {
				cout << "�������" << endl;
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
			cout << "�������" << endl;
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
		cout << "             WeChatע��" << endl;
		cout << "_________________________________" << endl;
		cout << "| 01 || ע��WeChat                |" << endl;
		cout << "| 00 || �˳�WeChat                |" << endl;
		cout << "_________________________________" << endl;
		cout << "����ѡ��:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 0)
			return nullptr;

		cout << "�����ǳ�(�����ո�������ַ�):";
		string userName;
		cin >> userName;
		refreshInput();
		cout << "��������(�����ո�������ַ�):";
		string password;
		cin >> password;
		refreshInput();
		int id = m_allWeChatUserList->size() + 1;
		system("cls");
		cout << "             WeChatע��" << endl;
		cout << "_________________________________" << endl;
		cout << "|΢��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << id << "|" << endl;
		cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << userName << "|" << endl;
		cout << "|����|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << password << "|" << endl;
		cout << "_________________________________" << endl;
		cout << "| 01 || ȷ��ע��                  |" << endl;
		cout << "| 00 || ȡ��ע��                  |" << endl;
		cout << "_________________________________" << endl;
		cout << "����ѡ��:";

		i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			if (curPlatformUser == nullptr) {
				curPlatformUser = m_platform->addPlatformUser();
				curPlatformUser->setWeChatStatus(true);
				WeChatUserNodeLA* p = m_allWeChatUserList->addWeChatUser(userName, password);
				p->setPlatformId(curPlatformUser->getID());
				m_allWeChatUserList->saveWeChatUserListData();

				cout << "ע��ɹ�!" << endl;
				system("pause");
				return p;
			}
			else {
				WeChatUserNodeLA* p = m_allWeChatUserList->addWeChatUser(userName, password);
				p->setPlatformId(curPlatformUser->getID());
				m_allWeChatUserList->saveWeChatUserListData();
				return p;
			}
		}
		else if (i == 0) {
			cout << "ȡ��ע��" << endl;
			system("pause");
			return nullptr;
		}
		else {
			cout << "�������" << endl;
			system("pause");
			continue;
		}
	}
}

void applicationWeChatLA::exit() {
	m_allWeChatGroupList->saveGroupListData();
	delete m_allWeChatGroupList;
	m_allWeChatUserList->saveWeChatUserListData();
	delete m_allWeChatUserList;
	cout << "���˳�WeChat" << endl;
	system("pause");
}

void applicationWeChatLA::mainPage() {
	while (1) {
		system("cls");
		cout << "             WeChat" << endl;
		cout << "_________________________________" << endl;
		cout << "| 01 || ����                      |" << endl;
		cout << "| 02 || Ⱥ��                      |" << endl;
		cout << "| 03 || ������������              |" << endl;
		cout << "| 04 || �˳���¼                  |" << endl;
		cout << "| 00 || �˳�                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "����ѡ��:";

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
			m_currentUser = nullptr;
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
		cout << "             ������������" << endl;
		cout << "_________________________________" << endl;
		cout << "|΢��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_currentUser->getAppUserId() << "|" << endl;
		cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_currentUser->getUserName() << "|" << endl;
		cout << "_________________________________" << endl;
		cout << "| 01 || �޸��ǳ�                  |" << endl;
		cout << "| 02 || �޸�����                  |" << endl;
		cout << "| 00 || ����                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "����ѡ��:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "�������ǳ�(�����ո�������ַ�,ֱ�ӻس�����):" << endl;
			string name;
			cin >> name;
			refreshInput();
			if (name == "") {
				continue;
			}
			m_currentUser->setUserName(name);
			m_allWeChatUserList->saveWeChatUserListData();
			system("cls");
			cout << "�޸ĳɹ�" << endl;
			cout << "���ǳ�Ϊ:" << m_currentUser->getUserName() << endl;
			system("pause");
			continue;
		}
		else if (i == 2) {
			cout << "���������(�����ո�������ַ�):";
			string password;
			cin >> password;
			refreshInput();
			if (password != m_currentUser->getUserPasswd()) {
				cout << "�������" << endl;
				system("pause");
				continue;
			}
			cout << "����������(�����ո�������ַ�,ֱ�ӻس�����):";
			cin >> password;
			refreshInput();
			if (password == "") {
				continue;
			}
			m_currentUser->setUserPasswd(password);
			m_allWeChatUserList->saveWeChatUserListData();
			system("cls");
			cout << "�޸ĳɹ�" << endl;
			cout << "������Ϊ:" << m_currentUser->getUserPasswd() << endl;
			system("pause");
			continue;
		}
		else if (i == 0) {
			return;
		}
		else {
			cout << "�������" << endl;
			system("pause");
			continue;
		}
	}
}

void applicationWeChatLA::makeUserFile(string path) {
	//�����û��ļ���
	My_mkdir(path.c_str());

	//�������������б��ļ�
	//�ļ������򲻸���ԭ�ļ�
	My_mkfile(path.c_str(), "friendrequest.dat");

	//�������������¼�ļ���
	My_mkdir((path + "\\chatrecord").c_str());
	//����Ⱥ�ļ�¼�ļ���
	My_mkdir((path + "\\groupchatrecord").c_str());

}
//TODO:color
void applicationWeChatLA::showMsg(vector<WMsg> m) {
	if (m.size() == 0) {
		cout << "            Ŀǰ����Ϣ" << endl;
		return;
	}
	for (int i = 0; i < m.size(); i++) {
		if (m_currentUser->getAppUserId() == m[i].senderId) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
			cout << "�� " << "(" << m[i].time << ")" << endl;
			cout << m[i].msg << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
		}
		else {
			cout << m[i].senderName << "(" << m[i].time << ")" << endl
				<< m[i].msg << endl;

		}
	}
}
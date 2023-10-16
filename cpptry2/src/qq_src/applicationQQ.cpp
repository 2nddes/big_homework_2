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
				cout << "ƽ̨�û�" << curPlatformUser->getUserName() << " δ��ͨQQ����" << endl;
				cout << "__________________________________" << endl;
				cout << "| 01 || ��ͨQQ����                |" << endl;
				cout << "|����|| �˳�QQ                    |" << endl;
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
		cout << "             QQ��¼" << endl;
		cout << "___________________________________" << endl;
		cout << "| 01 || ��¼QQ                    |" << endl;
		cout << "| 02 || ע��QQ                    |" << endl;
		cout << "| 00 || �˳�QQ                    |" << endl;
		cout << "__________________________________" << endl;
		cout << "����ѡ��:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1)
		{
			cout << "������QQ��:";
			int qqNumber = -1;
			cin >> qqNumber;
			refreshInput();

			qqUserNodeLA* qqUser = m_allQQUserList->findByQQId(qqNumber);
			if (qqUser == nullptr) {
				cout << "QQ�Ų�����,��������" << endl;
				system("pause");
				continue;
			}

			cout << "����������:" ;
			string password;
			cin >> password;
			refreshInput();

			if (qqUser->getUserPasswd() == password) {
				curPlatformUser = m_platform->findPlatformUser(qqUser->getPlatformId());
				system("cls");
				cout << "��¼�ɹ�!"<< endl
					<< "��ӭ����," << qqUser->getUserName() << endl;
				system("pause");
				return qqUser;
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

qqUserNodeLA* applicationQQLA::registerPage(userNodeLA*& curPlatformUser) {
	while(1)
	{
		system("cls");
		cout << "             QQע��" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || ע��QQ                   |" << endl;
		cout << "| 00 || �˳�QQ                   |" << endl;
		cout << "__________________________________" << endl;
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
		int id = m_allQQUserList->size() + 1;
		system("cls");
		cout << "             QQע��" << endl;
		cout << "__________________________________" << endl;
		cout << "|QQ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << id << "|" << endl;
		cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << userName << "|" << endl;
		cout << "|����|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << password << "|" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || ȷ��ע��                  |" << endl;
		cout << "| 00 || ȡ��ע��                  |" << endl;
		cout << "__________________________________" << endl;
		cout << "����ѡ��:";

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

				cout << "ע��ɹ�!" << endl;
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
		cout << "| 01 || ����                      |" << endl;
		cout << "| 02 || Ⱥ��                      |" << endl;
		cout << "| 03 || ������������              |" << endl;
		cout << "| 04 || �˳���¼                  |" << endl;
		cout << "| 00 || �˳�                      |" << endl;
		cout << "__________________________________" << endl;
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
			exit();
			return;
		}
		else if (i == 0) {
			exit();
			return;
		}
		else {
			cout << "�������" << endl;
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
		cout << "             ������������" << endl;
		cout << "__________________________________" << endl;
		cout << "|QQ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_currentUser->getAppUserId() << "|" << endl;
		cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_currentUser->getUserName() << "|" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || �޸��ǳ�                  |" << endl;
		cout << "| 02 || �޸�����                  |" << endl;
		cout << "| 00 || ����                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "����ѡ��:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "�������ǳ�(�����ո�������ַ�):" << endl;
			string name;
			cin >> name;
			refreshInput();

			m_currentUser->setUserName(name);
			m_allQQUserList->saveQQUserListData();
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
			cout << "����������(�����ո�������ַ�):";
			cin >> password;
			refreshInput();

			m_currentUser->setUserPasswd(password);
			m_allQQUserList->saveQQUserListData();
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

void applicationQQLA::makeUserFile(string path)const {
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
void applicationQQLA::showMsg(const vector<QMsg>& m) {
	if (m.size() == 0) {
		cout << "            Ŀǰ����Ϣ" << endl;
		cout << "__________________________________" << endl;
		return;
	}
	for (int i = 0; i < m.size(); i++) {
		if (m_currentUser->getAppUserId() == m[i].senderId) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
			cout << "�� " << "("<<m[i].time<<")" << endl;
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
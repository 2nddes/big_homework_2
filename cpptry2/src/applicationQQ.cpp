#define _CRT_SECURE_NO_WARNINGS
#include"utils.h"
#include"applicationQQ.h"
#include"platform.h"
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

	m_allQQGroupList = new qqGroupListLA();

	m_allQQUserList = new qqUserListLA();
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
				cout << "ƽ̨�û� "
					<< curPlatformUser->getUserName()
					<< " δ��ͨQQ����,�Ƿ�ͨ" << endl;
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
						curPlatformUser->setQQStatus(true);
						string path = "QQ\\" + to_string(m_currentUser->getAppUserId());
						makeUserFile(path);
						return true;
					}
				}
				else if(i == 0) {
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
qqUserNodeLA* applicationQQLA::loginPage(userNodeLA*& curPlatformUser) {
	while(m_currentUser == nullptr)
	{
		system("cls");
		cout << "             QQ��¼" << endl;
		cout << "_________________________________" << endl;
		cout << "| 01 || ��¼QQ                    |" << endl;
		cout << "| 02 || ע��QQ                    |" << endl;
		cout << "| 00 || �˳�QQ                    |" << endl;
		cout << "_________________________________" << endl;
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

			cout << "����������:" << endl;
			string password;
			cin >> password;
			refreshInput();

			if (qqUser->getUserPasswd() == password) {
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
		cout << "_________________________________" << endl;
		cout << "| 01 || ע��QQ                    |" << endl;
		cout << "| 00 || �˳�QQ                    |" << endl;
		cout << "_________________________________" << endl;

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 0)
			return nullptr;

		cout << "�����ǳ�" << endl;
		string userName;
		cin >> userName;
		refreshInput();
		cout << "��������" << endl;
		string password;
		cin >> password;
		refreshInput();
		cout << "             QQע��" << endl;
		cout << "_________________________________" << endl;
		cout << "|�ǳ�|| " << setw(26) << setiosflags(ios::left) << userName << "|" << endl;
		cout << "|����|| " << setw(26) << setiosflags(ios::left) << password << "|" << endl;
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
				curPlatformUser->setQQStatus(true);
				qqUserNodeLA* p = m_allQQUserList->addQQUser(userName, password);
				p->setPlatformId(curPlatformUser->getID());
				m_allQQUserList->saveQQUserListData();

				cout << "ע��ɹ�!" << endl;
				cout << "����QQ��Ϊ:" << p->getAppUserId() << endl;
				cout << "��������Ϊ:" << p->getUserPasswd() << endl;
				system("pause");
				return p;
			}
			else {
				qqUserNodeLA* p = m_allQQUserList->addQQUser(userName, password);
				p->setPlatformId(curPlatformUser->getID());
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
	cout << "���˳�QQ" << endl;
	system("pause");
}

void applicationQQLA::mainPage() {
	while (1) {
		system("cls");
		cout << "             QQ" << endl;
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

void applicationQQLA::setUserInfoPage()
{
	while (1)
	{
		system("cls");
		cout << "             ������������" << endl;
		cout << "_________________________________" << endl;
		cout << "|QQ��|| " << setw(26) << setiosflags(ios::left) << m_currentUser->getAppUserId() << "|" << endl;
		cout << "|�ǳ�|| " << setw(26) << setiosflags(ios::left) << m_currentUser->getUserName() << "|" << endl;
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
			cout << "�������ǳ�:";
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
			cout << "����������:";
			string password;
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

//////////////////////////////////////////////////////
void applicationQQLA::friendPage() {
	while (1) {
		system("cls");
		cout << "           ����" << endl;
		cout << "_________________________________" << endl;
		showQQFriendList(m_currentUser->getQQFriendInfo());

		cout << "| 01 || ѡ�����                  |" << endl;
		cout << "| 02 || ��Ӻ���                  |" << endl;
		cout << "| 03 || ɾ������                  |" << endl;
		cout << "| 04 || �鿴��������              |" << endl;
		cout << "| 00 || ����                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "����ѡ��:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			selectFriendPage();
		}
		else if (i == 2) {
			addFriendPage();
		}
		else if (i == 3) {
			deleteFriendPage();
		}
		else if (i == 4) {
			friendRequestPage();
		}
		else if (i == 0) {
			return;
		}
	}
}

void applicationQQLA::selectFriendPage() {
	system("cls");
	cout<<"           ����" << endl;
	cout << "_________________________________" << endl;
	showQQFriendList(m_currentUser->getQQFriendInfo());
	if(m_currentUser->getQQFriendInfo().size() == 0) {
		system("pause");
		return;
	}
	cout << "�������QQ��:";
	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	if (m_currentUser->isFriend(qqNumber)) {
		chatWithFriendPage(m_allQQUserList->findByQQId(qqNumber));
	}
	else {
		cout << "δ�ҵ�����" << endl;
		system("pause");
		return;
	}
}

void applicationQQLA::sendMsgPage(qqUserNodeLA* friendPtr)
{
	cout << "ֱ�ӻس�����;������Ϣ�س�����:" << endl;
	char message[300];
	memset(message, 0, 300);
	cin.getline(message, 300);
	if (message[0] == '\0') {
		return;
	}
	(sendMsgToFriend(friendPtr, message))
		? cout << "���ͳɹ�" << endl
		: cout << "����ʧ��" << endl;
}

void applicationQQLA::addFriendPage() {
	system("cls");
	cout<<"         ��Ӻ���" << endl;
	//TODO:�Ƽ�����//////////////////////////////////////
	cout << "_________________________________" << endl;
	cout << "����Ҫ��ӵ�QQ��:" << endl;
	int id;
	cin >> id;
	refreshInput();
	if (id == m_currentUser->getAppUserId())
	{
		cout << "�㲻������Լ�Ϊ����" << endl;
		system("pause");
		return;
	}

	qqUserNodeLA* friendToAddPtr = m_allQQUserList->findByQQId(id);
	if (friendToAddPtr == nullptr) {
		cout<<"�û�������"<<endl;
		system("pause");
		return;
	}
	if (m_currentUser->isFriend(friendToAddPtr)) {
		cout<<"�Ѿ��Ǻ���"<<endl;
		system("pause");
		return;
	}
	cout << "          �û���Ϣ" << endl;
	cout << "_________________________________" << endl;
	cout << "| QQ��|| " << setw(26) << setiosflags(ios::left) << friendToAddPtr->getAppUserId() << "|" << endl;
	cout << "| �ǳ�|| " << setw(26) << setiosflags(ios::left) << friendToAddPtr->getUserName() << "|" << endl;
	cout << "_________________________________" << endl;
	cout << "| 01 || ��������                  |" << endl;
	cout << "| 00 || ȡ��                      |" << endl;
	cout << "_________________________________" << endl;
	cout << "����ѡ��:";
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		applyFriend(m_currentUser, friendToAddPtr);
		cout << "��������ɹ�" << endl;
		system("pause");
		return;
	}
	else if (i == 0) {
		cout << "ȡ�����" << endl;
		system("pause");
		return;
	}
	else {
		cout << "�������" << endl;
		system("pause");
		return;
	}
	
}

void applicationQQLA::deleteFriendPage() {
	system("cls");
	cout << "           ɾ������" << endl;
	cout << "_________________________________" << endl;
	showQQFriendList(m_currentUser->getQQFriendInfo());
	if(m_currentUser->getQQFriendInfo().size() == 0) {
		system("pause");
		return;
	}
	cout << "�����ɾ������QQ��:" << endl;
	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	if(qqNumber==m_currentUser->getAppUserId()) {
		cout << "����ɾ���Լ�" << endl;
		system("pause");
		return;
	}
	int i = 0;
	for (i = 0; i < m_currentUser->getQQFriendInfo().size(); i++) {
		if (m_currentUser->getQQFriendInfo()[i].friendId == qqNumber) {
			cout << "          �û���Ϣ" << endl;
			cout << "_________________________________" << endl;
			cout << "| QQ��|| " << setw(26) << setiosflags(ios::left) << m_allQQUserList->findByQQId(qqNumber)->getAppUserId() << "|" << endl;
			cout << "| �ǳ�|| " << setw(26) << setiosflags(ios::left) << m_allQQUserList->findByQQId(qqNumber)->getUserName() << "|" << endl;
			cout << "_________________________________" << endl;
			cout << "| 01 || ȷ��ɾ��                  |" << endl;
			cout << "| 00 || ȡ��                      |" << endl;
			cout << "_________________________________" << endl;
			cout << "����ѡ��:";

			int i = 0;
			cin >> i;
			refreshInput();
			if (i == 1) {
				//����ɾ������
				m_allQQUserList->findByQQId(qqNumber)->deleteQQFriendId(m_currentUser->getAppUserId());
				m_currentUser->deleteQQFriendId(qqNumber);
				m_allQQUserList->saveQQUserListData();
				cout << "ɾ���ɹ�" << endl;
			}
			else if ( i == 0) {
				cout << "ȡ��ɾ��" << endl;
			}
			else {
				cout << "�������" << endl;
			}
			system("pause");
			return;
		}
	}
	if (i == m_currentUser->getQQFriendInfo().size()) {
		cout << "���Ǻ���" << endl;
		system("pause");
		return;
	}
}

void applicationQQLA::friendRequestPage() {
	string path = "QQ\\" + to_string(m_currentUser->getAppUserId()) + "\\friendrequest.dat";
	while(1)
	{
		system("cls");
		ifstream ifs(path, ios::in);
		if (!ifs.is_open()) {
			cout << "���ļ�ʧ��" << endl;
			return;
		}
		vector<int> qqNumberList;
		while (!ifs.eof()) {
			int qqNumber = -1;
			ifs >> qqNumber;
			if (qqNumber == -1) {
				break;
			}
			qqNumberList.push_back(qqNumber);
		}
		ifs.close();
		if (qqNumberList.size() == 0) {
			cout << "Ŀǰû�к�������" << endl;
			system("pause");
			return;
		}

		system("cls");
		cout << "         ���������б�" << endl;
		cout << "_________________________________" << endl;
		cout << "|QQ��|          �� ��           |" << endl;
		cout << "_________________________________" << endl;
		for (int i = 0; i < qqNumberList.size(); i++) {
			cout << "|" << setw(4) << qqNumberList[i] << "|";
			cout << m_allQQUserList->findByQQId(qqNumberList[i])->getUserName() << "|" << endl;
			cout << "_________________________________" << endl;
		}
		cout << "| 01 || ͬ��                    |" << endl;
		cout << "| 02 || �ܾ�                    |" << endl;
		cout << "| 00 || ����                    |" << endl;
		cout << "_________________________________" << endl;
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "����ͬ��ĺ���QQ��:" << endl;
			int qqNumber = 0;
			cin >> qqNumber;
			refreshInput();
			if (count(qqNumberList.begin(),qqNumberList.end(),qqNumber) == 0) {
				cout << "�û�������" << endl;
				system("pause");
				continue;
			}
			qqUserNodeLA* friendToAddPtr = m_allQQUserList->findByQQId(qqNumber);
			//������Ӻ���
			userInfo info;
			info.friendId = friendToAddPtr->getAppUserId();
			info.friendName = friendToAddPtr->getUserName();
			m_currentUser->addQQFriendInfo(info);
			info.friendId = m_currentUser->getAppUserId();
			info.friendName = m_currentUser->getUserName();
			friendToAddPtr->addQQFriendInfo(info);
			//ɾ������
			remove(qqNumberList.begin(), qqNumberList.end(), qqNumber);
			//�����ļ�
			m_allQQUserList->saveQQUserListData();
			ofstream ofs(path, ios::out);
			for (auto i : qqNumberList) {
				ofs << i << endl;
			}
			ofs.close();
			cout << "���� " << friendToAddPtr->getUserName() << " ��ӳɹ�" << endl;
			system("pause");
			return;
		}
		else if (i == 2) {
			cout << "����ܾ��ĺ���QQ��:" << endl;
			int qqNumber = 0;
			cin >> qqNumber;
			refreshInput();
			if (count(qqNumberList.begin(), qqNumberList.end(), qqNumber)) {
				cout << "�������벻����" << endl;
				system("pause");
				continue;
			}
			//ɾ������
			remove(qqNumberList.begin(), qqNumberList.end(), qqNumber);
			//�����ļ�
			ofstream ofs(path, ios::out);
			for (auto i : qqNumberList) {
				ofs << i << endl;
			}
			ofs.close();
			cout << "�ܾ��ɹ�" << endl;
			system("pause");
			return;
		}
		else if (i == 0) {
			return;
		}
		else {
			cout << "�������" << endl;
			system("pause");
			return;
		}
	}
}

void applicationQQLA::chatWithFriendPage(qqUserNodeLA* friendPtr) {
	while (1)
	{
		system("cls");
		long long len = friendPtr->getUserName().length();
		cout << setw((40 - len) / 2) << friendPtr->getUserName() << endl;
		cout << "_________________________________" << endl;
		showMsg(recvMsgFromFriend(friendPtr));
		cout << "_________________________________" << endl;
		cout << "| 01 || ������Ϣ                  |" << endl;
		cout << "| 00 || ����                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "����ѡ��:";
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			sendMsgPage(friendPtr);
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

void applicationQQLA::applyFriend(qqUserNodeLA* user, qqUserNodeLA* friendToAdd) {
	string path = "QQ\\" + to_string(friendToAdd->getAppUserId()) + "\\friendrequest.dat";
	//�ں��ѵ������б����������
	ofstream ofs(path, ios::app);
	if (!ofs.is_open()) {
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	ofs << user->getAppUserId() << endl;
	ofs.close();

}

//////////////////////////////////////////////////////
void applicationQQLA::groupPage() {
	while (1) {
		system("cls");
		cout << "           Ⱥ��" << endl;
		showQQGroupList(m_currentUser->getQQGroupId());
		cout << "| 01 || ѡ��Ⱥ                    |" << endl;
		cout << "| 02 || ����Ⱥ                    |" << endl;
		cout << "| 03 || ����Ⱥ                    |" << endl;
		cout << "| 04 || ����Ⱥ                    |" << endl;
		cout << "| 05 || �˳�Ⱥ                    |" << endl;
		cout << "| 00 || ����                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "����ѡ��:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			selectGroupPage();
		}
		else if (i == 2) {
			searchGroupPage();
		}
		else if (i == 3) {
			createGroupPage();
		}
		else if (i == 4) {
			joinGroupPage();
		}
		else if (i == 5) {
			quitGroupPage();
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

void applicationQQLA::selectGroupPage()
{
	system("cls");
	cout << "         ѡ��Ⱥ��" << endl;
	showQQGroupList(m_currentUser->getQQGroupId());
	if(m_currentUser->getQQGroupId().size() == 0) {
		system("pause");
		return;
	}
	cout << "����Ⱥ��:";

	int groupId = 0;
	cin >> groupId;
	refreshInput();
	qqGroupNodeLA* p = m_allQQGroupList->findByGroupId(groupId);
	if (p == nullptr) {
		cout << "Ⱥ������" << endl;
		system("pause");
		return;
	}
	else {
		chatInGroupPage(p);
	}
}

void applicationQQLA::chatInGroupPage(qqGroupNodeLA* groupPtr) {
	while(1)
	{
		system("cls");
		showMsg(recvMsgFromGroup(groupPtr));
		
		int userid = m_currentUser->getAppUserId();
		if(groupPtr->isOwner(userid)) {
			cout << setw(20) << groupPtr->getGroupName() << endl;
			cout << "_________________________________" << endl;
			cout << "| 01 || ������Ϣ                  |" << endl;
			cout << "| 02 || �鿴Ⱥ��Ա                |" << endl;
			cout << "| 03 || ��ɢȺ                    |" << endl;
			cout << "| 04 || ����Ⱥ                    |" << endl;
			cout << "| 05 || �����Ⱥ                  |" << endl;
			cout << "| 06 || �߳�Ⱥ��Ա                |" << endl;
			cout << "| 07 || �鿴Ⱥ����                |" << endl;
			cout << "| 08 || ���ù���Ա                |" << endl;
			cout << "| 00 || ����                      |" << endl;
			cout << "_________________________________" << endl;
			cout << "����ѡ��:";

			int i = 0;
			cin >> i;
			refreshInput();
			if (i == 1) {
				sendMsgPage(groupPtr);
			}
			else if (i == 2) {
				showGroupMemberPage(groupPtr);
			}
			else if (i == 3) {
				disbandGroupPage(groupPtr);
			}
			else if (i == 4) {
				setGroupConfigPage(groupPtr);
			}
			else if (i == 5) {
				inviteFriendInPage(groupPtr);
			}
			else if (i == 6) {
				kickMemberPage(groupPtr);
			}
			else if (i == 7) {
				groupRequestPage(groupPtr);
			}
			else if (i == 8) {
				setAdminPage(groupPtr);
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
		else if (groupPtr->isAdministrator(userid)) {
			cout << setw(20) << groupPtr->getGroupName() << endl;
			cout << "_________________________________" << endl;
			cout << "| 01 || ������Ϣ                  |" << endl;
			cout << "| 02 || �鿴Ⱥ��Ա                |" << endl;
			cout << "| 03 || �����Ⱥ                  |" << endl;
			cout << "| 04 || �˳�Ⱥ                    |" << endl;
			cout << "| 05 || �鿴Ⱥ����                |" << endl;
			cout << "| 06 || �߳�Ⱥ��Ա                |" << endl;
			cout << "| 00 || ����                      |" << endl;
			cout << "_________________________________" << endl;
			cout << "����ѡ��:";

			int i = 0;
			cin >> i;
			refreshInput();
			if (i == 1) {
				sendMsgPage(groupPtr);
			}
			else if (i == 2) {
				showGroupMemberPage(groupPtr);
			}
			else if (i == 3) {
				inviteFriendInPage(groupPtr);
			}
			else if (i == 4) {
				quitGroupPage(groupPtr);
			}
			else if (i == 5) {
				groupRequestPage(groupPtr);
			}
			else if (i == 6) {
				kickMemberPage(groupPtr);
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
		else if(groupPtr->isMember(userid)) {
			cout << setw(20) << groupPtr->getGroupName() << endl;
			cout << "_________________________________" << endl;
			cout << "| 01 || ������Ϣ                  |" << endl;
			cout << "| 02 || �鿴Ⱥ��Ա                |" << endl;
			cout << "| 03 || �����Ⱥ                  |" << endl;
			cout << "| 04 || �˳�Ⱥ                    |" << endl;
			cout << "| 05 || �鿴Ⱥ����                |" << endl;
			cout << "| 00 || ����                      |" << endl;
			cout << "_________________________________" << endl;
			cout << "����ѡ��:";
			
			int i = 0;
			cin >> i;
			refreshInput();
			if (i == 1) {
				cout << "ֱ�ӻس�����;������Ϣ�س�����:" << endl;
				char message[300];
				memset(message, 0, 300);
				cin.getline(message, 300);
				if (message[0] == '\0') {
					continue;
				}
				(sendMsgToGroup(groupPtr, message)) ? cout << "���ͳɹ�" << endl : cout << "����ʧ��" << endl;
			}
			else if (i == 2) {
				showGroupMemberPage(groupPtr);
			}
			else if (i == 3) {
				inviteFriendInPage(groupPtr);
			}
			else if (i == 4) {
				quitGroupPage(groupPtr);
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
		else {
			cout << setw(20) << groupPtr->getGroupName() << endl;
			cout << "_________________________________" << endl;
			cout << "| 01 || �鿴Ⱥ��Ա                |" << endl;
			cout << "| 02 || �������Ⱥ                |" << endl;
			cout << "| 00 || ����                      |" << endl;
			cout << "_________________________________" << endl;
			cout << "����ѡ��:";

			int i = 0;
			cin >> i;
			refreshInput();
			if (i == 1) {
				showGroupMemberPage(groupPtr);
			}
			else if (i == 2) {
				if (!groupPtr->isAllowJoin()) {
					cout << "��Ⱥ��ǰ���������" << endl;
					system("pause");
					continue;
				}
				userInfo info;
				info.friendId = m_currentUser->getAppUserId();
				info.friendName = m_currentUser->getUserName();
				groupPtr->addRequest(info);
				m_allQQGroupList->saveGroupListData();
				cout << "����ɹ�" << endl;
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
}

void applicationQQLA::setAdminPage(qqGroupNodeLA* groupPtr)
{
	if (!groupPtr->isOwner(m_currentUser->getAppUserId())) {
		cout << "�㲻��Ⱥ��,�޷����ù���Ա" << endl;
		system("pause");
		return;
	}
	if (!groupPtr->isAllowAdmins()) {
		cout << "�����ò��������Ա" << endl;
		system("pause");
		return;
	}
	system("cls");
	cout << "         ���ù���Ա" << endl;
	cout << "_________________________________" << endl;
	showGroupMemberPage(groupPtr);

	cout << "����Ҫ���õ�QQ��:";

	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	if(!groupPtr->isMember(qqNumber)) {
		cout << "���û�����Ⱥ��Ա" << endl;
		system("pause");
		return;
	}
	if (groupPtr->isAdministrator(qqNumber)) {
		cout << m_allQQUserList->findByQQId(qqNumber)->getUserName() << "�ǹ���Ա" << endl;
		cout << "����1���䳷������Ա" << endl;

		int i = 0;
		cin >> i;
		refreshInput();
		
		if (i == 1) {
			groupPtr->removeQQGroupAdmin(qqNumber);
			m_allQQGroupList->saveGroupListData();
			cout << "�����ɹ�" << endl;
			system("pause");
			return;
		}
		else {
			cout << "ȡ������" << endl;
			system("pause");
			return;
		}
	}
	else {
		cout << m_allQQUserList->findByQQId(qqNumber)->getUserName() << "���ǹ���Ա" << endl;
		cout << "����1��������Ϊ����Ա" << endl;
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			groupPtr->addQQGroupAdmin(qqNumber);
			m_allQQGroupList->saveGroupListData();
			cout << "���óɹ�" << endl;
			system("pause");
			return;
		}
		else {
			cout << "ȡ������" << endl;
			system("pause");
			return;
		}
	}
	return;
}

void applicationQQLA::searchGroupPage() {
	system("cls");
	cout << "����Ⱥ��:" << endl;
	int groupId = 0;
	cin >> groupId;
	refreshInput();
	qqGroupNodeLA* p = m_allQQGroupList->findByGroupId(groupId);
	if (p == nullptr) {
		cout << "Ⱥ������" << endl;
		system("pause");
		return;
	}
	else {
		chatInGroupPage(p);
		return;
	}
}

void applicationQQLA::sendMsgPage(qqGroupNodeLA* groupPtr)
{
	int id = m_currentUser->getAppUserId();
	if ((!groupPtr->isAllowSend()) && (!groupPtr->isAdministrator(id)) && (!groupPtr->isOwner(id))) {
		cout << "��Ⱥ������" << endl;
		system("pause");
		return;
	}
	cout << "ֱ�ӻس�����;������Ϣ�س�����:" << endl;
	char message[300];
	memset(message, 0, 300);
	cin.getline(message, 300);
	if (message[0] == '\0') {
		return;
	}
	(sendMsgToGroup(groupPtr, message))
		? cout << "���ͳɹ�" << endl
		: cout << "����ʧ��" << endl;
}

void applicationQQLA::createGroupPage() {
	system("cls");
	cout << "		 ����Ⱥ��" << endl;
	cout << "_________________________________" << endl;
	cout << "����Ⱥ��:";
	string groupName;
	cin >> groupName;
	refreshInput();
	system("cls");
	cout << "��1ȷ�ϴ���:" << endl;
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		qqGroupNodeLA* p = m_allQQGroupList->addGroup(groupName, m_currentUser->getAppUserId());
		
		m_currentUser->addQQGroupId(p->getGroupId());
		//�����ļ�
		m_allQQGroupList->saveGroupListData();
		m_allQQUserList->saveQQUserListData();
		system("cls");
		cout << "            �����ɹ�" << endl;
		cout << "_________________________________" << endl;
		cout << "| Ⱥ��|| " << setw(26) << setiosflags(ios::left) << p->getGroupId() << "|" << endl;
		cout << "| Ⱥ��|| " << setw(26) << setiosflags(ios::left) << p->getGroupName() << "|" << endl;
		cout << "_________________________________" << endl;
	}
	else {
		cout << "ȡ������" << endl;
	}
	system("pause");
	return;

}

void applicationQQLA::joinGroupPage() {
	system("cls");
	if (m_allQQGroupList->size() == 0) {
		cout << "û��Ⱥ�ɼ���" << endl;
		system("pause");
		return;
	}

	default_random_engine e(time(NULL));
	int id1 = 1001 + e() % m_allQQGroupList->size();
	int id2 = 1001 + e() % m_allQQGroupList->size();

	cout << "		     ����Ⱥ��" << endl;
	cout << "_________________________________" << endl;
	cout << "            �Ƽ�Ⱥ��" << endl;
	cout << "_________________________________" << endl;
	cout << "| Ⱥ��|| " << setw(26) << setiosflags(ios::left) << id1 << "|" << endl;
	cout << "| Ⱥ��|| " << setw(26) << setiosflags(ios::left) << m_allQQGroupList->findByGroupId(id1)->getGroupName() << "|" << endl;
	cout << "_________________________________" << endl;
	cout << "| Ⱥ��|| " << setw(26) << setiosflags(ios::left) << id2 << "|" << endl;
	cout << "| Ⱥ��|| " << setw(26) << setiosflags(ios::left) << m_allQQGroupList->findByGroupId(id2)->getGroupName() << "|" << endl;
	cout << "_________________________________" << endl;
	cout << resetiosflags(ios::left);
	cout << "����Ⱥ��:";

	int groupId = 0;
	cin >> groupId;
	refreshInput();
	if(m_currentUser->isAddedGroup(groupId)) {
		cout << "�Ѿ���Ⱥ��" << endl;
		system("pause");
		return;
	}
	qqGroupNodeLA* p = m_allQQGroupList->findByGroupId(groupId);
	if (p == nullptr) {
		cout << "Ⱥ������" << endl;
		system("pause");
		return;
	}
	else {
		cout << "         ����Ⱥ��" << endl;
		cout << "_________________________________" << endl;
		cout << "| Ⱥ��|| " << setw(26) << setiosflags(ios::left) << p->getGroupId() << "|" << endl;
		cout << "| Ⱥ��|| " << setw(26) << setiosflags(ios::left) << p->getGroupName() << "|" << endl;
		cout << "_________________________________" << endl;
		cout << "| 01 || �������                  |" << endl;
		cout << "|����|| ����                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "����ѡ��:";
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			//��ӵ�Ⱥ��Ա�б�
			userInfo info;
			info.friendId = m_currentUser->getAppUserId();
			info.friendName = m_currentUser->getUserName();
			//�������
			p->addRequest(info);
			//���浽�ļ�
			m_allQQGroupList->saveGroupListData();

			cout << "����ɹ�" << endl;
		}
		else if (i == 0) {
			cout << "ȡ������" << endl;
		}
		else {
			cout << "ȡ������" << endl;
		}
		system("pause");
		return;
	}
}

void applicationQQLA::disbandGroupPage(qqGroupNodeLA* groupPtr)
{
	system("cls");
	cout << "         ��ɢȺ��" << endl;
	cout << "_________________________________" << endl;
	cout << "| Ⱥ��|| " << setw(26) << setiosflags(ios::left) << groupPtr->getGroupId() << "|" << endl;
	cout << "| Ⱥ��|| " << setw(26) << setiosflags(ios::left) << groupPtr->getGroupName() << "|" << endl;
	cout << "_________________________________" << endl;
	cout << "| 01 || ȷ�Ͻ�ɢ(����ɾ�������¼!) |" << endl;
	cout << "|����|| ����                      |" << endl;
	cout << "_________________________________" << endl;
	cout << "����ѡ��:";

	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		//ɾ��ÿ���û����洢��Ⱥ��
		int groupId = groupPtr->getGroupId();
		vector<userInfo> memberList = groupPtr->getQQGroupMemberInfoList();
		for (int i = 0; i < memberList.size(); i++) {
			qqUserNodeLA* p = m_allQQUserList->findByQQId(memberList[i].friendId);
			p->deleteQQGroupId(groupId);
			//ɾ�������ļ�
			string path = "QQ\\" + to_string(p->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupId) + ".dat";
			if(_access(path.c_str(), 0) != -1) {
				remove(path.c_str());
			}
		}

		//�Ƴ�Ⱥ
		m_allQQGroupList->removeGroup(groupPtr);
		cout << "��ɢ�ɹ�" << endl;
		system("pause");
		return;
	}
	else {
		cout << "ȡ����ɢ" << endl;
		system("pause");
		return;
	}
}

void applicationQQLA::quitGroupPage() {
	system("cls");
	cout << "         �˳�Ⱥ��" << endl;
	cout << "_________________________________" << endl;
	showQQGroupList(m_currentUser->getQQGroupId());
	if(m_currentUser->getQQGroupId().size() == 0) {
		system("pause");
		return;
	}
	cout << "����Ⱥ��:" << endl;
	int groupId = 0;
	cin >> groupId;
	refreshInput();
	qqGroupNodeLA* p = m_allQQGroupList->findByGroupId(groupId);
	if (!m_currentUser->isAddedGroup(groupId)) {
		cout << "Ⱥ������" << endl;
		system("pause");
		return;
	}
	else if (p->isOwner(m_currentUser->getAppUserId())) {
		cout << "Ⱥ���޷��˳�Ⱥ��,�볢�Խ�ɢȺ" << endl;
		system("pause");
		return;
	}
	else {
		system("cls");
		cout << "         �˳�Ⱥ��" << endl;
		cout << "_________________________________" << endl;
		cout << "| Ⱥ��|| " << setw(26) << setiosflags(ios::left) << p->getGroupId() << "|" << endl;
		cout << "| Ⱥ��|| " << setw(26) << setiosflags(ios::left) << p->getGroupName() << "|" << endl;
		cout << "_________________________________" << endl;
		cout << "| 01 || ȷ���˳�(����ɾ�������¼!)|" << endl;
		cout << "|����|| ����                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "����ѡ��:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			//�໥ɾ��
			if (p->isAdministrator(m_currentUser->getAppUserId())) {
				p->removeQQGroupAdmin(m_currentUser->getAppUserId());
			}
			p->removeMember(m_currentUser->getAppUserId());
			m_currentUser->deleteQQGroupId(p->getGroupId());
			//���浽�ļ�
			m_allQQGroupList->saveGroupListData();
			m_allQQUserList->saveQQUserListData();
			string path = "QQ\\" + to_string(m_currentUser->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupId) + ".dat";
			if (_access(path.c_str(), 0) != -1) {
				remove(path.c_str());
			}

			cout << "�˳��ɹ�" << endl;
		}
		else {
			cout << "ȡ���˳�" << endl;
		}
		system("pause");
		return;
	}
}

void applicationQQLA::quitGroupPage(qqGroupNodeLA* groupPtr) {
	if (groupPtr->isOwner(m_currentUser->getAppUserId())) {
		cout << "Ⱥ���޷��˳�Ⱥ��,�볢�Խ�ɢȺ" << endl;
		system("pause");
		return;
	}
	system("cls");
	cout << "         �˳�Ⱥ��" << endl;
	cout << "_________________________________" << endl;
	cout << "| Ⱥ��|| " << setw(26) << setiosflags(ios::left) << groupPtr->getGroupId() << "|" << endl;
	cout << "| Ⱥ��|| " << setw(26) << setiosflags(ios::left) << groupPtr->getGroupName() << "|" << endl;
	cout << "_________________________________" << endl;
	cout << "| 01 || ȷ���˳�(����ɾ�������¼!)|" << endl;
	cout << "|����|| ����                      |" << endl;
	cout << "_________________________________" << endl;
	cout << "����ѡ��:";

	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		//�໥ɾ��
		if (groupPtr->isAdministrator(m_currentUser->getAppUserId())) {
			groupPtr->removeQQGroupAdmin(m_currentUser->getAppUserId());
		}
		groupPtr->removeMember(m_currentUser->getAppUserId());
		m_currentUser->deleteQQGroupId(groupPtr->getGroupId());
		//���浽�ļ�
		m_allQQGroupList->saveGroupListData();
		m_allQQUserList->saveQQUserListData();
		string path = "QQ\\" + to_string(m_currentUser->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupPtr->getGroupId()) + ".dat";
		if (_access(path.c_str(), 0) != -1) {
			remove(path.c_str());
		}

		cout << "�˳��ɹ�" << endl;
	}
	else {
		cout << "ȡ���˳�" << endl;
	}
	system("pause");
	return;
}

void applicationQQLA::setGroupConfigPage(qqGroupNodeLA* groupPtr) {
	while (1) 
	{
		system("cls");
		cout << setw(20) << groupPtr->getGroupName() << endl;
		cout << "_________________________________" << endl;
		cout << "| 01 || �޸�Ⱥ��                  |" << endl;
		cout << "| 02 || �Ƿ����������Ⱥ          |" << endl;
		cout << "| 03 || �Ƿ�������������          |" << endl;
		cout << "| 04 || �Ƿ�������              |" << endl;
		cout << "| 05 || �Ƿ��������ù���Ա        |" << endl;
		cout << "| 06 || �Ƿ�Ⱥ��Ա��ʱ�Ự        |" << endl;
		cout << "| 00 || ����                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "����ѡ��:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "������Ⱥ��,ֱ�ӻس��ɷ���" << endl;
			string groupName;
			cin >> groupName;
			refreshInput();
			if (groupName == "") {
				continue;
			}
			groupPtr->setQQGroupName(groupName);
			m_allQQGroupList->saveGroupListData();
			cout << "�޸ĳɹ�" << endl;
			system("pause");
			continue;
		}
		else if (i == 2) {
			if (groupPtr->isAllowInvite()) {
				cout << "��ǰ���������Ⱥ,��1��ֹ:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowInvite(false);
					m_allQQGroupList->saveGroupListData();
					cout << "�޸ĳɹ�" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "ȡ���޸�" << endl;
					system("pause");
					continue;
				}
			}
			else {
				cout << "��ǰ��ֹ�����Ⱥ,��1����:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowInvite(true);
					m_allQQGroupList->saveGroupListData();
					cout << "�޸ĳɹ�" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "ȡ���޸�" << endl;
					system("pause");
					continue;
				}
			}
		}
		else if (i == 3) {
			if (groupPtr->isAllowJoin()) {
				cout << "��ǰ������������,��1��ֹ:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowJoin(false);
					m_allQQGroupList->saveGroupListData();
					cout << "�޸ĳɹ�" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "ȡ���޸�" << endl;
					system("pause");
					continue;
				}
			}
			else {
				cout << "��ǰ��ֹ��������,��1����:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowJoin(true);
					m_allQQGroupList->saveGroupListData();
					cout << "�޸ĳɹ�" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "ȡ���޸�" << endl;
					system("pause");
					continue;
				}
			}
		}
		else if (i == 4) {
			if (groupPtr->isAllowSend()) {
				cout << "��ǰ������,��1��ֹ:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowSend(false);
					m_allQQGroupList->saveGroupListData();
					cout << "�޸ĳɹ�" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "ȡ���޸�" << endl;
					system("pause");
					continue;
				}
			}
			else {
				cout << "��ǰ��ֹ����,��1����:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowSend(true);
					m_allQQGroupList->saveGroupListData();
					cout << "�޸ĳɹ�" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "ȡ���޸�" << endl;
					system("pause");
					continue;
				}
			}
		}
		else if (i == 5) {
			if (groupPtr->isAllowAdmins()) {
				cout << "��ǰ�������Ա,��1��ֹ:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowAdmins(false);
					m_allQQGroupList->saveGroupListData();
					cout << "�޸ĳɹ�" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "ȡ���޸�" << endl;
					system("pause");
					continue;
				}
			}
			else {
				cout << "��ǰ��ֹ����Ա,��1����:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowAdmins(true);
					m_allQQGroupList->saveGroupListData();
					cout << "�޸ĳɹ�" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "ȡ���޸�" << endl;
					system("pause");
					continue;
				}
			}
		}
		else if (i == 6) {
			if (groupPtr->isAllowSubgroup()) {
				cout << "��ǰ����Ⱥ��Ա��ʱ�Ự,��1��ֹ:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowSubgroup(false);
					m_allQQGroupList->saveGroupListData();
					cout << "�޸ĳɹ�" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "ȡ���޸�" << endl;
					system("pause");
					continue;
				}
			}
			else {
				cout << "��ǰ��ֹȺ��Ա��ʱ�Ự,��1����:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowSubgroup(true);
					m_allQQGroupList->saveGroupListData();
					cout << "�޸ĳɹ�" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "ȡ���޸�" << endl;
					system("pause");
					continue;
				}
			}
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

void applicationQQLA::inviteFriendInPage(qqGroupNodeLA* groupPtr){
	if (!groupPtr->isAllowInvite()) {
		cout << "��Ⱥ��ǰ�������������" << endl;
		system("pause");
		return;
	}
	vector<userInfo> memberList = m_currentUser->getQQFriendInfo();
	system("cls");
	showQQFriendList(memberList);
	cout << "����Ҫ����ĺ���QQ��" << endl;
	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	if (groupPtr->isMember(qqNumber)) {
		cout << "���û��Ѿ���Ⱥ��" << endl;
		system("pause");
		return;
	}
	cout << "ȷ�����밴1" << endl;
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		groupPtr->addMember(qqNumber);
	}
	else {
		cout << "ȡ������" << endl;
		system("pause");
		return;
	}
}

void applicationQQLA::kickMemberPage(qqGroupNodeLA* groupPtr)
{
	system("cls");
	cout << "����Ҫ�߳���Ⱥ��ԱQQ��" << endl;
	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	if (!groupPtr->isMember(qqNumber)) {
		cout << "���û�����Ⱥ��Ա" << endl;
		system("pause");
		return;
	}
	if (groupPtr->isOwner(qqNumber)) {
		cout << "�����߳�Ⱥ��" << endl;
		system("pause");
		return;
	}
	if (m_currentUser->getAppUserId() == qqNumber) {
		cout << "�߳��Լ����˳���Ⱥ" << endl;
		quitGroupPage(groupPtr);
		return;
	}
	cout << "ȷ���߳���1" << endl;
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		//ɾ���û����洢��Ⱥ��
		int groupId = groupPtr->getGroupId();
		qqUserNodeLA* p = m_allQQUserList->findByQQId(qqNumber);
		p->deleteQQGroupId(groupId);

		//�Ƴ��û�
		groupPtr->removeMember(qqNumber);
		cout << "�߳��ɹ�" << endl;
		system("pause");
	}
	else {
		cout << "ȡ���߳�" << endl;
		system("pause");
	}


}

void applicationQQLA::groupRequestPage(qqGroupNodeLA* groupPtr) {
	while(1)
	{
		if (!groupPtr->isAdministrator(m_currentUser->getAppUserId()) && !groupPtr->isOwner(m_currentUser->getAppUserId())) {
			cout << "��Ȩ��������";
			system("pause");
			return;
		}
		vector<userInfo> requestList = groupPtr->getQQGroupRequestInfoList();
		if (requestList.size() == 0) {
			cout << "û������" << endl;
			system("pause");
			return;
		}
		cout << "           �����б�" << endl;
		cout << "_________________________________" << endl;

		for (int i = 0; i < requestList.size(); i++) {
			cout << "|QQ��|| " << setw(26) << setiosflags(ios::left) << requestList[i].friendId << "|" << endl;
			cout << "|�ǳ�|| " << setw(26) << setiosflags(ios::left) << requestList[i].friendName << "|" << endl;
			cout << "_________________________________" << endl;
		}
		cout << resetiosflags(ios::left);
		cout << "| 01 || ͬ��                      |" << endl;
		cout << "| 02 || �ܾ�                      |" << endl;
		cout << "| 00 || ����                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "����ѡ��:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "����ͬ���QQ��:";
			int qqNumber = 0;
			cin >> qqNumber;
			refreshInput();
			//����Ƿ���ڸ�����
			for (int i = 0; i < requestList.size(); i++) {
				if (requestList[i].friendId == qqNumber) {
					break;
				}
			}
			if (i == requestList.size()) {
				cout << "���󲻴���" << endl;
				system("pause");
				continue;
			}
			//�������
			groupPtr->addMember(qqNumber);

			qqUserNodeLA* p = m_allQQUserList->findByQQId(qqNumber);
			p->addQQGroupId(groupPtr->getGroupId());
			//�Ƴ�����
			groupPtr->removeRequest(qqNumber);
			
			//���浽�ļ�
			m_allQQGroupList->saveGroupListData();
			m_allQQUserList->saveQQUserListData();

			cout << "��ӳɹ�" << endl;
			system("pause");
			continue;
		}
		else {
			//�Ƴ�����
			groupPtr->removeRequest(requestList[i].friendId);
			cout << "�Ѿܾ�" << endl;
			system("pause");
			continue;
		}
	}
}

/////////////////////////////////////////////////////////////////
bool applicationQQLA::sendMsgToFriend(qqUserNodeLA* friendPtr, const char* msg) {
	string path = "QQ\\" + to_string(friendPtr->getAppUserId()) + "\\chatrecord\\" + to_string(m_currentUser->getAppUserId()) + ".dat";
	//��ȡʱ��
	string time = getTime();
	//�򿪺��ѵ�chatrecord�ļ�д�뷢����QQ��,�������ǳ�,����ʱ��,��Ϣ����
	ofstream ofs(path, ios::app);
	if (!ofs.is_open()) {
		cout << "��" << friendPtr->getAppUserId() << "�������¼�ļ�ʧ��" << endl;
		return false;
	}
	//д��
	ofs << m_currentUser->getAppUserId() << endl;
	ofs << m_currentUser->getUserName() << endl;
	ofs << time << endl;
	ofs << msg << endl;
	ofs.close();
	
	//���Լ���chatrecord�ļ�д�뷢����QQ��,�������ǳ�,����ʱ��,��Ϣ����
	path = "QQ\\" + to_string(m_currentUser->getAppUserId()) + "\\chatrecord\\" + to_string(friendPtr->getAppUserId()) + ".dat";
	ofs.open(path, ios::app);
	if (!ofs.is_open()) {
		cout << "��" << m_currentUser->getAppUserId() << "�������¼�ļ�ʧ��" << endl;
		return false;
	}
	//д��
	ofs << m_currentUser->getAppUserId() << endl;
	ofs << m_currentUser->getUserName() << endl;
	ofs << time << endl;
	ofs << msg << endl;
	ofs.close();

	return true;
}

bool applicationQQLA::sendMsgToGroup(qqGroupNodeLA* groupPtr, const char* msg) {
	//��Ⱥ����������(�����Լ�)���ļ���ӷ���ʱ�����Ϣ����
	vector<userInfo> memberList = groupPtr->getQQGroupMemberInfoList();
	for (int i = 0; i < memberList.size(); i++) {
		string path = "QQ\\" + to_string(memberList[i].friendId) + "\\groupchatrecord\\" + to_string(groupPtr->getGroupId()) + ".dat";
		
		//��ȡʱ��
		string time = getTime();
		//��ÿ���û���groupchatrecord�ļ�д�뷢����QQ��,�������ǳ�,����ʱ��,��Ϣ����
		ofstream ofs(path, ios::app);
		if (!ofs.is_open()) {
			cout << "��" << memberList[i].friendId << "��Ⱥ�ļ�¼�ļ�ʧ��" << endl;
			return false;
		}
		//д��
		ofs << m_currentUser->getAppUserId() << endl;
		ofs << m_currentUser->getUserName() << endl;
		ofs << time << endl;
		ofs << msg << endl;
		ofs.close();

	}
	return true;
}

vector<QMsg> applicationQQLA::recvMsgFromFriend(qqUserNodeLA* friendPtr)
{
	string path = "QQ\\" + to_string(m_currentUser->getAppUserId()) + "\\chatrecord\\" + to_string(friendPtr->getAppUserId()) + ".dat";
	//�ж��ļ��Ƿ����,�������򴴽�
	if(_access(path.c_str(), 0) == -1) {
		ofstream outFile;
		outFile.open(path, ios::out);
		outFile.close();
	}
	ifstream ifs(path, ios::in);
	if (!ifs.is_open()) {
		cout << "���ļ�ʧ��" << endl;
		return {};
	}
	//ѭ����ȡ�ļ��ڵ���Ϣ
	vector<QMsg> msgList;
	int id = 0;
	string name;
	string time;
	string msg;
	while (ifs >> id >> name >> time >> msg) {
		//������Ϣ�ṹ��
		QMsg qmsg;
		qmsg.senderId = id;
		qmsg.senderName = name;
		qmsg.time = time;
		qmsg.msg = msg;
		//ѹ����Ϣ�б�
		msgList.push_back(qmsg);
	}

	return msgList;
}

vector<QMsg> applicationQQLA::recvMsgFromGroup(qqGroupNodeLA* groupPtr)
{
	string path	= "QQ\\" + to_string(m_currentUser->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupPtr->getGroupId()) + ".dat";
	//�ж��ļ��Ƿ����,�������򴴽�
	if (_access(path.c_str(), 0) == -1) {
		ofstream outFile;
		outFile.open(path, ios::out);
		outFile.close();
	}
	//���ļ�
	ifstream ifs(path, ios::in);
	if (!ifs.is_open()) {
		cout << "���ļ�ʧ��" << endl;
		return {};
	}
	//ѭ����ȡ�ļ��ڵ���Ϣ
	vector<QMsg> msgList;
	int id;
	string name;
	string time;
	string msg;
	while (ifs >> id >> name >> time >> msg) {
		//������Ϣ�ṹ��
		QMsg qmsg;
		qmsg.senderId = id;
		qmsg.senderName = name;
		qmsg.time = time;
		qmsg.msg = msg;
		//ѹ����Ϣ�б�
		msgList.push_back(qmsg);
	}
	return msgList;
}

/////////////////////////////////////////////////////////////////
void applicationQQLA::makeUserFile(string path){
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
void applicationQQLA::showMsg(vector<QMsg> m) {
	for (int i = 0; i < m.size(); i++) {
		if (m_currentUser->getAppUserId() == m[i].senderId) {
			cout << "�� " << "("<<m[i].time<<")" << endl;
			cout << m[i].msg << endl;
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
			cout << m[i].senderName << "(" << m[i].time << ")" << endl
				<< m[i].msg << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);

		}
	}
}
//TODO:color
void applicationQQLA::showQQFriendList(vector<userInfo> friendlist) {
	if (friendlist.size() == 0)
	{
		cout << "        ��û���κκ���" << endl;
		cout << "_________________________________" << endl;
		return;
	}
	cout << "����" << friendlist.size() << "������" << endl;
	cout << "_________________________________" << endl;

	for (int i = 0; i < friendlist.size(); i++) {
		cout << "|QQ��|| " << setw(26) << setiosflags(ios::left) << friendlist[i].friendId << "|" << endl;
		cout << "|�ǳ�|| " << setw(26) << setiosflags(ios::left) << friendlist[i].friendName << "|" << endl;
		cout << "_________________________________" << endl;
	}
	cout << resetiosflags(ios::left);

	return;
}
//TODO:color
void applicationQQLA::showQQGroupList(vector<int> grouplist) {
	if (grouplist.size() == 0)
	{
		cout << "       ��û�м����κ�Ⱥ" << endl;
		cout << "_________________________________" << endl;
		return;
	}
	cout << "����" << grouplist.size() << "��Ⱥ" << endl;
	cout << "_________________________________" << endl;

	for (int i = 0; i < grouplist.size(); i++) {
		cout << "|Ⱥ��|| " << setw(26) << setiosflags(ios::left) << grouplist[i] << "|" << endl;
		cout << "|Ⱥ��|| " << setw(26) << setiosflags(ios::left) << m_allQQGroupList->findByGroupId(grouplist[i])->getGroupName() << "|" << endl;
		cout << "_________________________________" << endl;
	}
	cout << resetiosflags(ios::left);

	return;
}

void applicationQQLA::showGroupMemberPage(int groupId) {
	qqGroupNodeLA* groupPtr = m_allQQGroupList->findByGroupId(groupId);
	showGroupMemberPage(groupPtr);
}
//TODO:color
void applicationQQLA::showGroupMemberPage(qqGroupNodeLA* groupPtr) {
	system("cls");
	vector<userInfo> memberList = groupPtr->getQQGroupMemberInfoList();
	cout << "          Ⱥ��Ա�б�(" << memberList.size() << ")" << endl;
	cout << "_________________________________" << endl;

	for (int i = 0; i < memberList.size(); i++) {
		cout << "|QQ��|| " << setw(26) << setiosflags(ios::left) << memberList[i].friendId << "|" << endl;
		cout << "|�ǳ�|| " << setw(26) << setiosflags(ios::left) << memberList[i].friendName << "|" << endl;
		cout << "_________________________________" << endl;
	}
	cout << resetiosflags(ios::left);

	system("pause");
}
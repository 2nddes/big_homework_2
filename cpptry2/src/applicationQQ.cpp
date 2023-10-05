#include"utils.h"
#include"applicationQQ.h"
#include"platform.h"
#include<iostream>


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

void applicationQQLA::init(userNodeLA*& curPlatformUser) {
	system("cls");

	m_allQQGroupList = new qqGroupListLA();

	m_allQQUserList = new qqUserListLA();

	if (curPlatformUser == nullptr) {
		m_currentUser = loginPage(curPlatformUser);
	}
	else {
		if (curPlatformUser->isQQEnabled()) {
			m_currentUser = m_allQQUserList->findBySuperPointer(curPlatformUser);
			mainPage();//TODO
		}
		else {
			cout << "ƽ̨�û� "
				<< curPlatformUser->getUserName() 
				<< " δ��ͨQQ����,�Ƿ�ͨ" << endl;
			cout << "1.��ͨ" << endl;
			cout << "2.����ͨ" << endl;
			int i = 2;
			cin >> i;
			refreshInput();
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
}

qqUserNodeLA* applicationQQLA::loginPage(userNodeLA*& curPlatformUser) {
	while(m_currentUser == nullptr)
	{
		system("cls");
		cout << "QQ��¼��������,ע��QQ��2,�˳���3" << endl;
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 2) {
			m_currentUser = registerPage(curPlatformUser);
			continue;
		}
		else if (i == 3) {
			exit();
			return nullptr;
		}
		cout << "������QQ��" << endl;
		int qqNumber;
		cin >> qqNumber;
		refreshInput();
		cout << "����������" << endl;
		string password;
		cin >> password;
		refreshInput();

		qqUserNodeLA* qqUser = m_allQQUserList->findByQQId(qqNumber);
		if (qqUser == nullptr) {
			cout << "QQ�Ų�����" << endl;
			system("pause");
			continue;
		}
		else {
			if (qqUser->getUserPasswd() == password) {
				string qqnumber = to_string(qqUser->getAppUserId());
				string path = "QQ\\" + qqnumber;
				My_mkdir(path.c_str());
				cout << "��¼�ɹ�" << endl;
				return qqUser;
			}
			else {
				cout << "�������" << endl;
				system("pause");
				return nullptr;
			}
		}

	}
	return m_currentUser;
}

qqUserNodeLA* applicationQQLA::registerPage(userNodeLA*& curPlatformUser) {
	cout << "QQע�������(�����ȵ�¼�������з����ٽ���QQע��) �˳�1" << endl;
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1)
		return nullptr;

	cout << "�����ǳ�" << endl;
	string userName;
	cin >> userName;
	refreshInput();
	cout << "��������" << endl;
	string password;
	cin >> password;
	refreshInput();
	cout << "ȷ��ע�ᰴ1" << endl;
	i = 0;
	cin >> i;
	refreshInput();
	if(i == 1) {
		
		if(curPlatformUser == nullptr) {
			curPlatformUser = m_platform->addPlatformUser();
			curPlatformUser->setQQStatus(true);
			qqUserNodeLA* p = m_allQQUserList->addQQUser(userName, password);
			p->setPlatformId(curPlatformUser->getID());
			m_allQQUserList->saveQQUserListData();

			cout << "ע��ɹ�" << endl;
			cout << "QQ��Ϊ" << p->getAppUserId() << endl;
			cout << "����Ϊ" << p->getUserPasswd() << endl;
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
	else {
		cout << "ȡ��ע��" << endl;
		system("pause");
		return nullptr;
	}
}

void applicationQQLA::exit() {
	m_allQQGroupList->saveGroupListData();
	delete m_allQQGroupList;
	m_allQQUserList->saveQQUserListData();
	delete m_allQQUserList;
	cout << "�˳�QQ" << endl;
	system("pause");
}
////////////////////////////////////////////////////
void applicationQQLA::mainPage() {
	while (1) {
		system("cls");
		cout << "1.����" << endl;
		cout << "2.Ⱥ" << endl;
		cout << "3.�˳�" << endl;
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
			exit();
			return;
		}
	}
}

//////////////////////////////////////////////////////
void applicationQQLA::friendPage() {//TODO
	while (1) {
		system("cls");
		showQQFriendList(m_currentUser->getQQFriendInfo());
		cout << "1.��������" << endl;
		cout << "2.��Ӻ���" << endl;
		cout << "3.ɾ������" << endl;
		cout << "4.����" << endl;
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			searchFriendPage();
		}
		else if (i == 2) {
			addFriendPage();
		}
		else if (i == 3) {
			deleteFriendPage();
		}
		else if (i == 4) {
			return;
		}
	}
}

void applicationQQLA::searchFriendPage() {
	cout<<"�������QQ��"<<endl;
	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	qqUserNodeLA* p = m_allQQUserList->findByQQId(qqNumber);
	if(p == nullptr) {
		cout<<"���Ѳ�����"<<endl;
		system("pause");
		return;
	}
	else {
		cout<<"���Ѵ���"<<endl;//TODO:����������֮����ʲô
		system("pause");
		return;
	}
}

void applicationQQLA::addFriendPage() {
	int sub = 0;
	int id;
	string name, subname;
	bool flag = false;
	system("CLS");
	cout << "��������Ӻ��ѵ�QQ��" << endl;
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

}

void applicationQQLA::deleteFriendPage() {
	cout << "�������QQ��" << endl;
	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	for (int i = 0; i < m_currentUser->getQQFriendInfo().size(); i++) {
		if (m_currentUser->getQQFriendInfo()[i].friendId == qqNumber) {
			cout << "ȷ��ɾ����1" << endl;
			int i = 0;
			cin >> i;
			refreshInput();
			if (i == 1) {
				m_currentUser->deleteQQFriendId(qqNumber);//TODO
				cout << "ɾ���ɹ�" << endl;
			}
			else {
				cout << "ȡ��ɾ��" << endl;
			}
			system("pause");
			return;
		}
	}
}

//////////////////////////////////////////////////////
void applicationQQLA::groupPage() {
	while (1) {
		system("cls");
		showQQGroupList(m_currentUser->getQQGroupId());
		cout << "0.ѡ��Ⱥ" << endl;
		cout << "1.����Ⱥ" << endl;
		cout << "2.����Ⱥ" << endl;
		cout << "3.����Ⱥ" << endl;
		cout << "4.�˳�Ⱥ" << endl;
		cout << "5.����" << endl;
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 0) {
			cout<<"����Ⱥ��"<<endl;
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
		if (i == 1) {
			searchGroupPage();
		}
		else if (i == 2) {
			createGroupPage();
		}
		else if (i == 3) {
			joinGroupPage();
		}
		else if (i == 4) {
			quitGroupPage();
		}
		else if (i == 5) {
			return;
		}
	}
}

void applicationQQLA::searchGroupPage() {
	cout << "����Ⱥ��" << endl;
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
		cout << "Ⱥ����" << endl;//TODO
		system("pause");
		return;
	}
}

void applicationQQLA::createGroupPage() {
	cout << "����Ⱥ��" << endl;
	string groupName;
	cin >> groupName;
	refreshInput();
	cout << "ȷ�ϴ�����1" << endl;
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		qqGroupNodeLA* p = m_allQQGroupList->addGroup(groupName, m_currentUser->getAppUserId());
		m_currentUser->addQQGroupId(p->getGroupId());
		cout << "�����ɹ�" << endl;
	}
	else {
		cout << "ȡ������" << endl;
	}
	system("pause");
	return;

}

void applicationQQLA::joinGroupPage() {
	cout << "����Ⱥ��" << endl;
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
		cout << p->getGroupName() << endl;
		cout << "ȷ�ϼ��밴1" << endl;
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			p->addMember(m_currentUser->getAppUserId());
			m_currentUser->addQQGroupId(p->getGroupId());
			cout << "�������ɹ�" << endl;
		}
		else {
			cout << "ȡ������" << endl;
		}
		system("pause");
		return;
	}
}

void applicationQQLA::quitGroupPage() {
	cout << "����Ⱥ��" << endl;
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
		cout << p->getGroupName() << endl;
		cout << "ȷ���˳���1" << endl;
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			p->removeMember(m_currentUser->getAppUserId());
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
	cout << "ȷ���˳���1" << endl;
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		groupPtr->removeMember(m_currentUser->getAppUserId());
		m_currentUser->deleteQQGroupId(groupPtr->getGroupId());
		cout << "�˳��ɹ�" << endl;
		system("pause");
		return;
	}
	else {
		cout << "ȡ���˳�" << endl;
	}
}

void applicationQQLA::chatInGroupPage(qqGroupNodeLA* groupPtr) {
	while(1)
	{
		//showMessageList()
		int userid = m_currentUser->getAppUserId();
		if(groupPtr->isOwner(userid)) {
			cout << "1.������Ϣ" << endl;
			cout << "2.�鿴Ⱥ��Ա" << endl;
			cout << "3.��ɢȺ" << endl;
			cout << "4.����Ⱥ" << endl;
			cout << "5.�����Ⱥ" << endl;
			cout << "6.����" << endl;
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
				cout << "ȷ�Ͻ�ɢ��1" << endl;
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
					}

					//�Ƴ�Ⱥ
					m_allQQGroupList->removeGroup(groupPtr);
					cout << "��ɢ�ɹ�" << endl;
					system("pause");
					return;
				}
				else {
					cout << "ȡ����ɢ" << endl;
				}
			}
			else if (i == 4) {
				setGroupConfigPage(groupPtr);
			}
			else if (i == 5) {
				inviteFriendInPage(groupPtr);
			}
			else if (i == 6) {
				return;
			}
		}
		else if (groupPtr->isAdministrator(userid)) {
			//TODO:����Ա����
		}
		else if(groupPtr->isMember(userid))
		{
			cout << "1.������Ϣ" << endl;
			cout << "2.�鿴Ⱥ��Ա" << endl;
			cout << "3.�����Ⱥ" << endl;
			cout << "4.�˳�Ⱥ" << endl;
			cout << "5.����" << endl;
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
				//TODO
			}
			else if (i == 4) {
				quitGroupPage(groupPtr);
			}
			else if (i == 5) {
				return;
			}
		}
	}
}

void applicationQQLA::setGroupConfigPage(qqGroupNodeLA* groupPtr) {
	//TODO
}

void applicationQQLA::inviteFriendInPage(qqGroupNodeLA* groupPtr){
	//TODO
}

void applicationQQLA::chatWithFriendPage(qqUserNodeLA* friendPtr) {
	while (1)
	{
		//showMessageList()
		cout << "1.������Ϣ" << endl;
		cout << "2.����" << endl;
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "ֱ�ӻس��ɷ���;������Ϣ�س�����:" << endl;
			char message[300];
			memset(message, 0, 300);
			cin.getline(message, 300);
			if (message[0] == '\0') {
				continue;
			}
			(sendMsgToFriend(friendPtr, message)) ? cout << "���ͳɹ�" << endl : cout << "����ʧ��" << endl;
		}
		else if (i == 2) {
			return;
		}
		else {
			cout << "�������" << endl;
		}
	}
}

void applicationQQLA::applyFriend(qqUserNodeLA* user, qqUserNodeLA* friendToAdd) {
	string path = "QQ\\" + to_string(user->getAppUserId()) + "\\friendApply.txt";
}

bool applicationQQLA::sendMsgToFriend(qqUserNodeLA* friendPtr, const char* msg) {
	//TODO
	return true;
}
bool applicationQQLA::sendMsgToGroup(qqGroupNodeLA* groupPtr, const char* msg) {
	//TODO
	return true;
}


void applicationQQLA::showQQFriendList(vector<userInfo> friendlist) {
	cout << "�����б�" << endl;
	for (int i = 0; i < friendlist.size(); i++) {
		cout << friendlist[i].friendName << " ";
		cout << friendlist[i].friendId << endl;
	}
	system("pause");
}

void applicationQQLA::showQQGroupList(vector<int> grouplist) {
	cout << "Ⱥ�б�" << endl;
	for (int i = 0; i < grouplist.size(); i++) {
		cout << grouplist[i] << endl;
	}
	system("pause");
}

void applicationQQLA::showGroupMemberPage(int groupId) {
	qqGroupNodeLA* groupPtr = m_allQQGroupList->findByGroupId(groupId);
	showGroupMemberPage(groupPtr);
}

void applicationQQLA::showGroupMemberPage(qqGroupNodeLA* groupPtr) {
	cout << "Ⱥ��Ա�б�" << endl;
	for (int i = 0; i < groupPtr->getQQGroupMemberInfoList().size(); i++) {
		cout << groupPtr->getQQGroupMemberInfoList()[i].friendId
			<< " " << groupPtr->getQQGroupMemberInfoList()[i].friendName << endl;
	}
	system("pause");
}
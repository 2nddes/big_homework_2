#define _CRT_SECURE_NO_WARNINGS
#include"/project/C++Project/cpptry2/cpptry2/src/utils.h"
#include"applicationQQ.h"
#include"/project/C++Project/cpptry2/cpptry2/src/platform.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<random>
#include"/project/C++Project/cpptry2/cpptry2/src/wechat_src/applicationWeChat.h"

void applicationQQLA::friendPage() {
	while (1) {
		system("cls");
		cout << "           ����" << endl;
		cout << "__________________________________" << endl;
		showQQFriendList(m_currentUser->getQQFriendInfo());

		cout << "| 01 || ѡ�����                  |" << endl;
		cout << "| 02 || ��Ӻ���                  |" << endl;
		cout << "| 03 || ɾ������                  |" << endl;
		cout << "| 04 || �鿴��������              |" << endl;
		cout << "| 00 || ����                      |" << endl;
		cout << "__________________________________" << endl;
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
	cout << "           ����" << endl;
	cout << "__________________________________" << endl;
	showQQFriendList(m_currentUser->getQQFriendInfo());
	if (m_currentUser->getQQFriendInfo().size() == 0) {
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
	while (1)
	{
		system("cls");
		cout << "         ��Ӻ���" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || ��QQ�����                |" << endl;
		cout << "| 02 || ���ǳ�����                |" << endl;
		cout << "| 03 || ���΢�ź��ѵ�qq��        |" << endl;
		cout << "| 00 || ����                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "����ѡ��:";
		int i = 0;
		cin >> i;
		refreshInput();

		if (i == 1) {
			addByQQIdPage();
		}
		else if (i == 2) {
			addBySearchFriendNamePage();
		}
		else if (i == 3) {
			addExternWeChatFriendPage();
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

void applicationQQLA::deleteFriendPage() {
	system("cls");
	cout << "           ɾ������" << endl;
	cout << "__________________________________" << endl;
	showQQFriendList(m_currentUser->getQQFriendInfo());
	if (m_currentUser->getQQFriendInfo().size() == 0) {
		system("pause");
		return;
	}
	cout << "�����ɾ������QQ��:";
	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	if (qqNumber == m_currentUser->getAppUserId()) {
		cout << "����ɾ���Լ�" << endl;
		system("pause");
		return;
	}
	int i = 0;
	for (i = 0; i < m_currentUser->getQQFriendInfo().size(); i++) {
		if (m_currentUser->getQQFriendInfo()[i].friendId == qqNumber) {
			system("cls");
			cout << "          �û���Ϣ" << endl;
			cout << "__________________________________" << endl;
			cout << "| QQ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_allQQUserList->findByQQId(qqNumber)->getAppUserId() << "|" << endl;
			cout << "| �ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_allQQUserList->findByQQId(qqNumber)->getUserName() << "|" << endl;
			cout << "__________________________________" << endl;
			cout << "| 01 || ȷ��ɾ��                  |" << endl;
			cout << "| 00 || ȡ��                      |" << endl;
			cout << "__________________________________" << endl;
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
			else if (i == 0) {
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
	while (1)
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
		cout << "__________________________________" << endl;
		cout << "|QQ��|          �� ��           |" << endl;
		cout << "__________________________________" << endl;
		for (int i = 0; i < qqNumberList.size(); i++) {
			cout << "|" << setw(4) << setfill(' ') << qqNumberList[i] << "|";
			cout << setw(26) << setfill(' ') << m_allQQUserList->findByQQId(qqNumberList[i])->getUserName() << "|" << endl;
			cout << "__________________________________" << endl;
		}
		cout << "| 01 || ͬ��                    |" << endl;
		cout << "| 02 || �ܾ�                    |" << endl;
		cout << "| 00 || ����                    |" << endl;
		cout << "__________________________________" << endl;
		cout << "����ѡ��:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "����ͬ��ĺ���QQ��:";
			int qqNumber = 0;
			cin >> qqNumber;
			refreshInput();
			if (count(qqNumberList.begin(), qqNumberList.end(), qqNumber) == 0) {
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
			for (int i = 0; i < qqNumberList.size(); i++) {
				if (qqNumberList[i] == qqNumber) {
					qqNumberList.erase(qqNumberList.begin() + i);
				}
			}

			//�����ļ�
			m_allQQUserList->saveQQUserListData();
			ofstream ofs(path, ios::out);
			for (auto i : qqNumberList) {
				ofs << i << " ";
			}
			ofs.close();
			cout << "���� " << friendToAddPtr->getUserName() << " ��ӳɹ�" << endl;
			system("pause");
			continue;
		}
		else if (i == 2) {
			cout << "����ܾ��ĺ���QQ��:";
			int qqNumber = 0;
			cin >> qqNumber;
			refreshInput();
			if (count(qqNumberList.begin(), qqNumberList.end(), qqNumber) == 0) {
				cout << "�������벻����" << endl;
				system("pause");
				continue;
			}
			//ɾ������
			for (int i = 0; i < qqNumberList.size(); i++) {
				if (qqNumberList[i] == qqNumber) {
					qqNumberList.erase(qqNumberList.begin() + i);
				}
			}

			//�����ļ�
			ofstream ofs(path, ios::out);
			for (auto i : qqNumberList) {
				ofs << i << " ";
			}
			ofs.close();
			cout << "�ܾ��ɹ�" << endl;
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

void applicationQQLA::chatWithFriendPage(qqUserNodeLA* friendPtr) {
	while (1)
	{
		system("cls");
		long long len = friendPtr->getUserName().length();
		cout << setw((40 - len) / 2) << setfill(' ') << friendPtr->getUserName() << endl;
		cout << "__________________________________" << endl;
		showMsg(recvMsgFromFriend(friendPtr));
		cout << "__________________________________" << endl;
		cout << "| 01 || ������Ϣ                  |" << endl;
		cout << "| 00 || ����                      |" << endl;
		cout << "__________________________________" << endl;
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

void applicationQQLA::addExternWeChatFriendPage() {
	while (1)
	{
		//��wechat��ת��Ϊqqָ��
		userNodeLA* curPlatformUser = m_platform->findPlatformUser(m_currentUser->getPlatformId());
		if (curPlatformUser->isWeChatEnabled() == false) {
			cout << "δ��ͨ΢�ŷ���" << endl;
			system("pause");
			return;
		}
		applicationWeChatLA* wcApp = new applicationWeChatLA();
		wcApp->loadData();

		WeChatUserNodeLA* curWeChatUser = wcApp->findBySuperPtr(curPlatformUser);
		if (curWeChatUser == nullptr) {
			cout << "δ��ͨ΢�ŷ���" << endl;
			system("pause");
			return;
		}
		//��wechat����ת��Ϊqq����
		vector<userInfo> wcFriendList = curWeChatUser->getWeChatFriendInfo();
		if (wcFriendList.size() == 0) {
			cout << "΢�ź����б�Ϊ��" << endl;
			system("pause");
			return;
		}
		struct qqExternFriend {
			int wechatfriendId;
			qqUserNodeLA* friendqqPtr;
		};
		vector<qqExternFriend> wechatFriendList;
		for (int i = 0; i < wechatFriendList.size(); i++) {
			int platformid = wcApp->findByWeChatId(wcFriendList[i].friendId)->getPlatformId();
			qqUserNodeLA* quserptr = m_allQQUserList->findBySuperId(platformid);
			if (quserptr == nullptr) {
				continue;
			}
			if (m_currentUser->isFriend(quserptr)) {
				continue;
			}
			struct qqExternFriend w { -1, nullptr };
			w.wechatfriendId = wcFriendList[i].friendId;
			w.friendqqPtr = quserptr;
			wechatFriendList.push_back(w);
		}
		wcApp->exit();
		delete wcApp;
		if (wechatFriendList.size() == 0) {
			cout << "û��qq���ѿ�ͨ΢�ŷ���" << endl;
			system("pause");
			return;
		}
		system("cls");
		cout << "          �û���Ϣ" << endl;
		cout << "__________________________________" << endl;
		for (int i = 0; i < wechatFriendList.size(); i++) {
			cout << "|΢��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << wechatFriendList[i].wechatfriendId << "|" << endl;
			cout << "|QQ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << wechatFriendList[i].friendqqPtr->getAppUserId() << "|" << endl;
			cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << wechatFriendList[i].friendqqPtr->getUserName() << "|" << endl;
			cout << "__________________________________" << endl;
		}
		cout << "| 01 || ��������                  |" << endl;
		cout << "|����|| ����                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "����ѡ��:";
		int i = 0;
		cin >> i;
		refreshInput();

		if (i == 1) {
			cout << "����Ҫ��ӵ�qq��:";
			int wId = 0;
			cin >> wId;
			refreshInput();
			qqUserNodeLA* friendToAddPtr = nullptr;
			for (int i = 0; i < wechatFriendList.size(); i++) {
				if (wechatFriendList[i].wechatfriendId == wId) {
					friendToAddPtr = wechatFriendList[i].friendqqPtr;
					break;
				}
			}
			if (friendToAddPtr == nullptr) {
				cout << "�û�������" << endl;
				system("pause");
				continue;
			}
			if (m_currentUser->isFriend(friendToAddPtr)) {
				cout << "�Ѿ��Ǻ���" << endl;
				system("pause");
				continue;
			}
			applyFriend(m_currentUser, friendToAddPtr);
			cout << "��������ɹ�" << endl;
			system("pause");
			continue;
		}
		else {
			cout << "ȡ�����" << endl;
			system("pause");
			continue;
		}
	}

}

void applicationQQLA::addBySearchFriendNamePage() {
	while (1)
	{
		system("cls");
		cout << "		 ������������" << endl;
		cout << "__________________________________" << endl;
		cout << "����Ҫ�������ǳ�,ֱ�ӻس�����:" << endl;
		string name;
		cin >> name;
		refreshInput();
		if (name == "") {
			return;
		}
		vector<userInfo> friendsToAdd = m_allQQUserList->searchByName(name);
		for (int i = 0; i < friendsToAdd.size(); i++) {
			if (m_currentUser->getAppUserId() == friendsToAdd[i].friendId) {
				friendsToAdd.erase(friendsToAdd.begin() + i);
				break;
			}
		}
		if (friendsToAdd.size() == 0) {
			cout << "�û�������" << endl;
			system("pause");
			return;
		}
		system("cls");
		cout << "          �û���Ϣ" << endl;
		cout << "__________________________________" << endl;
		for (int i = 0; i < friendsToAdd.size(); i++) {
			cout << "|QQ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendsToAdd[i].friendId << "|" << endl;
			cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendsToAdd[i].friendName << "|" << endl;
			cout << "__________________________________" << endl;
		}
		cout << "| 01 || ��������                  |" << endl;
		cout << "| 00 || ȡ��                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "����ѡ��:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "����Ҫ��ӵ�qq��:" << endl;
			int id = -1;
			cin >> id;
			refreshInput();
			if (id == m_currentUser->getAppUserId())
			{
				cout << "��������Լ�Ϊ����" << endl;
				system("pause");
				continue;
			}

			qqUserNodeLA* friendToAddPtr = m_allQQUserList->findByQQId(id);
			if (friendToAddPtr == nullptr) {
				cout << "�û�������" << endl;
				system("pause");
				continue;
			}
			if (m_currentUser->isFriend(friendToAddPtr)) {
				chatWithFriendPage(friendToAddPtr);
				system("pause");
				return;
			}
			system("cls");
			cout << "          �û���Ϣ" << endl;
			cout << "__________________________________" << endl;
			cout << "|΢��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendToAddPtr->getAppUserId() << "|" << endl;
			cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendToAddPtr->getUserName() << "|" << endl;
			cout << "__________________________________" << endl;
			cout << "| 01 || ��������                  |" << endl;
			cout << "|����|| ȡ�����                  |" << endl;
			cout << "__________________________________" << endl;
			cout << "����ѡ��:";
			int i = 0;
			cin >> i;
			refreshInput();
			if (i == 1) {
				applyFriend(m_currentUser, friendToAddPtr);
				cout << "��������ɹ�" << endl;
				system("pause");
				continue;
			}
			else {
				cout << "ȡ�����" << endl;
				system("pause");
				continue;
			}
		}
		else {
			cout << "ȡ�����" << endl;
			system("pause");
			continue;
		}
	}
}

void applicationQQLA::addByQQIdPage() {
	while (1)
	{
		system("cls");
		if (m_allQQUserList->size() > 1) {
			default_random_engine e((unsigned int)time(NULL));
			int id1 = e() % m_allQQUserList->size();
			if (id1 != m_currentUser->getAppUserId()) {
				qqUserNodeLA* p = m_allQQUserList->findByQQId(id1);
				if (!m_currentUser->isFriend(p)) {
					if (p != nullptr) {
						cout << "         �Ƽ�����" << endl;
						cout << "__________________________________" << endl;
						cout << "|QQ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getAppUserId() << "|" << endl;
						cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getUserName() << "|" << endl;
						cout << "__________________________________" << endl;
					}
				}			
				else {
					cout << "�����Ƽ�����" << endl;
				}
			}

		}
		

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
			cout << "�û�������" << endl;
			system("pause");
			return;
		}
		if (m_currentUser->isFriend(friendToAddPtr)) {
			cout << "�Ѿ��Ǻ���" << endl;
			system("pause");
			return;
		}
		system("cls");
		cout << "          �û���Ϣ" << endl;
		cout << "__________________________________" << endl;
		cout << "|QQ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendToAddPtr->getAppUserId() << "|" << endl;
		cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendToAddPtr->getUserName() << "|" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || ��������                  |" << endl;
		cout << "|����|| ȡ��                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "����ѡ��:";
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			applyFriend(m_currentUser, friendToAddPtr);
			cout << "��������ɹ�" << endl;
			system("pause");
			continue;
		}
		else {
			cout << "ȡ�����" << endl;
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

void applicationQQLA::inviteFriendInPage(qqGroupNodeLA* groupPtr) {
	if (!groupPtr->isAllowInvite()) {
		cout << "��Ⱥ��ǰ�������������" << endl;
		system("pause");
		return;
	}
	vector<userInfo> memberList = m_currentUser->getQQFriendInfo();
	if (memberList.size() == 0) {
		cout << "û�к��ѿ�����" << endl;
		system("pause");
		return;
	}
	system("cls");
	cout << "         ������ѽ�Ⱥ" << endl;
	cout << "__________________________________" << endl;
	showQQFriendList(memberList);

	cout << "����Ҫ����ĺ���QQ��:";
	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	if (groupPtr->isMember(qqNumber)) {
		cout << "���û��Ѿ���Ⱥ��" << endl;
		system("pause");
		return;
	}
	cout << "��1ȷ������:";
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		groupPtr->addMember(qqNumber);
		//���Ⱥ��
		qqUserNodeLA* p = m_allQQUserList->findByQQId(qqNumber);
		p->addQQGroupId(groupPtr->getGroupId());
		//���浽�ļ�
		m_allQQGroupList->saveGroupListData();
		m_allQQUserList->saveQQUserListData();
		cout << "����ɹ�" << endl;
		system("pause");
		return;
	}
	else {
		cout << "ȡ������" << endl;
		system("pause");
		return;
	}
}

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

vector<QMsg> applicationQQLA::recvMsgFromFriend(qqUserNodeLA* friendPtr)
{
	string path = "QQ\\" + to_string(m_currentUser->getAppUserId()) + "\\chatrecord\\" + to_string(friendPtr->getAppUserId()) + ".dat";
	//�ж��ļ��Ƿ����,�������򴴽�
	if (_access(path.c_str(), 0) == -1) {
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
	char msg[300];
	memset(msg, 0, 300);
	while (ifs >> id >> name >> time) {
		//��ȡһ���е�����,�����ո�
		ifs.ignore();
		ifs.getline(msg, 300);

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
//TODO:color
void applicationQQLA::showQQFriendList(vector<userInfo> friendlist)const {
	if (friendlist.size() == 0)
	{
		cout << "        ��û���κκ���" << endl;
		cout << "__________________________________" << endl;
		return;
	}
	cout << "����" << friendlist.size() << "������" << endl;
	cout << "__________________________________" << endl;

	for (int i = 0; i < friendlist.size(); i++) {
		cout << "|QQ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendlist[i].friendId << "|" << endl;
		cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendlist[i].friendName << "|" << endl;
		cout << "__________________________________" << endl;
	}
	cout << resetiosflags(ios::left);

	return;
}


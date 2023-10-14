#define _CRT_SECURE_NO_WARNINGS
#include"/project/C++Project/cpptry2/cpptry2/src/utils.h"
#include"applicationWeChat.h"
#include"/project/C++Project/cpptry2/cpptry2/src/platform.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<random>
#include"/project/C++Project/cpptry2/cpptry2/src/qq_src/applicationQQ.h"

void applicationWeChatLA::friendPage() {
	while (1) {
		system("cls");
		cout << "           ����" << endl;
		cout << "__________________________________" << endl;
		showWeChatFriendList(m_currentUser->getWeChatFriendInfo());

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

void applicationWeChatLA::selectFriendPage() {
	system("cls");
	cout << "           ����" << endl;
	cout << "__________________________________" << endl;
	showWeChatFriendList(m_currentUser->getWeChatFriendInfo());
	if (m_currentUser->getWeChatFriendInfo().size() == 0) {
		system("pause");
		return;
	}
	cout << "�������WeChat��:";
	int WeChatNumber = 0;
	cin >> WeChatNumber;
	refreshInput();
	if (m_currentUser->isFriend(WeChatNumber)) {
		chatWithFriendPage(m_allWeChatUserList->findByWeChatId(WeChatNumber));
	}
	else {
		cout << "δ�ҵ�����" << endl;
		system("pause");
		return;
	}
}

void applicationWeChatLA::sendMsgPage(WeChatUserNodeLA* friendPtr)
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

void applicationWeChatLA::addFriendPage() {
	while (1)
	{
		system("cls");
		cout << "         ��Ӻ���" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || ��΢�ź����              |" << endl;
		cout << "| 02 || ���ǳ�����                |" << endl;
		cout << "| 03 || ���QQ���ѵ�΢�ź�        |" << endl;
		cout << "| 00 || ����                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "����ѡ��:";
		int i = 0;
		cin >> i;
		refreshInput();

		if (i == 1) {
			addByWeChatIdPage();
		}
		else if (i == 2) {
			addBySearchFriendNamePage();
		}
		else if (i == 3) {
			addExternQQFriendPage();
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

void applicationWeChatLA::addExternQQFriendPage() {
	while (1)
	{
		//��wechat��ת��Ϊqqָ��
		userNodeLA* curPlatformUser = m_platform->findPlatformUser(m_currentUser->getPlatformId());
		if (curPlatformUser->isQQEnabled() == false) {
			cout << "δ��ͨQQ����" << endl;
			system("pause");
			return;
		}
		applicationQQLA* qqApp = new applicationQQLA();
		qqApp->loadData();

		qqUserNodeLA* curQQUser = qqApp->findBySuperPtr(curPlatformUser);
		if (curQQUser == nullptr) {
			cout << "δ��ͨQQ����" << endl;
			system("pause");
			return;
		}
		//��qq����ת��Ϊwechat����
		vector<userInfo> qqFriendList = curQQUser->getQQFriendInfo();
		if (qqFriendList.size() == 0) {
			cout << "QQ�����б�Ϊ��" << endl;
			system("pause");
			return;
		}
		struct WeChatExternFriend {
			int qqfriendId;
			WeChatUserNodeLA* friendWeChatPtr;
		};
		vector<WeChatExternFriend> wechatFriendList;
		for (int i = 0; i < qqFriendList.size(); i++) {
			int platformid = qqApp->findByQQId(qqFriendList[i].friendId)->getPlatformId();
			WeChatUserNodeLA* wuserptr = m_allWeChatUserList->findBySuperId(platformid);
			if (wuserptr == nullptr) {
				continue;
			}
			if (m_currentUser->isFriend(wuserptr)) {
				continue;
			}
			struct WeChatExternFriend w { -1, nullptr };
			w.qqfriendId = qqFriendList[i].friendId;
			w.friendWeChatPtr = wuserptr;
			wechatFriendList.push_back(w);
		}
		qqApp->exit();
		delete qqApp;

		if (wechatFriendList.size() == 0) {
			cout << "û��qq���ѿ�ͨ΢�ŷ���" << endl;
			system("pause");
			return;
		}
		system("cls");
		cout << "          �û���Ϣ" << endl;
		cout << "__________________________________" << endl;
		for (int i = 0; i < wechatFriendList.size(); i++) {
			cout << "|QQ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << wechatFriendList[i].qqfriendId << "|" << endl;
			cout << "|΢��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << wechatFriendList[i].friendWeChatPtr->getAppUserId() << "|" << endl;
			cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << wechatFriendList[i].friendWeChatPtr->getUserName() << "|" << endl;
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
			cout << "����Ҫ��ӵ�΢�ź�:";
			int wId = 0;
			cin >> wId;
			refreshInput();
			WeChatUserNodeLA* friendToAddPtr = nullptr;
			for (int i = 0; i < wechatFriendList.size(); i++) {
				if (wechatFriendList[i].qqfriendId == wId) {
					friendToAddPtr = wechatFriendList[i].friendWeChatPtr;
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

void applicationWeChatLA::addBySearchFriendNamePage()
{
	while (1) 
	{
		cout << "����Ҫ�������ǳ�:" << endl;
		string name;
		cin >> name;
		refreshInput();
		vector<userInfo> friendsToAdd = m_allWeChatUserList->searchByName(name);
		if (friendsToAdd.size() == 0) {
			cout << "�û�������" << endl;
			system("pause");
			return;
		}
		system("cls");
		cout << "          �û���Ϣ" << endl;
		cout << "__________________________________" << endl;
		for (int i = 0; i < friendsToAdd.size(); i++) {
			cout << "|΢��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendsToAdd[i].friendId << "|" << endl;
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
			cout << "����Ҫ��ӵ�WeChat��:" << endl;
			int id = -1;
			cin >> id;
			refreshInput();
			if (id == m_currentUser->getAppUserId())
			{
				cout << "�㲻������Լ�Ϊ����" << endl;
				system("pause");
				continue;
			}

			WeChatUserNodeLA* friendToAddPtr = m_allWeChatUserList->findByWeChatId(id);
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
	}
}

void applicationWeChatLA::addByWeChatIdPage()
{
	while (1) 
	{
		system("cls");
		if (m_allWeChatUserList->size() > 1) {
			default_random_engine e((unsigned int)time(NULL));
			int id1 = e() % m_allWeChatUserList->size();
			if (id1 != m_currentUser->getAppUserId()) {
				WeChatUserNodeLA* p = m_allWeChatUserList->findByWeChatId(id1);
				if (!m_currentUser->isFriend(p)) {
					if (p != nullptr) {
						cout << "		 �Ƽ�����" << endl;
						cout << "__________________________________" << endl;
						cout << "|΢��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getAppUserId() << "|" << endl;
						cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getUserName() << "|" << endl;
						cout << "__________________________________" << endl;
						cout << resetiosflags(ios::left);
					}
				}
			}
		}

		cout << "����Ҫ��ӵ�WeChat��:" << endl;
		int id;
		cin >> id;
		refreshInput();
		if (id == m_currentUser->getAppUserId())
		{
			cout << "�㲻������Լ�Ϊ����" << endl;
			system("pause");
			return;
		}

		WeChatUserNodeLA* friendToAddPtr = m_allWeChatUserList->findByWeChatId(id);
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
		cout << "|΢��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendToAddPtr->getAppUserId() << "|" << endl;
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

void applicationWeChatLA::deleteFriendPage() {
	system("cls");
	cout << "           ɾ������" << endl;
	cout << "__________________________________" << endl;
	showWeChatFriendList(m_currentUser->getWeChatFriendInfo());
	if (m_currentUser->getWeChatFriendInfo().size() == 0) {
		system("pause");
		return;
	}
	cout << "�����ɾ������WeChat��:";
	int WeChatNumber = 0;
	cin >> WeChatNumber;
	refreshInput();
	if (WeChatNumber == m_currentUser->getAppUserId()) {
		cout << "����ɾ���Լ�" << endl;
		system("pause");
		return;
	}
	int i = 0;
	for (i = 0; i < m_currentUser->getWeChatFriendInfo().size(); i++) {
		if (m_currentUser->getWeChatFriendInfo()[i].friendId == WeChatNumber) {
			system("cls");
			cout << "          �û���Ϣ" << endl;
			cout << "__________________________________" << endl;
			cout << "|΢��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_allWeChatUserList->findByWeChatId(WeChatNumber)->getAppUserId() << "|" << endl;
			cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_allWeChatUserList->findByWeChatId(WeChatNumber)->getUserName() << "|" << endl;
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
				m_allWeChatUserList->findByWeChatId(WeChatNumber)->deleteWeChatFriendId(m_currentUser->getAppUserId());
				m_currentUser->deleteWeChatFriendId(WeChatNumber);
				m_allWeChatUserList->saveWeChatUserListData();
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
	if (i == m_currentUser->getWeChatFriendInfo().size()) {
		cout << "���Ǻ���" << endl;
		system("pause");
		return;
	}
}

void applicationWeChatLA::friendRequestPage() {
	string path = "WeChat\\" + to_string(m_currentUser->getAppUserId()) + "\\friendrequest.dat";
	while (1)
	{
		system("cls");
		ifstream ifs(path, ios::in);
		if (!ifs.is_open()) {
			cout << "���ļ�ʧ��" << endl;
			return;
		}
		vector<int> WeChatNumberList;
		while (!ifs.eof()) {
			int WeChatNumber = -1;
			ifs >> WeChatNumber;
			if (WeChatNumber == -1) {
				break;
			}
			WeChatNumberList.push_back(WeChatNumber);
		}
		ifs.close();
		if (WeChatNumberList.size() == 0) {
			cout << "Ŀǰû�к�������" << endl;
			system("pause");
			return;
		}

		system("cls");
		cout << "         ���������б�" << endl;
		cout << "__________________________________" << endl;
		cout << "|΢��|          �� ��           |" << endl;
		cout << "__________________________________" << endl;
		for (int i = 0; i < WeChatNumberList.size(); i++) {
			cout << "|" << setw(4) << setfill(' ') << WeChatNumberList[i] << "|";
			cout << setw(26) << setfill(' ') << m_allWeChatUserList->findByWeChatId(WeChatNumberList[i])->getUserName() << "|" << endl;
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
			cout << "����ͬ��ĺ���WeChat��:";
			int WeChatNumber = 0;
			cin >> WeChatNumber;
			refreshInput();
			if (count(WeChatNumberList.begin(), WeChatNumberList.end(), WeChatNumber) == 0) {
				cout << "�û�������" << endl;
				system("pause");
				continue;
			}
			WeChatUserNodeLA* friendToAddPtr = m_allWeChatUserList->findByWeChatId(WeChatNumber);
			//������Ӻ���
			userInfo info;
			info.friendId = friendToAddPtr->getAppUserId();
			info.friendName = friendToAddPtr->getUserName();
			m_currentUser->addWeChatFriendInfo(info);
			info.friendId = m_currentUser->getAppUserId();
			info.friendName = m_currentUser->getUserName();
			friendToAddPtr->addWeChatFriendInfo(info);
			//ɾ������
			for (int i = 0; i < WeChatNumberList.size(); i++) {
				if (WeChatNumberList[i] == WeChatNumber) {
					WeChatNumberList.erase(WeChatNumberList.begin() + i);
				}
			}

			//�����ļ�
			m_allWeChatUserList->saveWeChatUserListData();
			ofstream ofs(path, ios::out);
			for (auto i : WeChatNumberList) {
				ofs << i << " ";
			}
			ofs.close();
			cout << "���� " << friendToAddPtr->getUserName() << " ��ӳɹ�" << endl;
			system("pause");
			continue;
		}
		else if (i == 2) {
			cout << "����ܾ��ĺ���WeChat��:";
			int WeChatNumber = 0;
			cin >> WeChatNumber;
			refreshInput();
			if (count(WeChatNumberList.begin(), WeChatNumberList.end(), WeChatNumber) == 0) {
				cout << "�������벻����" << endl;
				system("pause");
				continue;
			}
			//ɾ������
			for (int i = 0; i < WeChatNumberList.size(); i++) {
				if (WeChatNumberList[i] == WeChatNumber) {
					WeChatNumberList.erase(WeChatNumberList.begin() + i);
				}
			}

			//�����ļ�
			ofstream ofs(path, ios::out);
			for (auto i : WeChatNumberList) {
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

void applicationWeChatLA::chatWithFriendPage(WeChatUserNodeLA* friendPtr) {
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

void applicationWeChatLA::applyFriend(WeChatUserNodeLA* user, WeChatUserNodeLA* friendToAdd) {
	string path = "WeChat\\" + to_string(friendToAdd->getAppUserId()) + "\\friendrequest.dat";
	//�ں��ѵ������б����������
	ofstream ofs(path, ios::app);
	if (!ofs.is_open()) {
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	ofs << user->getAppUserId() << endl;
	ofs.close();

}

void applicationWeChatLA::inviteFriendInPage(WeChatGroupNodeLA* groupPtr) {
	if (!groupPtr->isAllowInvite()) {
		cout << "��Ⱥ��ǰ�������������" << endl;
		system("pause");
		return;
	}
	vector<userInfo> memberList = m_currentUser->getWeChatFriendInfo();
	if (memberList.size() == 0) {
		cout << "û�к��ѿ�����" << endl;
		system("pause");
		return;
	}
	system("cls");
	cout << "         ������ѽ�Ⱥ" << endl;
	cout << "__________________________________" << endl;
	showWeChatFriendList(memberList);

	cout << "����Ҫ����ĺ���WeChat��:";
	int WeChatNumber = 0;
	cin >> WeChatNumber;
	refreshInput();
	if (groupPtr->isMember(WeChatNumber)) {
		cout << "���û��Ѿ���Ⱥ��" << endl;
		system("pause");
		return;
	}
	cout << "��1ȷ������:";
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		groupPtr->addMember(WeChatNumber);
		//���Ⱥ��
		WeChatUserNodeLA* p = m_allWeChatUserList->findByWeChatId(WeChatNumber);
		p->addWeChatGroupId(groupPtr->getGroupId());
		//���浽�ļ�
		m_allWeChatGroupList->saveGroupListData();
		m_allWeChatUserList->saveWeChatUserListData();
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

bool applicationWeChatLA::sendMsgToFriend(WeChatUserNodeLA* friendPtr, const char* msg) {
	string path = "WeChat\\" + to_string(friendPtr->getAppUserId()) + "\\chatrecord\\" + to_string(m_currentUser->getAppUserId()) + ".dat";
	//��ȡʱ��
	string time = getTime();
	//�򿪺��ѵ�chatrecord�ļ�д�뷢����WeChat��,�������ǳ�,����ʱ��,��Ϣ����
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

	//���Լ���chatrecord�ļ�д�뷢����WeChat��,�������ǳ�,����ʱ��,��Ϣ����
	path = "WeChat\\" + to_string(m_currentUser->getAppUserId()) + "\\chatrecord\\" + to_string(friendPtr->getAppUserId()) + ".dat";
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

vector<WMsg> applicationWeChatLA::recvMsgFromFriend(WeChatUserNodeLA* friendPtr)
{
	string path = "WeChat\\" + to_string(m_currentUser->getAppUserId()) + "\\chatrecord\\" + to_string(friendPtr->getAppUserId()) + ".dat";
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
	vector<WMsg> msgList;
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
		WMsg wmsg;
		wmsg.senderId = id;
		wmsg.senderName = name;
		wmsg.time = time;
		wmsg.msg = msg;
		//ѹ����Ϣ�б�
		msgList.push_back(wmsg);
	}

	return msgList;
}
//TODO:color
void applicationWeChatLA::showWeChatFriendList(vector<userInfo> friendlist) {
	if (friendlist.size() == 0)
	{
		cout << "        ��û���κκ���" << endl;
		cout << "__________________________________" << endl;
		return;
	}
	cout << "����" << friendlist.size() << "������" << endl;
	cout << "__________________________________" << endl;

	for (int i = 0; i < friendlist.size(); i++) {
		cout << "|΢��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendlist[i].friendId << "|" << endl;
		cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendlist[i].friendName << "|" << endl;
		cout << "__________________________________" << endl;
	}
	cout << resetiosflags(ios::left);

	return;
}
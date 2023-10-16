#define _CRT_SECURE_NO_WARNINGS
#include"/project/C++Project/cpptry2/cpptry2/src/utils.h"
#include"applicationWeChat.h"
#include"/project/C++Project/cpptry2/cpptry2/src/platform.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<random>

void applicationWeChatLA::groupPage() {
	while (1) {
		system("cls");
		cout << "           Ⱥ��" << endl;
		cout << "__________________________________" << endl;
		showWeChatGroupList(m_currentUser->getWeChatGroupId());
		cout << "| 01 || ѡ��Ⱥ                    |" << endl;
		cout << "| 02 || ����Ⱥ                    |" << endl;
		cout << "| 03 || ����Ⱥ                    |" << endl;
		cout << "| 04 || ����Ⱥ                    |" << endl;
		cout << "| 05 || �˳�Ⱥ                    |" << endl;
		cout << "| 00 || ����                      |" << endl;
		cout << "__________________________________" << endl;
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

void applicationWeChatLA::selectGroupPage()
{
	system("cls");
	cout << "         ѡ��Ⱥ��" << endl;
	showWeChatGroupList(m_currentUser->getWeChatGroupId());
	if (m_currentUser->getWeChatGroupId().size() == 0) {
		system("pause");
		return;
	}
	cout << "����Ⱥ��:";

	int groupId = 0;
	cin >> groupId;
	refreshInput();
	WeChatGroupNodeLA* p = m_allWeChatGroupList->findByGroupId(groupId);
	if (p == nullptr) {
		cout << "Ⱥ������" << endl;
		system("pause");
		return;
	}
	else {
		chatInGroupPage(p);
	}
}

void applicationWeChatLA::chatInGroupPage(WeChatGroupNodeLA* groupPtr) {
	while (1)
	{
		system("cls");
		cout << setw(20) << setfill(' ') << groupPtr->getGroupName() << endl;

		int userid = m_currentUser->getAppUserId();
		if (groupPtr->isOwner(userid)) {
			cout << "__________________________________" << endl;
			showMsg(recvMsgFromGroup(groupPtr));
			cout << "__________________________________" << endl;
			cout << "| 01 || ������Ϣ                  |" << endl;
			cout << "| 02 || �鿴Ⱥ��Ա                |" << endl;
			cout << "| 03 || ��ɢȺ                    |" << endl;
			cout << "| 04 || ����Ⱥ                    |" << endl;
			cout << "| 05 || �����Ⱥ                  |" << endl;
			cout << "| 06 || �߳�Ⱥ��Ա                |" << endl;
			cout << "| 07 || �鿴Ⱥ����                |" << endl;
			cout << "| 08 || ���ù���Ա                |" << endl;
			cout << "| 09 || ����Ⱥ�ǳ�                |" << endl;
			cout << "| 10 || ��������¼              |" << endl;
			cout << "| 11 || ���������¼			      |" << endl;
			cout << "| 00 || ����                      |" << endl;
			cout << "__________________________________" << endl;
			cout << "����ѡ��:";

			int i = 0;
			cin >> i;
			refreshInput();
			if (i == 1) {
				sendMsgPage(groupPtr);
			}
			else if (i == 2) {
				showGroupMemberList(groupPtr);
			}
			else if (i == 3) {
				if (disbandGroupPage(groupPtr)) {
					return;
				}
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
			else if (i == 9) {
				setGroupNickNamePage(groupPtr);
			}
			else if (i == 10) {
				clearChatRecord(groupPtr);
			}
			else if (i == 11) {
				searchChatRecordPage(groupPtr);
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
			cout << "__________________________________" << endl;
			showMsg(recvMsgFromGroup(groupPtr));
			cout << "__________________________________" << endl;
			cout << "| 01 || ������Ϣ                  |" << endl;
			cout << "| 02 || �鿴Ⱥ��Ա                |" << endl;
			cout << "| 03 || �����Ⱥ                  |" << endl;
			cout << "| 04 || �˳�Ⱥ                    |" << endl;
			cout << "| 05 || �鿴Ⱥ����                |" << endl;
			cout << "| 06 || �߳�Ⱥ��Ա                |" << endl;
			cout << "| 07 || ����Ⱥ�ǳ�                |" << endl;
			cout << "| 08 || ��������¼              |" << endl;
			cout << "| 09 || ���������¼              |" << endl;
			cout << "| 00 || ����                      |" << endl;
			cout << "__________________________________" << endl;
			cout << "����ѡ��:";

			int i = 0;
			cin >> i;
			refreshInput();
			if (i == 1) {
				sendMsgPage(groupPtr);
			}
			else if (i == 2) {
				showGroupMemberList(groupPtr);
			}
			else if (i == 3) {
				inviteFriendInPage(groupPtr);
			}
			else if (i == 4) {
				if (quitGroupPage(groupPtr))
					return;
			}
			else if (i == 5) {
				groupRequestPage(groupPtr);
			}
			else if (i == 6) {
				kickMemberPage(groupPtr);
			}
			else if (i == 7) {
				setGroupNickNamePage(groupPtr);
			}
			else if (i == 8) {
				clearChatRecord(groupPtr);
			}
			else if (i == 9) {
				searchChatRecordPage(groupPtr);
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
		else if (groupPtr->isMember(userid)) {
			cout << "__________________________________" << endl;
			showMsg(recvMsgFromGroup(groupPtr));
			cout << "__________________________________" << endl;
			cout << "| 01 || ������Ϣ                  |" << endl;
			cout << "| 02 || �鿴Ⱥ��Ա                |" << endl;
			cout << "| 03 || �����Ⱥ                  |" << endl;
			cout << "| 04 || �˳�Ⱥ                    |" << endl;
			cout << "| 05 || ����Ⱥ�ǳ�                |" << endl;
			cout << "| 06 || ��������¼              |" << endl;
			cout << "| 07 || ���������¼              |" << endl;
			cout << "| 00 || ����                      |" << endl;
			cout << "__________________________________" << endl;
			cout << "����ѡ��:";

			int i = 0;
			cin >> i;
			refreshInput();
			if (i == 1) {
				sendMsgPage(groupPtr);
			}
			else if (i == 2) {
				showGroupMemberList(groupPtr);
			}
			else if (i == 3) {
				inviteFriendInPage(groupPtr);
			}
			else if (i == 4) {
				if (quitGroupPage(groupPtr))
					return;
			}
			else if (i == 5) {
				setGroupNickNamePage(groupPtr);
			}
			else if (i == 6) {
				clearChatRecord(groupPtr);
			}
			else if (i == 7) {
				searchChatRecordPage(groupPtr);
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
			cout << "__________________________________" << endl;
			cout << "| 01 || �鿴Ⱥ��Ա                |" << endl;
			cout << "| 02 || �������Ⱥ                |" << endl;
			cout << "| 00 || ����                      |" << endl;
			cout << "__________________________________" << endl;
			cout << "����ѡ��:";

			int i = 0;
			cin >> i;
			refreshInput();
			if (i == 1) {
				showGroupMemberList(groupPtr);
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
				m_allWeChatGroupList->saveGroupListData();
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

void applicationWeChatLA::setAdminPage(WeChatGroupNodeLA* groupPtr)
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
	cout << "__________________________________" << endl;
	showGroupMemberList(groupPtr);

	cout << "����Ҫ���õ�WeChat��:";

	int WeChatNumber = 0;
	cin >> WeChatNumber;
	refreshInput();
	if (!groupPtr->isMember(WeChatNumber)) {
		cout << "���û�����Ⱥ��Ա" << endl;
		system("pause");
		return;
	}
	if (groupPtr->isOwner(WeChatNumber)) {
		cout << "����Ⱥ��" << endl;
		system("pause");
		return;
	}
	if (groupPtr->isAdministrator(WeChatNumber)) {
		cout << m_allWeChatUserList->findByWeChatId(WeChatNumber)->getUserName() << "�ǹ���Ա" << endl;
		cout << "����1���䳷������Ա" << endl;

		int i = 0;
		cin >> i;
		refreshInput();

		if (i == 1) {
			groupPtr->removeWeChatGroupAdmin(WeChatNumber);
			m_allWeChatGroupList->saveGroupListData();
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
		cout << m_allWeChatUserList->findByWeChatId(WeChatNumber)->getUserName() << "���ǹ���Ա" << endl;
		cout << "����1��������Ϊ����Ա" << endl;
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			groupPtr->addWeChatGroupAdmin(WeChatNumber);
			m_allWeChatGroupList->saveGroupListData();
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

void applicationWeChatLA::setGroupNickNamePage(WeChatGroupNodeLA* groupPtr) {
	system("cls");
	cout << "         ����Ⱥ�ǳ�" << endl;
	cout << "__________________________________" << endl;
	cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupNickName(m_currentUser->getAppUserId()) << "|" << endl;
	cout << "__________________________________" << endl;
	cout << "�����µ��ǳ�(�����ո�������ַ�):" << endl;
	string nickName;
	cin >> nickName;
	refreshInput();
	groupPtr->setGroupNickName(m_currentUser->getAppUserId(), nickName);
	m_allWeChatGroupList->saveGroupListData();

	cout << "������" << endl;
	system("pause");
	return;

}

void applicationWeChatLA::searchChatRecordPage(WeChatGroupNodeLA* groupPtr)
{
	system("cls");
	cout << "         ���������¼" << endl;
	cout << "__________________________________" << endl;
	cout << "����Ҫ���ҵ�����:" << endl;
	string content;
	cin >> content;
	refreshInput();

	vector<WMsg> recordList = recvMsgFromGroup(groupPtr);
	for (int i = 0; i < recordList.size(); i++) {
		if (recordList[i].msg.find(content) == string::npos) {
			recordList.erase(recordList.begin() + i);
			i--;
		}
	}
	system("cls");
	showMsg(recordList);
	system("pause");
	return;
}

void applicationWeChatLA::searchGroupPage() {
	system("cls");
	cout << "����Ⱥ��:" << endl;
	int groupId = 0;
	cin >> groupId;
	refreshInput();
	WeChatGroupNodeLA* p = m_allWeChatGroupList->findByGroupId(groupId);
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

void applicationWeChatLA::sendMsgPage(WeChatGroupNodeLA* groupPtr)
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

void applicationWeChatLA::createGroupPage() {
	system("cls");
	cout << "            ����Ⱥ��" << endl;
	cout << "__________________________________" << endl;
	cout << "����Ⱥ��(�����ո�������ַ�):";
	string groupName;
	cin >> groupName;
	refreshInput();
	cout << "��1ȷ�ϴ���:";
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		WeChatGroupNodeLA* p = m_allWeChatGroupList->addGroup(groupName, m_currentUser->getAppUserId());

		m_currentUser->addWeChatGroupId(p->getGroupId());
		//�����ļ�
		m_allWeChatGroupList->saveGroupListData();
		m_allWeChatUserList->saveWeChatUserListData();
		system("cls");
		cout << "            �����ɹ�" << endl;
		cout << "__________________________________" << endl;
		cout << "| Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupId() << "|" << endl;
		cout << "| Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupName() << "|" << endl;
		cout << "__________________________________" << endl;
	}
	else {
		cout << "ȡ������" << endl;
	}
	system("pause");
	return;

}

void applicationWeChatLA::joinGroupPage() {
	system("cls");
	if (m_allWeChatGroupList->size() == 0) {
		cout << "û��Ⱥ�ɼ���" << endl;
		system("pause");
		return;
	}

	default_random_engine e((unsigned int)time(NULL));
	int id1 = 1001 + e() % m_allWeChatGroupList->size();
	if (!m_currentUser->isAddedGroup(id1)) {
		WeChatGroupNodeLA* p = m_allWeChatGroupList->findByGroupId(id1);
		if (p != nullptr) {
			cout << "            �Ƽ�Ⱥ��" << endl;
			cout << "__________________________________" << endl;
			cout << "|Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << id1 << "|" << endl;
			cout << "|Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_allWeChatGroupList->findByGroupId(id1)->getGroupName() << "|" << endl;
			cout << "__________________________________" << endl;
			cout << resetiosflags(ios::left);

		}
	}
	cout << "����Ҫ��ӵ�Ⱥ��:";

	int groupId = 0;
	cin >> groupId;
	refreshInput();
	if (m_currentUser->isAddedGroup(groupId)) {
		cout << "�Ѿ���Ⱥ��" << endl;
		system("pause");
		return;
	}
	WeChatGroupNodeLA* p = m_allWeChatGroupList->findByGroupId(groupId);
	if (p == nullptr) {
		cout << "Ⱥ������" << endl;
		system("pause");
		return;
	}
	else {
		system("cls");
		cout << "         ����Ⱥ��" << endl;
		cout << "__________________________________" << endl;
		cout << "|Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupId() << "|" << endl;
		cout << "|Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupName() << "|" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || �������                  |" << endl;
		cout << "|����|| ����                      |" << endl;
		cout << "__________________________________" << endl;
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
			m_allWeChatGroupList->saveGroupListData();

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

bool applicationWeChatLA::disbandGroupPage(WeChatGroupNodeLA* groupPtr)
{
	system("cls");
	if (!groupPtr->isOwner(m_currentUser->getAppUserId())) {
		cout << "����Ⱥ��,�޷���ɢȺ" << endl;
		system("pause");
		return false;
	}
	cout << "         ��ɢȺ��" << endl;
	cout << "__________________________________" << endl;
	cout << "|Ⱥ��|| " << setw(24) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupId() << "|" << endl;
	cout << "|Ⱥ��|| " << setw(24) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupName() << "|" << endl;
	cout << "__________________________________" << endl;
	cout << "| 01 || ȷ�Ͻ�ɢ(����ɾ�������¼!)|" << endl;
	cout << "|����|| ����                      |" << endl;
	cout << "__________________________________" << endl;
	cout << "����ѡ��:";

	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		//ɾ��ÿ���û����洢��Ⱥ��
		int groupId = groupPtr->getGroupId();
		vector<userInfo> memberList = groupPtr->getWeChatGroupMemberInfoList();
		for (int i = 0; i < memberList.size(); i++) {
			WeChatUserNodeLA* p = m_allWeChatUserList->findByWeChatId(memberList[i].friendId);
			p->deleteWeChatGroupId(groupId);
			//ɾ�������ļ�
			string path = "WeChat\\" + to_string(p->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupId) + ".dat";
			if (_access(path.c_str(), 0) != -1) {
				remove(path.c_str());
			}
		}

		//�Ƴ�Ⱥ
		m_allWeChatGroupList->removeGroup(groupPtr);
		//���浽�ļ�
		m_allWeChatGroupList->saveGroupListData();
		m_allWeChatUserList->saveWeChatUserListData();
		cout << "��ɢ�ɹ�" << endl;
		system("pause");
		return true;
	}
	else {
		cout << "ȡ����ɢ" << endl;
		system("pause");
		return false;
	}
}

bool applicationWeChatLA::quitGroupPage() {
	system("cls");
	cout << "         �˳�Ⱥ��" << endl;
	cout << "__________________________________" << endl;
	showWeChatGroupList(m_currentUser->getWeChatGroupId());
	if (m_currentUser->getWeChatGroupId().size() == 0) {
		cout << "û��Ⱥ���˳�" << endl;
		system("pause");
		return false;
	}
	cout << "����Ⱥ��:" << endl;
	int groupId = 0;
	cin >> groupId;
	refreshInput();
	WeChatGroupNodeLA* p = m_allWeChatGroupList->findByGroupId(groupId);
	if (!m_currentUser->isAddedGroup(groupId)) {
		cout << "Ⱥ������" << endl;
		system("pause");
		return false;
	}
	else if (p->isOwner(m_currentUser->getAppUserId())) {
		cout << "Ⱥ���޷��˳�Ⱥ��,�볢�Խ�ɢȺ" << endl;
		system("pause");
		return false;
	}
	else {
		system("cls");
		cout << "         �˳�Ⱥ��" << endl;
		cout << "__________________________________" << endl;
		cout << "| Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupId() << "|" << endl;
		cout << "| Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupName() << "|" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || ȷ���˳�(����ɾ�������¼!)|" << endl;
		cout << "|����|| ����                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "����ѡ��:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			//�໥ɾ��
			if (p->isAdministrator(m_currentUser->getAppUserId())) {
				p->removeWeChatGroupAdmin(m_currentUser->getAppUserId());
			}
			p->removeMember(m_currentUser->getAppUserId());
			m_currentUser->deleteWeChatGroupId(p->getGroupId());
			//���浽�ļ�
			m_allWeChatGroupList->saveGroupListData();
			m_allWeChatUserList->saveWeChatUserListData();
			string path = "WeChat\\" + to_string(m_currentUser->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupId) + ".dat";
			if (_access(path.c_str(), 0) != -1) {
				remove(path.c_str());
			}

			cout << "�˳��ɹ�" << endl;
			system("pause");
			return true;
		}
		else {
			cout << "ȡ���˳�" << endl;
			system("pause");
			return false;
		}
	}
	return true;
}

bool applicationWeChatLA::quitGroupPage(WeChatGroupNodeLA* groupPtr) {
	if (groupPtr->isOwner(m_currentUser->getAppUserId())) {
		cout << "Ⱥ���޷��˳�Ⱥ��,�볢�Խ�ɢȺ" << endl;
		system("pause");
		return false;
	}
	system("cls");
	cout << "         �˳�Ⱥ��" << endl;
	cout << "__________________________________" << endl;
	cout << "| Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupId() << "|" << endl;
	cout << "| Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupName() << "|" << endl;
	cout << "__________________________________" << endl;
	cout << "| 01 || ȷ���˳�(����ɾ�������¼!)|" << endl;
	cout << "|����|| ����                      |" << endl;
	cout << "__________________________________" << endl;
	cout << "����ѡ��:";

	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		//�໥ɾ��
		if (groupPtr->isAdministrator(m_currentUser->getAppUserId())) {
			groupPtr->removeWeChatGroupAdmin(m_currentUser->getAppUserId());
		}
		groupPtr->removeMember(m_currentUser->getAppUserId());
		m_currentUser->deleteWeChatGroupId(groupPtr->getGroupId());
		//���浽�ļ�
		m_allWeChatGroupList->saveGroupListData();
		m_allWeChatUserList->saveWeChatUserListData();
		string path = "WeChat\\" + to_string(m_currentUser->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupPtr->getGroupId()) + ".dat";
		if (_access(path.c_str(), 0) != -1) {
			remove(path.c_str());
		}

		cout << "�˳��ɹ�" << endl;
		system("pause");
		return true;
	}
	else {
		cout << "ȡ���˳�" << endl;
		system("pause");
		return false;
	}
}

void applicationWeChatLA::setGroupConfigPage(WeChatGroupNodeLA* groupPtr) {
	while (1)
	{
		system("cls");
		cout << setw(20) << setfill(' ') << groupPtr->getGroupName() << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || �޸�Ⱥ��                  |" << endl;
		cout << "| 02 || �Ƿ����������Ⱥ          |" << endl;
		cout << "| 03 || �Ƿ�������������          |" << endl;
		cout << "| 04 || �Ƿ�������              |" << endl;
		cout << "| 05 || �Ƿ��������ù���Ա        |" << endl;
		cout << "| 06 || �Ƿ�Ⱥ��Ա��ʱ�Ự        |" << endl;
		cout << "| 00 || ����                      |" << endl;
		cout << "__________________________________" << endl;
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
			groupPtr->setWeChatGroupName(groupName);
			m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowInvite(false);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowInvite(true);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowJoin(false);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowJoin(true);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowSend(false);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowSend(true);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowAdmins(false);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowAdmins(true);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowSubgroup(false);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowSubgroup(true);
					m_allWeChatGroupList->saveGroupListData();
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


void applicationWeChatLA::kickMemberPage(WeChatGroupNodeLA* groupPtr)
{
	system("cls");
	cout << "         �߳�Ⱥ��Ա" << endl;
	cout << "__________________________________" << endl;
	showGroupMemberList(groupPtr);

	cout << "����Ҫ�߳���Ⱥ��ԱWeChat��:";
	int WeChatNumber = 0;
	cin >> WeChatNumber;
	refreshInput();
	if (!groupPtr->isMember(WeChatNumber)) {
		cout << "���û�����Ⱥ��Ա" << endl;
		system("pause");
		return;
	}
	if (groupPtr->isOwner(WeChatNumber)) {
		cout << "�����߳�Ⱥ��" << endl;
		system("pause");
		return;
	}
	if (m_currentUser->getAppUserId() == WeChatNumber) {
		cout << "�����߳��Լ�,�����˳�Ⱥ" << endl;
		return;
	}
	cout << "ȷ���߳���1" << endl;
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		//ɾ���û����洢��Ⱥ��
		int groupId = groupPtr->getGroupId();
		WeChatUserNodeLA* p = m_allWeChatUserList->findByWeChatId(WeChatNumber);
		p->deleteWeChatGroupId(groupId);

		//�Ƴ��û�
		groupPtr->removeMember(WeChatNumber);
		//���浽�ļ�
		m_allWeChatGroupList->saveGroupListData();
		m_allWeChatUserList->saveWeChatUserListData();
		string path = "WeChat\\" + to_string(WeChatNumber) + "\\groupchatrecord\\" + to_string(groupId) + ".dat";
		if (_access(path.c_str(), 0) != -1) {
			remove(path.c_str());
		}

		cout << "�߳��ɹ�" << endl;
		system("pause");
	}
	else {
		cout << "ȡ���߳�" << endl;
		system("pause");
	}

}

void applicationWeChatLA::groupRequestPage(WeChatGroupNodeLA* groupPtr) {
	while (1)
	{
		if (!groupPtr->isAdministrator(m_currentUser->getAppUserId()) && !groupPtr->isOwner(m_currentUser->getAppUserId())) {
			cout << "��Ȩ��������";
			system("pause");
			return;
		}

		vector<userInfo> requestList = groupPtr->getWeChatGroupRequestInfoList();
		if (requestList.size() == 0) {
			cout << "û������" << endl;
			system("pause");
			return;
		}
		system("cls");
		cout << "           �����б�" << endl;
		cout << "__________________________________" << endl;

		for (int i = 0; i < requestList.size(); i++) {
			cout << "|΢��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << requestList[i].friendId << "|" << endl;
			cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << requestList[i].friendName << "|" << endl;
			cout << "__________________________________" << endl;
		}
		cout << resetiosflags(ios::left);
		cout << "| 01 || ͬ��                      |" << endl;
		cout << "| 02 || �ܾ�                      |" << endl;
		cout << "| 00 || ����                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "����ѡ��:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "����ͬ���WeChat��:";
			int WeChatNumber = 0;
			cin >> WeChatNumber;
			refreshInput();
			if (groupPtr->isMember(WeChatNumber))
			{
				cout << "���û�����Ⱥ��Ա" << endl;
				groupPtr->removeRequest(WeChatNumber);
				m_allWeChatGroupList->saveGroupListData();
				system("pause");
				continue;
			}
			//����Ƿ���ڸ�����
			int j = 0;
			for (j = 0; j < requestList.size(); j++) {
				if (requestList[j].friendId == WeChatNumber) {
					break;
				}
			}
			if (j == requestList.size()) {
				cout << "���󲻴���" << endl;
				system("pause");
				continue;
			}
			//�������
			groupPtr->addMember(WeChatNumber);

			WeChatUserNodeLA* p = m_allWeChatUserList->findByWeChatId(WeChatNumber);
			p->addWeChatGroupId(groupPtr->getGroupId());
			//�Ƴ�����
			groupPtr->removeRequest(WeChatNumber);

			//���浽�ļ�
			m_allWeChatGroupList->saveGroupListData();
			m_allWeChatUserList->saveWeChatUserListData();

			cout << "��ӳɹ�" << endl;
			system("pause");
			continue;
		}
		else if (i == 2) {
			cout << "����ܾ���WeChat��:";
			int WeChatNumber = 0;
			cin >> WeChatNumber;
			refreshInput();
			if (groupPtr->isMember(WeChatNumber))
			{
				cout << "���û�����Ⱥ��Ա" << endl;
				groupPtr->removeRequest(WeChatNumber);
				m_allWeChatGroupList->saveGroupListData();
				system("pause");
				continue;
			}
			//����Ƿ���ڸ�����
			int j = 0;
			for (j = 0; j < requestList.size(); j++) {
				if (requestList[j].friendId == WeChatNumber) {
					break;
				}
			}
			if (j == requestList.size()) {
				cout << "���󲻴���" << endl;
				system("pause");
				continue;
			}
			//�Ƴ�����
			groupPtr->removeRequest(WeChatNumber);

			//���浽�ļ�
			m_allWeChatGroupList->saveGroupListData();

			cout << "�Ѿܾ�" << endl;
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

bool applicationWeChatLA::sendMsgToGroup(WeChatGroupNodeLA* groupPtr, const char* msg) {
	//��Ⱥ����������(�����Լ�)���ļ���ӷ���ʱ�����Ϣ����
	vector<userInfo> memberList = groupPtr->getWeChatGroupMemberInfoList();
	for (int i = 0; i < memberList.size(); i++) {
		string path = "WeChat\\" + to_string(memberList[i].friendId) + "\\groupchatrecord\\" + to_string(groupPtr->getGroupId()) + ".dat";

		//��ȡʱ��
		string time = getTime();
		//��ÿ���û���groupchatrecord�ļ�д�뷢����WeChat��,�������ǳ�,����ʱ��,��Ϣ����
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

void applicationWeChatLA::showWeChatGroupList(const vector<int>& grouplist) {
	if (grouplist.size() == 0)
	{
		cout << "       ��û�м����κ�Ⱥ" << endl;
		cout << "__________________________________" << endl;
		return;
	}
	cout << "����" << grouplist.size() << "��Ⱥ" << endl;
	cout << "__________________________________" << endl;

	for (int i = 0; i < grouplist.size(); i++) {
		cout << "|Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << grouplist[i] << "|" << endl;
		cout << "|Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_allWeChatGroupList->findByGroupId(grouplist[i])->getGroupName() << "|" << endl;
		cout << "__________________________________" << endl;
	}
	cout << resetiosflags(ios::left);

	return;
}

void applicationWeChatLA::showGroupMemberList(int groupId) {
	WeChatGroupNodeLA* groupPtr = m_allWeChatGroupList->findByGroupId(groupId);
	showGroupMemberList(groupPtr);
}
//TODO:color
void applicationWeChatLA::showGroupMemberList(WeChatGroupNodeLA* groupPtr) {
	system("cls");
	vector<userInfo> memberList = groupPtr->getWeChatGroupMemberInfoList();
	cout << "          Ⱥ��Ա�б�(" << memberList.size() << ")" << endl;
	cout << "__________________________________" << endl;

	for (int i = 0; i < memberList.size(); i++) {
		cout << "|΢��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << memberList[i].friendId << "|" << endl;
		cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << memberList[i].friendName << "|" << endl;
		cout << "__________________________________" << endl;
	}
	cout << resetiosflags(ios::left);

	system("pause");
}

vector<WMsg> applicationWeChatLA::recvMsgFromGroup(WeChatGroupNodeLA* groupPtr)
{
	string path = "WeChat\\" + to_string(m_currentUser->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupPtr->getGroupId()) + ".dat";
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
	vector<WMsg> msgList;
	int id;
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

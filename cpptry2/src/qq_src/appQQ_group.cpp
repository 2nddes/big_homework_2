#define _CRT_SECURE_NO_WARNINGS
#include"/project/C++Project/cpptry2/cpptry2/src/utils.h"
#include"applicationQQ.h"
#include"/project/C++Project/cpptry2/cpptry2/src/platform.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<random>

void applicationQQLA::groupPage() {
	while (1) {
		system("cls");
		cout << "           Ⱥ��" << endl;
		cout << "_________________________________" << endl;
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
	if (m_currentUser->getQQGroupId().size() == 0) {
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
	while (1)
	{
		system("cls");
		cout << setw(20) << setfill(' ') << groupPtr->getGroupName() << endl;

		int userid = m_currentUser->getAppUserId();
		if (groupPtr->isOwner(userid)) {
			cout << "_________________________________" << endl;
			showMsg(recvMsgFromGroup(groupPtr));
			cout << "_________________________________" << endl;
			cout << "| 01 || ������Ϣ                  |" << endl;
			cout << "| 02 || �鿴Ⱥ��Ա                |" << endl;
			cout << "| 03 || ��ɢȺ                    |" << endl;
			cout << "| 04 || ����Ⱥ                    |" << endl;
			cout << "| 05 || �����Ⱥ                  |" << endl;
			cout << "| 06 || �߳�Ⱥ��Ա                |" << endl;
			cout << "| 07 || �鿴Ⱥ����                |" << endl;
			cout << "| 08 || ���ù���Ա                |" << endl;
			cout << "| 09 || ����Ⱥ�ǳ�                |" << endl;
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
			cout << "_________________________________" << endl;
			showMsg(recvMsgFromGroup(groupPtr));
			cout << "_________________________________" << endl;
			cout << "| 01 || ������Ϣ                  |" << endl;
			cout << "| 02 || �鿴Ⱥ��Ա                |" << endl;
			cout << "| 03 || �����Ⱥ                  |" << endl;
			cout << "| 04 || �˳�Ⱥ                    |" << endl;
			cout << "| 05 || �鿴Ⱥ����                |" << endl;
			cout << "| 06 || �߳�Ⱥ��Ա                |" << endl;
			cout << "| 07 || ����Ⱥ�ǳ�                |" << endl;
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
			cout << "_________________________________" << endl;
			showMsg(recvMsgFromGroup(groupPtr));
			cout << "_________________________________" << endl;
			cout << "| 01 || ������Ϣ                  |" << endl;
			cout << "| 02 || �鿴Ⱥ��Ա                |" << endl;
			cout << "| 03 || �����Ⱥ                  |" << endl;
			cout << "| 04 || �˳�Ⱥ                    |" << endl;
			cout << "| 05 || ����Ⱥ�ǳ�                |" << endl;
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
				if (quitGroupPage(groupPtr))
					return;
			}
			else if (i == 5) {
				setGroupNickNamePage(groupPtr);
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
	if (!groupPtr->isMember(qqNumber)) {
		cout << "���û�����Ⱥ��Ա" << endl;
		system("pause");
		return;
	}
	if (groupPtr->isOwner(qqNumber)) {
		cout << "����Ⱥ��" << endl;
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

void applicationQQLA::setGroupNickNamePage(qqGroupNodeLA* groupPtr) {
	system("cls");
	cout << "         ����Ⱥ�ǳ�" << endl;
	cout << "_________________________________" << endl;
	cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupNickName(m_currentUser->getAppUserId()) << "|" << endl;
	cout << "_________________________________" << endl;
	cout << "�����µ��ǳ�(�����ո�������ַ�,ֱ�ӻس�����):" << endl;
	string nickName;
	cin >> nickName;
	refreshInput();
	if (nickName == "") {
		return;
	}
	groupPtr->setGroupNickName(m_currentUser->getAppUserId(), nickName);
	m_allQQGroupList->saveGroupListData();

	cout << "������" << endl;
	system("pause");
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
	cout << "            ����Ⱥ��" << endl;
	cout << "_________________________________" << endl;
	cout << "����Ⱥ��(�����ո�������ַ�):";
	string groupName;
	cin >> groupName;
	refreshInput();
	cout << "��1ȷ�ϴ���:";
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
		cout << "| Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupId() << "|" << endl;
		cout << "| Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupName() << "|" << endl;
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

	default_random_engine e((unsigned int)time(NULL));
	int id1 = 1001 + e() % m_allQQGroupList->size();

	cout << "            ����Ⱥ��" << endl;
	cout << "_________________________________" << endl;
	cout << "            �Ƽ�Ⱥ��" << endl;
	cout << "_________________________________" << endl;
	cout << "| Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << id1 << "|" << endl;
	cout << "| Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_allQQGroupList->findByGroupId(id1)->getGroupName() << "|" << endl;
	cout << "_________________________________" << endl;
	cout << resetiosflags(ios::left);
	cout << "����Ⱥ��:";

	int groupId = 0;
	cin >> groupId;
	refreshInput();
	if (m_currentUser->isAddedGroup(groupId)) {
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
		system("cls");
		cout << "         ����Ⱥ��" << endl;
		cout << "_________________________________" << endl;
		cout << "|Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupId() << "|" << endl;
		cout << "|Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupName() << "|" << endl;
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

bool applicationQQLA::disbandGroupPage(qqGroupNodeLA* groupPtr)
{
	system("cls");
	if (!groupPtr->isOwner(m_currentUser->getAppUserId())) {
		cout << "����Ⱥ��,�޷���ɢȺ" << endl;
		system("pause");
		return false;
	}
	cout << "         ��ɢȺ��" << endl;
	cout << "_________________________________" << endl;
	cout << "|Ⱥ��|| " << setw(24) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupId() << "|" << endl;
	cout << "|Ⱥ��|| " << setw(24) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupName() << "|" << endl;
	cout << "_________________________________" << endl;
	cout << "| 01 || ȷ�Ͻ�ɢ(����ɾ�������¼!)|" << endl;
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
			if (_access(path.c_str(), 0) != -1) {
				remove(path.c_str());
			}
		}

		//�Ƴ�Ⱥ
		m_allQQGroupList->removeGroup(groupPtr);
		//���浽�ļ�
		m_allQQGroupList->saveGroupListData();
		m_allQQUserList->saveQQUserListData();
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

bool applicationQQLA::quitGroupPage() {
	system("cls");
	cout << "         �˳�Ⱥ��" << endl;
	cout << "_________________________________" << endl;
	showQQGroupList(m_currentUser->getQQGroupId());
	if (m_currentUser->getQQGroupId().size() == 0) {
		cout << "û��Ⱥ���˳�" << endl;
		system("pause");
		return false;
	}
	cout << "����Ⱥ��:" << endl;
	int groupId = 0;
	cin >> groupId;
	refreshInput();
	qqGroupNodeLA* p = m_allQQGroupList->findByGroupId(groupId);
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
		cout << "_________________________________" << endl;
		cout << "| Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupId() << "|" << endl;
		cout << "| Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupName() << "|" << endl;
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

bool applicationQQLA::quitGroupPage(qqGroupNodeLA* groupPtr) {
	if (groupPtr->isOwner(m_currentUser->getAppUserId())) {
		cout << "Ⱥ���޷��˳�Ⱥ��,�볢�Խ�ɢȺ" << endl;
		system("pause");
		return false;
	}
	system("cls");
	cout << "         �˳�Ⱥ��" << endl;
	cout << "_________________________________" << endl;
	cout << "| Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupId() << "|" << endl;
	cout << "| Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupName() << "|" << endl;
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
		system("pause");
		return true;
	}
	else {
		cout << "ȡ���˳�" << endl;
		system("pause");
		return false;
	}
}

void applicationQQLA::setGroupConfigPage(qqGroupNodeLA* groupPtr) {
	while (1)
	{
		system("cls");
		cout << setw(20) << setfill(' ') << groupPtr->getGroupName() << endl;
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


void applicationQQLA::kickMemberPage(qqGroupNodeLA* groupPtr)
{
	system("cls");
	cout << "         �߳�Ⱥ��Ա" << endl;
	cout << "_________________________________" << endl;
	showGroupMemberPage(groupPtr);

	cout << "����Ҫ�߳���Ⱥ��ԱQQ��:";
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
		qqUserNodeLA* p = m_allQQUserList->findByQQId(qqNumber);
		p->deleteQQGroupId(groupId);

		//�Ƴ��û�
		groupPtr->removeMember(qqNumber);
		//���浽�ļ�
		m_allQQGroupList->saveGroupListData();
		m_allQQUserList->saveQQUserListData();
		string path = "QQ\\" + to_string(qqNumber) + "\\groupchatrecord\\" + to_string(groupId) + ".dat";
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

void applicationQQLA::groupRequestPage(qqGroupNodeLA* groupPtr) {
	while (1)
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
		system("cls");
		cout << "           �����б�" << endl;
		cout << "_________________________________" << endl;

		for (int i = 0; i < requestList.size(); i++) {
			cout << "|QQ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << requestList[i].friendId << "|" << endl;
			cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << requestList[i].friendName << "|" << endl;
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
			int j = 0;
			for (j = 0; j < requestList.size(); j++) {
				if (requestList[j].friendId == qqNumber) {
					break;
				}
			}
			if (j == requestList.size()) {
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
		else if (i == 2) {
			cout << "����ܾ���QQ��:";
			int qqNumber = 0;
			cin >> qqNumber;
			refreshInput();
			//����Ƿ���ڸ�����
			int j = 0;
			for (j = 0; j < requestList.size(); j++) {
				if (requestList[j].friendId == qqNumber) {
					break;
				}
			}
			if (j == requestList.size()) {
				cout << "���󲻴���" << endl;
				system("pause");
				continue;
			}
			//�Ƴ�����
			groupPtr->removeRequest(qqNumber);

			//���浽�ļ�
			m_allQQGroupList->saveGroupListData();

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
		cout << "|Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << grouplist[i] << "|" << endl;
		cout << "|Ⱥ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_allQQGroupList->findByGroupId(grouplist[i])->getGroupName() << "|" << endl;
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
		cout << "|QQ��|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << memberList[i].friendId << "|" << endl;
		cout << "|�ǳ�|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << memberList[i].friendName << "|" << endl;
		cout << "_________________________________" << endl;
	}
	cout << resetiosflags(ios::left);

	system("pause");
}

vector<QMsg> applicationQQLA::recvMsgFromGroup(qqGroupNodeLA* groupPtr)
{
	string path = "QQ\\" + to_string(m_currentUser->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupPtr->getGroupId()) + ".dat";
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

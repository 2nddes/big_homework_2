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
		cout << "           群组" << endl;
		cout << "_________________________________" << endl;
		showQQGroupList(m_currentUser->getQQGroupId());
		cout << "| 01 || 选择群                    |" << endl;
		cout << "| 02 || 搜索群                    |" << endl;
		cout << "| 03 || 创建群                    |" << endl;
		cout << "| 04 || 加入群                    |" << endl;
		cout << "| 05 || 退出群                    |" << endl;
		cout << "| 00 || 返回                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "输入选项:";

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
			cout << "输入错误" << endl;
			system("pause");
			continue;
		}
	}
}

void applicationQQLA::selectGroupPage()
{
	system("cls");
	cout << "         选择群组" << endl;
	showQQGroupList(m_currentUser->getQQGroupId());
	if (m_currentUser->getQQGroupId().size() == 0) {
		system("pause");
		return;
	}
	cout << "输入群号:";

	int groupId = 0;
	cin >> groupId;
	refreshInput();
	qqGroupNodeLA* p = m_allQQGroupList->findByGroupId(groupId);
	if (p == nullptr) {
		cout << "群不存在" << endl;
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
			cout << "| 01 || 发送消息                  |" << endl;
			cout << "| 02 || 查看群成员                |" << endl;
			cout << "| 03 || 解散群                    |" << endl;
			cout << "| 04 || 设置群                    |" << endl;
			cout << "| 05 || 邀请进群                  |" << endl;
			cout << "| 06 || 踢出群成员                |" << endl;
			cout << "| 07 || 查看群请求                |" << endl;
			cout << "| 08 || 设置管理员                |" << endl;
			cout << "| 09 || 设置群昵称                |" << endl;
			cout << "| 00 || 返回                      |" << endl;
			cout << "_________________________________" << endl;
			cout << "输入选项:";

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
				cout << "输入错误" << endl;
				system("pause");
				continue;
			}
		}
		else if (groupPtr->isAdministrator(userid)) {
			cout << "_________________________________" << endl;
			showMsg(recvMsgFromGroup(groupPtr));
			cout << "_________________________________" << endl;
			cout << "| 01 || 发送消息                  |" << endl;
			cout << "| 02 || 查看群成员                |" << endl;
			cout << "| 03 || 邀请进群                  |" << endl;
			cout << "| 04 || 退出群                    |" << endl;
			cout << "| 05 || 查看群请求                |" << endl;
			cout << "| 06 || 踢出群成员                |" << endl;
			cout << "| 07 || 设置群昵称                |" << endl;
			cout << "| 00 || 返回                      |" << endl;
			cout << "_________________________________" << endl;
			cout << "输入选项:";

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
				cout << "输入错误" << endl;
				system("pause");
				continue;
			}
		}
		else if (groupPtr->isMember(userid)) {
			cout << "_________________________________" << endl;
			showMsg(recvMsgFromGroup(groupPtr));
			cout << "_________________________________" << endl;
			cout << "| 01 || 发送消息                  |" << endl;
			cout << "| 02 || 查看群成员                |" << endl;
			cout << "| 03 || 邀请进群                  |" << endl;
			cout << "| 04 || 退出群                    |" << endl;
			cout << "| 05 || 设置群昵称                |" << endl;
			cout << "| 00 || 返回                      |" << endl;
			cout << "_________________________________" << endl;
			cout << "输入选项:";

			int i = 0;
			cin >> i;
			refreshInput();
			if (i == 1) {
				cout << "直接回车返回;输入消息回车发送:" << endl;
				char message[300];
				memset(message, 0, 300);
				cin.getline(message, 300);
				if (message[0] == '\0') {
					continue;
				}
				(sendMsgToGroup(groupPtr, message)) ? cout << "发送成功" << endl : cout << "发送失败" << endl;
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
				cout << "输入错误" << endl;
				system("pause");
				continue;
			}
		}
		else {
			cout << "_________________________________" << endl;
			cout << "| 01 || 查看群成员                |" << endl;
			cout << "| 02 || 申请加入群                |" << endl;
			cout << "| 00 || 返回                      |" << endl;
			cout << "_________________________________" << endl;
			cout << "输入选项:";

			int i = 0;
			cin >> i;
			refreshInput();
			if (i == 1) {
				showGroupMemberPage(groupPtr);
			}
			else if (i == 2) {
				if (!groupPtr->isAllowJoin()) {
					cout << "该群当前不允许加入" << endl;
					system("pause");
					continue;
				}
				userInfo info;
				info.friendId = m_currentUser->getAppUserId();
				info.friendName = m_currentUser->getUserName();
				groupPtr->addRequest(info);
				m_allQQGroupList->saveGroupListData();
				cout << "申请成功" << endl;
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
}

void applicationQQLA::setAdminPage(qqGroupNodeLA* groupPtr)
{
	if (!groupPtr->isOwner(m_currentUser->getAppUserId())) {
		cout << "你不是群主,无法设置管理员" << endl;
		system("pause");
		return;
	}
	if (!groupPtr->isAllowAdmins()) {
		cout << "已设置不允许管理员" << endl;
		system("pause");
		return;
	}
	system("cls");
	cout << "         设置管理员" << endl;
	cout << "_________________________________" << endl;
	showGroupMemberPage(groupPtr);

	cout << "输入要设置的QQ号:";

	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	if (!groupPtr->isMember(qqNumber)) {
		cout << "该用户不是群成员" << endl;
		system("pause");
		return;
	}
	if (groupPtr->isOwner(qqNumber)) {
		cout << "已是群主" << endl;
		system("pause");
		return;
	}
	if (groupPtr->isAdministrator(qqNumber)) {
		cout << m_allQQUserList->findByQQId(qqNumber)->getUserName() << "是管理员" << endl;
		cout << "输入1将其撤销管理员" << endl;

		int i = 0;
		cin >> i;
		refreshInput();

		if (i == 1) {
			groupPtr->removeQQGroupAdmin(qqNumber);
			m_allQQGroupList->saveGroupListData();
			cout << "撤销成功" << endl;
			system("pause");
			return;
		}
		else {
			cout << "取消撤销" << endl;
			system("pause");
			return;
		}
	}
	else {
		cout << m_allQQUserList->findByQQId(qqNumber)->getUserName() << "不是管理员" << endl;
		cout << "输入1将其设置为管理员" << endl;
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			groupPtr->addQQGroupAdmin(qqNumber);
			m_allQQGroupList->saveGroupListData();
			cout << "设置成功" << endl;
			system("pause");
			return;
		}
		else {
			cout << "取消设置" << endl;
			system("pause");
			return;
		}
	}
	return;
}

void applicationQQLA::setGroupNickNamePage(qqGroupNodeLA* groupPtr) {
	system("cls");
	cout << "         设置群昵称" << endl;
	cout << "_________________________________" << endl;
	cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupNickName(m_currentUser->getAppUserId()) << "|" << endl;
	cout << "_________________________________" << endl;
	cout << "输入新的昵称(不含空格等特殊字符,直接回车返回):" << endl;
	string nickName;
	cin >> nickName;
	refreshInput();
	if (nickName == "") {
		return;
	}
	groupPtr->setGroupNickName(m_currentUser->getAppUserId(), nickName);
	m_allQQGroupList->saveGroupListData();

	cout << "已设置" << endl;
	system("pause");
	return;

}

void applicationQQLA::searchGroupPage() {
	system("cls");
	cout << "输入群号:" << endl;
	int groupId = 0;
	cin >> groupId;
	refreshInput();
	qqGroupNodeLA* p = m_allQQGroupList->findByGroupId(groupId);
	if (p == nullptr) {
		cout << "群不存在" << endl;
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
		cout << "该群禁言中" << endl;
		system("pause");
		return;
	}
	cout << "直接回车返回;输入消息回车发送:" << endl;
	char message[300];
	memset(message, 0, 300);
	cin.getline(message, 300);
	if (message[0] == '\0') {
		return;
	}
	(sendMsgToGroup(groupPtr, message))
		? cout << "发送成功" << endl
		: cout << "发送失败" << endl;
}

void applicationQQLA::createGroupPage() {
	system("cls");
	cout << "            创建群组" << endl;
	cout << "_________________________________" << endl;
	cout << "输入群名(不含空格等特殊字符):";
	string groupName;
	cin >> groupName;
	refreshInput();
	cout << "按1确认创建:";
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		qqGroupNodeLA* p = m_allQQGroupList->addGroup(groupName, m_currentUser->getAppUserId());

		m_currentUser->addQQGroupId(p->getGroupId());
		//保存文件
		m_allQQGroupList->saveGroupListData();
		m_allQQUserList->saveQQUserListData();
		system("cls");
		cout << "            创建成功" << endl;
		cout << "_________________________________" << endl;
		cout << "| 群号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupId() << "|" << endl;
		cout << "| 群名|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupName() << "|" << endl;
		cout << "_________________________________" << endl;
	}
	else {
		cout << "取消创建" << endl;
	}
	system("pause");
	return;

}

void applicationQQLA::joinGroupPage() {
	system("cls");
	if (m_allQQGroupList->size() == 0) {
		cout << "没有群可加入" << endl;
		system("pause");
		return;
	}

	default_random_engine e((unsigned int)time(NULL));
	int id1 = 1001 + e() % m_allQQGroupList->size();

	cout << "            加入群组" << endl;
	cout << "_________________________________" << endl;
	cout << "            推荐群组" << endl;
	cout << "_________________________________" << endl;
	cout << "| 群号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << id1 << "|" << endl;
	cout << "| 群名|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_allQQGroupList->findByGroupId(id1)->getGroupName() << "|" << endl;
	cout << "_________________________________" << endl;
	cout << resetiosflags(ios::left);
	cout << "输入群号:";

	int groupId = 0;
	cin >> groupId;
	refreshInput();
	if (m_currentUser->isAddedGroup(groupId)) {
		cout << "已经在群内" << endl;
		system("pause");
		return;
	}
	qqGroupNodeLA* p = m_allQQGroupList->findByGroupId(groupId);
	if (p == nullptr) {
		cout << "群不存在" << endl;
		system("pause");
		return;
	}
	else {
		system("cls");
		cout << "         加入群组" << endl;
		cout << "_________________________________" << endl;
		cout << "|群号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupId() << "|" << endl;
		cout << "|群名|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupName() << "|" << endl;
		cout << "_________________________________" << endl;
		cout << "| 01 || 申请加入                  |" << endl;
		cout << "|其他|| 返回                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "输入选项:";
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			//添加到群成员列表
			userInfo info;
			info.friendId = m_currentUser->getAppUserId();
			info.friendName = m_currentUser->getUserName();
			//添加请求
			p->addRequest(info);
			//保存到文件
			m_allQQGroupList->saveGroupListData();

			cout << "申请成功" << endl;
		}
		else if (i == 0) {
			cout << "取消申请" << endl;
		}
		else {
			cout << "取消加入" << endl;
		}
		system("pause");
		return;
	}
}

bool applicationQQLA::disbandGroupPage(qqGroupNodeLA* groupPtr)
{
	system("cls");
	if (!groupPtr->isOwner(m_currentUser->getAppUserId())) {
		cout << "不是群主,无法解散群" << endl;
		system("pause");
		return false;
	}
	cout << "         解散群组" << endl;
	cout << "_________________________________" << endl;
	cout << "|群号|| " << setw(24) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupId() << "|" << endl;
	cout << "|群名|| " << setw(24) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupName() << "|" << endl;
	cout << "_________________________________" << endl;
	cout << "| 01 || 确认解散(将会删除聊天记录!)|" << endl;
	cout << "|其他|| 返回                      |" << endl;
	cout << "_________________________________" << endl;
	cout << "输入选项:";

	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		//删除每个用户所存储的群号
		int groupId = groupPtr->getGroupId();
		vector<userInfo> memberList = groupPtr->getQQGroupMemberInfoList();
		for (int i = 0; i < memberList.size(); i++) {
			qqUserNodeLA* p = m_allQQUserList->findByQQId(memberList[i].friendId);
			p->deleteQQGroupId(groupId);
			//删除聊天文件
			string path = "QQ\\" + to_string(p->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupId) + ".dat";
			if (_access(path.c_str(), 0) != -1) {
				remove(path.c_str());
			}
		}

		//移除群
		m_allQQGroupList->removeGroup(groupPtr);
		//保存到文件
		m_allQQGroupList->saveGroupListData();
		m_allQQUserList->saveQQUserListData();
		cout << "解散成功" << endl;
		system("pause");
		return true;
	}
	else {
		cout << "取消解散" << endl;
		system("pause");
		return false;
	}
}

bool applicationQQLA::quitGroupPage() {
	system("cls");
	cout << "         退出群组" << endl;
	cout << "_________________________________" << endl;
	showQQGroupList(m_currentUser->getQQGroupId());
	if (m_currentUser->getQQGroupId().size() == 0) {
		cout << "没有群可退出" << endl;
		system("pause");
		return false;
	}
	cout << "输入群号:" << endl;
	int groupId = 0;
	cin >> groupId;
	refreshInput();
	qqGroupNodeLA* p = m_allQQGroupList->findByGroupId(groupId);
	if (!m_currentUser->isAddedGroup(groupId)) {
		cout << "群不存在" << endl;
		system("pause");
		return false;
	}
	else if (p->isOwner(m_currentUser->getAppUserId())) {
		cout << "群主无法退出群组,请尝试解散群" << endl;
		system("pause");
		return false;
	}
	else {
		system("cls");
		cout << "         退出群组" << endl;
		cout << "_________________________________" << endl;
		cout << "| 群号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupId() << "|" << endl;
		cout << "| 群名|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupName() << "|" << endl;
		cout << "_________________________________" << endl;
		cout << "| 01 || 确认退出(将会删除聊天记录!)|" << endl;
		cout << "|其他|| 返回                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "输入选项:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			//相互删除
			if (p->isAdministrator(m_currentUser->getAppUserId())) {
				p->removeQQGroupAdmin(m_currentUser->getAppUserId());
			}
			p->removeMember(m_currentUser->getAppUserId());
			m_currentUser->deleteQQGroupId(p->getGroupId());
			//保存到文件
			m_allQQGroupList->saveGroupListData();
			m_allQQUserList->saveQQUserListData();
			string path = "QQ\\" + to_string(m_currentUser->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupId) + ".dat";
			if (_access(path.c_str(), 0) != -1) {
				remove(path.c_str());
			}

			cout << "退出成功" << endl;
			system("pause");
			return true;
		}
		else {
			cout << "取消退出" << endl;
			system("pause");
			return false;
		}
	}
	return true;
}

bool applicationQQLA::quitGroupPage(qqGroupNodeLA* groupPtr) {
	if (groupPtr->isOwner(m_currentUser->getAppUserId())) {
		cout << "群主无法退出群组,请尝试解散群" << endl;
		system("pause");
		return false;
	}
	system("cls");
	cout << "         退出群组" << endl;
	cout << "_________________________________" << endl;
	cout << "| 群号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupId() << "|" << endl;
	cout << "| 群名|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupName() << "|" << endl;
	cout << "_________________________________" << endl;
	cout << "| 01 || 确认退出(将会删除聊天记录!)|" << endl;
	cout << "|其他|| 返回                      |" << endl;
	cout << "_________________________________" << endl;
	cout << "输入选项:";

	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		//相互删除
		if (groupPtr->isAdministrator(m_currentUser->getAppUserId())) {
			groupPtr->removeQQGroupAdmin(m_currentUser->getAppUserId());
		}
		groupPtr->removeMember(m_currentUser->getAppUserId());
		m_currentUser->deleteQQGroupId(groupPtr->getGroupId());
		//保存到文件
		m_allQQGroupList->saveGroupListData();
		m_allQQUserList->saveQQUserListData();
		string path = "QQ\\" + to_string(m_currentUser->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupPtr->getGroupId()) + ".dat";
		if (_access(path.c_str(), 0) != -1) {
			remove(path.c_str());
		}

		cout << "退出成功" << endl;
		system("pause");
		return true;
	}
	else {
		cout << "取消退出" << endl;
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
		cout << "| 01 || 修改群名                  |" << endl;
		cout << "| 02 || 是否允许邀请进群          |" << endl;
		cout << "| 03 || 是否允许搜索加入          |" << endl;
		cout << "| 04 || 是否允许发言              |" << endl;
		cout << "| 05 || 是否允许设置管理员        |" << endl;
		cout << "| 06 || 是否群成员临时会话        |" << endl;
		cout << "| 00 || 返回                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "输入选项:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "输入新群名,直接回车可返回" << endl;
			string groupName;
			cin >> groupName;
			refreshInput();
			if (groupName == "") {
				continue;
			}
			groupPtr->setQQGroupName(groupName);
			m_allQQGroupList->saveGroupListData();
			cout << "修改成功" << endl;
			system("pause");
			continue;
		}
		else if (i == 2) {
			if (groupPtr->isAllowInvite()) {
				cout << "当前允许邀请进群,按1禁止:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowInvite(false);
					m_allQQGroupList->saveGroupListData();
					cout << "修改成功" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "取消修改" << endl;
					system("pause");
					continue;
				}
			}
			else {
				cout << "当前禁止邀请进群,按1允许:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowInvite(true);
					m_allQQGroupList->saveGroupListData();
					cout << "修改成功" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "取消修改" << endl;
					system("pause");
					continue;
				}
			}
		}
		else if (i == 3) {
			if (groupPtr->isAllowJoin()) {
				cout << "当前允许搜索加入,按1禁止:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowJoin(false);
					m_allQQGroupList->saveGroupListData();
					cout << "修改成功" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "取消修改" << endl;
					system("pause");
					continue;
				}
			}
			else {
				cout << "当前禁止搜索加入,按1允许:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowJoin(true);
					m_allQQGroupList->saveGroupListData();
					cout << "修改成功" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "取消修改" << endl;
					system("pause");
					continue;
				}
			}
		}
		else if (i == 4) {
			if (groupPtr->isAllowSend()) {
				cout << "当前允许发言,按1禁止:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowSend(false);
					m_allQQGroupList->saveGroupListData();
					cout << "修改成功" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "取消修改" << endl;
					system("pause");
					continue;
				}
			}
			else {
				cout << "当前禁止发言,按1允许:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowSend(true);
					m_allQQGroupList->saveGroupListData();
					cout << "修改成功" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "取消修改" << endl;
					system("pause");
					continue;
				}
			}
		}
		else if (i == 5) {
			if (groupPtr->isAllowAdmins()) {
				cout << "当前允许管理员,按1禁止:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowAdmins(false);
					m_allQQGroupList->saveGroupListData();
					cout << "修改成功" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "取消修改" << endl;
					system("pause");
					continue;
				}
			}
			else {
				cout << "当前禁止管理员,按1允许:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowAdmins(true);
					m_allQQGroupList->saveGroupListData();
					cout << "修改成功" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "取消修改" << endl;
					system("pause");
					continue;
				}
			}
		}
		else if (i == 6) {
			if (groupPtr->isAllowSubgroup()) {
				cout << "当前允许群成员临时会话,按1禁止:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowSubgroup(false);
					m_allQQGroupList->saveGroupListData();
					cout << "修改成功" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "取消修改" << endl;
					system("pause");
					continue;
				}
			}
			else {
				cout << "当前禁止群成员临时会话,按1允许:" << endl;
				int j = 0;
				cin >> j;
				refreshInput();
				if (j == 1) {
					groupPtr->setQQGroupIsAllowSubgroup(true);
					m_allQQGroupList->saveGroupListData();
					cout << "修改成功" << endl;
					system("pause");
					continue;
				}
				else {
					cout << "取消修改" << endl;
					system("pause");
					continue;
				}
			}
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


void applicationQQLA::kickMemberPage(qqGroupNodeLA* groupPtr)
{
	system("cls");
	cout << "         踢出群成员" << endl;
	cout << "_________________________________" << endl;
	showGroupMemberPage(groupPtr);

	cout << "输入要踢出的群成员QQ号:";
	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	if (!groupPtr->isMember(qqNumber)) {
		cout << "该用户不是群成员" << endl;
		system("pause");
		return;
	}
	if (groupPtr->isOwner(qqNumber)) {
		cout << "不能踢出群主" << endl;
		system("pause");
		return;
	}
	if (m_currentUser->getAppUserId() == qqNumber) {
		cout << "不可踢出自己,尝试退出群" << endl;
		return;
	}
	cout << "确认踢出按1" << endl;
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		//删除用户所存储的群号
		int groupId = groupPtr->getGroupId();
		qqUserNodeLA* p = m_allQQUserList->findByQQId(qqNumber);
		p->deleteQQGroupId(groupId);

		//移除用户
		groupPtr->removeMember(qqNumber);
		//保存到文件
		m_allQQGroupList->saveGroupListData();
		m_allQQUserList->saveQQUserListData();
		string path = "QQ\\" + to_string(qqNumber) + "\\groupchatrecord\\" + to_string(groupId) + ".dat";
		if (_access(path.c_str(), 0) != -1) {
			remove(path.c_str());
		}

		cout << "踢出成功" << endl;
		system("pause");
	}
	else {
		cout << "取消踢出" << endl;
		system("pause");
	}

}

void applicationQQLA::groupRequestPage(qqGroupNodeLA* groupPtr) {
	while (1)
	{
		if (!groupPtr->isAdministrator(m_currentUser->getAppUserId()) && !groupPtr->isOwner(m_currentUser->getAppUserId())) {
			cout << "无权处理申请";
			system("pause");
			return;
		}

		vector<userInfo> requestList = groupPtr->getQQGroupRequestInfoList();
		if (requestList.size() == 0) {
			cout << "没有申请" << endl;
			system("pause");
			return;
		}
		system("cls");
		cout << "           申请列表" << endl;
		cout << "_________________________________" << endl;

		for (int i = 0; i < requestList.size(); i++) {
			cout << "|QQ号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << requestList[i].friendId << "|" << endl;
			cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << requestList[i].friendName << "|" << endl;
			cout << "_________________________________" << endl;
		}
		cout << resetiosflags(ios::left);
		cout << "| 01 || 同意                      |" << endl;
		cout << "| 02 || 拒绝                      |" << endl;
		cout << "| 00 || 返回                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "输入选项:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "输入同意的QQ号:";
			int qqNumber = 0;
			cin >> qqNumber;
			refreshInput();
			//检查是否存在该请求
			int j = 0;
			for (j = 0; j < requestList.size(); j++) {
				if (requestList[j].friendId == qqNumber) {
					break;
				}
			}
			if (j == requestList.size()) {
				cout << "请求不存在" << endl;
				system("pause");
				continue;
			}
			//互相添加
			groupPtr->addMember(qqNumber);

			qqUserNodeLA* p = m_allQQUserList->findByQQId(qqNumber);
			p->addQQGroupId(groupPtr->getGroupId());
			//移除请求
			groupPtr->removeRequest(qqNumber);

			//保存到文件
			m_allQQGroupList->saveGroupListData();
			m_allQQUserList->saveQQUserListData();

			cout << "添加成功" << endl;
			system("pause");
			continue;
		}
		else if (i == 2) {
			cout << "输入拒绝的QQ号:";
			int qqNumber = 0;
			cin >> qqNumber;
			refreshInput();
			//检查是否存在该请求
			int j = 0;
			for (j = 0; j < requestList.size(); j++) {
				if (requestList[j].friendId == qqNumber) {
					break;
				}
			}
			if (j == requestList.size()) {
				cout << "请求不存在" << endl;
				system("pause");
				continue;
			}
			//移除请求
			groupPtr->removeRequest(qqNumber);

			//保存到文件
			m_allQQGroupList->saveGroupListData();

			cout << "已拒绝" << endl;
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

bool applicationQQLA::sendMsgToGroup(qqGroupNodeLA* groupPtr, const char* msg) {
	//给群组内所有人(包括自己)的文件添加发送时间和消息内容
	vector<userInfo> memberList = groupPtr->getQQGroupMemberInfoList();
	for (int i = 0; i < memberList.size(); i++) {
		string path = "QQ\\" + to_string(memberList[i].friendId) + "\\groupchatrecord\\" + to_string(groupPtr->getGroupId()) + ".dat";

		//获取时间
		string time = getTime();
		//打开每个用户的groupchatrecord文件写入发送者QQ号,发送者昵称,发送时间,消息内容
		ofstream ofs(path, ios::app);
		if (!ofs.is_open()) {
			cout << "打开" << memberList[i].friendId << "的群聊记录文件失败" << endl;
			return false;
		}
		//写入
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
		cout << "       您没有加入任何群" << endl;
		cout << "_________________________________" << endl;
		return;
	}
	cout << "您有" << grouplist.size() << "个群" << endl;
	cout << "_________________________________" << endl;

	for (int i = 0; i < grouplist.size(); i++) {
		cout << "|群号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << grouplist[i] << "|" << endl;
		cout << "|群名|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_allQQGroupList->findByGroupId(grouplist[i])->getGroupName() << "|" << endl;
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
	cout << "          群成员列表(" << memberList.size() << ")" << endl;
	cout << "_________________________________" << endl;

	for (int i = 0; i < memberList.size(); i++) {
		cout << "|QQ号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << memberList[i].friendId << "|" << endl;
		cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << memberList[i].friendName << "|" << endl;
		cout << "_________________________________" << endl;
	}
	cout << resetiosflags(ios::left);

	system("pause");
}

vector<QMsg> applicationQQLA::recvMsgFromGroup(qqGroupNodeLA* groupPtr)
{
	string path = "QQ\\" + to_string(m_currentUser->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupPtr->getGroupId()) + ".dat";
	//判断文件是否存在,不存在则创建
	if (_access(path.c_str(), 0) == -1) {
		ofstream outFile;
		outFile.open(path, ios::out);
		outFile.close();
	}
	//打开文件
	ifstream ifs(path, ios::in);
	if (!ifs.is_open()) {
		cout << "打开文件失败" << endl;
		return {};
	}
	//循环读取文件内的消息
	vector<QMsg> msgList;
	int id;
	string name;
	string time;
	char msg[300];
	memset(msg, 0, 300);
	while (ifs >> id >> name >> time) {
		//获取一整行的内容,包括空格
		ifs.ignore();
		ifs.getline(msg, 300);

		//创建消息结构体
		QMsg qmsg;
		qmsg.senderId = id;
		qmsg.senderName = name;
		qmsg.time = time;
		qmsg.msg = msg;
		//压入消息列表
		msgList.push_back(qmsg);
	}
	return msgList;
}

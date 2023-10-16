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
		cout << "           群组" << endl;
		cout << "__________________________________" << endl;
		showWeChatGroupList(m_currentUser->getWeChatGroupId());
		cout << "| 01 || 选择群                    |" << endl;
		cout << "| 02 || 搜索群                    |" << endl;
		cout << "| 03 || 创建群                    |" << endl;
		cout << "| 04 || 加入群                    |" << endl;
		cout << "| 05 || 退出群                    |" << endl;
		cout << "| 00 || 返回                      |" << endl;
		cout << "__________________________________" << endl;
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

void applicationWeChatLA::selectGroupPage()
{
	system("cls");
	cout << "         选择群组" << endl;
	showWeChatGroupList(m_currentUser->getWeChatGroupId());
	if (m_currentUser->getWeChatGroupId().size() == 0) {
		system("pause");
		return;
	}
	cout << "输入群号:";

	int groupId = 0;
	cin >> groupId;
	refreshInput();
	WeChatGroupNodeLA* p = m_allWeChatGroupList->findByGroupId(groupId);
	if (p == nullptr) {
		cout << "群不存在" << endl;
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
			cout << "| 01 || 发送消息                  |" << endl;
			cout << "| 02 || 查看群成员                |" << endl;
			cout << "| 03 || 解散群                    |" << endl;
			cout << "| 04 || 设置群                    |" << endl;
			cout << "| 05 || 邀请进群                  |" << endl;
			cout << "| 06 || 踢出群成员                |" << endl;
			cout << "| 07 || 查看群请求                |" << endl;
			cout << "| 08 || 设置管理员                |" << endl;
			cout << "| 09 || 设置群昵称                |" << endl;
			cout << "| 10 || 清空聊天记录              |" << endl;
			cout << "| 11 || 搜索聊天记录			      |" << endl;
			cout << "| 00 || 返回                      |" << endl;
			cout << "__________________________________" << endl;
			cout << "输入选项:";

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
				cout << "输入错误" << endl;
				system("pause");
				continue;
			}
		}
		else if (groupPtr->isAdministrator(userid)) {
			cout << "__________________________________" << endl;
			showMsg(recvMsgFromGroup(groupPtr));
			cout << "__________________________________" << endl;
			cout << "| 01 || 发送消息                  |" << endl;
			cout << "| 02 || 查看群成员                |" << endl;
			cout << "| 03 || 邀请进群                  |" << endl;
			cout << "| 04 || 退出群                    |" << endl;
			cout << "| 05 || 查看群请求                |" << endl;
			cout << "| 06 || 踢出群成员                |" << endl;
			cout << "| 07 || 设置群昵称                |" << endl;
			cout << "| 08 || 清空聊天记录              |" << endl;
			cout << "| 09 || 搜索聊天记录              |" << endl;
			cout << "| 00 || 返回                      |" << endl;
			cout << "__________________________________" << endl;
			cout << "输入选项:";

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
				cout << "输入错误" << endl;
				system("pause");
				continue;
			}
		}
		else if (groupPtr->isMember(userid)) {
			cout << "__________________________________" << endl;
			showMsg(recvMsgFromGroup(groupPtr));
			cout << "__________________________________" << endl;
			cout << "| 01 || 发送消息                  |" << endl;
			cout << "| 02 || 查看群成员                |" << endl;
			cout << "| 03 || 邀请进群                  |" << endl;
			cout << "| 04 || 退出群                    |" << endl;
			cout << "| 05 || 设置群昵称                |" << endl;
			cout << "| 06 || 清空聊天记录              |" << endl;
			cout << "| 07 || 搜索聊天记录              |" << endl;
			cout << "| 00 || 返回                      |" << endl;
			cout << "__________________________________" << endl;
			cout << "输入选项:";

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
				cout << "输入错误" << endl;
				system("pause");
				continue;
			}
		}
		else {
			cout << "__________________________________" << endl;
			cout << "| 01 || 查看群成员                |" << endl;
			cout << "| 02 || 申请加入群                |" << endl;
			cout << "| 00 || 返回                      |" << endl;
			cout << "__________________________________" << endl;
			cout << "输入选项:";

			int i = 0;
			cin >> i;
			refreshInput();
			if (i == 1) {
				showGroupMemberList(groupPtr);
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
				m_allWeChatGroupList->saveGroupListData();
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

void applicationWeChatLA::setAdminPage(WeChatGroupNodeLA* groupPtr)
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
	cout << "__________________________________" << endl;
	showGroupMemberList(groupPtr);

	cout << "输入要设置的WeChat号:";

	int WeChatNumber = 0;
	cin >> WeChatNumber;
	refreshInput();
	if (!groupPtr->isMember(WeChatNumber)) {
		cout << "该用户不是群成员" << endl;
		system("pause");
		return;
	}
	if (groupPtr->isOwner(WeChatNumber)) {
		cout << "已是群主" << endl;
		system("pause");
		return;
	}
	if (groupPtr->isAdministrator(WeChatNumber)) {
		cout << m_allWeChatUserList->findByWeChatId(WeChatNumber)->getUserName() << "是管理员" << endl;
		cout << "输入1将其撤销管理员" << endl;

		int i = 0;
		cin >> i;
		refreshInput();

		if (i == 1) {
			groupPtr->removeWeChatGroupAdmin(WeChatNumber);
			m_allWeChatGroupList->saveGroupListData();
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
		cout << m_allWeChatUserList->findByWeChatId(WeChatNumber)->getUserName() << "不是管理员" << endl;
		cout << "输入1将其设置为管理员" << endl;
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			groupPtr->addWeChatGroupAdmin(WeChatNumber);
			m_allWeChatGroupList->saveGroupListData();
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

void applicationWeChatLA::setGroupNickNamePage(WeChatGroupNodeLA* groupPtr) {
	system("cls");
	cout << "         设置群昵称" << endl;
	cout << "__________________________________" << endl;
	cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupNickName(m_currentUser->getAppUserId()) << "|" << endl;
	cout << "__________________________________" << endl;
	cout << "输入新的昵称(不含空格等特殊字符):" << endl;
	string nickName;
	cin >> nickName;
	refreshInput();
	groupPtr->setGroupNickName(m_currentUser->getAppUserId(), nickName);
	m_allWeChatGroupList->saveGroupListData();

	cout << "已设置" << endl;
	system("pause");
	return;

}

void applicationWeChatLA::searchChatRecordPage(WeChatGroupNodeLA* groupPtr)
{
	system("cls");
	cout << "         查找聊天记录" << endl;
	cout << "__________________________________" << endl;
	cout << "输入要查找的内容:" << endl;
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
	cout << "输入群号:" << endl;
	int groupId = 0;
	cin >> groupId;
	refreshInput();
	WeChatGroupNodeLA* p = m_allWeChatGroupList->findByGroupId(groupId);
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

void applicationWeChatLA::sendMsgPage(WeChatGroupNodeLA* groupPtr)
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

void applicationWeChatLA::createGroupPage() {
	system("cls");
	cout << "            创建群组" << endl;
	cout << "__________________________________" << endl;
	cout << "输入群名(不含空格等特殊字符):";
	string groupName;
	cin >> groupName;
	refreshInput();
	cout << "按1确认创建:";
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		WeChatGroupNodeLA* p = m_allWeChatGroupList->addGroup(groupName, m_currentUser->getAppUserId());

		m_currentUser->addWeChatGroupId(p->getGroupId());
		//保存文件
		m_allWeChatGroupList->saveGroupListData();
		m_allWeChatUserList->saveWeChatUserListData();
		system("cls");
		cout << "            创建成功" << endl;
		cout << "__________________________________" << endl;
		cout << "| 群号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupId() << "|" << endl;
		cout << "| 群名|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupName() << "|" << endl;
		cout << "__________________________________" << endl;
	}
	else {
		cout << "取消创建" << endl;
	}
	system("pause");
	return;

}

void applicationWeChatLA::joinGroupPage() {
	system("cls");
	if (m_allWeChatGroupList->size() == 0) {
		cout << "没有群可加入" << endl;
		system("pause");
		return;
	}

	default_random_engine e((unsigned int)time(NULL));
	int id1 = 1001 + e() % m_allWeChatGroupList->size();
	if (!m_currentUser->isAddedGroup(id1)) {
		WeChatGroupNodeLA* p = m_allWeChatGroupList->findByGroupId(id1);
		if (p != nullptr) {
			cout << "            推荐群组" << endl;
			cout << "__________________________________" << endl;
			cout << "|群号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << id1 << "|" << endl;
			cout << "|群名|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_allWeChatGroupList->findByGroupId(id1)->getGroupName() << "|" << endl;
			cout << "__________________________________" << endl;
			cout << resetiosflags(ios::left);

		}
	}
	cout << "输入要添加的群号:";

	int groupId = 0;
	cin >> groupId;
	refreshInput();
	if (m_currentUser->isAddedGroup(groupId)) {
		cout << "已经在群内" << endl;
		system("pause");
		return;
	}
	WeChatGroupNodeLA* p = m_allWeChatGroupList->findByGroupId(groupId);
	if (p == nullptr) {
		cout << "群不存在" << endl;
		system("pause");
		return;
	}
	else {
		system("cls");
		cout << "         加入群组" << endl;
		cout << "__________________________________" << endl;
		cout << "|群号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupId() << "|" << endl;
		cout << "|群名|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupName() << "|" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || 申请加入                  |" << endl;
		cout << "|其他|| 返回                      |" << endl;
		cout << "__________________________________" << endl;
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
			m_allWeChatGroupList->saveGroupListData();

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

bool applicationWeChatLA::disbandGroupPage(WeChatGroupNodeLA* groupPtr)
{
	system("cls");
	if (!groupPtr->isOwner(m_currentUser->getAppUserId())) {
		cout << "不是群主,无法解散群" << endl;
		system("pause");
		return false;
	}
	cout << "         解散群组" << endl;
	cout << "__________________________________" << endl;
	cout << "|群号|| " << setw(24) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupId() << "|" << endl;
	cout << "|群名|| " << setw(24) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupName() << "|" << endl;
	cout << "__________________________________" << endl;
	cout << "| 01 || 确认解散(将会删除聊天记录!)|" << endl;
	cout << "|其他|| 返回                      |" << endl;
	cout << "__________________________________" << endl;
	cout << "输入选项:";

	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		//删除每个用户所存储的群号
		int groupId = groupPtr->getGroupId();
		vector<userInfo> memberList = groupPtr->getWeChatGroupMemberInfoList();
		for (int i = 0; i < memberList.size(); i++) {
			WeChatUserNodeLA* p = m_allWeChatUserList->findByWeChatId(memberList[i].friendId);
			p->deleteWeChatGroupId(groupId);
			//删除聊天文件
			string path = "WeChat\\" + to_string(p->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupId) + ".dat";
			if (_access(path.c_str(), 0) != -1) {
				remove(path.c_str());
			}
		}

		//移除群
		m_allWeChatGroupList->removeGroup(groupPtr);
		//保存到文件
		m_allWeChatGroupList->saveGroupListData();
		m_allWeChatUserList->saveWeChatUserListData();
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

bool applicationWeChatLA::quitGroupPage() {
	system("cls");
	cout << "         退出群组" << endl;
	cout << "__________________________________" << endl;
	showWeChatGroupList(m_currentUser->getWeChatGroupId());
	if (m_currentUser->getWeChatGroupId().size() == 0) {
		cout << "没有群可退出" << endl;
		system("pause");
		return false;
	}
	cout << "输入群号:" << endl;
	int groupId = 0;
	cin >> groupId;
	refreshInput();
	WeChatGroupNodeLA* p = m_allWeChatGroupList->findByGroupId(groupId);
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
		cout << "__________________________________" << endl;
		cout << "| 群号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupId() << "|" << endl;
		cout << "| 群名|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getGroupName() << "|" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || 确认退出(将会删除聊天记录!)|" << endl;
		cout << "|其他|| 返回                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "输入选项:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			//相互删除
			if (p->isAdministrator(m_currentUser->getAppUserId())) {
				p->removeWeChatGroupAdmin(m_currentUser->getAppUserId());
			}
			p->removeMember(m_currentUser->getAppUserId());
			m_currentUser->deleteWeChatGroupId(p->getGroupId());
			//保存到文件
			m_allWeChatGroupList->saveGroupListData();
			m_allWeChatUserList->saveWeChatUserListData();
			string path = "WeChat\\" + to_string(m_currentUser->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupId) + ".dat";
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

bool applicationWeChatLA::quitGroupPage(WeChatGroupNodeLA* groupPtr) {
	if (groupPtr->isOwner(m_currentUser->getAppUserId())) {
		cout << "群主无法退出群组,请尝试解散群" << endl;
		system("pause");
		return false;
	}
	system("cls");
	cout << "         退出群组" << endl;
	cout << "__________________________________" << endl;
	cout << "| 群号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupId() << "|" << endl;
	cout << "| 群名|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << groupPtr->getGroupName() << "|" << endl;
	cout << "__________________________________" << endl;
	cout << "| 01 || 确认退出(将会删除聊天记录!)|" << endl;
	cout << "|其他|| 返回                      |" << endl;
	cout << "__________________________________" << endl;
	cout << "输入选项:";

	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		//相互删除
		if (groupPtr->isAdministrator(m_currentUser->getAppUserId())) {
			groupPtr->removeWeChatGroupAdmin(m_currentUser->getAppUserId());
		}
		groupPtr->removeMember(m_currentUser->getAppUserId());
		m_currentUser->deleteWeChatGroupId(groupPtr->getGroupId());
		//保存到文件
		m_allWeChatGroupList->saveGroupListData();
		m_allWeChatUserList->saveWeChatUserListData();
		string path = "WeChat\\" + to_string(m_currentUser->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupPtr->getGroupId()) + ".dat";
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

void applicationWeChatLA::setGroupConfigPage(WeChatGroupNodeLA* groupPtr) {
	while (1)
	{
		system("cls");
		cout << setw(20) << setfill(' ') << groupPtr->getGroupName() << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || 修改群名                  |" << endl;
		cout << "| 02 || 是否允许邀请进群          |" << endl;
		cout << "| 03 || 是否允许搜索加入          |" << endl;
		cout << "| 04 || 是否允许发言              |" << endl;
		cout << "| 05 || 是否允许设置管理员        |" << endl;
		cout << "| 06 || 是否群成员临时会话        |" << endl;
		cout << "| 00 || 返回                      |" << endl;
		cout << "__________________________________" << endl;
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
			groupPtr->setWeChatGroupName(groupName);
			m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowInvite(false);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowInvite(true);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowJoin(false);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowJoin(true);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowSend(false);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowSend(true);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowAdmins(false);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowAdmins(true);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowSubgroup(false);
					m_allWeChatGroupList->saveGroupListData();
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
					groupPtr->setWeChatGroupIsAllowSubgroup(true);
					m_allWeChatGroupList->saveGroupListData();
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


void applicationWeChatLA::kickMemberPage(WeChatGroupNodeLA* groupPtr)
{
	system("cls");
	cout << "         踢出群成员" << endl;
	cout << "__________________________________" << endl;
	showGroupMemberList(groupPtr);

	cout << "输入要踢出的群成员WeChat号:";
	int WeChatNumber = 0;
	cin >> WeChatNumber;
	refreshInput();
	if (!groupPtr->isMember(WeChatNumber)) {
		cout << "该用户不是群成员" << endl;
		system("pause");
		return;
	}
	if (groupPtr->isOwner(WeChatNumber)) {
		cout << "不能踢出群主" << endl;
		system("pause");
		return;
	}
	if (m_currentUser->getAppUserId() == WeChatNumber) {
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
		WeChatUserNodeLA* p = m_allWeChatUserList->findByWeChatId(WeChatNumber);
		p->deleteWeChatGroupId(groupId);

		//移除用户
		groupPtr->removeMember(WeChatNumber);
		//保存到文件
		m_allWeChatGroupList->saveGroupListData();
		m_allWeChatUserList->saveWeChatUserListData();
		string path = "WeChat\\" + to_string(WeChatNumber) + "\\groupchatrecord\\" + to_string(groupId) + ".dat";
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

void applicationWeChatLA::groupRequestPage(WeChatGroupNodeLA* groupPtr) {
	while (1)
	{
		if (!groupPtr->isAdministrator(m_currentUser->getAppUserId()) && !groupPtr->isOwner(m_currentUser->getAppUserId())) {
			cout << "无权处理申请";
			system("pause");
			return;
		}

		vector<userInfo> requestList = groupPtr->getWeChatGroupRequestInfoList();
		if (requestList.size() == 0) {
			cout << "没有申请" << endl;
			system("pause");
			return;
		}
		system("cls");
		cout << "           申请列表" << endl;
		cout << "__________________________________" << endl;

		for (int i = 0; i < requestList.size(); i++) {
			cout << "|微号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << requestList[i].friendId << "|" << endl;
			cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << requestList[i].friendName << "|" << endl;
			cout << "__________________________________" << endl;
		}
		cout << resetiosflags(ios::left);
		cout << "| 01 || 同意                      |" << endl;
		cout << "| 02 || 拒绝                      |" << endl;
		cout << "| 00 || 返回                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "输入选项:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "输入同意的WeChat号:";
			int WeChatNumber = 0;
			cin >> WeChatNumber;
			refreshInput();
			if (groupPtr->isMember(WeChatNumber))
			{
				cout << "该用户已是群成员" << endl;
				groupPtr->removeRequest(WeChatNumber);
				m_allWeChatGroupList->saveGroupListData();
				system("pause");
				continue;
			}
			//检查是否存在该请求
			int j = 0;
			for (j = 0; j < requestList.size(); j++) {
				if (requestList[j].friendId == WeChatNumber) {
					break;
				}
			}
			if (j == requestList.size()) {
				cout << "请求不存在" << endl;
				system("pause");
				continue;
			}
			//互相添加
			groupPtr->addMember(WeChatNumber);

			WeChatUserNodeLA* p = m_allWeChatUserList->findByWeChatId(WeChatNumber);
			p->addWeChatGroupId(groupPtr->getGroupId());
			//移除请求
			groupPtr->removeRequest(WeChatNumber);

			//保存到文件
			m_allWeChatGroupList->saveGroupListData();
			m_allWeChatUserList->saveWeChatUserListData();

			cout << "添加成功" << endl;
			system("pause");
			continue;
		}
		else if (i == 2) {
			cout << "输入拒绝的WeChat号:";
			int WeChatNumber = 0;
			cin >> WeChatNumber;
			refreshInput();
			if (groupPtr->isMember(WeChatNumber))
			{
				cout << "该用户已是群成员" << endl;
				groupPtr->removeRequest(WeChatNumber);
				m_allWeChatGroupList->saveGroupListData();
				system("pause");
				continue;
			}
			//检查是否存在该请求
			int j = 0;
			for (j = 0; j < requestList.size(); j++) {
				if (requestList[j].friendId == WeChatNumber) {
					break;
				}
			}
			if (j == requestList.size()) {
				cout << "请求不存在" << endl;
				system("pause");
				continue;
			}
			//移除请求
			groupPtr->removeRequest(WeChatNumber);

			//保存到文件
			m_allWeChatGroupList->saveGroupListData();

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

bool applicationWeChatLA::sendMsgToGroup(WeChatGroupNodeLA* groupPtr, const char* msg) {
	//给群组内所有人(包括自己)的文件添加发送时间和消息内容
	vector<userInfo> memberList = groupPtr->getWeChatGroupMemberInfoList();
	for (int i = 0; i < memberList.size(); i++) {
		string path = "WeChat\\" + to_string(memberList[i].friendId) + "\\groupchatrecord\\" + to_string(groupPtr->getGroupId()) + ".dat";

		//获取时间
		string time = getTime();
		//打开每个用户的groupchatrecord文件写入发送者WeChat号,发送者昵称,发送时间,消息内容
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

void applicationWeChatLA::showWeChatGroupList(const vector<int>& grouplist) {
	if (grouplist.size() == 0)
	{
		cout << "       您没有加入任何群" << endl;
		cout << "__________________________________" << endl;
		return;
	}
	cout << "您有" << grouplist.size() << "个群" << endl;
	cout << "__________________________________" << endl;

	for (int i = 0; i < grouplist.size(); i++) {
		cout << "|群号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << grouplist[i] << "|" << endl;
		cout << "|群名|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_allWeChatGroupList->findByGroupId(grouplist[i])->getGroupName() << "|" << endl;
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
	cout << "          群成员列表(" << memberList.size() << ")" << endl;
	cout << "__________________________________" << endl;

	for (int i = 0; i < memberList.size(); i++) {
		cout << "|微号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << memberList[i].friendId << "|" << endl;
		cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << memberList[i].friendName << "|" << endl;
		cout << "__________________________________" << endl;
	}
	cout << resetiosflags(ios::left);

	system("pause");
}

vector<WMsg> applicationWeChatLA::recvMsgFromGroup(WeChatGroupNodeLA* groupPtr)
{
	string path = "WeChat\\" + to_string(m_currentUser->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupPtr->getGroupId()) + ".dat";
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
	vector<WMsg> msgList;
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
		WMsg wmsg;
		wmsg.senderId = id;
		wmsg.senderName = name;
		wmsg.time = time;
		wmsg.msg = msg;
		//压入消息列表
		msgList.push_back(wmsg);
	}
	return msgList;
}

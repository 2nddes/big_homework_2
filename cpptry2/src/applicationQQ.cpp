#define _CRT_SECURE_NO_WARNINGS
#include"utils.h"
#include"applicationQQ.h"
#include"platform.h"
#include<iostream>
#include<fstream>
#include<iomanip>

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
				cout << "平台用户 "
					<< curPlatformUser->getUserName()
					<< " 未开通QQ服务,是否开通" << endl;
				cout << "1.开通" << endl;
				cout << "0.不开通" << endl;
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
					cout << "输入错误" << endl;
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
		cout << "             QQ登录" << endl;
		cout << "_________________________________" << endl;
		cout << "| 01 || 登录QQ                    |" << endl;
		cout << "| 02 || 注册QQ                    |" << endl;
		cout << "| 00 || 退出QQ                    |" << endl;
		cout << "_________________________________" << endl;
		cout << "输入选项:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1)
		{
			cout << "请输入QQ号:" << endl;
			int qqNumber = -1;
			cin >> qqNumber;
			refreshInput();

			qqUserNodeLA* qqUser = m_allQQUserList->findByQQId(qqNumber);
			if (qqUser == nullptr) {
				cout << "QQ号不存在,请检查输入" << endl;
				system("pause");
				continue;
			}

			cout << "请输入密码:" << endl;
			string password;
			cin >> password;
			refreshInput();

			if (qqUser->getUserPasswd() == password) {
				system("cls");
				cout << "		登录成功!"<< endl
					<< qqUser->getUserName() << "欢迎回来" << endl;
				system("pause");
				return qqUser;
			}
			else {
				cout << "密码错误" << endl;
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
			cout << "输入错误" << endl;
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
		cout << "             QQ注册" << endl;
		cout << "_________________________________" << endl;
		cout << "| 01 || 注册QQ                    |" << endl;
		cout << "| 00 || 退出QQ                    |" << endl;
		cout << "_________________________________" << endl;

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 0)
			return nullptr;

		cout << "输入昵称" << endl;
		string userName;
		cin >> userName;
		refreshInput();
		cout << "输入密码" << endl;
		string password;
		cin >> password;
		refreshInput();
		cout << "             QQ注册" << endl;
		cout << "_________________________________" << endl;
		cout << "|昵称|| " << setw(26) << setiosflags(ios::left) << userName << "|" << endl;
		cout << "|密码|| " << setw(26) << setiosflags(ios::left) << password << "|" << endl;
		cout << "_________________________________" << endl;
		cout << "| 01 || 确认注册                  |" << endl;
		cout << "| 00 || 取消注册                  |" << endl;
		cout << "_________________________________" << endl;
		cout << "输入选项:";

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

				cout << "		注册成功!" << endl;
				cout << "您的QQ号为:" << p->getAppUserId() << endl;
				cout << "您的密码为:" << p->getUserPasswd() << endl;
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
			cout << "取消注册" << endl;
			system("pause");
			return nullptr;
		}
		else {
			cout << "输入错误" << endl;
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
	cout << "		已退出QQ" << endl;
	system("pause");
}

void applicationQQLA::mainPage() {
	while (1) {
		system("cls");
		cout << "             QQ" << endl;
		cout << "_________________________________" << endl;
		cout << "| 01 || 好友                      |" << endl;
		cout << "| 02 || 群组                      |" << endl;
		cout << "| 03 || 个人资料设置              |" << endl;
		cout << "| 04 || 退出登录                  |" << endl;
		cout << "| 00 || 退出                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "输入选项:";

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
		cout << "             个人资料设置" << endl;
		cout << "_________________________________" << endl;
		cout << "|QQ号|| " << setw(26) << setiosflags(ios::left) << m_currentUser->getAppUserId() << "|" << endl;
		cout << "|昵称|| " << setw(26) << setiosflags(ios::left) << m_currentUser->getUserName() << "|" << endl;
		cout << "_________________________________" << endl;
		cout << "| 01 || 修改昵称                  |" << endl;
		cout << "| 02 || 修改密码                  |" << endl;
		cout << "| 00 || 返回                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "输入选项:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "输入新昵称:" << endl;
			string name;
			cin >> name;
			refreshInput();
			m_currentUser->setUserName(name);
			m_allQQUserList->saveQQUserListData();
			system("cls");
			cout << "		修改成功" << endl;
			cout << "新昵称为:" << m_currentUser->getUserName() << endl;
			system("pause");
			continue;
		}
		else if (i == 2) {
			cout << "输入新密码" << endl;
			string password;
			cin >> password;
			refreshInput();
			m_currentUser->setUserPasswd(password);
			m_allQQUserList->saveQQUserListData();
			system("cls");
			cout << "		修改成功" << endl;
			cout << "新密码为:" << m_currentUser->getUserPasswd() << endl;
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

//////////////////////////////////////////////////////
void applicationQQLA::friendPage() {
	while (1) {
		system("cls");
		cout << "           好友" << endl;
		cout << "_________________________________" << endl;
		showQQFriendList(m_currentUser->getQQFriendInfo());
		cout << "_________________________________" << endl;
		cout << "| 01 || 选择好友                  |" << endl;
		cout << "| 02 || 添加好友                  |" << endl;
		cout << "| 03 || 删除好友                  |" << endl;
		cout << "| 04 || 查看好友请求              |" << endl;
		cout << "| 00 || 返回                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "输入选项:";

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
	cout<<"           好友" << endl;
	cout << "_________________________________" << endl;
	showQQFriendList(m_currentUser->getQQFriendInfo());
	cout << "_________________________________" << endl;
	cout << "输入好友QQ号:";
	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	if (m_currentUser->isFriend(qqNumber)) {
		chatWithFriendPage(m_allQQUserList->findByQQId(qqNumber));
	}
	else {
		cout << "未找到好友" << endl;
		system("pause");
		return;
	}
}

void applicationQQLA::sendMsgPage(qqUserNodeLA* friendPtr)
{
	cout << "直接回车返回;输入消息回车发送:" << endl;
	char message[300];
	memset(message, 0, 300);
	cin.getline(message, 300);
	if (message[0] == '\0') {
		return;
	}
	(sendMsgToFriend(friendPtr, message))
		? cout << "发送成功" << endl
		: cout << "发送失败" << endl;
}

void applicationQQLA::addFriendPage() {
	system("cls");
	cout<<"         添加好友" << endl;
	//TODO:推荐好友//////////////////////////////////////
	cout << "_________________________________" << endl;
	cout << "输入要添加的QQ号:" << endl;
	int id;
	cin >> id;
	refreshInput();
	if (id == m_currentUser->getAppUserId())
	{
		cout << "你不能添加自己为好友" << endl;
		system("pause");
		return;
	}

	qqUserNodeLA* friendToAddPtr = m_allQQUserList->findByQQId(id);
	if (friendToAddPtr == nullptr) {
		cout<<"用户不存在"<<endl;
		system("pause");
		return;
	}
	if (m_currentUser->isFriend(friendToAddPtr)) {
		cout<<"已经是好友"<<endl;
		system("pause");
		return;
	}
	cout << "          用户信息" << endl;
	cout << "_________________________________" << endl;
	cout << "| QQ号|| " << setw(26) << setiosflags(ios::left) << friendToAddPtr->getAppUserId() << "|" << endl;
	cout << "| 昵称|| " << setw(26) << setiosflags(ios::left) << friendToAddPtr->getUserName() << "|" << endl;
	cout << "_________________________________" << endl;
	cout << "| 01 || 好友申请                  |" << endl;
	cout << "| 00 || 取消                      |" << endl;
	cout << "_________________________________" << endl;
	cout << "输入选项:";
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		applyFriend(m_currentUser, friendToAddPtr);
		cout << "好友申请成功" << endl;
		system("pause");
		return;
	}
	else if (i == 0) {
		cout << "取消添加" << endl;
		system("pause");
		return;
	}
	else {
		cout << "输入错误" << endl;
		system("pause");
		return;
	}
	
}

void applicationQQLA::deleteFriendPage() {
	system("cls");
	cout << "           删除好友" << endl;
	cout << "_________________________________" << endl;
	showQQFriendList(m_currentUser->getQQFriendInfo());
	cout << "_________________________________" << endl;
	cout << "输入待删除好友QQ号:" << endl;
	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	if(qqNumber==m_currentUser->getAppUserId()) {
		cout << "不能删除自己" << endl;
		system("pause");
		return;
	}
	int i = 0;
	for (i = 0; i < m_currentUser->getQQFriendInfo().size(); i++) {
		if (m_currentUser->getQQFriendInfo()[i].friendId == qqNumber) {
			cout << "          用户信息" << endl;
			cout << "_________________________________" << endl;
			cout << "| QQ号|| " << setw(26) << setiosflags(ios::left) << m_allQQUserList->findByQQId(qqNumber)->getAppUserId() << "|" << endl;
			cout << "| 昵称|| " << setw(26) << setiosflags(ios::left) << m_allQQUserList->findByQQId(qqNumber)->getUserName() << "|" << endl;
			cout << "_________________________________" << endl;
			cout << "| 01 || 确认删除                  |" << endl;
			cout << "| 00 || 取消                      |" << endl;
			cout << "_________________________________" << endl;
			cout << "输入选项:";

			int i = 0;
			cin >> i;
			refreshInput();
			if (i == 1) {
				//互相删除好友
				m_allQQUserList->findByQQId(qqNumber)->deleteQQFriendId(m_currentUser->getAppUserId());
				m_currentUser->deleteQQFriendId(qqNumber);
				m_allQQUserList->saveQQUserListData();
				cout << "删除成功" << endl;
			}
			else if ( i == 0) {
				cout << "取消删除" << endl;
			}
			else {
				cout << "输入错误" << endl;
			}
			system("pause");
			return;
		}
	}
	if (i == m_currentUser->getQQFriendInfo().size()) {
		cout << "不是好友" << endl;
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
			cout << "打开文件失败" << endl;
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
			cout << "目前没有好友请求" << endl;
			system("pause");
			return;
		}

		system("cls");
		cout << "         好友请求列表" << endl;
		cout << "_________________________________" << endl;
		cout << "|QQ号|          昵 称           |" << endl;
		cout << "_________________________________" << endl;
		for (int i = 0; i < qqNumberList.size(); i++) {
			cout << "|" << setw(4) << qqNumberList[i] << "|";
			cout << m_allQQUserList->findByQQId(qqNumberList[i])->getUserName() << "|" << endl;
			cout << "_________________________________" << endl;
		}
		cout << "| 01 || 同意                    |" << endl;
		cout << "| 02 || 拒绝                    |" << endl;
		cout << "| 00 || 返回                    |" << endl;
		cout << "_________________________________" << endl;
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "输入同意的好友QQ号:" << endl;
			int qqNumber = 0;
			cin >> qqNumber;
			refreshInput();
			if (count(qqNumberList.begin(),qqNumberList.end(),qqNumber) == 0) {
				cout << "用户不存在" << endl;
				system("pause");
				continue;
			}
			qqUserNodeLA* friendToAddPtr = m_allQQUserList->findByQQId(qqNumber);
			//互相添加好友
			userInfo info;
			info.friendId = friendToAddPtr->getAppUserId();
			info.friendName = friendToAddPtr->getUserName();
			m_currentUser->addQQFriendInfo(info);
			info.friendId = m_currentUser->getAppUserId();
			info.friendName = m_currentUser->getUserName();
			friendToAddPtr->addQQFriendInfo(info);
			//删除请求
			remove(qqNumberList.begin(), qqNumberList.end(), qqNumber);
			//保存文件
			m_allQQUserList->saveQQUserListData();
			ofstream ofs(path, ios::out);
			for (auto i : qqNumberList) {
				ofs << i << endl;
			}
			ofs.close();
			cout << "好友 " << friendToAddPtr->getUserName() << " 添加成功" << endl;
			system("pause");
			return;
		}
		else if (i == 2) {
			cout << "输入拒绝的好友QQ号:" << endl;
			int qqNumber = 0;
			cin >> qqNumber;
			refreshInput();
			if (count(qqNumberList.begin(), qqNumberList.end(), qqNumber)) {
				cout << "好友申请不存在" << endl;
				system("pause");
				continue;
			}
			//删除请求
			remove(qqNumberList.begin(), qqNumberList.end(), qqNumber);
			//保存文件
			ofstream ofs(path, ios::out);
			for (auto i : qqNumberList) {
				ofs << i << endl;
			}
			ofs.close();
			cout << "拒绝成功" << endl;
			system("pause");
			return;
		}
		else if (i == 0) {
			return;
		}
		else {
			cout << "输入错误" << endl;
			system("pause");
			return;
		}
	}
}

void applicationQQLA::chatWithFriendPage(qqUserNodeLA* friendPtr) {
	while (1)
	{
		system("cls");
		int len = friendPtr->getUserName().length();
		cout<<setw((40 - len) / 2)  << friendPtr->getUserName() << endl;
		cout << "_________________________________" << endl;
		showMsg(recvMsgFromFriend(friendPtr));
		cout << "_________________________________" << endl;
		cout << "| 01 || 发送消息                  |" << endl;
		cout << "| 00 || 返回                      |" << endl;
		cout << "_________________________________" << endl;
		cout << "输入选项:";
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
			cout << "输入错误" << endl;
			system("pause");
			continue;
		}
	}
}

void applicationQQLA::applyFriend(qqUserNodeLA* user, qqUserNodeLA* friendToAdd) {
	string path = "QQ\\" + to_string(friendToAdd->getAppUserId()) + "\\friendrequest.dat";
	//在好友的请求列表中添加请求
	ofstream ofs(path, ios::app);
	if (!ofs.is_open()) {
		cout << "打开文件失败" << endl;
		return;
	}
	ofs << user->getAppUserId() << endl;
	ofs.close();

}

//////////////////////////////////////////////////////
void applicationQQLA::groupPage() {
	while (1) {
		system("cls");
		showQQGroupList(m_currentUser->getQQGroupId());
		cout << "1.选择群" << endl;
		cout << "2.搜索群" << endl;
		cout << "3.创建群" << endl;
		cout << "4.加入群" << endl;
		cout << "5.退出群" << endl;
		cout << "0.返回" << endl;
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
	showQQGroupList(m_currentUser->getQQGroupId());
	cout << "输入群号" << endl;
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
	while(1)
	{
		system("cls");
		showMsg(recvMsgFromGroup(groupPtr));
		
		int userid = m_currentUser->getAppUserId();
		if(groupPtr->isOwner(userid)) {
			cout << "1.发送消息" << endl;
			cout << "2.查看群成员" << endl;
			cout << "3.解散群" << endl;
			cout << "4.设置群" << endl;
			cout << "5.邀请进群" << endl;
			cout << "6.踢出群成员" << endl;
			cout << "7.查看群请求" << endl;
			cout << "8.设置管理员" << endl;
			cout << "0.返回" << endl;
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
				cout << "输入错误" << endl;
				system("pause");
				continue;
			}
		}
		else if (groupPtr->isAdministrator(userid)) {
			cout << "1.发送消息" << endl;
			cout << "2.查看群成员" << endl;
			cout << "3.邀请进群" << endl;
			cout << "4.退出群" << endl;
			cout << "5.查看群请求" << endl;
			cout << "6.踢出群成员" << endl;

			cout << "0.返回" << endl;
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
				cout << "输入错误" << endl;
				system("pause");
				continue;
			}
		}
		else if(groupPtr->isMember(userid))
		{
			cout << "1.发送消息" << endl;
			cout << "2.查看群成员" << endl;
			cout << "3.邀请进群" << endl;
			cout << "4.退出群" << endl;
			cout << "0.返回" << endl;
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
				quitGroupPage(groupPtr);
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
			cout << "1.查看群成员" << endl;
			cout << "2.申请加入群" << endl;
			cout << "0.返回" << endl;
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
		cout << "你不是群主" << endl;
		system("pause");
		return;
	}
	if (!groupPtr->isAllowAdmins()) {
		cout << "已设置不允许管理员" << endl;
		system("pause");
		return;
	}
	cout << "输入要设置的管理员QQ号" << endl;
	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	if(!groupPtr->isMember(qqNumber)) {
		cout << "该用户不是群成员" << endl;
		system("pause");
		return;
	}
	if (groupPtr->isAdministrator(qqNumber)) {
		cout << "该用户已经是管理员" << endl;
		system("pause");
		return;
	}
	cout << "确认设置按1" << endl;
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

void applicationQQLA::searchGroupPage() {
	system("cls");
	cout << "输入群号" << endl;
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
	cout << "输入群名" << endl;
	string groupName;
	cin >> groupName;
	refreshInput();
	cout << "确认创建按1" << endl;
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		qqGroupNodeLA* p = m_allQQGroupList->addGroup(groupName, m_currentUser->getAppUserId());
		
		m_currentUser->addQQGroupId(p->getGroupId());
		//保存文件
		m_allQQGroupList->saveGroupListData();
		m_allQQUserList->saveQQUserListData();

		cout << "创建成功" << endl;
		cout << "群号为" << p->getGroupId() << endl;
		cout << "群名为" << p->getGroupName() << endl;
	}
	else {
		cout << "取消创建" << endl;
	}
	system("pause");
	return;

}

void applicationQQLA::joinGroupPage() {
	system("cls");
	cout << "输入群号" << endl;
	int groupId = 0;
	cin >> groupId;
	refreshInput();
	if(m_currentUser->isAddedGroup(groupId)) {
		cout << "已经在群里" << endl;
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
		cout << p->getGroupName() << endl;
		cout << "申请加入按1" << endl;
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			//输入在群里的昵称
			cout << "输入昵称" << endl;
			string name;
			cin >> name;
			refreshInput();
			//添加到群成员列表
			userInfo info;
			info.friendId = m_currentUser->getAppUserId();
			info.friendName = name;
			//添加请求
			p->addRequest(info);
			//保存到文件
			m_allQQGroupList->saveGroupListData();

			cout << "申请加入成功" << endl;
		}
		else {
			cout << "取消加入" << endl;
		}
		system("pause");
		return;
	}
}

void applicationQQLA::disbandGroupPage(qqGroupNodeLA* groupPtr)
{
	cout << "确认解散群" << groupPtr->getGroupName() << "按1" << endl;
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
		}

		//移除群
		m_allQQGroupList->removeGroup(groupPtr);
		cout << "解散成功" << endl;
		system("pause");
		return;
	}
	else {
		cout << "取消解散" << endl;
	}
}

void applicationQQLA::quitGroupPage() {
	system("cls");
	showQQGroupList(m_currentUser->getQQGroupId());
	cout << "输入群号" << endl;
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
		cout << p->getGroupName() << endl;
		cout << "确认退出按1" << endl;
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			//相互删除
			p->removeMember(m_currentUser->getAppUserId());
			m_currentUser->deleteQQGroupId(p->getGroupId());
			//保存到文件
			m_allQQGroupList->saveGroupListData();
			m_allQQUserList->saveQQUserListData();

			cout << "退出成功" << endl;
		}
		else {
			cout << "取消退出" << endl;
		}
		system("pause");
		return;
	}
}

void applicationQQLA::quitGroupPage(qqGroupNodeLA* groupPtr) {
	cout << "确认退出按1" << endl;
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		//相互删除
		groupPtr->removeMember(m_currentUser->getAppUserId());
		m_currentUser->deleteQQGroupId(groupPtr->getGroupId());
		//保存到文件
		m_allQQGroupList->saveGroupListData();
		m_allQQUserList->saveQQUserListData();

		cout << "退出成功" << endl;
	}
	else {
		cout << "取消退出" << endl;
	}
	system("pause");
	return;
}

void applicationQQLA::setGroupConfigPage(qqGroupNodeLA* groupPtr) {
	while (1) 
	{
		system("cls");
		cout << "1.修改群名" << endl;
		cout << "2.是否允许邀请进群" << endl;
		cout << "3.是否允许搜索加入" << endl;
		cout << "4.是否允许发言" << endl;
		cout << "5.是否允许管理员" << endl;
		cout << "6.是否群成员临时会话" << endl;
		cout << "0.返回" << endl;
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "当前群名为" << groupPtr->getGroupName() << endl;
			cout << "输入新群名,直接回车返回" << endl;
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
				cout << "当前允许邀请进群,禁止按1" << endl;
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
				cout << "当前禁止邀请进群,允许按1" << endl;
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
				cout << "当前允许搜索加入,禁止按1" << endl;
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
				cout << "当前禁止搜索加入,允许按1" << endl;
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
				cout << "当前允许发言,禁止按1" << endl;
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
				cout << "当前禁止发言,允许按1" << endl;
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
				cout << "当前允许管理员,禁止按1" << endl;
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
				cout << "当前禁止管理员,允许按1" << endl;
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
				cout << "当前允许群成员临时会话,禁止按1" << endl;
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
				cout << "当前禁止群成员临时会话,允许按1" << endl;
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

void applicationQQLA::inviteFriendInPage(qqGroupNodeLA* groupPtr){
	if (!groupPtr->isAllowInvite()) {
		cout << "该群当前不允许邀请进入" << endl;
		system("pause");
		return;
	}
	vector<userInfo> memberList = m_currentUser->getQQFriendInfo();
	system("cls");
	showQQFriendList(memberList);
	cout << "输入要邀请的好友QQ号" << endl;
	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	if (groupPtr->isMember(qqNumber)) {
		cout << "该用户已经在群里" << endl;
		system("pause");
		return;
	}
	cout << "确认邀请按1" << endl;
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		groupPtr->addMember(qqNumber);
	}
	else {
		cout << "取消邀请" << endl;
		system("pause");
		return;
	}
}

void applicationQQLA::kickMemberPage(qqGroupNodeLA* groupPtr)
{
	system("cls");
	cout << "输入要踢出的群成员QQ号" << endl;
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
		cout << "踢出自己将退出该群" << endl;
		quitGroupPage(groupPtr);
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
		cout << "踢出成功" << endl;
		system("pause");
	}
	else {
		cout << "取消踢出" << endl;
		system("pause");
	}


}

void applicationQQLA::groupRequestPage(qqGroupNodeLA* groupPtr)
{
	//TODO
}

/////////////////////////////////////////////////////////////////
bool applicationQQLA::sendMsgToFriend(qqUserNodeLA* friendPtr, const char* msg) {
	string path = "QQ\\" + to_string(friendPtr->getAppUserId()) + "\\chatrecord\\" + to_string(m_currentUser->getAppUserId()) + ".dat";
	//获取时间
	string time = getTime();
	//打开好友的chatrecord文件写入发送者QQ号,发送者昵称,发送时间,消息内容
	ofstream ofs(path, ios::app);
	if (!ofs.is_open()) {
		cout << "打开" << friendPtr->getAppUserId() << "的聊天记录文件失败" << endl;
		return false;
	}
	//写入
	ofs << m_currentUser->getAppUserId() << endl;
	ofs << m_currentUser->getUserName() << endl;
	ofs << time << endl;
	ofs << msg << endl;
	ofs.close();
	
	//打开自己的chatrecord文件写入发送者QQ号,发送者昵称,发送时间,消息内容
	path = "QQ\\" + to_string(m_currentUser->getAppUserId()) + "\\chatrecord\\" + to_string(friendPtr->getAppUserId()) + ".dat";
	ofs.open(path, ios::app);
	if (!ofs.is_open()) {
		cout << "打开" << m_currentUser->getAppUserId() << "的聊天记录文件失败" << endl;
		return false;
	}
	//写入
	ofs << m_currentUser->getAppUserId() << endl;
	ofs << m_currentUser->getUserName() << endl;
	ofs << time << endl;
	ofs << msg << endl;
	ofs.close();

	return true;
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

vector<QMsg> applicationQQLA::recvMsgFromFriend(qqUserNodeLA* friendPtr)
{
	string path = "QQ\\" + to_string(m_currentUser->getAppUserId()) + "\\chatrecord\\" + to_string(friendPtr->getAppUserId()) + ".dat";
	//判断文件是否存在,不存在则创建
	if(_access(path.c_str(), 0) == -1) {
		ofstream outFile;
		outFile.open(path, ios::out);
		outFile.close();
	}
	ifstream ifs(path, ios::in);
	if (!ifs.is_open()) {
		cout << "打开文件失败" << endl;
		return {};
	}
	//循环读取文件内的消息
	vector<QMsg> msgList;
	int id = 0;
	string name;
	string time;
	string msg;
	while (ifs >> id >> name >> time >> msg) {
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

vector<QMsg> applicationQQLA::recvMsgFromGroup(qqGroupNodeLA* groupPtr)
{
	string path	= "QQ\\" + to_string(m_currentUser->getAppUserId()) + "\\groupchatrecord\\" + to_string(groupPtr->getGroupId()) + ".dat";
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
	string msg;
	while (ifs >> id >> name >> time >> msg) {
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

/////////////////////////////////////////////////////////////////
void applicationQQLA::makeUserFile(string path){
	//创建用户文件夹
	My_mkdir(path.c_str());

	//创建好友请求列表文件
	//文件存在则不覆盖原文件
	My_mkfile(path.c_str(), "friendrequest.dat");
	
	//创建好友聊天记录文件夹
	My_mkdir((path + "\\chatrecord").c_str());
	//创建群聊记录文件夹
	My_mkdir((path + "\\groupchatrecord").c_str());

}

void applicationQQLA::showMsg(vector<QMsg> m) {
	for (int i = 0; i < m.size(); i++) {
		if (m_currentUser->getAppUserId() == m[i].senderId) {
			cout << "我 " << "("<<m[i].time<<")" << endl;
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

void applicationQQLA::showQQFriendList(vector<userInfo> friendlist) {
	if (friendlist.size() == 0)
	{
		cout << "您没有任何好友" << endl;
		return;
	}
	cout << "您有" << friendlist.size() << "个好友" << endl;
	cout << "好友昵称 好友QQ号" << endl;
	for (int i = 0; i < friendlist.size(); i++) {
		cout << friendlist[i].friendName << " ";
		cout << friendlist[i].friendId << endl;
	}
}

void applicationQQLA::showQQGroupList(vector<int> grouplist) {
	if (grouplist.size() == 0)
	{
		cout << "您没有加入任何群" << endl;
		return;
	}
	cout << "您有" << grouplist.size() << "个群" << endl;
	cout << "群号 群名" << endl;
	for (int i = 0; i < grouplist.size(); i++) {
		cout << grouplist[i] << " "
			<< m_allQQGroupList->findByGroupId(grouplist[i])->getGroupName() << endl;
	}
}

void applicationQQLA::showGroupMemberPage(int groupId) {
	qqGroupNodeLA* groupPtr = m_allQQGroupList->findByGroupId(groupId);
	showGroupMemberPage(groupPtr);
}

void applicationQQLA::showGroupMemberPage(qqGroupNodeLA* groupPtr) {
	system("cls");
	cout << "群成员列表" << endl;
	cout << "共有" << groupPtr->getQQGroupMemberInfoList().size() << "个成员" << endl;
	cout << "成员QQ号 成员昵称" << endl;
	for (int i = 0; i < groupPtr->getQQGroupMemberInfoList().size(); i++) {
		cout << groupPtr->getQQGroupMemberInfoList()[i].friendId << " " 
			<< groupPtr->getQQGroupMemberInfoList()[i].friendName << endl;
	}
	system("pause");
}
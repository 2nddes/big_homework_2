#include"applicationQQ.h"
#include"platform.h"
#include<iostream>


applicationQQLA::applicationQQLA() {
	m_appVersion = 1;
	m_allQQGroupList = nullptr;
	m_allQQUserList = nullptr;
	m_currentUser = nullptr;
}

applicationQQLA::applicationQQLA(platformLA* platform) {
	m_appVersion = 1;
	m_allQQGroupList = nullptr;
	m_allQQUserList = nullptr;
	m_currentUser = nullptr;
	this->m_platform = platform;
}

applicationQQLA::~applicationQQLA() {
	delete m_allQQGroupList;
	delete m_allQQUserList;
}

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
			cout << "平台用户 "
				<< curPlatformUser->getUserName() 
				<< " 未开通QQ服务,是否开通" << endl;
			cout << "1.开通" << endl;
			cout << "2.不开通" << endl;
			int i = 2;
			cin >> i;
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
		cout << "QQ登录按1,注册QQ按2,退出按3" << endl;
		int i = 0;
		cin >> i;
		if (i == 2) {
			m_currentUser = registerPage(curPlatformUser);
			continue;
		}
		else if (i == 3) {
			exit();
			return nullptr;
		}
		cout << "请输入QQ号" << endl;
		int qqNumber;
		cin >> qqNumber;
		cout << "请输入密码" << endl;
		string password;
		cin >> password;

		qqUserNodeLA* qqUser = m_allQQUserList->findByQQId(qqNumber);
		if (qqUser == nullptr) {
			cout << "QQ号不存在" << endl;
			system("pause");
			continue;
		}
		else {
			if (qqUser->getUserPasswd() == password) {
				cout << "登录成功" << endl;
				return qqUser;
			}
			else {
				cout << "密码错误" << endl;
				system("pause");
				return nullptr;
			}
		}

	}
	return m_currentUser;
}

qqUserNodeLA* applicationQQLA::registerPage(userNodeLA*& curPlatformUser) {
	cout << "QQ注册任意键(建议先登录其他已有服务再进行QQ注册) 退出1" << endl;
	int i = 0;
	cin >> i;
	if (i == 1)
		return nullptr;

	cout << "输入昵称" << endl;
	string userName;
	cin >> userName;
	cout << "输入密码" << endl;
	string password;
	cin >> password;
	cout << "确认注册按1" << endl;
	i = 0;
	cin >> i;
	if(i == 1) {
		//平台和应用的用户进行联系
		//TODO
		if(curPlatformUser == nullptr) {
			curPlatformUser = m_platform->addPlatformUser();
			curPlatformUser->setQQStatus(true);
			qqUserNodeLA* p = m_allQQUserList->addQQUser(userName, password);
			p->setPlatformId(curPlatformUser->getID());
			return p;
		}
		else {
			qqUserNodeLA* p = m_allQQUserList->addQQUser(userName, password);
			p->setPlatformId(curPlatformUser->getID());
			return p;
		}
	}
	else {
		cout << "取消注册" << endl;
		system("pause");
		return nullptr;
	}
}

void applicationQQLA::exit() {
	delete m_allQQGroupList;
	delete m_allQQUserList;
	cout << "退出QQ" << endl;
	system("pause");
}
////////////////////////////////////////////////////
void applicationQQLA::mainPage() {
	while (1) {
		system("cls");
		cout << "1.好友" << endl;
		cout << "2.群" << endl;
		cout << "3.退出" << endl;
		int i = 0;
		cin >> i;
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
		cout << "1.搜索好友" << endl;
		cout << "2.添加好友" << endl;
		cout << "3.删除好友" << endl;
		cout << "4.返回" << endl;
		int i = 0;
		cin >> i;
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
	cout<<"输入好友QQ号"<<endl;
	int qqNumber = 0;
	cin >> qqNumber;
	qqUserNodeLA* p = m_allQQUserList->findByQQId(qqNumber);
	if(p == nullptr) {
		cout<<"好友不存在"<<endl;
		system("pause");
		return;
	}
	else {
		cout<<"好友存在"<<endl;//TODO
		system("pause");
		return;
	}
}

void applicationQQLA::addFriendPage() {
	cout << "输入好友QQ号" << endl;
	int qqNumber = 0;
	cin >> qqNumber;
	qqUserNodeLA* p = m_allQQUserList->findByQQId(qqNumber);
	if(p == nullptr) {
		cout << "用户不存在" << endl;
		system("pause");
		return;
	}
	else {
		cout << p->getUserName() << endl;
		cout << "确认添加按1" << endl;
		int i = 0;
		cin >> i;
		if(i == 1) {
			m_currentUser->addQQFriendId(qqNumber);//TODO
			cout << "申请添加成功" << endl;
		}
		else {
			cout << "取消添加" << endl;
		}
		system("pause");
		return;
	}
}

void applicationQQLA::deleteFriendPage() {
	cout << "输入好友QQ号" << endl;
	int qqNumber = 0;
	cin >> qqNumber;
	for (int i = 0; i < m_currentUser->getQQFriendInfo().size(); i++) {
		if (m_currentUser->getQQFriendInfo()[i].friendId == qqNumber) {
			cout << "确认删除按1" << endl;
			int i = 0;
			cin >> i;
			if (i == 1) {
				m_currentUser->deleteQQFriendId(qqNumber);//TODO
				cout << "删除成功" << endl;
			}
			else {
				cout << "取消删除" << endl;
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
		cout << "0.选择群" << endl;
		cout << "1.搜索群" << endl;
		cout << "2.创建群" << endl;
		cout << "3.加入群" << endl;
		cout << "4.退出群" << endl;
		cout << "5.返回" << endl;
		int i = 0;
		cin >> i;
		if (i == 0) {
			cout<<"输入群号"<<endl;
			int groupId = 0;
			cin >> groupId;
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
	cout << "输入群号" << endl;
	int groupId = 0;
	cin >> groupId;
	qqGroupNodeLA* p = m_allQQGroupList->findByGroupId(groupId);
	if (p == nullptr) {
		cout << "群不存在" << endl;
		system("pause");
		return;
	}
	else {
		cout << "群存在" << endl;//TODO
		system("pause");
		return;
	}
}

void applicationQQLA::createGroupPage() {
	cout << "输入群名" << endl;
	string groupName;
	cin >> groupName;
	cout << "确认创建按1" << endl;
	int i = 0;
	cin >> i;
	if (i == 1) {
		qqGroupNodeLA* p = m_allQQGroupList->addGroup(groupName, m_currentUser->getAppUserId());
		m_currentUser->addQQGroupId(p->getGroupId());
		cout << "创建成功" << endl;
	}
	else {
		cout << "取消创建" << endl;
	}
	system("pause");
	return;

}

void applicationQQLA::joinGroupPage() {
	cout << "输入群号" << endl;
	int groupId = 0;
	cin >> groupId;
	qqGroupNodeLA* p = m_allQQGroupList->findByGroupId(groupId);
	if (p == nullptr) {
		cout << "群不存在" << endl;
		system("pause");
		return;
	}
	else {
		cout << p->getGroupName() << endl;
		cout << "确认加入按1" << endl;
		int i = 0;
		cin >> i;
		if (i == 1) {
			p->addMember(m_currentUser->getAppUserId());
			m_currentUser->addQQGroupId(p->getGroupId());
			cout << "申请加入成功" << endl;
		}
		else {
			cout << "取消加入" << endl;
		}
		system("pause");
		return;
	}
}

void applicationQQLA::quitGroupPage() {
	cout << "输入群号" << endl;
	int groupId = 0;
	cin >> groupId;
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
		if (i == 1) {
			p->removeMember(m_currentUser->getAppUserId());
			cout << "退出成功" << endl;
		}
		else {
			cout << "取消退出" << endl;
		}
		system("pause");
		return;
	}
}

void applicationQQLA::chatInGroupPage(qqGroupNodeLA* groupPtr) {
	while(1)
	{
		//showMessageList()
		//TODO:管理员功能
		//TODO:群主功能
		cout << "1.发送消息" << endl;
		cout << "2.查看群成员" << endl;
		cout << "3.退出群" << endl;
		cout << "4.返回" << endl;
		int i = 0;
		cin >> i;
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
			cout << "确认退出按1" << endl;
			int i = 0;
			cin >> i;
			if (i == 1) {
				groupPtr->removeMember(m_currentUser->getAppUserId());
				m_currentUser->deleteQQGroupId(groupPtr->getGroupId());
				cout << "退出成功" << endl;
				system("pause");
				return;
			}
			else {
				cout << "取消退出" << endl;
			}
		}
		else if (i == 4) {
			return;
		}
	}
}

void applicationQQLA::chatWithFriendPage(qqUserNodeLA* friendPtr) {
	while (1)
	{
		//showMessageList()
		cout << "1.发送消息" << endl;
		cout << "2.返回" << endl;
		int i = 0;
		cin >> i;
		if (i == 1) {
			cout << "直接回车可返回;输入消息回车发送:" << endl;
			char message[300];
			memset(message, 0, 300);
			cin.getline(message, 300);
			if (message[0] == '\0') {
				continue;
			}
			(sendMsgToFriend(friendPtr, message)) ? cout << "发送成功" << endl : cout << "发送失败" << endl;
		}
		else if (i == 2) {
			return;
		}
	}
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
	cout << "好友列表" << endl;
	for (int i = 0; i < friendlist.size(); i++) {
		cout << friendlist[i].friendName << " ";
		cout << friendlist[i].friendId << endl;
	}
	system("pause");
}

void applicationQQLA::showQQGroupList(vector<int> grouplist) {
	cout << "群列表" << endl;
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
	cout << "群成员列表" << endl;
	for (int i = 0; i < groupPtr->getQQGroupMemberIDList().size(); i++) {
		cout << groupPtr->getQQGroupMemberIDList()[i].friendId
			<< " " << groupPtr->getQQGroupMemberIDList()[i].friendName << endl;
	}
	system("pause");
}
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
		cout << "           好友" << endl;
		cout << "__________________________________" << endl;
		showQQFriendList(m_currentUser->getQQFriendInfo());

		cout << "| 01 || 选择好友                  |" << endl;
		cout << "| 02 || 添加好友                  |" << endl;
		cout << "| 03 || 删除好友                  |" << endl;
		cout << "| 04 || 查看好友请求              |" << endl;
		cout << "| 00 || 返回                      |" << endl;
		cout << "__________________________________" << endl;
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
	cout << "           好友" << endl;
	cout << "__________________________________" << endl;
	showQQFriendList(m_currentUser->getQQFriendInfo());
	if (m_currentUser->getQQFriendInfo().size() == 0) {
		system("pause");
		return;
	}
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
	while (1)
	{
		system("cls");
		cout << "         添加好友" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || 按QQ号添加                |" << endl;
		cout << "| 02 || 按昵称搜索                |" << endl;
		cout << "| 03 || 添加微信好友的qq号        |" << endl;
		cout << "| 00 || 返回                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "输入选项:";
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
			cout << "输入错误" << endl;
			system("pause");
			continue;
		}
	}
}

void applicationQQLA::deleteFriendPage() {
	system("cls");
	cout << "           删除好友" << endl;
	cout << "__________________________________" << endl;
	showQQFriendList(m_currentUser->getQQFriendInfo());
	if (m_currentUser->getQQFriendInfo().size() == 0) {
		system("pause");
		return;
	}
	cout << "输入待删除好友QQ号:";
	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	if (qqNumber == m_currentUser->getAppUserId()) {
		cout << "不能删除自己" << endl;
		system("pause");
		return;
	}
	int i = 0;
	for (i = 0; i < m_currentUser->getQQFriendInfo().size(); i++) {
		if (m_currentUser->getQQFriendInfo()[i].friendId == qqNumber) {
			system("cls");
			cout << "          用户信息" << endl;
			cout << "__________________________________" << endl;
			cout << "| QQ号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_allQQUserList->findByQQId(qqNumber)->getAppUserId() << "|" << endl;
			cout << "| 昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_allQQUserList->findByQQId(qqNumber)->getUserName() << "|" << endl;
			cout << "__________________________________" << endl;
			cout << "| 01 || 确认删除                  |" << endl;
			cout << "| 00 || 取消                      |" << endl;
			cout << "__________________________________" << endl;
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
			else if (i == 0) {
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
	while (1)
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
		cout << "__________________________________" << endl;
		cout << "|QQ号|          昵 称           |" << endl;
		cout << "__________________________________" << endl;
		for (int i = 0; i < qqNumberList.size(); i++) {
			cout << "|" << setw(4) << setfill(' ') << qqNumberList[i] << "|";
			cout << setw(26) << setfill(' ') << m_allQQUserList->findByQQId(qqNumberList[i])->getUserName() << "|" << endl;
			cout << "__________________________________" << endl;
		}
		cout << "| 01 || 同意                    |" << endl;
		cout << "| 02 || 拒绝                    |" << endl;
		cout << "| 00 || 返回                    |" << endl;
		cout << "__________________________________" << endl;
		cout << "输入选项:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "输入同意的好友QQ号:";
			int qqNumber = 0;
			cin >> qqNumber;
			refreshInput();
			if (count(qqNumberList.begin(), qqNumberList.end(), qqNumber) == 0) {
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
			for (int i = 0; i < qqNumberList.size(); i++) {
				if (qqNumberList[i] == qqNumber) {
					qqNumberList.erase(qqNumberList.begin() + i);
				}
			}

			//保存文件
			m_allQQUserList->saveQQUserListData();
			ofstream ofs(path, ios::out);
			for (auto i : qqNumberList) {
				ofs << i << " ";
			}
			ofs.close();
			cout << "好友 " << friendToAddPtr->getUserName() << " 添加成功" << endl;
			system("pause");
			continue;
		}
		else if (i == 2) {
			cout << "输入拒绝的好友QQ号:";
			int qqNumber = 0;
			cin >> qqNumber;
			refreshInput();
			if (count(qqNumberList.begin(), qqNumberList.end(), qqNumber) == 0) {
				cout << "好友申请不存在" << endl;
				system("pause");
				continue;
			}
			//删除请求
			for (int i = 0; i < qqNumberList.size(); i++) {
				if (qqNumberList[i] == qqNumber) {
					qqNumberList.erase(qqNumberList.begin() + i);
				}
			}

			//保存文件
			ofstream ofs(path, ios::out);
			for (auto i : qqNumberList) {
				ofs << i << " ";
			}
			ofs.close();
			cout << "拒绝成功" << endl;
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

void applicationQQLA::chatWithFriendPage(qqUserNodeLA* friendPtr) {
	while (1)
	{
		system("cls");
		long long len = friendPtr->getUserName().length();
		cout << setw((40 - len) / 2) << setfill(' ') << friendPtr->getUserName() << endl;
		cout << "__________________________________" << endl;
		showMsg(recvMsgFromFriend(friendPtr));
		cout << "__________________________________" << endl;
		cout << "| 01 || 发送消息                  |" << endl;
		cout << "| 00 || 返回                      |" << endl;
		cout << "__________________________________" << endl;
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

void applicationQQLA::addExternWeChatFriendPage() {
	while (1)
	{
		//将wechat号转化为qq指针
		userNodeLA* curPlatformUser = m_platform->findPlatformUser(m_currentUser->getPlatformId());
		if (curPlatformUser->isWeChatEnabled() == false) {
			cout << "未开通微信服务" << endl;
			system("pause");
			return;
		}
		applicationWeChatLA* wcApp = new applicationWeChatLA();
		wcApp->loadData();

		WeChatUserNodeLA* curWeChatUser = wcApp->findBySuperPtr(curPlatformUser);
		if (curWeChatUser == nullptr) {
			cout << "未开通微信服务" << endl;
			system("pause");
			return;
		}
		//将wechat好友转化为qq好友
		vector<userInfo> wcFriendList = curWeChatUser->getWeChatFriendInfo();
		if (wcFriendList.size() == 0) {
			cout << "微信好友列表为空" << endl;
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
			cout << "没有qq好友开通微信服务" << endl;
			system("pause");
			return;
		}
		system("cls");
		cout << "          用户信息" << endl;
		cout << "__________________________________" << endl;
		for (int i = 0; i < wechatFriendList.size(); i++) {
			cout << "|微号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << wechatFriendList[i].wechatfriendId << "|" << endl;
			cout << "|QQ号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << wechatFriendList[i].friendqqPtr->getAppUserId() << "|" << endl;
			cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << wechatFriendList[i].friendqqPtr->getUserName() << "|" << endl;
			cout << "__________________________________" << endl;
		}
		cout << "| 01 || 好友申请                  |" << endl;
		cout << "|其他|| 返回                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "输入选项:";
		int i = 0;
		cin >> i;
		refreshInput();

		if (i == 1) {
			cout << "输入要添加的qq号:";
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
				cout << "用户不存在" << endl;
				system("pause");
				continue;
			}
			if (m_currentUser->isFriend(friendToAddPtr)) {
				cout << "已经是好友" << endl;
				system("pause");
				continue;
			}
			applyFriend(m_currentUser, friendToAddPtr);
			cout << "好友申请成功" << endl;
			system("pause");
			continue;
		}
		else {
			cout << "取消添加" << endl;
			system("pause");
			continue;
		}
	}

}

void applicationQQLA::addBySearchFriendNamePage() {
	while (1)
	{
		system("cls");
		cout << "		 搜索好友名称" << endl;
		cout << "__________________________________" << endl;
		cout << "输入要搜索的昵称,直接回车返回:" << endl;
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
			cout << "用户不存在" << endl;
			system("pause");
			return;
		}
		system("cls");
		cout << "          用户信息" << endl;
		cout << "__________________________________" << endl;
		for (int i = 0; i < friendsToAdd.size(); i++) {
			cout << "|QQ号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendsToAdd[i].friendId << "|" << endl;
			cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendsToAdd[i].friendName << "|" << endl;
			cout << "__________________________________" << endl;
		}
		cout << "| 01 || 好友申请                  |" << endl;
		cout << "| 00 || 取消                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "输入选项:";

		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			cout << "输入要添加的qq号:" << endl;
			int id = -1;
			cin >> id;
			refreshInput();
			if (id == m_currentUser->getAppUserId())
			{
				cout << "不能添加自己为好友" << endl;
				system("pause");
				continue;
			}

			qqUserNodeLA* friendToAddPtr = m_allQQUserList->findByQQId(id);
			if (friendToAddPtr == nullptr) {
				cout << "用户不存在" << endl;
				system("pause");
				continue;
			}
			if (m_currentUser->isFriend(friendToAddPtr)) {
				chatWithFriendPage(friendToAddPtr);
				system("pause");
				return;
			}
			system("cls");
			cout << "          用户信息" << endl;
			cout << "__________________________________" << endl;
			cout << "|微号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendToAddPtr->getAppUserId() << "|" << endl;
			cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendToAddPtr->getUserName() << "|" << endl;
			cout << "__________________________________" << endl;
			cout << "| 01 || 好友申请                  |" << endl;
			cout << "|其他|| 取消添加                  |" << endl;
			cout << "__________________________________" << endl;
			cout << "输入选项:";
			int i = 0;
			cin >> i;
			refreshInput();
			if (i == 1) {
				applyFriend(m_currentUser, friendToAddPtr);
				cout << "好友申请成功" << endl;
				system("pause");
				continue;
			}
			else {
				cout << "取消添加" << endl;
				system("pause");
				continue;
			}
		}
		else {
			cout << "取消添加" << endl;
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
						cout << "         推荐好友" << endl;
						cout << "__________________________________" << endl;
						cout << "|QQ号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getAppUserId() << "|" << endl;
						cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getUserName() << "|" << endl;
						cout << "__________________________________" << endl;
					}
				}			
				else {
					cout << "暂无推荐好友" << endl;
				}
			}

		}
		

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
			cout << "用户不存在" << endl;
			system("pause");
			return;
		}
		if (m_currentUser->isFriend(friendToAddPtr)) {
			cout << "已经是好友" << endl;
			system("pause");
			return;
		}
		system("cls");
		cout << "          用户信息" << endl;
		cout << "__________________________________" << endl;
		cout << "|QQ号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendToAddPtr->getAppUserId() << "|" << endl;
		cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendToAddPtr->getUserName() << "|" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || 好友申请                  |" << endl;
		cout << "|其他|| 取消                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "输入选项:";
		int i = 0;
		cin >> i;
		refreshInput();
		if (i == 1) {
			applyFriend(m_currentUser, friendToAddPtr);
			cout << "好友申请成功" << endl;
			system("pause");
			continue;
		}
		else {
			cout << "取消添加" << endl;
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

void applicationQQLA::inviteFriendInPage(qqGroupNodeLA* groupPtr) {
	if (!groupPtr->isAllowInvite()) {
		cout << "该群当前不允许邀请进入" << endl;
		system("pause");
		return;
	}
	vector<userInfo> memberList = m_currentUser->getQQFriendInfo();
	if (memberList.size() == 0) {
		cout << "没有好友可邀请" << endl;
		system("pause");
		return;
	}
	system("cls");
	cout << "         邀请好友进群" << endl;
	cout << "__________________________________" << endl;
	showQQFriendList(memberList);

	cout << "输入要邀请的好友QQ号:";
	int qqNumber = 0;
	cin >> qqNumber;
	refreshInput();
	if (groupPtr->isMember(qqNumber)) {
		cout << "该用户已经在群里" << endl;
		system("pause");
		return;
	}
	cout << "按1确认邀请:";
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		groupPtr->addMember(qqNumber);
		//添加群号
		qqUserNodeLA* p = m_allQQUserList->findByQQId(qqNumber);
		p->addQQGroupId(groupPtr->getGroupId());
		//保存到文件
		m_allQQGroupList->saveGroupListData();
		m_allQQUserList->saveQQUserListData();
		cout << "邀请成功" << endl;
		system("pause");
		return;
	}
	else {
		cout << "取消邀请" << endl;
		system("pause");
		return;
	}
}

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

vector<QMsg> applicationQQLA::recvMsgFromFriend(qqUserNodeLA* friendPtr)
{
	string path = "QQ\\" + to_string(m_currentUser->getAppUserId()) + "\\chatrecord\\" + to_string(friendPtr->getAppUserId()) + ".dat";
	//判断文件是否存在,不存在则创建
	if (_access(path.c_str(), 0) == -1) {
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
//TODO:color
void applicationQQLA::showQQFriendList(vector<userInfo> friendlist)const {
	if (friendlist.size() == 0)
	{
		cout << "        您没有任何好友" << endl;
		cout << "__________________________________" << endl;
		return;
	}
	cout << "您有" << friendlist.size() << "个好友" << endl;
	cout << "__________________________________" << endl;

	for (int i = 0; i < friendlist.size(); i++) {
		cout << "|QQ号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendlist[i].friendId << "|" << endl;
		cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendlist[i].friendName << "|" << endl;
		cout << "__________________________________" << endl;
	}
	cout << resetiosflags(ios::left);

	return;
}


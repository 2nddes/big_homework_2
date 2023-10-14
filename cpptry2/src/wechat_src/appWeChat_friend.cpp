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
		cout << "           好友" << endl;
		cout << "__________________________________" << endl;
		showWeChatFriendList(m_currentUser->getWeChatFriendInfo());

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

void applicationWeChatLA::selectFriendPage() {
	system("cls");
	cout << "           好友" << endl;
	cout << "__________________________________" << endl;
	showWeChatFriendList(m_currentUser->getWeChatFriendInfo());
	if (m_currentUser->getWeChatFriendInfo().size() == 0) {
		system("pause");
		return;
	}
	cout << "输入好友WeChat号:";
	int WeChatNumber = 0;
	cin >> WeChatNumber;
	refreshInput();
	if (m_currentUser->isFriend(WeChatNumber)) {
		chatWithFriendPage(m_allWeChatUserList->findByWeChatId(WeChatNumber));
	}
	else {
		cout << "未找到好友" << endl;
		system("pause");
		return;
	}
}

void applicationWeChatLA::sendMsgPage(WeChatUserNodeLA* friendPtr)
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

void applicationWeChatLA::addFriendPage() {
	while (1)
	{
		system("cls");
		cout << "         添加好友" << endl;
		cout << "__________________________________" << endl;
		cout << "| 01 || 按微信号添加              |" << endl;
		cout << "| 02 || 按昵称搜索                |" << endl;
		cout << "| 03 || 添加QQ好友的微信号        |" << endl;
		cout << "| 00 || 返回                      |" << endl;
		cout << "__________________________________" << endl;
		cout << "输入选项:";
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
			cout << "输入错误" << endl;
			system("pause");
			continue;
		}
	}
}

void applicationWeChatLA::addExternQQFriendPage() {
	while (1)
	{
		//将wechat号转化为qq指针
		userNodeLA* curPlatformUser = m_platform->findPlatformUser(m_currentUser->getPlatformId());
		if (curPlatformUser->isQQEnabled() == false) {
			cout << "未开通QQ服务" << endl;
			system("pause");
			return;
		}
		applicationQQLA* qqApp = new applicationQQLA();
		qqApp->loadData();

		qqUserNodeLA* curQQUser = qqApp->findBySuperPtr(curPlatformUser);
		if (curQQUser == nullptr) {
			cout << "未开通QQ服务" << endl;
			system("pause");
			return;
		}
		//将qq好友转化为wechat好友
		vector<userInfo> qqFriendList = curQQUser->getQQFriendInfo();
		if (qqFriendList.size() == 0) {
			cout << "QQ好友列表为空" << endl;
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
			cout << "没有qq好友开通微信服务" << endl;
			system("pause");
			return;
		}
		system("cls");
		cout << "          用户信息" << endl;
		cout << "__________________________________" << endl;
		for (int i = 0; i < wechatFriendList.size(); i++) {
			cout << "|QQ号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << wechatFriendList[i].qqfriendId << "|" << endl;
			cout << "|微号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << wechatFriendList[i].friendWeChatPtr->getAppUserId() << "|" << endl;
			cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << wechatFriendList[i].friendWeChatPtr->getUserName() << "|" << endl;
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
			cout << "输入要添加的微信号:";
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

void applicationWeChatLA::addBySearchFriendNamePage()
{
	while (1) 
	{
		cout << "输入要搜索的昵称:" << endl;
		string name;
		cin >> name;
		refreshInput();
		vector<userInfo> friendsToAdd = m_allWeChatUserList->searchByName(name);
		if (friendsToAdd.size() == 0) {
			cout << "用户不存在" << endl;
			system("pause");
			return;
		}
		system("cls");
		cout << "          用户信息" << endl;
		cout << "__________________________________" << endl;
		for (int i = 0; i < friendsToAdd.size(); i++) {
			cout << "|微号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendsToAdd[i].friendId << "|" << endl;
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
			cout << "输入要添加的WeChat号:" << endl;
			int id = -1;
			cin >> id;
			refreshInput();
			if (id == m_currentUser->getAppUserId())
			{
				cout << "你不能添加自己为好友" << endl;
				system("pause");
				continue;
			}

			WeChatUserNodeLA* friendToAddPtr = m_allWeChatUserList->findByWeChatId(id);
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
						cout << "		 推荐好友" << endl;
						cout << "__________________________________" << endl;
						cout << "|微号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getAppUserId() << "|" << endl;
						cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << p->getUserName() << "|" << endl;
						cout << "__________________________________" << endl;
						cout << resetiosflags(ios::left);
					}
				}
			}
		}

		cout << "输入要添加的WeChat号:" << endl;
		int id;
		cin >> id;
		refreshInput();
		if (id == m_currentUser->getAppUserId())
		{
			cout << "你不能添加自己为好友" << endl;
			system("pause");
			return;
		}

		WeChatUserNodeLA* friendToAddPtr = m_allWeChatUserList->findByWeChatId(id);
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
		cout << "|微号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendToAddPtr->getAppUserId() << "|" << endl;
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

void applicationWeChatLA::deleteFriendPage() {
	system("cls");
	cout << "           删除好友" << endl;
	cout << "__________________________________" << endl;
	showWeChatFriendList(m_currentUser->getWeChatFriendInfo());
	if (m_currentUser->getWeChatFriendInfo().size() == 0) {
		system("pause");
		return;
	}
	cout << "输入待删除好友WeChat号:";
	int WeChatNumber = 0;
	cin >> WeChatNumber;
	refreshInput();
	if (WeChatNumber == m_currentUser->getAppUserId()) {
		cout << "不能删除自己" << endl;
		system("pause");
		return;
	}
	int i = 0;
	for (i = 0; i < m_currentUser->getWeChatFriendInfo().size(); i++) {
		if (m_currentUser->getWeChatFriendInfo()[i].friendId == WeChatNumber) {
			system("cls");
			cout << "          用户信息" << endl;
			cout << "__________________________________" << endl;
			cout << "|微号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_allWeChatUserList->findByWeChatId(WeChatNumber)->getAppUserId() << "|" << endl;
			cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << m_allWeChatUserList->findByWeChatId(WeChatNumber)->getUserName() << "|" << endl;
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
				m_allWeChatUserList->findByWeChatId(WeChatNumber)->deleteWeChatFriendId(m_currentUser->getAppUserId());
				m_currentUser->deleteWeChatFriendId(WeChatNumber);
				m_allWeChatUserList->saveWeChatUserListData();
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
	if (i == m_currentUser->getWeChatFriendInfo().size()) {
		cout << "不是好友" << endl;
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
			cout << "打开文件失败" << endl;
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
			cout << "目前没有好友请求" << endl;
			system("pause");
			return;
		}

		system("cls");
		cout << "         好友请求列表" << endl;
		cout << "__________________________________" << endl;
		cout << "|微号|          昵 称           |" << endl;
		cout << "__________________________________" << endl;
		for (int i = 0; i < WeChatNumberList.size(); i++) {
			cout << "|" << setw(4) << setfill(' ') << WeChatNumberList[i] << "|";
			cout << setw(26) << setfill(' ') << m_allWeChatUserList->findByWeChatId(WeChatNumberList[i])->getUserName() << "|" << endl;
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
			cout << "输入同意的好友WeChat号:";
			int WeChatNumber = 0;
			cin >> WeChatNumber;
			refreshInput();
			if (count(WeChatNumberList.begin(), WeChatNumberList.end(), WeChatNumber) == 0) {
				cout << "用户不存在" << endl;
				system("pause");
				continue;
			}
			WeChatUserNodeLA* friendToAddPtr = m_allWeChatUserList->findByWeChatId(WeChatNumber);
			//互相添加好友
			userInfo info;
			info.friendId = friendToAddPtr->getAppUserId();
			info.friendName = friendToAddPtr->getUserName();
			m_currentUser->addWeChatFriendInfo(info);
			info.friendId = m_currentUser->getAppUserId();
			info.friendName = m_currentUser->getUserName();
			friendToAddPtr->addWeChatFriendInfo(info);
			//删除请求
			for (int i = 0; i < WeChatNumberList.size(); i++) {
				if (WeChatNumberList[i] == WeChatNumber) {
					WeChatNumberList.erase(WeChatNumberList.begin() + i);
				}
			}

			//保存文件
			m_allWeChatUserList->saveWeChatUserListData();
			ofstream ofs(path, ios::out);
			for (auto i : WeChatNumberList) {
				ofs << i << " ";
			}
			ofs.close();
			cout << "好友 " << friendToAddPtr->getUserName() << " 添加成功" << endl;
			system("pause");
			continue;
		}
		else if (i == 2) {
			cout << "输入拒绝的好友WeChat号:";
			int WeChatNumber = 0;
			cin >> WeChatNumber;
			refreshInput();
			if (count(WeChatNumberList.begin(), WeChatNumberList.end(), WeChatNumber) == 0) {
				cout << "好友申请不存在" << endl;
				system("pause");
				continue;
			}
			//删除请求
			for (int i = 0; i < WeChatNumberList.size(); i++) {
				if (WeChatNumberList[i] == WeChatNumber) {
					WeChatNumberList.erase(WeChatNumberList.begin() + i);
				}
			}

			//保存文件
			ofstream ofs(path, ios::out);
			for (auto i : WeChatNumberList) {
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

void applicationWeChatLA::chatWithFriendPage(WeChatUserNodeLA* friendPtr) {
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

void applicationWeChatLA::applyFriend(WeChatUserNodeLA* user, WeChatUserNodeLA* friendToAdd) {
	string path = "WeChat\\" + to_string(friendToAdd->getAppUserId()) + "\\friendrequest.dat";
	//在好友的请求列表中添加请求
	ofstream ofs(path, ios::app);
	if (!ofs.is_open()) {
		cout << "打开文件失败" << endl;
		return;
	}
	ofs << user->getAppUserId() << endl;
	ofs.close();

}

void applicationWeChatLA::inviteFriendInPage(WeChatGroupNodeLA* groupPtr) {
	if (!groupPtr->isAllowInvite()) {
		cout << "该群当前不允许邀请进入" << endl;
		system("pause");
		return;
	}
	vector<userInfo> memberList = m_currentUser->getWeChatFriendInfo();
	if (memberList.size() == 0) {
		cout << "没有好友可邀请" << endl;
		system("pause");
		return;
	}
	system("cls");
	cout << "         邀请好友进群" << endl;
	cout << "__________________________________" << endl;
	showWeChatFriendList(memberList);

	cout << "输入要邀请的好友WeChat号:";
	int WeChatNumber = 0;
	cin >> WeChatNumber;
	refreshInput();
	if (groupPtr->isMember(WeChatNumber)) {
		cout << "该用户已经在群里" << endl;
		system("pause");
		return;
	}
	cout << "按1确认邀请:";
	int i = 0;
	cin >> i;
	refreshInput();
	if (i == 1) {
		groupPtr->addMember(WeChatNumber);
		//添加群号
		WeChatUserNodeLA* p = m_allWeChatUserList->findByWeChatId(WeChatNumber);
		p->addWeChatGroupId(groupPtr->getGroupId());
		//保存到文件
		m_allWeChatGroupList->saveGroupListData();
		m_allWeChatUserList->saveWeChatUserListData();
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

bool applicationWeChatLA::sendMsgToFriend(WeChatUserNodeLA* friendPtr, const char* msg) {
	string path = "WeChat\\" + to_string(friendPtr->getAppUserId()) + "\\chatrecord\\" + to_string(m_currentUser->getAppUserId()) + ".dat";
	//获取时间
	string time = getTime();
	//打开好友的chatrecord文件写入发送者WeChat号,发送者昵称,发送时间,消息内容
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

	//打开自己的chatrecord文件写入发送者WeChat号,发送者昵称,发送时间,消息内容
	path = "WeChat\\" + to_string(m_currentUser->getAppUserId()) + "\\chatrecord\\" + to_string(friendPtr->getAppUserId()) + ".dat";
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

vector<WMsg> applicationWeChatLA::recvMsgFromFriend(WeChatUserNodeLA* friendPtr)
{
	string path = "WeChat\\" + to_string(m_currentUser->getAppUserId()) + "\\chatrecord\\" + to_string(friendPtr->getAppUserId()) + ".dat";
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
	vector<WMsg> msgList;
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
//TODO:color
void applicationWeChatLA::showWeChatFriendList(vector<userInfo> friendlist) {
	if (friendlist.size() == 0)
	{
		cout << "        您没有任何好友" << endl;
		cout << "__________________________________" << endl;
		return;
	}
	cout << "您有" << friendlist.size() << "个好友" << endl;
	cout << "__________________________________" << endl;

	for (int i = 0; i < friendlist.size(); i++) {
		cout << "|微号|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendlist[i].friendId << "|" << endl;
		cout << "|昵称|| " << setw(26) << setfill(' ') << setiosflags(ios::left) << friendlist[i].friendName << "|" << endl;
		cout << "__________________________________" << endl;
	}
	cout << resetiosflags(ios::left);

	return;
}
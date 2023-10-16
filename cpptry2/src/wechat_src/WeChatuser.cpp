#include<fstream>
#include"WeChatuser.h"
#include"/project/C++Project/cpptry2/cpptry2/src/utils.h"

WeChatUserListLA::WeChatUserListLA() {
	m_sentinel = new WeChatUserNodeLA(0, "sentinel", "sentinel", nullptr);

	ifstream ifs("WeChat\\WeChatusers.dat", ios::in);
	if (!ifs) {
		m_WeChatUserCount = 0;
		return;
	}
	ifs >> m_WeChatUserCount;
	int platformId, WeChatId, WeChatFriendIdSize, WeChatGroupIdSize, friendId;
	string WeChatName, WeChatPassword, friendName;
	while (ifs >> platformId >> WeChatId >> WeChatName >> WeChatPassword >> WeChatFriendIdSize) {
		WeChatUserNodeLA* WeChatUserToAdd = new WeChatUserNodeLA(WeChatId, WeChatName, WeChatPassword, m_sentinel->getNext());

		WeChatUserToAdd->setPlatformId(platformId);
		WeChatUserToAdd->setAppUserId(WeChatId);

		for (int i = 0; i < WeChatFriendIdSize; i++) {
			ifs >> friendId;
			ifs >> friendName;
			userInfo friendInfo;
			friendInfo.friendId = friendId;
			friendInfo.friendName = friendName;
			WeChatUserToAdd->addWeChatFriendInfo(friendInfo);
		}
		ifs >> WeChatGroupIdSize;
		for (int i = 0; i < WeChatGroupIdSize; i++) {
			int groupId;
			ifs >> groupId;
			WeChatUserToAdd->addWeChatGroupId(groupId);
		}
		m_sentinel->setNext(WeChatUserToAdd);
	}
	ifs.close();
}

void WeChatUserListLA::saveWeChatUserListData()const {
	ofstream ofs;
	ofs.open("WeChat\\WeChatusers.dat", ios::out);//清除原有数据
	WeChatUserNodeLA* p = m_sentinel->getNext();
	ofs << m_WeChatUserCount << " ";
	while (p != nullptr) {
		ofs << p->getPlatformId() << " "
			<< p->getAppUserId() << " "
			<< p->getUserName() << " "
			<< p->getUserPasswd() << " "
			//用户好友的ID大小
			<< p->getWeChatFriendInfo().size() << " ";
		//用户好友的ID和好友备注
		for (int i = 0; i < p->getWeChatFriendInfo().size(); i++) {
			ofs << p->getWeChatFriendInfo()[i].friendId << " ";
			ofs << p->getWeChatFriendInfo()[i].friendName << " ";
		}
		ofs << p->getWeChatGroupId().size() << " ";
		//用户所在群的ID
		for (int i = 0; i < p->getWeChatGroupId().size(); i++) {
			ofs << p->getWeChatGroupId()[i] << " ";
		}
		p = p->getNext();
	}
	ofs.close();
}

int WeChatUserListLA::size() const {
	return m_WeChatUserCount;
}

WeChatUserListLA::~WeChatUserListLA() {
	WeChatUserNodeLA* p = m_sentinel->getNext();
	while (p != nullptr) {
		WeChatUserNodeLA* q = p->getNext();
		delete p;
		p = q;
	}
	delete m_sentinel;
}

WeChatUserNodeLA* WeChatUserListLA::findByWeChatId(int id)const {
	WeChatUserNodeLA* p = m_sentinel->getNext();
	while (p != nullptr) {
		if (p->getAppUserId() == id) {
			return p;
		}
		p = p->getNext();
	}
	return nullptr;
}

WeChatUserNodeLA* WeChatUserListLA::findBySuperId(int id)const {
	WeChatUserNodeLA* p = m_sentinel->getNext();
	while (p != nullptr) {
		if (p->getPlatformId() == id) {
			return p;
		}
		p = p->getNext();
	}
	return nullptr;
}

WeChatUserNodeLA* WeChatUserListLA::addWeChatUser(string name, string password) {
	WeChatUserNodeLA* WeChatUserToAdd = new WeChatUserNodeLA(++m_WeChatUserCount, name, password, m_sentinel->getNext());
	m_sentinel->setNext(WeChatUserToAdd);
	return WeChatUserToAdd;
}

void WeChatUserListLA::deleteWeChatUser(WeChatUserNodeLA* WeChatUserToDelete) {
	WeChatUserNodeLA* p = m_sentinel;
	while (p->getNext() != WeChatUserToDelete) {
		p = p->getNext();
	}
	p->setNext(WeChatUserToDelete->getNext());
	delete WeChatUserToDelete;
	m_WeChatUserCount--;
}

void WeChatUserListLA::deleteWeChatUserByWeChatId(int id) {
	WeChatUserNodeLA* p = m_sentinel;
	while (p->getNext() != nullptr) {
		if (p->getNext()->getAppUserId() == id) {
			WeChatUserNodeLA* q = p->getNext();
			p->setNext(q->getNext());
			delete q;
			m_WeChatUserCount--;
			return;
		}
		p = p->getNext();
	}
}

WeChatUserNodeLA* WeChatUserListLA::findBySuperPointer(userNodeLA* userToFind)const {
	WeChatUserNodeLA* p = m_sentinel->getNext();
	while (p != nullptr) {
		if (p->getPlatformId() == userToFind->getPlatformId()) {
			return p;
		}
		p = p->getNext();
	}
	return nullptr;
}

vector<userInfo> WeChatUserListLA::searchByName(string name) const {
	vector<userInfo> UserToFind;
	WeChatUserNodeLA* p = m_sentinel->getNext();
	while ((p != nullptr) && (UserToFind.size() <= 10)) {
		//模糊搜索
		if (p->getUserName().find(name) != string::npos) {
			userInfo user;
			user.friendId = p->getAppUserId();
			user.friendName = p->getUserName();
			UserToFind.push_back(user);
		}
		p = p->getNext();
	}
	return UserToFind;
}

////////////////////////////////////////////////////
WeChatUserNodeLA::WeChatUserNodeLA() {
	m_WeChatId = 0;
	m_WeChatName = "";
	m_WeChatPassword = "";
	m_next = nullptr;
	m_WeChatFriendId.clear();
	m_WeChatGroupId.clear();
}

WeChatUserNodeLA::WeChatUserNodeLA(int WeChatid, string name, string password, WeChatUserNodeLA* next) {
	m_WeChatId = WeChatid;
	m_WeChatName = name;
	m_WeChatPassword = password;
	m_next = next;
	m_WeChatFriendId.clear();
	m_WeChatGroupId.clear();
}

WeChatUserNodeLA::~WeChatUserNodeLA() {
	m_WeChatFriendId.clear();
	m_WeChatGroupId.clear();
}

bool WeChatUserNodeLA::isFriend(int friendId) const {
	for (int i = 0; i < m_WeChatFriendId.size(); i++) {
		if (m_WeChatFriendId[i].friendId == friendId) {
			return true;
		}
	}
	return false;
}

bool WeChatUserNodeLA::isFriend(WeChatUserNodeLA* friendPtr) const {
	if (friendPtr == nullptr) return false;
	for (size_t i = 0; i < m_WeChatFriendId.size(); i++) {
		if (m_WeChatFriendId[i].friendId == friendPtr->getAppUserId()) {
			return true;
		}
	}
	return false;
}

bool WeChatUserNodeLA::isAddedGroup(int groupId) const
{
	for (int i = 0; i < m_WeChatGroupId.size(); i++) {
		if (m_WeChatGroupId[i] == groupId) {
			return true;
		}
	}
	return false;
}

void WeChatUserNodeLA::addWeChatFriendInfo(userInfo friendInfo) {
	m_WeChatFriendId.push_back(friendInfo);
}

void WeChatUserNodeLA::addWeChatGroupId(int id) {
	m_WeChatGroupId.push_back(id);
}

void WeChatUserNodeLA::deleteWeChatFriendId(int id) {
	for (int i = 0; i < m_WeChatFriendId.size(); i++) {
		if (m_WeChatFriendId[i].friendId == id) {
			m_WeChatFriendId.erase(m_WeChatFriendId.begin() + i);
			i--;
		}
	}
}

void WeChatUserNodeLA::deleteWeChatGroupId(int id) {
	for (int i = 0; i < m_WeChatGroupId.size(); i++) {
		if (m_WeChatGroupId[i] == id) {
			m_WeChatGroupId.erase(m_WeChatGroupId.begin() + i);
			i--;
		}
	}
}

void WeChatUserNodeLA::setPlatformId(int id) {
	m_platformId = id;
}

void WeChatUserNodeLA::setAppUserId(int id) {
	m_WeChatId = id;
}

void WeChatUserNodeLA::setUserName(string name) {
	m_WeChatName = name;
}

void WeChatUserNodeLA::setUserPasswd(string password) {
	m_WeChatPassword = password;
}

void WeChatUserNodeLA::setNext(WeChatUserNodeLA* next) {
	m_next = next;
}

int WeChatUserNodeLA::getAppUserId()const {
	return m_WeChatId;
}

string WeChatUserNodeLA::getUserName()const {
	return m_WeChatName;
}

string WeChatUserNodeLA::getUserPasswd()const {
	return m_WeChatPassword;
}

vector<userInfo> WeChatUserNodeLA::getWeChatFriendInfo()const {
	return m_WeChatFriendId;
}

vector<int> WeChatUserNodeLA::getWeChatGroupId()const {
	return m_WeChatGroupId;
}

WeChatUserNodeLA* WeChatUserNodeLA::getNext()const {
	if (this == nullptr) {
		return nullptr;
	}
	return m_next;
}

int WeChatUserNodeLA::getPlatformId()const {
	return m_platformId;
}

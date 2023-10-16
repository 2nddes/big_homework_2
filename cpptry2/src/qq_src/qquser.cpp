#include<fstream>
#include"qquser.h"
#include"/project/C++Project/cpptry2/cpptry2/src/utils.h"

qqUserListLA::qqUserListLA() {
	m_sentinel = new qqUserNodeLA(0, "sentinel", "sentinel", nullptr);

	ifstream ifs("QQ\\qqusers.dat", ios::in);
	if (!ifs) {
		m_qqUserCount = 0;
		return;
	}
	ifs >> m_qqUserCount;
	int platformId, qqId, qqFriendIdSize, qqGroupIdSize, friendId;
	string qqName, qqPassword, friendName;
	while (ifs >> platformId >> qqId >> qqName >> qqPassword >> qqFriendIdSize) {
		qqUserNodeLA* qqUserToAdd = new qqUserNodeLA(qqId, qqName, qqPassword, m_sentinel->getNext());
		
		qqUserToAdd->setPlatformId(platformId);
		qqUserToAdd->setAppUserId(qqId);
		
		for (int i = 0; i < qqFriendIdSize; i++) {
				ifs >> friendId;
				ifs >> friendName;
				userInfo friendInfo;
				friendInfo.friendId = friendId;
				friendInfo.friendName = friendName;
				qqUserToAdd->addQQFriendInfo(friendInfo);
			}
		ifs >> qqGroupIdSize;
		for (int i = 0; i < qqGroupIdSize; i++) {
			int groupId;
			ifs >> groupId;
			qqUserToAdd->addQQGroupId(groupId);
		}
		m_sentinel->setNext(qqUserToAdd);
	}
	ifs.close();
}

void qqUserListLA::saveQQUserListData()const {
	ofstream ofs;
	ofs.open("QQ\\qqusers.dat", ios::out);//清除原有数据
	qqUserNodeLA* p = m_sentinel->getNext();
	ofs << m_qqUserCount << " ";
	while (p != nullptr) {
		ofs << p->getPlatformId() << " "
			<< p->getAppUserId() << " "
			<< p->getUserName() << " "
			<< p->getUserPasswd()<< " "
			//用户好友的ID大小
			<< p->getQQFriendInfo().size() << " ";
		//用户好友的ID和好友备注
		for (int i = 0; i < p->getQQFriendInfo().size(); i++) {
			ofs << p->getQQFriendInfo()[i].friendId << " ";
			ofs << p->getQQFriendInfo()[i].friendName << " ";
		}
		ofs << p->getQQGroupId().size() << " ";
		//用户所在群的ID
		for (int i = 0; i < p->getQQGroupId().size(); i++) {
			ofs << p->getQQGroupId()[i] << " ";
		}
		p = p->getNext();
	}
	ofs.close();
}

vector<userInfo> qqUserListLA::searchByName(string name) const {
	vector<userInfo> result;
	qqUserNodeLA* p = m_sentinel->getNext();
	while ((p != nullptr) && (result.size() <= 10)) {
		if (p->getUserName().find(name) != string::npos) {
			userInfo info;
			info.friendId = p->getAppUserId();
			info.friendName = p->getUserName();
			result.push_back(info);
		}
		p = p->getNext();
	}
	return result;
}

int qqUserListLA::size() const {
	return m_qqUserCount;
}

qqUserListLA::~qqUserListLA() {
	qqUserNodeLA* p = m_sentinel->getNext();
	while (p != nullptr) {
		qqUserNodeLA* q = p->getNext();
		delete p;
		p = q;
	}
	delete m_sentinel;
}

qqUserNodeLA* qqUserListLA::findByQQId(int id)const {
	qqUserNodeLA* p = m_sentinel->getNext();
	while (p != nullptr) {
		if (p->getAppUserId() == id) {
			return p;
		}
		p = p->getNext();
	}
	return nullptr;
}

qqUserNodeLA* qqUserListLA::findBySuperId(int id)const {
	qqUserNodeLA* p = m_sentinel->getNext();
	while (p != nullptr) {
		if (p->getPlatformId() == id) {
			return p;
		}
		p = p->getNext();
	}
	return nullptr;
}

qqUserNodeLA* qqUserListLA::addQQUser(string name, string password) {
	qqUserNodeLA* qqUserToAdd = new qqUserNodeLA(++m_qqUserCount, name, password, m_sentinel->getNext());
	m_sentinel->setNext(qqUserToAdd);
	return qqUserToAdd;
}

void qqUserListLA::deleteQQUser(qqUserNodeLA* qqUserToDelete) {
	qqUserNodeLA* p = m_sentinel;
	while (p->getNext() != qqUserToDelete) {
		p = p->getNext();
	}
	p->setNext(qqUserToDelete->getNext());
	delete qqUserToDelete;
	m_qqUserCount--;
}

void qqUserListLA::deleteQQUserByQQId(int id) {
	qqUserNodeLA* p = m_sentinel;
	while (p->getNext() != nullptr) {
		if (p->getNext()->getAppUserId() == id) {
			qqUserNodeLA* q = p->getNext();
			p->setNext(q->getNext());
			delete q;
			m_qqUserCount--;
			return;
		}
		p = p->getNext();
	}
}

qqUserNodeLA* qqUserListLA::findBySuperPointer(userNodeLA* userToFind)const {
	qqUserNodeLA* p = m_sentinel->getNext();
	while (p != nullptr) {
		if (p->getPlatformId() == userToFind->getPlatformId()) {
			return p;
		}
		p = p->getNext();
	}
	return nullptr;
}

////////////////////////////////////////////////////
qqUserNodeLA::qqUserNodeLA() {
	m_qqId = 0;
	m_qqName = "";
	m_qqPassword = "";
	m_next = nullptr;
	m_qqFriendId.clear();
	m_qqGroupId.clear();
}

qqUserNodeLA::qqUserNodeLA(int QQid, string name, string password, qqUserNodeLA* next) {
	m_qqId = QQid;
	m_qqName = name;
	m_qqPassword = password;
	m_next = next;
	m_qqFriendId.clear();
	m_qqGroupId.clear();
}

qqUserNodeLA::~qqUserNodeLA() {
	m_qqFriendId.clear();
	m_qqGroupId.clear();
}

bool qqUserNodeLA::isFriend(int friendId) const{
	for (int i = 0; i < m_qqFriendId.size(); i++) {
		if (m_qqFriendId[i].friendId == friendId) {
			return true;
		}
	}
	return false;
}

bool qqUserNodeLA::isFriend(qqUserNodeLA* friendPtr) const{
	for (size_t i = 0; i < m_qqFriendId.size(); i++) {
		if (m_qqFriendId[i].friendId == friendPtr->getAppUserId()) {
			return true;
		}
	}
	return false;
}

bool qqUserNodeLA::isAddedGroup(int groupId) const
{
	for (int i = 0; i < m_qqGroupId.size(); i++) {
		if (m_qqGroupId[i] == groupId) {
			return true;
		}
	}
	return false;
}

void qqUserNodeLA::addQQFriendInfo(userInfo friendInfo) {
	m_qqFriendId.push_back(friendInfo);
}

void qqUserNodeLA::addQQGroupId(int id) {
	m_qqGroupId.push_back(id);
}

void qqUserNodeLA::deleteQQFriendId(int id) {
	for (int i = 0; i < m_qqFriendId.size(); i++) {
		if (m_qqFriendId[i].friendId == id) {
			m_qqFriendId.erase(m_qqFriendId.begin() + i);
			i--;
		}
	}
}

void qqUserNodeLA::deleteQQGroupId(int id) {
	for (int i = 0; i < m_qqGroupId.size(); i++) {
		if (m_qqGroupId[i] == id) {
			m_qqGroupId.erase(m_qqGroupId.begin() + i);
			i--;
		}
	}
}

void qqUserNodeLA::setPlatformId(int id) {
	m_platformId = id;
}

void qqUserNodeLA::setAppUserId(int id) {
	m_qqId = id;
}

void qqUserNodeLA::setUserName(string name) {
	m_qqName = name;
}

void qqUserNodeLA::setUserPasswd(string password) {
	m_qqPassword = password;
}

void qqUserNodeLA::setNext(qqUserNodeLA* next) {
	m_next = next;
}

int qqUserNodeLA::getAppUserId()const {
	return m_qqId;
}

string qqUserNodeLA::getUserName()const {
	return m_qqName;
}

string qqUserNodeLA::getUserPasswd()const {
	return m_qqPassword;
}

vector<userInfo> qqUserNodeLA::getQQFriendInfo()const {
	return m_qqFriendId;
}

vector<int> qqUserNodeLA::getQQGroupId()const {
	return m_qqGroupId;
}

qqUserNodeLA* qqUserNodeLA::getNext()const {
	if (this == nullptr) {
		return nullptr;
	}
	return m_next;
}

int qqUserNodeLA::getPlatformId()const {
	return m_platformId;
}

#include<fstream>
#include"qquser.h"

int qqUserListLA::m_qqUserCount = 0;
qqUserNodeLA* qqUserListLA::m_sentinel = nullptr;

qqUserListLA::qqUserListLA() {
	ifstream ifs;
	ifs.open("qqusers.dat", ios::in, ios::binary);
	ifs >> m_qqUserCount;
	m_sentinel = new qqUserNodeLA(0, "sentinel", "sentinel",nullptr);
	int platformId, qqId, qqFriendIdSize, qqGroupIdSize;
	string qqName, qqPassword;
	while (ifs >> platformId >> qqId >> qqName >> qqPassword >> qqFriendIdSize) {
		qqUserNodeLA* qqUserToAdd = new qqUserNodeLA(qqId, qqName, qqPassword, m_sentinel->getNext());
		qqUserToAdd->setPlatformId(platformId);
		qqUserToAdd->setAppUserId(qqId);
		for (int i = 0; i < qqFriendIdSize; i++) {
				int friendId;
				ifs >> friendId;
				qqUserToAdd->addQQFriendId(friendId);
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

void qqUserListLA::saveQQUserList() {
	ofstream ofs;
	ofs.open("qqusers.dat", ios::out, ios::binary);//清除原有数据
	qqUserNodeLA* p = m_sentinel->getNext();
	ofs << m_qqUserCount << endl;
	while (p != nullptr) {
		ofs << p->getPlatformId()
			<< p->getAppUserId() 
			<< " " << p->getUserName() 
			<< " " << p->getUserPasswd()
			<< " " << p->getQQFriendInfo().size();
		for (int i = 0; i < p->getQQFriendInfo().size(); i++) {
			ofs << " " << p->getQQFriendInfo()[i].friendId;
			ofs << " " << p->getQQFriendInfo()[i].friendName;
		}
		ofs << " " << p->getQQGroupId().size();
		for (int i = 0; i < p->getQQGroupId().size(); i++) {
			ofs << " " << p->getQQGroupId()[i];
		}
		ofs << endl;
		p = p->getNext();
	}
	ofs.close();
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

qqUserNodeLA* qqUserListLA::findByQQId(int id) {
	qqUserNodeLA* p = m_sentinel->getNext();
	while (p != nullptr) {
		if (p->getAppUserId() == id) {
			return p;
		}
		p = p->getNext();
	}
	return nullptr;
}

qqUserNodeLA* qqUserListLA::findBySuperId(int id) {
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
	qqUserNodeLA* qqUserToAdd = new qqUserNodeLA(m_qqUserCount, name, password, m_sentinel->getNext());
	m_sentinel->setNext(qqUserToAdd);
	m_qqUserCount++;
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

qqUserNodeLA* qqUserListLA::findBySuperPointer(userNodeLA* userToFind) {
	qqUserNodeLA* p = m_sentinel->getNext();
	while (p != nullptr) {
		if (p->getPlatformId() == userToFind->getID()) {
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

void qqUserNodeLA::addQQFriendId(int id) {
	userInfo* p = new userInfo;
	p->friendId = id;
	p->friendName = qqUserListLA::findByQQId(id)->getUserName();
	m_qqFriendId.push_back(*p);
}

void qqUserNodeLA::addQQGroupId(int id) {
	m_qqGroupId.push_back(id);
}

void qqUserNodeLA::deleteQQFriendId(int id) {
	for (int i = 0; i < m_qqFriendId.size(); i++) {
		if (m_qqFriendId[i].friendId == id) {
			m_qqFriendId.erase(m_qqFriendId.begin() + i);
			return;
		}
	}
}

void qqUserNodeLA::deleteQQGroupId(int id) {
	for (int i = 0; i < m_qqGroupId.size(); i++) {
		if (m_qqGroupId[i] == id) {
			m_qqGroupId.erase(m_qqGroupId.begin() + i);
			return;
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
	return m_next;
}

int qqUserNodeLA::getPlatformId()const {
	return m_platformId;
}

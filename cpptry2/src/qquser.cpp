#include<fstream>
#include"qquser.h"

int qqUserListLA::m_qqUserCount = 0;

qqUserListLA::qqUserListLA() {
	ifstream ifs;
	ifs.open("data\\qqusers.dat", ios::in, ios::binary);
	ifs >> m_qqUserCount;
	m_sentinel = new qqUserNodeLA(0, "sentinel", "sentinel",nullptr);
	int platformId, qqId, qqFriendIdSize, qqGroupIdSize;
	string qqName, qqPassword;
	while (ifs >> platformId >> qqId >> qqName >> qqPassword >> qqFriendIdSize) {
		qqUserNodeLA* qqUserToAdd = new qqUserNodeLA(qqId, qqName, qqPassword, m_sentinel->getNext());
		qqUserToAdd->setPlatformId(platformId);
		qqUserToAdd->setQQId(qqId);
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
	ofs.open("data\\qqusers.dat", ios::out, ios::binary);//清除原有数据
	qqUserNodeLA* p = m_sentinel->getNext();
	ofs << m_qqUserCount << endl;
	while (p != nullptr) {
		ofs << p->getPlatformId()
			<< p->getQQId() 
			<< " " << p->getQQName() 
			<< " " << p->getQQPassword()
			<< " " << p->getQQFriendId().size();
		for (int i = 0; i < p->getQQFriendId().size(); i++) {
			ofs << " " << p->getQQFriendId()[i];
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
		if (p->getQQId() == id) {
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
		if (p->getNext()->getQQId() == id) {
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
	m_qqFriendId.push_back(id);
}

void qqUserNodeLA::addQQGroupId(int id) {
	m_qqGroupId.push_back(id);
}

void qqUserNodeLA::deleteQQFriendId(int id) {
	for (int i = 0; i < m_qqFriendId.size(); i++) {
		if (m_qqFriendId[i] == id) {
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

void qqUserNodeLA::setQQId(int id) {
	m_qqId = id;
}

void qqUserNodeLA::setQQName(string name) {
	m_qqName = name;
}

void qqUserNodeLA::setQQPassword(string password) {
	m_qqPassword = password;
}

void qqUserNodeLA::setNext(qqUserNodeLA* next) {
	m_next = next;
}

int qqUserNodeLA::getQQId() {
	return m_qqId;
}

string qqUserNodeLA::getQQName() {
	return m_qqName;
}

string qqUserNodeLA::getQQPassword() {
	return m_qqPassword;
}

vector<int> qqUserNodeLA::getQQFriendId() {
	return m_qqFriendId;
}

vector<int> qqUserNodeLA::getQQGroupId() {
	return m_qqGroupId;
}

qqUserNodeLA* qqUserNodeLA::getNext() {
	return m_next;
}

int qqUserNodeLA::getPlatformId() {
	return m_platformId;
}

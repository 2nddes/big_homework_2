#include"qqgroup.h"
#include<fstream>
#include<iostream>

int qqGroupNodeLA::m_qqGroupCount = 0;

qqGroupNodeLA::qqGroupNodeLA() {
	m_qqGroupId = ++m_qqGroupCount;
	string m_qqGroupName = "无";
	m_qqGroupMemberIDList.clear();
	m_qqGroupOwnerID = 0;
	m_qqGroupAdminsIDList.clear();
	m_isAllowAdmins = true;
	m_isAllowInvite = true;
	m_isAllowJoin = true;
	m_isAllowSend = true;
	m_isAllowSubgroup = true;
}

qqGroupNodeLA::qqGroupNodeLA(int qqGroupId, string qqGroupName, int qqGroupOwnerId, qqGroupNodeLA* next) {
	m_qqGroupId = qqGroupId;
	m_qqGroupName = qqGroupName;
	m_qqGroupOwnerID = qqGroupOwnerId;
	m_next = next;
	m_isAllowAdmins = true;
	m_isAllowInvite = true;
	m_isAllowJoin = true;
	m_isAllowSend = true;
	m_isAllowSubgroup = true;
}

qqGroupNodeLA::~qqGroupNodeLA() {
	m_qqGroupMemberIDList.clear();
	m_qqGroupAdminsIDList.clear();
}

int qqGroupNodeLA::getGroupId()const {
	return m_qqGroupId;
}

string qqGroupNodeLA::getGroupName()const {
	return m_qqGroupName;
}

void qqGroupNodeLA::setQQGroupId(int qqGroupId) {
	m_qqGroupId = qqGroupId;
}

void qqGroupNodeLA::setQQGroupName(string qqGroupName) {
	m_qqGroupName = qqGroupName;
}

qqGroupNodeLA* qqGroupNodeLA::getNext() {
	return m_next;
}

void qqGroupNodeLA::setNext(qqGroupNodeLA* next) {
	m_next = next;
}

void qqGroupNodeLA::addMember(int userId) {
	m_qqGroupMemberIDList.push_back(userId);
}

void qqGroupNodeLA::addQQGroupAdmin(int userId) {
	m_qqGroupAdminsIDList.push_back(userId);
}

void qqGroupNodeLA::changeOwner(int userId) {
	m_qqGroupOwnerID = userId;
}

void qqGroupNodeLA::removeMember(int userId) {
	for (auto it = m_qqGroupMemberIDList.begin(); it != m_qqGroupMemberIDList.end(); it++) {
		if (*it == userId) {
			m_qqGroupMemberIDList.erase(it);
			return;
		}
	}
}

void qqGroupNodeLA::removeQQGroupAdmin(int userId) {
	for (auto it = m_qqGroupAdminsIDList.begin(); it != m_qqGroupAdminsIDList.end(); it++) {
		if (*it == userId) {
			m_qqGroupAdminsIDList.erase(it);
			return;
		}
	}
}

void qqGroupNodeLA::setQQGroupIsAllowJoin(bool isAllowJoin) {
	m_isAllowJoin = isAllowJoin;
}

void qqGroupNodeLA::setQQGroupIsAllowSubgroup(bool isAllowSubgroup) {
	m_isAllowSubgroup = isAllowSubgroup;
}

void qqGroupNodeLA::setQQGroupIsAllowSend(bool isAllowSend) {
	m_isAllowSend = isAllowSend;
}

void qqGroupNodeLA::setQQGroupIsAllowInvite(bool isAllowInvite) {
	m_isAllowInvite = isAllowInvite;
}

void qqGroupNodeLA::setQQGroupIsAllowAdmins(bool isAllowAdmins) {
	m_isAllowAdmins = isAllowAdmins;
}

bool qqGroupNodeLA::isAdministrator(int userId)const {
	for (auto it = m_qqGroupAdminsIDList.begin(); it != m_qqGroupAdminsIDList.end(); it++) {
		if (*it == userId) {
			return true;
		}
	}
	return false;
}

bool qqGroupNodeLA::isMember(int userId)const {
	for (auto it = m_qqGroupMemberIDList.begin(); it != m_qqGroupMemberIDList.end(); it++) {
		if (*it == userId) {
			return true;
		}
	}
	return false;
}

bool qqGroupNodeLA::isOwner(int userId)const {
	return m_qqGroupOwnerID == userId;
}

bool qqGroupNodeLA::isAllowJoin()const {
	return m_isAllowJoin;
}

bool qqGroupNodeLA::isAllowSubgroup()const {
	return m_isAllowSubgroup;
}

bool qqGroupNodeLA::isAllowSend()const {
	return m_isAllowSend;
}

bool qqGroupNodeLA::isAllowInvite()const {
	return m_isAllowInvite;
}

bool qqGroupNodeLA::isAllowAdmins()const {
	return m_isAllowAdmins;
}

int qqGroupNodeLA::getQQGroupOwnerID()const {
	return m_qqGroupOwnerID;
}

int qqGroupNodeLA::getQQGroupMemberCount()const {
	return m_qqGroupMemberIDList.size();
}

int qqGroupNodeLA::getQQGroupId()const {
	return m_qqGroupId;
}

string qqGroupNodeLA::getQQGroupName()const {
	return m_qqGroupName;
}

vector<int> qqGroupNodeLA::getQQGroupMemberIDList()const {
	return m_qqGroupMemberIDList;
}

vector<int> qqGroupNodeLA::getQQGroupAdminsIDList()const {
	return m_qqGroupAdminsIDList;
}

/////////////////////////////////////////////////

qqGroupListLA::qqGroupListLA() {
	m_sentinel = new qqGroupNodeLA();
	//从文件data\\qqgroups.dat读取群列表
	ifstream fin("data\\qqgroups.dat",ios::in,ios::binary);
	if (!fin) {
		cout << "qqgroups.dat not found!" << endl;
		return;
	}
	///////////////////////////TODO////////////////////////
	int qqGroupNum = 0;
	string qqGroupName;
	int qqGroupMemberCount = 0;
	int qqGroupAdminsCount = 0;
	int qqGroupOwnerId = 0;
	int qqGroupMemberId = 0;
	int qqGroupAdminId = 0;
	bool isAllowJoin = false;
	bool isAllowSubgroup = false;
	bool isAllowSend = false;
	bool isAllowInvite = false;
	while (fin >> qqGroupNum >> qqGroupName >> qqGroupOwnerId) {
		m_sentinel->setNext(new qqGroupNodeLA(qqGroupNum, qqGroupName, qqGroupOwnerId, m_sentinel->getNext()));
		qqGroupNodeLA* p = m_sentinel->getNext();
		fin >> isAllowJoin >> isAllowSubgroup >> isAllowSend >> isAllowInvite;
		p->setQQGroupIsAllowJoin(isAllowJoin);
		p->setQQGroupIsAllowSubgroup(isAllowSubgroup);
		p->setQQGroupIsAllowSend(isAllowSend);
		p->setQQGroupIsAllowInvite(isAllowInvite);
		fin >> qqGroupMemberCount;
		for (int i = 0; i < qqGroupMemberCount; i++) {
			fin >> qqGroupMemberId;
			p->m_qqGroupMemberIDList.push_back(qqGroupMemberId);
		}
		fin >> qqGroupAdminsCount;
		for (int i = 0; i < qqGroupAdminsCount; i++) {
			fin >> qqGroupAdminId;
			p->m_qqGroupAdminsIDList.push_back(qqGroupAdminId);
		}


	}
	///////////////////////////TODO///////////////////////////
}



qqGroupListLA::~qqGroupListLA() {
	saveGroupListData();
	qqGroupNodeLA* p = m_sentinel->getNext();
	while (p != m_sentinel) {
		qqGroupNodeLA* q = p->getNext();
		delete p;
		p = q;
	}
	delete m_sentinel;
}

void qqGroupListLA::saveGroupListData() {
	ofstream fout("data\\qqgroups.dat",ios::out,ios::binary);
	if (!fout) {
		cout << "qqgroups.dat not found!" << endl;
		return;
	}
	qqGroupNodeLA* p = m_sentinel->getNext();
	while (p != m_sentinel) {
		fout << p->getGroupId() << " " << p->getGroupName() << " " << p->getQQGroupOwnerID() << endl;
		fout << p->isAllowJoin() << " " << p->isAllowSubgroup() << " " << p->isAllowSend() << " " << p->isAllowInvite() << endl;
		fout << p->getQQGroupMemberCount() << endl;
		for (auto it = p->getQQGroupMemberIDList().begin(); it != p->getQQGroupMemberIDList().end(); it++) {
			fout << *it << " ";
		}
		fout << endl;
		fout << p->getQQGroupAdminsIDList().size() << endl;
		for (auto it = p->getQQGroupAdminsIDList().begin(); it != p->getQQGroupAdminsIDList().end(); it++) {
			fout << *it << " ";
		}
		fout << endl;
		p = p->getNext();
	}

}

void qqGroupListLA::addGroup(qqGroupNodeLA* node) {
	node->setNext(m_sentinel->getNext());
	m_sentinel->setNext(node);
}

void qqGroupListLA::removeGroup(qqGroupNodeLA* node) {
	qqGroupNodeLA* p = m_sentinel;
	while (p->getNext() != node) {
		p = p->getNext();
	}
	p->setNext(node->getNext());
	delete node;
}

qqGroupNodeLA* qqGroupListLA::findByGroupId(int qqGroupId) {
	qqGroupNodeLA* p = m_sentinel->getNext();
	while (p != m_sentinel) {
		if (p->getGroupId() == qqGroupId) {
			return p;
		}
		p = p->getNext();
	}
	return nullptr;
}

qqGroupNodeLA* qqGroupListLA::getSentinel() {
	return m_sentinel;
}

#include"utils.h"
#include"qqgroup.h"
#include<fstream>
#include<iostream>

qqGroupNodeLA::qqGroupNodeLA() {
	m_qqGroupId = 0;
	string m_qqGroupName = "无";
	m_qqGroupMemberInfoList.clear();
	m_qqGroupOwnerID = 0;
	m_qqGroupAdminsIDList.clear();
	m_next = nullptr;
	m_qqGroupInvitedIDList.clear();
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
	m_qqGroupMemberInfoList.clear();
	m_qqGroupAdminsIDList.clear();
	m_qqGroupInvitedIDList.clear();
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
	if (this == nullptr) {
		return nullptr;
	}
	return m_next;
}

void qqGroupNodeLA::setNext(qqGroupNodeLA* next) {
	m_next = next;
}

void qqGroupNodeLA::addMember(int userId) {
	userInfo memberInfo;
	memberInfo.friendId = userId;
	memberInfo.friendName = "无";
	m_qqGroupMemberInfoList.push_back(memberInfo);
}

void qqGroupNodeLA::addQQGroupAdmin(int userId) {
	userInfo adminInfo;
	adminInfo.friendId = userId;
	adminInfo.friendName = "无";
	m_qqGroupAdminsIDList.push_back(adminInfo);
}

void qqGroupNodeLA::addRequest(userInfo userinfo){
	m_qqGroupInvitedIDList.push_back(userinfo);
}

void qqGroupNodeLA::removeRequest(int userId) {
	for (int i = 0; i < m_qqGroupInvitedIDList.size();i++) {
		if (userId == m_qqGroupInvitedIDList[i].friendId) {
			m_qqGroupInvitedIDList.erase(m_qqGroupInvitedIDList.begin() + i);
			return;
		}
	}
}

void qqGroupNodeLA::changeOwner(int userId) {
	m_qqGroupOwnerID = userId;
}

void qqGroupNodeLA::removeMember(int userId) {
	for (auto it = m_qqGroupMemberInfoList.begin(); it != m_qqGroupMemberInfoList.end(); it++) {
		if (userId == it->friendId) {
			m_qqGroupMemberInfoList.erase(it);
			return;
		}
	}
}

void qqGroupNodeLA::removeMember(vector<int> userIdList) {
	for (auto it = userIdList.begin(); it != userIdList.end(); it++) {
		for (auto it2 = m_qqGroupMemberInfoList.begin(); it2 != m_qqGroupMemberInfoList.end(); it2++) {
			if (*it == it2->friendId) {
				m_qqGroupMemberInfoList.erase(it2);
				break;
			}
		}
	}
}

void qqGroupNodeLA::removeQQGroupAdmin(int userId) {
	for (auto it = m_qqGroupAdminsIDList.begin(); it != m_qqGroupAdminsIDList.end(); it++) {
		if (it->friendId == userId) {
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

void qqGroupNodeLA::setMemberName(int userId, string userName) {
	for (auto it = m_qqGroupMemberInfoList.begin(); it != m_qqGroupMemberInfoList.end(); it++) {
		if (it->friendId == userId) {
			it->friendName = userName;
			return;
		}
	}
}

void qqGroupNodeLA::setGroupNickName(int userId, string groupNickName)
{
	for (auto it = m_qqGroupMemberInfoList.begin(); it != m_qqGroupMemberInfoList.end(); it++) {
		if (it->friendId == userId) {
			it->friendName = groupNickName;
			return;
		}
	}
}

bool qqGroupNodeLA::isAdministrator(int userId)const {
	for (auto it = m_qqGroupAdminsIDList.begin(); it != m_qqGroupAdminsIDList.end(); it++) {
		if (it->friendId == userId) {
			return true;
		}
	}
	return false;
}

bool qqGroupNodeLA::isMember(int userId)const {
	for (auto it = m_qqGroupMemberInfoList.begin(); it != m_qqGroupMemberInfoList.end(); it++) {
		if (it->friendId == userId) {
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
	return (int)m_qqGroupMemberInfoList.size();
}

int qqGroupNodeLA::getQQGroupId()const {
	return m_qqGroupId;
}

string qqGroupNodeLA::getQQGroupName()const {
	return m_qqGroupName;
}

string qqGroupNodeLA::getGroupNickName(int userId) const {
	for (auto it = m_qqGroupMemberInfoList.begin(); it != m_qqGroupMemberInfoList.end(); it++) {
		if (it->friendId == userId) {
			return it->friendName;
		}
	}
	return "无";
}

vector<userInfo> qqGroupNodeLA::getQQGroupMemberInfoList()const {
	return m_qqGroupMemberInfoList;
}

vector<userInfo> qqGroupNodeLA::getQQGroupAdminsInfoList()const {
	return m_qqGroupAdminsIDList;
}

vector<userInfo> qqGroupNodeLA::getQQGroupRequestInfoList() const {
	return m_qqGroupInvitedIDList;
}

/////////////////////////////////////////////////

qqGroupListLA::qqGroupListLA() {
	m_sentinel = new qqGroupNodeLA();

	ifstream fin("QQ\\qqgroups.dat",ios::in);
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

	fin >> m_qqGroupCount;
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

			userInfo qqGroupMemberInfo;
			fin >> qqGroupMemberInfo.friendId;
			fin >> qqGroupMemberInfo.friendName;

			p->m_qqGroupMemberInfoList.push_back(qqGroupMemberInfo);
		}

		fin >> qqGroupAdminsCount;

		for (int i = 0; i < qqGroupAdminsCount; i++) {

			userInfo qqGroupAdminsInfo;
			fin >> qqGroupAdminsInfo.friendId;
			fin >> qqGroupAdminsInfo.friendName;

			p->m_qqGroupAdminsIDList.push_back(qqGroupAdminsInfo);
		}

		int qqGroupInvitedCount = 0;
		fin >> qqGroupInvitedCount;

		for (int i = 0; i < qqGroupInvitedCount; i++) {

			userInfo qqGroupInvitedInfo;
			fin >> qqGroupInvitedInfo.friendId;
			fin >> qqGroupInvitedInfo.friendName;

			p->m_qqGroupInvitedIDList.push_back(qqGroupInvitedInfo);
		}

	}
	fin.close();
	///////////////////////////TODO///////////////////////////
}



qqGroupListLA::~qqGroupListLA() {
	qqGroupNodeLA* p = m_sentinel->getNext();
	while (p != nullptr) {
		qqGroupNodeLA* q = p->getNext();
		delete p;
		p = q;
	}
	delete m_sentinel;
}

void qqGroupListLA::saveGroupListData() {
	ofstream fout("QQ\\qqgroups.dat",ios::out);
	if (!fout) {
		cout << "qqgroups.dat not found!" << endl;
		return;
	}
	fout << m_qqGroupCount << " ";
	qqGroupNodeLA* p = m_sentinel->getNext();
	while (p != nullptr) {
		fout << p->getGroupId() << " " 
			<< p->getGroupName() << " " 
			<< p->getQQGroupOwnerID() << " " 
			<< p->isAllowJoin() << " " 
			<< p->isAllowSubgroup() << " " 
			<< p->isAllowSend() << " " 
			<< p->isAllowInvite() << " " 

			<< p->getQQGroupMemberCount() << " ";
		vector<userInfo> memberList = p->getQQGroupMemberInfoList();
		for (int i = 0; i < memberList.size();i++) {
			fout << memberList[i].friendId << " " 
				<< memberList[i].friendName << " ";
		}
		fout << p->getQQGroupAdminsInfoList().size() << endl;
		vector<userInfo> adminsList = p->getQQGroupAdminsInfoList();
		for (int i = 0; i < adminsList.size();i++) {
			fout << adminsList[i].friendId << " " 
				<< adminsList[i].friendName << " ";
		}
		vector<userInfo> invitedList = p->getQQGroupRequestInfoList();
		fout << invitedList.size() << endl;
		for (int i = 0; i < invitedList.size(); i++) {
			fout << invitedList[i].friendId << " " 
				<< invitedList[i].friendName << " ";
		}

		p = p->getNext();
	}
	fout.close();
}

void qqGroupListLA::addGroup(qqGroupNodeLA* node) {
	node->setNext(m_sentinel->getNext());
	m_sentinel->setNext(node);
}

qqGroupNodeLA* qqGroupListLA::addGroup(string qqGroupName, int qqGroupOwnerID) {
	qqGroupNodeLA* p = new qqGroupNodeLA(m_qqGroupCount++, qqGroupName, qqGroupOwnerID, m_sentinel->getNext());
	p->setQQGroupName(qqGroupName);
	p->addMember(qqGroupOwnerID);
	p->changeOwner(qqGroupOwnerID);
	addGroup(p);
	return p;
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
	while (p != nullptr) {
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

int qqGroupListLA::size() const{
	return m_qqGroupCount;
}

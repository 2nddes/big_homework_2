#include"/project/C++Project/cpptry2/cpptry2/src/utils.h"
#include"WeChatgroup.h"
#include<fstream>
#include<iostream>

WeChatGroupNodeLA::WeChatGroupNodeLA() {
	m_WeChatGroupId = 0;
	string m_WeChatGroupName = "无";
	m_WeChatGroupMemberInfoList.clear();
	m_WeChatGroupOwnerID = 0;
	m_WeChatGroupAdminsIDList.clear();
	m_next = nullptr;
	m_WeChatGroupInvitedIDList.clear();
	m_isAllowAdmins = false;
	m_isAllowInvite = false;
	m_isAllowJoin = false;
	m_isAllowSend = false;
	m_isAllowSubgroup = false;
}

WeChatGroupNodeLA::WeChatGroupNodeLA(int WeChatGroupId, string WeChatGroupName, int WeChatGroupOwnerId, WeChatGroupNodeLA* next) {
	m_WeChatGroupId = WeChatGroupId;
	m_WeChatGroupName = WeChatGroupName;
	m_WeChatGroupOwnerID = WeChatGroupOwnerId;
	m_next = next;
	m_isAllowAdmins = false;
	m_isAllowInvite = false;
	m_isAllowJoin = false;
	m_isAllowSend = false;
	m_isAllowSubgroup = false;
}

WeChatGroupNodeLA::~WeChatGroupNodeLA() {
	m_WeChatGroupMemberInfoList.clear();
	m_WeChatGroupAdminsIDList.clear();
	m_WeChatGroupInvitedIDList.clear();
}

int WeChatGroupNodeLA::getGroupId()const {
	return m_WeChatGroupId;
}

string WeChatGroupNodeLA::getGroupName()const {
	return m_WeChatGroupName;
}

void WeChatGroupNodeLA::setWeChatGroupId(int WeChatGroupId) {
	m_WeChatGroupId = WeChatGroupId;
}

void WeChatGroupNodeLA::setWeChatGroupName(string WeChatGroupName) {
	m_WeChatGroupName = WeChatGroupName;
}

WeChatGroupNodeLA* WeChatGroupNodeLA::getNext() {
	if (this == nullptr) {
		return nullptr;
	}
	return m_next;
}

void WeChatGroupNodeLA::setNext(WeChatGroupNodeLA* next) {
	m_next = next;
}

void WeChatGroupNodeLA::addMember(int userId) {
	userInfo memberInfo;
	memberInfo.friendId = userId;
	memberInfo.friendName = "无";
	m_WeChatGroupMemberInfoList.push_back(memberInfo);
}

void WeChatGroupNodeLA::addWeChatGroupAdmin(int userId) {
	userInfo adminInfo;
	adminInfo.friendId = userId;
	adminInfo.friendName = "无";
	m_WeChatGroupAdminsIDList.push_back(adminInfo);
}

void WeChatGroupNodeLA::addRequest(userInfo userinfo) {
	m_WeChatGroupInvitedIDList.push_back(userinfo);
}

void WeChatGroupNodeLA::removeRequest(int userId) {
	for (int i = 0; i < m_WeChatGroupInvitedIDList.size(); i++) {
		if (userId == m_WeChatGroupInvitedIDList[i].friendId) {
			m_WeChatGroupInvitedIDList.erase(m_WeChatGroupInvitedIDList.begin() + i);
			return;
		}
	}
}

void WeChatGroupNodeLA::changeOwner(int userId) {
	m_WeChatGroupOwnerID = userId;
}

void WeChatGroupNodeLA::removeMember(int userId) {
	for (auto it = m_WeChatGroupMemberInfoList.begin(); it != m_WeChatGroupMemberInfoList.end(); it++) {
		if (userId == it->friendId) {
			m_WeChatGroupMemberInfoList.erase(it);
			return;
		}
	}
}

void WeChatGroupNodeLA::removeMember(vector<int> userIdList) {
	for (auto it = userIdList.begin(); it != userIdList.end(); it++) {
		for (auto it2 = m_WeChatGroupMemberInfoList.begin(); it2 != m_WeChatGroupMemberInfoList.end(); it2++) {
			if (*it == it2->friendId) {
				m_WeChatGroupMemberInfoList.erase(it2);
				break;
			}
		}
	}
}

void WeChatGroupNodeLA::removeWeChatGroupAdmin(int userId) {
	for (auto it = m_WeChatGroupAdminsIDList.begin(); it != m_WeChatGroupAdminsIDList.end(); it++) {
		if (it->friendId == userId) {
			m_WeChatGroupAdminsIDList.erase(it);
			return;
		}
	}
}

void WeChatGroupNodeLA::setWeChatGroupIsAllowJoin(bool isAllowJoin) {
	m_isAllowJoin = isAllowJoin;
}

void WeChatGroupNodeLA::setWeChatGroupIsAllowSubgroup(bool isAllowSubgroup) {
	m_isAllowSubgroup = isAllowSubgroup;
}

void WeChatGroupNodeLA::setWeChatGroupIsAllowSend(bool isAllowSend) {
	m_isAllowSend = isAllowSend;
}

void WeChatGroupNodeLA::setWeChatGroupIsAllowInvite(bool isAllowInvite) {
	m_isAllowInvite = isAllowInvite;
}

void WeChatGroupNodeLA::setWeChatGroupIsAllowAdmins(bool isAllowAdmins) {
	m_isAllowAdmins = isAllowAdmins;
}

void WeChatGroupNodeLA::setMemberName(int userId, string userName) {
	for (auto it = m_WeChatGroupMemberInfoList.begin(); it != m_WeChatGroupMemberInfoList.end(); it++) {
		if (it->friendId == userId) {
			it->friendName = userName;
			return;
		}
	}
}

void WeChatGroupNodeLA::setGroupNickName(int userId, string groupNickName)
{
	for (auto it = m_WeChatGroupMemberInfoList.begin(); it != m_WeChatGroupMemberInfoList.end(); it++) {
		if (it->friendId == userId) {
			it->friendName = groupNickName;
			return;
		}
	}
}

bool WeChatGroupNodeLA::isAdministrator(int userId)const {
	for (auto it = m_WeChatGroupAdminsIDList.begin(); it != m_WeChatGroupAdminsIDList.end(); it++) {
		if (it->friendId == userId) {
			return true;
		}
	}
	return false;
}

bool WeChatGroupNodeLA::isMember(int userId)const {
	for (auto it = m_WeChatGroupMemberInfoList.begin(); it != m_WeChatGroupMemberInfoList.end(); it++) {
		if (it->friendId == userId) {
			return true;
		}
	}
	return false;
}

bool WeChatGroupNodeLA::isOwner(int userId)const {
	return m_WeChatGroupOwnerID == userId;
}

bool WeChatGroupNodeLA::isAllowJoin()const {
	return m_isAllowJoin;
}

bool WeChatGroupNodeLA::isAllowSubgroup()const {
	return m_isAllowSubgroup;
}

bool WeChatGroupNodeLA::isAllowSend()const {
	return m_isAllowSend;
}

bool WeChatGroupNodeLA::isAllowInvite()const {
	return m_isAllowInvite;
}

bool WeChatGroupNodeLA::isAllowAdmins()const {
	return m_isAllowAdmins;
}

int WeChatGroupNodeLA::getWeChatGroupOwnerID()const {
	return m_WeChatGroupOwnerID;
}

int WeChatGroupNodeLA::getWeChatGroupMemberCount()const {
	return (int)m_WeChatGroupMemberInfoList.size();
}

int WeChatGroupNodeLA::getWeChatGroupId()const {
	return m_WeChatGroupId;
}

string WeChatGroupNodeLA::getWeChatGroupName()const {
	return m_WeChatGroupName;
}

string WeChatGroupNodeLA::getGroupNickName(int userId) const {
	for (auto it = m_WeChatGroupMemberInfoList.begin(); it != m_WeChatGroupMemberInfoList.end(); it++) {
		if (it->friendId == userId) {
			return it->friendName;
		}
	}
	return "无";
}

vector<userInfo> WeChatGroupNodeLA::getWeChatGroupMemberInfoList()const {
	return m_WeChatGroupMemberInfoList;
}

vector<userInfo> WeChatGroupNodeLA::getWeChatGroupAdminsInfoList()const {
	return m_WeChatGroupAdminsIDList;
}

vector<userInfo> WeChatGroupNodeLA::getWeChatGroupRequestInfoList() const {
	return m_WeChatGroupInvitedIDList;
}

/////////////////////////////////////////////////

WeChatGroupListLA::WeChatGroupListLA() {
	m_sentinel = new WeChatGroupNodeLA();

	ifstream fin("WeChat\\WeChatgroups.dat", ios::in);
	if (!fin) {
		cout << "WeChatgroups.dat not found!" << endl;
		return;
	}
	///////////////////////////TODO////////////////////////
	int WeChatGroupNum = 0;
	string WeChatGroupName;
	int WeChatGroupMemberCount = 0;
	int WeChatGroupAdminsCount = 0;
	int WeChatGroupOwnerId = 0;
	int WeChatGroupMemberId = 0;
	int WeChatGroupAdminId = 0;
	bool isAllowJoin = false;
	bool isAllowSubgroup = false;
	bool isAllowSend = false;
	bool isAllowInvite = false;

	fin >> m_WeChatGroupCount;
	while (fin >> WeChatGroupNum >> WeChatGroupName >> WeChatGroupOwnerId) {

		m_sentinel->setNext(new WeChatGroupNodeLA(WeChatGroupNum, WeChatGroupName, WeChatGroupOwnerId, m_sentinel->getNext()));
		WeChatGroupNodeLA* p = m_sentinel->getNext();
		fin >> isAllowJoin >> isAllowSubgroup >> isAllowSend >> isAllowInvite;
		p->setWeChatGroupIsAllowJoin(isAllowJoin);
		p->setWeChatGroupIsAllowSubgroup(isAllowSubgroup);
		p->setWeChatGroupIsAllowSend(isAllowSend);
		p->setWeChatGroupIsAllowInvite(isAllowInvite);

		fin >> WeChatGroupMemberCount;

		for (int i = 0; i < WeChatGroupMemberCount; i++) {

			userInfo WeChatGroupMemberInfo;
			fin >> WeChatGroupMemberInfo.friendId;
			fin >> WeChatGroupMemberInfo.friendName;

			p->m_WeChatGroupMemberInfoList.push_back(WeChatGroupMemberInfo);
		}

		fin >> WeChatGroupAdminsCount;

		for (int i = 0; i < WeChatGroupAdminsCount; i++) {

			userInfo WeChatGroupAdminsInfo;
			fin >> WeChatGroupAdminsInfo.friendId;
			fin >> WeChatGroupAdminsInfo.friendName;

			p->m_WeChatGroupAdminsIDList.push_back(WeChatGroupAdminsInfo);
		}

		int WeChatGroupInvitedCount = 0;
		fin >> WeChatGroupInvitedCount;

		for (int i = 0; i < WeChatGroupInvitedCount; i++) {

			userInfo WeChatGroupInvitedInfo;
			fin >> WeChatGroupInvitedInfo.friendId;
			fin >> WeChatGroupInvitedInfo.friendName;

			p->m_WeChatGroupInvitedIDList.push_back(WeChatGroupInvitedInfo);
		}

	}
	fin.close();
	///////////////////////////TODO///////////////////////////
}



WeChatGroupListLA::~WeChatGroupListLA() {
	WeChatGroupNodeLA* p = m_sentinel->getNext();
	while (p != nullptr) {
		WeChatGroupNodeLA* q = p->getNext();
		delete p;
		p = q;
	}
	delete m_sentinel;
}

void WeChatGroupListLA::saveGroupListData() {
	ofstream fout("WeChat\\WeChatgroups.dat", ios::out);
	if (!fout) {
		cout << "WeChatgroups.dat not found!" << endl;
		return;
	}
	fout << m_WeChatGroupCount << " ";
	WeChatGroupNodeLA* p = m_sentinel->getNext();
	while (p != nullptr) {
		fout << p->getGroupId() << " "
			<< p->getGroupName() << " "
			<< p->getWeChatGroupOwnerID() << " "
			<< p->isAllowJoin() << " "
			<< p->isAllowSubgroup() << " "
			<< p->isAllowSend() << " "
			<< p->isAllowInvite() << " "

			<< p->getWeChatGroupMemberCount() << " ";
		vector<userInfo> memberList = p->getWeChatGroupMemberInfoList();
		for (int i = 0; i < memberList.size(); i++) {
			fout << memberList[i].friendId << " "
				<< memberList[i].friendName << " ";
		}
		fout << p->getWeChatGroupAdminsInfoList().size() << endl;
		vector<userInfo> adminsList = p->getWeChatGroupAdminsInfoList();
		for (int i = 0; i < adminsList.size(); i++) {
			fout << adminsList[i].friendId << " "
				<< adminsList[i].friendName << " ";
		}
		vector<userInfo> invitedList = p->getWeChatGroupRequestInfoList();
		fout << invitedList.size() << endl;
		for (int i = 0; i < invitedList.size(); i++) {
			fout << invitedList[i].friendId << " "
				<< invitedList[i].friendName << " ";
		}

		p = p->getNext();
	}
	fout.close();
}

void WeChatGroupListLA::addGroup(WeChatGroupNodeLA* node) {
	node->setNext(m_sentinel->getNext());
	m_sentinel->setNext(node);
}

WeChatGroupNodeLA* WeChatGroupListLA::addGroup(string WeChatGroupName, int WeChatGroupOwnerID) {
	WeChatGroupNodeLA* p = new WeChatGroupNodeLA(m_WeChatGroupCount++, WeChatGroupName, WeChatGroupOwnerID, m_sentinel->getNext());
	p->setWeChatGroupName(WeChatGroupName);
	p->addMember(WeChatGroupOwnerID);
	p->changeOwner(WeChatGroupOwnerID);
	addGroup(p);
	return p;
}

void WeChatGroupListLA::removeGroup(WeChatGroupNodeLA* node) {
	WeChatGroupNodeLA* p = m_sentinel;
	while (p->getNext() != node) {
		p = p->getNext();
	}
	p->setNext(node->getNext());
	delete node;
}

WeChatGroupNodeLA* WeChatGroupListLA::findByGroupId(int WeChatGroupId) {
	WeChatGroupNodeLA* p = m_sentinel->getNext();
	while (p != nullptr) {
		if (p->getGroupId() == WeChatGroupId) {
			return p;
		}
		p = p->getNext();
	}
	return nullptr;
}

WeChatGroupNodeLA* WeChatGroupListLA::getSentinel() {
	return m_sentinel;
}

int WeChatGroupListLA::size() const {
	return m_WeChatGroupCount - 1001;
}

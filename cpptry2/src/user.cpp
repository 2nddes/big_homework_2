#include"utils.h"
#include"user.h"
#include<fstream>
#include<iostream>

userNodeLA::userNodeLA() {
	m_userName = "无";
	m_birth = 20000101;
	m_address = "无";
	m_next = nullptr;
	m_userId = -1;
}

userNodeLA::userNodeLA(int userID, string userName, int birth, string address, userNodeLA* next) {
	m_userId = userID;
	m_userName = userName;
	m_birth = birth;
	m_address = address;
	m_next = next;
	m_userId = userID;
	m_qqActivationStatus = false;
}

userNodeLA::userNodeLA(int userID, string userName, int birth, string address, bool qqActivationStatus, userNodeLA* next) {
	m_userId = userID;
	m_userName = userName;
	m_birth = birth;
	m_address = address;
	m_next = next;
	m_userId = userID;
	m_qqActivationStatus = qqActivationStatus;
}

userNodeLA::~userNodeLA() {}

int userNodeLA::getID()const {
	return m_userId;
}

string userNodeLA::getUserName()const {
	return m_userName;
}

int userNodeLA::getBirth()const {
	return m_birth;
}

string userNodeLA::getAddress()const {
	return m_address;
}

userNodeLA* userNodeLA::getNext()const {
	return m_next;
}

int userNodeLA::getTAge()const {
	return 2018 - m_birth;
	//TODO: calculate age
}

void userNodeLA::setNext(userNodeLA* next) {
	m_next = next;
}

void userNodeLA::setUserName(string userName) {
	m_userName = userName;
}

void userNodeLA::setBirth(int birth) {
	m_birth = birth;
}

void userNodeLA::setAddress(string address) {
	m_address = address;
}

bool userNodeLA::isQQEnabled()const {
	return m_qqActivationStatus;
}

bool userNodeLA::isWeChatEnabled() const {
	return m_wechatActivationStatus;
}

void userNodeLA::setQQStatus(bool status) {
	m_qqActivationStatus = status;
}

void userNodeLA::setWeChatStatus(bool status) {
	m_wechatActivationStatus = status;
}

void userNodeLA::setPhone(string phoneNumber)
{
	m_phoneNumber = phoneNumber;
}

void userNodeLA::setEmail(string email)
{
	m_email = email;
}

userListLA::userListLA() {
	m_sentinel = new userNodeLA();
}

userListLA::~userListLA() {
	userNodeLA* temp = m_sentinel;
	while (temp != NULL) {
		userNodeLA* next = temp->getNext();
		delete temp;
		temp = next;
	}
}

userNodeLA* userListLA::addUser() {
	userNodeLA* userToAdd = new userNodeLA(m_userCount++, "无", 20000101, "无", false, m_sentinel->getNext());
	m_sentinel->setNext(userToAdd);
	saveUserList();
	return userToAdd;
}

userNodeLA* userListLA::addUser(string userName, int birth, string address) {
	userNodeLA* userToAdd = new userNodeLA(m_userCount++, userName, birth, address, false, m_sentinel->getNext());
	m_sentinel->setNext(userToAdd);
	saveUserList();
	return userToAdd;
}

userNodeLA* userListLA::findByUserName(string userName)const {
	userNodeLA* temp = m_sentinel->getNext();
	while (temp != NULL) {
		if (temp->getUserName() == userName) {
			return temp;
		}
		temp = temp->getNext();
	}
	return NULL;
}

userNodeLA* userListLA::findByUserId(int id)const {
	userNodeLA* temp = m_sentinel->getNext();
	while (temp != NULL) {
		if (temp->getID() == id) {
			return temp;
		}
		temp = temp->getNext();
	}
	return NULL;
}

void userListLA::loadUserList() {
	ifstream fin("userlist.dat", ios::in);
	if (!fin) {
		cout << "userlist.dat not found!" << endl;
		return;
	}

	int userId;
	string userName;
	int birth;
	int TAge;
	string address;
	bool qqActivationStatus;

	fin >> m_userCount;
	while (fin >> userId >> userName >> birth >> TAge >> address >> qqActivationStatus) {
		userNodeLA* userToAdd = new userNodeLA(userId, userName, birth, address, qqActivationStatus, m_sentinel->getNext());
		m_sentinel->setNext(userToAdd);
	}

	fin.close();
}

void userListLA::saveUserList()const {
	ofstream fout("userlist.dat", ios::out);
	if (!fout) {
		cout << "userlist.dat not found!" << endl;
		return;
	}

	fout << m_userCount << " ";
	userNodeLA* temp = m_sentinel->getNext();

	while (temp != NULL) {
		fout << temp->getID() << " "
			 << temp->getUserName()<< " "
			 << temp->getBirth()<< " "
			 << temp->getTAge()<< " "
			 << temp->getAddress()<< " "
			 << temp->isQQEnabled()<< " ";
		temp = temp->getNext();
	}

	fout.close();
}
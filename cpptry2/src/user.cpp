#include"utils.h"
#include"user.h"
#include<fstream>
#include<iostream>

userNodeLA::userNodeLA() {
	m_userName = "无";
	m_birth = 20000101;
	m_address = "无";
	m_next = nullptr;
	m_platformId = -1;
}

userNodeLA::userNodeLA(int userID, string userName, int birth, string address, userNodeLA* next) {
	m_platformId = userID;
	m_userName = userName;
	m_birth = birth;
	m_address = address;
	m_next = next;
	m_platformId = userID;
	m_qqActivationStatus = false;
}

userNodeLA::userNodeLA(int userID, string userName, int birth, string address, bool qqActivationStatus, bool WeChatActivationStatus, userNodeLA* next) {
	m_platformId = userID;
	m_userName = userName;
	m_birth = birth;
	m_address = address;
	m_next = next;
	m_platformId = userID;
	m_qqActivationStatus = qqActivationStatus;
	m_wechatActivationStatus = WeChatActivationStatus;
}

userNodeLA::~userNodeLA() {}

int userNodeLA::getPlatformId()const {
	return m_platformId;
}

string userNodeLA::getUserName()const {
	return m_userName;
}

string userNodeLA::getUserPasswd() const
{
	return string();
}

int userNodeLA::getAppUserId() const
{
	return -1;
}

void userNodeLA::setPlatformId(int platformId)
{
	m_platformId = platformId;
}

void userNodeLA::setAppUserId(int appUserId)
{
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

string userNodeLA::getPhone() const
{
	return m_phoneNumber;
}

string userNodeLA::getEmail() const
{
	return m_email;
}

void userNodeLA::setNext(userNodeLA* next) {
	m_next = next;
}

void userNodeLA::setUserName(string userName) {
	m_userName = userName;
}

void userNodeLA::setUserPasswd(string userPassword)
{
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
	userNodeLA* userToAdd = new userNodeLA(m_userCount++, "无", 20000101, "无", false, false, m_sentinel->getNext());
	m_sentinel->setNext(userToAdd);
	saveUserList();
	return userToAdd;
}

userNodeLA* userListLA::addUser(string userName, int birth, string address) {
	userNodeLA* userToAdd = new userNodeLA(m_userCount++, userName, birth, address, false, false, m_sentinel->getNext());
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
		if (temp->getPlatformId() == id) {
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
	bool wechatActivationStatus;

	fin >> m_userCount;
	while (fin >> userId >> userName >> birth >> TAge >> address >> qqActivationStatus >>wechatActivationStatus) {
		userNodeLA* userToAdd = new userNodeLA(userId, userName, birth, address, qqActivationStatus, wechatActivationStatus, m_sentinel->getNext());
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
		fout << temp->getPlatformId() << " "
			<< temp->getUserName() << " "
			<< temp->getBirth() << " "
			<< temp->getTAge() << " "
			<< temp->getAddress() << " "
			<< temp->isQQEnabled() << " "
			<< temp->isWeChatEnabled() << " ";
		temp = temp->getNext();
	}

	fout.close();
}
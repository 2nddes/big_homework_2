#include"user.h"
#include<fstream>

int userNodeLA::m_userCount = 0;

userNodeLA::userNodeLA() {
	m_userId = ++m_userCount;
}

userNodeLA::userNodeLA(string userName, int birth, string address, userNodeLA* next) {
	m_userId = ++m_userCount;
	m_userName = userName;
	m_birth = birth;
	m_address = address;
	m_next = next;
	m_userId = m_userCount++;
	m_qqActivationStatus = false;
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

void userNodeLA::setQQStatus(bool status) {
	m_qqActivationStatus = status;
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
	userNodeLA* userToAdd = new userNodeLA("нч",20000101,"нч",m_sentinel->getNext());
	m_sentinel->setNext(userToAdd);
	return userToAdd;
}

userNodeLA* userListLA::addUser(string userName, int birth, string address) {
	userNodeLA* userToAdd = new userNodeLA(userName, birth, address, m_sentinel->getNext());
	m_sentinel->setNext(userToAdd);
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
	ifstream fin("userlist.dat", ios::in, ios::binary);
	string userName;
	int birth;
	string address;
	while (fin >> userName >> birth >> address) {
		addUser(userName, birth, address);
	}
	fin.close();
}

void userListLA::saveUserList()const {
	ofstream fout("userlist.dat");
	userNodeLA* temp = m_sentinel->getNext();
	while (temp != NULL) {
		fout << temp->getUserName() 
			<< " " << temp->getBirth() 
			<< " " << temp->getAddress() << endl;
		temp = temp->getNext();
	}
	fout.close();
}
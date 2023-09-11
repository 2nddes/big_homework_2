#ifndef USER_H
#define USER_H

#include<string>
#include<vector> 
#include"group.h"
#include"friend.h"

class userNodeLA {
protected:
	int m_userId;//�û�ID,Ψһ��ʶ
	string m_userName = "��";//�û���
	int m_birth = 20000101;//����
	int m_TAge = 0;//T��
	string m_address = "��";//��ַ
	bool m_qqActivationStatus = false;//qq����ͨ״̬
	
	static int m_userCount;//�û�����

	userNodeLA* m_next = nullptr;
public:
	userNodeLA();
	userNodeLA(string userName, int birth, string address, userNodeLA* next);
	virtual ~userNodeLA();
	
	int getID();//��ȡ�û�ID	
	string getUserName();//��ȡ�û���
	int getBirth();//��ȡ����
	int getTAge();//��ȡT��
	string getAddress();//��ȡ��ַ
	userNodeLA* getNext();//��ȡ��һ���û�

	void setUserName(string userName);//�����û���	
	void setBirth(int birth);//��������
	void setAddress(string address);//���õ�ַ
	void setNext(userNodeLA* next);//������һ���û�

	bool isQQEnabled();//�ж��Ƿ�ͨqq����
	void setQQStatus(bool status);//����qq����ͨ״̬

};

class userListLA {
private:
	userNodeLA* m_sentinel;

public:
	userListLA();
	virtual ~userListLA();
	
	void loadUserList();
	void saveUserList();

	userNodeLA* addUser(string userName, int birth, string address);
	userNodeLA* findByUserId(int userId);
	userNodeLA* findByUserName(string userName);
};
#endif // !USER_H
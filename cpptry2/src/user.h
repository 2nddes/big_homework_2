#ifndef USER_H
#define USER_H

#include<string>
using namespace std;

class userOfApp {
public:
	virtual int getPlatformId()const = 0;//��ȡƽ̨ID
	virtual int getAppUserId()const = 0;//��ȡӦ��ID
	virtual string getUserName()const = 0;//��ȡ�û���
	virtual string getUserPasswd()const = 0;//��ȡ�û�����


	virtual void setPlatformId(int platformId) = 0;//����ƽ̨ID
	virtual void setAppUserId(int appUserId) = 0;//����Ӧ��ID
	virtual void setUserName(string userName) = 0;//�����û���
	virtual void setUserPasswd(string userPassword) = 0;//�����û�����
protected:
	int m_platformId;//platformID
	
};

class userNodeLA {
public:
	userNodeLA();
	userNodeLA(string userName, int birth, string address, userNodeLA* next);
	virtual ~userNodeLA();
	
	int getID()const;//��ȡ�û�ID	
	string getUserName()const;//��ȡ�û���
	int getBirth()const;//��ȡ����
	int getTAge()const;//��ȡT��
	string getAddress()const;//��ȡ��ַ
	userNodeLA* getNext()const;//��ȡ��һ���û�

	void setUserName(string userName);//�����û���	
	void setBirth(int birth);//��������
	void setAddress(string address);//���õ�ַ
	void setNext(userNodeLA* next);//������һ���û�

	bool isQQEnabled()const;//�ж��Ƿ�ͨqq����
	void setQQStatus(bool status);//����qq����ͨ״̬

protected:
	int m_userId;//�û�ID,Ψһ��ʶ
	string m_userName = "��";//�û���
	int m_birth = 20000101;//����
	int m_TAge = 0;//T��
	string m_address = "��";//��ַ

	bool m_qqActivationStatus = false;//qq����ͨ״̬
	
	static int m_userCount;//�û�����

	userNodeLA* m_next = nullptr;
};

class userListLA {
public:
	userListLA();
	virtual ~userListLA();
	
	void loadUserList();
	void saveUserList()const;

	userNodeLA* addUser();
	userNodeLA* addUser(string userName, int birth, string address);
	userNodeLA* findByUserId(int userId)const;
	userNodeLA* findByUserName(string userName)const;
private:
	userNodeLA* m_sentinel = nullptr;

};
#endif // !USER_H
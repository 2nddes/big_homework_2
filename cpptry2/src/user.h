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
	userNodeLA(int userID, string userName, int birth, string address, userNodeLA* next);
	userNodeLA(int userID, string userName, int birth, string address, bool qqActivationStatus, userNodeLA* next);
	virtual ~userNodeLA();
	
	int getID()const;//��ȡ�û�ID	
	int getBirth()const;//��ȡ����
	int getTAge()const;//��ȡT��
	bool isQQEnabled()const;//�ж��Ƿ�ͨqq����
	string getUserName()const;//��ȡ�û���
	string getAddress()const;//��ȡ��ַ
	userNodeLA* getNext()const;//��ȡ��һ���û�

	void setUserName(string userName);//�����û���
	void setBirth(int birth);//��������
	void setAddress(string address);//���õ�ַ
	void setNext(userNodeLA* next);//������һ���û�
	void setQQStatus(bool status);//����qq����ͨ״̬
	void setPhone(string phoneNumber);//���õ绰����
	void setEmail(string email);//��������

protected:
	int         m_userId;          //�û�ID,Ψһ��ʶ
	string      m_userName = "��"; //�û���
	int         m_birth = 20000101;//����
	int         m_TAge = 0;        //T��
	string      m_address = "��";  //��ַ
	string      m_phoneNumber = ""; //�绰����
	string      m_email = "";      //����
			     
	bool        m_qqActivationStatus = false;//qq����ͨ״̬

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

	int m_userCount = 0;

};
#endif // !USER_H
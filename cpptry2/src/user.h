#ifndef USER_H
#define USER_H

#include<string>
using namespace std;

typedef struct userInfo {
	int friendId{};
	string friendName{};
}userInfo;

class userNodeLA {
public:
	userNodeLA();
	userNodeLA(int userID, string userName, int birth, string address, userNodeLA* next);
	userNodeLA(int userID, string userName, int birth, string address, bool qqActivationStatus, bool WeChatActivationStatus, userNodeLA* next);
	virtual ~userNodeLA();
	
	virtual int getPlatformId()const;//��ȡ�û�ID
	virtual string getUserName()const;//��ȡ�û���
	virtual string getUserPasswd()const;//��ȡ�û�����
	virtual int getAppUserId()const;//��ȡӦ��ID
	virtual void setPlatformId(int platformId);//����ƽ̨ID
	virtual void setAppUserId(int appUserId);//����Ӧ��ID
	virtual void setUserName(string userName);//�����û���
	virtual void setUserPasswd(string userPassword);//�����û�����

	int getBirth()const;//��ȡ����
	int getTAge()const;//��ȡT��
	string getPhone()const;//��ȡ�绰����
	string getEmail()const;//��ȡ����
	bool isQQEnabled()const;//�ж��Ƿ�ͨqq����
	bool isWeChatEnabled()const;//�ж��Ƿ�ͨ΢�ŷ���
	string getAddress()const;//��ȡ��ַ
	userNodeLA* getNext()const;//��ȡ��һ���û�

	void setBirth(int birth);//��������
	void setAddress(string address);//���õ�ַ
	void setNext(userNodeLA* next);//������һ���û�
	void setQQStatus(bool status);//����qq����ͨ״̬
	void setWeChatStatus(bool status);//����΢�ŷ���ͨ״̬
	void setPhone(string phoneNumber);//���õ绰����
	void setEmail(string email);//��������

protected:
	int      m_platformId;       //�û�ID,Ψһ��ʶ
	string   m_userName = "��"; //�û���
	int      m_birth = 20000101;//����
	int      m_TAge = 0;        //T��
	string   m_address = "��";  //��ַ
	string   m_phoneNumber = ""; //�绰����
	string   m_email = "";      //����
		    
	bool     m_qqActivationStatus = false;//qq����ͨ״̬
	bool     m_wechatActivationStatus = false;//΢�ŷ���ͨ״̬

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
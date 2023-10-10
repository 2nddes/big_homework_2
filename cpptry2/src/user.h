#ifndef USER_H
#define USER_H

#include<string>
using namespace std;

class userOfApp {
public:
	virtual int getPlatformId()const = 0;//获取平台ID
	virtual int getAppUserId()const = 0;//获取应用ID
	virtual string getUserName()const = 0;//获取用户名
	virtual string getUserPasswd()const = 0;//获取用户密码


	virtual void setPlatformId(int platformId) = 0;//设置平台ID
	virtual void setAppUserId(int appUserId) = 0;//设置应用ID
	virtual void setUserName(string userName) = 0;//设置用户名
	virtual void setUserPasswd(string userPassword) = 0;//设置用户密码
protected:
	int m_platformId;//platformID
	
};

class userNodeLA {
public:
	userNodeLA();
	userNodeLA(int userID, string userName, int birth, string address, userNodeLA* next);
	userNodeLA(int userID, string userName, int birth, string address, bool qqActivationStatus, userNodeLA* next);
	virtual ~userNodeLA();
	
	int getID()const;//获取用户ID	
	int getBirth()const;//获取生日
	int getTAge()const;//获取T龄
	bool isQQEnabled()const;//判断是否开通qq服务
	string getUserName()const;//获取用户名
	string getAddress()const;//获取地址
	userNodeLA* getNext()const;//获取下一个用户

	void setUserName(string userName);//设置用户名
	void setBirth(int birth);//设置生日
	void setAddress(string address);//设置地址
	void setNext(userNodeLA* next);//设置下一个用户
	void setQQStatus(bool status);//设置qq服务开通状态
	void setPhone(string phoneNumber);//设置电话号码
	void setEmail(string email);//设置邮箱

protected:
	int         m_userId;          //用户ID,唯一标识
	string      m_userName = "无"; //用户名
	int         m_birth = 20000101;//生日
	int         m_TAge = 0;        //T龄
	string      m_address = "无";  //地址
	string      m_phoneNumber = ""; //电话号码
	string      m_email = "";      //邮箱
			     
	bool        m_qqActivationStatus = false;//qq服务开通状态

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
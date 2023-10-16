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
	
	virtual int getPlatformId()const;//获取用户ID
	virtual string getUserName()const;//获取用户名
	virtual string getUserPasswd()const;//获取用户密码
	virtual int getAppUserId()const;//获取应用ID
	virtual void setPlatformId(int platformId);//设置平台ID
	virtual void setAppUserId(int appUserId);//设置应用ID
	virtual void setUserName(string userName);//设置用户名
	virtual void setUserPasswd(string userPassword);//设置用户密码

	int getBirth()const;//获取生日
	int getTAge()const;//获取T龄
	string getPhone()const;//获取电话号码
	string getEmail()const;//获取邮箱
	bool isQQEnabled()const;//判断是否开通qq服务
	bool isWeChatEnabled()const;//判断是否开通微信服务
	string getAddress()const;//获取地址
	userNodeLA* getNext()const;//获取下一个用户

	void setBirth(int birth);//设置生日
	void setAddress(string address);//设置地址
	void setNext(userNodeLA* next);//设置下一个用户
	void setQQStatus(bool status);//设置qq服务开通状态
	void setWeChatStatus(bool status);//设置微信服务开通状态
	void setPhone(string phoneNumber);//设置电话号码
	void setEmail(string email);//设置邮箱

protected:
	int      m_platformId;       //用户ID,唯一标识
	string   m_userName = "无"; //用户名
	int      m_birth = 20000101;//生日
	int      m_TAge = 0;        //T龄
	string   m_address = "无";  //地址
	string   m_phoneNumber = ""; //电话号码
	string   m_email = "";      //邮箱
		    
	bool     m_qqActivationStatus = false;//qq服务开通状态
	bool     m_wechatActivationStatus = false;//微信服务开通状态

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
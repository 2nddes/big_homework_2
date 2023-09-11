#ifndef USER_H
#define USER_H

#include<string>
#include<vector> 
#include"group.h"
#include"friend.h"

class userNodeLA {
protected:
	int m_userId;//用户ID,唯一标识
	string m_userName = "无";//用户名
	int m_birth = 20000101;//生日
	int m_TAge = 0;//T龄
	string m_address = "无";//地址
	bool m_qqActivationStatus = false;//qq服务开通状态
	
	static int m_userCount;//用户总数

	userNodeLA* m_next = nullptr;
public:
	userNodeLA();
	userNodeLA(string userName, int birth, string address, userNodeLA* next);
	virtual ~userNodeLA();
	
	int getID();//获取用户ID	
	string getUserName();//获取用户名
	int getBirth();//获取生日
	int getTAge();//获取T龄
	string getAddress();//获取地址
	userNodeLA* getNext();//获取下一个用户

	void setUserName(string userName);//设置用户名	
	void setBirth(int birth);//设置生日
	void setAddress(string address);//设置地址
	void setNext(userNodeLA* next);//设置下一个用户

	bool isQQEnabled();//判断是否开通qq服务
	void setQQStatus(bool status);//设置qq服务开通状态

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
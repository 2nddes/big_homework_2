#ifndef GROUP_H
#define GROUP_H

#include<string>
#include<vector>
using namespace std;

class groupNodeLA {
protected:
	
	bool m_isAllowJoin = true;//是否允许加入
	bool m_isAllowSubgroup = true;//是否允许创建子群
	bool m_isAllowSend = true;//是否允许发送消息
	bool m_isAllowInvite = true;//是否允许邀请
	bool m_isAllowAdmins = true;//是否有管理员

public:
	groupNodeLA() {};
	virtual ~groupNodeLA() {};
	virtual void addMember(int userId) = 0;
	virtual void removeMember(int userId) = 0;
	virtual void changeOwner(int userId) = 0;
	virtual int getGroupId()const = 0;
	virtual string getGroupName()const = 0;

};
#endif // !GROUP_H
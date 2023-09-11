#ifndef GROUP_H
#define GROUP_H

#include<string>
#include<vector>
using namespace std;

class groupNodeLA {
protected:
	
	bool m_isAllowJoin;//�Ƿ��������
	bool m_isAllowSubgroup;//�Ƿ���������Ⱥ
	bool m_isAllowSend;//�Ƿ���������Ϣ
	bool m_isAllowInvite;//�Ƿ���������
	bool m_isAllowAdmins;//�Ƿ��й���Ա

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
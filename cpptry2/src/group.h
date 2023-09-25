#ifndef GROUP_H
#define GROUP_H

#include<string>
#include<vector>
using namespace std;

class groupNodeLA {
protected:
	
	bool m_isAllowJoin = true;//�Ƿ��������
	bool m_isAllowSubgroup = true;//�Ƿ���������Ⱥ
	bool m_isAllowSend = true;//�Ƿ���������Ϣ
	bool m_isAllowInvite = true;//�Ƿ���������
	bool m_isAllowAdmins = true;//�Ƿ��й���Ա

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
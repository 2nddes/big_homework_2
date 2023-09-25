#ifndef QQGROUP_H
#define QQGROUP_H

#include"group.h"
#include"qquser.h"

class qqGroupNodeLA :public groupNodeLA {
public:
	qqGroupNodeLA();
	qqGroupNodeLA(int qqGroupId, string qqGroupName, int qqGroupOwnerID, qqGroupNodeLA* next);
	virtual ~qqGroupNodeLA();

	int getGroupId()const override;
	string getGroupName()const override;

	bool isAdministrator(int userId)const;
	bool isMember(int userId)const;
	bool isOwner(int userId)const;

	bool isAllowJoin()const;
	bool isAllowSubgroup()const;
	bool isAllowSend()const;
	bool isAllowInvite()const;
	bool isAllowAdmins()const;

	void addMember(int userId)override;//��ӳ�Ա//TODO
	void changeOwner(int userId)override;
	void removeMember(int userId)override;//ע���Ƿ�Ϊ���һ��
	void setQQGroupId(int qqGroupId);
	void setQQGroupName(string qqGroupName);
	void addQQGroupAdmin(int userId);
	void removeQQGroupAdmin(int userId);
	void setQQGroupIsAllowJoin(bool isAllowJoin);
	void setQQGroupIsAllowSubgroup(bool isAllowSubgroup);
	void setQQGroupIsAllowSend(bool isAllowSend);
	void setQQGroupIsAllowInvite(bool isAllowInvite);
	void setQQGroupIsAllowAdmins(bool isAllowAdmins);

	int getQQGroupId()const;
	string getQQGroupName()const;
	vector<userInfo> getQQGroupMemberIDList()const;
	int getQQGroupOwnerID()const;
	vector<userInfo> getQQGroupAdminsIDList()const;
	int getQQGroupMemberCount()const;



	void setNext(qqGroupNodeLA* next);
	qqGroupNodeLA* getNext();
private:
	int m_qqGroupId = 0;//ȺID,Ψһ��ʶ
	string m_qqGroupName = "��";//Ⱥ��
	vector<userInfo> m_qqGroupMemberIDList;//Ⱥ��Ա��Ϣ�б�
	int m_qqGroupOwnerID = 0;//Ⱥ��ID
	vector<userInfo> m_qqGroupAdminsIDList;	//����Ա��Ϣ�б�

	static int m_qqGroupCount;//Ⱥ����
	qqGroupNodeLA* m_next = nullptr;

	friend class qqGroupListLA;
};

class qqGroupListLA {
public:
	qqGroupListLA();
	~qqGroupListLA();

	void saveGroupListData();
	void addGroup(qqGroupNodeLA* node);
	qqGroupNodeLA* addGroup(string qqGroupName, int qqGroupOwnerID);
	void removeGroup(qqGroupNodeLA* node);
	qqGroupNodeLA* findByGroupId(int qqGroupId);
	qqGroupNodeLA* getSentinel();

private:
	qqGroupNodeLA* m_sentinel;


};
#endif // !QQGROUP_H
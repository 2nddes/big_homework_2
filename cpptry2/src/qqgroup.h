#ifndef QQGROUP_H
#define QQGROUP_H

#include"group.h"
#include"qquser.h"

class qqGroupNodeLA :public groupNodeLA {
private:
	int m_qqGroupId = 0;//群ID,唯一标识
	string m_qqGroupName = "无";//群名
	vector<int> m_qqGroupMemberIDList;//群成员ID列表
	int m_qqGroupOwnerID = 0;//群主ID
	vector<int> m_qqGroupAdminsIDList;	//管理员ID列表

	static int m_qqGroupCount;//群总数
	qqGroupNodeLA* m_next = nullptr;

	friend class qqGroupListLA;
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

	void addMember(int userId)override;
	void changeOwner(int userId)override;
	void removeMember(int userId)override;
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
	vector<int> getQQGroupMemberIDList()const;
	int getQQGroupOwnerID()const;
	vector<int> getQQGroupAdminsIDList()const;
	int getQQGroupMemberCount()const;



	void setNext(qqGroupNodeLA* next);
	qqGroupNodeLA* getNext();
};

class qqGroupListLA {
private:
	qqGroupNodeLA* m_sentinel;


public:
	qqGroupListLA();
	~qqGroupListLA();

	void saveGroupListData();
	void addGroup(qqGroupNodeLA* node);
	void removeGroup(qqGroupNodeLA* node);
	qqGroupNodeLA* findByGroupId(int qqGroupId);
	qqGroupNodeLA* getSentinel();

};
#endif // !QQGROUP_H
#ifndef QQGROUP_H
#define QQGROUP_H

#include"/project/C++Project/cpptry2/cpptry2/src/group.h"
#include"qquser.h"

class qqGroupNodeLA :public groupNodeLA {
public:
	qqGroupNodeLA();
	qqGroupNodeLA(int qqGroupId, string qqGroupName, int qqGroupOwnerID, qqGroupNodeLA* next);
	virtual ~qqGroupNodeLA();

	int    getGroupId()const override;
	string getGroupName()const override;

	bool isAdministrator(int userId)const;
	bool isMember(int userId)const;
	bool isOwner(int userId)const;

	bool isAllowJoin()const;
	bool isAllowSubgroup()const;
	bool isAllowSend()const;
	bool isAllowInvite()const;
	bool isAllowAdmins()const;

	void addMember(int userId)override;//添加成员
	void changeOwner(int userId)override;
	void removeMember(int userId)override;//注意是否为最后一人
	void removeMember(vector<int> userIdList);//注意是否为最后一人
	void setQQGroupId(int qqGroupId);
	void setQQGroupName(string qqGroupName);
	void addQQGroupAdmin(int userId);
	void addRequest(userInfo userinfo);//添加申请人
	void removeRequest(int userId);//删除申请人
	void removeQQGroupAdmin(int userId);
	void setQQGroupIsAllowJoin(bool isAllowJoin);
	void setQQGroupIsAllowSubgroup(bool isAllowSubgroup);
	void setQQGroupIsAllowSend(bool isAllowSend);
	void setQQGroupIsAllowInvite(bool isAllowInvite);
	void setQQGroupIsAllowAdmins(bool isAllowAdmins);
	void setMemberName(int userId, string userName);
	void setGroupNickName(int userId, string groupNickName);

	int getQQGroupId()const;
	int getQQGroupMemberCount()const;
	int getQQGroupOwnerID()const;
	string getQQGroupName()const;
	string getGroupNickName(int userId)const;
	vector<userInfo> getQQGroupMemberInfoList()const;
	vector<userInfo> getQQGroupAdminsInfoList()const;
	vector<userInfo> getQQGroupRequestInfoList()const;



	void setNext(qqGroupNodeLA* next);
	qqGroupNodeLA* getNext();
private:
	int              m_qqGroupId = 0;//群ID,唯一标识
	string           m_qqGroupName = "无";//群名
	int              m_qqGroupOwnerID = 0;//群主ID
	vector<userInfo> m_qqGroupMemberInfoList;//群成员信息列表,包括管理员群主
	vector<userInfo> m_qqGroupAdminsIDList;	//管理员信息列表
	vector<userInfo> m_qqGroupInvitedIDList;//申请人信息列表

	qqGroupNodeLA*   m_next = nullptr;

	friend class qqGroupListLA;
};

class qqGroupListLA {
public:
	qqGroupListLA();
	~qqGroupListLA();

	void saveGroupListData()const;
	void addGroup(qqGroupNodeLA* node);
	void removeGroup(qqGroupNodeLA* node);

	qqGroupNodeLA* addGroup(string qqGroupName, int qqGroupOwnerID);
	qqGroupNodeLA* findByGroupId(int qqGroupId)const;
	qqGroupNodeLA* getSentinel()const;
	int size()const;
private:
	qqGroupNodeLA* m_sentinel;

	int m_qqGroupCount = 1001;
};
#endif // !QQGROUP_H
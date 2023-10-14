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

	void addMember(int userId)override;//��ӳ�Ա
	void changeOwner(int userId)override;
	void removeMember(int userId)override;//ע���Ƿ�Ϊ���һ��
	void removeMember(vector<int> userIdList);//ע���Ƿ�Ϊ���һ��
	void setQQGroupId(int qqGroupId);
	void setQQGroupName(string qqGroupName);
	void addQQGroupAdmin(int userId);
	void addRequest(userInfo userinfo);//���������
	void removeRequest(int userId);//ɾ��������
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
	int              m_qqGroupId = 0;//ȺID,Ψһ��ʶ
	string           m_qqGroupName = "��";//Ⱥ��
	int              m_qqGroupOwnerID = 0;//Ⱥ��ID
	vector<userInfo> m_qqGroupMemberInfoList;//Ⱥ��Ա��Ϣ�б�,��������ԱȺ��
	vector<userInfo> m_qqGroupAdminsIDList;	//����Ա��Ϣ�б�
	vector<userInfo> m_qqGroupInvitedIDList;//��������Ϣ�б�

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
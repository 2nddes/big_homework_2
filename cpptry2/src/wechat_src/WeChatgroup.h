#ifndef WeChatGROUP_H
#define WeChatGROUP_H

#include"/project/C++Project/cpptry2/cpptry2/src/group.h"
#include"WeChatuser.h"

class WeChatGroupNodeLA :public groupNodeLA {
public:
	WeChatGroupNodeLA();
	WeChatGroupNodeLA(int WeChatGroupId, string WeChatGroupName, int WeChatGroupOwnerID, WeChatGroupNodeLA* next);
	virtual ~WeChatGroupNodeLA();

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
	void setWeChatGroupId(int WeChatGroupId);
	void setWeChatGroupName(string WeChatGroupName);
	void addWeChatGroupAdmin(int userId);
	void addRequest(userInfo userinfo);//���������
	void removeRequest(int userId);//ɾ��������
	void removeWeChatGroupAdmin(int userId);
	void setWeChatGroupIsAllowJoin(bool isAllowJoin);
	void setWeChatGroupIsAllowSubgroup(bool isAllowSubgroup);
	void setWeChatGroupIsAllowSend(bool isAllowSend);
	void setWeChatGroupIsAllowInvite(bool isAllowInvite);
	void setWeChatGroupIsAllowAdmins(bool isAllowAdmins);
	void setMemberName(int userId, string userName);
	void setGroupNickName(int userId, string groupNickName);

	int getWeChatGroupId()const;
	int getWeChatGroupMemberCount()const;
	int getWeChatGroupOwnerID()const;
	string getWeChatGroupName()const;
	string getGroupNickName(int userId)const;
	vector<userInfo> getWeChatGroupMemberInfoList()const;
	vector<userInfo> getWeChatGroupAdminsInfoList()const;
	vector<userInfo> getWeChatGroupRequestInfoList()const;



	void setNext(WeChatGroupNodeLA* next);
	WeChatGroupNodeLA* getNext();
private:
	int              m_WeChatGroupId = 0;//ȺID,Ψһ��ʶ
	string           m_WeChatGroupName = "��";//Ⱥ��
	int              m_WeChatGroupOwnerID = 0;//Ⱥ��ID
	vector<userInfo> m_WeChatGroupMemberInfoList;//Ⱥ��Ա��Ϣ�б�,��������ԱȺ��
	vector<userInfo> m_WeChatGroupAdminsIDList;	//����Ա��Ϣ�б�
	vector<userInfo> m_WeChatGroupInvitedIDList;//��������Ϣ�б�

	WeChatGroupNodeLA* m_next = nullptr;

	friend class WeChatGroupListLA;
};

class WeChatGroupListLA {
public:
	WeChatGroupListLA();
	~WeChatGroupListLA();

	void saveGroupListData();
	void addGroup(WeChatGroupNodeLA* node);
	void removeGroup(WeChatGroupNodeLA* node);

	WeChatGroupNodeLA* addGroup(string WeChatGroupName, int WeChatGroupOwnerID);
	WeChatGroupNodeLA* findByGroupId(int WeChatGroupId);
	WeChatGroupNodeLA* getSentinel();
	int size()const;
private:
	WeChatGroupNodeLA* m_sentinel;

	int m_WeChatGroupCount = 1001;
};
#endif // !WeChatGROUP_H
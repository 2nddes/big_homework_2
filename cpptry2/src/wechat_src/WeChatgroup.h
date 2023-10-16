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

	void addMember(int userId)override;//添加成员
	void changeOwner(int userId)override;
	void removeMember(int userId)override;//注意是否为最后一人
	void removeMember(vector<int> userIdList);//注意是否为最后一人
	void setWeChatGroupId(int WeChatGroupId);
	void setWeChatGroupName(string WeChatGroupName);
	void addWeChatGroupAdmin(int userId);
	void addRequest(userInfo userinfo);//添加申请人
	void removeRequest(int userId);//删除申请人
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
	int              m_WeChatGroupId = 0;//群ID,唯一标识
	string           m_WeChatGroupName = "无";//群名
	int              m_WeChatGroupOwnerID = 0;//群主ID
	vector<userInfo> m_WeChatGroupMemberInfoList;//群成员信息列表,包括管理员群主
	vector<userInfo> m_WeChatGroupAdminsIDList;	//管理员信息列表
	vector<userInfo> m_WeChatGroupInvitedIDList;//申请人信息列表

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
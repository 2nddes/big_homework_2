#ifndef APPLICATIONWECHAT_H
#define APPLICATIONWECHAT_H

#include"/project/C++Project/cpptry2/cpptry2/src/application.h"
#include"WeChatuser.h"
#include"WeChatgroup.h"
#include"/project/C++Project/cpptry2/cpptry2/src/utils.h"

#include<Windows.h>
#include<io.h>
#include<direct.h>

typedef struct WECHATMsgNodeLA {
	int senderId{};
	string senderName{};
	string time{};
	string msg{};
}WMsg;

class applicationWeChatLA :public applicationLA {
public:
	applicationWeChatLA();
	applicationWeChatLA(platformLA* platform);
	virtual ~applicationWeChatLA();

	bool init(userNodeLA*& curPlatformUser)override;//�������ݺͳ�ʼ����
	void exit()override;//������ص�����
	void mainPage() override;//������
	void loadData() override;//��������
	void logOut() override;//ע��

	string getAppName()const override;//��ȡӦ����
	int getAppVersion()const override;//��ȡӦ�ð汾

	//����Ϊƽ̨�û�,��¼�󷵻�WeChat�û�,ͬʱ��¼ƽ̨�û�
	WeChatUserNodeLA* loginPage(userNodeLA*& curPlatformUser);
	WeChatUserNodeLA* registerPage(userNodeLA*& curPlatformUser);

	WeChatUserNodeLA* findBySuperPtr(userNodeLA* superPtr)const override;//ͨ����ָ������û�
	WeChatUserNodeLA* findByWeChatId(int id)const;

	void showPersonalInfoPage(WeChatUserNodeLA* userPtr)const;//��ʾ������Ϣ

	void setUserInfoPage();//�����û���Ϣ

	void friendPage();//���Ѹ�����
	void selectFriendPage();//ѡ�����
	void sendMsgPage(WeChatUserNodeLA* friendPtr);
	void addFriendPage();//��Ӻ���
	void deleteFriendPage();//ɾ������
	bool deleteFriendPage(WeChatUserNodeLA* friendPtr);//ɾ������
	void friendRequestPage();//���ĺ�������
	void chatWithFriendPage(WeChatUserNodeLA* friendPtr);//�����������
	void addExternQQFriendPage();//����ⲿQQ����
	void addBySearchFriendNamePage();//��������
	void addByWeChatIdPage();//ͨ��΢�ź���Ӻ���
	void searchChatRecordPage(WeChatUserNodeLA* friendPtr);//���������¼

	void groupPage();//Ⱥ������
	void selectGroupPage();//ѡ��Ⱥ
	void searchGroupPage();//����Ⱥ
	void sendMsgPage(WeChatGroupNodeLA* groupPtr);//����Ⱥ��Ϣ
	void createGroupPage();//����Ⱥ
	void joinGroupPage();//����Ⱥ,����������Ⱥ��
	bool disbandGroupPage(WeChatGroupNodeLA* groupPtr);//��ɢȺ
	bool quitGroupPage();//�˳�Ⱥ,����������Ⱥ��
	bool quitGroupPage(WeChatGroupNodeLA* groupPtr);//�˳�Ⱥ
	void setGroupConfigPage(WeChatGroupNodeLA* groupPtr);//����Ⱥ����
	void inviteFriendInPage(WeChatGroupNodeLA* groupPtr);//������ѽ�Ⱥ
	void kickMemberPage(WeChatGroupNodeLA* groupPtr);//�߳�Ⱥ��Ա
	void groupRequestPage(WeChatGroupNodeLA* groupPtr);//����Ⱥ����
	void chatInGroupPage(WeChatGroupNodeLA* groupPtr);//Ⱥ�������
	void setAdminPage(WeChatGroupNodeLA* groupPtr);//���ù���Ա
	void setGroupNickNamePage(WeChatGroupNodeLA* groupPtr);//����Ⱥ�ǳ�
	void searchChatRecordPage(WeChatGroupNodeLA* groupPtr);//����Ⱥ�����¼

private:
	void makeUserFile(string path);//�����û��ļ�

	void clearChatRecord(WeChatUserNodeLA* friendPtr);//��������¼

	void clearChatRecord(WeChatGroupNodeLA* groupPtr);//��������¼

	void showWeChatFriendList(const vector<userInfo>& friendlist);//��ʾ�����б�
	void showWeChatGroupList(const vector<int>& grouplist);//��ʾȺ�б�
	void showGroupMemberList(int groupId);//��ʾȺ��Ա
	void showGroupMemberList(WeChatGroupNodeLA* groupPtr);//��ʾȺ��Ա
	//�������
	void applyFriend(WeChatUserNodeLA* user, WeChatUserNodeLA* friendToAdd);
	//���ͺ�����Ϣ
	bool sendMsgToFriend(WeChatUserNodeLA* friendPtr, const char* msg);
	//��Ⱥ��Ϣ
	bool sendMsgToGroup(WeChatGroupNodeLA* groupPtr, const char* msg);

	vector<WMsg> recvMsgFromFriend(WeChatUserNodeLA* friendPtr);//���պ�����Ϣ
	vector<WMsg> recvMsgFromGroup(WeChatGroupNodeLA* groupPtr);//����Ⱥ��Ϣ
	void loadUserFile();//�����û��ļ�
	void loadGroupFile();//����Ⱥ�ļ�

	void showMsg(const vector<WMsg>& m);//��ʾ��Ϣ
	
protected:
	WeChatUserNodeLA* m_currentUser = nullptr;//��ǰ�û�

	WeChatGroupListLA* m_allWeChatGroupList = nullptr;//����Ⱥ�б�

	WeChatUserListLA* m_allWeChatUserList = nullptr;//�����û��б�

	platformLA* m_platform = nullptr;//����ƽ̨
};

#endif // !APPLICATIONWECHAT_H
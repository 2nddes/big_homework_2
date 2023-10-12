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

	string getAppName()const override;//��ȡӦ����
	int getAppVersion()const override;//��ȡӦ�ð汾

	//����Ϊƽ̨�û�,��¼�󷵻�WeChat�û�,ͬʱ��¼ƽ̨�û�
	WeChatUserNodeLA* loginPage(userNodeLA*& curPlatformUser);
	WeChatUserNodeLA* registerPage(userNodeLA*& curPlatformUser);

	void mainPage();

	void setUserInfoPage();//�����û���Ϣ

	void friendPage();//���Ѹ�����
	void selectFriendPage();//ѡ�����
	void sendMsgPage(WeChatUserNodeLA* friendPtr);
	void addFriendPage();//��Ӻ���
	void deleteFriendPage();//ɾ������
	void friendRequestPage();//���ĺ�������
	void chatWithFriendPage(WeChatUserNodeLA* friendPtr);//�����������

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

	//TODO:��������
	void makeUserFile(string path);//�����û��ļ�

	void showWeChatFriendList(vector<userInfo> friendlist);//��ʾ�����б�
	void showWeChatGroupList(vector<int> grouplist);//��ʾȺ�б�
	void showGroupMemberPage(int groupId);//��ʾȺ��Ա
	void showGroupMemberPage(WeChatGroupNodeLA* groupPtr);//��ʾȺ��Ա
	//�������
	void applyFriend(WeChatUserNodeLA* user, WeChatUserNodeLA* friendToAdd);
	//���ͺ�����Ϣ
	bool sendMsgToFriend(WeChatUserNodeLA* friendPtr, const char* msg);
	//��Ⱥ��Ϣ
	bool sendMsgToGroup(WeChatGroupNodeLA* groupPtr, const char* msg);

	vector<WMsg> recvMsgFromFriend(WeChatUserNodeLA* friendPtr);//���պ�����Ϣ
	vector<WMsg> recvMsgFromGroup(WeChatGroupNodeLA* groupPtr);//����Ⱥ��Ϣ

	void showMsg(vector<WMsg> m);//��ʾ��Ϣ
	//�������ݺͳ�ʼ����
	bool init(userNodeLA*& curPlatformUser)override;
	//������ص�����
	void exit()override;

private:
	WeChatUserNodeLA* m_currentUser = nullptr;//��ǰ�û�

	WeChatGroupListLA* m_allWeChatGroupList = nullptr;//����Ⱥ�б�

	WeChatUserListLA* m_allWeChatUserList = nullptr;//�����û��б�

	platformLA* m_platform = nullptr;//����ƽ̨
};

#endif // !APPLICATIONWECHAT_H
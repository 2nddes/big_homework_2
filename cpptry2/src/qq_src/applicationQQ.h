#ifndef APPLICATIONQQ_H
#define APPLICATIONQQ_H

#include"/project/C++Project/cpptry2/cpptry2/src/application.h"
#include"qquser.h"
#include"qqgroup.h"
#include"/project/C++Project/cpptry2/cpptry2/src/utils.h"

#include<Windows.h>
#include<io.h>
#include<direct.h>

typedef struct QQMsgNodeLA {
	int senderId{};
	string senderName{};
	string time{};
	string msg{};
}QMsg;

class applicationQQLA :public applicationLA {
public:
	applicationQQLA();
	applicationQQLA(platformLA* platform);
	virtual ~applicationQQLA();

	string getAppName()const override;//��ȡӦ����
	int getAppVersion()const override;//��ȡӦ�ð汾

	//����Ϊƽ̨�û�,��¼�󷵻�qq�û�,ͬʱ��¼ƽ̨�û�
	qqUserNodeLA* loginPage(userNodeLA*& curPlatformUser);
	qqUserNodeLA* registerPage(userNodeLA*& curPlatformUser);
	
	void mainPage();

	void setUserInfoPage();//�����û���Ϣ

	void friendPage();//���Ѹ�����
	void selectFriendPage();//ѡ�����
	void sendMsgPage(qqUserNodeLA* friendPtr);
	void addFriendPage();//��Ӻ���
	void deleteFriendPage();//ɾ������
	void friendRequestPage();//���ĺ�������
	void chatWithFriendPage(qqUserNodeLA* friendPtr);//�����������

	void groupPage();//Ⱥ������
	void selectGroupPage();//ѡ��Ⱥ
	void searchGroupPage();//����Ⱥ
	void sendMsgPage(qqGroupNodeLA* groupPtr);//����Ⱥ��Ϣ
	void createGroupPage();//����Ⱥ
	void joinGroupPage();//����Ⱥ,����������Ⱥ��
	bool disbandGroupPage(qqGroupNodeLA* groupPtr);//��ɢȺ
	bool quitGroupPage();//�˳�Ⱥ,����������Ⱥ��
	bool quitGroupPage(qqGroupNodeLA* groupPtr);//�˳�Ⱥ
	void setGroupConfigPage(qqGroupNodeLA* groupPtr);//����Ⱥ����
	void inviteFriendInPage(qqGroupNodeLA* groupPtr);//������ѽ�Ⱥ
	void kickMemberPage(qqGroupNodeLA* groupPtr);//�߳�Ⱥ��Ա
	void groupRequestPage(qqGroupNodeLA* groupPtr);//����Ⱥ����
	void chatInGroupPage(qqGroupNodeLA* groupPtr);//Ⱥ�������
	void setAdminPage(qqGroupNodeLA* groupPtr);//���ù���Ա
	void setGroupNickNamePage(qqGroupNodeLA* groupPtr);//����Ⱥ�ǳ�

	//TODO:��������
	void makeUserFile(string path);//�����û��ļ�

	void showQQFriendList(vector<userInfo> friendlist);//��ʾ�����б�
	void showQQGroupList(vector<int> grouplist);//��ʾȺ�б�
	void showGroupMemberPage(int groupId);//��ʾȺ��Ա
	void showGroupMemberPage(qqGroupNodeLA* groupPtr);//��ʾȺ��Ա
	//�������
	void applyFriend(qqUserNodeLA* user,qqUserNodeLA* friendToAdd);
	//���ͺ�����Ϣ
	bool sendMsgToFriend(qqUserNodeLA* friendPtr,const char* msg);
	//��Ⱥ��Ϣ
	bool sendMsgToGroup(qqGroupNodeLA* groupPtr,const char* msg);
	
	vector<QMsg> recvMsgFromFriend(qqUserNodeLA* friendPtr);//���պ�����Ϣ
	vector<QMsg> recvMsgFromGroup(qqGroupNodeLA* groupPtr);//����Ⱥ��Ϣ

	void showMsg(vector<QMsg> m);//��ʾ��Ϣ
	//�������ݺͳ�ʼ����
	bool init(userNodeLA*& curPlatformUser)override;
	//������ص�����
	void exit()override;

private:
	qqUserNodeLA*  m_currentUser = nullptr;//��ǰ�û�

	qqGroupListLA* m_allQQGroupList = nullptr;//����Ⱥ�б�

	qqUserListLA*  m_allQQUserList = nullptr;//�����û��б�

	platformLA*    m_platform = nullptr;//����ƽ̨
};

#endif // !APPLICATIONQQ_H
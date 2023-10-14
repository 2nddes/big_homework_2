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

	
	bool init(userNodeLA*& curPlatformUser)override;//�������ݺ͵�¼����
	void exit()override;//������ص�����
	void loadData()override;//��������
	void logOut()override;//�ǳ�
	void mainPage()override;//������
	
	string getAppName()const override;//��ȡӦ����
	int getAppVersion()const override;//��ȡӦ�ð汾

	qqUserNodeLA* findBySuperPtr(userNodeLA* superPtr)const override;//ͨ����ָ������û�
	qqUserNodeLA* findByQQId(int id)const;

	//����Ϊƽ̨�û�,��¼�󷵻�qq�û�,ͬʱ��¼ƽ̨�û�
	qqUserNodeLA* loginPage(userNodeLA*& curPlatformUser);
	qqUserNodeLA* registerPage(userNodeLA*& curPlatformUser);
	


	void setUserInfoPage();//�����û���Ϣ

	void friendPage();//���Ѹ�����
	void selectFriendPage();//ѡ�����
	void sendMsgPage(qqUserNodeLA* friendPtr);
	void addFriendPage();//��Ӻ���
	void deleteFriendPage();//ɾ������
	void friendRequestPage();//���ĺ�������
	void chatWithFriendPage(qqUserNodeLA* friendPtr);//�����������
	void addExternWeChatFriendPage();//����ⲿWeChat����
	void addBySearchFriendNamePage();//��������
	void addByQQIdPage();//ͨ��QQ����Ӻ���

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


private:
	//TODO:��������
	void makeUserFile(string path)const;//�����û��ļ�

	void showQQFriendList(vector<userInfo> friendlist)const; //��ʾ�����б�
	void showQQGroupList(vector<int> grouplist)const; //��ʾȺ�б�
	void showGroupMemberList(int groupId)const; //��ʾȺ��Ա
	void showGroupMemberList(qqGroupNodeLA* groupPtr)const; //��ʾȺ��Ա
	//�������
	void applyFriend(qqUserNodeLA* user,qqUserNodeLA* friendToAdd);
	//���ͺ�����Ϣ
	bool sendMsgToFriend(qqUserNodeLA* friendPtr,const char* msg);
	//��Ⱥ��Ϣ
	bool sendMsgToGroup(qqGroupNodeLA* groupPtr,const char* msg);
	
	vector<QMsg> recvMsgFromFriend(qqUserNodeLA* friendPtr);//���պ�����Ϣ
	vector<QMsg> recvMsgFromGroup(qqGroupNodeLA* groupPtr);//����Ⱥ��Ϣ
	void loadUserFile();//�����û��ļ�
	void loadGroupFile();//����Ⱥ�ļ�

	void showMsg(vector<QMsg> m);//��ʾ��Ϣ

private:
	qqUserNodeLA*  m_currentUser = nullptr;//��ǰ�û�

	qqGroupListLA* m_allQQGroupList = nullptr;//����Ⱥ�б�

	qqUserListLA*  m_allQQUserList = nullptr;//�����û��б�

	platformLA*    m_platform = nullptr;//����ƽ̨
};

#endif // !APPLICATIONQQ_H
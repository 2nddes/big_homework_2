#include"applicationQQ.h"
#include<iostream>


applicationQQLA::applicationQQLA() {
	
}

applicationQQLA::~applicationQQLA() {
	
}

string applicationQQLA::getAppName()const {
	return "QQ";
}

int applicationQQLA::getAppVersion()const {
	return m_appVersion;
}

void applicationQQLA::init(userNodeLA*& curPlatformUser) {
	m_allQQGroupList = new qqGroupListLA();

	m_allQQUserList = new qqUserListLA();

	if (curPlatformUser == nullptr) {
		m_currentUser = loginPage(curPlatformUser);
	}
	else {
		if (curPlatformUser->isQQEnabled()) {
			m_currentUser = m_allQQUserList->findBySuperPointer(curPlatformUser);
		}
		else {
			cout << "ƽ̨�û� "
				<< curPlatformUser->getUserName() 
				<< " δ��ͨQQ����,�Ƿ�ͨ" << endl;
			cout << "1.��ͨ" << endl;
			cout << "2.����ͨ" << endl;
			int i = 2;
			cin >> i;
			if (i == 1) {
				m_currentUser = registerPage(curPlatformUser);
				if(m_currentUser == nullptr) {
					exit();
					return;
				}
				else {
					curPlatformUser->setQQStatus(true);
				}
			}
			else {
				exit();
				return;

			}
		}
	}
	//TODO
	//��������Ⱥ����Ϣ
	//��������qq�û���Ϣ
	//qq���˺�����Ϣ��Ⱥ����Ϣ�����ڸ��˽ṹ����
	//���Ƿ�װ������Ϣ��Ⱥ����ϢΪ�����ٱ�����qq�û��ṹ����

}

qqUserNodeLA* applicationQQLA::loginPage(userNodeLA*& curPlatformUser) {
	while(m_currentUser == nullptr)
	{
		cout << "QQ��¼��1,ע��QQ��2,�˳���3" << endl;
		int i = 0;
		cin >> i;
		if (i == 2) {
			m_currentUser = registerPage(curPlatformUser);
		}
		else if (i == 3) {
			exit();
			return nullptr;
		}
	}

	cout << "������QQ��" << endl;
	int qqNumber;
	cin >> qqNumber;
	cout << "����������" << endl;
	string password;
	cin >> password;

	qqUserNodeLA* qqUser = m_allQQUserList->findByQQId(qqNumber);
	if (qqUser == nullptr) {
		cout << "QQ�Ų�����" << endl;
		return nullptr;
	}
	else {
		if (qqUser->getQQPassword() == password) {
			cout << "��¼�ɹ�" << endl;
			return qqUser;
		}
		else {
			cout << "�������" << endl;
			return nullptr;
		}
	}
}

qqUserNodeLA* applicationQQLA::registerPage(userNodeLA*& curPlatformUser) {
	cout << "QQע�������(�����ȵ�¼�������з����ٽ���QQע��) �˳�1" << endl;
	int i = 0;
	cin >> i;
	if (i == 1)
		return nullptr;

	cout << "�����ǳ�" << endl;
	string userName;
	cin >> userName;
	cout << "��������" << endl;
	string password;
	cin >> password;
	cout << "ȷ��ע�ᰴ1" << endl;
	i = 0;
	cin >> i;
	if(i == 1) {
		return m_allQQUserList->addQQUser(userName,password);
	}
	else {
		cout << "ȡ��ע��" << endl;
		return nullptr;
	}
}

void applicationQQLA::exit() {
	cout << "�����˳�QQ" << endl;

	delete m_allQQGroupList;
	delete m_allQQUserList;
}
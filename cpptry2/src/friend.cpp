#include"friend.h"

friendNodeLA::friendNodeLA() {
	m_commentName = "��";
	m_next = nullptr;
}

friendNodeLA::friendNodeLA(userListLA* friendUser, string commentName, friendNodeLA* next) {
	m_commentName = commentName;
	m_next = next;
}

friendNodeLA::~friendNodeLA() {

}


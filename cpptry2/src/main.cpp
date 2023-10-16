#include"platform.h"

int main(void) {
	system("color F0");

	platformLA* p = new platformLA();
	p->run();
	
	delete p;

	return 0;
}
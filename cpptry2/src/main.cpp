#include"platform.h"

int main(void) {

	platformLA* p = new platformLA();
	p->run();
		
	delete p;

	return 0;
}
#include "stdfx.h"


int main() {
	Linkedlist<int>* L1 = new Linkedlist<int>;
	int a;
	L1->Insert(0x10);
	L1->Insert(0x11);
	L1->Insert(0x12);
	L1->Insert(0x13);
	L1->Insert(0x14);
	L1->Insert(1,0x200);
	L1->Delete(3);
	L1->GetElement(3, a);
	std::cout << L1->GetSize() << std::endl << a << std::endl;
}
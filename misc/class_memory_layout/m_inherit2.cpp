#include <iostream>
using namespace std;

class A {
public:
	virtual void print(){
		cout << "A print\n";
	}
	virtual void af() {
		cout << "af function\n";
	}
private:
	long ia{11};
};

class B {
public:
	virtual void print() {
		cout << "B print\n";
	}
	virtual void bf() {
		cout << "bf function\n";
	}
private:
	long ib{22};
};

class C : public A, public B {
public:
	virtual void print() {
		cout << "C print\n";
	}
	virtual void cf() {
		cout << "cf function\n";
	}
private:
	long ic{33};
};

typedef void (*fn)();
//
int main() {
	C c;
    cout << "sizeof(int)=" << sizeof(int) << endl;
	cout << "sizeof(long*)=" << sizeof(long*) << endl;
	long* p = (long*)&c;
	long* virtual_tbl_ptr = (long*)*p;
	fn f = (fn)*virtual_tbl_ptr;
	f();

	fn af = (fn)*(virtual_tbl_ptr + 1);
	af();

	fn cf = (fn)*(virtual_tbl_ptr + 2);
	cf();

	//ia
	cout << *(p+1) << endl;

	// cout << *(p+2) << endl;
	//second virtual table pointer
	long* virtual_tbl_ptr2 = (long*)*(p + 2);
	fn f2 = (fn)*virtual_tbl_ptr2;
	f2();

    fn bf = (fn)*(virtual_tbl_ptr2 + 1);
	bf();

    //don't has cf function
    // fn cf2 = (fn)*(virtual_tbl_ptr2 + 2);
	// cf2();

    //ib
    cout << *(p+3) << endl;

    //ic
    cout << *(p+4) << endl;

    return 0;
}

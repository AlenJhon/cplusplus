#include "concrete_subject.h"
#include "concrete_observer.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) {delete (p); (p)=NULL;} }
#endif //SAFE_DELETE


int main() {
    //create subject 
    concrete_subject *ptr_subject = new concrete_subject();

    //create observer
    iobserver *pobserver1 = new concrete_observer("zhang san");
    iobserver *pobserver2 = new concrete_observer("li si");

    ptr_subject->attach(pobserver1);
    ptr_subject->attach(pobserver2);

    ptr_subject->set_price(123456.7);
    ptr_subject->notify();


    ptr_subject->detach(pobserver1);
    ptr_subject->set_price(654321.0);
    ptr_subject->notify();

    SAFE_DELETE(ptr_subject);
    SAFE_DELETE(pobserver1);
    SAFE_DELETE(pobserver2);
    return 0;
}
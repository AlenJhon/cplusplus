#include <iostream>
#include <queue>


int main(){
	
	std::priority_queue<int> mypq;
	mypq.push(30);
	mypq.push(100);
	std::cout << "top=" << mypq.top() << std::endl;
	mypq.push(40);
	mypq.push(140);
	mypq.push(240);
	mypq.push(340);
	mypq.push(440);
	std::cout << "top=" << mypq.top() << " , size=" << mypq.size() << std::endl;

	//mypq.pop_back();
	//std::cout << "top=" << mypq.top() << std::endl;


	return 0;
}

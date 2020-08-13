#include <iostream>
#include "rbtree_cpp.h"

using namespace std;

int main()
{
	const int NEG_INF = -99999;
	RedBlackTree<int> t(NEG_INF);

	t.insert(50);
	t.insert(40);
	t.insert(30);
	
	//cout << t.header->right->element << endl;

	if(!t.isEmpty()) cout << "红黑树不是空的" << endl;

	t.makeEmpty();
	if(t.isEmpty()) cout << "红黑树是空的" << endl;

	t.insert(200);
	t.insert(100);
	t.insert(90);
	t.insert(50);
	t.insert(80);
	t.insert(70);
	t.insert(60);

	if(t.findMin().get() == 50) cout << "找到了最小的数" << endl;

	cout << "最大的: " << t.findMax().get() << endl;

	Cref<int> r = t.find(80);

	if(r.isNull())
	{
		cout << "没找到!" << endl;
	}
	else
	{
		cout << "找到: " << r.get() << endl;
	}


	t.remove(100);
	cout << "最大的: " << t.findMax().get() << endl;
	


	cout << "OK" << endl;
	return 0;
}

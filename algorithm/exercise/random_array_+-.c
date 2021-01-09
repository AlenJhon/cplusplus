#include <stdio.h>

void show(int* arr, int len);


//1 2 3 -2 -4 -> 1 -2 2 -4 3
//下面的算法重复的在做一个动作是

//1 2 3 -2 -4 -> 1 -2 2 3 -4
//从上面的这个过程转换
//循环第一次发现第一个位置就是1，进入下一个循环，
//在第二次循环中发现2不是预期的负数将从它后面开始，也就是第三个数开始找到第一个负数拿到第二个位置来，然后将所有的正数往后面移动一位
void proc(int* arr, int len) 
{
	bool op = true; // true +, false -
	//从头开始遍历数组 i表示遍历的下标
	for (int i = 0; i < len; ++i) 
	{
		//show(arr, len);
		if (op == true) //op的状态是在true和false两个状态直接来回切换
		{
			if (arr[i] > 0) //大于0表示正数直接跳过遍历下一个
			{
				op = false;
				continue;
			}
			
			//遇到非期望的数值，比方说这个位置是正数而且现在放的是负数的，
			//应该向后面找第一个正数放在这个位置，然后将移动距离之间的负数往后移动一位确保相对位置不变
			int tmp = arr[i];//-
			//寻找正数并将第一个正数放到前面位置
			for (int j = i + 1; j < len; ++j) 
			{
				if (arr[j] > 0 ) //找到正数了
				{
					arr[i] = arr[j];//前置,将向后遍历遇到的第一个正数前置
					
					int pre_idx = j;//可写入数据位置，j位置前置了，空出位置了
					//将i到j之间的负数向后移动一个位置
					for (int k = j-1; k > i; --k)
					{
						if (arr[k] < 0)//
						{
							arr[pre_idx] = arr[k];
							pre_idx = k;//记录下一次可以覆盖的位置
						}
					}
					arr[pre_idx] = tmp;//
					op = false;//切换状态
					break;//记得退出循环
				}
			}
		}
		else 
		{
			if (arr[i] < 0) 
			{
				op = true;
				continue;
			}
		
			int tmp = arr[i]; // +
			//寻找负数
			for (int j=i+1; j < len; ++j)
			{
				if (arr[j] < 0)
				{
					arr[i] = arr[j];//前置
					
					int pre_idx = j;
					for (int k=j-1; k > i; --k)
					{
						if (arr[k] > 0 ) {
							arr[pre_idx] = arr[k];
							pre_idx = k;
						}
					}
					arr[pre_idx] = tmp;
					op = true;
					break;
				}
			}
		}
		//show(arr, len);
	}
}

void show(int* arr, int len) {
	for( int i = 0; i < len; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main(){
	int arr[] = {1,2,3,-2,-4,-6,7,8};
	//int arr[] = {1,2,3};
	int len = sizeof(arr)/sizeof(int);
	show(arr, len);
	proc(arr, len);	
	show(arr, len);	
	
	return 0;
}

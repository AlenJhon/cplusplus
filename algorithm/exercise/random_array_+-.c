#include <stdio.h>

void show(int* arr, int len);

void proc(int* arr, int len) 
{
	bool op = true; // true +, false -
	for (int i = 0; i < len; ++i) 
	{
		//show(arr, len);
		if (op == true) 
		{
			if (arr[i] > 0) 
			{
				op = false;
				continue;
			}
			
			int tmp = arr[i];//-
			//寻找正数并将第一个正数放到前面位置
			for (int j = i + 1; j < len; ++j) 
			{
				if (arr[j] > 0 ) 
				{
					arr[i] = arr[j];//前置
					
					int pre_idx = j;//可写入数据位置
					for (int k = j-1; k > i; --k)
					{
						if (arr[k] < 0)
						{
							arr[pre_idx] = arr[k];
							pre_idx = k;
						}
					}
					arr[pre_idx] = tmp;
					op = false;
					break;
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

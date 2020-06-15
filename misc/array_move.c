#include <stdio.h>

int exchange(int *parr, int start, int end) {
	
	while (start < end) {
		int tmp = parr[start];
		parr[start] = parr[end];
		parr[end] = tmp;

		start ++;
		end --;
	}
	return 0;
}

int array_move(int *parr, int arr_len, int move_num) {
	
	if (move_num > arr_len) return -1;
	int l = arr_len - move_num;
	
	exchange(parr, 0, l - 1); // 6, 5, 4, 3, 2, 1
	exchange(parr, l, arr_len - 1);// 8, 7
	exchange(parr, 0, arr_len - 1);

	return 0;
}

int main(void) {

	int arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	int len = sizeof(arr)/sizeof(int);
	//target
	//{7, 8, 1, 2, 3, 4, 5, 6 }
	
	array_move(arr, len, 2);

	for (int i = 0; i < len; i++) {
		printf("%2d ", arr[i]);
	}
	printf("\n");

	return 0;
}

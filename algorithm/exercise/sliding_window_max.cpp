#include <iostream>
#include <deque>

/*
����һ����������arr������w����ʾһ����СΪw�Ĵ��ڴ����������߻������ұߡ�
��ÿ�δ����ڵ����ֵ�������ؽ������
����
arr=[4, 3, 5, 4, 3, 3, 6, 7] , w= 3 ʱ�����շ���[5, 5, 5, 4, 6, 7]
[4, 3, 5], 4, 3, 3, 6, 7        ���������ֵΪ5
4, [3, 5, 4], 3, 3, 6, 7        ���������ֵΪ5
4, 3, [5, 4, 3], 3, 6, 7        ���������ֵΪ5
4, 3, 5, [4, 3, 3], 6, 7        ���������ֵΪ4
4, 3, 5, 4, [3, 3, 6], 7        ���������ֵΪ6
4, 3, 5, 4, 3, [3, 6, 7]        ���������ֵΪ7
*/

using namespace std;

void GetMaxWindow(int* arr, int sz, int w) {
    if (arr == nullptr || w < 1 || sz < w) {
        return ;
    }

    deque<int> dq;

    int len = sz - w + 1;
    int* res = new int[len];

    int rescnt = 0;
    for (int i = 0; i < sz; ++i) {
        
        //��β��ǰ���������<=��ǰ�¼��봰�ڵ�ֵ�Ӷ���pop_back
        while (!dq.empty() && arr[i] >= arr[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i);//��ǰ�ڵ���±�������

        //�鿴�����Ƿ����
        if (dq.front() == i - w) {
            dq.pop_front();
        }
        //�������
        if (i >= w - 1) { //����û�γɲ��ռ���
            res[rescnt++] = arr[dq.front()];
        }
    }


    for (int i = 0; i < len; ++i) {
        cout << res[i] << " ";
    }
    cout << endl;
    delete[] res;
}

int main() {
    int arr[] = {4, 3, 5, 4, 3, 3, 6, 7};
    int len = sizeof(arr) / sizeof(int);
    GetMaxWindow(arr, len, 3);

    return 0;
}

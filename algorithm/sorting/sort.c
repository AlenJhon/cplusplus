#include <stdio.h>

//buble sort 
//o(n*n)
void bubble_sort(int *pdata, int ilength)
{
    int itemp = 0;
    for(int i = 0; i < ilength; i++){
        
        for (int j = 0; j < ilength-1-i; j++){

            if (pdata[j] > pdata[j+1]){
                itemp = pdata[j+1];
                pdata[j+1] = pdata[j];
                pdata[j] = itemp;
            }
        }
    }
    return;
}

void bubble_sort2(int *pdata, int ilength)
{
    int itemp=0;
    // bool is_change = false;
    char is_exchange = 0;
    
    for (int i = 0; i<ilength; i++){
        
        is_exchange = 0;
        for(int j=ilength-1; j>0; j--){

            if(pdata[j] < pdata[j-1]){
                itemp = pdata[j];
                pdata[j] = pdata[j-1];
                pdata[j-1] = itemp;
                is_exchange = 1;
            }
        }
        
        if(!is_exchange){
            break;
        }
    }

    return;
}

//insert sort
// o(n*n)
void insert_sort(int *pdata, int ilength)
{
    if(!pdata) return;
    int itemp = 0;
    int i = 0, j = 0;
    
    for (i=1; i<ilength; i++){

        itemp = pdata[i];
        for(j=i-1; j>=0 && itemp < pdata[j]; j--){
            pdata[j+1] = pdata[j];
        }
        pdata[j+1] = itemp;
    }
    return;
}


//shell sort
//o(n^1.3)  ~   o(n*n)
//�������������һ����������
void shell_sort(int *pdata, int ilength)
{
    if (!pdata) return;
    int itemp=0, step=0, i=0, j=0;
    
    //for(int step = ilength/2; step > 0; step /= 2){ //step>=1 
    for(step = ilength/2; step >= 1; step /= 2){
        
        for(i = step; i < ilength; i++){
            itemp=pdata[i];
            for(j = i-step; j >= 0 && itemp < pdata[j]; j -= step){
                pdata[j + step] = pdata[j];// ����Ķ������ݺ���
            }
            pdata[j + step] = itemp;//��������
        }
    }
    return;
}


//merge sort
void merge_sort_i(int *pdata, int *ptemp, int istart, int imiddle, int iend)
{
    //static int call_count=0; // call count
    //printf("%4d", call_count++);

    int i = istart, j = imiddle+1, k=istart;
    while(i <= imiddle && j <= iend){
        if(pdata[i] >= pdata[j]){
            ptemp[k++] = pdata[j++];
        }
        else{
            ptemp[k++] = pdata[i++];
        }
    }   
    
    while(i <= imiddle){
        ptemp[k++] = pdata[i++];
    }
    
    while(j <= iend){
        ptemp[k++] = pdata[j++];
    }

    for(int x=istart; x<k; x++){
        pdata[x] = ptemp[x];
    }
    return;
}

void merge_sort(int *pdata, int *ptemp, int istart, int iend)
{
    if(!pdata || !ptemp) return;
    
    int imiddle = istart + (iend-istart) / 2;
    
    if(istart < iend){
        merge_sort(pdata, ptemp, istart, imiddle);
        merge_sort(pdata, ptemp, imiddle+1, iend);

        merge_sort_i(pdata, ptemp, istart, imiddle, iend);
    }
    return;    
}


//ѡ������
//o(n*n)
void select_sort(int *pdata, int ilength)
{
    int max_elm_idx = 0, itemp=0;
    int i=0, j=0;
    
    for(i=0; i<ilength; i++){//ִ������ÿһ���ҳ����ķ����������/����

        max_elm_idx = ilength-1-i;
        for(j=0; j<ilength-i; j++){
            if(pdata[max_elm_idx] < pdata[j]){
                max_elm_idx = j;
            }
        }

        if(max_elm_idx != ilength-1-i){
            itemp = pdata[max_elm_idx];
            pdata[max_elm_idx] = pdata[ilength-1-i] ;
            pdata[ilength-1-i] = itemp;
        }
    }
    return;
}


//��������
//o(nlogn)
void quick_sort_i(int *data, int left, int right){

    if(right <= left) return;

    int i = left, j = right;
    int key = data[left];
    
    while(i != j){

        while(i < j && data[j] >= key){
            j--;
        }
        data[i] = data[j];

        while(i < j && data[i] <= key){
            i++;
        }
        data[j] = data[i];
    }
    data[i] =  key;

    quick_sort_i(data, left, i-1); // i �Ѿ���λ�˲���Ҫ����
    quick_sort_i(data, i+1, right);
    
    return;
}
void quick_sort(int *pdata, int ilength)
{
    quick_sort_i(pdata, 0, ilength-1);
    return;
}



int main(void)
{
    int data[] = {17, 99, 45, 33, 26, 87, 32, 75, 32, 10};
    //int data[]= {2,4,3,1};
    int length = sizeof(data)/sizeof(int);
#if 0
    //bubble_sort(data, length);
    bubble_sort2(data, length);
#elseif 0
    insert_sort(data, length);
#elseif 0
    shell_sort(data, length);
#elseif 0
    int temp[length] = {0};
    merge_sort(data, temp, 0, length-1);
#elseif 0
    select_sort(data, length);
#elseif 0
    quick_sort(data, length);

    
#endif

    printf("\n");
    for (int i=0; i<length; i++){
        printf("%4d", data[i]);
    }
    printf("\n");
}

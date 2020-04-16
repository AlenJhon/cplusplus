#include <cstdio>


// sizeof class inst
class sizeofx
{
protected:
    /* data */
    
public:
    sizeofx(/* args */){}
    ~sizeofx(){}

    int m_iBaseData;
};

class sizeofxx:public sizeofx
{
private:
    /* data */
    int m_iData2;
    static int m_iDataStatic;
public:
    sizeofxx(/* args */){}
    ~sizeofxx(){}
};

int sizeofxx::m_iDataStatic = 100;

bool TestSizeofx()
{
    printf("sizeof int : %d\n", sizeof(int));
    sizeofxx x;
    printf("sizeofxx:%d\n", sizeof(x));
    return true;
}


//sizeof function param

int FuncSizeof(int a[])
{
    printf("int a[] sizeof:%d\n", sizeof(a));
}

int FuncSizeof2(int a[10])
{
    printf("int a[] sizeof:%d\n", sizeof(a));
}

int FuncSizeof3(int (&a)[10])
{
    printf("int a[] sizeof:%d\n", sizeof(a));
}

bool TestFuncParamSizeof()
{
    int a[10] = {0};
    FuncSizeof(a);
    FuncSizeof2(a);
    FuncSizeof3(a);

    int *p = NULL;
    printf("int *p sizeof :%d\n", sizeof(p));

    printf("long sizeof:%d\n", sizeof(long));
    printf("long int sizeof:%d\n", sizeof(long int));
    printf("short sizeof:%d\n", sizeof(short));

    return true;
}
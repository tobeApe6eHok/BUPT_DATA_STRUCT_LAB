/*
数据结构实验六  实验环境: WIN10 + VScode + Cpp20
*/

#include<iostream>
using namespace std;

//定义需要排序的结构体,默认按照Value字段进行排序,用户可以在结构体中自定义其他数据字段
template<class T>
struct Element
{
    T Value;                       //按照Value的值大小进行排序
    
    //结构体中还可以定义其他数据域
    
    Element():Value(0){}           //无参构造函数
    Element(T value):Value(value){}//结构体的构造函数
};

//打印每次正向、逆向排序的结果,便于检测排序的正确性
//函数调用中如果Direct<0,表示刚刚进行的是逆向排序
//如果Direct>0,表示刚刚进行的是正向排序
template<class T>
void Printf(int Direct,int ArraySize,Element<T> Array[])
{
    if(Direct<0)
    {
        cout<<"第"<<-Direct<<"次反向排序结果:"<<"\t";
    }
    else
    {
        cout<<"第"<<Direct<<"次正向排序结果:"<<"\t";
    }
    for(int p=0;p<ArraySize;p++)
    {
        cout<<Array[p].Value<<" ";
    }
    cout<<endl;
}

//比较函数
//Reverse==true则表示逆向排序,则Front.Value<Latter.Value时交换前后顺序
template<class T>
bool CompareKey(Element<T> &Front,Element<T> &Latter,bool Reverse=false)
{
    return Reverse?(Front.Value<Latter.Value):(Front.Value>Latter.Value);
}

//双向冒泡排序
//默认是升序
//如果需要逆序排序,则在调用时将Reverse设成true
template<class T>
void TowWayBubbleSort(int ArraySize,Element<T> Array[],bool Reverse=false)
{
    //LeftRemain和RightRemain用来记录待排序数组范围的左右边界
    //Loop用来记录已经循环的次数
    //Flag用来充当哨兵
    //P是循环过程中的指针
    int LeftRemain=0,RightRemain=ArraySize-1,Loop=1,Flag,P;

    while(LeftRemain<RightRemain)
    {
        //设置哨兵,记录是否已经排好序
        Flag=false;
        P=LeftRemain;

        //正向排序
        while(P<RightRemain)
        {
            if(CompareKey(Array[P],Array[P+1],Reverse))//如果满足交换的条件,则交换,并且告知哨兵
            {
                swap(Array[P],Array[P+1]);
                Flag=true;//说明本次循环中有交换位置,说明还没有排好序
            }
            ++P;
        }

        //显示本次正向排序的结果
        Printf(Loop,ArraySize,Array);

        //Flag==false表示本次循环比较中没有进行交换,说明数组已经排好序
        if(!Flag)   break;
        --RightRemain,--P,Flag=false;//缩小待排序数组的范围,并且重置哨兵

        //逆向排序
        while(P>LeftRemain)
        {
            if(CompareKey(Array[P-1],Array[P],Reverse))//如果满足交换的条件,则交换,并且告知哨兵
            {
                swap(Array[P-1],Array[P]);
                Flag=true;//说明本次循环中有交换位置,说明还没有排好序
            }
            --P;
        }

        //显示本次逆向排序结果
        Printf(-Loop,ArraySize,Array);

        //Flag==false表示本次循环比较中没有进行交换,说明数组已经排好序
        if(!Flag)   break;
        ++LeftRemain,++Loop,Flag=false;//缩小待排序的数组范围,并且重置哨兵,记录下一次的循环次数
    }
}

//test1函数,其中有一个正向排序的测试样例
void test1()
{
    Element<int> nums[10];
    for(int i=9;i>=0;i--)
    {
        nums[9-i]=Element<int>(i);
    }
    TowWayBubbleSort(10,nums);
}

//test2函数,其中有一个逆向排序的测试样例
void test2()
{
    Element<int> nums[10];
    for(int i=0;i<10;i++)
    {
        nums[i]=Element<int>(i);
    }
    TowWayBubbleSort(10,nums,true);    
}

void test3()
{
    Element<int> nums[10];
    int values[]={45,19,77,81,13,28,18,19,77,11};
    for(int i=0;i<10;i++)
    {
        nums[i]=Element<int>(values[i]);
    }
    TowWayBubbleSort(10,nums);
}

int main()
{
    cout<<"\n第一个测试样例:"<<endl;
    test1();
    cout<<"\n第二个测试样例:"<<endl;
    test2();
    cout<<"\n第三个测试样例:"<<endl;
    test3();
}
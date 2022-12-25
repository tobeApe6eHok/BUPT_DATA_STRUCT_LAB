/*
    数据结构第5次实验 实验环境: WIN 10 + VScode + C++20
*/
#include<iostream>
using namespace std;

//邻接链表中的边界点
struct ListNode
{
    int place;          //存储该相邻图节点在数组中的下标
    ListNode* next;     //存储下一个相邻节点的指针
    ListNode(int p)     //初始化函数
    {
        place = p;
        next = NULL;
    }
};

//图节点
template<class T>
struct GridNode
{
    T Data;                             //存储图节点内部的信息
    ListNode* NeiborHead;               //存储相邻节点链表的头节点
    GridNode() { NeiborHead = NULL; };  //初始化函数
};

//图模板类
template<class T>
class Grid
{
private:
    GridNode<T>* Graph;                                                         //存储图节点的数组
    int GridSize;                                                               //存储图节点的数量
    int VertexNum;                                                              //存储图中边的数量
public:
    Grid(int GridNodeCnt, T GridNodeInfo[], int VertexCnt, int GridVertex[]);   //构造函数
    void ShowAdjacentList();                                                    //将构造好的邻接表打印出来
    ~Grid();                                                                    //析构函数
    void DeepFirstSearch(int Start=0);                                          //非递归的深度优先遍历函数
};

//构造函数
//GridNodeCnt表示图节点的数量,GridNodeInfo依次存储图节点中的信息
//VertextCnt表示图中有向边的数量,GridVertex中使用(2*i)和(2*i+1)分别表示边的始末节点下标
template<class T>
Grid<T>::Grid(int GridNodeCnt, T GridNodeInfo[], int VertexCnt, int GridVertex[])
{
    this->GridSize = GridNodeCnt;                                   //初始化图节点的数量
    this->VertexNum=VertexCnt;                                      //初始化图的边数
    this->Graph = new GridNode<T>[GridNodeCnt];                     //分配存储图节点的数组内存
    for (int i = 0; i < GridNodeCnt; i++)                           
    {
        this->Graph[i].Data = GridNodeInfo[i];                      //依次初始化图节点的内部信息
        this->Graph[i].NeiborHead = NULL;                           //将邻居链表的头节点设置为NULL
    }
    for (int cnt = 0, VP = 0; cnt < VertexCnt; cnt++, VP += 2)      //偶数下标表示边的起始节点,奇数表示终止节点下标
    {
        //头插链表节点
        ListNode* temp = new ListNode(GridVertex[VP + 1]);
        temp->next = this->Graph[GridVertex[VP]].NeiborHead;
        this->Graph[GridVertex[VP]].NeiborHead = temp;
    }
}

//将创建好的邻接表打印出来
template<class T>
void Grid<T>::ShowAdjacentList()
{
    //遍历每个图节点
    for (int i = 0; i < this->GridSize; i++)
    {
        cout << this->Graph[i].Data <<"("<<i << ") : ";
        ListNode* t = this->Graph[i].NeiborHead;
        //遍历每个图节点的邻居节点下标
        while (t != NULL)
        {
            cout << t->place;
            t = t->next;
            if (t != NULL)
            {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}

//析构函数
template<class T>
Grid<T>::~Grid()
{
    //遍历每个图节点
    for (int i = 0; i < this->GridSize; i++)
    {
        ListNode* t = this->Graph[i].NeiborHead;
        //释放每个链表节点的内存
        while (t != NULL)
        {
            ListNode* tt = t;
            t = t->next;
            delete tt;
        }
        cout << endl;
    }
    //释放存储图节点的数组内存
    delete[] this->Graph;
}

//图的非递归深度优先遍历函数
template<class T>
void Grid<T>::DeepFirstSearch(int Start)
{
    //初始化记录每个节点有无被访问过的数组
    bool* JudgePassed = new bool[this->GridSize];
    for (int i = 0; i < this->GridSize; i++)
    {
        JudgePassed[i] = 0;//将每个标记设置为 未访问
    }
    //使用数组模拟 栈结构
    //Remain[0]表示栈的大小
    //Remain[Remain[0]]表示栈顶元素
    int* Remain = new int[this->VertexNum + 1];//+1是因为0下标元素用来表示栈目前占用大小
    Remain[0] = 1, Remain[1] = Start;

    //只要栈中还有元素,就表示还有可能有未访问的节点
    while (Remain[0])
    {
        //取出栈顶元素
        int First = Remain[Remain[0]--];
        
        //栈顶元素是上次访问过的节点的第一个未被访问过的邻居节点
        //与递归的方式对称
        if (!JudgePassed[First])
        {
            JudgePassed[First] = 1;
            cout << First << "  ";//访问
        }

        //获得每个邻居节点
        ListNode* t = this->Graph[First].NeiborHead;
        while (t != NULL)
        {
            //模拟递归方式中的顺序遍历邻居节点
            //迭代方式中只需要将每个未访问的邻居节点都放入栈中即可
            if (!JudgePassed[t->place])
            {
                Remain[++Remain[0]] = t->place;
            }
            t = t->next;
        }
    }
    cout << endl;
    //释放内存
    delete[] JudgePassed;
    delete[] Remain;

}

//测试样例1
void test1()
{
    int GridNodeCnt = 8;//表示有8个节点
    char GridNodeInfo[] = { 'a','b','c','d','e','f','g','h' };//节点中的内部信息
    int VertexCnt = 16;//表示有16条边
    //(2*i)->(2*i+1)有一条边
    //0->1,1->0,1->2,1->3...
    int GridVertex[] = { 0,1,1,0,1,2,1,3,2,4,2,6,3,1,3,5,4,2,4,6,4,7,5,6,6,2,6,4,7,5,7,6 };
    Grid<char> a(GridNodeCnt, GridNodeInfo, VertexCnt, GridVertex);
    cout<<"第一个测试样例结果:\n"<<endl;
    cout << "邻接表结构如下 :" << endl;
    a.ShowAdjacentList();
    cout << "深度优先遍历的节点顺序如下 :" << endl;
    a.DeepFirstSearch();
}

//测试样例2
void test2()
{
    int GridNodeCnt = 8;//表示有8个节点
    int GridNodeInfo[] = { 101,102,103,104,105,106,107,108};//节点中的内部信息
    int VertexCnt = 14;//表示有14条边
    //(2*i)->(2*i+1)有一条边
    //1->5,2->0,2->1,2->5...
    int GridVertex[] = { 1,5,2,0,2,1,2,5,3,1,3,5,3,7,4,2,5,1,5,3,5,6,6,2,6,5,7,5 };
    Grid<int> a(GridNodeCnt, GridNodeInfo, VertexCnt, GridVertex);
    cout<<"第二个测试样例结果:\n"<<endl;
    cout << "邻接表结构如下 :" << endl;
    a.ShowAdjacentList();
    cout << "深度优先遍历的节点顺序如下 :" << endl;
    a.DeepFirstSearch(4);
}

int main()
{
    test1();
    test2();
}
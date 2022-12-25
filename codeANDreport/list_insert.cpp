/*
	数据结构课设实验一

	我的实验环境: WIN10 + VS2019

	程序中定义的链表是含有头节点的链表,头节点不存储任何数据,只是用于初始化链表,在插入时更方便

	建议测试者:
	1、使用PushBack()函数不断向链表最后插入节点,以初始化要构造的链表
	2、使用ListIndsertByPlace()|ListIndsertByData()|ListIndsertByPointer()在节点前插入节点
	3、使用ListPrintf()来验证是否已经插入了该节点
*/
#include<iostream>
using namespace std;

//创建一个模板类
template<typename T>
class List {
private:
	//在模板类中定义一个对应的结构体,用于定义节点的结构
	struct Node {
		T data;                 //存储节点的数据
		struct Node* next;      //存储下一个节点的地址
	};
	Node* head;                 //链表的头节点
	Node* tail;                 //链表的尾节点
	int len;                    //记录链表的长度,头节点不计算在内
public:
	List();                                           //链表的构造函数
	~List();                                          //链表的析构函数
	void PushBack(T value);                           //向链表的最后一个位置插入一个节点,主要用于用户创建链表时
	void ListPrintf();                                //依次打印链表中的节点,主要用于验证链表的插入效果
	void ListInsertByPlace(int place, T value);       //指定第几个节点(第0个节点是头节点),在该节点前插入节点,value是要插入的数据
	void ListInsertByData(T target, T value);		  //指定数据,在含有该数据的第一个节点前插入节点,value是要插入的数据
	void ListInsertByPointer(Node* ptr, T value);     //指定一个节点的地址,在该地址的节点前插入节点(用户一般不会使用),该函数被另外两个插入函数调用
};

//构造函数:
//1、初始化头节点,此时链表只有头节点,所以头节点就是尾节点
//2、由于头节点不计算在链表长度内,所以此时链表长度为0
template<typename T>
List<T>::List() {
	tail = head = (Node*)malloc(sizeof(Node));//使用malloc申请内存
	head->next = NULL;
	len = 0;
}

//析构函数:
//逐个将所有的节点的内存都释放掉
template<typename T>
List<T>::~List() {
	Node* tmp = NULL;//tmp用于记录要释放内存的节点地址
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);//使用free释放内存
	}
	len = 0;//节点都释放掉之后,链表长度变成0 (头节点也没有了)
}

//在链表的最后加一个节点,用户可以反复使用这个函数初始化要构造的链表
template<typename T>
void List<T>::PushBack(T value) {
	Node* tmp = (Node*)malloc(sizeof(Node));//加入一个节点
	if (tmp) {//如果申请空间成功
		//在tail后插入该节点,并且tail指向该节点
		tmp->data = value;
		tmp->next = NULL;
		tail->next = tmp;
		tail = tmp;
		++len;
	}
	else {
		cout << "无法申请空间" << endl;
	}
}

//将链表的节点的data依次打印出来,用于验证链表确实完成了在某个节点前插入节点的功能
template<typename T>
void List<T>::ListPrintf() {
	Node* tmp = head->next;
	while (tmp != NULL) {
		cout << tmp->data << " ";
		tmp = tmp->next;
	}
	cout << endl;
}

//根据节点的地址插入值为value的节点
//该函数一般不会被用户调用,该函数被另外两个插入函数调用
template<typename T>
void List<T>::ListInsertByPointer(Node* ptr, T value) {
	Node* newNode = (Node*)malloc(sizeof(Node));//先申请节点内存空间
	if (newNode) {//如果内存空间申请成功
		//先将指定节点的数据copy到下一个空节点
		//然后将要插入的数据放到指定节点上,这样就完成了插入
		newNode->data = ptr->data;
		newNode->next = ptr->next;
		ptr->data = value;
		ptr->next = newNode;
		//此处需要考虑一个特殊情况:
		//如果tail是要找的节点,由于插入的机制时在其后插入一个节点,所以tail就不能保证指向最后一个节点了
		//所以此处进行特殊判断
		if (tail->next != NULL)
		{
			tail = tail->next;
		}
		//插入了一个节点,链表长度+1
		++len;
	}
	else {
		cout << "无法申请空间" << endl;
	}
}

//根据指定的数据找到节点,并在其之前插入节点
template<typename T>
void List<T>::ListInsertByData(T target, T value) {
	Node* tmp = head->next;
	//首先找到data==target的节点
	while (tmp != NULL && tmp->data != target)
	{
		tmp = tmp->next;
	}
	//如果tmp==NULL,那么说明链表中没有这样的节点
	if (tmp != NULL)
	{
		ListInsertByPointer(tmp, value);//找到了该节点,就可以使用根据地址插入的函数插入节点
	}
	else
	{
		cout << "未找到目标节点" << endl;
	}
}

//根据位置在节点前插入节点
template<typename T>
void List<T>::ListInsertByPlace(int place, T value) {
	//判断指定的位置是否有效
	if (place > len || place <= 0) {
		cout << "位置错误" << endl;
	}
	else {
		Node* tmp = head->next;
		//找到该位置的节点
		while (--place)
		{
			tmp = tmp->next;
		}
		ListInsertByPointer(tmp, value);//找到了该节点,就可以使用根据地址插入的函数插入节点
	}
}

//以下是测试用例
int main()
{
	List<int> list;
	int n, choice, t1, t2, p;
	cout << "请输入初始链表的节点数:" << endl;
	cin >> n;
	cout << "请输入各个节点的值:" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> t1;
		list.PushBack(t1);
	}
	while (1)
	{
		cout << "当前的链表是:" << endl;
		list.ListPrintf();
		cout << "请输入要进行的操作:" << endl;
		cout << "1、在链表的最后插入" << endl;
		cout << "2、按照位置在特定节点前插入节点" << endl;
		cout << "3、在含有特定数据的节点前插入节点" << endl;
		cin >> choice;
		if (choice == 1)
		{
			cout << "请输入要插入的节点数据" << endl;
			cin >> t1;
			list.PushBack(t1);
		}
		else if (choice == 2)
		{
			cout << "请输入指定节点的位置和要插入的数据" << endl;
			cin >> p >> t1;
			list.ListInsertByPlace(p, t1);
		}
		else if (choice == 3)
		{
			cout << "请输入指定节点的数据和要插入的数据" << endl;
			cin >> t1 >> t2;
			list.ListInsertByData(t1, t2);
		}
		else
		{
			cout << "程序结束" << endl;
			break;
		}
		system("cls");
	}
}
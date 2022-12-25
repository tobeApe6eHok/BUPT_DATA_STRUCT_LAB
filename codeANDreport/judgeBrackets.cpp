/*
    数据结构实验第2次实验
    我的实验环境: WINDOWS10 + VScode/VS2019 + c++20

    代码中假设要检查的字符串长度是150,可以改变LENGTH的值

    检查括号匹配和判断括号使用正确的规则:
    1、括号前后匹配
    2、小括号中不可以有中括号或者大括号
    3、中括号中必须要有小括号，不可以有大括号
    4、大括号中必须要有中括号
    5、但是同级括号之间可以并包

    例子:
    正确的例子:
    {{()[()]}{[[(())](())[(())](())]{(()())[()]}}}     :其中中括号并包
    {{()[()]}{[[(())](())[(())](())]}}                 :其中每种括号均有同级并包
    [()()(((())))[[()][[[()]]][()]][[()]][(())]]
    等

    错误的例子:
    {{()[()]}{[[(())](())[(())](())]{[]}}}             :其中的[]里有一个没有()
    {{()[()]}{[[(()[])](())[(())](())]}}               :其中有一个()包含了[]
    {{()[()]}{[[(())](())[(())](())]{(()())}}}         :其中有一个{}中没有[]
    等
*/
#include<iostream>
#include<stack>
using namespace std;

#define LENGTH          150   //假设要判断的字符串长度最长是150,可以改变LENGTH的值

//将不同的括号设置为不同的整型
#define NONE            0     //未输入时为NONE
#define LITTLE          1     //表示小括号
#define MIDDEL          2     //表示中括号
#define LARGE           3     //表示大括号

//表示下一级对应的括号是否已经出现,stack<pair<int,int>>中的第二个值使用这两个宏
#define NeXTHAVENT      0     //表示下一级对应的括号未出现
#define NeXTHAVED       1     //表示下一级对应的括号出现了

//表示为什么括号匹配不成功,或者括号的使用有什么不正确的错误类型
#define BIGinSMALL      1     //表示在低级括号中使用了高级括号
#define NOLITTLE        2     //表示在一个高级括号中没有使用小括号
#define CANTMATCH       3     //表示前后两个括号不可以匹配,或者丢失了一个反括号
#define CHAREXTRA       4     //表示输入的字符串中有冗余括号

//根据宏定义的值获得代表括号的字符串
string BRAKET(int NOW)
{
    if (NOW == LITTLE) return "()";
    else if (NOW == MIDDEL) return "[]";
    else return "{}";
}

//判断括号是否匹配成功的函数
//s是用户的输入，len是字符串的长度
bool isValid(char* s, int len)
{
    //一个打印为什么匹配不同，或者括号使用不正确的原因的函数
    //type表示错误的类型，与上面的宏定义一一对应
    auto raiseruntimerror = [](int type, int FIRST = -1, int SECOND = -1)->void {
        cout << endl;
        if (type == BIGinSMALL)
        {
            cout << "从" << BRAKET(FIRST) << "中发现" << BRAKET(SECOND) << ",低级括号包含高级括号" << endl;
        }
        else if (type == NOLITTLE)
        {
            cout << "有一个" << BRAKET(FIRST) << "中没有下一级括号" << endl;
        }
        else if (type == CANTMATCH)
        {
            cout << BRAKET(FIRST) << "前括号不可以和" << BRAKET(SECOND) << "后括号匹配,或者少了一个" << BRAKET(FIRST) << "后括号" << endl;
        }
        else if (type == CHAREXTRA)
        {
            cout << "有冗余字符" << endl;
        }
    };

    //使用栈
    //第一个元素存储括号的级别
    //第二个元素存储后面是否出现了比本括号只小一级的括号，因为中括号中必须要有小括号、大括号中必须要有中括号
    stack<pair<int, int>>unpaired;
    //NeXTsMALLER表示该前括号和对应的后括号之间的括号都应比本括号的级别要小，因为中括号中不许有大括号，小括号中不许有中括号和大括号
    //NOW表示现在遍历到的括号的级别
    int NeXTsMALLER = LARGE, NOW = NONE;
    for (int i = 0; i < len; i++)
    {
        switch (s[i]) {
        //如果是前括号，获得其级别
        case '(':
            NOW = (NOW == NONE ? LITTLE : NOW);
        case '[':
            NOW = (NOW == NONE ? MIDDEL : NOW);
        case '{':
            NOW = (NOW == NONE ? LARGE : NOW);

            //对于所有的前括号操作相同

            //如果当前的括号比前面的括号级别高，则不满足中括号中不许有大括号、小括号中不许有中括号和大括号的要求
            if (NOW > NeXTsMALLER)
            {
                raiseruntimerror(BIGinSMALL, NeXTsMALLER, NOW);
                return false;
            }
            //更改下一个括号的级别要求
            NeXTsMALLER = NOW;
            //向栈中放入相应的前括号
            //如果是小括号，则只需要使用NeXTsMALLER判断是否满足级别不会再增大，而不需要再判断括号中是否有只小一级的括号，因为小括号级别最小
            unpaired.push({ NOW,(NOW == LITTLE ? NeXTHAVED : NeXTHAVENT) });
            break;

        //如果是后括号，获得其级别
        case ')':
            NOW = (NOW == NONE ? LITTLE : NOW);
        case ']':
            NOW = (NOW == NONE ? MIDDEL : NOW);
        case '}':
            NOW = (NOW == NONE ? LARGE : NOW);

            //对所有后括号的操作相同

            //如果前面没有对应的前括号匹配
            if (unpaired.empty())
            {
                raiseruntimerror(CHAREXTRA);
                return false;
            }
            //如果这两个括号之间没有只小一级的括号，则不满足中括号中必须要有小括号、大括号中必须要有中括号的要求
            else if (unpaired.top().second == NeXTHAVENT)
            {
                raiseruntimerror(NOLITTLE, unpaired.top().first);
                return false;
            }
            //如果前括号和后括号类型不匹配
            else if (unpaired.top().first != NOW)
            {
                raiseruntimerror(CANTMATCH, unpaired.top().first, NOW);
                return false;
            }

            //匹配成功，出栈
            unpaired.pop();
            //如果此次储栈的括号是叠加在另一个更大的括号中的
            if (!unpaired.empty())
            {
                //获得更大括号的类型
                NeXTsMALLER = unpaired.top().first;
                //如果刚刚出栈的括号是只小一级的括号，或者是同级括号，则栈顶前括号的第二个元素可以变成NeXTHAVED
                if (NeXTsMALLER == NOW || NeXTsMALLER == NOW + 1)
                {
                    unpaired.top().second = NeXTHAVED;
                }
            }
            else
            {
                //如果本段括号匹配完毕，则将最初的级别限制放宽
                NeXTsMALLER = LARGE;
            }
            break;

        default:
            break;
        }
        //还未读取的下一个字符
        NOW = NONE;
    }

    //如果最后还有前括号，则说明括号冗余
    if (!unpaired.empty())
    {
        raiseruntimerror(CHAREXTRA);
        return false;
    }

    return true;
}

int main()
{
    char* strInput = (char*)malloc(sizeof(char) * LENGTH);
    int isContinue = 2;
    while (isContinue)
    {
        cout << "请输入要检查的字符串:" << endl;
        char* charTOINPUT = strInput, justIN;
        if (isContinue == 1)
        {
            justIN = cin.get();
        }
        while (justIN = cin.get())
        {
            if (justIN == '\n' || !charTOINPUT)
            {
                break;
            }
            *charTOINPUT++ = justIN;
        }
        int inputSize = charTOINPUT - strInput;
        bool judgeResult = isValid(strInput, inputSize);
        if (judgeResult)
        {
            cout << "满足要求." << endl;
        }
        else
        {
            cout << "所以不满足要求." << endl;
        }
        cout << "\n是否继续? 0|1" << endl;
        cin >> isContinue;
        if (isContinue != 1)
        {
            break;
        }
    }
    free(strInput);
    return 0;
}
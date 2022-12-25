/*
    ���ݽṹʵ���2��ʵ��
    �ҵ�ʵ�黷��: WINDOWS10 + VScode/VS2019 + c++20

    �����м���Ҫ�����ַ���������150,���Ըı�LENGTH��ֵ

    �������ƥ����ж�����ʹ����ȷ�Ĺ���:
    1������ǰ��ƥ��
    2��С�����в������������Ż��ߴ�����
    3���������б���Ҫ��С���ţ��������д�����
    4���������б���Ҫ��������
    5������ͬ������֮����Բ���

    ����:
    ��ȷ������:
    {{()[()]}{[[(())](())[(())](())]{(()())[()]}}}     :���������Ų���
    {{()[()]}{[[(())](())[(())](())]}}                 :����ÿ�����ž���ͬ������
    [()()(((())))[[()][[[()]]][()]][[()]][(())]]
    ��

    ���������:
    {{()[()]}{[[(())](())[(())](())]{[]}}}             :���е�[]����һ��û��()
    {{()[()]}{[[(()[])](())[(())](())]}}               :������һ��()������[]
    {{()[()]}{[[(())](())[(())](())]{(()())}}}         :������һ��{}��û��[]
    ��
*/
#include<iostream>
#include<stack>
using namespace std;

#define LENGTH          150   //����Ҫ�жϵ��ַ����������150,���Ըı�LENGTH��ֵ

//����ͬ����������Ϊ��ͬ������
#define NONE            0     //δ����ʱΪNONE
#define LITTLE          1     //��ʾС����
#define MIDDEL          2     //��ʾ������
#define LARGE           3     //��ʾ������

//��ʾ��һ����Ӧ�������Ƿ��Ѿ�����,stack<pair<int,int>>�еĵڶ���ֵʹ����������
#define NeXTHAVENT      0     //��ʾ��һ����Ӧ������δ����
#define NeXTHAVED       1     //��ʾ��һ����Ӧ�����ų�����

//��ʾΪʲô����ƥ�䲻�ɹ�,�������ŵ�ʹ����ʲô����ȷ�Ĵ�������
#define BIGinSMALL      1     //��ʾ�ڵͼ�������ʹ���˸߼�����
#define NOLITTLE        2     //��ʾ��һ���߼�������û��ʹ��С����
#define CANTMATCH       3     //��ʾǰ���������Ų�����ƥ��,���߶�ʧ��һ��������
#define CHAREXTRA       4     //��ʾ������ַ���������������

//���ݺ궨���ֵ��ô������ŵ��ַ���
string BRAKET(int NOW)
{
    if (NOW == LITTLE) return "()";
    else if (NOW == MIDDEL) return "[]";
    else return "{}";
}

//�ж������Ƿ�ƥ��ɹ��ĺ���
//s���û������룬len���ַ����ĳ���
bool isValid(char* s, int len)
{
    //һ����ӡΪʲôƥ�䲻ͬ����������ʹ�ò���ȷ��ԭ��ĺ���
    //type��ʾ��������ͣ�������ĺ궨��һһ��Ӧ
    auto raiseruntimerror = [](int type, int FIRST = -1, int SECOND = -1)->void {
        cout << endl;
        if (type == BIGinSMALL)
        {
            cout << "��" << BRAKET(FIRST) << "�з���" << BRAKET(SECOND) << ",�ͼ����Ű����߼�����" << endl;
        }
        else if (type == NOLITTLE)
        {
            cout << "��һ��" << BRAKET(FIRST) << "��û����һ������" << endl;
        }
        else if (type == CANTMATCH)
        {
            cout << BRAKET(FIRST) << "ǰ���Ų����Ժ�" << BRAKET(SECOND) << "������ƥ��,��������һ��" << BRAKET(FIRST) << "������" << endl;
        }
        else if (type == CHAREXTRA)
        {
            cout << "�������ַ�" << endl;
        }
    };

    //ʹ��ջ
    //��һ��Ԫ�ش洢���ŵļ���
    //�ڶ���Ԫ�ش洢�����Ƿ�����˱ȱ�����ֻСһ�������ţ���Ϊ�������б���Ҫ��С���š��������б���Ҫ��������
    stack<pair<int, int>>unpaired;
    //NeXTsMALLER��ʾ��ǰ���źͶ�Ӧ�ĺ�����֮������Ŷ�Ӧ�ȱ����ŵļ���ҪС����Ϊ�������в����д����ţ�С�����в����������źʹ�����
    //NOW��ʾ���ڱ����������ŵļ���
    int NeXTsMALLER = LARGE, NOW = NONE;
    for (int i = 0; i < len; i++)
    {
        switch (s[i]) {
        //�����ǰ���ţ�����伶��
        case '(':
            NOW = (NOW == NONE ? LITTLE : NOW);
        case '[':
            NOW = (NOW == NONE ? MIDDEL : NOW);
        case '{':
            NOW = (NOW == NONE ? LARGE : NOW);

            //�������е�ǰ���Ų�����ͬ

            //�����ǰ�����ű�ǰ������ż���ߣ��������������в����д����š�С�����в����������źʹ����ŵ�Ҫ��
            if (NOW > NeXTsMALLER)
            {
                raiseruntimerror(BIGinSMALL, NeXTsMALLER, NOW);
                return false;
            }
            //������һ�����ŵļ���Ҫ��
            NeXTsMALLER = NOW;
            //��ջ�з�����Ӧ��ǰ����
            //�����С���ţ���ֻ��Ҫʹ��NeXTsMALLER�ж��Ƿ����㼶�𲻻������󣬶�����Ҫ���ж��������Ƿ���ֻСһ�������ţ���ΪС���ż�����С
            unpaired.push({ NOW,(NOW == LITTLE ? NeXTHAVED : NeXTHAVENT) });
            break;

        //����Ǻ����ţ�����伶��
        case ')':
            NOW = (NOW == NONE ? LITTLE : NOW);
        case ']':
            NOW = (NOW == NONE ? MIDDEL : NOW);
        case '}':
            NOW = (NOW == NONE ? LARGE : NOW);

            //�����к����ŵĲ�����ͬ

            //���ǰ��û�ж�Ӧ��ǰ����ƥ��
            if (unpaired.empty())
            {
                raiseruntimerror(CHAREXTRA);
                return false;
            }
            //�������������֮��û��ֻСһ�������ţ��������������б���Ҫ��С���š��������б���Ҫ�������ŵ�Ҫ��
            else if (unpaired.top().second == NeXTHAVENT)
            {
                raiseruntimerror(NOLITTLE, unpaired.top().first);
                return false;
            }
            //���ǰ���źͺ��������Ͳ�ƥ��
            else if (unpaired.top().first != NOW)
            {
                raiseruntimerror(CANTMATCH, unpaired.top().first, NOW);
                return false;
            }

            //ƥ��ɹ�����ջ
            unpaired.pop();
            //����˴δ�ջ�������ǵ�������һ������������е�
            if (!unpaired.empty())
            {
                //��ø������ŵ�����
                NeXTsMALLER = unpaired.top().first;
                //����ոճ�ջ��������ֻСһ�������ţ�������ͬ�����ţ���ջ��ǰ���ŵĵڶ���Ԫ�ؿ��Ա��NeXTHAVED
                if (NeXTsMALLER == NOW || NeXTsMALLER == NOW + 1)
                {
                    unpaired.top().second = NeXTHAVED;
                }
            }
            else
            {
                //�����������ƥ����ϣ�������ļ������Ʒſ�
                NeXTsMALLER = LARGE;
            }
            break;

        default:
            break;
        }
        //��δ��ȡ����һ���ַ�
        NOW = NONE;
    }

    //��������ǰ���ţ���˵����������
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
        cout << "������Ҫ�����ַ���:" << endl;
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
            cout << "����Ҫ��." << endl;
        }
        else
        {
            cout << "���Բ�����Ҫ��." << endl;
        }
        cout << "\n�Ƿ����? 0|1" << endl;
        cin >> isContinue;
        if (isContinue != 1)
        {
            break;
        }
    }
    free(strInput);
    return 0;
}
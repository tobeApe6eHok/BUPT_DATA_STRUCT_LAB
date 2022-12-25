"""
数据结构课设第3次实验
实验环境: WIN10 + VS code + Python 3.10.0

提示:
    python是动态语言,所以测试者可以自行定义队列元素数据结构,支持泛型编程
    若测试者使用自定义的数据类型,需要自定义如何打印该数据类型的__repr__函数和input,以便实现如下形式的可视化和测试时的输入:
    
        Left
        ↓ →→→→→
    ----------------------------------------------------------------------------------------------------
    |   None   |   None   |   None   |   None   |   None   |   None   |   None   |   None   |   None   |
    ----------------------------------------------------------------------------------------------------
        →→↑
        Right
    
    (其中None表示该位置没有元素)
"""

class Deque:

    def __init__(self,DequeSize:int)->None:
        """初始化循环队列,队列中最多含有DequeSize个元素 (DequeSize>0)"""
        self.Element=[None]*DequeSize               # 初始化循环队列的元素列表
        self.Front,self.Rear=0,0                    # 初始化队首、队尾的位置
        self.Tag=False                              # 将队列满的标志设置为Flase,代表不满
        return 
    
    def DequeRepr(self)->str:
        """
        `为了形式化展示队列的状态,可以形象化队列`
        `将队列转换成str类型,直接打印返回的str即可`
        """
        def Between(num:int)->bool:
            """判断一个下标num是否在self.Front和self.Rear之间"""
            # 如果Front==Rear只需要判断队列是否已满
            # 如果未满,则没有元素,返回False
            # 如果已满,则num在Front和Rear之间
            if self.Front==self.Rear:
                return self.Tag
            # num在Front和Rear之间的情况只有如下三种
            return num<self.Rear<self.Front or self.Rear<self.Front<=num or self.Front<=num<self.Rear
        # 将Front和Rear之间的元素使用类型内置的__repr__函数转成字符串
        # 将不在Front和Rear之间的元素的str设置为'None'
        EleStr=[type(self.Element[E]).__repr__(self.Element[E]) if Between(E) else 'None' for E in range(len(self.Element))]
        # 设置队列中每个元素所占的空间
        Length=max([len(i) for i in EleStr])+6
        # 将所有元素安排在一行上
        LS='|'+'|'.join([i.center(Length,' ') for i in EleStr])+'|'
        # 将Front和Rear指针打印出来
        LEFTS=' '*((1+Length)*self.Front+Length//2-1)+'Front'+'\n'+' '*((1+Length)*self.Front+Length//2-1)+' ↓ →→→→→'
        RIGHTS=' '*((1+Length)*self.Rear+Length//2-1)+'→→↑'+'\n'+' '*((1+Length)*self.Rear+Length//2-1)+'Rear'
        # 设置上下行
        GAP='-'*len(LS)
        FIRST='\n整个数组的状态如下:\n\n'+LEFTS+'\n'+GAP+'\n'+LS+'\n'+GAP+'\n'+RIGHTS
        return FIRST
    
    def Push(self,Value:any)->bool:
        """元素入队"""
        # 如果已满,则无法入队
        if self.Tag:
            return False
        # 将Rear设置为Value
        self.Element[self.Rear]=Value
        # 将Rear指向下一个位置
        self.Rear=(self.Rear+1)%len(self.Element)
        # 如果Front==Rear且此时队列必定非空,那么队列必定已满
        self.Tag=True if self.Front==self.Rear else False
        return True
    
    def Pop(self)->bool:
        """元素出队"""
        # 判断队列是否为空
        if not self.Tag and self.Front==self.Rear:
            return False
        # 如果非空,则直接将队首设置成下一个元素即可
        self.Front=(self.Front+1)%len(self.Element)
        # 出队后,队列必定不满
        self.Tag=False
        return True

# 测试函数
def main()->None:
    """测试函数"""
    IScontinue=1
    TestDeque=Deque(int(input('请输入要创建的循环队列的大小:')))
    print(TestDeque.DequeRepr())
    MENU='\n可进行如下操作:\n1、入队\n2、出队\n请输入要进行的操作序号:'
    while IScontinue==1:
        cho=int(input(MENU))
        if cho==1:
            result=TestDeque.Push(int(input('请输入要入队的元素:')))
            if not result:
                print("\033[%dm\033[1;%dm%s\033[0m"%(41,37,'队列已满,入队失败.'))
            else:
                print("\033[%dm\033[1;%dm%s\033[0m"%(42,37,'入队成功.'))
        elif cho==2:
            result=TestDeque.Pop()
            if not result:
                print("\033[%dm\033[1;%dm%s\033[0m"%(41,37,'队列中没有元素,不可以出队.'))
            else:
                print("\033[%dm\033[1;%dm%s\033[0m"%(42,37,'出队成功.'))
        else: continue
        print(TestDeque.DequeRepr())
        IScontinue=int(input('请输入是否继续: 1 or 0\n'))

if __name__=='__main__':
    main()
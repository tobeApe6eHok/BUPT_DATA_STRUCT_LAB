"""数据结构第4次实验 实验环境:WIN10 + VScode + python 3.10.0"""

class Node:
    
    def __init__(self,v) -> None:
        """定义每个节点的内部结构"""
        self.Val=v           # 定义value值
        self.Left=None       # 定义Left子节点的指针
        self.Right=None      # 定义Right子节点的指针

class Tree:

    def __init__(self,Nodes:list) -> None:
        """使用层序遍历结果Nodes初始化二叉树"""
        # 如果层序遍历结果为空,则说明二叉树为空,将根节点设置为None即可
        if len(Nodes)==0:
            self.Root=None
            return 
        # 将根节点的value设置为层序遍历第一个值
        self.Root=Node(Nodes[0])
        # remain是还未设置Left和Right的节点和其在Nodes中的位置
        remain=[[self.Root,0]]
        while len(remain)>0:
            node,place=remain.pop(0)
            # 得到左子节点、右子节点在层序遍历结果中的下标
            leftPlace=place*2+1
            rightPlace=leftPlace+1
            # 如果下标合法,则创建Left节点或者Right节点
            # 并放入remain中
            if leftPlace<len(Nodes) and Nodes[leftPlace]!=None:
                node.Left=Node(Nodes[leftPlace])
                remain.append([node.Left,leftPlace])
            if rightPlace<len(Nodes) and Nodes[rightPlace]!=None:
                node.Right=Node(Nodes[rightPlace])
                remain.append([node.Right,rightPlace])
        return 

    def NonRECURSIVEpre(self)->list:
        """非递归实现前序遍历"""
        # result是前序遍历的结果
        result=[]
        # 如果Root为空,则表示二叉树为空,返回空列表
        if self.Root==None:
            return result
        # remain表示模拟的栈
        remain=[self.Root]
        # 只要栈中还有元素,就代表还未遍历完
        while len(remain)>0:
            # 最后一个元素出栈
            node=remain.pop(-1)
            # 获得子树根节点值
            result.append(node.Val)
            # 先让右子节点入栈,后让左子节点入栈
            if node.Right!=None:
                remain.append(node.Right)
            if node.Left!=None:
                remain.append(node.Left)
        return result
    
    def RECURSIVEpre(self)->list:
        """递归实现前序遍历"""
        # result是前序遍历的结果
        result=[]
        # 如果Root为空,则表示二叉树为空,返回空列表
        if self.Root==None:
            return result
        # 递归函数闭包
        def recursive(node)->None:
            # 按照顺序递归遍历当前节点、左子树、右子树
            result.append(node.Val)
            if node.Left!=None:
                recursive(node.Left)
            if node.Right!=None:
                recursive(node.Right)
        recursive(self.Root)
        return result

    def MORRISpre(self)->list:
        """Morris非递归算法"""
        # result是前序遍历的结果
        result=[]
        # 如果Root为空,则表示二叉树为空,返回空列表
        if self.Root==None:
            return result
        # 将最初的当前节点设置为根节点
        node1=self.Root
        # 直到当前节点为None,代表所有节点都已遍历
        while node1!=None:
            # 判断其左子节点是否为空
            node2=node1.Left
            # 若非空
            if node2!=None:
                # 则需要找到当前节点的中序遍历前驱节点
                # 因为在Morris算法中将所有节点都和前驱节点连起来一次,所以需要加上两个判断条件
                while node2.Right!=None and node2.Right!=node1:
                    node2=node2.Right
                # 如果还未连接
                if node2.Right==None:
                    result.append(node1.Val)
                    # 连接前驱节点和当前节点
                    node2.Right=node1
                    # 将当前节点设置为其左子节点
                    node1=node1.Left
                    continue
                # 如果已经连接
                else:
                    # 以为在连接时,已经取过其值,故只需要遍历其右子树即可
                    node2.Right=None
            # 若为空,只需要先取其值,然后遍历其右子树即可
            else:
                result.append(node1.Val)
            # 默认将当前节点设置为其右子节点
            node1=node1.Right
        return result


def main(Nodes:list,num:int):
    """测试程序"""
    print('\n测试 '+str(num)+' :')
    t=Tree(Nodes)
    print('递归前序遍历:')
    print('            '+str(t.NonRECURSIVEpre()))
    print('栈模拟递归算法:')
    print('             '+str(t.RECURSIVEpre()))
    print('Morris算法:')
    print('              '+str(t.MORRISpre()))
    
    
if __name__=='__main__':
    a=[1,2,3,4,5,6,7,None,8,9,None,10,11,None,12]
    b=[1,2,3,4,5,None,6,None,7,8,9,None,None,10,None,None,None,11,12,None,None,13,14,None,None,None,None,None,15]
    # 测试一
    main(a,1)
    # 测试二
    main(b,2)
    #input()


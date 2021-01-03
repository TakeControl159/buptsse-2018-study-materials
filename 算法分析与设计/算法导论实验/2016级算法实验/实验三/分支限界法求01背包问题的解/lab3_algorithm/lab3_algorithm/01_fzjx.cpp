#include <iostream>

using namespace std;
    //tree node

    typedef struct _treenode{

    //struct _treenode *liveNode; //活节点

    double upperProfit; //节点的价值上界

    double profit; //节点价值*

    double weight; //节点重量

    int level; //活节点在子树中所处的层序号

    //bool left;

    }TreeNode;

    void initNode(TreeNode &node, double up, double p, double w, int lev)

    {

    node.upperProfit = up; node.profit = p; node.weight = w; node.level = lev;

    }

    ///////////////////////////////////////////////////////////////////////////////////

    #define MAX_LENGTH 20

    //class LQueue

    class LQueue{

    public:

    LQueue() {length = 0;}

    virtual ~LQueue(){}

    void addTail(TreeNode tn);

    TreeNode removeHead();

    TreeNode removeMax();

    TreeNode removeMin();

    int GetLength(){return length;}

    protected:

    private:

    //int queue[MAX_LENGTH];

    TreeNode queue[MAX_LENGTH]; //序号0处开始存储   

    int length; //节点个数

    };

    void LQueue::addTail(TreeNode tn)

    {

    queue[length++] = tn;

    }

    TreeNode LQueue::removeHead()

    {

    return queue[--length];

    }

    TreeNode LQueue::removeMax()

    {

    double max = 0.0;

    int num = -1;

    for (int i = 0; i < length; i++)

    {

    if (max < queue[i].profit)

    {

    max = queue[i].profit;

    num = i;

    }

    }

    TreeNode lq = queue[num];

    for (int j = num; j < (length-1); j++) //删除节点

    {

    queue[j] = queue[j+1];

    }

    length--;

    return lq;

    }

    TreeNode LQueue::removeMin() //该程序不用

    {

    return TreeNode();

    }

    ////////////////////////////////////////////////////////////////////////////////////

    #define ARRAY_LENGTH 4 //物品数

    LQueue queue;

    double w[] = {3, 5, 2, 1}; double p[] = {9, 10, 7, 4}; int sort[ARRAY_LENGTH];  //{3, 2, 0, 1}

    double c; //背包容量7

    double cw; //当前重量

    double cp; //当前价值

    double bestp; //当前最优价值

    void init(double cc); //初始化

    void sortpw(); //以物品单位重量价值递减序列排序存储于sort[]中   

    double bound(int i); //计算i层节点价值的上界(i: 0 ~ ARRAY_LENGTH-1)

    double bbKnapsack(); //分支限界法求0/1背包问题的解

 int main()

    {

    init(7.0);

    sortpw();

    double max = bbKnapsack();

	cout<<endl;
	
	cout<<"背包大小为7，共有4个物品，重量为3, 5, 2, 1，价值为9, 10, 7, 4 "<<endl;

    cout<<endl<<endl<<"最大价值为："<<max<<endl;

	//system("pause");
	return 0;

    }

    void init(double cc)

    {

    c = cc;

    cw = 0.0; cp = 0.0; bestp = 0.0;

    }

    void sortpw()

    {

    double pw[ARRAY_LENGTH];

    for (int i = 0; i < ARRAY_LENGTH; i++)

    {

    pw[i] = p[i] / w[i];

    }

    for (int i = 0; i < ARRAY_LENGTH; i++)

    {

    double max = 0.0;

    for (int j = 0; j < ARRAY_LENGTH; j++)

    {

    if (max < pw[j])

    {

    max = pw[j];

    sort[i] = j;

    }

    }

    pw[sort[i]] = 0.0;

    }

    }

    double bound(int i)

    {

    double cleft = c - cw;

    double b = cp;

    while (i < ARRAY_LENGTH && w[sort[i]] <= cleft)

    {

    cleft -= w[sort[i]];

    b += p[sort[i]];

    i++;

    }

    if (i < ARRAY_LENGTH)

    {

    b += p[sort[i]] / w[sort[i]] * cleft;

    }

    return b;

    }

    double bbKnapsack()

    {

    int i = 0; //从0层开始

    double bestp = 0.0;

    double up = bound(0);

    while(i != ARRAY_LENGTH)

    {

    double wt = cw + w[sort[i]];

    if (wt <= c) //左儿子节点为可行节点

    {

    if (bestp < (cp+p[sort[i]]))

    {

    bestp = cp + p[sort[i]];

    }

    TreeNode *node = new TreeNode();

    initNode(*node, up, (cp+p[sort[i]]), (cw+w[sort[i]]), i+1); queue.addTail(*node);

    }

    up = bound(i+1);

    if (bestp <= up) //右儿子节点

    {

    TreeNode *node = new TreeNode();

    initNode(*node, up, cp, cw, i+1); queue.addTail(*node);

    }

    TreeNode tnode = queue.removeMax();

    cout<<tnode.weight<<"-"<<tnode.profit<<"  ";  //输出当前节点的价值(价值递增)

    cw = tnode.weight; cp = tnode.profit; up = tnode.upperProfit; i = tnode.level;

    }

    return bestp;

    }

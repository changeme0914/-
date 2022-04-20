/*注：本程序需用CB运行*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define Max_Vertex_Num 100 ///最大顶点数
typedef struct///输入图的信息
{
    char vex;///顶点信息
    char start;///一条边的两个顶点start,endx
    char endx;///
} Node;

/**图的邻接表存储结构**/
typedef struct ArcNode///表结点
{
    int adjvex;///该弧所指的顶点编号
    struct ArcNode *nextarc;///指向下一条弧的指针
    int weight;///权值
} ArcNode;
typedef struct VNode///表头结点
{
    char vertex;///顶点信息
    ArcNode *firstarc;///指向第一条依附于该顶点的弧的指针
} VNode;

typedef VNode AdjList[Max_Vertex_Num];///表头向量
typedef struct
{
    AdjList adjlist;///邻接表
    int vexnum,arcnum;///顶点数和边数
} ALGraph;
typedef struct
{
    char vexs[Max_Vertex_Num];///顶点向量
    int arcs[Max_Vertex_Num][Max_Vertex_Num];///邻接矩阵
    int vexnum,arcnum;///顶点数和边数
} Mgraph;
///////////////////////////////////////////////////////////////////
int LocateVex1(Mgraph *G,char u);
void CreateMGraph(Mgraph *G,int n,int m,Node *q);
void DispMatrix(Mgraph G);
int LocateVex2(ALGraph *G,char u);
void CreateALGraph(ALGraph *G,int n,int m,Node *q);
void DispAdjList(ALGraph G);
void changeAdjlist(Mgraph g,ALGraph *G);
void changeMGraph(Mgraph *G,ALGraph g);
void BfsALGraph(ALGraph G,int n,int v);
void Dfs(Mgraph G,int i,int visited[],int *t);
void DFSTraverse(Mgraph G,int n,int *t);

///////////////////////////////////////////////////////////////////
int main()
{
    Mgraph G1,G4;
    ALGraph G2,G3;
    Node q[100];
    int n,m,i,l,t=0;
    printf("输入顶点数和边数:\n");
    scanf("%d %d",&n,&m);
    printf("输入每个顶点(顶点须为大写字母 例：A B C D E):\n");
    for(i=0; i<n; i++)
    {
        getchar();
        scanf("%c",&q[i].vex);
    }
    printf("输入每条边(输入方式 例：AB AD BC CD CE):\n");
    for(i=0; i<m; i++)
    {
        getchar();
        scanf("%c%c",&q[i].start,&q[i].endx);
    }
    printf("*******************************************************************************************\n");
    printf("                            1.输出图的邻接矩阵G\n");
	printf("                            2.输出图的邻接表G\n");
	printf("                            3.邻接矩阵G转换成邻接表G\n");
	printf("                            4.邻接表G转换成邻接邻阵G\n");
    printf("                            5.以邻接表G为存储结构的图的广度优先搜索\n");
	printf("                            6.以邻接矩阵G为存储结构的图的深度优先搜索\n");
	printf("                            7.退出\n");
	printf("*******************************************************************************************\n");
    
	while(1)
	{
	printf("请选择您需要的功能（输入数字即可）\n");
	scanf("%d",&l);
		if(l==1){
    printf("输出图的邻接矩阵G:\n");
    CreateMGraph(&G1,n,m,q);
    DispMatrix(G1);}
		if(l==2){
    printf("输出图的邻接表G:\n");
    CreateALGraph(&G2,n,m,q);
    DispAdjList(G2);}
		if(l==3){
    printf("邻接矩阵G转换成邻接表G:\n");
    changeAdjlist(G1,&G3);
    printf("转换前邻接矩阵G:\n");
    DispMatrix(G1);
    printf("转换后邻接表G:\n");
    DispAdjList(G3);}
		if(l==4){
    printf("邻接表G转换成邻接邻阵G:\n");
    changeMGraph(&G4,G3);
    printf("转换前邻接表G:\n");
    DispAdjList(G2);
    printf("转换后邻接矩阵G:\n");
    DispMatrix(G4);}
		if(l==5){
    printf("以邻接表G为存储结构的图的广度优先搜索:\n");
    BfsALGraph(G2,n,0);
    printf("\n");}
		if(l==6){
    printf("以邻接矩阵G为存储结构的图的深度优先搜索:\n");
    DFSTraverse(G1,n,&t);
	printf("\n");}
	if(l==7)
        exit(1);
	}
    return 0;
}

///////////////////////////////////////////////////////////////////
///构建邻接矩阵
int LocateVex1(Mgraph *G,char u)
{
    int i;
    for(i=0; i<G->vexnum; i++)///用循环查找该结点
    {
        if(G->vexs[i]==u)
            return i;
    }
    return -1;
}
void CreateMGraph(Mgraph *G,int n,int m,Node *q)
{
    int i,j,k;
    ///顶点数
    G->vexnum=n;
    ///边数
    G->arcnum=m;
    ///顶点信息
    for(i=0; i<G->vexnum; i++)
    {
        G->vexs[i]=q[i].vex;
    }
    ///初始化邻接矩阵
    for(i=0; i<G->vexnum; i++)
    {
        for(j=0; j<G->vexnum; j++)
        {
            G->arcs[i][j]=0;
        }
    }
    for(k=0; k<G->arcnum; k++)
    {
        char v1=q[k].start;///每条边的顶点v1,v2
        char v2=q[k].endx;
        i=LocateVex1(G,v1);///查找v1,v2在图中的位置
        j=LocateVex1(G,v2);
        if((i==-1)||(j==-1))
            printf("该条边不存在\n");
        else
        {
            G->arcs[i][j]=1;///该条边存在赋值为1
            G->arcs[j][i]=1;
        }
    }
}
///输出邻接矩阵
void DispMatrix(Mgraph G)
{
    int i,j;
    printf("  ");
    for(i=0;i<G.vexnum;i++)
    {
        printf("%c ",G.vexs[i]);
    }
    printf("\n");
    for(i=0; i<G.vexnum; i++)
    {
        printf("%c ",G.vexs[i]);
        for(j=0; j<G.vexnum; j++)
            printf("%d ",G.arcs[i][j]);
        printf("\n");
    }
}
///创建邻接表
int LocateVex2(ALGraph *G,char u)
{
    int i;
    for(i=0; i<G->vexnum; i++)///用循环查找该结点
    {
        if(G->adjlist[i].vertex==u)
            return i;
    }
    return -1;
}
void CreateALGraph(ALGraph *G,int n,int m,Node *q)
{
    ArcNode *p1,*p2;
    int i,j,k;
    ///顶点数
    G->vexnum=n;
    ///边数
    G->arcnum=m;
    ///顶点信息
    for(k=0; k<G->vexnum; k++)
    {
        G->adjlist[k].vertex=q[k].vex;
        G->adjlist[k].firstarc=NULL;///表头数组链域的值为空
    }
    k=0;
    while(k<G->arcnum)
    {
        char v1=q[k].start;///每条边的顶点对v1,v2
        char v2=q[k].endx;
        i=LocateVex2(G,v1);///查找v1,v2在图中的位置
        j=LocateVex2(G,v2);
        if((i==-1)||(j==-1))
            printf("该边不存在!\n");
        else
        {
            k++;///边计数
            p1=(ArcNode *)malloc(sizeof(ArcNode));///申请空间，生成表结点
            p1->adjvex=j;
            p1->nextarc=G->adjlist[i].firstarc;///将p1指针指向当前顶点指向的结点
            G->adjlist[i].firstarc=p1;///将结点j插入第i个链表中
            p2=(ArcNode *)malloc(sizeof(ArcNode));///申请空间，生成表结点
            p2->adjvex=i;
            p2->nextarc=G->adjlist[j].firstarc;///将p2指针指向当前顶点指向的结点
            G->adjlist[j].firstarc=p2;///将结点i插入第j个链表中
        }
    }
}
///输出邻接表
void DispAdjList(ALGraph G)
{
    ArcNode *p;
    int i;
    for(i=0; i<G.vexnum; i++)
    {
        printf("%c:",G.adjlist[i].vertex);
        for(p=G.adjlist[i].firstarc; p!=NULL; p=p->nextarc)
            printf("->%c",p->adjvex+'A');
        printf("\n");
    }
}
///邻接矩阵化为邻接表
void changeAdjlist(Mgraph g,ALGraph *G)
{
    int i,j;
    ArcNode *p;
    for (i=0; i<g.vexnum; i++)
    {///给邻接表中所有头节点的指针域置初值
        G->adjlist[i].vertex=g.vexs[i];
        G->adjlist[i].firstarc=NULL;
    }
    for (i=0; i<g.vexnum; i++)                ///检查邻接矩阵中每个元素
        for (j=g.vexnum-1; j>=0; j--)
            if (g.arcs[i][j]!=0)       ///存在一条边
            {
                p=(ArcNode *)malloc(sizeof(ArcNode));   ///创建一个节点*p
                p->adjvex=j;
                p->nextarc=G->adjlist[i].firstarc;        ///采用头插法插入*p
                G->adjlist[i].firstarc=p;
            }
    G->vexnum=g.vexnum;
    G->arcnum=g.arcnum;
}
///邻接表转换为邻接矩阵
void changeMGraph(Mgraph *G,ALGraph g)
{
    int i;
    ArcNode *p;
    for(i=0;i<g.vexnum;i++)
        G->vexs[i]=g.adjlist[i].vertex;
    for(i=0;i<g.vexnum;i++)
    {
        p=g.adjlist[i].firstarc;

        while(p!=NULL)
        {
            G->arcs[i][p->adjvex]=1;///边存在赋值为1
            p=p->nextarc;
        }
    }
    G->vexnum=g.vexnum;
    G->arcnum=g.arcnum;
}
///以邻接表为存储结构的图的广度优先搜索
void BfsALGraph(ALGraph G,int n,int v)///n个顶点，从第v个顶点开始遍历
{
    ArcNode *p;
    int i,j;
    int Q[n+1],r,f;///Q数组为循环队列，f,r分别为队头和队尾指针
    int visited[n];///定义访问标志数组
    for(i=0;i<G.vexnum;i++)
    {
        visited[i]=0;///访问标志向量初始化
    }
    r=0;f=0;///初始化队列
    visited[v]=1;///将第v个顶点标志为已遍历
    printf("%c",G.adjlist[v].vertex);///输出第v个顶点
    r=(r+1)%(n+1);
    Q[r]=v;///将第v个顶点入队列
    while(f!=r)
    {
        f=(f+1)%(n+1);
        j=Q[f];///当队列不空时，删除队头元素并置为j
        p=G.adjlist[j].firstarc;
        while(p!=NULL)///找顶点j的没有被访问的邻接点
        {
            if(visited[p->adjvex]==0)
            {
                printf(" %c",p->adjvex+'A');///输出邻接点
                visited[p->adjvex]=1;
                r=(r+1)%(n+1);
                Q[r]=p->adjvex;
            }
            p=p->nextarc;
        }
    }

}
///以邻接矩阵为存储结构的图的深度优先搜索
void Dfs(Mgraph G,int i,int visited[],int *t)
{
    int j;
    visited[i]=1;///标志i已被访问过
    if(t+1==G.vexnum)
    {
        printf("%c ",G.vexs[i]);///输出已被标志的顶点
    }
    else
    {
        printf("%c ",G.vexs[i]);///输出已被标志的顶点
        t++;
    }
    for(j=0;j<G.vexnum;j++)
    {
        if(G.arcs[i][j]!=0&&!visited[j])///如果未被访问且未被标志，则进行Dfs
        {
            Dfs(G,j,visited,&t);
        }
    }
}

void DFSTraverse(Mgraph G,int n,int *t)
{
    int visited[n];///定义访问标志数组
    int i;
    for(i=0;i<G.vexnum;i++)
        visited[i]=0;///访问标志向量初始化
    for(i=0;i<G.vexnum;i++)///检查图中每个顶点是否被访问过
    {
        if(!visited[i])///i未被访问过,从i开始进行Dfs搜索
            Dfs(G,i,visited,&t);
    }
}



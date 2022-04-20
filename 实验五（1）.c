/*ע������������CB����*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define Max_Vertex_Num 100 ///��󶥵���
typedef struct///����ͼ����Ϣ
{
    char vex;///������Ϣ
    char start;///һ���ߵ���������start,endx
    char endx;///
} Node;

/**ͼ���ڽӱ�洢�ṹ**/
typedef struct ArcNode///����
{
    int adjvex;///�û���ָ�Ķ�����
    struct ArcNode *nextarc;///ָ����һ������ָ��
    int weight;///Ȩֵ
} ArcNode;
typedef struct VNode///��ͷ���
{
    char vertex;///������Ϣ
    ArcNode *firstarc;///ָ���һ�������ڸö���Ļ���ָ��
} VNode;

typedef VNode AdjList[Max_Vertex_Num];///��ͷ����
typedef struct
{
    AdjList adjlist;///�ڽӱ�
    int vexnum,arcnum;///�������ͱ���
} ALGraph;
typedef struct
{
    char vexs[Max_Vertex_Num];///��������
    int arcs[Max_Vertex_Num][Max_Vertex_Num];///�ڽӾ���
    int vexnum,arcnum;///�������ͱ���
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
    printf("���붥�����ͱ���:\n");
    scanf("%d %d",&n,&m);
    printf("����ÿ������(������Ϊ��д��ĸ ����A B C D E):\n");
    for(i=0; i<n; i++)
    {
        getchar();
        scanf("%c",&q[i].vex);
    }
    printf("����ÿ����(���뷽ʽ ����AB AD BC CD CE):\n");
    for(i=0; i<m; i++)
    {
        getchar();
        scanf("%c%c",&q[i].start,&q[i].endx);
    }
    printf("*******************************************************************************************\n");
    printf("                            1.���ͼ���ڽӾ���G\n");
	printf("                            2.���ͼ���ڽӱ�G\n");
	printf("                            3.�ڽӾ���Gת�����ڽӱ�G\n");
	printf("                            4.�ڽӱ�Gת�����ڽ�����G\n");
    printf("                            5.���ڽӱ�GΪ�洢�ṹ��ͼ�Ĺ����������\n");
	printf("                            6.���ڽӾ���GΪ�洢�ṹ��ͼ�������������\n");
	printf("                            7.�˳�\n");
	printf("*******************************************************************************************\n");
    
	while(1)
	{
	printf("��ѡ������Ҫ�Ĺ��ܣ��������ּ��ɣ�\n");
	scanf("%d",&l);
		if(l==1){
    printf("���ͼ���ڽӾ���G:\n");
    CreateMGraph(&G1,n,m,q);
    DispMatrix(G1);}
		if(l==2){
    printf("���ͼ���ڽӱ�G:\n");
    CreateALGraph(&G2,n,m,q);
    DispAdjList(G2);}
		if(l==3){
    printf("�ڽӾ���Gת�����ڽӱ�G:\n");
    changeAdjlist(G1,&G3);
    printf("ת��ǰ�ڽӾ���G:\n");
    DispMatrix(G1);
    printf("ת�����ڽӱ�G:\n");
    DispAdjList(G3);}
		if(l==4){
    printf("�ڽӱ�Gת�����ڽ�����G:\n");
    changeMGraph(&G4,G3);
    printf("ת��ǰ�ڽӱ�G:\n");
    DispAdjList(G2);
    printf("ת�����ڽӾ���G:\n");
    DispMatrix(G4);}
		if(l==5){
    printf("���ڽӱ�GΪ�洢�ṹ��ͼ�Ĺ����������:\n");
    BfsALGraph(G2,n,0);
    printf("\n");}
		if(l==6){
    printf("���ڽӾ���GΪ�洢�ṹ��ͼ�������������:\n");
    DFSTraverse(G1,n,&t);
	printf("\n");}
	if(l==7)
        exit(1);
	}
    return 0;
}

///////////////////////////////////////////////////////////////////
///�����ڽӾ���
int LocateVex1(Mgraph *G,char u)
{
    int i;
    for(i=0; i<G->vexnum; i++)///��ѭ�����Ҹý��
    {
        if(G->vexs[i]==u)
            return i;
    }
    return -1;
}
void CreateMGraph(Mgraph *G,int n,int m,Node *q)
{
    int i,j,k;
    ///������
    G->vexnum=n;
    ///����
    G->arcnum=m;
    ///������Ϣ
    for(i=0; i<G->vexnum; i++)
    {
        G->vexs[i]=q[i].vex;
    }
    ///��ʼ���ڽӾ���
    for(i=0; i<G->vexnum; i++)
    {
        for(j=0; j<G->vexnum; j++)
        {
            G->arcs[i][j]=0;
        }
    }
    for(k=0; k<G->arcnum; k++)
    {
        char v1=q[k].start;///ÿ���ߵĶ���v1,v2
        char v2=q[k].endx;
        i=LocateVex1(G,v1);///����v1,v2��ͼ�е�λ��
        j=LocateVex1(G,v2);
        if((i==-1)||(j==-1))
            printf("�����߲�����\n");
        else
        {
            G->arcs[i][j]=1;///�����ߴ��ڸ�ֵΪ1
            G->arcs[j][i]=1;
        }
    }
}
///����ڽӾ���
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
///�����ڽӱ�
int LocateVex2(ALGraph *G,char u)
{
    int i;
    for(i=0; i<G->vexnum; i++)///��ѭ�����Ҹý��
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
    ///������
    G->vexnum=n;
    ///����
    G->arcnum=m;
    ///������Ϣ
    for(k=0; k<G->vexnum; k++)
    {
        G->adjlist[k].vertex=q[k].vex;
        G->adjlist[k].firstarc=NULL;///��ͷ���������ֵΪ��
    }
    k=0;
    while(k<G->arcnum)
    {
        char v1=q[k].start;///ÿ���ߵĶ����v1,v2
        char v2=q[k].endx;
        i=LocateVex2(G,v1);///����v1,v2��ͼ�е�λ��
        j=LocateVex2(G,v2);
        if((i==-1)||(j==-1))
            printf("�ñ߲�����!\n");
        else
        {
            k++;///�߼���
            p1=(ArcNode *)malloc(sizeof(ArcNode));///����ռ䣬���ɱ���
            p1->adjvex=j;
            p1->nextarc=G->adjlist[i].firstarc;///��p1ָ��ָ��ǰ����ָ��Ľ��
            G->adjlist[i].firstarc=p1;///�����j�����i��������
            p2=(ArcNode *)malloc(sizeof(ArcNode));///����ռ䣬���ɱ���
            p2->adjvex=i;
            p2->nextarc=G->adjlist[j].firstarc;///��p2ָ��ָ��ǰ����ָ��Ľ��
            G->adjlist[j].firstarc=p2;///�����i�����j��������
        }
    }
}
///����ڽӱ�
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
///�ڽӾ���Ϊ�ڽӱ�
void changeAdjlist(Mgraph g,ALGraph *G)
{
    int i,j;
    ArcNode *p;
    for (i=0; i<g.vexnum; i++)
    {///���ڽӱ�������ͷ�ڵ��ָ�����ó�ֵ
        G->adjlist[i].vertex=g.vexs[i];
        G->adjlist[i].firstarc=NULL;
    }
    for (i=0; i<g.vexnum; i++)                ///����ڽӾ�����ÿ��Ԫ��
        for (j=g.vexnum-1; j>=0; j--)
            if (g.arcs[i][j]!=0)       ///����һ����
            {
                p=(ArcNode *)malloc(sizeof(ArcNode));   ///����һ���ڵ�*p
                p->adjvex=j;
                p->nextarc=G->adjlist[i].firstarc;        ///����ͷ�巨����*p
                G->adjlist[i].firstarc=p;
            }
    G->vexnum=g.vexnum;
    G->arcnum=g.arcnum;
}
///�ڽӱ�ת��Ϊ�ڽӾ���
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
            G->arcs[i][p->adjvex]=1;///�ߴ��ڸ�ֵΪ1
            p=p->nextarc;
        }
    }
    G->vexnum=g.vexnum;
    G->arcnum=g.arcnum;
}
///���ڽӱ�Ϊ�洢�ṹ��ͼ�Ĺ����������
void BfsALGraph(ALGraph G,int n,int v)///n�����㣬�ӵ�v�����㿪ʼ����
{
    ArcNode *p;
    int i,j;
    int Q[n+1],r,f;///Q����Ϊѭ�����У�f,r�ֱ�Ϊ��ͷ�Ͷ�βָ��
    int visited[n];///������ʱ�־����
    for(i=0;i<G.vexnum;i++)
    {
        visited[i]=0;///���ʱ�־������ʼ��
    }
    r=0;f=0;///��ʼ������
    visited[v]=1;///����v�������־Ϊ�ѱ���
    printf("%c",G.adjlist[v].vertex);///�����v������
    r=(r+1)%(n+1);
    Q[r]=v;///����v�����������
    while(f!=r)
    {
        f=(f+1)%(n+1);
        j=Q[f];///�����в���ʱ��ɾ����ͷԪ�ز���Ϊj
        p=G.adjlist[j].firstarc;
        while(p!=NULL)///�Ҷ���j��û�б����ʵ��ڽӵ�
        {
            if(visited[p->adjvex]==0)
            {
                printf(" %c",p->adjvex+'A');///����ڽӵ�
                visited[p->adjvex]=1;
                r=(r+1)%(n+1);
                Q[r]=p->adjvex;
            }
            p=p->nextarc;
        }
    }

}
///���ڽӾ���Ϊ�洢�ṹ��ͼ�������������
void Dfs(Mgraph G,int i,int visited[],int *t)
{
    int j;
    visited[i]=1;///��־i�ѱ����ʹ�
    if(t+1==G.vexnum)
    {
        printf("%c ",G.vexs[i]);///����ѱ���־�Ķ���
    }
    else
    {
        printf("%c ",G.vexs[i]);///����ѱ���־�Ķ���
        t++;
    }
    for(j=0;j<G.vexnum;j++)
    {
        if(G.arcs[i][j]!=0&&!visited[j])///���δ��������δ����־�������Dfs
        {
            Dfs(G,j,visited,&t);
        }
    }
}

void DFSTraverse(Mgraph G,int n,int *t)
{
    int visited[n];///������ʱ�־����
    int i;
    for(i=0;i<G.vexnum;i++)
        visited[i]=0;///���ʱ�־������ʼ��
    for(i=0;i<G.vexnum;i++)///���ͼ��ÿ�������Ƿ񱻷��ʹ�
    {
        if(!visited[i])///iδ�����ʹ�,��i��ʼ����Dfs����
            Dfs(G,i,visited,&t);
    }
}



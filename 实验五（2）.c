//ע:���������н������������Ҫ�ȴ�����Ż������ʾ
//����ʵ������ 9 12        v1 v2 v3 v4 v5 v6 v7 v8 v9
/*
v1 v2 a1 6
v1 v3 a2 4 
v1 v4 a3 5
v2 v5 a4 1
v3 v5 a5 1
v3 v6 a6 1
v4 v6 a7 2
v5 v7 a8 9
v5 v8 a9 8
v6 v8 a10 4
v7 v9 a11 2
v8 v9 a12 4
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define MAX 100
int earlist[MAX];
int least[MAX];
int indegree[MAX];
int outdegree[MAX];
typedef struct 
{
	char v[10];
	char w[10];
	char s[10];
}Bool;
typedef struct
{
	Bool hd[MAX];
	char td[MAX][10];
	int jz[MAX][MAX];
	int tds;
	int bs;
}Mjz;
/////////////////////////////////////////////////////////////////////////////
int Locatevex(Mjz *G,char u[10]);
void Greatljjz(Mjz *G);
void ljjzschu(Mjz *G);
void gegree(Mjz *G);
void tupo1(Mjz *G);
int tupo(Mjz *G);
void outtupo(Mjz *G);
void outtupo2(Mjz *G,int EAR);
/////////////////////////////////////////////////////////////////////////////

int main()
{
	Mjz g;
	int e,i,j,t,h;
	printf("***************************************************************************************\n");
	printf("\t1:����AOE���ڽӾ���洢�ṹ\n");
	printf("\t2:�жϴ˹����ܷ�˳������(��������������������)\n");
	printf("\t3:����Щ�ӹ�����Ӱ���������ڵ��깤ʱ��(�����ؼ�·���͹ؼ�·�����ȼ��ؼ��)\n");
	printf("\t4:�˳�\n");
	printf("***************************************************************************************\n");
	while(1)
	{
		printf("ѡ����:");
		scanf("%d",&t);
		getchar();
		switch(t)
		{
		case 1: 
			Greatljjz(&g);
			ljjzschu(&g);
			break;
		case 2:
			gegree(&g);
			printf("�����������:");
			tupo1(&g);
	        printf("\n");
			printf("�����������:");
			outtupo(&g);
			printf("\n");
			break;
		case 3:
			gegree(&g);
        	e=tupo(&g);
	        if(e!=-1)
			{
				printf("�ؼ�·������:");
				printf("%d \n",e);
				outtupo2(&g,e);
				printf("�ؼ�·��(�ؼ��):\n");
				for(i=0;i<g.tds;i++)
				{
					for(j=g.tds-1;j>=0;j--)
					{
						if((g.jz[i][j]!=0)&&(earlist[i]+g.jz[i][j]==least[j]))
						{
							printf("<%s,%s>",g.td[i],g.td[j]);
							for(h=0;h<g.bs;h++)
							{
								if(strcmp(g.hd[h].v,g.td[i])==0&&strcmp(g.hd[h].w,g.td[j])==0)
									printf("(%s)  ",g.hd[h].s);//	printf("\n");
							}
						}
					}
				}
			}
			printf("\n");
			break;
		case 4:
			exit(1);
			break;
		}
	}
	return 0;
}


int Locatevex(Mjz *G,char u[10])
{
	int i,j=-1;
	for(i=0;i<G->tds;++i)
	{
		if(strcmp(G->td[i],u)==0)
		{
			j=i;
			break;
		}
	}
	return j;
}
void Greatljjz(Mjz *G)
{
	int i,j,k,m,n,w;
	char v1[10],v2[10],s[10];
	printf("�����뽨���ڽӾ���Ķ������ͱ���(��:9 12):");
	scanf("%d%d",&(G->tds),&(G->bs));
	printf("�����붥��(��:v1 v2 v3...):");
	for(i=0;i<G->tds;i++)
	{
		getchar();
		scanf("%s",&(G->td[i]));
	}
	for(i=0;i<G->tds;i++)
	{
		for(j=0;j<G->tds;j++)
		{
			G->jz[i][j]=0;
		}
	}
	printf("����߶�Ӧ�Ķ��� ��� Ȩֵ(��:v1 v2 a1 6):\n");
	for(k=0;k<G->bs;k++)
	{
		getchar();
		scanf("%s %s %s %d",&v1,&v2,&s,&w);
		strcpy(G->hd[k].v,v1);
		strcpy(G->hd[k].w,v2);
		strcpy(G->hd[k].s,s);
		m=Locatevex(G,v1);
		n=Locatevex(G,v2);
		if((m==-1)||(n==-1))
			printf("�ñ߲����ڣ�����������\n");
		else
		{
			G->jz[m][n]=w;
		}
	}
}
void ljjzschu(Mjz *G)
{
	int i,j;
	printf("�ڽӾ����ʾΪ:\n");
	for(i=0;i<G->tds;i++)
	{
		for(j=0;j<G->tds;j++)
				printf("%d ",G->jz[i][j]);
		printf("\n");
	}
}
void gegree(Mjz *G)
{
	int i,j,t;
	for(i=0;i<G->tds;i++)
	{
		t=0;
		for(j=0;j<G->tds;j++)
			if(G->jz[i][j]!=0)
				t++;
	outdegree[i]=t;
	}
	for(i=0;i<G->tds;i++)
	{
		t=0;
		for(j=0;j<G->tds;j++)
			if(G->jz[j][i]!=0)
				t++;
	indegree[i]=t;
	}
}
void tupo1(Mjz *G)
{
	int i,rear=0,head=0,t,h=0;
	int qune[MAX];
	char sj[MAX][10];
	for(i=0;i<G->tds;i++)
	{
		if(indegree[i]==0)
		{
			qune[rear++]=i;
		}
	}
	while(rear>head)
	{
		t=qune[head++];
		strcpy(sj[h],G->td[t]);
		h++;
		for(i=0;i<G->tds;i++)
		{
			if(G->jz[t][i]!=0)
			{
				if(--indegree[i]==0)
				{
					qune[rear++]=i;
				}
			}
		}
	}
	for(i=0;i<G->tds;i++)
		printf("%s ",sj[i]);
}
int tupo(Mjz *G)
{
	int i,rear=0,head=0;
	int qune[MAX];
	int count=0;
	int t,Max;
	for(i=0;i<G->tds;i++)
	{
		if(indegree[i]==0)
		{
			qune[rear++]=i;
		}
	}
	while(rear>head)
	{
		count++;
		t=qune[head++];
		for(i=0;i<G->tds;i++)
		{
			if(G->jz[t][i]!=0)
			{
				if(--indegree[i]==0)
				{
					qune[rear++]=i;
				}
				if(earlist[i]<earlist[t]+G->jz[t][i])
					earlist[i]=earlist[t]+G->jz[t][i];
			}
		}
	}
	if(count==G->tds)
	{
		for(i=0;i<G->tds;i++)
		{
			if(earlist[i]>Max)
				Max=earlist[i];
		}
		return Max;
	}
	else
		return -1;
}
void outtupo(Mjz *G)
{
	int i,rear=0,head=0;
	int qune[MAX];
	char sj[MAX][10];
	int t,h=0;
	for(i=0;i<G->tds;i++)
	{
		if(outdegree[i]==0)
		{
			qune[rear++]=i;
		}
	}
	while(rear>head)
	{
		t=qune[head++];
		strcpy(sj[h],G->td[t]);
	    h++;
		for(i=0;i<G->tds;i++)
		{

			if(G->jz[i][t]!=0)
			{
				if(--outdegree[i]==0)
				{
					qune[rear++]=i;
				}
			}
		}
	}
	for(i=0;i<G->tds;i++)
		printf("%s ",sj[i]);
}
void outtupo2(Mjz *G,int EAR)
{
	int i,rear=0,head=0;
	int quna[MAX];
	int t;
	for(i=0;i<G->tds;i++)
	{
		least[i]=EAR;
		if(outdegree[i]==0)
		{
			quna[rear++]=i;
		}
	}
	while(rear>head)
	{
		t=quna[head++];
		for(i=0;i<G->tds;i++)
		{
			if((G->jz[i][t]!=0))
			{
				if(--outdegree[i]==0)
				{
					quna[rear++]=i;
				}
				if(least[i]>least[t]-G->jz[i][t])
					least[i]=least[t]-G->jz[i][t];
			}
		}
	}
}

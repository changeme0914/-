#include<stdio.h>
#include<stdlib.h>
typedef struct park{
int num;
int time;
int size;
int cur;
}slinklist[100];
typedef struct Node
{
	int num;
	int time;
	struct Node *next;
}queuenode;

typedef struct LinkQueue
{
	queuenode *front;
	queuenode *rear;
	int size;
}linkqueue;//队列（便道）

void initspace(slinklist space,int n)//初始化备用链表
{
	int i;
	for(i=0;i<n;i++)
	{
		space[i].cur=i+1;
		space[i].size=0;
	}
     space[n].cur=0;
	 space[n].size=0;
}
int Malloc(slinklist space)//从备用链表取一个结点
{
    int i=space[0].cur;
    if(i)
    space[0].cur=space[i].cur;
    return i;
}
void Free(int k,slinklist space)//将空闲结点链接到备用链表中
{
    space[k].cur=space[0].cur;
    space[0].cur=k;
}
void creatduilie(linkqueue *q) // 队列的初始化
{
	q->front=(queuenode *)malloc(sizeof(queuenode));
	q->rear=q->front;
	q->front->next=NULL;
	q->size=0;

}
int ruduilie(linkqueue *q,int *num,int *time)//入队列
{
	queuenode *l;
	l=(queuenode *)malloc(sizeof(queuenode));
	if(l!=NULL)
	{
		l->num=*num;
		l->time=*time;
		l->next=NULL;
		q->rear->next=l;
		q->rear=l;
		q->size++;
       return 1;

	}
	else
		return 0;

}
int chuduilie(linkqueue *q,int *num1,int *time1)//出队列
{
	queuenode *l;
	if(q->front==q->rear)
		return 0;
	l=q->front->next;
	q->front->next=l->next;
	if(q->rear==l)
		q->rear=q->front;
	*num1=l->num;
	*time1=l->time;
	free(l);
	q->size--;
	return 1;
}
int huo(linkqueue *q,int *num)
{
	queuenode *p;
	if(q->front==q->rear)
		return 0;
	p=q->front->next;
	*num=p->num;
	return 1;
}

int t=1;

void wang(slinklist space)

{
	int i=1;
	while(1)
{           
	           

               if(space[i].size==1)
			   {
				   printf("%d号车位有%d号车\n",i,space[i].num);
                   i=space[i].cur;
				   if(i==0)
					   break;
			    
			   } 
              if(space[i].size==0)
			   {	
                 printf("%d号车位没有车\n",i);
                i=space[i].cur;
                  if(i==0)
					   break;
			   }

	
               
}
}

void arrive(slinklist space,int num,int time,linkqueue *q)

{ 
	int s,w;

   if(w=zhao(num,space))
   {
	   if(space[w].size==1)
	   printf("停车场内已有该号车不能重号\n");
	   if(space[w].size==0)
	   {
         	s=Malloc(space);
    space[s].num=num;
	space[s].time=time;
	space[s].size=1;
	
	 if(s!=1)
	 space[t].cur=s; 
	 t=s;
	 

  if(s)
    printf("%d号车进入停车场,在%d号车库\n",num,t);
  else
  {
    ruduilie(q,&num,&time);
	printf("停车场已满,%d号车在%d号便道等待\n",num,q->size);

  }
	   }
   }
else
{

    
	s=Malloc(space);
    space[s].num=num;
	space[s].time=time;
	space[s].size=1;
	 if(s!=1)
	 space[t].cur=s; 
	 t=s;
   
if(s)
    printf("%d号车进入停车场,在%d号车库\n",num,t);
  else
  {
    ruduilie(q,&num,&time);
	printf("停车场已满,%d号车在%d号便道等待\n",num,q->size);

  }
}
 



}
int zhao(int num,slinklist space)
{
	int i=1,a=0;
 
   while(i)
   {
	   
		   if(num==space[i].num)
	{	a=i;
		  
        break;
	}
   
else
{
     i=space[i].cur;
	 if(i==space[i].cur)
		 break;
}
	   

   }
    return a;
             
}
int checkroad_free(int num,linkqueue *q)
{ 
	queuenode *l;
	l=q->front->next;
	while(q->front!=q->rear)
	{
		if(l->num==num)
			return 1;
		l=l->next;

	}
	return 0;

}


void leave(slinklist space,int num,int time,linkqueue *q)
{
        int w,l,k,sum,num1,time1;
        if(k=zhao(num,space))
	 {
          sum=10*(time-space[k].time);
          printf("%d号车在%d号车库停车时长为%d小时，共收费%d元\n",num,k,time-space[k].time,sum);
           if(q->size!=0)
		   {
             chuduilie(q,&num1,&time1);
             space[k].num=num1;
             space[k].time=time1;
             printf("%d号车从便道进入%d号车库，进入时间为%d\n",num1,k,time);
			 space[k].time=time;
		   }
           else
		   {
             Free(k,space);
			 space[k].size=0;
		   }
	}
       else
	   {
        if(l=checkroad_free(num,q))
		{
			if(q->front->next->num==num)
			{
	
         chuduilie(q,&num1,&time1);
		printf("车牌号为%d号的车辆未进出停车场从便道离开\n",num1);
			}
          else if(q->front->next->num !=num)
		  {
		      huo(q,&w);
            
			while(q->front->next->num!=num)
			{
			chuduilie(q,&num1,&time1);
			ruduilie(q,&num1,&time1);

			}
          
		chuduilie(q,&num1,&time1);
		printf("车牌号为%d号的车辆未进出停车场从便道离开\n",num);
       if(q->front->next->num!=w)
	   {
			chuduilie(q,&num1,&time1);
			ruduilie(q,&num1,&time1);
	   }
		  } 
		}  
	   

       else
         printf("输入错误!\n");
	   }


}


int main()
{ 
	int n,w;
	int num,time; 
	char stu;
    slinklist space;
    linkqueue *q;
    q=(linkqueue *)malloc(sizeof(linkqueue));
    creatduilie(q);
	printf("请输入停车场内车位数:");
	scanf("%d",&n);
    initspace(space,n);
   
     printf("********* 停车场程序****\n\n");
	 printf("停车1小时收取10元\n");
       printf("键盘输入1，查看停车位\n");
	   printf("键盘输入2，查看便道车位\n");
	   printf("键盘输入3，进行车辆信息的输入、输出，还可以查看停车场和便道的状态\n");
     printf("************************\n\n");
   while(1)
   {
	    printf("请键盘输入1或2或3\n");
	    scanf("%d",&w);
		if(w!=1&w!=2&w!=3)
		{
			printf("输入错误，请重新输入\n");
		}
		else
		{
	if(w==3)
	{
		printf("请依次输入车辆到达A离去D结束E信息、车牌号以及当前时间：例如E 0 0   \n\n");
    	printf("==========================================================\n");
	   getchar();
     scanf("%c%d%d",&stu,&num,&time);
     switch(stu)
	 {
    case 'A': arrive(space,num,time,q);
	         break;
    case 'D': leave(space,num,time,q);
		     break;
	case'E': printf("程序结束\n");
		break;
		return 0;
	default:printf("第一个字母输入错误\n");
	 }

   }
	if(w==2)
	{
		printf("便道上有%d辆车在排队等待\n",q->size);
	}
	if(w==1)
	{
      wang(space);
	}
	if(stu=='E')
		break;
	
		}
   }
  return 0;
   }
 








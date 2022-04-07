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
}linkqueue;//���У������

void initspace(slinklist space,int n)//��ʼ����������
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
int Malloc(slinklist space)//�ӱ�������ȡһ�����
{
    int i=space[0].cur;
    if(i)
    space[0].cur=space[i].cur;
    return i;
}
void Free(int k,slinklist space)//�����н�����ӵ�����������
{
    space[k].cur=space[0].cur;
    space[0].cur=k;
}
void creatduilie(linkqueue *q) // ���еĳ�ʼ��
{
	q->front=(queuenode *)malloc(sizeof(queuenode));
	q->rear=q->front;
	q->front->next=NULL;
	q->size=0;

}
int ruduilie(linkqueue *q,int *num,int *time)//�����
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
int chuduilie(linkqueue *q,int *num1,int *time1)//������
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
				   printf("%d�ų�λ��%d�ų�\n",i,space[i].num);
                   i=space[i].cur;
				   if(i==0)
					   break;
			    
			   } 
              if(space[i].size==0)
			   {	
                 printf("%d�ų�λû�г�\n",i);
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
	   printf("ͣ���������иúų������غ�\n");
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
    printf("%d�ų�����ͣ����,��%d�ų���\n",num,t);
  else
  {
    ruduilie(q,&num,&time);
	printf("ͣ��������,%d�ų���%d�ű���ȴ�\n",num,q->size);

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
    printf("%d�ų�����ͣ����,��%d�ų���\n",num,t);
  else
  {
    ruduilie(q,&num,&time);
	printf("ͣ��������,%d�ų���%d�ű���ȴ�\n",num,q->size);

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
          printf("%d�ų���%d�ų���ͣ��ʱ��Ϊ%dСʱ�����շ�%dԪ\n",num,k,time-space[k].time,sum);
           if(q->size!=0)
		   {
             chuduilie(q,&num1,&time1);
             space[k].num=num1;
             space[k].time=time1;
             printf("%d�ų��ӱ������%d�ų��⣬����ʱ��Ϊ%d\n",num1,k,time);
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
		printf("���ƺ�Ϊ%d�ŵĳ���δ����ͣ�����ӱ���뿪\n",num1);
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
		printf("���ƺ�Ϊ%d�ŵĳ���δ����ͣ�����ӱ���뿪\n",num);
       if(q->front->next->num!=w)
	   {
			chuduilie(q,&num1,&time1);
			ruduilie(q,&num1,&time1);
	   }
		  } 
		}  
	   

       else
         printf("�������!\n");
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
	printf("������ͣ�����ڳ�λ��:");
	scanf("%d",&n);
    initspace(space,n);
   
     printf("********* ͣ��������****\n\n");
	 printf("ͣ��1Сʱ��ȡ10Ԫ\n");
       printf("��������1���鿴ͣ��λ\n");
	   printf("��������2���鿴�����λ\n");
	   printf("��������3�����г�����Ϣ�����롢����������Բ鿴ͣ�����ͱ����״̬\n");
     printf("************************\n\n");
   while(1)
   {
	    printf("���������1��2��3\n");
	    scanf("%d",&w);
		if(w!=1&w!=2&w!=3)
		{
			printf("�����������������\n");
		}
		else
		{
	if(w==3)
	{
		printf("���������복������A��ȥD����E��Ϣ�����ƺ��Լ���ǰʱ�䣺����E 0 0   \n\n");
    	printf("==========================================================\n");
	   getchar();
     scanf("%c%d%d",&stu,&num,&time);
     switch(stu)
	 {
    case 'A': arrive(space,num,time,q);
	         break;
    case 'D': leave(space,num,time,q);
		     break;
	case'E': printf("�������\n");
		break;
		return 0;
	default:printf("��һ����ĸ�������\n");
	 }

   }
	if(w==2)
	{
		printf("�������%d�������Ŷӵȴ�\n",q->size);
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
 








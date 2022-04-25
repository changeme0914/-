#include<stdio.h>
#include<string.h>
#include<math.h>
#include<malloc.h>
typedef int ElemType;
///�����������Ķ���������ṹ
typedef struct BTNode
{
    ElemType key;
    struct BTNode *lchild, *rchild;
} BTNode, *BSTree;

//////////////////////////////////////////
void menu();//�˵�
BSTree InsertBST(BSTree T, BTNode *s);///��������������
BSTree CreateBST();
BTNode *SearchBST(BSTree T, int key);///����
BTNode *SearchBST_F(BSTree T, int key, BSTree *F);
BSTree SearchDeleteBST(BSTree T, int key);
BSTree InsertBST_key(BSTree T, int key);///����
BSTree deleteBST(BSTree T, BTNode *p, BTNode *f);///ɾ��
//////////////////////////////////////////
int main()
{
    BSTree T,T1;
    int n,key;
    menu();
    while(1)
    {
		printf("������ѡ��:\n");
        scanf("%d",&n);
		switch(n)
		{
        case 1:
        
            T=CreateBST();
            break;
        case 2:
        
            printf("������ҵĹؼ���:\n");
            scanf("%d",&key);
            T1=SearchBST(T,key);
			if(T1==NULL)
				printf("����ʧ��!\n");
			else
				printf("���ҳɹ�!\n");
			break;
        case 3:
        
            printf("����Ҫ����Ĺؼ���:\n");
            scanf("%d",&key);
            T=InsertBST_key(T,key);
			break;
        case 4:
        
            printf("����Ҫɾ���Ĺؼ���:\n");
            scanf("%d",&key);
            T=SearchDeleteBST(T,key);
			break;
        case 5:
			exit(1);
		}
    }
    return 0;
}


void menu()
{
    printf("*******************************************\n");
    printf("\t1.�����������Ľ���\n");
    printf("\t2.�����������Ĳ���\n");
    printf("\t3.�����������Ĳ���\n");
    printf("\t4.������������ɾ��\n");
    printf("\t5.�˳�\n");
    printf("*******************************************\n");
}


///��������������
BSTree InsertBST(BSTree T, BTNode *s)
{
    if(T == NULL)
        T = s;
    else
    {
        if(s->key < T->key)
            T->lchild = InsertBST(T->lchild, s);
        else
        {
            if(s->key > T->key)
                T->rchild = InsertBST(T->rchild, s);
        }
    }
    return T;
}
BSTree CreateBST()
{
    BSTree T, s;
    int key;
    T = NULL;
    printf("����ؼ���key,����-1����.\n");
    while(1)
    {
        scanf("%d", &key);
        if(key == -1)
		{
			printf("�����ɹ�!\n");
            break;
		}
        else
        {
            s = (BTNode*)malloc(sizeof(BTNode));
            s->key = key;
            s->lchild = NULL;
            s->rchild = NULL;
            T = InsertBST(T, s);
        }
    }
    return T;
}
///����
BTNode *SearchBST(BSTree T, int key)
{
    if(T == NULL)
    {
        //printf("����ʧ��!\n");
        return NULL;
    }
    else
    {
        if(key == T->key)
        {
            //printf("���ҳɹ�!\n");
            return T;
        }
        else
        {
            if(key < T->key)
                return (SearchBST(T->lchild, key));
            else
                return (SearchBST(T->rchild, key));
        }
    }
}
///����
BSTree InsertBST_key(BSTree T, int key)
{
    BTNode *s;
    s = SearchBST(T, key);
    if(s)
    {
        printf("�ؼ���%d�Ѵ���!\n", s->key);
    }
    else
    {
        s = (BTNode*)malloc(sizeof(BTNode));
        s->key = key;
        s->lchild = NULL;
        s->rchild = NULL;
        T = InsertBST(T, s);
        printf("����ɹ�!\n");
    }
    return T;
}
///ɾ��
BTNode *SearchBST_F(BSTree T, int key, BSTree *F)
{
    if(T == NULL)
        return NULL;
    if(key == T->key)
        return T;
    else
    {
        *F = T;
        if(key < T->key)
            return (SearchBST_F(T->lchild, key, F));
        else
            return (SearchBST_F(T->rchild, key, F));
    }
}
BSTree deleteBST(BSTree T, BTNode *p, BTNode *f)
{
    /*  ɾ��pָ��ָ��Ľ�㣬fָ��p��˫�׽�㣬Tָ�������ָ�� */
    BTNode *par, *s;
    int kind;
    if(!p->lchild && !p->rchild)
        kind = 1; /*���1��*pΪҶ�ӽ��*/
    else  if (!p->rchild)
        kind = 2; /*���2��*pֻ��������*/
    else  if(!p->lchild)
        kind = 3; /*���2��*pֻ��������*/
    else
        kind = 4; /*���3��*p��������������*/
    switch(kind)
    {
    case 1:
        if(!f)
            T = NULL;
        else
        {
            if(f->lchild == p)
                f->lchild = NULL;
            else
                f->rchild = NULL;
            free(p);
        }
        break;
    case 2:
        if(!f)
            T = p->lchild;
        else
        {
            if(p == f->lchild)
                f->lchild = p->lchild;
            else
                f->rchild = p->lchild;
        }
        free(p);
        break;
    case 3:
        if(!f)
            T = p->rchild;
        else
        {
            if(p == f->lchild)
                f->lchild = p->rchild;
            else
                f->rchild = p->rchild;
        }
        free(p);
        break;
    case 4:
        par = p;
        s = p->lchild;
        while(s->rchild != NULL)
        {
            par = s;
            s = s->rchild;
        }
        p->key = s->key;
        if(par == p)
            par->lchild = s->lchild;
        else
            par->rchild = s->lchild;
        free(s);
        break;
    }
    return T;
}
BSTree SearchDeleteBST(BSTree T, int key)
{
    BTNode *f, *p;
    f = NULL;
    p = SearchBST_F(T, key, &f);
    if(p)
    {
        T = deleteBST(T, p, f);
		printf("ɾ���ɹ�!\n");
    }
    else
    {
        printf("�ؼ���Ϊ%d�ļ�¼������!\n",key);
    }
	//printf("ɾ���ɹ�!\n");
    return T;
}


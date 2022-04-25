#include<stdio.h>
#include<string.h>
#include<math.h>
#include<malloc.h>
typedef int ElemType;
///二叉排序树的二叉链表储存结构
typedef struct BTNode
{
    ElemType key;
    struct BTNode *lchild, *rchild;
} BTNode, *BSTree;

//////////////////////////////////////////
void menu();//菜单
BSTree InsertBST(BSTree T, BTNode *s);///创建二叉排序树
BSTree CreateBST();
BTNode *SearchBST(BSTree T, int key);///查找
BTNode *SearchBST_F(BSTree T, int key, BSTree *F);
BSTree SearchDeleteBST(BSTree T, int key);
BSTree InsertBST_key(BSTree T, int key);///插入
BSTree deleteBST(BSTree T, BTNode *p, BTNode *f);///删除
//////////////////////////////////////////
int main()
{
    BSTree T,T1;
    int n,key;
    menu();
    while(1)
    {
		printf("请输入选项:\n");
        scanf("%d",&n);
		switch(n)
		{
        case 1:
        
            T=CreateBST();
            break;
        case 2:
        
            printf("输入查找的关键字:\n");
            scanf("%d",&key);
            T1=SearchBST(T,key);
			if(T1==NULL)
				printf("查找失败!\n");
			else
				printf("查找成功!\n");
			break;
        case 3:
        
            printf("输入要插入的关键字:\n");
            scanf("%d",&key);
            T=InsertBST_key(T,key);
			break;
        case 4:
        
            printf("输入要删除的关键字:\n");
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
    printf("\t1.二叉排序树的建立\n");
    printf("\t2.二叉排序树的查找\n");
    printf("\t3.二叉排序树的插入\n");
    printf("\t4.二叉排序树的删除\n");
    printf("\t5.退出\n");
    printf("*******************************************\n");
}


///创建二叉排序树
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
    printf("输入关键字key,输入-1结束.\n");
    while(1)
    {
        scanf("%d", &key);
        if(key == -1)
		{
			printf("建立成功!\n");
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
///查找
BTNode *SearchBST(BSTree T, int key)
{
    if(T == NULL)
    {
        //printf("查找失败!\n");
        return NULL;
    }
    else
    {
        if(key == T->key)
        {
            //printf("查找成功!\n");
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
///插入
BSTree InsertBST_key(BSTree T, int key)
{
    BTNode *s;
    s = SearchBST(T, key);
    if(s)
    {
        printf("关键字%d已存在!\n", s->key);
    }
    else
    {
        s = (BTNode*)malloc(sizeof(BTNode));
        s->key = key;
        s->lchild = NULL;
        s->rchild = NULL;
        T = InsertBST(T, s);
        printf("插入成功!\n");
    }
    return T;
}
///删除
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
    /*  删除p指针指向的结点，f指向p的双亲结点，T指向根结点的指针 */
    BTNode *par, *s;
    int kind;
    if(!p->lchild && !p->rchild)
        kind = 1; /*情况1，*p为叶子结点*/
    else  if (!p->rchild)
        kind = 2; /*情况2，*p只有左子树*/
    else  if(!p->lchild)
        kind = 3; /*情况2，*p只有右子树*/
    else
        kind = 4; /*情况3，*p左右子树均不空*/
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
		printf("删除成功!\n");
    }
    else
    {
        printf("关键字为%d的记录不存在!\n",key);
    }
	//printf("删除成功!\n");
    return T;
}


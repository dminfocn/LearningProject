//
//  main.c
//  线性表链式存储
//
//  Created by apple on 2017/10/30.
//  Copyright © 2017年 apple. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20   /*存储空间初始分配*/

typedef int EleType;/* ElemType类型根据实际情况而定，这里假设为int */
typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

typedef struct Node{
    EleType data;
    struct Node *next;
}Node;
typedef struct Node *LinkList;/* 定义LinkList */

/* 初始化顺序线性表 */
Status InitList(LinkList *L) {
    *L = (LinkList) malloc(sizeof(Node));/* 产生头结点,并使L指向此头结点 */
    if(!(*L)) {/* 存储分配失败 */
        return ERROR;
    }
    (*L) -> next = NULL;/* 指针域为空 */
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
EleType ListLength(LinkList L) {
    int i = 0;
    LinkList p = L -> next;
    while (p) {
        i++;
        p = p->next;
    }
    return i;
}

/* 初始条件：顺序线性表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
Status ListInsert(LinkList *L, int i, EleType e) {
    LinkList p, s;
    int j;
    p = *L;
    j = 1;
    while (p && j < i) {
        p = p -> next;
        j++;
    }
    if(!p || j>i) {
        return ERROR;
    }
    s = (LinkList) malloc(sizeof(Node));
    s ->data = e;
    s->next = p->next; /* 将p的后继结点赋值给s的后继  */
    p -> next = s; /* 将s赋值给p的后继 */
    return OK;
}

Status Visit(EleType e) {
    printf("%d,",e);
    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(LinkList L) {
    LinkList p = L->next;
    while (p) {
        Visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
Status ListEmpty(LinkList L) {
    if(L->next) {
        return FALSE;
    }else {
        return TRUE;
    }
}

/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(LinkList *L) {
    LinkList p,q;
    p = (*L) -> next;
    while (p) {
        q = p->next;
        free(q);
        p = q;
    }
    (*L) -> next = NULL;
    return OK;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值 */
Status GetElem(LinkList L, int i, EleType *e) {
    LinkList p;
    int m;
    if(i > MAXSIZE) {
        return ERROR;
    }
    p = L->next;
    m = 1;
    while (p && m < i) {
        m++;
        p = p->next;
    }
    if(!p || m > i) {
        return ERROR;
    }
    *e = p -> data;
    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
int LocateElem(LinkList L, EleType e) {
    int m = 0;
    LinkList p;
    p = L -> next;
    while (p) {
        m++;
        if(p->data == e) {
            return m;
        }
        p = p -> next;
    }
    return 0;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(LinkList *L, int i, EleType *e) {
    LinkList p,q;
    int m = 1;
    p = (*L);
    while (p->next && m < i) {
        m++;
        p = p->next;
    }
    if(!(p->next) || m > i) {
        return ERROR;
    }
    q = p -> next;
    p->next = q->next;
    *e = q -> data;
    free(q);
    return OK;
}

/*  随机产生n个元素的值，建立带表头结点的单链线性表L（头插法） */
void CreateListHead(LinkList *L, int n) {
    LinkList p;
    int i;
    srand(time(0));
    *L = (LinkList) malloc(sizeof(Node));
    (*L) -> next = NULL;
    for(i=0; i<n; i++) {
        p = (LinkList) malloc(sizeof(Node));
        p -> data = rand() % 100 + 1;
        p -> next = (*L) -> next;
        (*L) -> next = p;
    }
}

/*  随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法） */
void CreateListTail(LinkList *L, int n) {
    LinkList p, q;
    int i;
    srand(time(0));
    *L = (LinkList) malloc(sizeof(Node));
    q = *L;
    for(i=0; i<n; i++) {
        p = (LinkList) malloc(sizeof(Node));
        p -> data = rand() % 100 + 1;
        q -> next = p;
        q = p;
    }
    q -> next = NULL;
}


int main(int argc, const char * argv[]) {
    LinkList L;
    EleType e;
    Status i;
    int j,k;
    i = InitList(&L);
    printf("初始化L后：ListLength(L)=%d\n",ListLength(L));
    
    for(j=1; j<=5; j++) {
        i = ListInsert(&L, 1, j);/*从头部依次插入*/
    }
    printf("在L的表头依次插入1～5后：L.data=");
    ListTraverse(L);
    
    printf("ListLength(L)=%d \n",ListLength(L));
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);
    
    i=ClearList(&L);
    printf("清空L后：ListLength(L)=%d\n",ListLength(L));
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);
    
    for(j=1; j<=10; j++) {
        i = ListInsert(&L, j, j);
    }
    printf("尾部插入十个数据后L长度为：%d\n", ListLength(L));
    ListTraverse(L);
    
    i = ListInsert(&L, 1, 0);
    printf("在表头插入0后长度为：%d\n", ListLength(L));
    ListTraverse(L);
    
    GetElem(L,5,&e);
    printf("L的第五个元素为：%d\n", e);
    ListTraverse(L);
    
    for(j=3;j<=4;j++)
    {
        k=LocateElem(L,j);
        if(k)
        printf("值为%d是L的第%d个元素\n",k,j);
        else
        printf("没有值为%d的元素\n",j);
    }
    
    k= ListLength(L); /* k为表长 */
    for(j=k+1;j>=k;j--)
    {
        i=ListDelete(&L,j,&e); /* 删除第j个数据 */
        if(i==ERROR) {
            printf("删除第%d个数据失败\n",j);
        }else {
            printf("删除第%d个的元素值为：%d\n",j,e);
        }
    }
    printf("依次输出元素：");
    ListTraverse(L);
    
    j = 5;
    ListDelete(&L, j, &e);
    printf("删除第%d个的元素值为：%d\n",j,e);
    
    printf("依次输出L的元素：");
    ListTraverse(L);
    
    i=ClearList(&L);
    printf("\n清空L后：ListLength(L)=%d\n",ListLength(L));
    CreateListHead(&L,20);
    printf("整体创建L的元素(头插法)：");
    ListTraverse(L);
    
    i=ClearList(&L);
    printf("\n删除L后：ListLength(L)=%d\n",ListLength(L));
    CreateListTail(&L,20);
    printf("整体创建L的元素(尾插法)：");
    ListTraverse(L);
    
    return 0;
}

//
//  main.c
//  静态链表
//
//  Created by apple on 2017/10/31.
//  Copyright © 2017年 apple. All rights reserved.
//

#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 1000

typedef char EleType;
typedef int Status;

typedef struct {
    EleType data;
    int cur; /*游标，为零时表示无指向*/
} Component, StaticLinkList[MAXSIZE];

/*初始化链表*/
Status InitList(StaticLinkList space) {
    int i;
    for(i=0; i<MAXSIZE-1; i++) {
        space[i].cur = i+1;
    }
    space[MAXSIZE-1].cur = 0;/*目前静态链表为空，最后一个元素的cur为0*/
    return OK;
}

/* 初始条件：静态链表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(StaticLinkList space) {
    int j=0;
    int k = space[MAXSIZE - 1].cur;
    while (k) {
        k = space[k].cur;
        j++;
    }
    return j;
}

/* 若备用空间链表非空，则返回分配的结点下标，否则返回0 */
int Malloc_SSL(StaticLinkList L) {
    int i = L[0].cur;
    if(L[0].cur) {
        L[0].cur = L[i].cur;
    }
    return i;
}

/*  在L中第i个元素之前插入新的数据元素e   */
Status ListInsert(StaticLinkList L, int i, EleType e) {
    int j, k, l;
    k = MAXSIZE - 1;/* 注意k首先是最后一个元素的下标 */
    if(i<1 || i>ListLength(L) + 1) {
        return ERROR;
    }
    j = Malloc_SSL(L);//获得空闲分量的下标
    if(j) {
        L[j].data = e;
        for(l=1; l<=i-1; l++) {/* 找到第i个元素之前的位置 */
            k = L[k].cur;
        }
        L[j].cur = L[k].cur;
        L[k].cur = j;
        return OK;
    }
    return OK;
}

Status VisitChar(EleType e) {
    printf("%c",e);
    return OK;
}

Status ListTraverse(StaticLinkList L) {
    int i = L[MAXSIZE-1].cur;
    while (i) {
        VisitChar(L[i].data);
        i = L[i].cur;
    }
    printf("\n");
    return OK;
}

/*  将下标为k的空闲结点回收到备用链表 */
void Free_SSL(StaticLinkList space, int k) {
    space[k].cur = space[0].cur;/* 把第一个元素的cur值赋给要删除的分量cur */
    space[0].cur = k;/* 把要删除的分量下标赋值给第一个元素的cur */
}

/*  删除在L中第i个数据元素   */
Status ListDelete(StaticLinkList L, int i) {
    int j, k;
    if(i<1 || i>MAXSIZE+1) {
        return ERROR;
    }
    
    k = MAXSIZE -1;
    for(j=1; j<=i-1; j++) {
        k = L[k].cur;
    }
    j = L[k].cur;
    L[k].cur = L[j].cur;
    Free_SSL(L, j);
    return OK;
}
int main(int argc, const char * argv[]) {
    
    StaticLinkList L;
    Status i;
    i = InitList(L);
    printf("初始化后链表长度为：%d\n",ListLength(L));
    
    i=ListInsert(L,1,'F');
    i=ListInsert(L,1,'E');
    i=ListInsert(L,1,'D');
    i=ListInsert(L,1,'B');
    i=ListInsert(L,1,'A');
    printf("\n在L的表头依次插入FEDBA后：\nL.data=");
    ListTraverse(L);
    
    i=ListInsert(L,3,'C');
    printf("\n在L的“B”与“D”之间插入“C”后：\nL.data=");
    ListTraverse(L);
    
    i=ListDelete(L,1);
    printf("\n在L的删除“A”后：\nL.data=");
    ListTraverse(L);
    printf("\n");
    return 0;
}

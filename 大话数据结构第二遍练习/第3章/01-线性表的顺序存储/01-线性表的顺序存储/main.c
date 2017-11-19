//
//  main.c
//  01-线性表的顺序存储
//
//  Created by 朱占龙 on 2017/11/19.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#include <stdio.h>

#define MAXSIZE 20 /*存储空间初始分配量*/

#define  OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#warning - 注意位置索引和数组索引之间的转换

typedef int Status;/*程序运行的状态*/

typedef int ElemType;/*根据实际情况而定，此处暂定为int类型*/
typedef struct {
    ElemType data[MAXSIZE];/*数组存储数据元素，最大值为MAXSIZE*/
    int length;
}SqList;

/*初始化一个链表*/
Status InitList(SqList *L) {
    L->length = 0;
    return OK;
}

/*判断线性表是否为空*/
Status ListEmpty(SqList L) {
    if (L.length == 0) {
        return TRUE;
    }else {
        return FALSE;
    }
}

/*将线性表清空*/
Status ClearList(SqList *L) {
    return OK;
}
/*获取线性表L中i位置的元素值返回给e*/
Status GetEle(SqList L, int i, int *e) {
    return OK;
}

/*查找与给定值e相等的元素，若成功返回序号，否则返回0*/
Status LocateElem(SqList L, int e) {
    return OK;
}

/*在线性表L的第i个位置插入新元素e*/
Status ListInsert(SqList *L, int i, int e) {
    int k;
    if (L->length == MAXSIZE) {
        return ERROR;
    }
    if (i<1 || i>L->length+1) {
        return ERROR;
    }
    if (i <= L->length) {//不在表尾插入
        for (k=L->length-1; k>=i-1; k--) {
            L->data[k+1] = L->data[k];
        }
    }
    
    L->data[i-1] = e;
    L->length++;
    return OK;
}

/*删除线性表L中第i个位置的元素，并用e返回*/
Status ListDelete(SqList *L, int i, int *e) {
    return OK;
}

/*计算线性表的长度*/
int ListLength(SqList L) {
    return L.length;
}

void visti(int i) {
    printf("%d ",i);
}
void print(SqList L) {
    int i;
    for (i=0; i<=L.length-1; i++) {
        visti(L.data[i]);
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    
    SqList L;
    ElemType e;
    Status i;
    
    //初始化一个顺序存储的链表
    InitList(&L);
    printf("初始化后L的长度为：%d\n",ListLength(L));
    
    int j;
    for (j=1; j<=5; j++) {
        i = ListInsert(&L, 1, j);
    }
    printf("在表头依次插入五个数据元素后：\n");
    print(L);
    
    printf("L.length=%d \n",L.length);
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);
    
    return 0;
}

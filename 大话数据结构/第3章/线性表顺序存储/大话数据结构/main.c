//
//  main.c
//  大话数据结构
//
//  Created by 朱占龙 on 2017/10/29.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20       /*存储空间初始分配*/

typedef int Status;      /* Status是函数的类型,其值是函数结果状态代码，如OK等*/
typedef int EleType;     /* EleType类型根据实际情况而定，此处为int*/

typedef struct {
    EleType data[MAXSIZE];
    int length;
}SqList;

/*初始化顺序线性表*/
Status InitList(SqList *L) {
    L->length = 0;
    return OK;
}

/*顺序线性表中插入值*/
Status ListInsert(SqList *L, int i, EleType e) {
    int k;
    if (L->length == MAXSIZE) {/*顺序线性表已满*/
        return ERROR;
    }
    if (i<1 || i > L->length + 1) {
        return ERROR;
    }
    if (i <= L->length) {/*插入数据位置不在表尾*/
        for (k=L->length-1; k>=i-1; k--) {
            L->data[k+1] = L->data[k];
        }
    }
    L->data[i-1] = e;
    L->length++;
    
    return OK;
}

Status visit(EleType e) {
    printf("%d",e);
    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(SqList L) {
    int i;
    for (i=0; i<L.length; i++) {
        visit(L.data[i]);
    }
    printf("\n");
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
Status ListEmpty(SqList L) {
    if (L.length == 0) {
        return TRUE;
    }else {
        return FALSE;
    }
}

/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(SqList *L) {
    L -> length = 0;
    return OK;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值,注意i是指位置，第1个位置的数组是从0开始 */
Status GetElem(SqList L, int i, EleType *e) {
    if (L.length == 0 || i<1 || i>L.length) {
        return ERROR;
    }
    *e = L.data[i-1];
    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
EleType LocateElem(SqList L, EleType e) {
    int i;
    if (L.length == 0) {
        return ERROR;
    }
    for (i=1; i<L.length; i++) {
        if (i == e) {
            break;
        }
    }
    if (i > L.length) {
        return ERROR;
    }
    return i+1;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(SqList *L, int i, EleType *e) {
    int m;
    if (L->length == 0) {
        return ERROR;
    }
    if (i < 1 || i > L->length) {
        return ERROR;
    }
    *e = L->data[i-1];
    for (m=i; m<L->length; m++) {/*要删除元素在中间，则要将数据前移*/
        L->data[m-1] = L->data[m];
    }
    L->length--;
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(SqList L) {
    return L.length;
}

void unionL(SqList *La,SqList Lb) {
    int La_len,Lb_len,i;
    EleType e;
    La_len=ListLength(*La);
    Lb_len=ListLength(Lb);
    for (i=1;i<=Lb_len;i++)
    {
        GetElem(Lb,i,&e);
        if (!LocateElem(*La,e))
            ListInsert(La,++La_len,e);
    }
}

int main(int argc, const char * argv[]) {
    SqList L;
    SqList Lb;
    
    EleType e;
    Status i;
    int j,k;
    i = InitList(&L);
    printf("初始化L后，长度为：%d\n",L.length);
    
    for (j=1; j<=5; j++) {
        i = ListInsert(&L, 1, j);
    }
    printf("在L的表头一次插入5个数据后，L.data=");
    
    ListTraverse(L);
    
    printf("L.length = %d \n", L.length);
    i = ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);
    
    i = ClearList(&L);
    printf("清空L后：L.length=%d\n",L.length);
    i = ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);
    
    for (j=1; j<=10; j++) {
        ListInsert(&L, j, j);
    }
    printf("在L的表尾依次插入1～10后：L.data=");
    ListTraverse(L);
    
    printf("L.length=%d \n",L.length);
    ListInsert(&L, 1, 0);
    printf("在L的表头插入0后：L.data=");
    ListTraverse(L);
    printf("L.length=%d \n",L.length);
    
    GetElem(L, 5, &e);
    printf("第5个元素的值为:%d\n",e);
    
    for (j=3; j<=4; j++) {
        k = LocateElem(L, j);
        if (k) {
            printf("第%d个元素的值为%d\n",k,j);
        }else {
            printf("没有值为%d的元素\n",j);
        }
    }
    printf("依次输出L的元素：");
    ListTraverse(L);
    
    j=5;
    ListDelete(&L, j, &e);/*删除第五个数据*/
    printf("删除第%d个的元素值为：%d\n",j,e);
    printf("删除后L的元素：");
    ListTraverse(L);
    
    //构造一个有10个数的Lb
    i=InitList(&Lb);
    for(j=6;j<=15;j++){
        i=ListInsert(&Lb,1,j);
    }
    unionL(&L,Lb);
    printf("依次输出合并了Lb的L的元素：");
    ListTraverse(L);
}

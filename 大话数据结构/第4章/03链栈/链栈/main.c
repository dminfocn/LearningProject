//
//  main.c
//  链栈
//
//  Created by 朱占龙 on 2017/10/31.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;
typedef int ElemType; /* SElemType类型根据实际情况而定，这里假设为int */
/* 链栈结构*/
typedef struct StackNode {
    ElemType data;
    struct StackNode *next;
}StackNode;
typedef struct StackNode *LinkStackPtr;

typedef struct {
    LinkStackPtr top;
    int count;
}LinkStack;

Status visit(ElemType c)
{
    printf("%d ",c);
    return OK;
}

/*初始化一个空栈*/
Status InitStack(LinkStack *S) {
    S->top = (LinkStackPtr) malloc(sizeof(StackNode));
    if (!S->top) {
        return ERROR;
    }
    S->top = NULL;
    S->count = 0;
    return OK;
}

Status Push(LinkStack *L, ElemType e) {
    LinkStackPtr s = (LinkStackPtr) malloc(sizeof(StackNode));
    s->data = e;
    s->next = L->top;/*把当前栈顶元素直接赋值给新节点的后继*/
    L->top = s;/*将新的节点赋值给栈顶元素*/
    L->count++;
    return OK;
}

Status StackTraverse(LinkStack L) {
    LinkStackPtr p;
    p = L.top;
    while (p) {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

Status Pop(LinkStack *L, ElemType *e) {
    LinkStackPtr p = L->top;
    *e = p->data;
    L->top = p->next;
    L->count--;
    free(p);
    return OK;
}

Status StackEmpty(LinkStack L) {
    if (L.count == 0) {
        return TRUE;
    }else {
        return FALSE;
    }
}

int StackLength(LinkStack L) {
    return L.count;
}

Status GetTop(LinkStack L, ElemType *e) {
    if (L.top == NULL) {
        return ERROR;
    }
    *e = L.top->data;
    return OK;
}

/*清空栈*/
Status ClearStack(LinkStack *L) {
    LinkStackPtr p,q;
    p = L->top;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    L->count = 0;
    return OK;
}

int main(int argc, const char * argv[]) {
    int j;
    LinkStack s;
    int e;
    if(InitStack(&s)==OK) {
        for (j=1; j<=10; j++) {
            Push(&s, j);
        }
    }
    printf("栈中元素依次为：");
    StackTraverse(s);
    
    Pop(&s,&e);
    printf("弹出的栈顶元素 e=%d\n",e);
    printf("栈空否：%d(1:空 0:否)\n",StackEmpty(s));
    
    GetTop(s,&e);
    printf("栈顶元素 e=%d 栈的长度为%d\n",e,StackLength(s));
    ClearStack(&s);
    printf("清空栈后，栈空否：%d(1:空 0:否)\n",StackEmpty(s));
    return 0;
}

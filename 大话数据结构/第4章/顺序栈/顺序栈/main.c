//
//  main.c
//  顺序栈
//
//  Created by 朱占龙 on 2017/10/31.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 /*初始化大小*/

typedef int Status;
typedef int EleType;

/* 顺序栈结构 */
typedef struct {
    EleType data[MAXSIZE];
    int top; /*栈顶指针*/
}sqStack;

/*  构造一个空栈S */
Status InitStack(sqStack *S) {
    S -> top = -1;
    return OK;
}

Status Push(sqStack *S, int e) {
    if (S -> top == MAXSIZE -1) {
        return ERROR;
    }
    S -> top++;
    S->data[S->top] = e;
    return OK;
}

void Visit(EleType e) {
    printf("%d",e);
}

void TStackTraverse(sqStack S) {
    int m = 0;
    while (m <= S.top) {
        Visit(S.data[m]);
        m++;
    }
    printf("\n");
}

Status Pop(sqStack *S, EleType *e) {
    if (S->top == -1) {
        return ERROR;
    }
    *e = S->data[S->top--];
    return OK;
}

Status StackEmpty(sqStack S) {
    if (S.top == -1) {
        return TRUE;
    }else {
        return FALSE;
    }
}

Status GetTop(sqStack S, EleType *e) {
    if (S.top == -1) {
        return ERROR;
    }else {
        *e = S.data[S.top];
        return OK;
    }
}

Status StackLength(sqStack S) {
    return S.top + 1;
}

/* 把S置为空栈 */
Status ClearStack(sqStack *S) {
    S -> top = -1;
    return OK;
}

int main(int argc, const char * argv[]) {
    int j;
    sqStack S;
    int e;
    if (InitStack(&S) == OK) {
        for(j=0; j<10; j++) {
            Push(&S, j);
        }
    }
    printf("栈中元素依次为：");
    TStackTraverse(S);
    
    Pop(&S, &e);
    printf("弹出的栈顶元素为：%d\n",e);
    Pop(&S, &e);
    printf("弹出的栈顶元素为：%d\n",e);
    
    printf("栈是否为空：%d(1:空 0:否)\n",StackEmpty(S));
    
    printf("栈中元素依次为：");
    TStackTraverse(S);
    
    GetTop(S,&e);
    printf("栈顶元素 e=%d 栈的长度为%d\n",e,StackLength(S));
    
    ClearStack(&S);
    printf("清空栈后，栈空否：%d(1:空 0:否)\n",StackEmpty(S));
    return 0;
}

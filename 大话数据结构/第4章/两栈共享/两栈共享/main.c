//
//  main.c
//  两栈共享
//
//  Created by 朱占龙 on 2017/10/31.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20

typedef int ElemType;
typedef int Status;

/* 两栈共享空间结构 */
typedef struct {
    ElemType data[MAXSIZE];
    int top1; /*栈1顶指针*/
    int top2; /*栈1顶指针*/
}DoubleStack;

Status visit(ElemType c)
{
    printf("%d ",c);
    return OK;
}

/*  构造一个空栈S */
Status InitStack(DoubleStack *s) {
    s->top1 = -1;
    s->top2 = MAXSIZE;
    return OK;
}

Status Push(DoubleStack *s, ElemType e, int index) {
    if (s->top1 + 1 == s->top2) {/* 栈已满，不能再push新元素了 */
        return ERROR;
    }
    if (index ==1 ) {
        s->top1++;
        s->data[s->top1] = e;
    }else if(index == 2){
        s->top2--;
        s->data[s->top2] = e;
    }
    return OK;
}

Status StackTraverse(DoubleStack s) {
    int i = 0;
    while (i <= s.top1) {
        visit(s.data[i++]);
    }
    i = s.top2;
    while (i < MAXSIZE) {
        visit(s.data[i++]);
    }
    printf("\n");
    return OK;
}

int StackLength(DoubleStack S) {
    return (S.top1 + 1) + (MAXSIZE - S.top2);
}

Status Pop(DoubleStack *S, ElemType *e, int index) {
    if (index == 1) {
        if (S->top1 == -1) {
            return ERROR;
        }
        *e = S->data[S->top1--];
    }else if(index == 2) {
        if (S->top2 == MAXSIZE) {
            return ERROR;
        }
        *e = S->data[S->top2++];
    }
    return OK;
}

Status StackEmpty(DoubleStack S) {
    if (S.top1 == -1 && S.top2 == MAXSIZE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

Status ClearStack(DoubleStack *S) {
    S->top1 = -1;
    S->top2 = MAXSIZE;
    return OK;
}

int main(int argc, const char * argv[]) {
    int j;
    DoubleStack s;
    int e;
    if (InitStack(&s) == OK) {
        for (j=1; j<=5; j++) {
            Push(&s, j, 1);
        }
        for (j=MAXSIZE; j>=MAXSIZE-2; j--) {
            Push(&s, j, 2);
        }
    }
    printf("栈中元素依次为：");
    StackTraverse(s);
    
    printf("当前栈中元素有：%d \n",StackLength(s));
    
    Pop(&s,&e,2);
    printf("弹出的栈顶元素 e=%d\n",e);
    printf("栈空否：%d(1:空 0:否)\n",StackEmpty(s));
    
    for (j=6; j<=MAXSIZE-2; j++) {
        Push(&s, j, 1);
    }
    printf("栈中元素依次为：");
    StackTraverse(s);
    
    printf("栈满否：%d(1:否 0:满)\n",Push(&s,100,1));
    
    
    ClearStack(&s);
    printf("清空栈后，栈空否：%d(1:空 0:否)\n",StackEmpty(s));
    
    return 0;
}

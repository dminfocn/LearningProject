//
//  main.c
//  05顺序队列
//
//  Created by apple on 2017/11/1.
//  Copyright © 2017年 apple. All rights reserved.
//

#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int ElemType;
typedef int Status;

/* 循环队列的顺序存储结构 */
typedef struct {
    ElemType data[MAXSIZE];
    int front;/*头指针*/
    int rear;/*尾指针，若队列为空，则指向下一个*/
}sqQueue;

Status InitQueue(sqQueue *Q) {
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

Status QueueEmpty(sqQueue Q) {
    if (Q.front == Q.rear) {/* 队列空的标志 */
        return TRUE;
    }else {
        return FALSE;
    }
}

Status EnQueue(sqQueue *Q, ElemType e) {
    if ((Q->rear+1) % MAXSIZE == Q->front) {/*队列满的条件*/
        return ERROR;
    }
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE;/* rear指针向后移一位置， */
    return OK;
}

int QueueLength(sqQueue Q) {
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

Status DeQueue(sqQueue *Q, ElemType *e) {
    if (Q->front == Q->rear) {/*队列为空*/
        return ERROR;
    }
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;/* front指针向后移一位置， */
    return OK;
}

Status Visit(ElemType e) {
    printf("%d ",e);
    return OK;
}

Status QueueTraverse(sqQueue Q) {
    int i;
    i=Q.front;
    while((i+Q.front)!=Q.rear)
    {
        Visit(Q.data[i]);
        i=(i+1)%MAXSIZE;
    }
    printf("\n");
    return OK;
}

Status GetHead(sqQueue Q, ElemType *e) {
    if (Q.rear == Q.front) {
        return ERROR;
    }
    *e = Q.data[Q.front];
    return OK;
}

/*清除队列*/
Status ClearQueue(sqQueue *Q) {
    Q->front = Q->rear = 0;
    return OK;
}

int main(int argc, const char * argv[]) {
    sqQueue Q;
    Status j;
    ElemType e;
    int i=0, l;
    
    InitQueue(&Q);
    printf("初始化队列后，队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
    
    printf("请输入整型队列元素(不超过%d个),-1为提前结束符:\n ", MAXSIZE-1);
    do {
        /* scanf("%d",&d); */
        e = i + 100;
        if (e == -1) {
            break;
        }
        i++;
        EnQueue(&Q,e);
    } while (i < MAXSIZE-1);
    printf("队列长度为: %d\n",QueueLength(Q));
    printf("现在队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
    
    printf("连续%d次由队头删除元素,队尾插入元素:\n",MAXSIZE);
    for(l=1;l<=MAXSIZE;l++)
    {
        DeQueue(&Q,&e);
        printf("删除的元素是%d,插入的元素:%d \n",e,l+1000);
        /* scanf("%d",&d); */
        e=l+1000;
        EnQueue(&Q,e);
    }
    l=QueueLength(Q);
    
    printf("现在队列中的元素为: \n");
    QueueTraverse(Q);
    
    printf("共向队尾插入了%d个元素\n",i+MAXSIZE);
    if(l-2>0) {
      printf("现在由队头删除%d个元素:\n",l-2);
    }
    while(QueueLength(Q)>2)
    {
        DeQueue(&Q,&e);
        printf("删除的元素值为%d\n",e);
    }
    
    printf("现在队列中的元素为: \n");
    QueueTraverse(Q);
    
    j=GetHead(Q,&e);
    if(j) {
      printf("现在队头元素为: %d\n",e);
    }
    
    ClearQueue(&Q);
    printf("清空队列后, 队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
    
    return 0;
}

//
//  main.c
//  06链队列
//
//  Created by apple on 2017/11/1.
//  Copyright © 2017年 apple. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;
typedef int ElemType;

/* 结点结构 */
typedef struct QNode{
    ElemType data;
    struct QNode *next;
}QNode;
typedef struct QNode *QueuePtr;

/* 队列的链表结构 */
typedef struct {
    QueuePtr front;
    QueuePtr rear;
}linkQueue;

Status visit(ElemType c)
{
    printf("%d ",c);
    return OK;
}

Status InitQueue(linkQueue *Q) {
    Q->front = Q->rear = (QueuePtr) malloc(sizeof(QNode));
    if (!Q->front) {
        exit(OVERFLOW);
    }
    Q->front->next = NULL;
    return OK;
}

Status QueueEmpty(linkQueue Q) {
    if (Q.front == Q.rear) {
        return TRUE;
    }else {
        return FALSE;
    }
}

int QueueLength(linkQueue Q) {
    int i=0;
    QueuePtr p;
    p = Q.front;
    while (Q.rear != p) {
        i++;
        p = p->next;
    }
    return i;
}

/* 插入元素e为Q的新的队尾元素 */
Status EnQueue(linkQueue *Q, ElemType e) {
    QueuePtr q = (QueuePtr) malloc(sizeof(QNode));
    if (!q) {/*存储分派失败*/
        exit(OVERFLOW);
    }
    q->data = e;
    q->next = NULL;
    Q->rear->next = q;/* 把拥有元素e的新结点q赋值给原队尾结点的后继，见图中① */
    Q->rear = q;/* 把当前的q设置为队尾结点，rear指向q，见图中② */
    return OK;
}

Status QueueTraverse(linkQueue Q) {
    QueuePtr p;
    p = Q.front->next;
    while (p) {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

Status GetHead(linkQueue Q, ElemType *e) {
    if (Q.rear ==  Q.front) {
        return ERROR;
    }
    *e = Q.front->next->data;
    return OK;
}

Status DeQueue(linkQueue *Q, ElemType *e) {
    if (QueueEmpty(*Q)) {
        return ERROR;
    }
    QueuePtr p;
    p = Q->front->next;
    Q->front->next = p->next;
    *e = p->data;
    if(Q->rear==p) {/* 若队头就是队尾，则删除后将rear指向头结点，见图中③ */
        Q->rear = Q->front;
    }
    free(p);
    return OK;
}

/* 将Q清为空队列 */
Status ClearQueue(linkQueue *Q) {
    QueuePtr p,q;
    Q->rear = Q->front;
    p = Q->front->next;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    return OK;
}

/* 销毁队列Q */
Status DestroyQueue(linkQueue *Q) {
    while (Q->front) {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
    return OK;
}


int main(int argc, const char * argv[]) {
    int i;
    ElemType e;
    linkQueue Q;
    i = InitQueue(&Q);
    if (i) {
        printf("成功地构造了一个空队列\n");
    }
    printf("是否空队列？%d(1:空，0：不为空)\n",QueueEmpty(Q));
    printf("队列的长度为%d\n",QueueLength(Q));
    
    printf("是否空队列？%d(1:空 0:否)\n",QueueEmpty(Q));
    
    EnQueue(&Q,-5);
    EnQueue(&Q,5);
    EnQueue(&Q,10);
    printf("插入3个元素(-5,5,10)后,队列的长度为%d\n",QueueLength(Q));
    
    printf("队列的元素依次为：\n");
    QueueTraverse(Q);
    
    i=GetHead(Q,&e);
    if(i==OK) {
        printf("队头元素是：%d\n",e);
    }
    
    DeQueue(&Q,&e);
    printf("删除了队头元素%d\n",e);
    
    i=GetHead(Q,&e);
    if(i==OK) {
        printf("新的队头元素是：%d\n",e);
    }
    
    ClearQueue(&Q);
    printf("清空队列后,q.front=%u q.rear=%u q.front->next=%u\n",Q.front,Q.rear,Q.front->next);
    DestroyQueue(&Q);
    printf("销毁队列后,q.front=%u q.rear=%u\n",Q.front, Q.rear);
    return 0;
}

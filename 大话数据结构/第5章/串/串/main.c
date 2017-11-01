//
//  main.c
//  串
//
//  Created by 朱占龙 on 2017/11/1.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 40

typedef int ElemType;
typedef int Status;

typedef char String[MAXSIZE+1];/*  0号单元存放串的长度 */

/* 生成一个其值等于chars的串T */
Status StrAssign(String T, char *chars) {
    int i;
    if (strlen(chars) > MAXSIZE) {
        return ERROR;
    }else {
        T[0] = strlen(chars);
        for (i=1; i<=T[0]; i++) {
            T[i] = *(chars+i-1);
        }
    }
    return OK;
}

/* 返回串的元素个数 */
int StrLength(String S) {
    return S[0];
}

Status StrEmpty(String S) {
    if (S[0] > 0) {
        return FALSE;
    }else {
        return TRUE;
    }
}

Status StrCopy(String T, String S) {
    int i;
    for (i=0; i<=S[0]; i++) {
        T[i] = S[i];
    }
    return OK;
}

Status StrPrint(String S) {
    int i;
    for (i=1; i<=S[0]; i++) {
        printf("%c",S[i]);
    }
    printf("\n");
    return OK;
}

int StrCompare(String T, String S) {
    int i;
    for (i=1; i<=T[0] && i< S[0]; i++) {
        if (T[i] != S[i]) {
            return T[i] - S[i];
        }
    }
    return T[0] - S[0];
}

/* 用T返回S1和S2联接而成的新串。若未截断，则返回TRUE，否则FALSE */
Status Concat(String T, String S1, String S2) {
    int i;
    if (S1[0] + S2[0] < MAXSIZE) {//未截断
        for (i=1; i<=S1[0]; i++) {
            T[i] = S1[i];
        }
        for (i=1; i<=S2[0]; i++) {
            T[S1[0] + i] = S2[i];
        }
        T[0] = S1[0] + S2[0];
        return TRUE;
    }else {//已截断S2
        for (i=1; i<=S1[0]; i++) {
            T[i] = S1[i];
        }
        for (i=1; i<=MAXSIZE-S1[0]; i++) {
            T[S1[0] + i] = S2[i];
        }
        T[0] = MAXSIZE;
        return FALSE;
    }
}

Status ClearString(String S) {
    S[0] = 0;
    return OK;
}

Status SubString(String S, String T, int pos, int len) {
    int i;
    if (pos > T[0] || pos<1 || len<0 || len > T[0]-pos+1) {
        return ERROR;
    }
    for (i=1; i<=len; i++) {
        S[i] = T[pos+i-1];
    }
    S[0] = len;
    return OK;
}

/*  初始条件: 串S存在,1≤pos≤StrLength(S)-len+1 */
/*  操作结果: 从串S中删除第pos个字符起长度为len的子串 */
Status StrDelete(String S, int pos, int len) {
    int i;
    if (pos<1||pos>S[0]-len+1||len<0) {
        return ERROR;
    }
    for (i=pos+len; i<S[0]; i++) {
        S[i-len]=S[i];
    }
    S[0] -= len;
    return OK;
}

Status StrInsert(String S, int pos, String T) {
    int i;
    if(pos<1||pos>S[0]+1)
        return ERROR;
    if(S[0]+T[0]<=MAXSIZE)
    { /*  完全插入 */
        for(i=S[0];i>=pos;i--)
            S[i+T[0]]=S[i];
        for(i=pos;i<pos+T[0];i++)
            S[i]=T[i-pos+1];
        S[0]=S[0]+T[0];
        return TRUE;
    }else { /*  部分插入 */
        for(i=MAXSIZE;i<=pos;i--)
            S[i]=S[i-T[0]];
        for(i=pos;i<pos+T[0];i++)
            S[i]=T[i-pos+1];
        S[0]=MAXSIZE;
        return FALSE;
    }
}
/* 返回子串T在主串S中第pos个字符之后的位置。若不存在,则函数返回值为0。 */
/* 其中,T非空,1≤pos≤StrLength(S)。 */
int Index(String S, String T, int pos)
{
    int i = pos;    /* i用于主串S中当前位置下标值，若pos不为1，则从pos位置开始匹配 */
    int j = 1;                /* j用于子串T中当前位置下标值 */
    while (i <= S[0] && j <= T[0]) /* 若i小于S的长度并且j小于T的长度时，循环继续 */
    {
        if (S[i] == T[j])     /* 两字母相等则继续 */
        {
            ++i;
            ++j;
        }else                 /* 指针后退重新开始匹配 */{
            i = i-j+2;        /* i退回到上次匹配首位的下一位 */
            j = 1;             /* j退回到子串T的首位 */
        }
    }
    if (j > T[0]) {
        return i-T[0];
    }else {
        return 0;
    }
}

/*  初始条件: 串S,T和V存在,T是非空串（此函数与串的存储结构无关） */
/*  操作结果: 用V替换主串S中出现的所有与T相等的不重叠的子串 */
Status Replace(String S,String T,String V)
{
    int i=1; /*  从串S的第一个字符起查找串T */
    if(StrEmpty(T)) /*  T是空串 */
        return ERROR;
    do{
        i=Index(S,T,i); /*  结果i为从上一个i之后找到的子串T的位置 */
        if(i) /*  串S中存在串T */
        {
            StrDelete(S,i,StrLength(T)); /*  删除该串T */
            StrInsert(S,i,V); /*  在原串T的位置插入串V */
            i+=StrLength(V); /*  在插入的串V后面继续查找串T */
        }
    }while(i);
    return OK;
}

int main(int argc, const char * argv[]) {
    int i,j;
    Status k;
    char s;
    String t, s1, s2;
    k = StrAssign(s1, "abcd");
    if (!k) {
        printf("串长超过MAXSIZE(=%d)\n",MAXSIZE);
        exit(0);
    }
    
    printf("串长为%d 串空否？%d(1:是 0:否)\n",StrLength(s1),StrEmpty(s1));
    
    StrCopy(s2,s1);
    printf("拷贝s1生成的串为: ");
    StrPrint(s2);
    
    k = StrAssign(s2, "efghijk");
    if (!k) {
        printf("串长超过字符串MAXSIZE(%d)",MAXSIZE);
        exit(0);
    }
    
    i=StrCompare(s1,s2);
    if(i<0) {
        s='<';
    }else if(i==0) {
        s='=';
    }else {
        s='>';
    }
    printf("串s1%c串s2\n",s);
    
    k=Concat(t,s1,s2);
    printf("串s1联接串s2得到的串t为: ");
    StrPrint(t);
    if(k==FALSE) {
        printf("串t有截断\n");
    }
    
    ClearString(s1);
    printf("清为空串后,串s1为: ");
    StrPrint(s1);
    printf("串长为%d 串空否？%d(1:是 0:否)\n",StrLength(s1),StrEmpty(s1));
    
    ClearString(s2);
    k=SubString(s2,t,2,3);
    if(k){
        printf("子串s2为: ");
        StrPrint(s2);
    }
    
    StrDelete(t,4,2);
    printf("删除后的串t为: ");
    StrPrint(t);
    i=StrLength(s2)/2;
    
    StrInsert(s2,i,t);
    printf("在串s2的第%d个字符之前插入串t后,串s2为:\n",i);
    StrPrint(s2);
    
    i=Index(s2,t,1);
    printf("s2的第%d个字母起和t第一次匹配\n",i);
    SubString(t,s2,1,1);
    printf("串t为：");
    StrPrint(t);
    Concat(s1,t,t);
    printf("串s1为：");
    StrPrint(s1);
    Replace(s2,t,s1);
    printf("用串s1取代串s2中和串t相同的不重叠的串后,串s2为: ");
    StrPrint(s2);
    
    return 0;
}

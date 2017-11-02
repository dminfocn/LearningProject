//
//  main.c
//  KMP模式匹配算法
//
//  Created by 朱占龙 on 2017/11/2.
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

typedef int Status;
typedef int ElemType;
typedef char String[MAXSIZE+1];

/* 生成一个其值等于chars的串T */
Status StrAssign(String S, char *chars) {
    int i;
    if (strlen(chars) > MAXSIZE) {
        return ERROR;
    }else {
        S[0] = strlen(chars);
        for (i=1; i<=strlen(chars); i++) {
            S[i] = *(chars+i-1);
        }
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

void get_next(String T, int *next) {
    int i,j;
    i = 1;
    j=0;
    next[1] = 0;
    while (i < T[0]) {
        if (j==0 || T[i] == T[j]) {
            ++i;
            ++j;
            next[i] = j;
        }else {
            j = next[j];
        }
    }
}

int StrLength(String S) {
    return S[0];
}

Status NextPrint(int next[], int len) {
    int i;
    for (i=1; i<=len; i++) {
        printf("%d",next[i]);
    }
    return OK;
}

/* 朴素的模式匹配法 */
int Index(String S, String T, int pos) {
    int i = pos;    /* i用于主串S中当前位置下标值，若pos不为1，则从pos位置开始匹配 */
    int j = 1;
    while (i<=S[0] && j <= T[0]) {
        if (S[i] == T[j]) {
            ++i;
            ++j;
        }else {
            i = i-j+2;/* i退回到上次匹配首位的下一位 */
            j = 1;/* j退回到子串T的首位 */
        }
    }
    if (j > T[0]) {
        return i - T[0];
    }else {
        return 0;
    }
}

/* 返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数返回值为0。 */
/*  T非空，1≤pos≤StrLength(S)。 */
int Index_KMP(String S, String T, int pos) {
    int i = pos;
    int j = 1;
    int next[255];
    get_next(T, next);
    while (i <= S[0] && j <= T[0]) {
        if (j==0 || S[i] == T[j]) {
            ++i;
            ++j;
        }else {
            j = next[j];
        }
    }
    if (j > T[0]) {
        return i - T[0];
    }else {
        return 0;
    }
}

void get_nextval(String T, int *nextval) {
    int i, j;
    i = 1;
    j = 0;
    nextval[1] = 0;
    while (i < T[0]) {
        if (j == 0 || T[i] == T[j]) {
            ++i;
            ++j;
            if (T[i] != T[j]) {
                nextval[i] = j;
            }else {
                nextval[i] = nextval[j];
            }
        }else {
            j = nextval[j];
        }
    }
}

int Index_KMP1(String S, String T, int pos) {
    int i = pos;
    int j = 1;
    int next[255];
    get_nextval(T, next);
    while (i <= S[0] && j <= T[0]) {
        if (j == 0 || S[i] == T[j]) {
            ++i;
            ++j;
        }else {
            j = next[j];
        }
    }
    if (j > T[0]) {
        return i - T[0];
    }else {
        return 0;
    }
}

int main(int argc, const char * argv[]) {
    
    int i, *p;
    String s1, s2;
    StrAssign(s1, "abcdex");
    printf("子串为: ");
    StrPrint(s1);
    i=StrLength(s1);
    p = (int *) malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("Next为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");
    
    StrAssign(s1, "abcabx");
    printf("子串为：");
    StrPrint(s1);
    i = StrLength(s1);
    p = (int *) malloc(sizeof(int) * (i+1));
    get_next(s1, p);
    printf("Next为：");
    NextPrint(p, StrLength(s1));
    printf("\n");
    
    StrAssign(s1, "ababaaaba");
    printf("子串为:");
    StrPrint(s1);
    i = StrLength(s1);
    p = (int *) malloc((i+1) * sizeof(int));
    get_next(s1, p);
    printf("Next为：");
    NextPrint(p, StrLength(s1));
    printf("\n");
    
    StrAssign(s1, "ababaaaba");
    printf("   子串为: ");
    StrPrint(s1);
    i = StrLength(s1);
    p = (int *) malloc(sizeof(int) *(i+1));
    get_next(s1, p);
    printf("Next为：");
    NextPrint(p, StrLength(s1));
    printf("\n");
    
    StrAssign(s1, "aaaaaaaab");
    printf("子串为：");
    StrPrint(s1);
    i = StrLength(s1);
    p = (int *) malloc(sizeof(int) *(i+1));
    get_next(s1, p);
    printf("Next为：");
    NextPrint(p, StrLength(s1));
    printf("\n");
    
    StrAssign(s1, "00001");
    printf("主串为:");
    StrPrint(s1);
    
    StrAssign(s2, "01");
    printf("子串为：");
    StrPrint(s2);
    printf("\n");
    
    printf("主串和子串在第%d个字符处首次匹配（朴素模式匹配算法）\n",Index(s1,s2,1));
    printf("主串和子串在第%d个字符处首次匹配（KMP算法） \n",Index_KMP(s1,s2,1));
    printf("主串和子串在第%d个字符处首次匹配（KMP改良算法） \n",Index_KMP1(s1,s2,1));
    return 0;
}

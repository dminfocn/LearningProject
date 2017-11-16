//
//  main.c
//  01排序算法
//
//  Created by 朱占龙 on 2017/11/15.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAX_LENGTH_INSERT_SORT 7 /*用于快速排序时判断是否选用插入排序的阈值*/
#define MAXSIZE 10000

typedef int Status;
typedef struct {
    int r[MAXSIZE + 1];/*位置0用做哨兵或者存放临时变量*/
    int length;/*记录顺序表的长度*/
}SqList;

void swap(SqList *L, int i, int j) {
    int temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
    
}

void print(SqList L) {
    int i;
    for (i = 1; i<L.length; i++) {
        printf("%d,", L.r[i]);
    }
    printf("%d", L.r[i]);
    printf("\n");
}

/*初级冒泡排序法*/
void BubbleSort0(SqList *L) {
    int i, j;
    for (i=1; i<L->length; i++) {
        for (j=i+1;j<=L->length; j++) {
            if (L->r[i] > L->r[j]) {
                swap(L, i, j);
            }
        }
    }
}

void BubbleSort(SqList *L) {
    int i, j;
    for (i=1; i<L->length; i++) {
        for (j=L->length-1; j>=i; j--) {
            if(L->r[j] > L->r[j+1]) {
                swap(L, j, j+1);
            }
        }
    }
}

/*冒泡排序改进*/
void BubbleSort2(SqList *L) {
    int i, j;
    Status flag = TRUE;
    for (i=1; i<L->length && flag; i++) {
        flag = FALSE;
        for (j=L->length-1; j>=i; j--) {
            if(L->r[j] > L->r[j+1]) {
                swap(L, j, j+1);
                flag = TRUE;
            }
        }
    }
}

/*简单选择排序*/
void SelectSort(SqList *L) {
    int i, j, m;
    for(i=1; i<L->length; i++) {
        m = i;
        for(j=i+1; j<=L->length; j++) {
            if(L->r[m] > L->r[j]) {
                m = j;
            }
        }
        if(i != m) {
            swap(L, m, i);
        }
    }
}

/*直接插入排序*/
void InsertSort(SqList *L) {
    int i, j;
    for (i=2; i<=L->length; i++) {
        if(L->r[i] < L->r[i-1]) {
            L->r[0] = L->r[i];/*设置哨兵*/
            for (j=i-1; L->r[j] > L->r[0]; j--) {
                L->r[j+1] = L->r[j];
            }
            L->r[j+1] = L->r[0];
        }
    }
}

/*希尔排序*/
void ShellSort(SqList *L) {
    int i, j;
    int increment = L->length;
    do {
        increment = increment / 3 + 1;/*增量序列*/
        for (i=increment+1; i<=L->length; i++) {
            if(L->r[i] < L->r[i-increment]) {
                L->r[0] = L->r[i];
                for(j=i-increment; L->r[j] > L->r[0]; j--) {
                    L->r[j+increment] = L->r[j];/*记录后移，查找插入位置*/
                }
                L->r[j+increment] = L->r[0];/*插入*/
            }
        }
    }while (increment > 1);
}

void HeapAdjust(SqList *L, int s, int m) {
    int temp, j;
    temp = L->r[s];
    for(j=2*s; j<=m; j*=2) {
        if(j<m && L->r[j]<L->r[j+1]) {
            ++j;
        }
        if(temp >= L->r[j]) {
            break;
        }
        L->r[s] = L->r[j];
        s = j;
    }
    L->r[s] = temp;
}

/*堆排序*/
void HeapSort(SqList *L) {
    int i;
    for(i=L->length/2; i>0; i--) {
        HeapAdjust(L, i, L->length);
    }
    for(i = L->length; i>1; i--) {
        swap(L, 1, i);
        HeapAdjust(L, 1, i-1);
    }
}

/*将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]*/
void Merge(int SR[], int TR[], int i, int m, int n) {
    int j, k, l;
    for(j=m+1,k=i; i<=m && j<=n; k++) {
        if(SR[i] < SR[j]) {
            TR[k] = SR[i++];
        }else {
            TR[k] = SR[j++];
        }
    }
    if(i <= m) {
        for(l=0; l<=m-1; l++) {
            TR[k+l] = SR[i+l];
        }
    }
    if(j <= n) {
        for(l=0; l<=n-j; l++) {
            TR[k+l] = SR[j+l];
        }
    }
}

/*将SR[s..t]归并排序为TR1[s..t]*/
void MSort(int SR[], int TR1[], int s, int t) {
    int m;
    int TR2[MAXSIZE+1];
    if(s == t) {
        TR1[s] = SR[s];
    }else {
        m = (s+t) / 2;
        MSort(SR, TR2, s, m);
        MSort(SR, TR2, m+1, t);
        Merge(TR2, TR1, s, m, t);
    }
}

/*归并排序递归法*/
void MergeSort(SqList *L) {
    MSort(L->r, L->r, 1, L->length);
}

void MergePass(int SR[], int TR[], int s, int n) {
    int i = 1;
    int j;
    while (i <= n-2*s+1) {
        Merge(SR, TR, i, i+s-1,i+2*s-1);/*两两归并*/
        i = i + 2 * s;
    }
    if(i < n - s + 1) {
        Merge(SR, TR, i, i+s-1, n);
    }else {
        for(j=i; j<=n; j++) {
            TR[j] = SR[j];
        }
    }
}

/*归并排序非递归*/
void MergeSort2(SqList *L) {
    /*申请额外空间*/
    int *TR = (int *) malloc(sizeof(L->length * sizeof(int)));
    int k = 1;
    while (k < L->length) {
        MergePass(L->r, TR, k, L->length);
        k = 2 * k; /* 子序列长度加倍*/
        MergePass(TR, L->r,k, L->length);
        k = 2 * k;/* 子序列长度加倍*/
        
    }
}

int Partition(SqList *L, int low, int high) {
    int pivotkey;
    pivotkey = L->r[low];
    while (low < high) {
        while (low < high && L->r[high] > pivotkey) {
            high--;
        }
        swap(L, low, high);
        while (low < high && L->r[low] <= pivotkey) {
            low++;
        }
        swap(L, low, high);
    }
    return low;
}

void QSort(SqList *L, int low, int high){
    int privot;
    if(low < high) {
        privot = Partition(L, low, high);
        
        QSort(L, low, privot-1);
        QSort(L, privot+1, high);
    }
}

/*基础快速排序*/
void QuickSort(SqList *L) {
    QSort(L, 1, L->length);
}

int Partition1(SqList *L, int low, int high) {
    int pivotkey;
    int m  = low + (high - low) / 2;
    if(L->r[low] > L->r[high]) {
        swap(L, low, high);
    }
    if(L->r[m] > L->r[high]) {
        swap(L, m, high);
    }
    if(L->r[m] > L->r[low]) {
        swap(L, m, low);
    }
    pivotkey = L->r[low];
    L->r[0] = pivotkey;
    while (low < high) {
        while (low < high && L->r[high] >= pivotkey) {
            high--;
        }
        L->r[low] = L->r[high];
        while (low < high && L->r[low] <= pivotkey) {
            low++;
        }
        L->r[high] = L->r[low];
    }
    L->r[low] = L->r[0];
    return low;
}

#define MAX_LENGTH_INSERT_SORT 7
void QSort1(SqList *L, int low, int high) {
    int pivot;
    if((high-low) > MAX_LENGTH_INSERT_SORT) {
        while (low < high) {
            pivot = Partition1(L, low, high);
            
            QSort1(L, low, pivot-1);
            low = pivot + 1;
        }
    }else {
        InsertSort(L);
    }
}

void QuickSort1(SqList *L) {
    QSort1(L,1,L->length);
}

#define N 9
int main(int argc, const char * argv[]) {
    
    int i;
    int d[N]={50,10,90,30,70,40,80,60,20};
    SqList l0,l1,l2,l3,l4,l5,l6,l7,l8,l9,l10;
    for(i=0; i<N; i++) {
        l0.r[i+1] = d[i];
    }
    l0.length = N;
    l1 = l2 = l3 = l4 = l5 = l6 = l7 = l8 = l9 = l10 = l0;
    
    printf("排序前：");
    print(l0);
    
    printf("初级冒泡排序：\n");
    BubbleSort0(&l0);
    print(l0);
    
    printf("冒泡排序：\n");
    BubbleSort(&l1);
    print(l1);
    
    printf("冒泡排序改进：\n");
    BubbleSort2(&l2);
    print(l2);
    
    printf("选择排序:\n");
    SelectSort(&l3);
    print(l3);
    
    printf("直接插入排序:\n");
    InsertSort(&l4);
    print(l4);
    
    printf("希尔排序:\n");
    ShellSort(&l5);
    print(l5);
    
    printf("堆排序:\n");
    HeapSort(&l6);
    print(l6);
    
    printf("归并排序（递归）:\n");
    MergeSort(&l7);
    print(l7);
    
    printf("归并排序（非递归）:\n");
    MergeSort2(&l8);
    print(l8);
    
    printf("快速排序:\n");
    QuickSort(&l9);
    print(l9);
    
    printf("改进快速排序:\n");
    QuickSort1(&l10);
    print(l10);
    
    return 0;
}

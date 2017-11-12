//
//  main.c
//  01静态查找
//
//  Created by 朱占龙 on 2017/11/12.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define  MAXSIZE 100

typedef int  Status;/*状态码*/

int F[100];/*斐波那契数列*/

/* 无哨兵顺序查找，a为数组，n为要查找的数组个数，key为要查找的关键字 */
int Sequential_Search(int *a, int n, int key) {
    for(int i=1; i<=n; i++) {
        if(a[i] == key) {
            return i;
        }
    }
    return 0;
}

/* 有哨兵顺序查找 */
int Sequential_Search2(int *a, int n, int key) {
    int i;
    a[0] = key;/*将第一位标记为要查找的值*/
    i = n;
    while (a[i] != key) {/*从后往前找*/
        i--;
    }
    return i;
}

int Binary_Search(int *a, int n, int key) {
    int low, mid, high;
    low = 1;/* 定义最低下标为记录首位 */
    high = n;/* 定义最低上标为记录末位 */
    while(low <= high) {
        mid = (low + high) * 0.5;/*折半*/
        if(key > a[mid]) {/*若查找值比中值大*/
            low = mid + 1;/*最低下标调整到中值加1*/
        }else if(key < a[mid]) {/*查找值比中值小*/
            high = mid - 1;/* 最高小标调整到中值减1 */
        }else {
            return mid;/*相等则说明找到*/
        }
    }
    return 0;
}

/*插值查找法*/
int Interpolation_Search(int *a, int n, int key) {
    int low, mid, high;
    low = 1;
    high = n;
    while (low <= high) {
        mid = low + (key-a[low])/(a[high] - a[low]) * (high -low);/*插值*/
        if(key < a[mid]) {
            high = mid - 1;
        }else if(key > a[mid]) {
            low = mid + 1;
        }else {
            return mid;
        }
    }
    return 0;
}

int Fibonacci_Search(int *a, int n, int key) {
    int low, mid, high, i, k=0;
    low = 1;
    high = n;
    while (n > F[k]-1) {/*查找值所在的位置*/
        k++;
    }
    for(i=n; i<F[k]-1; i++) {
        a[i] = a[n];
    }
    while (low <= high) {
        mid = low + F[k-1]-1;
        if(key < a[mid]) {
            k = k-1;
            high = mid -1;
        }else if(key > a[mid]) {
            k = k - 2;
            low = mid + 1;
        }else {
            if(mid <= n) {
                return mid;
            }else {
                return n;
            }
        }
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    int a[MAXSIZE + 1], i, result;
    int arr[MAXSIZE] = {0,1,16,24,35,47,59,62,73,88,99};
    
    for(i=0; i<= MAXSIZE; i++) {
        a[i] = i;
    }
    
    result = Sequential_Search(a,MAXSIZE,50);
    printf("Sequential_Search is %d\n", result);
    result=Sequential_Search2(a,MAXSIZE,1);
    printf("Sequential_Search2:%d \n",result);
    
    result=Binary_Search(arr,10,62);
    printf("Binary_Search:%d \n",result);
    
    result=Interpolation_Search(arr,10,62);
    printf("Interpolation_Search:%d \n",result);
    
    F[0] = 0;
    F[1] = 1;
    for(i = 2; i<100; i++) {
        F[i] = F[i-1] + F[i-2];
    }
    
    result = Fibonacci_Search(arr, 10, 62);
    printf("Fibonacci_Search:%d \n",result);
    return 0;
}

//
//  main.c
//  斐波那契函数
//
//  Created by 朱占龙 on 2017/10/31.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#include <stdio.h>

int FBI(int x) {
    if (x<2) {
        return x==0 ? 0 : 1;
    }else {
        return FBI(x-1) + FBI(x-2);
    }
}

int main(int argc, const char * argv[]) {
    //迭代显示斐波那契数列
    int i;
    int a[40];
    a[0] = 0;
    a[1] = 1;
    printf("%d ",a[0]);
    printf("%d ",a[1]);
    for (i=2; i<40; i++) {
        a[i] = a[i-1] + a[i-2];
        printf("%d ",a[i]);
    }
    printf("\n");
    
    //递归显示斐波那契数列
    for (i=0; i<40; i++) {
        printf("%d ",FBI(i));
    }
    return 0;
}



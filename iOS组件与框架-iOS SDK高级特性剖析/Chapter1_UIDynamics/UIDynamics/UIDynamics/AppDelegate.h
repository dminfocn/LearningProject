//
//  AppDelegate.h
//  UIDynamics
//
//  Created by 朱占龙 on 2017/10/21.
//  Copyright © 2017年 cuit. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZLIndexViewController.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
    UINavigationController *naviController;
}

@property (strong, nonatomic) UIWindow *window;

/** 引用控制器 */
@property(nonatomic, strong)  ZLIndexViewController* viewController;

@end


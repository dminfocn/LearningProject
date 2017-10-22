//
//  ZLPushViewController.h
//  UIDynamics
//
//  Created by 朱占龙 on 2017/10/22.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ZLPushViewController : UIViewController
{
    IBOutlet UIImageView * dragonImageView;
    UIDynamicAnimator *animator;
}
/** <#name#> */
@property(nonatomic, strong) UIPushBehavior *pushBehavior;
@end

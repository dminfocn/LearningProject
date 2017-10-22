//
//  ZLGravityViewController.m
//  UIDynamics
//
//  Created by 朱占龙 on 2017/10/22.
//  Copyright © 2017年 cuit. All rights reserved.
//

#import "ZLGravityViewController.h"

@interface ZLGravityViewController ()

@end

@implementation ZLGravityViewController

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        
    }
    return self;
}
- (void)viewDidLoad {
    [super viewDidLoad];
    animator = [[UIDynamicAnimator alloc] initWithReferenceView:self.view];
    UIGravityBehavior *gravityBehavior = [[UIGravityBehavior alloc] initWithItems:@[frogImageView]];
    gravityBehavior.gravityDirection = CGVectorMake(0.0, 0.1);
    //角度
//    gravityBehavior.angle = 0;
    //速度
    gravityBehavior.magnitude = 0.1;
    [animator addBehavior:gravityBehavior];
}
@end

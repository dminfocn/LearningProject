//
//  ZLPushViewController.m
//  UIDynamics
//
//  Created by 朱占龙 on 2017/10/22.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#import "ZLPushViewController.h"

@interface ZLPushViewController ()

@end

@implementation ZLPushViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    animator = [[UIDynamicAnimator alloc] initWithReferenceView:self.view];
    UICollisionBehavior *collisionBehavior = [[UICollisionBehavior alloc] initWithItems:@[dragonImageView]];
    collisionBehavior.translatesReferenceBoundsIntoBoundary = YES;
    [animator addBehavior:collisionBehavior];
    
    UIPushBehavior *pushBehavior = [[UIPushBehavior alloc] initWithItems:@[dragonImageView] mode:UIPushBehaviorModeContinuous];
    pushBehavior.angle = 0.0;
    pushBehavior.magnitude = 0.0;
    self.pushBehavior = pushBehavior;
    [animator addBehavior:pushBehavior];
}

- (IBAction)handleTapGesture:(UITapGestureRecognizer *)gesture {
    CGPoint point = [gesture locationInView:self.view];
    
    CGPoint origin = CGPointMake(CGRectGetMidX(self.view.bounds), CGRectGetMidY(self.view.bounds));
    CGFloat distance = sqrtf(pow(point.x-origin.x, 2) + pow(point.y-origin.y, 2));
    
    CGFloat angle = atan2(point.y-origin.y, point.x-origin.x);
    
    [self.pushBehavior setAngle:angle];
    [self.pushBehavior setMagnitude:distance/100.0];
    [self.pushBehavior setActive:YES];
}

@end

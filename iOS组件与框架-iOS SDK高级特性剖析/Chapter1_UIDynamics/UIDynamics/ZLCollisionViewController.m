//
//  ZLCollisionViewController.m
//  UIDynamics
//
//  Created by 朱占龙 on 2017/10/22.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#import "ZLCollisionViewController.h"

@interface ZLCollisionViewController ()<UICollisionBehaviorDelegate>

@end

@implementation ZLCollisionViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    dynamic = [[UIDynamicAnimator alloc] initWithReferenceView:self.view];
    UIGravityBehavior *gravityBehavior = [[UIGravityBehavior alloc] initWithItems:@[frogImageView, dragImageView]];
    [gravityBehavior setGravityDirection:CGVectorMake(0.0, 1.0)];
    
    UICollisionBehavior *collisionBehavior = [[UICollisionBehavior alloc] initWithItems:@[frogImageView,dragImageView]];
    collisionBehavior.collisionDelegate = self;
    [collisionBehavior setCollisionMode:UICollisionBehaviorModeBoundaries];
    //设置碰撞边界
    collisionBehavior.translatesReferenceBoundsIntoBoundary = YES;
    
    [dynamic addBehavior:gravityBehavior];
    [dynamic addBehavior:collisionBehavior];
}

- (void)collisionBehavior:(UICollisionBehavior *)behavior beganContactForItem:(id<UIDynamicItem>)item withBoundaryIdentifier:(id<NSCopying>)identifier atPoint:(CGPoint)p {
    if ([item isEqual:frogImageView]) {
        NSLog(@"接触边界了");
        collisionLabelOne.text = @"Frog Collisied";
    }
    if ([item isEqual:dragImageView]) {
        collisionLabelTwo.text = @"Drag Collisied";
    }
}

- (void)collisionBehavior:(UICollisionBehavior *)behavior endedContactForItem:(id<UIDynamicItem>)item withBoundaryIdentifier:(id<NSCopying>)identifier {
    NSLog(@"collision did end");
}
@end

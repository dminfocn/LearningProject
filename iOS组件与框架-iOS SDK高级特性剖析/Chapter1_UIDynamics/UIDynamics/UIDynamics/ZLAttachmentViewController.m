//
//  ZLAttachmentViewController.m
//  UIDynamics
//
//  Created by 朱占龙 on 2017/10/22.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#import "ZLAttachmentViewController.h"

@interface ZLAttachmentViewController ()

@end

@implementation ZLAttachmentViewController

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        //
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    dynamic = [[UIDynamicAnimator alloc] initWithReferenceView:self.view];
    
    UICollisionBehavior *collisionBehavior = [[UICollisionBehavior alloc] initWithItems:@[frogImageView, dragImageView]];
    [collisionBehavior setCollisionMode:UICollisionBehaviorModeBoundaries];
    collisionBehavior.translatesReferenceBoundsIntoBoundary = YES;
    
    UIGravityBehavior *gravityBehavior = [[UIGravityBehavior alloc] initWithItems:@[dragImageView]];
    
    CGPoint frogCenter = CGPointMake(frogImageView.center.x, frogImageView.center.y);
    self.attachentBehavior = [[UIAttachmentBehavior alloc] initWithItem:dragImageView attachedToAnchor:frogCenter];
    [self.attachentBehavior setFrequency:1.0f];
    [self.attachentBehavior setDamping:0.1f];
    [self.attachentBehavior setLength:100.0f];
    
    [dynamic addBehavior:collisionBehavior];
    [dynamic addBehavior:gravityBehavior];
    [dynamic addBehavior:self.attachentBehavior];
}

- (IBAction)handleAttachmentGesture:(UIPanGestureRecognizer *)gesture {
    CGPoint gesturePoint = [gesture locationInView:self.view];
    [frogImageView setCenter: gesturePoint];
    [self.attachentBehavior setAnchorPoint:gesturePoint];
}

@end

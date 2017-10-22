//
//  ZLPropertiesViewController.m
//  UIDynamics
//
//  Created by 朱占龙 on 2017/10/22.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#import "ZLPropertiesViewController.h"

@interface ZLPropertiesViewController ()

@end

@implementation ZLPropertiesViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    animator = [[UIDynamicAnimator alloc] initWithReferenceView:self.view];
    
    UIGravityBehavior *gravitBehavior = [[UIGravityBehavior alloc] initWithItems:@[frogImageView, dragonImageView]];
    
    UICollisionBehavior *collisionBehavior = [[UICollisionBehavior alloc] initWithItems:@[frogImageView, dragonImageView]];
    collisionBehavior.translatesReferenceBoundsIntoBoundary = YES;
    
    UIDynamicItemBehavior *propertiesBehavior = [[UIDynamicItemBehavior alloc] initWithItems:@[frogImageView]];
    propertiesBehavior.elasticity = 1.0f;
    propertiesBehavior.allowsRotation = NO;
    propertiesBehavior.angularResistance = 0.0f;
    propertiesBehavior.density = 1.0f;
    propertiesBehavior.friction = 0.0f;
    propertiesBehavior.resistance = 0.0f;
    
    [animator addBehavior:gravitBehavior];
    [animator addBehavior:collisionBehavior];
    [animator addBehavior:propertiesBehavior];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end

//
//  ZLSnapViewController.m
//  UIDynamics
//
//  Created by 朱占龙 on 2017/10/22.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#import "ZLSnapViewController.h"

@interface ZLSnapViewController ()

@end

@implementation ZLSnapViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    animator = [[UIDynamicAnimator alloc] initWithReferenceView:self.view];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (IBAction)handleGesture:(UITapGestureRecognizer *)gesture {
    CGPoint center = [gesture locationInView:self.view];
    UISnapBehavior *snapBehavior = [[UISnapBehavior alloc] initWithItem:dragonImageView snapToPoint:center];
    snapBehavior.damping = 0.75f;
    [animator addBehavior:snapBehavior];
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

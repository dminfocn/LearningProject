//
//  ZLCollisionViewController.h
//  UIDynamics
//
//  Created by 朱占龙 on 2017/10/22.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ZLCollisionViewController : UIViewController
{
    IBOutlet UIImageView *dragImageView;
    IBOutlet UIImageView *frogImageView;
    
    IBOutlet UILabel *collisionLabelOne;
    IBOutlet UILabel *collisionLabelTwo;
    
    UIDynamicAnimator *dynamic;
}
@end

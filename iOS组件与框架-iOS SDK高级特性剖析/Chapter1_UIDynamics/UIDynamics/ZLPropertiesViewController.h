//
//  ZLPropertiesViewController.h
//  UIDynamics
//
//  Created by 朱占龙 on 2017/10/22.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ZLPropertiesViewController : UIViewController
{
    UIDynamicAnimator *animator;
    
    __weak IBOutlet UIImageView *dragonImageView;
    __weak IBOutlet UIImageView *frogImageView;
}
@end

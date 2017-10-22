//
//  ZLAttachmentViewController.h
//  UIDynamics
//
//  Created by 朱占龙 on 2017/10/22.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ZLAttachmentViewController : UIViewController
{
    IBOutlet UIImageView *frogImageView;
    IBOutlet UIImageView *dragImageView;
    
    UIDynamicAnimator *dynamic;
}

/** attachmentBehavior */
@property(nonatomic, strong) UIAttachmentBehavior *attachentBehavior;
@end

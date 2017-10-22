//
//  ZLIndexViewController.m
//  UIDynamics
//
//  Created by 朱占龙 on 2017/10/21.
//  Copyright © 2017年 cuit. All rights reserved.
//

#import "ZLIndexViewController.h"
#import "ZLGravityViewController.h"
#import "ZLCollisionViewController.h"
#import "ZLAttachmentViewController.h"

@interface ZLIndexViewController ()

@end

@implementation ZLIndexViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"UIKit Dynamics";
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    //取消选中
    [myTableView deselectRowAtIndexPath:[myTableView indexPathForSelectedRow] animated:YES];
}

- (NSInteger)tableView:(nonnull UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 7;
}

- (nonnull UITableViewCell *)tableView:(nonnull UITableView *)tableView cellForRowAtIndexPath:(nonnull NSIndexPath *)indexPath {
    UITableViewCell *cell = [myTableView dequeueReusableCellWithIdentifier:@"cell"];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"cell"];
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    }
    switch ([indexPath row]) {
        case 0:
            cell.textLabel.text = @"Gravity";
            break;
        case 1:
            cell.textLabel.text = @"Collision";
            break;
        case 2:
            cell.textLabel.text = @"attachement";
            break;
        default:
            break;
    }
    return cell;
}
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    UIViewController *viewController = nil;
    switch (indexPath.row) {
        case 0:
            //跳转
            viewController = [[ZLGravityViewController alloc] initWithNibName:@"ZLGravityViewController" bundle:nil];
            break;
        case 1:
            viewController = [[ZLCollisionViewController alloc] initWithNibName:@"ZLCollisionViewController" bundle:nil];
            break;
        case 2:
            viewController = [[ZLAttachmentViewController alloc] initWithNibName:@"ZLAttachmentViewController" bundle:nil];
            break;
        default:
            break;
    }
    [self.navigationController pushViewController:viewController animated:YES];
}
@end

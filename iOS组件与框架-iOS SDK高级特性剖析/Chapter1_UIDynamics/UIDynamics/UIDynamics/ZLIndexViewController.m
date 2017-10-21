//
//  ZLIndexViewController.m
//  UIDynamics
//
//  Created by 朱占龙 on 2017/10/21.
//  Copyright © 2017年 cuit. All rights reserved.
//

#import "ZLIndexViewController.h"

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
        default:
            break;
    }
    return cell;
}
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    switch (indexPath.row) {
        case 0:
            //跳转
            break;
            
        default:
            break;
    }
}
@end

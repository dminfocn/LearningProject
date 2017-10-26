//
//  AppDelegate.h
//  FavoritePlaces
//
//  Created by 朱占龙 on 2017/10/22.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
//描述数据模型的结构信息
@property (readonly, strong, nonatomic) NSManagedObjectModel *managedObjectModel;
//数据持久层和内存对象模型的协调器
@property (readonly, strong, nonatomic) NSPersistentStoreCoordinator *persistentStoreCoordinator;
//内存中 managedObject 对象的上下文
@property (readonly, strong, nonatomic) NSManagedObjectContext *managedObjectContext;


- (void)saveContext;
- (NSURL *)applicationDocumentsDirectory;
@end


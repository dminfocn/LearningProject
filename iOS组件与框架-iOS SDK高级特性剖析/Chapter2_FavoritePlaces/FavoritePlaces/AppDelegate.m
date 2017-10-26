//
//  AppDelegate.m
//  FavoritePlaces
//
//  Created by 朱占龙 on 2017/10/22.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#import "AppDelegate.h"
#import "ZLLocationManager.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

@synthesize managedObjectModel = __managedObjectModel;
@synthesize persistentStoreCoordinator = __persistentStoreCoordinator;
@synthesize managedObjectContext = __managedObjectContext;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    if ([CLLocationManager locationServicesEnabled]) {
        ZLLocationManager *appLocationManager = [ZLLocationManager sharedLocationManager];
        [appLocationManager.locationManager startUpdatingLocation];
    }else {
        NSLog(@"Location service is not avaliable!");
    }
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    ZLLocationManager *appLocationManager = [ZLLocationManager sharedLocationManager];
    [appLocationManager.locationManager stopUpdatingLocation];
}

- (void)saveContext
{
    NSError *error = nil;
    NSManagedObjectContext *managedObjectContext = self.managedObjectContext;
    if (managedObjectContext != nil) {
        if ([managedObjectContext hasChanges] && ![managedObjectContext save:&error]) {
            NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
            abort();
        }
    }
}

#pragma mark - Core Data stack
// Returns the managed object model for the application.
// If the model doesn't already exist, it is created from the application's model.
- (NSManagedObjectModel *)managedObjectModel
{
    if (__managedObjectModel != nil)
    {
        return __managedObjectModel;
    }
    NSURL *modelURL =
    [[NSBundle mainBundle] URLForResource:@"FavoritePlace" withExtension:@"momd"];
    __managedObjectModel = [[NSManagedObjectModel alloc] initWithContentsOfURL:modelURL];
    return __managedObjectModel;
}

// Returns the persistent store coordinator for the application.
// If the coordinator doesn't already exist, it is created and the application's store added to it.
- (NSPersistentStoreCoordinator *)persistentStoreCoordinator
{
    if (__persistentStoreCoordinator != nil)
    {
        return __persistentStoreCoordinator;
    }
    NSError *error = nil;
    NSURL *storeURL =
    [[self applicationDocumentsDirectory] URLByAppendingPathComponent:@"FavoritePlaces.sqlite"];
    BOOL dataFileAlreadyExists =
    [[NSFileManager defaultManager] fileExistsAtPath:[storeURL path]];
    if (!dataFileAlreadyExists) {
        NSString *bundleStore = [[NSBundle mainBundle] pathForResource:@"FavoritePlaces" ofType:@"sqlite"];
        [[NSFileManager defaultManager] copyItemAtPath:bundleStore toPath:[storeURL path] error:&error];
        if (error) {
            NSLog(@"Error copying baked database: %@", error);
        }
    }
    __persistentStoreCoordinator = [[NSPersistentStoreCoordinator alloc]
     initWithManagedObjectModel:[self managedObjectModel]];
    if (![__persistentStoreCoordinator
          addPersistentStoreWithType:NSSQLiteStoreType
          configuration:nil URL:storeURL options:nil
          error:&error]){
        NSLog(@"Unresolved error %@, %@", error,
              [error userInfo]);
        abort();
    }
    return __persistentStoreCoordinator;
}
// Returns the managed object context for the application.
// If the context doesn't already exist, it is created and bound to the persistent store coordinator for the application.
- (NSManagedObjectContext *)managedObjectContext
{
    if (__managedObjectContext != nil)
    {
        return __managedObjectContext;
    }
    
    NSPersistentStoreCoordinator *coordinator =
    [self persistentStoreCoordinator];
    
    if (coordinator != nil)
    {
        __managedObjectContext =
        [[NSManagedObjectContext alloc] initWithConcurrencyType:NSMainQueueConcurrencyType];
        
        [__managedObjectContext
         setPersistentStoreCoordinator:coordinator];
    }
    return __managedObjectContext;
}
#pragma mark - Application's Documents directory

// Returns the URL to the application's Documents directory.
- (NSURL *)applicationDocumentsDirectory
{
    return [[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask] lastObject];
}

@end

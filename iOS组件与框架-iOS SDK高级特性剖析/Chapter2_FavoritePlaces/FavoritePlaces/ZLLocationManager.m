//
//  ZLLocationManager.m
//  FavoritePlaces
//
//  Created by 朱占龙 on 2017/10/22.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#import "ZLLocationManager.h"

static ZLLocationManager *_sharedLocationManager;

@interface ZLLocationManager()
/** array */
@property(nonatomic, strong) NSMutableArray *completionBlocks;
@end
@implementation ZLLocationManager

+ (ZLLocationManager *)sharedLocationManager {
    static dispatch_once_t once_Token;
    dispatch_once(&once_Token, ^{
        _sharedLocationManager = [[ZLLocationManager alloc] init];
    });
    return _sharedLocationManager;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        [self setLocationManager:[[CLLocationManager alloc] init]];
        [self.locationManager setDesiredAccuracy:kCLLocationAccuracyBest];
        [self.locationManager setDistanceFilter:100.0f];
        [self.locationManager setDelegate:self];
        [self setCompletionBlocks:[NSMutableArray arrayWithCapacity:30]];
        [self setGeocoder:[[CLGeocoder alloc] init]];
    }
    return self;
}

- (void)getLocationWithCompletionBlock:(ZLLocationUpdateCompletionBlock)block {
    if (block) {
        [self.completionBlocks addObject:[block copy]];
    }
    if (self.hasLocation) {
        for (ZLLocationUpdateCompletionBlock completionBlock in self.completionBlocks) {
            completionBlock(self.location, nil);
        }
        if ([self.completionBlocks count] == 0) {
            [[NSNotificationCenter defaultCenter] postNotificationName:@"locationUpdated" object:nil];
        }
        [self.completionBlocks removeAllObjects];
    }
    if (self.locationError) {
        for (ZLLocationUpdateCompletionBlock completionBlock in self.completionBlocks) {
            completionBlock(nil, self.locationError);
        }
        [self.completionBlocks removeAllObjects];
    }
}

#pragma mark - CLLocationManagerDelegate methods
- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray<CLLocation *> *)locations {
    //过滤不准确的点
    CLLocation *lastLocation = locations.lastObject;
    if (lastLocation.horizontalAccuracy < 0) {
        return;
    }
    [self setLocation:lastLocation];
    [self setHasLocation:YES];
    [self setLocationError:nil];
    
    CLLocationCoordinate2D coordinate = lastLocation.coordinate;
    NSLog(@"Location lat/long: %f,%f",coordinate.latitude, coordinate.longitude);
    
    CLLocationAccuracy accuracy = lastLocation.horizontalAccuracy;
    NSLog(@"Horizontal accuracy: %f meters",accuracy);
    
    CLLocationDistance distance = lastLocation.altitude;
    NSLog(@"Location altitude: %f meters",distance);
    
    CLLocationAccuracy verticalAccuracy = lastLocation.verticalAccuracy;
    NSLog(@"verticalAccuracy accuracy: %f meters",verticalAccuracy);
    
    CLLocationSpeed speed = lastLocation.speed;
    NSLog(@"speed: %f meters per second", speed);
    
    CLLocationDirection direction = lastLocation.course;
    NSLog(@"course: %f degrees from true north", direction);
    [self getLocationWithCompletionBlock:nil];
}

- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error {
    [self.locationManager stopUpdatingLocation];
    [self setLocationError:error];
    [self getLocationWithCompletionBlock:nil];
}

- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status {
    if (status == kCLAuthorizationStatusDenied) {
        //禁用了定位功能
        [self.locationManager stopUpdatingLocation];
        
        NSString *errorMessage = @"Location Services Permission Denied for this app.  Visit Settings.app to allow.";
        NSDictionary *erroInfo = @{NSLocalizedDescriptionKey:errorMessage};
        NSError *deniedInfo = [NSError errorWithDomain:@"ZLLocationErrorDomain" code:1 userInfo:erroInfo];
        [self setLocationError:deniedInfo];
        [self getLocationWithCompletionBlock:nil];
    }
    if (status == kCLAuthorizationStatusAuthorizedAlways) {
        [self.locationManager startUpdatingLocation];
        [self setLocationError:nil];
    }
}
@end

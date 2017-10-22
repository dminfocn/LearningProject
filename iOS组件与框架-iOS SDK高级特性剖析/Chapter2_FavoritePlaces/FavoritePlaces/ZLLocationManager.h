//
//  ZLLocationManager.h
//  FavoritePlaces
//
//  Created by 朱占龙 on 2017/10/22.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

typedef void(^ZLLocationUpdateCompletionBlock)(CLLocation *location,NSError *error);

@interface ZLLocationManager : NSObject<CLLocationManagerDelegate>

+ (ZLLocationManager *)sharedLocationManager;
/** location */
@property(nonatomic, strong) CLLocation *location;
/** locationManager */
@property(nonatomic, strong) CLLocationManager *locationManager;
/** geocoder */
@property(nonatomic, strong) CLGeocoder *geocoder;
@property (nonatomic) BOOL hasLocation;
/** error */
@property(nonatomic, strong) NSError *locationError;

- (void)getLocationWithCompletionBlock:(ZLLocationUpdateCompletionBlock)block;
@end

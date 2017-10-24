//
//  ZLFavoritePlace.m
//  FavoritePlaces
//
//  Created by 朱占龙 on 2017/10/24.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#import "ZLFavoritePlace.h"

@implementation ZLFavoritePlace
- (CLLocationCoordinate2D)coordinate {
    CLLocationDegrees lati = [[self valueForKeyPath:@"latitude"] doubleValue];
    CLLocationDegrees lon = [[self valueForKeyPath:@"longtitude"] doubleValue];
    CLLocationCoordinate2D cooredinate = CLLocationCoordinate2DMake(lati, lon);
    return cooredinate;
}
- (void)setCoordinate:(CLLocationCoordinate2D)newCoordinate {
    [self setValue:@(newCoordinate.latitude) forKey:@"latitude"];
    [self setValue:@(newCoordinate.longitude) forKey:@"longtitude"];
}

- (NSString *)title {
    return [self valueForKeyPath:@"placeName"];
}

- (NSString *)subtitle {
    NSString *subTittle = @"";
    NSString *addressString = [self valueForKeyPath:@"placeStreetAddress"];
    if ([addressString length] > 0) {
        NSString *addre = [self valueForKeyPath:@"placeStreetAddress"];
        NSString *city = [self valueForKey:@"placeCity"];
        NSString *state = [self valueForKey:@"placeState"];
        NSString *zip = [self valueForKey:@"placePostal"];
        subTittle = [NSString stringWithFormat:@"%@, %@, %@, %@",addre, city, state, zip];
    }
    return subTittle;
}
@end

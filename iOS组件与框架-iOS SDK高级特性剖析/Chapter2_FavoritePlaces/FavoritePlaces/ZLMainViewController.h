//
//  ZLMainViewController.h
//  FavoritePlaces
//
//  Created by 朱占龙 on 2017/10/23.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>

@interface ZLMainViewController : UIViewController<MKMapViewDelegate>

@property (strong, nonatomic) IBOutlet MKMapView *mapView;

- (IBAction)mapTyeChanged:(id)sender;

@end

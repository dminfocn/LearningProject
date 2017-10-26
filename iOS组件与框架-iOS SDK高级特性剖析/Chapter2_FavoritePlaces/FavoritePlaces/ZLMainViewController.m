//
//  ZLMainViewController.m
//  FavoritePlaces
//
//  Created by 朱占龙 on 2017/10/23.
//  Copyright © 2017年 dminfo. All rights reserved.
//

#import "ZLMainViewController.h"
#import <CoreLocation/CoreLocation.h>
#import "ZLLocationManager.h"
#import "ZLFavoritePlace.h"

@interface ZLMainViewController ()

// 缩放地图到合适的大小
- (void)zoomMapToFitAnnotations;
-(void)updateMapAnnotations;
- (void)locationUpdated:(NSNotification *)notification;

@end

@implementation ZLMainViewController

- (void)viewDidLoad {
    [super viewDidLoad];
   
    [self updateMapAnnotations];
}
- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    ZLLocationManager *appLocationManager = [ZLLocationManager sharedLocationManager];
    [appLocationManager getLocationWithCompletionBlock:^(CLLocation *location, NSError *error) {
        if (error) {
            UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:@"错误" message:@"地图错误信息" preferredStyle:UIAlertControllerStyleAlert];
            UIAlertAction *action = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:nil];
            [alertVc addAction:action];
            [self presentViewController:alertVc animated:YES completion:nil];
        }
        //将地图缩放至适当大小
        [self zoomMapToFitAnnotations];
    }];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(locationUpdated:) name:@"locationUpdated" object:nil];
}

- (void)locationUpdated:(NSNotification *)notification {
    NSLog(@"位置更新通知:%@",notification);
}

- (void)zoomMapToFitAnnotations {
    CLLocationCoordinate2D maxCoordinate = CLLocationCoordinate2DMake(-90.0, -180.0);
    CLLocationCoordinate2D minCoordinate = CLLocationCoordinate2DMake(90.0, 180.0);
    //获取地图中的所有标注
    NSArray *currentPlace = [self.mapView annotations];
    
    //获取地图上的最大和最下经度和纬度
    maxCoordinate.latitude = [[currentPlace valueForKeyPath:@"@max.latitude"] doubleValue];
    maxCoordinate.longitude = [[currentPlace valueForKeyPath:@"@max.longtitude"] doubleValue];
    minCoordinate.latitude = [[currentPlace valueForKeyPath:@"@min.latitude"] doubleValue];
    minCoordinate.longitude = [[currentPlace valueForKeyPath:@"@min.longtitude"] doubleValue];
    
    //根据最大和最小经纬度，计算坐标中心
    CLLocationCoordinate2D centerCoordinate;
    centerCoordinate.latitude = (maxCoordinate.latitude + minCoordinate.latitude) * 0.5;
    centerCoordinate.longitude = (maxCoordinate.longitude + minCoordinate.longitude) * 0.5;
    
    //计算地图的跨度，为了最大标注点处显示完整，乘1.2
    MKCoordinateSpan coordinateSpan;
    coordinateSpan.latitudeDelta = (maxCoordinate.latitude - minCoordinate.latitude) * 1.2;
    coordinateSpan.longitudeDelta = (maxCoordinate.longitude - minCoordinate.longitude) * 1.2;
    
    //根据计算所得数据定位地图中心
    MKCoordinateRegion region = MKCoordinateRegionMake(centerCoordinate, coordinateSpan);
    //将地图缩放至适当大小
    [self.mapView setRegion:region animated:YES];
}

//填充初始地图标注
- (void)updateMapAnnotations {
    [self.mapView removeAnnotations:self.mapView.annotations];
    [self.mapView removeOverlays:self.mapView.overlays];
    
    NSFetchRequest *placesRequest =
    [[NSFetchRequest alloc] initWithEntityName:@"FavoritePlace"];
    
    NSManagedObjectContext *moc = kAppDelegate.managedObjectContext;
    
    NSError *error = nil;
    NSArray *places = [moc executeFetchRequest:placesRequest error:&error];
    if (error) {
        NSLog(@"Core Data fetch error %@, %@", error,
              [error userInfo]);
    }
    
    [self.mapView addAnnotations:places];
}

- (IBAction)mapTyeChanged:(id)segment {
    UISegmentedControl *segmentContro = (UISegmentedControl *)segment;
    switch (segmentContro.selectedSegmentIndex) {
        case 0:
            [self.mapView setMapType:MKMapTypeStandard];
            break;
        case 1:
            [self.mapView setMapType:MKMapTypeSatellite];
            break;
        case 2:
            [self.mapView setMapType:MKMapTypeHybrid];
            break;
        default:
            break;
    }
    
}

#pragma mark - MapViewDelegate
- (void)mapView:(MKMapView *)mapView regionDidChangeAnimated:(BOOL)animated {
    MKCoordinateRegion region = mapView.region;
    CLLocationCoordinate2D coordianteCenter = region.center;
    MKCoordinateSpan span = region.span;
    NSLog(@"New map region center:<%f/%f>,span:<%f/%f>",coordianteCenter.latitude, coordianteCenter.longitude,span.latitudeDelta, span.longitudeDelta);
}
@end

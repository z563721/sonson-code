//
//  RootViewController.m
//
// The MIT License
//
// Copyright (c) 2009 sonson, sonson@Picture&Software
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// Created by sonson on 09/07/11.
// Copyright 2009 sonson, sonson@Picture&Software. All rights reserved.
//

#import "RootViewController.h"
#import "DetailViewController.h"

@implementation RootViewController

- (void)viewDidLoad {
    [super viewDidLoad];
	self.title = @"Map";
	self.navigationItem.titleView = searchBar;
}

#pragma mark -
#pragma mark UICGOOGMapGeocodingControllerDelegate

- (void)didFinishGeocoding:(UICGOOGMapGeocodingController*)controller annotation:(id<MKAnnotation>)annotation {
	DNSLogMethod
	//
	// Remove all pins
	//
	[mapView removeAnnotations:mapView.annotations];
	
	//
	// Set view
	//
	MKCoordinateRegion region;
	CLLocationCoordinate2D pos = annotation.coordinate;
	region.center = pos;
	region.span.latitudeDelta = 0.1;
	region.span.longitudeDelta = 0.1;
	[mapView setRegion:region animated:YES];
	
	//
	// Add pin
	//
	[mapView addAnnotation:annotation];
}

- (void)failedGeocoding:(UICGOOGMapGeocodingController*)controller error:(NSError*)error {
}

#pragma mark -
#pragma mark MKMapViewDelegate

- (void)mapView:(MKMapView *)mapView regionWillChangeAnimated:(BOOL)animated {
	[searchBar resignFirstResponder];
}

- (MKAnnotationView *)mapView:(MKMapView *)aMapView viewForAnnotation:(id <MKAnnotation>)annotation {
	MKPinAnnotationView *annotationView = (MKPinAnnotationView*)[mapView dequeueReusableAnnotationViewWithIdentifier:@"A"];
	if (annotationView == nil) {
		annotationView = [[MKPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:@"A"];
		[annotationView autorelease];
	}
	
	annotationView.animatesDrop = YES;
	annotationView.canShowCallout = YES;
	
	//
	// Callout view
	//
	UIButton *button = [UIButton buttonWithType:UIButtonTypeDetailDisclosure];
	annotationView.rightCalloutAccessoryView = button;
	
	return annotationView;
}

- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view calloutAccessoryControlTapped:(UIControl *)control {
	DNSLogMethod
	DetailViewController *detailViewController = [[DetailViewController alloc] initWithStyle:UITableViewStyleGrouped];
	detailViewController.annotation = view.annotation;
	[self.navigationController pushViewController:detailViewController animated:YES];
	[DetailViewController release];
}

#pragma mark -
#pragma mark UISearchBarDelegate

- (void)searchBarSearchButtonClicked:(UISearchBar *)aSearchBar {
	DNSLogMethod
	//
	// Search with keyword
	//
	UICGOOGMapGeocodingController *con = [[UICGOOGMapGeocodingController alloc] initWithQuery:searchBar.text delegate:self];
	[con autorelease];
	[aSearchBar resignFirstResponder];
}

- (void)searchBarCancelButtonClicked:(UISearchBar *)aSearchBar {
	//
	// Remove all pins
	//
	[mapView removeAnnotations:mapView.annotations];
	[searchBar resignFirstResponder];
}

#pragma mark -
#pragma mark dealloc

- (void)dealloc {
    [super dealloc];
}


@end


//
//  UICGoogleGeocoding.m
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

#import "UICGOOGMap.h"
#import "UICGOOGMapGeocodingController.h"

@interface UICGOOGMapGeocodingController(private)
- (UICGOOGMapAnnotation*)checkResultXMLParsing;
@end

@implementation UICGOOGMapGeocodingController

@synthesize currentElementName, currentString, dict;
@synthesize query;

- (id)initWithQuery:(NSString*)incomingQuery delegate:(id<UICGOOGMapGeocodingControllerDelegate>)newDelegate {
	self = [super init];
	
	self.query = incomingQuery;
	
	NSString *divided_string = [incomingQuery stringByReplacingOccurrencesOfString:@" " withString:@"+"];
	NSString *baseURL = @"http://maps.google.com/maps/geo?q=%@&hl=ja&output=xml&oe=utf8&key=%@";
	
	NSString *URLString = [NSString stringWithFormat:baseURL,  [divided_string stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding], google_api_key];
	NSURL *URL = [NSURL URLWithString:URLString];
	NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:URL];
	[request setHTTPMethod:@"GET"];
	
	cache = [[NSMutableData data] retain];
	NSURLConnection *connection = [NSURLConnection connectionWithRequest:request delegate:self];
	[connection start];
	
	
	[UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
	
	delegate = newDelegate;
	
	return self;
}

#pragma mark -
#pragma mark Original

- (UICGOOGMapAnnotation*)checkResultXMLParsing {
	UICGOOGMapAnnotation* annotation = nil;
	
	NSString *coordinateString = [self.dict objectForKey:@"coordinates"];
	NSString *nameString = [self.dict objectForKey:@"name"];
	NSString *addressString = [self.dict objectForKey:@"address"];
	
	float lon, lat;
	
	if (coordinateString != nil) {
		NSArray *nums = [coordinateString componentsSeparatedByString:@","];
		lon = [[nums objectAtIndex:0] floatValue];
		lat = [[nums objectAtIndex:1] floatValue];
	}
	if (nameString != nil) {
	}
	if (addressString != nil) {
	}
	
	if (coordinateString != nil) {
		annotation = [[UICGOOGMapAnnotation alloc] init];
		CLLocationCoordinate2D pos;
		pos.latitude = lat;
		pos.longitude = lon;
		annotation.coordinate = pos;
		annotation.title = nameString;
		annotation.subtitle = addressString;
		[annotation autorelease];
	}
	self.dict = nil;
	return annotation;
}

#pragma mark -
#pragma mark NSXMLParserDelegate

- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qualifiedName attributes:(NSDictionary *)attributeDict {
	self.currentElementName = elementName;
	self.currentString = [NSMutableString string];
}

- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string {
	[self.currentString appendString:string];
}

- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName {
	if( self.currentElementName && self.currentString && [self.currentString length] > 0 ) {
		if ([self.currentElementName isEqualToString:@"coordinates"] || [self.currentElementName isEqualToString:@"name"] || [self.currentElementName isEqualToString:@"address"]) {
			[self.dict setValue:self.currentString forKey:self.currentElementName];
		}
	}
	self.currentElementName = nil;
	self.currentString = nil;
}

#pragma mark -
#pragma mark NSURLConnectionDelegate

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
	[cache appendData:data];
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
	[UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection {
	[UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
	NSXMLParser *parser = [[NSXMLParser alloc] initWithData:cache];
	[parser setDelegate:self];
	self.dict = [NSMutableDictionary dictionary];
	[parser parse];
	
	UICGOOGMapAnnotation *annotation = [self checkResultXMLParsing];
	
	if (annotation == nil) {
		[delegate failedGeocoding:self error:nil];
	}
	else {
		[delegate didFinishGeocoding:self annotation:annotation];
	}
}

#pragma mark -
#pragma mark dealloc

- (void) dealloc {
	DNSLogMethod
	[query release];
	[currentString release];
	[currentElementName release];
	[dict release];
	[cache release];
	[super dealloc];
}

@end

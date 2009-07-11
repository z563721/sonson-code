//
//  UICGoogleGeocoding.h
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

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>

@class UICGOOGMapAnnotation;
@class UICGOOGMapGeocodingController;

// Protocol
@protocol UICGOOGMapGeocodingControllerDelegate <NSObject>
- (void)didFinishGeocoding:(UICGOOGMapGeocodingController*)controller annotation:(id<MKAnnotation>)annotation;
- (void)failedGeocoding:(UICGOOGMapGeocodingController*)controller error:(NSError*)error;
@end

// Class
@interface UICGOOGMapGeocodingController : NSObject {
	NSString										*query;
	id<UICGOOGMapGeocodingControllerDelegate>		delegate;
	
	//
	// Use as cache while NSURLConnection is downloading XML data
	//
	NSMutableData									*cache;
	
	//
	// For XML Parsing
	//
	NSString										*currentElementName;
	NSMutableString									*currentString;
	NSMutableDictionary								*dict;
}
@property (nonatomic, retain) NSString				*currentElementName;
@property (nonatomic, retain) NSMutableString		*currentString;
@property (nonatomic, retain) NSMutableDictionary	*dict;
@property (nonatomic, retain) NSString				*query;
- (id)initWithQuery:(NSString*)query delegate:(id<UICGOOGMapGeocodingControllerDelegate>)newDelegate;
@end

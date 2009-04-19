//
//  UIOpenURL.m
//
//  Created by sonson on 09/04/14.
//  Copyright 2009 UICoderz. All rights reserved.
//
// The MIT License
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

#import "UICOpenURL.h"
#include <stdarg.h>
#include "NSString+URIEscape.h"

@implementation UICOpenURL

#pragma mark -
#pragma mark Class method

+ (UICOpenURL*)OpenURLWithNSURL:(NSURL*)url {
	return [UICOpenURL URLWithString:[url absoluteString]];
}

+ (UICOpenURL*)OpenURLWithScheme:(NSString*)scheme
						  action:(NSString*)action
							path:(NSString*)path
						   query:(NSString*)escapedQuery
			   callbackURLString:(NSString*)callbackURLString {
	NSMutableString* source = [NSMutableString string];
	if ([scheme length] > 0 && [action length] > 0) {
		[source appendFormat:@"%@://%@", scheme, action];
	}
	else {
		return nil;
	}
	if ([path length] > 0) {
		[source appendFormat:@"/%@", path];
	}
	if ([escapedQuery length] > 0) {
		[source appendFormat:@"?%@", escapedQuery];
	}
	if ([callbackURLString length] > 0) {
		[source appendFormat:@"#%@", callbackURLString];
	}
	return [UICOpenURL URLWithString:source];
}

// help tool, to make escaped URL
+ (NSString*)escapedQueryWithValuesAndNames:(NSString*)firstValue, ... {
	va_list argumentList;
	NSMutableString* string = [NSMutableString string];
	if (firstValue) {
		// 最初の引数は varargs リストの一部ではないので、別個に処理する。
		NSString* value = firstValue;
		va_start(argumentList, firstValue);
		NSString* name = va_arg(argumentList, NSString*);
		
		if (value && name) {
			[string appendFormat:@"%@=%@", name, [value stringByAddingPercentEscapesAllSingleByteCharsUsingEncoding:NSUTF8StringEncoding]];
		}
		
		while (1) {
			NSString* value = va_arg(argumentList, NSString*);
			NSString* name = va_arg(argumentList, NSString*);
			if (value && name) {
				[string appendFormat:@"&%@=%@", name, [value stringByAddingPercentEscapesAllSingleByteCharsUsingEncoding:NSUTF8StringEncoding]];
			}
			else {
				break;
			}
		}
		va_end(argumentList);
	}
	return string;
}

#pragma mark -
#pragma mark instance method

// accesor
- (NSString*)callbackURLString {
	NSString *fragment = [self fragment];
	if([fragment length] > 0){
		return fragment;
	}
	return nil;
}

- (NSString*)action {
	return [self host];
}

- (NSString*)data {
	if ([self query]) {
		return [[self query] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	}
	return nil;
}

- (NSDictionary*)valuesAndNamesOfQuery {
	NSString *query = [self query];
	NSArray *queries = [query componentsSeparatedByString:@"&"];
	NSMutableDictionary *queryDict = [NSMutableDictionary dictionary];
	for( id obj in queries ) {
		NSLog( obj );
		NSString* element = (NSString*)obj;
		NSArray *values = [element componentsSeparatedByString:@"="];
		if( [values count] == 2 ) {
			NSString *name = (NSString*)CFURLCreateStringByReplacingPercentEscapesUsingEncoding( kCFAllocatorDefault,  (CFStringRef)[values objectAtIndex:0],	CFSTR(""), kCFStringEncodingUTF8);
			NSString *value = (NSString*)CFURLCreateStringByReplacingPercentEscapesUsingEncoding( kCFAllocatorDefault,  (CFStringRef)[values objectAtIndex:1],	CFSTR(""), kCFStringEncodingUTF8);
			[queryDict setObject:value forKey:name];
			[name release];
			[value release];
		}
	}
	return queryDict;
}

@end

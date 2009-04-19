//
//  receiverAppDelegate.m
//  receiver
//
//  Created by sonson on 09/04/05.
//  Copyright 2009 sonson. All rights reserved.
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

#import "receiverAppDelegate.h"
#import "receiverViewController.h"
#import "UICOpenURL.h"

@implementation receiverAppDelegate

@synthesize window;
@synthesize viewController;
@synthesize callbackURLString;

- (void)applicationDidFinishLaunching:(UIApplication *)application {    
    
    // Override point for customization after app launch    
    [window addSubview:viewController.view];
    [window makeKeyAndVisible];
}

#pragma mark -
#pragma mark Override

- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url {
	UICOpenURL* gotURL = [UICOpenURL OpenURLWithNSURL:url];
	
	UIAlertView *view = [[UIAlertView alloc] initWithTitle:@"UICOpenURL" message:[gotURL path] delegate:nil cancelButtonTitle:nil otherButtonTitles:@"OK",nil];
	[view show];
	[view release];
	
	NSDictionary *queryDict = [gotURL valuesAndNamesOfQuery];
	if ([queryDict objectForKey:@"callback"]) {
		// check callback mode
	}
	self.callbackURLString = [gotURL callbackURLString];
	if ([[queryDict objectForKey:@"mime"] isEqualToString:@"image/png"]) {
		NSString* path = [gotURL path];
		NSData *data = [NSData dataWithContentsOfFile:path];
		UIImage *image = [UIImage imageWithData:data];
		[viewController setImage:image];
		[viewController setText:[NSString stringWithFormat:@"%d", [data length]]];
		return YES;
	}
	return NO;
}

- (void)dealloc {
	[callbackURLString release];
    [viewController release];
    [window release];
    [super dealloc];
}


@end

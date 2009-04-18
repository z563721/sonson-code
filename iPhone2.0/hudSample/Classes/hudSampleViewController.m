// 
// Classes
// hudSampleViewController.m
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
////
//  hudSampleViewController.m
//  hudSample
//
//  Created by sonson on 08/10/27.
//  Copyright __MyCompanyName__ 2008. All rights reserved.
//

#import "hudSampleViewController.h"
#import "hudSampleAppDelegate.h"

@implementation hudSampleViewController

- (IBAction)openHUD:(id)sender {	
	[NSThread detachNewThreadSelector:@selector(openActivityHUDOfString) toTarget:self withObject:nil];	
	int i;
	for( i = 0; i < 10; i++ ) {
		NSLog( @"%d", i );
		[NSThread sleepForTimeInterval:0.1];
	}
	[hud_ dismiss];
}

- (IBAction)openHUDWithCheck:(id)sender {	
	[NSThread detachNewThreadSelector:@selector(openActivityHUDOfStringWithoutCheck) toTarget:self withObject:nil];
	int i;
	for( i = 0; i < 10; i++ ) {
		NSLog( @"%d", i );
		[NSThread sleepForTimeInterval:0.1];
	}
	[hud_ dismiss];
}

- (void) openActivityHUDOfString {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
    hud_ = [[SNHUDActivityView alloc] initWithString:@"Loading..."];
	@synchronized( self ) {
		[hud_ showInView:self.view];
		[hud_ release];
	}
	[pool release];
	[NSThread exit];
}

- (void) openActivityHUDOfStringWithoutCheck {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
    hud_ = [[SNHUDActivityView alloc] initWithString:@"Loading..."];
	@synchronized( self ) {
		hud_.isShownCheckMark = YES;
		[hud_ showInView:self.view];
		[hud_ release];
	}
	[pool release];
	[NSThread exit];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning]; // Releases the view if it doesn't have a superview
    // Release anything that's not essential, such as cached data
}

- (void)dealloc {
    [super dealloc];
}

@end

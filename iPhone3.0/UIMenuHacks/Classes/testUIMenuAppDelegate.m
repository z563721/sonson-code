//
//  testUIMenuAppDelegate.m
//  testUIMenu
//
//  Created by sonson on 09/08/19.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//

#import "testUIMenuAppDelegate.h"
#import "testUIMenuViewController.h"

@implementation testUIMenuAppDelegate

@synthesize window;
@synthesize viewController;


- (void)applicationDidFinishLaunching:(UIApplication *)application {    
    
    // Override point for customization after app launch    
    [window addSubview:viewController.view];
    [window makeKeyAndVisible];
}


- (void)dealloc {
    [viewController release];
    [window release];
    [super dealloc];
}


@end

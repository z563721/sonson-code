//
//  TutorialTestAppDelegate.m
//  TutorialTest
//
//  Created by sonson on 09/09/19.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//

#import "TutorialTestAppDelegate.h"
#import "TutorialTestViewController.h"

@implementation TutorialTestAppDelegate

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

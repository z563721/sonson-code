//
//  testUIMenuAppDelegate.h
//  testUIMenu
//
//  Created by sonson on 09/08/19.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//

#import <UIKit/UIKit.h>

@class testUIMenuViewController;

@interface testUIMenuAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    testUIMenuViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet testUIMenuViewController *viewController;

@end


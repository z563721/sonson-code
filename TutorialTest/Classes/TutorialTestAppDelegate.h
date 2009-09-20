//
//  TutorialTestAppDelegate.h
//  TutorialTest
//
//  Created by sonson on 09/09/19.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//

#import <UIKit/UIKit.h>

@class TutorialTestViewController;

@interface TutorialTestAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    TutorialTestViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet TutorialTestViewController *viewController;

@end


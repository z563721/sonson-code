//
//  UIMenuController+Hack.h
//  UIMenuHacks
//
//  Created by sonson on 09/09/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *kDidDismissedUIMenuController;

@protocol UIMenuControllerHack <NSObject>
+ (void)replaceCallBarButton:(id)callBarButton action:(SEL)action;
+ (void)getBacckCallBarButton:(id)callBarButton action:(SEL)action;
@end

@interface NSObject(UICallBar)
- (BOOL)visible;
- (BOOL)recentlyFaded;
- (id)visibleButtons;
- (id)targetForAction:(SEL)action;
@end

@interface NSObject(UICallBarButton)
- (void)setupWithTitle:(id)title action:(SEL)action;
- (void)setupWithImage:(id)image action:(SEL)action;
- (SEL)action;
@end

@interface UIMenuController(Hack)
@end

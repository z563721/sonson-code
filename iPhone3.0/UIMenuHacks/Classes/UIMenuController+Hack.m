//
//  UIMenuController+Hack.m
//  UIMenuHacks
//
//  Created by sonson on 09/09/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "UIMenuController+Hack.h"

NSMutableArray *targetClassArray = nil;

NSMutableArray *editedButtons = nil;

NSString *kDidDismissedUIMenuController = @"kDidDismissedUIMenuController";

@implementation UIMenuController(Hack)

- (void)checkMethod:(id)callBar {
	if ([callBar visible] && [callBar recentlyFaded]) {
		DNSLog(@"visible - recentlyFaded = 1 - 1");
	}
	else if (![callBar visible] && [callBar recentlyFaded]) {
		DNSLog(@"visible - recentlyFaded = 0 - 1");
	}
	else if ([callBar visible] && ![callBar recentlyFaded]) {
		DNSLog(@"visible - recentlyFaded = 1 - 0");
	}
	else if (![callBar visible] && ![callBar recentlyFaded]) {
		DNSLog(@"visible - recentlyFaded = 0 - 0");
	}
}

- (void)dump:(id)callBar {
	DNSLogMethod
	NSLog(@"UICallBarDelegate %s", class_getName([[callBar delegate] class]));
	NSArray *buttons = [callBar visibleButtons];
	if ([buttons count]) {
		id button = [buttons objectAtIndex:0];
		SEL action = [button action];
		id target = [callBar targetForAction:action];
		NSLog(@"UICallBarButtonDelegate %s %@", class_getName([target class]), NSStringFromSelector(action));
	}
}

- (void)getBacckCallBarButton:(id)callBarButton action:(SEL)action {
	DNSLogMethod
//	NSLog(@"%@", NSStringFromSelector(action));
	if (action == @selector(cut:)) {
		[callBarButton setupWithTitle:NSLocalizedString(@"Cut", nil) action:action];
	}
	else if (action == @selector(copy:)) {
		NSLog(@"%@", NSStringFromSelector(action));
		[callBarButton setupWithTitle:NSLocalizedString(@"Copy", nil) action:action];
	}
	else if (action == @selector(paste:)) {
		[callBarButton setupWithTitle:NSLocalizedString(@"Paste", nil) action:action];
	}
	else if (action == @selector(select:)) {
		[callBarButton setupWithTitle:NSLocalizedString(@"Select", nil) action:action];
	}
	else if (action == @selector(selectAll:)) {
		[callBarButton setupWithTitle:NSLocalizedString(@"Select All", nil) action:action];
	}
	else if (action == @selector(_setRtoLTextDirection:)) {
	}
	else if (action == @selector(_setLtoRTextDirection:)) {
	}
}

- (void)calloutBarWillStartAnimation:(id)callBar {
	DNSLogMethod
//	[self checkMethod:callBar];
//	[self dump:callBar];
	
	NSArray *buttons = [callBar visibleButtons];
	
//	for (id button in buttons) {
//		DNSLog(@"Button %@ %@", NSStringFromSelector([button action]), button);
//	}
	if ([callBar visible] && [callBar recentlyFaded]) {
	}
	
	if (![callBar visible] && ![callBar recentlyFaded]) {
		NSArray *buttons = [callBar visibleButtons];
		
		if (targetClassArray == nil) {
			targetClassArray = [[NSMutableArray array] retain];
		}
		[targetClassArray removeAllObjects];
		
		if (editedButtons == nil) {
			editedButtons = [[NSMutableArray array] retain];
		}
		else {
		}
		
		for (int i = 0; i < [buttons count]; i++) {
			id button = [buttons objectAtIndex:i];
			SEL action = [button action];
			id target = [callBar targetForAction:action];
			if ([[target class] respondsToSelector:@selector(replaceCallBarButton:action:)]) {
				[[target class] replaceCallBarButton:button action:action];
				[targetClassArray addObject:[target class]];
				[editedButtons addObject:button];
			}
		}
	}
}

- (void)calloutBarDidFinishAnimation:(id)callBar {
	DNSLogMethod
	[self checkMethod:callBar];
//	[self dump:callBar];
	
	BOOL isDirty = NO;
	if (![callBar visible] && [callBar recentlyFaded]) {
		
		
		for (id button in [editedButtons reverseObjectEnumerator]) {
			DNSLog(@"Button %@ %@", NSStringFromSelector([button action]), button);
		}
		
		for (id button in [editedButtons reverseObjectEnumerator]) {
			SEL action = [button action];
			// id target = [callBar targetForAction:action];
			[self getBacckCallBarButton:button action:action];
			/*
			if ([[target class] respondsToSelector:@selector(getBacckCallBarButton:action:)]) {
				[[target class] getBacckCallBarButton:button action:action];
				DNSLog(@"Button %@ %@", NSStringFromSelector([button action]), button);
				isDirty = YES;
			}
			 */
			isDirty = YES;
			[editedButtons removeObject:button];
		}
		
		if (isDirty) {
			[[NSNotificationCenter defaultCenter] postNotificationName:kDidDismissedUIMenuController object:nil];
		}
	}
}

@end

/*
for (int i = 0; i < [buttons count]; i++) {
	id button = [buttons objectAtIndex:i];
	if ([targetClassArray count]) {
		id targetClass = [targetClassArray objectAtIndex:i];
		SEL action = [button action];
		NSLog(@"%@", NSStringFromSelector(action));
		if ([targetClass respondsToSelector:@selector(getBacckCallBarButton:action:)]) {
			[targetClass getBacckCallBarButton:button action:action];
			isDirty = YES;
		}
	}
}
*/

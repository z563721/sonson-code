//
//  UIMenuController+Hack.m
//  UIMenuHacks
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

#import "UIMenuController+Hack.h"

NSMutableArray *editedButtons = nil;

@implementation UIMenuController(Hack)

// Get back the captions with strings which are almost original.
- (void)getBackCallBarButton:(id)callBarButton action:(SEL)action {
	DNSLogMethod
	if (action == @selector(cut:)) {
		[callBarButton setupWithImage:nil action:action];
		[callBarButton setupWithTitle:NSLocalizedString(@"Cut", nil) action:action];
	}
	else if (action == @selector(copy:)) {
		[callBarButton setupWithImage:nil action:action];
		[callBarButton setupWithTitle:NSLocalizedString(@"Copy", nil) action:action];
	}
	else if (action == @selector(paste:)) {
		[callBarButton setupWithImage:nil action:action];
		[callBarButton setupWithTitle:NSLocalizedString(@"Paste", nil) action:action];
	}
	else if (action == @selector(select:)) {
		[callBarButton setupWithImage:nil action:action];
		[callBarButton setupWithTitle:NSLocalizedString(@"Select", nil) action:action];
	}
	else if (action == @selector(selectAll:)) {
		[callBarButton setupWithImage:nil action:action];
		[callBarButton setupWithTitle:NSLocalizedString(@"Select All", nil) action:action];
	}
	else if (action == @selector(_setRtoLTextDirection:)) {
	}
	else if (action == @selector(_setLtoRTextDirection:)) {
	}
}

// Call this method when UICallBar's animation will start appearing and hiding. 
- (void)calloutBarWillStartAnimation:(id)callBar {
	DNSLogMethod
	if (![callBar visible] && ![callBar recentlyFaded]) {
		// make array to save buttons which are replaced captions or images.
		if (editedButtons == nil)
			editedButtons = [[NSMutableArray array] retain];
		else
			[editedButtons removeAllObjects];
		
		// If target class has method to replace UICallBarButton's caption, do it.
		for (id button in [callBar visibleButtons]) {
			SEL action = [button action];
			id target = [callBar targetForAction:action];
			if ([[target class] respondsToSelector:@selector(replaceCallBarButton:action:)]) {
				[[target class] replaceCallBarButton:button action:action];
				[editedButtons addObject:button];
			}
		}
	}
}

// Call this method when UICallBar's animation ends appearing and hiding. 
- (void)calloutBarDidFinishAnimation:(id)callBar {
	DNSLogMethod
	if (![callBar visible] && [callBar recentlyFaded]) {
		// Get back buttons with original states.
		for (id button in [editedButtons reverseObjectEnumerator]) {
			[self getBackCallBarButton:button action:[button action]];
			[editedButtons removeObject:button];
		}
	}
}

@end

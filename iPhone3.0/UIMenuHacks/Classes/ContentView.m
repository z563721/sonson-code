//
//  ContentView.m
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

#import "ContentView.h"

@interface NSObject(UIMenuControllerHack)
// delegate
+ (void)replaceCallBarButton:(id)uicallbarbutton action:(SEL)action;
+ (void)getBacckCallBarButton:(id)uicallbarbutton action:(SEL)action;

// UICallBar
- (BOOL)visible;
- (BOOL)recentlyFaded;
- (id)visibleButtons;
- (id)targetForAction:(SEL)fp8;

// UICallBarButton
- (void)setupWithTitle:(id)fp8 action:(SEL)fp12;
- (void)setupWithImage:(id)fp8 action:(SEL)fp12;
- (SEL)action;
@end

BOOL isDirty;
NSMutableArray *targetClassArray = nil;

@implementation UIMenuController(Hack)

- (void)calloutBarWillStartAnimation:(id)fp8 {
	DNSLogMethod
	if (![fp8 visible] && ![fp8 recentlyFaded]) {
		NSArray *buttons = [fp8 visibleButtons];
		
		if (targetClassArray == nil) {
			targetClassArray = [[NSMutableArray array] retain];
		}
		[targetClassArray removeAllObjects];
		
		for (int i = 0; i < [buttons count]; i++) {
			id button = [buttons objectAtIndex:i];
			SEL action = [button action];
			id target = [fp8 targetForAction:action];
			DNSLog(@"%s", class_getName([target class]));
			if ([[target class] respondsToSelector:@selector(replaceCallBarButton:action:)]) {
				[[target class] replaceCallBarButton:button action:action];
				isDirty = YES;
				[targetClassArray addObject:[target class]];
			}
		}
	}
}

- (void)calloutBarDidFinishAnimation:(id)fp8 {
	DNSLogMethod
	
	if (![fp8 visible] && [fp8 recentlyFaded]) {
		NSArray *buttons = [fp8 visibleButtons];
		
		for (int i = 0; i < [buttons count]; i++) {
			id button = [buttons objectAtIndex:i];
			if ([targetClassArray count]) {
			id targetClass = [targetClassArray objectAtIndex:i];
			SEL action = [button action];
			if ([targetClass respondsToSelector:@selector(getBacckCallBarButton:action:)]) {
				[targetClass getBacckCallBarButton:button action:action];
			}
			}
		}
	}
}

@end


#import "ContentView.h"

@implementation ContentView

+ (void)replaceCallBarButton:(id)uicallbarbutton action:(SEL)action {
	if (action == @selector(cut:)) {
		[uicallbarbutton setupWithTitle:NSLocalizedString(@"Copy Body", nil) action:@selector(cut:)];	
	}
	else if (action == @selector(copy:)) {
		[uicallbarbutton setupWithTitle:NSLocalizedString(@"Copy Title&URL", nil) action:@selector(copy:)];	
	}
	else if (action == @selector(paste:)) {
		[uicallbarbutton setupWithTitle:NSLocalizedString(@"Copy All", nil) action:@selector(paste:)];
	}
	else if (action == @selector(select:)) {
	}
	else if (action == @selector(selectAll:)) {
	}
}

+ (void)getBacckCallBarButton:(id)uicallbarbutton action:(SEL)action {
	NSLog(@"getBacckCallBarButton");
	NSLog(@"%@", NSStringFromSelector(action));
	if (action == @selector(cut:)) {
		[uicallbarbutton setupWithTitle:NSLocalizedString(@"Cut", nil) action:@selector(cut:)];
	}
	else if (action == @selector(copy:)) {
		NSLog(@"%@", NSStringFromSelector(action));
		[uicallbarbutton setupWithTitle:NSLocalizedString(@"Copy", nil) action:@selector(copy:)];
	}
	else if (action == @selector(paste:)) {
		[uicallbarbutton setupWithTitle:NSLocalizedString(@"Paste", nil) action:@selector(paste:)];
	}
	else if (action == @selector(select:)) {
		[uicallbarbutton setupWithTitle:NSLocalizedString(@"Select", nil) action:@selector(select:)];
	}
	else if (action == @selector(selectAll:)) {
		[uicallbarbutton setupWithTitle:NSLocalizedString(@"Select All", nil) action:@selector(selectAll:)];
	}
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	
	UITouch *touch = [touches anyObject];
	
	CGPoint point = [touch locationInView:self];
	
	[self becomeFirstResponder];
	UIMenuController *controller = [UIMenuController sharedMenuController];
	[controller setTargetRect:CGRectMake(point.x, point.y, 1, 1) inView:self];
	[controller setMenuVisible:YES animated:YES];
	[controller update];
}

- (BOOL)canBecomeFirstResponder {
	return YES;
}

- (void)copy:(id)sender {
	DNSLogMethod
}

- (void)cut:(id)sender {
	DNSLogMethod
}

- (void)paste:(id)sender {
	DNSLogMethod
}

- (void)select:(id)sender {
	DNSLogMethod
}

- (BOOL)canPerformAction:(SEL)action withSender:(id)sender{
	if (action == @selector(copy:)) {
		return YES;
	}
	if (action == @selector(cut:)) {
		return YES;
	}
	if (action == @selector(paste:)) {
		return YES;
	}
	return NO;
}

- (id)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        // Initialization code
    }
    return self;
}

- (void)drawRect:(CGRect)rect {
    // Drawing code
}

- (void)dealloc {
    [super dealloc];
}

@end

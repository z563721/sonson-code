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
#import "UIMenuController+Hack.h"


#import "ContentView.h"

@implementation ContentView

#pragma mark -
#pragma mark UIMenuControllerHack

+ (void)replaceCallBarButton:(id)callBarButton action:(SEL)action {
	if (action == @selector(cut:)) {
		[callBarButton setupWithTitle:NSLocalizedString(@"do hoge", nil) action:action];
	}
	else if (action == @selector(copy:)) {
		[callBarButton setupWithTitle:NSLocalizedString(@"do bar", nil) action:action];
	}
	else if (action == @selector(paste:)) {
		[callBarButton setupWithTitle:NSLocalizedString(@"do foo", nil) action:action];
	}
	else if (action == @selector(select:)) {
	}
	else if (action == @selector(selectAll:)) {
	}
	else if (action == @selector(_setRtoLTextDirection:)) {
	}
	else if (action == @selector(_setLtoRTextDirection:)) {
	}
}

+ (void)getBacckCallBarButton:(id)callBarButton action:(SEL)action {
	DNSLogMethod
	NSLog(@"%@", NSStringFromSelector(action));
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

#pragma mark -
#pragma mark for UIMenuController

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

- (void)selectAll:(id)sender {
	DNSLogMethod
}

- (void)_setRtoLTextDirection:(id)sender {
	DNSLogMethod
}

- (void)_setLtoRTextDirection:(id)sender {
	DNSLogMethod
}

- (BOOL)canPerformAction:(SEL)action withSender:(id)sender{
	NSLog(@"%@", NSStringFromSelector(action));
	if (action == @selector(cut:)) {
		return YES;
	}
	if (action == @selector(copy:)) {
		return YES;
	}
	if (action == @selector(paste:)) {
		return YES;
	}
	return NO;
}

- (void)didDismissedUIMenuController:(NSNotification*)notification {
	NSLog(@"didDismissedUIMenuController:");
	[self resignFirstResponder];
}

#pragma mark -
#pragma mark Override

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	
	UITouch *touch = [touches anyObject];
	
	CGPoint point = [touch locationInView:self];
	
	[self becomeFirstResponder];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didDismissedUIMenuController:) name:kDidDismissedUIMenuController object:nil];
	UIMenuController *controller = [UIMenuController sharedMenuController];
	[controller setTargetRect:CGRectMake(point.x, point.y, 1, 1) inView:self];
	[controller setMenuVisible:YES animated:YES];
	[controller update];
}

- (BOOL)canBecomeFirstResponder {
	return YES;
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
	[[NSNotificationCenter defaultCenter] removeObserver:self];
    [super dealloc];
}

@end

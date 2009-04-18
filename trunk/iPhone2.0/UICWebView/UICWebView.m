// 
// UICWebView
// UICWebView.m
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
//  SNWebView.m
//  hookWebViewSample
//
//  Created by sonson on 08/11/07.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "UICWebView.h"
#if TARGET_IPHONE_SIMULATOR
	#import <objc/objc-runtime.h>
#else
	#import <objc/runtime.h>
#endif

const char* kUIWebDocumentView= "UIWebDocumentView";

@interface NSObject (UICWebViewDelegate)
- (void)touchesBegan:(NSSet*)touches inWebView:(UIWebView*)sender withEvent:(UIEvent*)event;
- (void)touchesMoved:(NSSet*)touches inWebView:(UIWebView*)sender withEvent:(UIEvent*)event;
- (void)touchesEnded:(NSSet*)touches inWebView:(UIWebView*)sender withEvent:(UIEvent*)event;
- (void)touchesCancelled:(NSSet*)touches inWebView:(UIWebView*)sender withEvent:(UIEvent*)event;
@end

@interface UICWebView (private)
- (void)hookedTouchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)hookedTouchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)hookedTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)hookedTouchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;
@end

@implementation UIView (__TapHook)

- (void)__replacedTouchesBegan:(NSSet*)touches withEvent:(UIEvent*)event {
	[self __replacedTouchesBegan:touches withEvent:event];		// call @selector(touchesBegan:withEvent:)
	if( [self.superview.superview isMemberOfClass:[UICWebView class]] ) {
		[(UICWebView*)self.superview.superview hookedTouchesBegan:touches withEvent:event];
	}
}
- (void)__replacedTouchesMoved:(NSSet*)touches withEvent:(UIEvent*)event {
	[self __replacedTouchesMoved:touches withEvent:event];		// call @selector(touchesMoved:withEvent:)
	if( [self.superview.superview isMemberOfClass:[UICWebView class]] ) {
		[(UICWebView*)self.superview.superview hookedTouchesMoved:touches withEvent:event];
	}
}

- (void)__replacedTouchesEnded:(NSSet*)touches withEvent:(UIEvent*)event {
	[self __replacedTouchesEnded:touches withEvent:event];		// call @selector(touchesEnded:withEvent:)
	if( [self.superview.superview isMemberOfClass:[UICWebView class]] ) {
		[(UICWebView*)self.superview.superview hookedTouchesEnded:touches withEvent:event];
	}
}

- (void)__replacedTouchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event {
	[self __replacedTouchesCancelled:touches withEvent:event];	// call @selector(touchesCancelled:withEvent:)
	if( [self.superview.superview isMemberOfClass:[UICWebView class]] ) {
		[(UICWebView*)self.superview.superview hookedTouchesCancelled:touches withEvent:event];
	}
}

@end

static BOOL isAlreaddHookInstalled = NO;

@implementation UICWebView

#pragma mark Class method setup hookmethod for UIWebDocumentView

+ (void)installHook {
	if( isAlreaddHookInstalled )
		return;
	isAlreaddHookInstalled = YES;
	
	Class klass = objc_getClass( kUIWebDocumentView );
	
	if( klass == nil )
		return;		// if there is no UIWebDocumentView in the future.
	
	// replace touch began event
	method_exchangeImplementations(
					class_getInstanceMethod(klass, @selector(touchesBegan:withEvent:)), 
					class_getInstanceMethod(klass, @selector(__replacedTouchesBegan:withEvent:)) );
	
	// replace touch moved event
	method_exchangeImplementations(
					class_getInstanceMethod(klass, @selector(touchesMoved:withEvent:)), 
					class_getInstanceMethod(klass, @selector(__replacedTouchesMoved:withEvent:))
	);
	
	// replace touch ended event
	method_exchangeImplementations(
					class_getInstanceMethod(klass, @selector(touchesEnded:withEvent:)), 
					class_getInstanceMethod(klass, @selector(__replacedTouchesEnded:withEvent:))
	);
	
	// replace touch cancelled event
	method_exchangeImplementations(
					class_getInstanceMethod(klass, @selector(touchesCancelled:withEvent:)), 
					class_getInstanceMethod(klass, @selector(__replacedTouchesCancelled:withEvent:))
	);
}

#pragma mark Original method for call delegate method

- (void)hookedTouchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	if( [self.delegate respondsToSelector:@selector(touchesBegan:inWebView:withEvent:)] )
		[(NSObject*)self.delegate touchesBegan:touches inWebView:self withEvent:event];
}

- (void)hookedTouchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
	if( [self.delegate respondsToSelector:@selector(touchesMoved:inWebView:withEvent:)] )
		[(NSObject*)self.delegate touchesMoved:touches inWebView:self withEvent:event];
}

- (void)hookedTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	if( [self.delegate respondsToSelector:@selector(touchesEnded:inWebView:withEvent:)] )
		[(NSObject*)self.delegate touchesEnded:touches inWebView:self withEvent:event];
}

- (void)hookedTouchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
	if( [self.delegate respondsToSelector:@selector(touchesCancelled:inWebView:withEvent:)] )
		[(NSObject*)self.delegate touchesCancelled:touches inWebView:self withEvent:event];
}

#pragma mark override

- (id)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
		[UICWebView installHook];
    }
    return self;
}

- (id)initWithCoder:(NSCoder*)coder {
    if (self = [super initWithCoder:coder]) {
		[UICWebView installHook];
    }
    return self;
}

@end

//
//  ContentView.m
//  testUIMenu
//
//  Created by sonson on 09/08/19.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "ContentView.h"

@interface NSObject(UIMenuControllerHack)
- (id)visibleButtons;
- (void)setupWithTitle:(id)fp8 action:(SEL)fp12;
- (void)setupWithImage:(id)fp8 action:(SEL)fp12;
- (SEL)action;
- (BOOL)visible;
- (id)targetForAction:(SEL)fp8;
@end

BOOL isOriginalMenu = NO;

@implementation UIMenuController(Hack)

- (void)calloutBarWillStartAnimation:(id)fp8 {
	NSLog( @"%s", class_getName([fp8 class]) );
	
	if (![fp8 visible]) {
		NSArray *buttons = [fp8 visibleButtons];
		NSLog( @"%s", class_getName([buttons class]) );
		for (id button in buttons) {
			NSLog( @"%s", class_getName([button class]) );
			if ([button action] == @selector(copy:) && [[fp8 targetForAction:@selector(copy:)] isKindOfClass:[ContentView class]]) {
				[button setupWithTitle:@"Copy Title" action:@selector(hoge:)];
			}
		}		
	}
}

- (void)calloutBarDidFinishAnimation:(id)fp8 {
	if (![fp8 visible]) {
		NSArray *buttons = [fp8 visibleButtons];
		NSLog( @"%s", class_getName([buttons class]) );
		for (id button in buttons) {
			NSLog( @"%s", class_getName([button class]) );
			if ([button action] == @selector(hoge:) && [[fp8 targetForAction:@selector(hoge:)] isKindOfClass:[ContentView class]]) {
				[button setupWithTitle:@"Copy" action:@selector(copy:)];
			}
		}
	}
}

@end


#import "ContentView.h"

void dumpSubview( UIView* view ) {
    NSLog( @"%s", class_getName([view class]) );
    for( UIView *subview in [view subviews] ) {
        dumpSubview( subview );
    }
}


@implementation ContentView

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	NSLog(@"a");
	
	isOriginalMenu = YES;
	
	[self becomeFirstResponder];
	UIMenuController *controller = [UIMenuController sharedMenuController];
	[controller setTargetRect:CGRectMake(0, 0, 100, 10) inView:self];
	[controller setMenuVisible:YES animated:YES];
	
	dumpSubview(self.superview.superview);
	[controller update];
	
	id cameraController = [objc_getClass(@"UICalloutView") sharedCalloutView];
}

- (BOOL)canBecomeFirstResponder {
	return YES;
}

- (void)copy:(id)sender {
}

- (void)paste:(id)sender {
}

- (void)hoge:(id)sender {
}

- (BOOL)canPerformAction:(SEL)action withSender:(id)sender{
//    NSLog(@"%s", class_getName([sender class]) );
//	NSLog(@"%@", NSStringFromSelector(action));
	if (action == @selector(copy:)) {
		return YES;
	}
	if (action == @selector(paste:)) {
		return YES;
	}
	if (action == @selector(hoge:)) {
		return YES;
	}
	return NO;
//	return YES;	
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

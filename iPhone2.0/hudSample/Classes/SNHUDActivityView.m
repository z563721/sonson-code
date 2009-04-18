// 
// Classes
// SNHUDActivityView.m
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
//#import "SNHUDActivityView.h"

@implementation SNHUDActivityView

@synthesize isShownCheckMark = isShownCheckMark_;
@synthesize durationToShowCheckMark = durationToShowCheckMark_;

#pragma mark Override

- (void) initializeMessageLabelWithString:(NSString*)message {
	// setup label
	label_ = [[UILabel alloc] initWithFrame:CGRectZero];
	label_.backgroundColor = [UIColor clearColor];
	label_.textColor = [UIColor whiteColor];
	label_.font = [UIFont boldSystemFontOfSize:24];
	label_.textAlignment = UITextAlignmentCenter;
	label_.baselineAdjustment = UIBaselineAdjustmentAlignCenters;
	label_.lineBreakMode = UILineBreakModeCharacterWrap;
	label_.numberOfLines = 2;
	label_.text = message;
	[self addSubview:label_];
	[label_ release];
}

- (id) initWithString:(NSString*)message {
	NSLog( @"[SNHUDProgressView] - initWithString:" );
	UIImage *base =  [UIImage imageNamed:@"dialogue.png"];
	UIImage *newImage = [base stretchableImageWithLeftCapWidth:11.0 topCapHeight:11.0];
	
	if( self = [super initWithImage:newImage] ) {
		[self initializeMessageLabelWithString:message];
		
		indicator_ = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
		[self addSubview:indicator_];
		[indicator_ release];
		
		isShownCheckMark_ = DEFAULT_IS_SHOWN_CHECK_MARK;
		durationToShowCheckMark_ = DEFAULT_DURATION_TO_SHOW_MARK;
		
		// layout UILabel
		CGRect activity_arranged_rect;
		CGRect messageLabel_arranged_rect;
		CGRect hud_arranged_rect;
		
		messageLabel_arranged_rect = [label_ textRectForBounds:CGRectMake( 0,0,DEFAULT_MESSAGE_WIDTH,DEFAULT_MESSAGE_HEIGHT) limitedToNumberOfLines:2];
		hud_arranged_rect = CGRectMake( 0, 0, messageLabel_arranged_rect.size.width + DEFAULT_MESSAGE_HORIZONTAL_MARGIN, DEFAULT_HUD_HEIGHT );
		
		activity_arranged_rect = indicator_.frame;
		activity_arranged_rect.origin.x = hud_arranged_rect.size.width / 2 - activity_arranged_rect.size.width / 2 ;
		activity_arranged_rect.origin.y = DEFAULT_MARK_TOP_MARGIN - activity_arranged_rect.size.height / 2 ;
		indicator_.frame = activity_arranged_rect;
		
		messageLabel_arranged_rect.origin.x = hud_arranged_rect.size.width / 2 - messageLabel_arranged_rect.size.width / 2 ;
		messageLabel_arranged_rect.origin.y = activity_arranged_rect.origin.y + activity_arranged_rect.size.height/2 + DEFAULT_MARGIN_BETWEEN_MARK_MESSAGE;
		label_.frame = messageLabel_arranged_rect;
		
		hud_arranged_rect.size.height = messageLabel_arranged_rect.origin.y +  + messageLabel_arranged_rect.size.height + DEFAULT_MESSAGE_BOTTOM_MARGIN;
		
		self.frame = hud_arranged_rect;
		
	}
	return self;
}

- (void) showInView:(UIView*) view {
	CGRect superview_rect = view.frame;
	CGRect self_rect = self.frame;
	self_rect.origin.x = superview_rect.size.width /2 - self.frame.size.width /2;
	self_rect.origin.y = superview_rect.size.height /2 - self.frame.size.height /2;
	self.frame = self_rect;
	[indicator_ startAnimating];
	[view addSubview:self];
	[self makeDisabledInteraction];
}

- (void) dismiss {
	if( isShownCheckMark_ ) {
		[NSThread detachNewThreadSelector:@selector(addCheck) toTarget:self withObject:nil];
	}
	else {
		[self makeEnabledInteraction];
		[self removeFromSuperview];
	}
}

- (void) makeDisabledInteraction {
	[[UIApplication sharedApplication] beginIgnoringInteractionEvents];
}

- (void) makeEnabledInteraction {
	while( [[UIApplication sharedApplication] isIgnoringInteractionEvents] ) {
		[NSThread sleepForTimeInterval:0.05];
		[[UIApplication sharedApplication] endIgnoringInteractionEvents];
	}
}

- (void) addCheck {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	@synchronized( self ) {	
		UIImage *check_mark =  [UIImage imageNamed:@"check.png"];
		UIImageView *check_ = [[UIImageView alloc] initWithImage:check_mark];
		[indicator_ removeFromSuperview];
		
		CGRect animation_item_rect = check_.frame;
		animation_item_rect.origin.x = self.frame.size.width / 2 - animation_item_rect.size.width / 2 ;
		animation_item_rect.origin.y = DEFAULT_MARK_TOP_MARGIN - animation_item_rect.size.height / 2 ;
		check_.frame = animation_item_rect;
		[self addSubview:check_];
		[check_ release];
		[NSThread detachNewThreadSelector:@selector(dimissAfterShowingCheckMark) toTarget:self withObject:nil];
	}
	[pool release];
	[NSThread exit];
}

- (void) dimissAfterShowingCheckMark {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	@synchronized( self ) {
		[NSThread sleepForTimeInterval:durationToShowCheckMark_];
		[self makeEnabledInteraction];
		[self removeFromSuperview];
	}
	[pool release];
	[NSThread exit];
}

- (BOOL) isShown {
	return (self.superview == nil);
}

@end

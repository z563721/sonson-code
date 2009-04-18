// 
// Classes
// SNMiniBadgeView.m
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
//  MiniBadgeView.m
//  2tch
//
//  Created by sonson on 08/12/28.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "SNMiniBadgeView.h"

UIImage* badgeImage = nil;

@implementation SNMiniBadgeView

@synthesize rightTop = rightTop_;

+ (void)initialize {
	if( badgeImage == nil ) {
		UIImage *original = [UIImage imageNamed:@"miniBadge.png"];
		badgeImage = [[original stretchableImageWithLeftCapWidth:15 topCapHeight:0] retain];
	}
}

- (id)init {
    if (self = [super initWithImage:badgeImage]) {
        // Initialization code
		CGRect frame2;
		
		// 29, 30
		frame2.size = badgeImage.size;
		self.frame = frame2;
		label_ = [[UILabel alloc] initWithFrame:CGRectZero];
		label_.font = [UIFont boldSystemFontOfSize:14];
		label_.textColor = [UIColor whiteColor];
		label_.backgroundColor = [UIColor clearColor];
		[self addSubview:label_];
		self.hidden = YES;
    }
    return self;
}

- (void)set:(int)remained {
	DNSLogMethod
	if( remained == 0 ) {
		self.hidden = YES;
	}
	else {
		label_.text = [NSString stringWithFormat:@"%d", remained];
		CGRect rect = [label_ textRectForBounds:CGRectMake( 0, 0, 300, 300) limitedToNumberOfLines:1];
		DNSLog( @"%f,%f", rect.size.width, rect.size.height );
		
		CGRect newRect = self.frame;
		newRect.size.width = rect.size.width + 24;
		self.frame = newRect;
		label_.frame = rect;
		label_.center = CGPointMake( self.frame.size.width / 2.0 + 0.25, self.frame.size.height / 2.0 - 3.25 );
		CGRect newSelfViewFrame = self.frame;
		newSelfViewFrame.origin.x = rightTop_.x - newSelfViewFrame.size.width;
		newSelfViewFrame.origin.y = rightTop_.y;
		self.frame = newSelfViewFrame;
		self.hidden = NO;
	}
}

- (void)dealloc {
	[label_ release];
    [super dealloc];
}


@end

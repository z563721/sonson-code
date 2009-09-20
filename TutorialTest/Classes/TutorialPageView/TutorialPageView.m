//
//  TutorialPageView.m
//  TutorialTest
//
//  Created by sonson on 09/09/19.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import "TutorialPageView.h"
#import "MessageView.h"

@implementation TutorialPageView

@dynamic page, pageTitle;

#pragma mark -
#pragma mark Class method

+ (int)totalPage {
	return 15;
}

+ (NSString*)titleOfPage:(int)page {
	return @"title";
}

+ (NSString*)messageOfPage:(int)page {
	return @"abcdefghijklm\rnopqrstuvw";
}

+ (UIImage*)imageOfPage:(int)page {
	return [UIImage imageNamed:@"test.png"];
}

#pragma mark -
#pragma mark Accessor

- (NSString*)pageTitle {
	return [[self class] titleOfPage:page];
}

- (void)setPage:(int)newValue {
	if (page != newValue) {
		page = newValue;
		[self reloadContent];
	}
}

#pragma mark -
#pragma mark Instance method

- (void)reloadContent {
	[imageview removeFromSuperview];
	imageview = [[UIImageView alloc] initWithImage:[[self class] imageOfPage:page]];
	[self.view addSubview:[imageview autorelease]];
	
	[messageview removeFromSuperview];
	messageview= [[MessageView alloc] initWithMessage:[[self class] messageOfPage:page]];
	[self.view addSubview:[messageview autorelease]];
	CGRect frame = messageview.frame;
	frame.origin.x = (int)(self.view.frame.size.width - messageview.frame.size.width)/2;
	frame.origin.y = imageview.frame.size.height - messageview.bounds.size.height;
	messageview.frame = frame;
}

#pragma mark -
#pragma mark Override

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if (self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil]) {
        // Custom initialization
		self.view.backgroundColor = [UIColor colorWithRed:143.0f/255.0f green:145.0f/255.0f blue:146.0f/255.0f alpha:255.0f/255.0f];
		[self reloadContent];
    }
    return self;
}

#pragma mark -
#pragma mark dealloc

- (void)dealloc {
    [super dealloc];
}

@end

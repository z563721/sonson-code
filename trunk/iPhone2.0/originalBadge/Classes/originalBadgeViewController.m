// 
// Classes
// originalBadgeViewController.m
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
//  originalBadgeViewController.m
//  originalBadge
//
//  Created by sonson on 08/12/29.
//  Copyright __MyCompanyName__ 2008. All rights reserved.
//

#import "originalBadgeViewController.h"
#import "SNMiniBadgeView.h"

@implementation originalBadgeViewController

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
	UISlider *slider = [[UISlider alloc] initWithFrame:CGRectMake( 0, 0, 200, 20 )];
	[self.view addSubview:slider];
	[slider release];
	slider.minimumValue = 0;
	slider.maximumValue = 100;
	slider.center = CGPointMake( 160, 240 );
	[slider addTarget:self action:@selector(sliderAction:) forControlEvents:UIControlEventValueChanged];
	
	badge_ = [[SNMiniBadgeView alloc] init];
	[self.view addSubview:badge_];
	badge_.rightTop = CGPointMake( 160, 200 );
    [super viewDidLoad];
}

- (void)sliderAction:(id)sender {
	UISlider *slider = (UISlider*)sender;
	slider.value;
	[badge_ set:(int)slider.value];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning]; // Releases the view if it doesn't have a superview
    // Release anything that's not essential, such as cached data
}

- (void)dealloc {
    [super dealloc];
}

@end

//
//  receiverViewController.m
//  receiver
//
//  Created by sonson on 09/04/05.
//  Copyright 2009 sonson. All rights reserved.
//
// The MIT License
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

#import "receiverViewController.h"

@implementation receiverViewController

- (void)setImage:(UIImage*)image {
	[imageView removeFromSuperview];
	imageView = [[UIImageView alloc] initWithImage:image];
	float ratio = 160 / image.size.width;
	imageView.frame = CGRectMake(0, 0, (int)(image.size.width*ratio), (int)(image.size.height*ratio));
	imageView.center = CGPointMake(160, 250);
	[self.view addSubview:imageView];
	[imageView release];
	
	NSString* m = [NSString stringWithFormat:@"%f,%f", image.size.width, image.size.height];
	UITextField *field = [[UITextField alloc] initWithFrame:CGRectMake(0, 0, 200, 200)];
	field.text = m;
	[self.view addSubview:field];
	[field release];
}

- (void)setText:(NSString*)text {
	[textField removeFromSuperview];
	textField = [[UITextField alloc] initWithFrame:CGRectMake(0, 0, 200, 200)];
	textField.text = text;
	[self.view addSubview:textField];
	[textField release];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning]; // Releases the view if it doesn't have a superview
    // Release anything that's not essential, such as cached data
}


- (void)dealloc {
    [super dealloc];
}

@end

//
//  callbackOpenURLViewController.m
//  callbackOpenURL
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

#import "callbackOpenURLViewController.h"
#import "UICOpenURL.h"

@implementation callbackOpenURLViewController

- (IBAction)push:(id)sender {
	NSString* query = [UICOpenURL escapedQueryWithValuesAndNames:@"http://www.yahoo.co.jp", @"url", @"immediately", @"callback", nil];
	UICOpenURL *callbackURL = [UICOpenURL OpenURLWithScheme:@"callbackOpenURL" action:@"dummy" path:nil query:nil callbackURLString:nil];
	UICOpenURL *url = [UICOpenURL OpenURLWithScheme:@"dharma" action:@"post" path:nil query:query callbackURLString:[callbackURL absoluteString]];
	[[UIApplication sharedApplication] openURL:url];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning]; // Releases the view if it doesn't have a superview
    // Release anything that's not essential, such as cached data
}

- (IBAction)takeAndSend:(id)sender {
	UIImagePickerController* imagePickerController = [[UIImagePickerController alloc] init];
	imagePickerController.delegate = self;
	imagePickerController.editing = NO;
	imagePickerController.sourceType = UIImagePickerControllerSourceTypeCamera;
	[self presentModalViewController:imagePickerController animated:YES];
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingImage:(UIImage *)image editingInfo:(NSDictionary *)editingInfo {
	[imageView removeFromSuperview];
	imageView = [[UIImageView alloc] initWithImage:image];
	float ratio = 160 / image.size.width;
	imageView.frame = CGRectMake(0, 0, (int)(image.size.width*ratio), (int)(image.size.height*ratio));
	imageView.center = CGPointMake(160, 250);
	[self.view addSubview:imageView];
	[self sendImage:image];
	[imageView release];
	[picker dismissModalViewControllerAnimated:YES];
	[picker release];
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker {
	[picker dismissModalViewControllerAnimated:YES];
	[picker release];
}

- (void)sendImage:(UIImage*)image {
	NSData* data = UIImagePNGRepresentation(image);
	NSString* path = @"/tmp/tmp.png";
	NSError *error = nil;
	[data writeToURL:[NSURL URLWithString:@"file:///tmp/tmp.png"] options:0 error:&error];
	if (error) {
		NSLog(@"%@", [error description]);
	}
	
	NSString* query = [UICOpenURL escapedQueryWithValuesAndNames:@"image/png", @"mime", nil];
	UICOpenURL *callbackURL = [UICOpenURL OpenURLWithScheme:@"callbackOpenURL" action:@"dummy" path:nil query:nil callbackURLString:nil];
	UICOpenURL *url = [UICOpenURL OpenURLWithScheme:@"receiver" action:@"send" path:@"tmp/tmp.png" query:query callbackURLString:[callbackURL absoluteString]];
	NSLog(@"%@", [url absoluteString]);
	[[UIApplication sharedApplication] openURL:url];
}

- (void)dealloc {
    [super dealloc];
}

@end

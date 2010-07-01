//
//  OverlayViewController.m
//  Overlay
//
// The MIT License
//
// Copyright (c) 2010, sonson
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

#import "OverlayViewController.h"

@implementation OverlayViewController

- (IBAction)open:(id)sender {
	picker = [[UIImagePickerController alloc] init];
	picker.sourceType = UIImagePickerControllerSourceTypeCamera;
	
	UIView *base = [[UIView alloc] initWithFrame:CGRectMake(0, 20, 320, 460)];
	UIImageView *i = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"eva.png"]];
	CGSize imageSize = [i.image size];
	imageSize.height = imageSize.height / imageSize.width * 300;
	imageSize.width = 300;
	[i setFrame:CGRectMake(5, 406-imageSize.height, imageSize.width, imageSize.height)];
	UIToolbar *toolbar = [[UIToolbar alloc] initWithFrame:CGRectMake(0, 406, 320, 54)];
	UIBarButtonItem *item = [[UIBarButtonItem alloc] initWithTitle:@"捕獲" style:UIBarButtonItemStyleBordered target:self action:@selector(get:)];
	NSArray *items = [NSArray arrayWithObject:item];
	[toolbar setItems:items];
	[base addSubview:i];
	[base addSubview:toolbar];
	picker.showsCameraControls = NO;
	picker.cameraOverlayView = base;
	[i release];
	[picker setDelegate:self];
	[self presentModalViewController:picker animated:YES];
	[picker release];
}

- (void)get:(id)sender {
	[picker takePicture];
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info {
	NSLog(@"5");
	UIImage *image = [info objectForKey:UIImagePickerControllerOriginalImage];
	UIImage *stamp = [UIImage imageNamed:@"eva.png"];
	
	CGSize imageSize = image.size;
	UIGraphicsBeginImageContext(imageSize);

	[image drawInRect:CGRectMake(0, 0, imageSize.width, imageSize.height)];
	
	CGSize stampSize = stamp.size;
	stampSize.height = stampSize.height / stampSize.width * imageSize.width;
	stampSize.width = imageSize.width;
	
	[stamp drawInRect:CGRectMake(0, imageSize.height - stampSize.height, stampSize.width, stampSize.height)];
	
	UIImage* output = UIGraphicsGetImageFromCurrentImageContext();
	
	UIGraphicsEndImageContext();
	UIImageWriteToSavedPhotosAlbum(output, self, @selector(image:didFinishSavingWithError:contextInfo:), nil);
	
	indicator = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
	[indicator startAnimating];
	[picker.cameraOverlayView addSubview:indicator];
	CGRect r = indicator.frame;
	r.origin.x = (picker.cameraOverlayView.frame.size.width - r.size.width)/2;
	r.origin.y = (picker.cameraOverlayView.frame.size.height - r.size.height)/2;
	indicator.frame = r;
	[indicator release];
	[[UIApplication sharedApplication] beginIgnoringInteractionEvents];
}

- (void) image: (UIImage *) image didFinishSavingWithError: (NSError *) error contextInfo: (void *) contextInfo {
	NSLog(@"end");
	[indicator removeFromSuperview];
	indicator = nil;
	[[UIApplication sharedApplication] endIgnoringInteractionEvents];
	
	if (error) {
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error"
														message:[error localizedDescription]
													   delegate:nil
											  cancelButtonTitle:nil
											  otherButtonTitles:@"OK", nil];
		[alert show];
		[alert release];
	}
}

/*
// The designated initializer. Override to perform setup that is required before the view is loaded.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/


/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
*/


/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

- (void)didReceiveMemoryWarning {
	// Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}

@end

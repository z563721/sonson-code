// 
// SNHUDActivityView
// SNHUDActivityView.h
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
//#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

#define	DEFAULT_DURATION_TO_SHOW_MARK		0.5

#define DEFAULT_IS_SHOWN_CHECK_MARK			NO

#define	DEFAULT_HUD_HEIGHT					150

#define	DEFAULT_MESSAGE_WIDTH				220
#define	DEFAULT_MESSAGE_HEIGHT				60
#define	DEFAULT_MESSAGE_HORIZONTAL_MARGIN	20

#define	DEFAULT_MARK_TOP_MARGIN				45
#define	DEFAULT_MARGIN_BETWEEN_MARK_MESSAGE	26
#define	DEFAULT_MESSAGE_BOTTOM_MARGIN		24

@interface SNHUDActivityView : UIImageView {
	UILabel					*label_;
	UIActivityIndicatorView *indicator_;
	BOOL					isShownCheckMark_;
	float					durationToShowCheckMark_;
}
@property (nonatomic, assign) BOOL isShownCheckMark;
@property (nonatomic, assign) float durationToShowCheckMark;
- (void) initializeMessageLabelWithString:(NSString*)message;
- (id) initWithString:(NSString*)message;
- (void) showInView:(UIView*) view;
- (void) dismiss;
- (void) makeDisabledInteraction;
- (void) makeEnabledInteraction;
- (void) addCheck;
- (void) dimissAfterShowingCheckMark;
- (BOOL) isShown;
@end

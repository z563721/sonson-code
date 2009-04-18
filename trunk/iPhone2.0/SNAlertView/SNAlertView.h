// 
// SNAlertView
// SNAlertView.h
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
//  SNAlertView.h
//  dharma
//
//  Created by sonson on 09/01/22.
//  Copyright 2009 sonson. All rights reserved.
// MIT License

#import <UIKit/UIKit.h>

@interface SNAlertView : UIAlertView {
	NSMutableArray		*fieldArray_;
	NSMutableDictionary	*fieldTable_;
	BOOL				isLayouted_;
	CGSize				keyboardSize_;
}
- (void)registerForKeyboardNotifications;
- (void)keyboardWillShow:(NSNotification*)aNotification ;
#pragma mark Access to TextFields
- (NSArray*)textFieldTags;
- (NSInteger)textFieldCount;
- (UITextField*)textFieldWithTag:(NSString*)tag ;
- (UITextField*)textFieldAtIndex:(NSInteger)index;
- (BOOL)addTextFieldDefaultValue:(NSString*)value placeholder:(NSString*)placeholder tag:(NSString*)tag;
#pragma mark Layout helper
- (float)heightOfLabelArea;
- (float)heightOfFields;
@end

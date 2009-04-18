// 
// transparent
// MyTransWindow.m
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
/////////////////////////////////////////////////////////////////////////////////
// Transparent OpenGLView
//										 version1.00(20021206)
//                         Produced by sonson@Picture&Software
///////////////////////////////////////////////////////////////////////////////
//
//	     2002 sonson@Picture&Software, All right reserved.
//
///////////////////////////////////////////////////////////////////////////////
// Email:
//	web_sonson@hotmail.com
// HOMEPAGE:sonson@Picture&Software
//	http://www.geocities.jp/yuichi2001/
///////////////////////////////////////////////////////////////////////////////

#import "MyTransWindow.h"

@implementation MyTransWindow

////////////////////////////////////////////////////////////////////////////////////
// intialize Window
- (id) initWithContentRect : (NSRect ) contentRect
                styleMask : (unsigned int) aStyle
                backing : (NSBackingStoreType) bufferingType
                defer : (BOOL ) flag
{
    // alloc window
    NSWindow* win = [ super
                initWithContentRect : contentRect
                styleMask : NSBorderlessWindowMask
                backing : NSBackingStoreBuffered
                defer : NO ];
    // create color
    NSColor *windowColor 
        = [NSColor clearColor];
    // set color
    [ win setBackgroundColor:windowColor];
    // set window position
    [ win center ];
    // set non-Opaque
    [ win setOpaque : NO];
    // set window level
    [ win setLevel : NSStatusWindowLevel ];
    // set window alpha value
    [ win setAlphaValue : 0.5f ];

    return win;
}
@end

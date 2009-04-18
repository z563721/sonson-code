// 
// transparent
// MyMouseClickView.m
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

#import "MyMouseClickView.h"

@implementation MyMouseClickView

- (id)initWithFrame:(NSRect)frameRect
{
	[super initWithFrame:frameRect];
	return self;
}
////////////////////////////////////////////////////////////////////////////////////
// mouse event for dragging window
- (void)mouseDragged:(NSEvent *)theEvent
{    
   NSPoint currentLocation;
   NSPoint newOrigin;
   NSRect  screenFrame = [[NSScreen mainScreen] frame];
   NSRect  windowFrame = [[ self window ] frame];

   //grab the current global mouse location; we could just as easily get the mouse location 
   //in the same way as we do in -mouseDown:
    currentLocation = [[ self window ] convertBaseToScreen:[[ self window ] mouseLocationOutsideOfEventStream]];
    newOrigin.x = currentLocation.x - initialLocation.x;
    newOrigin.y = currentLocation.y - initialLocation.y;
    
    // Don't let window get dragged up under the menu bar
    if( (newOrigin.y+windowFrame.size.height) > (screenFrame.origin.y+screenFrame.size.height) ){
	newOrigin.y=screenFrame.origin.y + (screenFrame.size.height-windowFrame.size.height);
    }
    
    //go ahead and move the window to the new location
    [[ self window ] setFrameOrigin:newOrigin];
}
//We start tracking the a drag operation here when the user first clicks the mouse,
//to establish the initial location.
- (void)mouseDown:(NSEvent *)theEvent
{    
    NSLog(@"window click");
    NSRect  windowFrame = [[ self window ] frame];

    //grab the mouse location in global coordinates
   initialLocation = [[ self window ] convertBaseToScreen:[theEvent locationInWindow]];
   initialLocation.x -= windowFrame.origin.x;
   initialLocation.y -= windowFrame.origin.y;
}
@end

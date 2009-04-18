// 
// transparent
// SonsonOpenGLView.m
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

#import "SonsonOpenGLView.h"
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#import <GLUT/glut.h>

NSTimer *drawTimer = nil;	// timer for animation

@implementation SonsonOpenGLView
//////////////////////////////////////////////////////////////////////////
// override init
-(id)initWithFrame:(NSRect)frameRect{
    // init pixelformat array
    NSOpenGLPixelFormatAttribute attrs[] =
    {
        NSOpenGLPFADoubleBuffer,	// double buffered
        NSOpenGLPFAColorSize, 	24,	// color buffer 24bit
        NSOpenGLPFAAlphaSize, 	8,	// alpha buffer 8bit
        NSOpenGLPFADepthSize, 	16,	// depth buffer 16bit
        NSOpenGLPFAAccelerated,		// hardware acceleration
        nil							// stopper
    };
    // allocate pixelformat
    NSOpenGLPixelFormat* pixFmt 
        = [[[NSOpenGLPixelFormat alloc] initWithAttributes:attrs] autorelease];
    // timer for animation of OpenGL
    drawTimer = [ NSTimer scheduledTimerWithTimeInterval : 0.01f
                      target : self
                    selector : @selector(reDraw)
                    userInfo : nil
                     repeats : YES];
    // time parameter for animation
    t =0.0f;
    // init view
    self = [super initWithFrame:frameRect pixelFormat:pixFmt];
    // set current context of OpenGL
    [ [ self openGLContext ] makeCurrentContext ];
    // set non-opaque OpenGL context
    long opq=0;
    [ [ self openGLContext ] setValues:&opq forParameter:NSOpenGLCPSurfaceOpacity];
    //opq = -1;
    //[ [ self openGLContext ] setValues:&opq forParameter:NSOpenGLCPSurfaceOrder];
    [self setNeedsDisplay:YES];
    return( self );
}
//////////////////////////////////////////////////////////////////////////
// resize
- (void)reshape{
    // get size of view
    NSRect bounds = [self bounds];
    // set OpenGL viewport with size of view
    glViewport(
        (int)bounds.origin.x, (int)bounds.origin.y,
        (int)bounds.size.width, (int)bounds.size.height);
    // set projection of OpenGL
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45, ( float ) bounds.size.width/ ( float ) bounds.size.height, 1.0, 500.0 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    //glDepthFunc(GL_LEQUAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //クライアント領域の初期化
    glClearDepth( 1.0 );
}
//////////////////////////////////////////////////////////////////////////
// draw OpenGL funcion
- (void)reDraw
{
     [ [ self openGLContext ] makeCurrentContext ]; 
    // Set the drawable
    [[self openGLContext] setView:self];
    // clear all pixels
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	// init matrix
	glLoadIdentity();
	// set lookat point
	gluLookAt(
		0,0,5,
		0,0,0,
		0.0, 1.0, 0.0);
	glRotatef(t,0,1,1);
        glutSolidTeapot(1);
    glFinish();
    // swap buffers
    [ [ self openGLContext ] flushBuffer ];
    // time parameter incremented
    [[ self window] setAlphaValue : 0.5*(sin(t/20)+1)];
    t+=2.0f;
}
////////////////////////////////////////////////////////////////////////////////////
// draw function for view

- (void)drawRect:(NSRect)aRect
{
	[self reDraw];
    [super drawRect:aRect];
}
- (BOOL)isOpaque
{
	return NO;   
}
@end
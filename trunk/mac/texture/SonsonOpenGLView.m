// 
// texture
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
// class to create OpenGL texture for Cocoa
//										 version1.00(20021128)
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
#import "NSGLTexture.h"
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>

NSTimer *drawTimer = nil;

@implementation SonsonOpenGLView
//////////////////////////////////////////////////////////////////////////
//オーバーライド
-(id)initWithFrame:(NSRect)frameRect{
    // ピクセルフォーマットを配列に代入する
    NSOpenGLPixelFormatAttribute attrs[] =
    {
        NSOpenGLPFADoubleBuffer,	// ダブルバッファ
        NSOpenGLPFAColorSize, 	24,	// カラーバッファ・24bit
        NSOpenGLPFAAlphaSize, 	8,	// アルファバッファ・8bit
        NSOpenGLPFADepthSize, 	16,	// デプスバッファ・16bit
        NSOpenGLPFAAccelerated,	0,	// ハードウェア・アクセラレーション
    };
    // attrs配列を元にピクセルフォーマットを確保する
    NSOpenGLPixelFormat* pixFmt 
        = [[[NSOpenGLPixelFormat alloc] initWithAttributes:attrs] autorelease];
    // 描画のためのタイマー
    drawTimer = [ NSTimer scheduledTimerWithTimeInterval : 0.01f
                      target : self
                    selector : @selector(reDraw)
                    userInfo : nil
                     repeats : YES];
    // 描画のための媒介変数
    t =0.0f;
    // viewを初期化する
    self = [super initWithFrame:frameRect pixelFormat:pixFmt];
    // カレントコンテキストを設定
    [ [ self openGLContext ] makeCurrentContext ];
    return( self );
}
//////////////////////////////////////////////////////////////////////////
//リサイズ処理
- (void)reshape{
    // viewサイズを取得する．
    NSRect bounds = [self bounds];
    // viewサイズからViewportを設定する．
    glViewport(
        (int)bounds.origin.x, (int)bounds.origin.y,
        (int)bounds.size.width, (int)bounds.size.height);
    // 射影変換の設定
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45, ( float ) bounds.size.width/ ( float ) bounds.size.height, 1.0, 500.0 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.5,0.5,0.5,1);
    
    glAlphaFunc(GL_GREATER, 0.5);
    glEnable(GL_ALPHA_TEST);
    
}
- (void)reDraw
{
     [ [ self openGLContext ] makeCurrentContext ]; 
    // Set the drawable
    [[self openGLContext] setView:self];
    //
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//視点の変換行列の初期化
	glLoadIdentity();
	//視点の決定
	gluLookAt(
		0,0,4,
		0,0,0,
		0.0, 1.0, 0.0);
	glRotatef(t,0,1,0);
	//ポリゴンとテクスチャ
	glPushMatrix();
		glBegin(GL_QUADS);
		//glColor4f(0.0,0.0,0.0,1.0);
		glColor3f(0.0,0.0,0.8);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(1.0, 1.0, 0.0);
		//glColor4f(0.8,0.0,0.0,1.0);
		glColor3f(0.0,0.0,0.8);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(1.0,-1.0, 0.0);
		//glColor4f(0.8,0.0,0.0,0.0);
		glColor3f(0.0,0.0,0.8);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(-1.0,-1.0, 0.0);
		//glColor4f(0.8,0.0,0.0,0.0);
		glColor3f(0.8,0.0,0.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(-1.0, 1.0, 0.0);
		glEnd();
	glPopMatrix();
    glFinish();
    //バッファ入れ替え
    [ [ self openGLContext ] flushBuffer ];
    //時間を進める
    t+=2.0f;
}
////////////////////////////////////////////////////////////////////////////////////
//再描画処理
- (void)drawRect:(NSRect)aRect
{
    [self reDraw];
    [super drawRect:aRect];    
}
////////////////////////////////////////////////////////////////////////////////////
//ボタン用の処理
- (IBAction)pushTIF:(id)sender
{
    NSString*path = [NSString stringWithCString:"texture.tif"];
    NSGLTexture*data;
    data = [NSGLTexture imageRepWithContentsOfBundleFile:path];
    if(data)NSLog(@"alloced");
    glDeleteTextures(1,&tex_number);
    tex_number = [data genGLTexture];
    NSRect bounds = [self bounds];
    [self drawRect:bounds];
}
- (IBAction)pushTIFT:(id)sender
{
    NSString*path = [NSString stringWithCString:"texture_trans.tif"];
    NSGLTexture*data;
    data = [NSGLTexture imageRepWithContentsOfBundleFile:path];
    if(data)NSLog(@"alloced");
    glDeleteTextures(1,&tex_number);
    tex_number = [data genGLTexture];
    NSRect bounds = [self bounds];
    [self drawRect:bounds];
}
- (IBAction)pushGIF:(id)sender
{
    NSString*path = [NSString stringWithCString:"texture_256.gif"];
    NSGLTexture*data;
    data = [NSGLTexture imageRepWithContentsOfBundleFile:path];
    if(data)NSLog(@"alloced");
    tex_number = [data genGLTexture];
    NSRect bounds = [self bounds];
    [self drawRect:bounds];
}
- (IBAction)pushGIFT:(id)sender
{
    NSString*path = [NSString stringWithCString:"texture_trans.gif"];
    NSGLTexture*data;
    data = [NSGLTexture imageRepWithContentsOfBundleFile:path];
    if(data)NSLog(@"alloced");
    tex_number = [data genGLTexture];
    NSRect bounds = [self bounds];
    [self drawRect:bounds];
}
- (IBAction)pushBMP:(id)sender
{
    NSString*path = [NSString stringWithCString:"texture.bmp"];
    NSGLTexture*data;
    data = [NSGLTexture imageRepWithContentsOfBundleFile:path];
    if(data)NSLog(@"alloced");
    glDeleteTextures(1,&tex_number);
    tex_number = [data genGLTexture];
    NSRect bounds = [self bounds];
    [self drawRect:bounds];
}
- (IBAction)pushPNG:(id)sender
{
    NSString*path = [NSString stringWithCString:"texture.png"];
    NSGLTexture*data;
    data = [NSGLTexture imageRepWithContentsOfBundleFile:path];
    if(data)NSLog(@"alloced");
    glDeleteTextures(1,&tex_number);
    tex_number = [data genGLTexture];
    NSRect bounds = [self bounds];
    [self drawRect:bounds];
}
- (IBAction)pushJPG:(id)sender
{
    NSString*path = [NSString stringWithCString:"texture.jpg"];
    NSGLTexture*data;
    data = [NSGLTexture imageRepWithContentsOfBundleFile:path];
    glDeleteTextures(1,&tex_number);
    tex_number = [data genGLTexture];
    NSRect bounds = [self bounds];
    [self drawRect:bounds];
}
- (IBAction)pushOther:(id)sender
{
    NSArray		*fileTypes	= [ NSArray arrayWithObjects : @"jpg", @"gif", @"bmp", @"png", @"tif" ];
    NSOpenPanel	*panel		= [ NSOpenPanel openPanel ];
    int			panelResult;
        
    // Open Panel
    panelResult = [ panel runModalForDirectory : NSHomeDirectory() 
                                     file : @"~/" 
                                    types : fileTypes ];
    // Open File
    if(panelResult == NSOKButton){
        NSGLTexture*data;
        data = [NSGLTexture imageRepWithContentsOfFile:[panel filename]];
        glDeleteTextures(1,&tex_number);
        tex_number = [data genGLTexture];
    }
    NSRect bounds = [self bounds];
    [self drawRect:bounds];
}
@end

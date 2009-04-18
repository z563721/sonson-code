// 
// mac_gl_mdi
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
//#import "SonsonOpenGLView.h"
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>

@implementation SonsonOpenGLView
//////////////////////////////////////////////////////////////////////////
//オーバーライド
-(id)initWithFrame:(NSRect)frameRect{
    // ピクセルフォーマットを配列に代入する
    NSOpenGLPixelFormatAttribute attrs[] =
    {
        NSOpenGLPFADoubleBuffer,	// ダブルバッファ
        NSOpenGLPFAColorSize, 24,	// カラーバッファ・24bit
        NSOpenGLPFAAlphaSize, 8,	// アルファバッファ・8bit
        NSOpenGLPFADepthSize, 16,	// デプスバッファ・16bit
	NSOpenGLPFAAccelerated,		// ハードウェアアクセラレーション
	0
    };
    // attrs配列を元にピクセルフォーマットを確保する
    NSOpenGLPixelFormat* pixFmt = [[[NSOpenGLPixelFormat alloc] 							initWithAttributes:attrs] autorelease];
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
    glClearColor(1,1,1,1);
}
////////////////////////////////////////////////////////////////////////////////////
//再描画処理
- (void)drawRect:(NSRect)aRect
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFinish();
    //バッファ入れ替え
    [ [ self openGLContext ] flushBuffer ];
    [super drawRect:aRect];    
}
////////////////////////////////////////////////////////////////////////////////////
//マウスダウン
- (void)mouseDown:(NSEvent*)theEvent{
    // viewサイズを取得する．
    NSRect bounds = [self bounds];
    glClearColor(0,0,0,1);
    [self drawRect:bounds];
}
////////////////////////////////////////////////////////////////////////////////////
//マウスアップ
- (void)mouseUp:(NSEvent*)theEvent{
    // viewサイズを取得する．
    NSRect bounds = [self bounds];
    glClearColor(1,1,1,1);
    [self drawRect:bounds];
}
////////////////////////////////////////////////////////////////////////////////////
//Viewがフォーカスされたときの処理
//NSWindowのデリゲートに設定されたMyDocumentが処理し，MyDocumentによって呼び出される
- (void)DidViewFocused
{
    [ [ self openGLContext ] makeCurrentContext ]; 
    // Set the drawable
    [[self openGLContext] setView:self];
}
@end

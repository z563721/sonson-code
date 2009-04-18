// 
// mac_offscreen_rendering
// NSGLOffscreen.m
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
//#import "NSGLOffscreen.h"

#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#import <GLUT/glut.h>

#define C_BUF 24		//カラー・バッファサイズ
#define A_BUF 8			//アルファ・バッファサイズ
#define D_BUF 16		//デプス・バッファサイズ

void orderPixels(unsigned char*pixel_data,int width, int height)
{
    int i,j;
    unsigned char tempArray[4];
    // order, to RGBA from ARGB
#ifdef _COCOA_DEBUG
    FILE *fp;
    fp = fopen("test.txt","w");
    fprintf(fp,"Red Green Blue Alpha\n");
#endif
    for(i=0;i<width;i++){
        for(j=0;j<height;j++){
#ifdef _COCOA_DEBUG
            fprintf(fp,"(%3d ",*(pixel_data+4*i*height+4*j+1));
            fprintf(fp, "%3d ",*(pixel_data+4*i*height+4*j+2));
            fprintf(fp, "%3d",*(pixel_data+4*i*height+4*j+3));
            fprintf(fp, "%3d)\n",*(pixel_data+4*i*height+4*j));
#endif
            // reorder pixels
            tempArray[0] = *(pixel_data+4*i*height+4*j);
            tempArray[1] = *(pixel_data+4*i*height+4*j+1);
            tempArray[2] = *(pixel_data+4*i*height+4*j+2);
            tempArray[3] = *(pixel_data+4*i*height+4*j+3);
            
            *(pixel_data+4*i*height+4*j) = tempArray[1];
            *(pixel_data+4*i*height+4*j+1)=tempArray[2];
            *(pixel_data+4*i*height+4*j+2)=tempArray[3];
            *(pixel_data+4*i*height+4*j+3)=tempArray[0];
        }
    }
#ifdef _COCOA_DEBUG
    fclose(fp);
#endif
} 

@implementation NSGLOffscreen

-(id)init
{
    // initialize pixelformat array
    NSOpenGLPixelFormatAttribute attrs[] =
    {
        NSOpenGLPFAColorSize, C_BUF,	// color buffer 24bit
        NSOpenGLPFAAlphaSize, A_BUF,	// alpha buffer 8bit
        NSOpenGLPFADepthSize, D_BUF,	// depth buffer 16bit
        NSOpenGLPFAOffScreen, YES,		// support offscreen
        nil
    };
    // allocate and intialize pixel format
    NSOpenGLPixelFormat* pixFmt = [[[NSOpenGLPixelFormat alloc] 							initWithAttributes:attrs] autorelease];
    // initiallize context
    glContext = [[NSOpenGLContext alloc] initWithFormat:pixFmt shareContext:nil];

    return self;
}
-(void)initGLwithRect:(NSRect)aRect
{
    // viewサイズからViewportを設定する．
    glViewport(
        (int)aRect.origin.x, (int)aRect.origin.y,
        (int)aRect.size.width, (int)aRect.size.height);
    // 射影変換の設定
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45, ( float ) aRect.size.width/ ( float ) aRect.size.height, 1.0, 500.0 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(1,1,1,1);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_AUTO_NORMAL );
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
    glEnable(GL_DEPTH_TEST);
}
-(void)drawGL
{
    	//ウィンドウを塗りつぶす
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//視点の変換行列の初期化
	glLoadIdentity();
	//視点の決定
	gluLookAt(
		2,2,2,
		0,0,0,
		0.0, 1.0, 0.0);

	glColor3f(1,0.5,0.5);
	glutSolidTeapot(1);
	glFinish();
}
- (NSImage*)drawSetRect:(NSRect)aRect;
{
    //screen size
    int buffWidth = aRect.size.width;
    int buffHeight = aRect.size.height;
    //offscreen buffer size
    int bufferSize = 4*sizeof(unsigned char)*buffWidth*buffHeight;
    //
    unsigned char *pixel_data = (unsigned char*)malloc(bufferSize);
    //initialize offscreen
    [glContext setOffScreen:(void *)pixel_data
            width:buffWidth
            height:buffHeight 
            rowbytes:(buffWidth)*(C_BUF+A_BUF)/8];
    [ glContext makeCurrentContext ];
    //init OpenGL
    [self initGLwithRect:aRect];
    //draw OpenGL
    [self drawGL];

    //reorder pixels
    orderPixels(pixel_data,buffWidth,buffHeight);

    //offscreen buffer to bitmap image
    NSBitmapImageRep* bmpImageRep = [[[NSBitmapImageRep alloc] 
        initWithBitmapDataPlanes:&pixel_data
        pixelsWide:buffWidth
	    pixelsHigh:buffHeight
	    bitsPerSample:8
	    samplesPerPixel:4
	    hasAlpha:YES
	    isPlanar:NO
	    colorSpaceName:NSDeviceRGBColorSpace
	    bytesPerRow:(buffWidth)*4
        bitsPerPixel:32]
        autorelease];
    // allocation of NSImage
    NSImage  *img = [[ [ NSImage alloc ] initWithSize : [bmpImageRep size]]autorelease];
    
/* to write TIFF file
    NSData* data;
    NSMutableString* path;
    
    path = [NSMutableString stringWithString:NSHomeDirectory()];
    [path appendString:@"/test.tiff"];
    
    data = [img TIFFRepresentation];
    [data writeToFile:path atomically:YES];
*/
    NSRect rec = {{0, 0}, {buffWidth, buffHeight}};	
    [ img drawRepresentation : bmpImageRep inRect : rec ];
    //スクリーンバッファの解放
    free(pixel_data);
    return img;
}
@end

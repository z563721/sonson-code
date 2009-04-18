// 
// texture
// NSGLTexture.m
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

#import "NSGLTexture.h"

// max texture size
#define TEX_SIZE 512

///////////////////////////////////////////////////////////////////////////////
// check image size for OpenGL
int CheckSize(unsigned int pict_size){
	unsigned int i=2;
	unsigned int max_texture = TEX_SIZE*TEX_SIZE;
	//サイズチェック
	for(i=2;i<=max_texture;i*=2){
		if( i == pict_size){
			return 1;
		}
	}
	return 0;
};
///////////////////////////////////////////////////////////////////////////////
// class method create instance from bundled filename 
@implementation NSGLTexture
+ (id)imageRepWithContentsOfBundleFile:(NSString *)name
{
#ifdef _COCOA_DEBUG
    NSLog(@"Open Bundled File");
#endif
    NSBundle* mainBundle;
    NSString* fileName;
    id returnSelf;
    // get bundle object
    mainBundle = [NSBundle mainBundle];
    // Get images from bundle resource
    fileName = [mainBundle pathForImageResource:name];
#ifdef _COCOA_DEBUG
    NSLog(@"File's Path");
    NSLog(@"%@",fileName);
#endif
    returnSelf = [super imageRepWithContentsOfFile:fileName];
    // return instance pointor
    return returnSelf;
}
///////////////////////////////////////////////////////////////////////////////
// create OpenGL Texture from image data in instance
- (unsigned int)genGLTexture
{
    unsigned int tex_number;			// valiable to return
    unsigned char *pixel_data=NULL;		// pointor to save image data
    GLenum format_type;					// texture data type for OpenGL
    int i,j;
    // gets height, width and bit per pixel.
    int Height = [self pixelsHigh];
    int Width = [self pixelsWide];
    int bits = [self bitsPerPixel];
    unsigned char* file_data = [self bitmapData];
                                        // pointor of file's image data 
    // Disp Debug Message
#ifdef _COCOA_DEBUG
    NSLog(@"Generate OpenGL Texture",[self pixelsHigh]);
    NSLog(@"Height %d",[self pixelsHigh]);
    NSLog(@"Width  %d",[self pixelsWide]);
    NSLog(@"Bits   %d",[self bitsPerPixel]);
    NSLog(@"Planes %d",[self numberOfPlanes]);
#endif

    // check image's plane
    if([self numberOfPlanes]>1){
#ifdef _COCOA_DEBUG
    NSLog(@"Image has mutilple layers.");
#endif
        return NULL;
    }

    // check image size for OpenGL Texture
    if(!CheckSize(Height*Width)){
#ifdef _COCOA_DEBUG
    NSLog(@"Image size is wrong");
#endif
        return NULL;
    }
    
    // process for every bit pattern.
    switch(bits){
        case 8:
            // 8bit color
            format_type = GL_RGB;
            pixel_data = (unsigned char*)malloc(sizeof(unsigned char)*Height*Width*3);
            for(j=0;j<Height;j++){
                for(i=Width-1;i>=0;i--){
                    *(pixel_data+3*i+3*j*Width)   = ((*file_data));
                    *(pixel_data+3*i+3*j*Width+1) = ((*file_data));
                    *(pixel_data+3*i+3*j*Width+2) = ((*file_data));
                    file_data++;
                }
            }
            break;
        case 16:
            // 8bit color and 8bit alhpa
            format_type = GL_RGBA;
            pixel_data = (unsigned char*)malloc(sizeof(unsigned char)*Height*Width*4);
            for(j=0;j<Width;j++){
                for(i=Width-1;i>=0;i--){
                    *(pixel_data+4*i+4*j*Width)   = ((*file_data));
                    *(pixel_data+4*i+4*j*Width+1) = ((*file_data));
                    *(pixel_data+4*i+4*j*Width+2) = ((*file_data));
                    file_data++;
                    *(pixel_data+4*i+4*j*Width+3) = ((*file_data));
                    file_data++;
                }
            }
            break;
        case 24:
            //24bit color
            format_type = GL_RGB;
            pixel_data = (unsigned char*)malloc(sizeof(unsigned char)*Height*Width*3);
            for(j=0;j<Height;j++){
                for(i=Width-1;i>=0;i--){
                    *(pixel_data+3*i+3*j*Width)   = ((*file_data));
                    file_data++;
                    *(pixel_data+3*i+3*j*Width+1) = ((*file_data));
                    file_data++;
                    *(pixel_data+3*i+3*j*Width+2) = ((*file_data));
                    file_data++;
                }
            }
            break;
        case 32:
            //24bit color and 8bit alpha
            format_type = GL_RGBA;
            pixel_data = (unsigned char*)malloc(sizeof(unsigned char)*Height*Width*4);
            for(j=0;j<Height;j++){
                for(i=Width-1;i>=0;i--){
                    *(pixel_data+4*i+4*j*Width)   = ((*file_data));
                    file_data++;
                    *(pixel_data+4*i+4*j*Width+1) = ((*file_data));
                    file_data++;
                    *(pixel_data+4*i+4*j*Width+2) = ((*file_data));
                    file_data++;
                    *(pixel_data+4*i+4*j*Width+3) = ((*file_data));
                    file_data++;
                }
            }
            break;
        default:
            return NULL;
    }
    // create texture
    glGenTextures(1, (GLuint*)&tex_number);
    glBindTexture(GL_TEXTURE_2D, tex_number);
    glTexImage2D(GL_TEXTURE_2D, 0, format_type, Width, 
        Height, 0, format_type, GL_UNSIGNED_BYTE, pixel_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D);
    // release memory
    if(pixel_data!=NULL)free(pixel_data);
    // return texture number for OpenGL
    return tex_number;
}
@end

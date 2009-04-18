// 
// texture
// NSGLTexture.h
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
////////////////////////////////////////////////////////////////
// class to create OpenGL texture for Cocoa
//										 version1.00(20021128)
//                         Produced by sonson@Picture&Software
//////////////////////////////////////////////////////////////
//
//	     2002 sonson@Picture&Software, All right reserved.
//
//////////////////////////////////////////////////////////////
// Email:
//	web_sonson@hotmail.com
// HOMEPAGE:sonson@Picture&Software
//	http://www.geocities.jp/yuichi2001/
//////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <OpenGL/gl.h>

@interface NSGLTexture : NSBitmapImageRep {
}
// create instance from bundled filename
+ (id)imageRepWithContentsOfBundleFile:(NSString *)name;
// create OpenGL texture from image data
- (unsigned int)genGLTexture;					
@end

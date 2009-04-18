// 
// bitmapSrc
// main.cpp
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
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Bitmap.h"

int main (int argc, char * const argv[]) {
	int x,y;
	int width = 131;
	int height= 121;
	
	// メモリ確保
	unsigned char *pixel = (unsigned char*)malloc(sizeof(unsigned char)*width*height*3);
	
	for( x=0;x<width;x++){
		for( y=0;y<height;y++){
			int pix1=0,pix2=0;
			if(x<width/2)
				pix1 = 255;
			if(y<height/2)
				pix2 = 255;
			*(pixel+3*(x+y*width)  )=pix1;
			*(pixel+3*(x+y*width)+1)=pix2;
			*(pixel+3*(x+y*width)+2)=0;
		}
	}
	
	WriteBitmap("test01.bmp",pixel, width, height);
	free(pixel);
	
	ReadBitmap("test01.bmp",&pixel,&width,&height);
	WriteBitmap("test02.bmp",pixel, width, height);
	free(pixel);
}

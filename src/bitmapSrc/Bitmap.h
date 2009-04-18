// 
// bitmapSrc
// Bitmap.h
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
//
// Bitmap Utility for 24bit Bitmap File
//
// sonson@Picture&Software ver 0.00, sonson@P&S all rights reserved.
//
// version 0.00 2006/04/24
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define __ENDIAN		// you have to comment out under the little endian.

//BitmapHeader
typedef struct _BitmapHeader{
	char	m_cDistinct1;
	char	m_cDistinct2;
	int		m_nFilesize;
	short	m_sReserve1;
	short	m_sReserve2;
	int		m_nOffset;
}BitmapHeader;

//BitmapInfoHeader
typedef struct _BitmapInfoHeader{
	int		m_nHeaderSize;
	int		m_nWidth;
	int		m_nHeight;
	short	m_sPlane;
	short	m_sBitsCount;
	int		m_nCompression;
	int		m_nCompressedImgSize;
	int		m_nXResolution;
	int		m_nYResolution;
	int		m_nPalletCount;
	int		m_ImportabtnPalletNum;
}BitmapInfoHeader;

// functions
int WriteBitmap(char*fileName, unsigned char *pixel,int width, int height);

// warnings
// you have to dealloc memory which is made by below function.
int ReadBitmap(const char*pFilename, unsigned char **pPixel, int *nWidth, int *nHeight);
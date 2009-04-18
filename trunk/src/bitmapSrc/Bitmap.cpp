// 
// bitmapSrc
// Bitmap.cpp
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

#include "Bitmap.h"

#ifdef __ENDIAN

unsigned short SwapShortByteOrder(unsigned short n){
	return (n << 8) | (n >> 8);
}

unsigned int SwapIntByteOrder(unsigned int n){
	return SwapShortByteOrder(n >> 16) | (SwapShortByteOrder(n) << 16);
}

void SwapByteOrderHeaders(BitmapHeader *header,BitmapInfoHeader *info){
	header->m_nFilesize = SwapIntByteOrder(header->m_nFilesize);
	header->m_sReserve1 = SwapShortByteOrder(header->m_sReserve1);
	header->m_sReserve2 = SwapShortByteOrder(header->m_sReserve2);
	header->m_nOffset = SwapIntByteOrder(header->m_nOffset);
	info->m_nHeaderSize = SwapIntByteOrder(info->m_nHeaderSize);
	info->m_nWidth = SwapIntByteOrder(info->m_nWidth);
	info->m_nHeight = SwapIntByteOrder(info->m_nHeight);
	info->m_sPlane = SwapShortByteOrder(info->m_sPlane);
	info->m_sBitsCount = SwapShortByteOrder(info->m_sBitsCount);
	info->m_nCompression = SwapIntByteOrder(info->m_nCompression);
	info->m_nCompressedImgSize = SwapIntByteOrder(info->m_nCompressedImgSize);
	info->m_nXResolution = SwapIntByteOrder(info->m_nXResolution);
	info->m_nYResolution = SwapIntByteOrder(info->m_nYResolution);
	info->m_nPalletCount = SwapIntByteOrder(info->m_nPalletCount);
	info->m_ImportabtnPalletNum = SwapIntByteOrder(info->m_ImportabtnPalletNum);
};
#endif

///////////////////////////////////////////////////////////////////////////////
// initialize bitmap headers
void InitHeaders(BitmapHeader *header,BitmapInfoHeader *info){
	header->m_cDistinct1 = 'B';
	header->m_cDistinct2 = 'M';
	header->m_nFilesize = 0;
	header->m_sReserve1 = 0;
	header->m_sReserve2 = 0;
	header->m_nOffset = 54;

	info->m_nHeaderSize = 40;
	info->m_nWidth = 0;
	info->m_nHeight = 0;
	info->m_sPlane = 1;
	info->m_sBitsCount = 24;
	info->m_nCompression = 0;
	info->m_nCompressedImgSize = 0;
	info->m_nXResolution = 0;
	info->m_nYResolution = 0;
	info->m_nPalletCount = 0;
	info->m_ImportabtnPalletNum = 0;
};

///////////////////////////////////////////////////////////////////////////////
// write bitmap header to File
void WriteHeader(BitmapHeader *header,FILE *fp){
	fwrite(&(header->m_cDistinct1), sizeof(char),1,fp);
	fwrite(&(header->m_cDistinct2), sizeof(char),1,fp);
	fwrite(&(header->m_nFilesize), sizeof(int),1,fp);
	fwrite(&(header->m_sReserve1), sizeof(short),1,fp);
	fwrite(&(header->m_sReserve2), sizeof(short),1,fp);
	fwrite(&(header->m_nOffset), sizeof(int),1,fp);
}

///////////////////////////////////////////////////////////////////////////////
// write bitmap information header to File
void WriteInfoHeader(BitmapInfoHeader *info,FILE *fp){
	fwrite(&(info->m_nHeaderSize), sizeof(int),1,fp);
	fwrite(&(info->m_nWidth), sizeof(int),1,fp);
	fwrite(&(info->m_nHeight), sizeof(int),1,fp);
	fwrite(&(info->m_sPlane), sizeof(short),1,fp);
	fwrite(&(info->m_sBitsCount), sizeof(short),1,fp);
	fwrite(&(info->m_nCompression), sizeof(int),1,fp);
	fwrite(&(info->m_nCompressedImgSize), sizeof(int),1,fp);
	fwrite(&(info->m_nXResolution), sizeof(int),1,fp);
	fwrite(&(info->m_nYResolution), sizeof(int),1,fp);
	fwrite(&(info->m_nPalletCount), sizeof(int),1,fp);
	fwrite(&(info->m_ImportabtnPalletNum), sizeof(int),1,fp);
}

///////////////////////////////////////////////////////////////////////////////
// read bitmap header to File
int ReadHeader(BitmapHeader *header,FILE *fp){
	if( fread(&(header->m_cDistinct1), sizeof(char),1,fp)<1 )return 0;
	if( fread(&(header->m_cDistinct2), sizeof(char),1,fp)<1 )return 0;
	if( fread(&(header->m_nFilesize), sizeof(int),1,fp)<1   )return 0;
	if( fread(&(header->m_sReserve1), sizeof(short),1,fp)<1 )return 0;
	if( fread(&(header->m_sReserve2), sizeof(short),1,fp)<1 )return 0;
	if( fread(&(header->m_nOffset), sizeof(int),1,fp)<1     )return 0;
	return 1;
}

///////////////////////////////////////////////////////////////////////////////
// read bitmap information header to File
int ReadInfoHeader(BitmapInfoHeader *info,FILE *fp){
	if( fread(&(info->m_nHeaderSize), sizeof(int),1,fp)<1 )return 0;
	if( fread(&(info->m_nWidth), sizeof(int),1,fp)<1 )return 0;
	if( fread(&(info->m_nHeight), sizeof(int),1,fp)<1 )return 0;
	if( fread(&(info->m_sPlane), sizeof(short),1,fp)<1 )return 0;
	if( fread(&(info->m_sBitsCount), sizeof(short),1,fp)<1 )return 0;
	if( fread(&(info->m_nCompression), sizeof(int),1,fp)<1 )return 0;
	if( fread(&(info->m_nCompressedImgSize), sizeof(int),1,fp)<1 )return 0;
	if( fread(&(info->m_nXResolution), sizeof(int),1,fp)<1 )return 0;
	if( fread(&(info->m_nYResolution), sizeof(int),1,fp)<1 )return 0;
	if( fread(&(info->m_nPalletCount), sizeof(int),1,fp)<1 )return 0;
	if( fread(&(info->m_ImportabtnPalletNum), sizeof(int),1,fp)<1 )return 0;
	return 1;
}

///////////////////////////////////////////////////////////////////////////////
// header check
int CheckHeaders(BitmapHeader *header,BitmapInfoHeader *info){
	// header's character
	if( header->m_cDistinct1!='B' || header->m_cDistinct2!='M' )return 0;
	// layer's mount is 1
	if( info->m_sPlane !=1 )return 0;
	// check if compressed
	if( info->m_nCompression !=0 ) return 0;
	// check bit count
	if( info->m_sBitsCount !=24 )return 0;
	return 1;
}

///////////////////////////////////////////////////////////////////////////////
// output bitmap
int WriteBitmap(char*pFileName, unsigned char *pPixel,int nWidth, int nHeight){
	FILE				*fp;
	BitmapHeader		header;
	BitmapInfoHeader	info;
	int					x,y;
	unsigned char		dummy=0;
	int					writeWidth=0;

	// open file
	if(!( fp = fopen(pFileName, "wb") ))
		return 0;

	// initialize headers
	InitHeaders(&header, &info);
	
	// image size
	info.m_nWidth = nWidth;
	info.m_nHeight = nHeight;
	
	// calculate alignment size
	if( nWidth*3%4 == 0)
		writeWidth = nWidth*3;
	else
		writeWidth = nWidth*3 + 4 - (nWidth*3)%4;
	
	// set file size
	header.m_nFilesize =
		writeWidth*nHeight		// bitmap size
		+ 14					// header size
		+ 40;					// information header size

#ifdef __ENDIAN		// convert endian
	SwapByteOrderHeaders(&header, &info);
#endif

	// write headers
	WriteHeader(&header,fp);
	WriteInfoHeader(&info,fp);

	// write pixels
	for( y=nHeight-1 ; y>=0 ; y--){
		// sort RGB -> BGR
		for( x=0 ; x < nWidth ; x++ ){
			fwrite((pPixel+3*(x+nWidth*y)+2),sizeof(unsigned char),1,fp);
			fwrite((pPixel+3*(x+nWidth*y)+1),sizeof(unsigned char),1,fp);
			fwrite((pPixel+3*(x+nWidth*y)  ),sizeof(unsigned char),1,fp);
		}
		// fill in margin memory with zero
		if( nWidth*3%4 != 0)
			for( int j=0;j<4-(nWidth*3)%4;j++)
				fwrite(&dummy,sizeof(unsigned char),1,fp);
	}
	fclose(fp);
	return 1;
}

///////////////////////////////////////////////////////////////////////////////
// read bitmap
int ReadBitmap(const char*pFilename, unsigned char **pPixel, int *nWidth, int *nHeight){
	int					x,y;
	FILE				*fp;
	unsigned char*		bitdata; 
	BitmapHeader		header;
	BitmapInfoHeader	info;
	unsigned char		red,green,blue,dummy;
	
	if( !( fp = fopen(pFilename, "rb") ))
		return 0;
		
	if( !ReadHeader(&header,fp) ){
		fclose(fp);
		return 0;
	}
	
	if( !ReadInfoHeader(&info,fp) ){
		fclose(fp);
		return 0;
	}
	
#ifdef __ENDIAN		// convert endian
	SwapByteOrderHeaders(&header, &info);
#endif

	// check header
	if( !CheckHeaders(&header,&info) ){
		fclose(fp);
		return 0;
	}

	// calculate alignment size
	int dataWidth = (header.m_nFilesize - header.m_nOffset)/info.m_nHeight;
	int writeWidth = dataWidth - 3*info.m_nWidth;

	// read pixels
	bitdata = (unsigned char*)malloc(3*info.m_nWidth*info.m_nHeight*sizeof(unsigned char));
	for(y=info.m_nHeight-1;y>=0;y--){
		for(x=0;x<info.m_nWidth;x++){
			fread( &blue, sizeof(unsigned char),1,fp);
			fread( &green, sizeof(unsigned char),1,fp);
			fread( &red, sizeof(unsigned char),1,fp);
			// BGR->RGB
			*(bitdata+3*(x+y*info.m_nWidth)  )  = red;
			*(bitdata+3*(x+y*info.m_nWidth)+1)= green; 
			*(bitdata+3*(x+y*info.m_nWidth)+2)= blue;
		}
		for(x=0;x<writeWidth;x++){
			fread( &dummy, sizeof(unsigned char),1,fp);
		}
	}
	
	// return bitmap data
	*nWidth = info.m_nWidth;
	*nHeight= info.m_nHeight;
	*pPixel = bitdata;

	// file close
	fclose(fp);
	return 1;
}
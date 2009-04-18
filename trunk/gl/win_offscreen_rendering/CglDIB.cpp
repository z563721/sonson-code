// 
// win_offscreen_rendering
// CglDIB.cpp
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
//OpenGL用DIBクラス実装

#include "CglDIB.h"

///////////////////////////////////////////////////////////////////////////////
//デストラクタ
CglDIB::~CglDIB(){
	HGLRC hRC;
	//レンダリングコンテキストの開放
	hRC = wglGetCurrentContext();
	//カレントコンテキストを解放
	wglMakeCurrent(NULL, NULL);
	if(hRC){
		//解放
		wglDeleteContext(hRC);
	}
	//以前のビットマップとむすびつける
	SelectObject(hDC, hBitmapOld);
	//ビットマップオブジェクトを削除
	DeleteObject(hBitmap);
	//DCを開放
	DeleteDC(hDC);
	//ビットマップヘッダのメモリ開放
	delete BitmapInfo;
};
///////////////////////////////////////////////////////////////////////////////
//描画
BOOL CglDIB::Draw(HDC destDC,			//コピー先のデバイスコンテキスト
				  int destWidth,		//コピー先領域の範囲
				  int destHeight
				  ){
	//転送モード設定
	SetStretchBltMode(destDC, COLORONCOLOR);
	//転送（コピー）
	StretchDIBits(
		destDC,
		0,0,			//コピー先の座標
		destWidth,destHeight,
		0,0,			//ソースの座標
		width, height,
		data,
		(BITMAPINFO*)BitmapInfo,
		DIB_RGB_COLORS,
		SRCCOPY
	);
  return TRUE;
};
///////////////////////////////////////////////////////////////////////////////
//ビットマップメモリの作成
BOOL CglDIB::CreateGLDIB(int inputWidth,		//メモリのサイズ
						 int inputHeight,
						 int inputColor,		//メモリの色数
						 int inputDepth			//メモリのデプスバッファ
						 ){
	HGLRC hRC;
	width = inputWidth;
	height = inputHeight;
	
	//ビットマップ情報
	BitmapInfo = new BITMAPINFOHEADER;
	int iSize = sizeof(BITMAPINFOHEADER) ;
	memset(BitmapInfo, 0, iSize);
	//
	BitmapInfo->biSize = iSize;
	BitmapInfo->biWidth = width;
	BitmapInfo->biHeight = height;
	BitmapInfo->biPlanes = 1;
	BitmapInfo->biBitCount = inputColor;
	BitmapInfo->biCompression = BI_RGB;
	//互換デバイスコンテキストの作成
	hDC = CreateCompatibleDC(NULL);
	//ビットマップメモリ作成
	hBitmap = CreateDIBSection(hDC,
		(BITMAPINFO*)BitmapInfo,
		DIB_RGB_COLORS,
		&data,
		NULL,
		0
		);
    //以前のビットマップメモリ情報を退避させる
	if(hBitmap){
		hBitmapOld = (HBITMAP)SelectObject(hDC,hBitmap);
	}
	//ピクセルフォーマット設定
	int pixelformat;
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),		//この構造体のサイズ
		1,									//OpenGLバージョン
		PFD_DRAW_TO_BITMAP |                //ビットマップ設定
		PFD_SUPPORT_OPENGL |                    
		PFD_SUPPORT_GDI,
		PFD_TYPE_RGBA,						//RGBAカラー
		inputColor,							//色数
		0, 0,								//RGBAのビットとシフト設定		
		0, 0,								//G
		0, 0,								//B
		0, 0,								//A
		0,									//アキュムレーションバッファ
		0, 0, 0, 0, 						//RGBAアキュムレーションバッファ
		inputDepth,									//Zバッファ	
		0,									//ステンシルバッファ
		0,									//使用しない
		PFD_MAIN_PLANE,						//レイヤータイプ
		0,									//予約
		0, 0, 0								//レイヤーマスクの設定・未使用
    };
    //ピクセルフォーマットの選定
    if((pixelformat = ChoosePixelFormat(hDC, &pfd))==0){
		return FALSE;
	}
    //ピクセルフォーマットの入力
    if(SetPixelFormat(hDC, pixelformat, &pfd)==FALSE){
		return FALSE;
	}
	//レンダリングコンテキストの作成
	if((hRC = wglCreateContext(hDC))==NULL){
		return FALSE;
	}
	wglMakeCurrent(hDC, hRC);
	return TRUE;
};
///////////////////////////////////////////////////////////////////////////////
HDC	CglDIB::GetDC(void){
	//ビットマップメモリクラスのコンテキストを返す
	return hDC;
}
///////////////////////////////////////////////////////////////////////////////
HBITMAP CglDIB::GetBitmap(void){
	//ビットマップメモリクラスのビットマップハンドルを返す
	return hBitmap;
}
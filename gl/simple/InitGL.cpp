// 
// simple
// InitGL.cpp
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
//////////////////////////////////////////////////////////////////////
//OpenGLの初期化、リサイズに関する関数 InitGL.cpp

#include "InitGL.h"

//OpenGLレンダリングコンテキストの作成
//ピクセルフォーマットの設定
HGLRC Init_Pixel(HWND hWnd)
{
	HGLRC hRC;
	HDC hDC;
	int pixelformat;

    static PIXELFORMATDESCRIPTOR pfd = {
	sizeof(PIXELFORMATDESCRIPTOR),		//この構造体のサイズ
	1,									//OpenGLバージョン
	PFD_DRAW_TO_WINDOW |				//Windowスタイル
		PFD_SUPPORT_OPENGL |			//OpenGL
		PFD_DOUBLEBUFFER,				//ダブルバッファ使用可能
	PFD_TYPE_RGBA,						//RGBAカラー
	24,									//色数
	0, 0,								//RGBAのビットとシフト設定		
	0, 0,								//G
	0, 0,								//B
	0, 0,								//A
	0,									//アキュムレーションバッファ
	0, 0, 0, 0, 						//RGBAアキュムレーションバッファ
	16,									//Zバッファ	
	0,									//ステンシルバッファ
	0,									//使用しない
	PFD_MAIN_PLANE,						//レイヤータイプ
	0,									//予約
	0, 0, 0								//レイヤーマスクの設定・未使用
    };

	//デバイスコンテキスト
	if (!(hDC=GetDC(hWnd))){
		MessageBox(hWnd,"Getting HDC Failed....","ERROR",MB_OK);
		return NULL;
	}
	//ピクセルフォーマットの指定
    if ( (pixelformat = ChoosePixelFormat(hDC, &pfd)) == 0 ){
        MessageBox(hWnd, "ChoosePixelFormat Failed....", "Error", MB_OK);
        return NULL;
    }
	//ピクセルフォーマットの設定
    if (SetPixelFormat(hDC, pixelformat, &pfd) == FALSE){
        MessageBox(hWnd, "SetPixelFormat Failed....", "Error", MB_OK);
        return NULL;
    }
	//OpenGLレンダリングコンテキストの作成
	if (!(hRC=wglCreateContext(hDC))){
		MessageBox(NULL,"Creating HGLRC Failed....","ERROR",MB_OK);
		return NULL;
	}
	ReleaseDC(hWnd,hDC);

	return hRC;
}
//ウィンドウのリサイズ時の処理
void Resize(HWND hWnd){
	GLdouble aspect;
	RECT rect;
	//現在のウィンドウのサイズを取得
	GetClientRect(hWnd, &rect);
	//それによってビューポートを設定する
	glViewport(0, 0, rect.right, rect.bottom);
	//アスペクト比の初期化
	aspect = (GLdouble)rect.right/(GLdouble)rect.bottom;
	//プロジェクションモードで射影
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60.0, aspect, 1.0, 10.0 );
	//ノーマルのモデルビューモードへ移行
	glMatrixMode( GL_MODELVIEW );
}
//各コンテキストの解放
void Release_GLWindow(HWND hWnd){
	HDC hDC;
	HGLRC hRC;
	//OpenGLレンダリングコンテキストと
	//デバイスコンテキストを取得
	hRC = wglGetCurrentContext();
	hDC = wglGetCurrentDC();
	//カレントコンテキストを解放
	wglMakeCurrent(NULL, NULL);
	if(!hRC){
		//OpenGLレンダリングコンテキストがない
		MessageBox(hWnd,"Release HGLRC Failed....","ERROR",MB_OK);
	}
	if(hRC){
		//解放
		wglDeleteContext(hRC);
	}
	if(!hDC){
		//デバイスコンテキストがない
		MessageBox(hWnd,"Release HDC Failed....","ERROR",MB_OK);
	}
	if(hDC){
		//解放
		ReleaseDC(hWnd, hDC);
	}
}
//各GL Functionの開始
void StartFunction(void){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//クライアント領域の塗りつぶし色の設定
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	//デプスバッファクリア値の設定
	glClearDepth( 1.0 );
}
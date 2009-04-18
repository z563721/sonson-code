// 
// output_avi
// Main.cpp
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
////////////////////////////////////////////////////////////////////////////////
//オフスクリーン・レンダリングによるAVI出力
//					（ディスプレイキャプチャーあれ）使用
//		sonson(c)2001 17/9
//

#include "EasyAVI.h"		//Tomoyoヘッダ
#include "main.h"
#include "CglDIB.h"

#define WIDTH 320			//DIBサイズ
#define HEIGHT 240

GLfloat LookAt[][4] = {
	{0.0, 0.0, 0.0},
	{3.0,3.0, 4.5}
};							//視点の初期位置

GLfloat Look_deg =0;	//視点の角度
float tt=0;

///////////////////////////////////////////////////////////////////////////////
//描画関数
void Draw(void){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//視点の変換行列の初期化
	glLoadIdentity();
	//視点の決定
	gluLookAt(LookAt[1][0],LookAt[1][1],LookAt[1][2],
		LookAt[0][0],LookAt[0][1],LookAt[0][2],
		0.0, 1.0, 0.0);
	//視点の移動
	//回転
	Look_deg=90*sin(tt/15);
	glRotated(Look_deg,0,1,0);
	drawAxis();
	tt+=0.1f;
	glFlush();
}
///////////////////////////////////////////////////////////////////////////////
//メイン
int WINAPI WinMain(HINSTANCE hCurInst,HINSTANCE hPrevInst,LPSTR lpsCmdLine,int nCmdShow)
{
	//各種変数の初期化
	EasyAVI *e = NULL;
	HDC hMemDC = NULL;
	int i = 0;

	//DIB作成
	CglDIB render;
	render.CreateGLDIB(WIDTH,HEIGHT,24,24);
	//DIB上のOpenGLの初期化
	Init_GLWindow(WIDTH,HEIGHT);
	Resize(WIDTH,HEIGHT);
	StartFunction();
	//EasyAVIクラスの作成
	e = new EasyAVI();

	//録画準備
	hMemDC = e->Start(NULL,WIDTH,HEIGHT,"TEST.AVI",1,30);

	//フレームの描画
	for(i=0;i<240;i++){
		Draw();
		render.Draw(hMemDC,WIDTH,HEIGHT);
		//フレームをAVIに追加
		e->Save();
	}

	//EasyAVIの変数の開放
	e->Clear();

	//EasyAVIの削除
	delete e;
	e = NULL;

	MessageBox(NULL,"AVI出力完了","sonson OpenGL",MB_OK);
	return 0;
}

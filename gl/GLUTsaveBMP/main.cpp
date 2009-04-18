// 
// GLUTsaveBMP
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
//#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "Bitmap.h"

///////////////////////////////////////////////////////////////////////////////
//デフォルトウィンドウサイズ
#define WIDTH	201
#define HEIGHT	201
//リサイズ後のウィンドウサイズを保存する変数
int width;
int height;

///////////////////////////////////////////////////////////////////////////////
//描画関数
void display(void){
	//ウィンドウを塗りつぶす
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//視点の変換行列の初期化
	glLoadIdentity();
	//視点の決定
	gluLookAt(
		2,2,2,
		0,0,0,
		0.0, 1.0, 0.0);
	//四角形の描画

	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3d(1.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glColor3d(1.0, 1.0, 0.0);
			glVertex3f(0.0, 0.0, 1.0);
			glColor3d(1.0, 0.0, 1.0);
			glVertex3f(1.0, 0.0, 1.0);
			glVertex3f(1.0, 0.0, 0.0);
		glEnd();
	glPopMatrix();

	//描画終了
	glFinish();
	glutSwapBuffers();
}
///////////////////////////////////////////////////////////////////////////////
//OpenGL初期化コマンド
void init (void){
	glClearColor (1.0, 0.0, 0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//クライアント領域の塗りつぶし色の設定
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	//デプスバッファクリア値の設定
	glClearDepth( 1.0 );
}
///////////////////////////////////////////////////////////////////////////////
//マウス処理
void mouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			WriteBitmap("output.bmp",width,height);
			break;
	}
}
///////////////////////////////////////////////////////////////////////////////
//リサイズ処理
void resize(int w, int h)
{
	GLdouble aspect;
	//それによってビューポートを設定する
	glViewport(0, 0, w, h);
	width = w;
	height =h;
	//アスペクト比の初期化
	aspect = (GLdouble)w/(GLdouble)h;
	//プロジェクションモードで射影
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60.0, aspect, 1.0,100.0 );
	//ノーマルのモデルビューモードへ移行
	glMatrixMode( GL_MODELVIEW );
}
///////////////////////////////////////////////////////////////////////////////
//メイン関数
int main(int argc, char** argv){
	//GLUT初期化
	glutInit(&argc, argv);
	//GLUTピクセルフォーマット
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	//ウィンドウの初期化と作成
	glutInitWindowSize (WIDTH,HEIGHT); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Save to Bitmap");
	//OpenGL初期化
	init();
	//各処理関数の登録
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	//メインループ
	glutMainLoop();
	return 0;
}
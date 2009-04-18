// 
// GLUTtexture
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
#define WIDTH	300
#define HEIGHT	300
//リサイズ後のウィンドウサイズを保存する変数
int width;
int height;

//時間
float t=0;

//テクスチャ番号
unsigned int tex;

///////////////////////////////////////////////////////////////////////////////
//描画関数
void display(void){
	//ウィンドウを塗りつぶす
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//視点の変換行列の初期化
	glLoadIdentity();
	//視点の決定
	gluLookAt(
		0,0,4,
		0,0,0,
		0.0, 1.0, 0.0);
	//四角形の描画
	glRotatef(t,0,1,0);
	glBindTexture(GL_TEXTURE_2D, tex);
	//ポリゴンとテクスチャ
	glPushMatrix();
		glBegin(GL_QUADS);
		glColor3f(0.5,0.5,0.5);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(1.0, 1.0, 0.0);
			
			glTexCoord2f(0.0, 1.0);
			glVertex3f(1.0,-1.0, 0.0);
			
			glTexCoord2f(1.0, 1.0);
			glVertex3f(-1.0,-1.0, 0.0);
			
			glTexCoord2f(1.0, 0.0);
			glVertex3f(-1.0, 1.0, 0.0);
		glEnd();
	glPopMatrix();
	//描画終了
	glFinish();
	glutSwapBuffers();
	t+=1;
}
///////////////////////////////////////////////////////////////////////////////
//OpenGL初期化コマンド
void init (void){
	glClearColor (1.0, 0.0, 0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	//クライアント領域の塗りつぶし色の設定
	glClearColor( 1.0, 1.0, 0.0, 1.0 );
	//デプスバッファクリア値の設定
	glClearDepth( 1.0 );
	//テクスチャの生成
	tex = GenTextureBitmap("texture.bmp");
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D);
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
	glutCreateWindow ("Bitmap Texture");
	//OpenGL初期化
	init();
	//各処理関数の登録
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(resize);
	//メインループ
	glutMainLoop();
	return 0;
}
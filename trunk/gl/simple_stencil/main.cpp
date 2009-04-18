// 
// simple_stencil
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
#include <math.h>
#define WIDTH	300
#define HEIGHT	300

float t=0;

///////////////////////////////////////////////////////////////////////////////
//描画関数
void display(void){

	//ウィンドウを塗りつぶす
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//視点の変換行列の初期化
	glLoadIdentity();      
	//視点の決定
	gluLookAt(
		0,0,8,
		0,0,0,
		0.0, 1.0, 0.0);
	/////////////////////////////////////////////
	//四角形の描画範囲にステンシル１を付加する
	glEnable(GL_STENCIL_TEST);
	glStencilFunc( GL_ALWAYS, 1, ~0);
	//これから描画するもののステンシル値にすべて１タグをつける
	glStencilOp(GL_KEEP,GL_REPLACE,GL_REPLACE);
	/////////////////////////////////////////////
	//カラー・デプスバッファマスクをセットする
	//これで以下の内容のピクセルの色の値は，書き込まれない．
	glColorMask(0,0,0,0);
	glDepthMask(0);
	//
	glPushMatrix();
		//四角形を動かすため
		glTranslatef(4*cos(t*0.1),sin(t*0.1),0);
		glBegin(GL_QUADS);
			glVertex3f( 1, 1,0);
			glVertex3f(-1, 1,0);
			glVertex3f(-1,-1,0);
			glVertex3f( 1,-1,0);
		glEnd();
	glPopMatrix();
	/////////////////////////////////////////////
	//ビットマスクを解除
	glColorMask(1,1,1,1);
	glDepthMask(1);
	glStencilOp(GL_KEEP,GL_KEEP ,GL_KEEP);
	/////////////////////////////////////////////
	//ティーポット・オブジェクトの描画
	//ステンシルが1のピクセルにワイヤーフレームで描画
	glStencilFunc( GL_EQUAL, 1, ~0);
	glColor3f(1,0.5,0.5);
	glutWireTeapot(3);
	/////////////////////////////////////////////
	//ティーポット・オブジェクトの描画
	//ステンシルが1のピクセルにソリッドモデルで描画
	glStencilFunc( GL_EQUAL, 0, ~0);
	glColor3f(1,0.5,0.5);
	glutSolidTeapot(3);

	/////////////////////////////////////////////
	//ステンシルテスト終了
	glDisable(GL_STENCIL_TEST);
	glFinish();
	glutSwapBuffers();
	t++;
}
///////////////////////////////////////////////////////////////////////////////
//OpenGL初期化コマンド
void init (void){
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//クライアント領域の塗りつぶし色の設定
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	//デプスバッファクリア値の設定
	glClearDepth( 1.0 );
	//ステンシルバッファクリア値の設定
	glClearStencil(0);
	//光源と材質の設定
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL );
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
}
///////////////////////////////////////////////////////////////////////////////
//マウス処理
void mouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT_BUTTON:
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
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	//ウィンドウの初期化と作成
	glutInitWindowSize (800,600); 
	glutInitWindowPosition (200,200);
	glutCreateWindow ("Simple GLUT");
	//OpenGL初期化
	init();
	//各処理関数の登録
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutIdleFunc(display);
	//メインループ
	glutMainLoop();
	return 0;
}
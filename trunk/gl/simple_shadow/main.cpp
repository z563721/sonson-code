// 
// simple_shadow
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

////////////////////////////////////////////////////////////////////
//任意の平面へ影を射影する行列構築関数
void projectShadowMatrix(double *m,				//作成する行列のポインタ
						 double plane[4],		//射影する表面の平面方程式
						 float light[4]			//光源の同時座標値
						 ){
	float dot = plane[0]*light[0] + plane[1]*light[1] +
				plane[2]*light[2] + plane[3]*light[3];

	m[0]  = dot - light[0]*plane[0];
	m[4]  =     - light[0]*plane[1];
	m[8]  =     - light[0]*plane[2];
	m[12] =     - light[0]*plane[3];

	m[1]  =     - light[1]*plane[0];
	m[5]  = dot - light[1]*plane[1];
	m[9]  =     - light[1]*plane[2];
	m[13] =     - light[1]*plane[3];

	m[2]  =     - light[2]*plane[0];
	m[6]  =     - light[2]*plane[1];
	m[10] = dot - light[2]*plane[2];
	m[14] =     - light[2]*plane[3];

	m[3]  =     - light[3]*plane[0];
	m[7]  =     - light[3]*plane[1];
	m[11] =     - light[3]*plane[2];
	m[15] = dot - light[3]*plane[3];
}
///////////////////////////////////////////////////////////////////////////////
//床の描画
void DrawFloor(void){	
	glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
		glVertex3f( 10, -2, 10);
		glVertex3f( 10, -2,-10);
		glVertex3f(-10, -2,-10);
		glVertex3f(-10, -2, 10);
	glEnd();
	glEnable(GL_LIGHTING);
}
///////////////////////////////////////////////////////////////////////////////
//描画関数
void display(void){
	//
	double floor_planar[4] = {0,1,0,2};
	double pM[16];
	float lightpos[4] = { 10, 8, 0, 1};

	//ウィンドウを塗りつぶす
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//視点の変換行列の初期化
	glLoadIdentity();      
	//視点の決定
	gluLookAt(
		5,5,20,
		0,0,0,
		0.0, 1.0, 0.0);
	
	/////////////////////////////////////////////
	//光源の位置の計算と設定
	lightpos[0] = 3*sin(t*0.05);
	lightpos[2] = 6*cos(t*0.05);
	glLightfv(GL_LIGHT0, GL_POSITION, (float*)lightpos);
	
	/////////////////////////////////////////////
	// Plannar Projected Shadow Matrix
	// 平面射影行列の算出
	projectShadowMatrix(pM,floor_planar,lightpos);

	/////////////////////////////////////////////
	//光源の描画
	glColor3f(0.7,0.0,0.7);
	glPushMatrix();
		glTranslatef(lightpos[0],lightpos[1],lightpos[2]);
		glutSolidSphere(0.2,10,10);
	glPopMatrix();

	/////////////////////////////////////////////
	//ティーポット・オブジェクトの描画
	glColor3f(1,0.5,0.5);
	glDisable(GL_CULL_FACE);	
		glutSolidTeapot(3);
	glEnable(GL_CULL_FACE);	

	/////////////////////////////////////////////
	//床のステンシルを付ける
	glEnable(GL_STENCIL_TEST);
	glStencilFunc( GL_ALWAYS, 1, ~0);
	//これから描画するもののステンシル値にすべて１タグをつける
	glStencilOp(GL_KEEP,GL_KEEP ,GL_REPLACE);
	glColor4f(0.7f, 0.4f, 0.0f, 1.0f);
	DrawFloor();
	/////////////////////////////////////////////
	//カラー・デプスバッファマスクをセットする
	//これで以下の内容のピクセルの色の値は、書き込まれない。
	glColorMask(0,0,0,0);
	glDepthMask(0);
	/////////////////////////////////////////////
	//床にティーポットの影のステンシルを付ける
	glEnable(GL_STENCIL_TEST);
	glStencilFunc( GL_EQUAL, 1, ~0);
	//これから描画するもののステンシル値にすべて１タグをつける
	glStencilOp(GL_KEEP,GL_KEEP ,GL_INCR);
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
		glMultMatrixd(pM);
		glDisable(GL_CULL_FACE);	
			glutSolidTeapot(3);
		glEnable(GL_CULL_FACE);	
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);

	/////////////////////////////////////////////
	//ビットマスクを解除
	glColorMask(1,1,1,1);
	glDepthMask(1);
	
	/////////////////////////////////////////////
	//影をつける
	glStencilFunc( GL_EQUAL, 2, ~0 );
	glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.1f, 0.1f, 0.1f, 0.5f);
		glDisable(GL_DEPTH_TEST);		
			DrawFloor();
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	glDisable(GL_STENCIL_TEST);

	/////////////////////////////////////////////
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
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);		
	//光源と材質の設定
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL );
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);

	printf("%u", ~0);
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
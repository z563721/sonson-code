// 
// picking
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

#define WIDTH	300
#define HEIGHT	300
#define BUFSIZE 512

///////////////////////////////////////////////////////////////////////////////
//オブジェクトを描画する
void DrawObjects(GLenum mode){
	///////////////////////////////////////////////////////
	//識別番号1
	if (mode == GL_SELECT)glPushName(1);
		glBegin(GL_QUADS);
		glColor3f(0.0, 1.0, 1.0);
		glVertex3i(3, 2, -1);
		glVertex3i(3, 8, -1);
		glVertex3i(8, 8, -1);
		glVertex3i(8, 2, -1);
		glEnd();
	glPopName();
	///////////////////////////////////////////////////////
	//識別番号2
	if(mode == GL_SELECT)glPushName(2);
		///////////////////////////////////////////////////////
		//識別番号2-1
		glPushName(1);
			glBegin(GL_QUADS);
			glColor3f(1.0, 1.0, 0.0);
			glVertex3i(2, 0,-0.1);
			glVertex3i(2, 6,-0.1);
			glVertex3i(6, 6,-0.1);
			glVertex3i(6, 0,-0.1);
			glEnd();
		glPopName();
			///////////////////////////////////////////////////////
			//識別番号2-2
			glPushName(2);
			///////////////////////////////////////////////////////
			//識別番号2-2-1
			glPushName(1);
				glBegin(GL_QUADS);
				glColor3f(1.0, 0.0, 0.0);
				glVertex3i(2, 0, -0.05);
				glVertex3i(2, 1, -0.05);
				glVertex3i(8, 1, -0.05);
				glVertex3i(8, 0, -0.05);
				glEnd();
			glPopName();
			///////////////////////////////////////////////////////
			//識別番号2-2-2
			glPushName(2);
				glBegin(GL_QUADS);
				glColor3f(1.0, 1.0, 1.0);
				glVertex3i( 1, 0, 0);
				glVertex3i( 1, 1, 0);
				glVertex3i(-1, 1, 0);
				glVertex3i(-1, 0, 0);
				glEnd();
			glPopName();
		glPopName();
	glPopName();
	///////////////////////////////////////////////////////
	//識別番号3
	if (mode == GL_SELECT)glPushName(3);
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3i(0, 2, -2);
	glVertex3i(0, 7, -2);
	glVertex3i(5, 7, -2);
	glVertex3i(5, 2, -2);
	glEnd();
	glPopName();
}
///////////////////////////////////////////////////////////////////////////////
//セレクションバッファを整理する
int SelectHits(GLuint hits,GLuint *buf){
	unsigned int i,j;
	// 最大階層数を4と仮定した処理
	GLuint hit_name[4]={-1, -1, -1, -1};
	float depth_min=10.0f;
	float depth_1=1.0f;
	float depth_2=1.0f;
	GLuint depth_name;
	GLuint *ptr;
	// ヒットしたデータなし
	if(hits<=0)return -1;
	// ポインタを作業用ptrへ渡す．
	ptr = (GLuint*)buf;

	printf("ヒット総数 %d\n\n",(int)hits);
	for(i=0; i<hits; i++){
		printf("  ヒット %d",(int)i+1);
		// 識別番号の階層の深さ
		depth_name = *ptr;
		printf("  識別番号の階層数 %d\n",(int)depth_name);
		ptr++;
		depth_1 = (float) *ptr/0x7fffffff;
		printf("    デプスの最小値 %f\n",depth_1);
		ptr++;
		depth_2 = (float) *ptr/0x7fffffff;
		printf("    デプスの最大値 %f\n",depth_2);
		ptr++;
		printf("    識別番号 ");
		// 最小デプスの確認
		if(depth_min>depth_1){
			depth_min = depth_1;
			// 識別番号を保存
			for(j=0; j<depth_name; j++){
				printf("%d ",*ptr);
				hit_name[j] = *ptr;
				ptr++;
			}
		}
		else{
			for(j=0; j<depth_name; j++){
				printf("%d ",*ptr);
				ptr++;
			}
		}
		printf("\n");
	}
	printf("\nデプス最小の識別番号\n");
	for(i=0;i<4;i++){
		if(hit_name[i]==-1)break;
		printf("%d ",hit_name[i]);
	}
	printf("\n\n\n");
	return 1;
}
///////////////////////////////////////////////////////////////////////////////
//ピックアップ
void pick(int x, int y){
  GLuint selectBuf[BUFSIZE];
	GLint hits;
	GLint viewport[4];
	float current_aspect;
	glGetIntegerv(GL_VIEWPORT, viewport);

	glSelectBuffer(BUFSIZE, selectBuf);
	(void) glRenderMode(GL_SELECT);

	glInitNames();
	glMatrixMode(GL_PROJECTION);			//プロジェクションモード
	glPushMatrix();							//セレクションモードのときのみ下の行列計算
		glLoadIdentity();					//を反映させるためにPushする
		gluPickMatrix(x,viewport[3]-y,		//ピッキング行列の乗算
			5.0,5.0, viewport);
		current_aspect = (float)viewport[2]/(float)viewport[3];
		gluPerspective( 60.0, current_aspect, 1.0, 100.0 );
		glMatrixMode( GL_MODELVIEW );		//ここでモデルビューモードにする！！！！
		DrawObjects(GL_SELECT);				//セレクションモードで描画する
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );			//モデルビューモードへ戻す

	hits = glRenderMode(GL_RENDER);
	SelectHits(hits, selectBuf);
}
///////////////////////////////////////////////////////////////////////////////
//描画関数
void display(void){
	//ウィンドウを塗りつぶす
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//視点の変換行列の初期化
	glLoadIdentity();
	//視点の決定
	gluLookAt(
		4,4,12,
		4,4,0,
		0.0, 1.0, 0.0);

	DrawObjects(GL_RENDER);
	glFlush();
	glutSwapBuffers();
}
///////////////////////////////////////////////////////////////////////////////
//OpenGL初期化コマンド
void init (void){
	glEnable(GL_DEPTH_TEST);
	//クライアント領域の塗りつぶし色の設定
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	//デプスバッファクリア値の設定
	glClearDepth( 1.0 );
}
///////////////////////////////////////////////////////////////////////////////
//マウス処理
void mouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN)pick(x,y);
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
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	//ウィンドウの初期化と作成
	glutInitWindowSize (WIDTH,HEIGHT); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Simple GLUT");
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
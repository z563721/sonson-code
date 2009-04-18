// 
// shadow_volume
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
//
#ifdef WIN32
#include <GL/glut.h>
#else
#include <glut/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define V_SIZE 10		// 投影のサイズ

int flag_teapot=0;		// オマケのフラグ
int flag_volume=0;
int flag_sphere=0;

float look_y=0;			// 注視点のY座標
float t=0;				// 時間

float ground_vertex[10][10][3];
						// 床の座標
float object_vertex[4][3]={
	{-1, 3, -1},
	{ 2, 3, -1},
	{-1, 3,  2},
	{ 0, 5,  0}
};						//操作用の四面体の座標値
float base_object_vertex[4][3]={
	{-1, -1, -1},
	{ 2, -1, -1},
	{-1, -1,  2},
	{ 0, 1,  0}
};						// 元になる四面体の座標値
////////////////////////////////////////////////////////////////////
//方向ベクトルの平滑化関数
void Normalizef(float *vector){
	float tmp=0;
	//絶対値を計算
	tmp+=vector[0]*vector[0];
	tmp+=vector[1]*vector[1];
	tmp+=vector[2]*vector[2];
	//絶対値が０のとき処理
	if(tmp!=0){
		tmp=sqrt(tmp);
		//単位ベクトルに処理
		vector[0]/=tmp;
		vector[1]/=tmp;
		vector[2]/=tmp;
	}
}
////////////////////////////////////////////////////////////////////
//与えられた３点からその面の法線ベクトルを算出する
void Normal_Vecf(GLfloat input1[3],GLfloat input2[3],GLfloat input3[3],GLfloat result[3]){
	float temp1[3];
	float temp2[3];
	//
	temp1[0]=input2[0]-input3[0];
	temp1[1]=input2[1]-input3[1];
	temp1[2]=input2[2]-input3[2];
	temp2[0]=input2[0]-input1[0];
	temp2[1]=input2[1]-input1[1];
	temp2[2]=input2[2]-input1[2];
	//外積
	result[0]=temp1[1]*temp2[2]-temp1[2]*temp2[1];
	result[1]=temp1[2]*temp2[0]-temp1[0]*temp2[2];
	result[2]=temp1[0]*temp2[1]-temp1[1]*temp2[0];
	//平滑化
	Normalizef(result);
}
////////////////////////////////////////////////////////////////////
//3*3行列と3次元ベクトルの乗算
void multMatrix(double *m,			//乗算する行列のポインタ
				float input[3],			//乗算する点のポインタ
				float result[3]			//結果
				 ){
	result[0] = m[0]*input[0] + m[4]*input[1] + m[8]*input[2];
	result[1] = m[1]*input[0] + m[5]*input[1] + m[9]*input[2];
	result[2] = m[2]*input[0] + m[6]*input[1] + m[10]*input[2];
}
///////////////////////////////////////////////////////////////////////////////
//部屋の描画関数
void DrawRoom(void){
	int i,j;
	float normal[3];
	/////////////////////////////////////////////
	//波打つ床
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			glBegin(GL_TRIANGLES);
				Normal_Vecf(ground_vertex[i][j],ground_vertex[i][j+1],ground_vertex[i+1][j+1],normal);
				glNormal3fv(normal);
				glVertex3fv(ground_vertex[i][j]);
				glVertex3fv(ground_vertex[i][j+1]);
				glVertex3fv(ground_vertex[i+1][j+1]);
				Normal_Vecf(ground_vertex[i][j],ground_vertex[i+1][j+1],ground_vertex[i+1][j],normal);
				glNormal3fv(normal);
				glVertex3fv(ground_vertex[i][j]);
				glVertex3fv(ground_vertex[i+1][j+1]);
				glVertex3fv(ground_vertex[i+1][j]);
			glEnd();
		}
	}
	/////////////////////////////////////////////
	//壁
	glBegin(GL_QUADS);
		//1
		glVertex3f(-10, 15,-10);
		glVertex3f(-10, 15,  8);
		glVertex3f(-10, 0,  8);
		glVertex3f(-10, 0,-10);
		//2
		glVertex3f( 8, -5,-10);
		glVertex3f( 8,-5,  8);
		glVertex3f( 8, 15,  8);
		glVertex3f( 8, 15,-10);
		//3
		glVertex3f(-10, -5,-10);
		glVertex3f(  8, -5,-10);
		glVertex3f(  8, 15,-10);
		glVertex3f(-10, 15,-10);
		//4
		glVertex3f( 8, -5, 8);
		glVertex3f(-10, -5, 8);
		glVertex3f(-10, 15, 8);
		glVertex3f( 8, 15, 8);
	glEnd();
}
///////////////////////////////////////////////////////////////////////////////
//光源と任意の点の延長上にある点を算出
void ClacShadowPoint(float *lightpos, float *point, float *result){
	float vec[3];

	vec[0] = point[0] - lightpos[0];
	vec[1] = point[1] - lightpos[1];
	vec[2] = point[2] - lightpos[2];

	result[0] = lightpos[0] + vec[0]*V_SIZE;
	result[1] = lightpos[1] + vec[1]*V_SIZE;
	result[2] = lightpos[2] + vec[2]*V_SIZE;
}
///////////////////////////////////////////////////////////////////////////////
//入力された３点から構成されるポリゴンのShadow Volumeを描画する
void drawShadowPolygon(float *lightpos,float *point0,float *point1,float *point2){
	float shadow_point[3][3];

	/////////////////////////////////////////////
	//射影後の点をすべて算出
	ClacShadowPoint(lightpos,point0, shadow_point[0]);
	ClacShadowPoint(lightpos,point1, shadow_point[1]);
	ClacShadowPoint(lightpos,point2, shadow_point[2]);
	/////////////////////////////////////////////
	//Shadow Volume描画
	glBegin(GL_QUADS);
		//1
		glVertex3fv(point1);
		glVertex3fv(point0);
		glVertex3fv(shadow_point[0]);
		glVertex3fv(shadow_point[1]);
		//2
		glVertex3fv(point2);
		glVertex3fv(point1);
		glVertex3fv(shadow_point[1]);
		glVertex3fv(shadow_point[2]);
		//3
		glVertex3fv(point0);
		glVertex3fv(point2);
		glVertex3fv(shadow_point[2]);
		glVertex3fv(shadow_point[0]);
	glEnd();
}
///////////////////////////////////////////////////////////////////////////////
//光源に対しての向きをチェックする
int CheckShadow(float *lightpos, float *point0,float *point1,float *point2){
	float center[3];
	float light_direction[3];
	float polygon_normal[3];
	float inner_product;

	//重心算出
	center[0] = (point0[0] + point1[0] + point2[0])*0.333f;
	center[1] = (point0[1] + point1[1] + point2[1])*0.333f;
	center[2] = (point0[2] + point1[2] + point2[2])*0.333f;
	//光線方向
	light_direction[0] = center[0] - lightpos[0];
	light_direction[1] = center[1] - lightpos[1];
	light_direction[2] = center[2] - lightpos[2];
	Normalizef(light_direction);
	//ポリゴンの法線ベクトル
	Normal_Vecf(point0,point1,point2,polygon_normal);
	//内積算出
	inner_product = light_direction[0]*polygon_normal[0]
					+ light_direction[1]*polygon_normal[1]
					+ light_direction[2]*polygon_normal[2];
	if(inner_product>=0){
		return 1;
	}
	else 
		return 0;
}
///////////////////////////////////////////////////////////////////////////////
//描画関数
void drawShadowVolume(float *lightpos){
	//光源に対して向きが反対のものはShadowVolumeを逆向きで描画する
	//CULL_FACEを使用するため
	if( CheckShadow(lightpos,object_vertex[1],object_vertex[2],object_vertex[0])){
		drawShadowPolygon(lightpos,object_vertex[1],object_vertex[2],object_vertex[0]);
	}else{
		drawShadowPolygon(lightpos,object_vertex[0],object_vertex[2],object_vertex[1]);
	}
	if( CheckShadow(lightpos,object_vertex[2],object_vertex[1],object_vertex[3])){
		drawShadowPolygon(lightpos,object_vertex[2],object_vertex[1],object_vertex[3]);
	}else{
		drawShadowPolygon(lightpos,object_vertex[3],object_vertex[1],object_vertex[2]);
	}
	if( CheckShadow(lightpos,object_vertex[0],object_vertex[2],object_vertex[3])){
		drawShadowPolygon(lightpos,object_vertex[0],object_vertex[2],object_vertex[3]);
	}else{
		drawShadowPolygon(lightpos,object_vertex[3],object_vertex[2],object_vertex[0]);
	}
	if( CheckShadow(lightpos,object_vertex[1],object_vertex[0],object_vertex[3])){
		drawShadowPolygon(lightpos,object_vertex[1],object_vertex[0],object_vertex[3]);
	}else{
		drawShadowPolygon(lightpos,object_vertex[3],object_vertex[0],object_vertex[1]);
	}
}
///////////////////////////////////////////////////////////////////////////////
//オブジェクトを回転させる
void rotateObject(float t){
	float rotated[3];
	double rM[16] = { 
					1,0,0,0,
					0,1,0,0,
					0,0,1,0,
					0,0,0,1};
	//Z軸中心に回転
	rM[0] = cos(t);rM[4] = -sin(t);
	rM[1] = sin(t);rM[5] = cos(t);
	//originalの座標値から常に計算する
	multMatrix(rM,base_object_vertex[0],rotated);
	object_vertex[0][0]=rotated[0];
	object_vertex[0][1]=rotated[1]+5;
	object_vertex[0][2]=rotated[2];
	multMatrix(rM,base_object_vertex[1],rotated);
	object_vertex[1][0]=rotated[0];
	object_vertex[1][1]=rotated[1]+5;
	object_vertex[1][2]=rotated[2];
	multMatrix(rM,base_object_vertex[2],rotated);
	object_vertex[2][0]=rotated[0];
	object_vertex[2][1]=rotated[1]+5;
	object_vertex[2][2]=rotated[2];
	multMatrix(rM,base_object_vertex[3],rotated);
	object_vertex[3][0]=rotated[0];
	object_vertex[3][1]=rotated[1]+5;
	object_vertex[3][2]=rotated[2];
}
///////////////////////////////////////////////////////////////////////////////
//四面体描画関数
void drawObject(void){
	float normal[3];
	glBegin(GL_TRIANGLES);
		Normal_Vecf(object_vertex[1],object_vertex[2],object_vertex[0],normal);
		glNormal3fv(normal);
		glVertex3fv(object_vertex[1]);
		glVertex3fv(object_vertex[2]);
		glVertex3fv(object_vertex[0]);
		Normal_Vecf(object_vertex[2],object_vertex[1],object_vertex[3],normal);
		glNormal3fv(normal);
		glVertex3fv(object_vertex[2]);
		glVertex3fv(object_vertex[1]);
		glVertex3fv(object_vertex[3]);
		Normal_Vecf(object_vertex[0],object_vertex[2],object_vertex[3],normal);
		glNormal3fv(normal);
		glVertex3fv(object_vertex[0]);
		glVertex3fv(object_vertex[2]);
		glVertex3fv(object_vertex[3]);
		Normal_Vecf(object_vertex[1],object_vertex[0],object_vertex[3],normal);
		glNormal3fv(normal);
		glVertex3fv(object_vertex[1]);
		glVertex3fv(object_vertex[0]);
		glVertex3fv(object_vertex[3]);
	glEnd();
}

///////////////////////////////////////////////////////////////////////////////
//描画関数
void display(void){
	//光源位置
	float lightpos[4] = { 0, 10, 0, 1};
	look_y = 7+ 5*sin(t*0.01);
	//ウィンドウを塗りつぶす
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//視点の変換行列の初期化
	glLoadIdentity();
	//視点の決定
	glPushMatrix();
	gluLookAt(
		0,look_y,10,
		0,4,0,
		0.0, 1.0, 0.0);
	//シーン全体を回転
	glRotatef(t*0.5,0,1,0);
		/////////////////////////////////////////////
		//光源の位置の計算と設定
		lightpos[0] = 4*sin(t*0.035);
		lightpos[1] = 10+2*cos(t*0.05);
		lightpos[2] = 4*cos(t*0.05);
		glLightfv(GL_LIGHT0, GL_POSITION, (float*)lightpos);
		/////////////////////////////////////////////
		//光源の描画
		glColor3f(1.0,1.0,1.0);
		glDisable(GL_LIGHTING);
		glPushMatrix();
			glTranslatef(lightpos[0],lightpos[1],lightpos[2]);
			glutSolidSphere(0.2,10,10);
		glPopMatrix();
		glEnable(GL_LIGHTING);
		/////////////////////////////////////////////
		//付加効果のティーポット・オマケ
		if(flag_teapot || flag_sphere){
			glPushMatrix();
				glTranslatef(4*sin(t*0.01),2,4*cos(t*0.01));
				glDisable(GL_CULL_FACE);		
				if(flag_teapot)glutSolidTeapot(1.5);
				if(flag_sphere)glutSolidSphere(1.5,20,20);
				glEnable(GL_CULL_FACE);		
			glPopMatrix();
		}
		/////////////////////////////////////////////
		//四面体描画
		rotateObject(t*0.05);
		drawObject();
		glColor3f(0.0,0.0,0.6);
		/////////////////////////////////////////////
		//部屋の描画
		DrawRoom();
		//
		glDisable(GL_LIGHTING);
		/////////////////////////////////////////////
		//Shadow Volumeの描画
		if(flag_volume){
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			glDisable(GL_CULL_FACE);
			glColor3f(1,1,1);
			drawShadowVolume(lightpos);
			glEnable(GL_CULL_FACE);		
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		}
		/////////////////////////////////////////////
		//Shadow Volumeステンシルのセット
		//カラー・デプスマスク，セット
		glColorMask(0,0,0,0);
		glDepthMask( GL_FALSE );
		//ステンシル
		glEnable(GL_STENCIL_TEST);
		glStencilFunc( GL_ALWAYS, 1, ~0);
		/////////////////////////////////////////////
		//前面のステンシル
		glStencilOp( GL_KEEP, GL_KEEP, GL_INCR);
		glFrontFace(GL_CW);
		drawShadowVolume(lightpos);
		//背面のステンシル
		glStencilOp( GL_KEEP, GL_KEEP, GL_DECR);
		if(!flag_volume){
			glFrontFace(GL_CCW);
			drawShadowVolume(lightpos);
		}
		/////////////////////////////////////////////
		//描画方向を右手系に再セット
		glFrontFace(GL_CCW);
		//マスク解除
		glColorMask(1,1,1,1);
		glDepthMask(GL_TRUE);
	glPopMatrix();
	/////////////////////////////////////////////
	//影・シーンよりも手前にドーンと描画する
	glStencilFunc( GL_NOTEQUAL, 0, ~0 );
	glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.0f, 0.1f, 0.1f, 0.5f);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glBegin(GL_QUADS);
			//1
			glVertex3f( 10, 10,-2);
			glVertex3f( 10,-10,-2);
			glVertex3f(-10,-10,-2);
			glVertex3f(-10, 10,-2);
		glEnd();
		glEnable(GL_CULL_FACE);		
		glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_LIGHTING);

	glFinish();
	glutSwapBuffers();
	//時間
	t++;
}
///////////////////////////////////////////////////////////////////////////////
//OpenGL初期化コマンド
void init (void){
	int i,j;
	glEnable(GL_DEPTH_TEST);

	//クライアント領域の塗りつぶし色の設定
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
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
	//床の作成
	for(i=-5;i<5;i++){
		for(j=-5;j<5;j++){
			ground_vertex[i+5][j+5][0] = 2*i;
			ground_vertex[i+5][j+5][1] = 0.7*sin(i)-0.5*cos(j);
			ground_vertex[i+5][j+5][2] = 2*j;
		}
	}
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
	gluPerspective( 70.0, aspect, 1.0,100.0 );
	//ノーマルのモデルビューモードへ移行
	glMatrixMode( GL_MODELVIEW );
}
void keyboard(unsigned char key,int x, int y){
	//オマケの操作
	if(key=='t'){
		if(flag_teapot)flag_teapot = 0;
		else{
			flag_sphere = 0;
			flag_teapot = 1;
		}
	}
	else if(key=='v'){
		if(flag_volume)flag_volume = 0;
		else flag_volume = 1;
	}
	else if(key=='s'){
		if(flag_sphere)flag_sphere = 0;
		else{
			flag_sphere = 1;
			flag_teapot = 0;
		}
	}
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
	glutCreateWindow ("Shadow Volume Sample");
	//OpenGL初期化
	init();
	//各処理関数の登録
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);

	//メインループ
	glutMainLoop();
	return 0;
}
////////////////////////////////////////////////////////////////////
//座標軸を描画する関数

#include "Axis.h"
//座標軸のデータ
GLdouble vertex3[][3] = {
	{ 100.0,  0.0, 0.0 },
	{ -100.0, 0.0, 0.0 },
	{ 0.0,  100.0, 0.0 },
	{ 0.0,  -100.0, 0.0 },
	{ 0.0,  0.0, 100.0 },
	{ 0.0,  0.0, -100.0 },
};
//座標軸の位相データ
int edge2[][2] = {
	{ 0, 1 },
	{ 2, 3 },
	{ 4, 5 },
};
//描画関数
GLvoid drawAxis(GLvoid)
{
	int i;
    glPushMatrix();
	//座標軸の描画
	glColor3f(0,0,0);
	glBegin(GL_LINES);		//描画する図形のタイプを指定する
	for(i = 0; i <3; i++){
			glVertex3dv(vertex3[edge2[i][0]]);
			glVertex3dv(vertex3[edge2[i][1]]);
	}
	glEnd();
    glPopMatrix();
}
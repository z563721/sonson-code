// 
// glutSkelton
// glutSkelton.cpp
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
//#include <gl.h>
#include <glu.h>
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
	
double widthPro = 1.0f;
double heightPro = 1.0f;
	
#define INI_WIDTH	250
#define INI_HEIGHT	250
	
void mouse( int button, int state, int x, int y ) {
	if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
		printf( "%3.1f,%3.1f\n", x * widthPro, INI_HEIGHT - y * heightPro );
	glutPostRedisplay();
}
	
void init ( void ) {
	glPointSize ( 3 );
	glClearColor ( 0.0, 0.0, 0.0, 0.0 );
	glMatrixMode ( GL_PROJECTION ) ;
	glLoadIdentity ();
	glOrtho ( 0.0, INI_WIDTH, 0.0, INI_HEIGHT, -1.0, 1.0 );
	glMatrixMode ( GL_MODELVIEW );
}
	
void resize ( int w, int h ) {
	widthPro = (float) INI_WIDTH / (float) w;
	heightPro = (float) INI_HEIGHT /(float) h;
	glViewport ( 0, 0, w, h );
	glClearColor ( 0.0, 0.0, 0.0, 0.0 );
	glMatrixMode ( GL_PROJECTION ) ;
	glLoadIdentity ();
	glOrtho ( 0.0, INI_WIDTH, 0.0, INI_HEIGHT, -1.0, 1.0 );
	glMatrixMode ( GL_MODELVIEW );
}
	
void display ( void ) {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	glFlush ();
}
	
int main (int argc, char** argv) {
	glutInit ( &argc, argv );
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize ( INI_WIDTH, INI_HEIGHT ); 
	glutInitWindowPosition ( 100, 100 );
	glutCreateWindow ( "GLUT" );
	init ();
	glutReshapeFunc ( resize );
	glutMouseFunc ( mouse );
	glutDisplayFunc ( display );
	glutMainLoop ();
	return 0;
}
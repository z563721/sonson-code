// 
// polygon
// dividePolygon.cpp
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
#include <gl.h>
#include <glu.h>
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
	
double widthPro = 1.0f;
double heightPro = 1.0f;
	
#define INI_WIDTH	250
#define INI_HEIGHT	250

typedef struct _Point {
	double	x;
	double	y;
	_Point	*pPrev;
	_Point	*pNext;
	int		flag;
} Point;
	
Point *head = NULL;
Point *curr = NULL;
int	counter = 0;

using namespace std;
vector<Point*> divided;
	
Point* add( Point *curr, double x, double y ) {
	counter++;
	Point *p = (Point*) malloc ( sizeof( Point ) );
	p->x = x;
	p->y = y;
	p->flag = 0;
	if( curr == NULL ) {
		p->pPrev = p;
		p->pNext = p;
		head = p;
	}
	else {
		p->pPrev = curr;
		p->pNext = head;
		p->pPrev->pNext = p;
		p->pNext->pPrev = p;
	}
	return p;
	printf( "%3.1f, %3.1f\n", p->x, p->y );
}
	
Point* del( Point *curr ) {
	if( curr == NULL )
		return NULL;
	counter--;
	if( curr->pPrev == curr || curr->pNext == curr ) {
		free( curr );
		head = NULL;
		return NULL;
	}
	if( curr == head )
		head = curr->pNext;
	curr->pNext->pPrev = curr->pPrev;
	curr->pPrev->pNext = curr->pNext;
	Point *next = curr->pNext;
	free( curr );
	return next;
}

int wayOfNormal( Point *input1, Point *input2, Point *input3 ){
	double temp1[2];
	double temp2[2];
	//
	temp1[0] = input1->x - input2->x;
	temp1[1] = input1->y - input2->y;
	
	temp2[0] = input1->x - input3->x;
	temp2[1] = input1->y - input3->y;
	
	double ret= temp1[0] * temp2[1] - temp1[1] * temp2[0];
	
	if ( ret > 0 )
		return 1;
	else
		return 0;
}

int CheckPointInTriangle( Point *p1, Point *p2, Point *p3, Point *check){
	
	int result1 = wayOfNormal( check, p1, p2 );
	int result2 = wayOfNormal( check, p2, p3 );
	int result3 = wayOfNormal( check, p3, p1 );

	if( result1 == result2 && result2 == result3 )
		return 1;
	else
		return 0;
};

int checkIsOtherPointsInside( Point *point ) {
	Point *p = point->pNext->pNext;
	while( 1 ) {
		if( p == NULL )
			break;
		if ( CheckPointInTriangle( point, point->pNext, point->pPrev, p) )
			return 1;
		p = p->pNext;
		if ( p == point->pPrev ) {
			break;
		}
	}
	return 0;
}
	
Point*getMaxDistanceFromOrigin( void ) {
	double distance = 0;
	Point *p = head;
	Point *max = head;
	while( 1 ) {
		if( p == NULL )
			break;
		double abs = sqrt( p->x * p->x + p->y * p->y );
		if( abs > distance ) {
			distance = abs;
			max = p;
		}
		p = p->pNext;
		if ( p == head )
			break;
	}
	return max;
}

void divide( ) {
	while( counter > 2 ) {
		Point *start = getMaxDistanceFromOrigin ( );
		Point *p = head;
		int way = wayOfNormal ( start, start->pPrev, start->pNext );
		p = start;
		while( 1 ) {
			if( p == NULL )
				break;
			if( way == wayOfNormal ( p, p->pPrev, p->pNext ) )
				if( !checkIsOtherPointsInside( p ) ) {
					del ( p );
					Point *newP = (Point*) malloc ( sizeof( Point ) );
					newP->x = p->x;
					newP->y = p->y;
					divided.push_back( newP );
					newP = (Point*) malloc ( sizeof( Point ) );
					newP->x = p->pNext->x;
					newP->y = p->pNext->y;
					divided.push_back( newP );
					newP = (Point*) malloc ( sizeof( Point ) );
					newP->x = p->pPrev->x;
					newP->y = p->pPrev->y;
					divided.push_back( newP );
					break;
				}
			p = p->pNext;
			if ( p == start )
				break;
		}
	}
}

void mouse( int button, int state, int x, int y ) {
	if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
		curr = add( curr,  x * widthPro, INI_HEIGHT - y * heightPro );
	if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
		divide ();
	glutPostRedisplay();
}

void init (void) {
	glPointSize ( 3 );
	glClearColor ( 0.0, 0.0, 0.0, 0.0 );
	glMatrixMode ( GL_PROJECTION) ;
	glLoadIdentity ();
	glOrtho ( 0.0, INI_WIDTH, 0.0, INI_HEIGHT, -1.0, 1.0 );
	glMatrixMode(GL_MODELVIEW);
}

void resize ( int w, int h ) {
	widthPro = (float) INI_WIDTH / (float) w;
	heightPro = (float) INI_HEIGHT /(float) h;
	glViewport(0, 0, w, h);
	glClearColor ( 0.0, 0.0, 0.0, 0.0 );
	glMatrixMode ( GL_PROJECTION ) ;
	glLoadIdentity ();
	glOrtho ( 0.0, INI_WIDTH, 0.0, INI_HEIGHT, -1.0, 1.0 );
	glMatrixMode(GL_MODELVIEW);
}

void draw ( void ) {
	Point *p = head;
	glBegin ( GL_LINE_LOOP );
	glColor3f( 1, 1, 1 );
	while( 1 ) {
		if( p == NULL )
			break;
		glVertex3f ( p->x, p->y, 0 );
		p = p->pNext;
		if ( p == head ) {
			break;
		}
	}
	glEnd ();
	glBegin ( GL_POINTS );
	p = head;
	glColor3f( 1, 0, 1 );
	while( 1 ) {
		if( p == NULL )
			break;
		glVertex3f ( p->x, p->y, 0 );
		p = p->pNext;
		if ( p == head ) {
			break;
		}
	}
	glEnd ();
	vector<Point*>::iterator it = divided.begin();
	while( it != divided.end() ) {
	glColor3f( 0.5, 0.5, 0.5 );
	glBegin ( GL_LINE_LOOP );
		glVertex3f ( (*it)->x, (*it)->y, 0 );
		++it;
		glVertex3f ( (*it)->x, (*it)->y, 0 );
		++it;
		glVertex3f ( (*it)->x, (*it)->y, 0 );
		++it;
	glEnd ();
	}
}

void display ( void ) {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	draw ();
	glFlush ();
}

int main (int argc, char** argv) {
	glutInit ( &argc, argv );
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize ( INI_WIDTH, INI_HEIGHT ); 
	glutInitWindowPosition ( 100, 100 );
	glutCreateWindow ( "hello" );
	init ();
	glutReshapeFunc(resize);
	glutMouseFunc ( mouse );
	glutDisplayFunc ( display );
	glutMainLoop ();
	return 0;
}
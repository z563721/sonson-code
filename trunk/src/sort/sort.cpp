// 
// sort
// sort.cpp
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
//////////////////////////////////////////////////////////////////////////////////////////
//
// sorting algorithm
//
////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mt19937ar.h"

//
// miscellaneous
//

void swap( int* a, int *b ) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void disp( int *array, int size ) {
	for( int i = 0; i < size; i++ ) {
		printf( "%8d", *(array+i) );
		if( i%10 == 9 )
			printf( "\n" );
	}
	printf( "\n" );
}

int* makeArray( int size ) {
	unsigned long init[4] = { 0x123, 0x234, 0x345, 0x456 };
	unsigned long length = 10;
	init_by_array( init, length );
	int*array = ( int* )malloc( sizeof(int) * size );
	if( !array )
		return NULL;
	int*p = array;
	for( int i = 0; i < size; i++ )
		*p++ = abs( (int) genrand_int32() >> 16 );
	return array;
}

//
// quicksort
//

int quick_swap( int *array, int size ) {
	if( size < 1 )
		return 0;
	//int somewhere = size / 2;
	int somewhere = rand()%size;
	int pivot = array[somewhere];
	array[somewhere] = *(array);
	int p = 0;
	for ( int i = 0 + 1; i <= size; i++) {
		if ( *(array+i) < pivot) {
			p++;
			swap( array+p, array+i);
		}
	}
	*(array) = *(array+p);
	*(array+p) = pivot;
	disp( array, p );
	quick_swap( array, p-1 );
	disp( array+ p, size - p );
	quick_swap( array+ p+1, size - p - 1 );
	return 0;
}

int quicksort( int *array, int size ) {
	int *input = ( int* )malloc( sizeof(int) * size );
	for( int i = 0; i < size; i++ ) {
		*(input+i) = *(array+i);
	}
	printf( "////////////////////////////////////////\n" );
	printf( "// quick sort start\n" );
	disp( input , size );
	
	quick_swap( input, size - 1 );
	printf( "// result\n" );
	disp( input , size );
	
	
	free( input );
	return 0;
}

//
// merge sort
//

int choiseMax( int *array, int a ) {
	int a2 = a * 2;
	int a2_1 = a2 + 1;
	if( array[a] > array[a2] ) {
		if( array[a2] > array[a2_1] ) {
			return a;
		}
		else {
			if( array[a2_1] > array[a] ) {
				return a2_1;
			}
			else
				return a;
		}
	}
	else {
		if( array[a] > array[a2_1] ) {
			return a2;
		}
		else {
			if( array[a2_1] > array[a2] ) {
				return a2_1;
			}
			else
				return a2;
		}
	}
};

int merge_swap( int *front, int *back, int start, int block_size, int size ) {
	int start1 = start;
	int start2 = start+block_size;
	int end1 = ( start+block_size-1 < size) ? start+block_size : size;
	int end2 = ( start+2*block_size-1 < size) ? start+2*block_size : size;
	int p1 = start1;
	int p2 = start2;
	int *tempback = back + p1;
	while( p1 < end1 && p2 < end2 ) {
		if( front[p1] < front[p2] ) {
			*tempback++ = front[p1];
			p1++;
		}
		else {
			*tempback++ = front[p2];
			p2++;
		}
	}
	while( p1 < end1 ) {
		*tempback++ = front[p1];
		p1++;
	}
	while( p2 < end2 ) {
		*tempback++ = front[p2];
		p2++;
	}
	return 0;
}

int mergesort( int *array, int size ) {
	
	int *front = ( int* )malloc( sizeof(int) * size );
	int *back = ( int* )malloc( sizeof(int) * size );
	
	for( int i = 0; i < size; i++ ) {
		*(front+i) = *(array+i);
		*(back+i) = *(array+i);
	}
	printf( "////////////////////////////////////////\n" );
	printf( "// merge sort start\n" );
	disp( front , size );
	
    for( int block_size = 1; block_size < size; block_size*=2 ) {
		for( int start = 0; start < size; start+=(block_size*2) ) {
			merge_swap( front, back, start, block_size, size );
		}
		int *temp = (int*)back;
		back = front;
		front = temp;
		disp( front , size );
	}
	
	printf( "// result\n" );
	disp( front , size );
	
	
	free( front );
	free( back );
	return 0;
}

//
// heap sort
//

int make_heap( int *array, int size ) {
	int i = size / 2;
	int a = i;
	array--;
	while( a >= 1 ) {
		int prev_a = a;
		//printf( "a->%d, i->%d\n", a,i );
		//printf( "a->%d, 2a->%d, 2a+1->%d\n", array[a],array[2*a],array[2*a+1] );
		//disp( array+1, size );
		if( 2 * a + 1 <= size ) {
			int max = choiseMax( array, a );
			int temp = array[a];
			array[a] = array[max];
			array[max] = temp;
			a = max;
		}
		else if( 2 * a <= size ) {
			int max = 0;
			if( array[2*a] > array[a] ) {
				max = 2 * a;
				int temp = array[a];
				array[a] = array[max];
				array[max] = temp;
				a = max;
			}
		}
		if( a == prev_a ) {
			i--;
			a = i;
		}
	}
	return 0;
}

int heapsort( int *array, int size ) {

	int *a = ( int* )malloc( sizeof(int) * size );
	
	for( int i = 0; i < size; i++ ) {
		*(a+i) = *(array+i);
	}
	printf( "////////////////////////////////////////\n" );
	printf( "// heap sort start\n" );
	disp( a , size );
	
	for( int i = size; i > 0; i-- ) {
		make_heap( a, i );
		int temp = a[i-1];
		a[i-1] = a[0];
		a[0] = temp;
	}
	
	printf( "// result\n" );
	disp( a , size );
	free( a );
	
	return 0;
}

//
// main
//

int main( int argc, void ** argv ) {
	int array_count = 20;
	int *array = makeArray( array_count );
	if( !array )
		return 0;
	
	quicksort( array, array_count );
	mergesort( array, array_count );
	heapsort( array, array_count );
	
	free( array );
	return 0;
}
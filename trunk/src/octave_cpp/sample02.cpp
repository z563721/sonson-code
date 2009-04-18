// 
// octave_cpp
// sample02.cpp
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
//#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <octave/config.h>
#include <octave/Matrix.h>
#include <octave/EIG.h>
#include <octave/CDiagMatrix.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// main

int main ( int argc, char **argv ) {
	
	cout << "Complex・・・複素数" << endl;
	Complex x(1,0);
	cout << "Complex = " << endl << x << endl;
	
	cout << "inverse・・・逆行列" << endl;
	Matrix m_inverse(3, 3);
	m_inverse(0,0) = 3;m_inverse(0,1) = 1;m_inverse(0,2) = 4;
	m_inverse(1,0) = 2;m_inverse(1,1) = 0;m_inverse(1,2) = 2;
	m_inverse(2,0) = 3;m_inverse(2,1) = 3;m_inverse(2,2) = 2;
	cout << "Original Matrix" << endl <<  m_inverse << endl;
	cout << "Inverse Matrix" << endl << m_inverse.inverse() << endl;
	cout << "Recomposed Matrix" << endl <<  m_inverse.inverse()*m_inverse << endl;
	
	cout << "eigen・・・固有値" << endl;
	Matrix m_eigen(3, 3);
	m_eigen(0,0) = 3;m_eigen(0,1) = 2;m_eigen(0,2) = 2;
	m_eigen(1,0) = 2;m_eigen(1,1) = 0;m_eigen(0,2) = 1;
	m_eigen(2,0) = 2;m_eigen(2,1) = 0;m_eigen(2,2) = 2;
	cout << "Original Matrix" << endl <<  m_eigen << endl;
	EIG eig(m_eigen);
	cout << "Eigen Vectors" << endl <<  eig.eigenvectors() << endl;
	cout << "Eigen Values" << endl <<  eig.eigenvalues() << endl;
	cout << "Recomposed Matrix" << endl << eig.eigenvectors()*ComplexMatrix(ComplexDiagMatrix(eig.eigenvalues()))*eig.eigenvectors().inverse() << endl;
	
	cout << "singular・・・特異値" << endl;
	Matrix m_singular(2, 3);
	m_singular(0,0) = 3;m_singular(0,1) = 1;m_singular(0,2) = 4;
	m_singular(1,0) = 2;m_singular(1,1) = 0;m_singular(1,2) = 2;
	cout << "Original Matrix" << endl <<  m_singular << endl;
	SVD svd(m_singular);
	cout << "Left Singular Matrix" << endl <<  svd.left_singular_matrix() << endl;
	cout << "Singular Values" << endl <<  svd.singular_values() << endl;
	cout << "Right Singular Matrix" << endl <<  svd.right_singular_matrix() << endl;
	cout << "Recomposed Matrix" << endl << svd.left_singular_matrix() * Matrix(DiagMatrix(svd.singular_values())) * svd.right_singular_matrix() << endl;

	return 0;
}
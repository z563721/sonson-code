// 
// gflags
// gflags_test.cpp
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
//#include <string>#include <stdio.h>#include <stdlib.h>#include "hoge.h"#include "google/gflags.h"// definition for argumentsDEFINE_bool(flagBool, false, "Bool type flag");DEFINE_int32(flagInt32, 0, "Int 32 type flag");DEFINE_int64(flagInt64, 0, "Int 64 type flag");DEFINE_uint64(flagUint64, 0, "Unsigned int 64 type flag");DEFINE_double(flagDouble, 0, "Double type flag");DEFINE_string(flagString, "default string", "String type flag");// mainint main ( int argc, char **argv ) {	google::ParseCommandLineFlags(&argc, &argv, true);		if( FLAGS_flagBool )		printf( "flagBool\n" );			printf( "%d\n", FLAGS_flagInt32 );			printf( "%d\n", FLAGS_flagInt64 );		printf( "%d\n", FLAGS_flagUint64 );			printf( "%lf\n", FLAGS_flagDouble );	printf( "%s\n", FLAGS_flagString.c_str() );		hoge(0);		return 0;}
// 
// thinning
// imgtool.h
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
//#include <string.h>#include <stdio.h>#include <stdlib.h>#include <magick/api.h>#ifdef _CH_#pragma package <opencv>#endif#include <opencv/cv.h>#include <opencv/highgui.h>void showRGBPixelsInWindow( unsigned char*pixel, int width, int height );void showGrayPixelsInWindow( unsigned char*pixel, int width, int height );// デフォルトでは，上下左右逆さまでピクセルに配置される．// このフラグでそれを訂正する．//#define __RE_ALIGNE_PIXELS/** * たいていの画像を読み込んでしまう関数 * * - 結果は unsigned char の1次元配列 * - 結果配列は使用者側で解放すること * - 画素のフォーマットを colormap で指定する必要がある *   - colormap は R,G,B,A,C,Y,M,K,I の任意の組み合わせ *   - ふつう，PPM ファイルなら colormap = "RGB" *   - R だけほしければ colormap = "R" とすればよい * * @param filename [in] ファイル名 * @param width [out] 読み込んだ画像の横サイズ * @param height [out] 読み込んだ画像の縦サイズ * @param colormap [in] 取得する画素形式 * @return 成功したときは得られた1次元配列の先頭へのポインタを，失敗したときはNULLを返す */unsigned char * magick_read(const char * filename, int * width, int *height, const char * colormap);/** * たいていの画像形式で書き込んでしまう関数 * * - 渡すデータは unsigned char の1次元配列 * - 渡すデータのフォーマットを colormap で指定する必要がある *	 - colormap は R,G,B,A,C,Y,M,K,I の任意の組み合わせ *	 - R,G,B 8bit ずつのデータなら colormap = "RGB" * * @param filename [in] ファイル名 * @param data [in] 画像データ * @param width [in] 画像の横サイズ * @param height [in] 画像の縦サイズ * @param colormap [in] 渡したデータの画素形式 * @return 成功したときは0を返す */int magick_write(const char * filename, unsigned char * data, int width, int height, const char * colormap);
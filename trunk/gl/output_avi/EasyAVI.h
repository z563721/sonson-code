// 
// output_avi
// EasyAVI.h
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
///*********************************************************
	"EasyAVI.h"			2001/6/19 (c)小紅

【プログラムの説明】
AVIの作成に関する処理をクラス化したものです。
"Microsoft Visual C++ 6.0"の環境に合わせて作成しています。
他の環境の場合は、一部変更を加える必要があるかもしれません。

【主な関数の説明】
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
EasyAVI()

動作:
new を使ってEasyAVIクラスが作成された時必ず呼び出される関数です。
各種変数を初期化します。
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
~EasyAVI()

動作:
delete を使ってEasyAVIクラスが削除された時呼び出される関数です。
各種変数を開放します。
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
Start(HWND hWnd,int width,int height,const char* file,int scale,int rate)

引数: 
hWnd	作成した画像を描画したいウィンドのハンドルです。
		NULLを入れるとディスプレイが指定されます。
width	作成したいAVIの幅です。
height	作成したいAVIの高さです。
file	作成したいAVIのファイル名です。
scale	作成したいAVIの時間単位です。
rate	作成したいAVIのレートです。
		フレームレートは"step"秒間に"rate"フレームとなります。

動作:
録画の前準備を行います。
なお、使用後カレントディレクトリが変化している可能性があります。

返り値:
作成されたメモリコンテキストデバイスのハンドルが返されます。
このメモリコンテキストデバイスに描きこんだ内容が、
Save()を行うことによってAVIに追加されます。
失敗したときの返り値はNULLです。
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
Save()
引数:
ありません。

動作:
Startで返したHDCの内容をAVIに追加します。

返り値:
成功すれば true 、失敗すれば false を返します。
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
Clear()
引数:
ありません。

動作:
各種メモリを開放します。
この関数の中でStartで開かれたファイルを閉じています。
そのためこの関数が呼ばれた以降はAVIファイルにフレームの追加は出来ません。

返り値:
ありません。
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
GetBuf(),GetHBITMAP(),GetWidth,GetHeight(),GetHDC();
動作:
名前から推測してください。

【このプログラムの使用について】
以下のことを守る限り使用は自由です。
改造も自由です。

 1. 悪用しない。（どうすれば悪用できるのか分かりませんが・・・）
 2. 他人がこのソースを使用するのを妨げない。
 3. 各人の責任の元に使用する。

ちなみに2.に関しては
「勝手に著作権を主張した挙句『このソースは流用禁止！』とか言うな。」
という意味です。
別にソースの出典や著作権の有無をどうのこうの言う義務はありません。
「オープンソースにしろ！」とも言いません。
ただ、他の人がこれを使用するのを妨げるような行為は行うなと言う意味です。
こっそりと使う分には全く問題ありませんし、オンラインに公開するのも勝手です。
これを利用したソフトをフリーやシェアで流すのも全くの自由です。

後、このソースは有用であるとは思いますが、絶対であるとは思いません。
だから何処かにバグが存在しているかもしれませんし、
何らかの悪影響を及ぼす可能性もあります。
しかしそのようなことになっても、私は一切責任は持ちません。
使用は各人の責任の元に行ってください。

【更新履歴】
2001/6/19
	動画を圧縮して保存できるようになった。
**********************************************************/
#ifndef _INCLUDE_EASYAVI_
#define _INCLUDE_EASYAVI_

//Vfw32.libをリンクします
#pragma comment(lib,"Vfw32.lib")
#include <windows.h>
#include <direct.h>
#include <vfw.h>
class EasyAVI{
public:
	EasyAVI();
	~EasyAVI();
	//録画の前準備
	HDC Start(HWND,unsigned int,unsigned int,const char*,DWORD,DWORD);
	//取り込んだ画像をAVIファイルに付け足す
	bool Save(void);
	//HDC等をすべて開放
	void Clear(void);
	//lpBmpを取得
	LPVOID GetBuf(void);
	//hBmpを取得
	HBITMAP GetHBITMAP(void);
	//幅を取得
	unsigned int GetWidth(void);
	//高さを取得
	unsigned int GetHeight(void);
	//hMemDCを取得
	HDC GetHDC(void);
	HDC SetBits(LPBITMAPINFOHEADER);
	//ストリームを保存していく
	bool SaveStream(PAVISTREAM);
private:
	LPVOID lpBmp;
	HBITMAP hBmp;
	HBITMAP hBmpOld;
	HDC hMemDC;
	PAVISTREAM pstm,ptmp;
	PAVIFILE pavi;
	COMPVARS cv;
	AVICOMPRESSOPTIONS opt;
	unsigned int nWidth,nHeight,nSize;
	unsigned int pos;
};
EasyAVI::EasyAVI()
{
	lpBmp = NULL;
	hBmp = NULL;
	hMemDC = NULL;
	pstm = NULL;
	ptmp = NULL;
	pavi = NULL;
	nWidth = nHeight = nSize = 0;
	pos = 0;

}
EasyAVI::~EasyAVI()
{
	Clear();
}
HDC EasyAVI::Start(HWND hWnd,unsigned int width,unsigned int height,const char* file,DWORD scale,DWORD rate)
{
	//まずは初期化
	Clear();

	//各種変数に値を入れる
	nWidth = width;
	nHeight = height;
	nSize = (((nWidth*24+31)&~31)/8)*nHeight;

	HDC hDC;
	BITMAPINFOHEADER bmih={sizeof(BITMAPINFOHEADER),nWidth
		,nHeight,1,24,BI_RGB
		,nSize
		,0,0,0,0};
	AVISTREAMINFO si={streamtypeVIDEO,comptypeDIB,0,0,0,0,
						scale,rate,0,0,0,0,(DWORD)-1,0,{0,0,nWidth,nHeight},0,0,"VIDEO"};


	AVIFileInit();

	memset(&cv,0,sizeof(COMPVARS));
	cv.cbSize=sizeof(COMPVARS);
	cv.dwFlags=ICMF_COMPVARS_VALID;
	cv.fccHandler=comptypeDIB;
	cv.lQ=ICQUALITY_DEFAULT;

	if (!ICCompressorChoose(NULL,ICMF_CHOOSE_DATARATE | ICMF_CHOOSE_KEYFRAME,
		&bmih,NULL,&cv,NULL)){
		AVIFileExit();
		return NULL;
	}

	si.fccHandler=cv.fccHandler;
	opt.fccType=streamtypeVIDEO;
	opt.fccHandler=cv.fccHandler;
	opt.dwKeyFrameEvery=cv.lKey;
	opt.dwQuality=cv.lQ;
	opt.dwBytesPerSecond=cv.lDataRate;
	opt.dwFlags=(cv.lDataRate>0?AVICOMPRESSF_DATARATE:0)
		|(cv.lKey>0?AVICOMPRESSF_KEYFRAMES:0);
	opt.lpFormat=NULL;
	opt.cbFormat=0;
	opt.lpParms=cv.lpState;
	opt.cbParms=cv.cbState;
	opt.dwInterleaveEvery=0;

//#define MOVE_CURRENT
#ifdef MOVE_CURRENT
	//OSによってはしばしばよそのディレクトリを指定できないことがあります
	//そのときは上の"#define MOVE_CURRENT"のコメントアウトをはずしてください
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char name[_MAX_FNAME+4];
	_splitpath(file,drive,dir,name,NULL);
		
	//ディレクトリとドライブの移動
	_chdrive(drive[0]-'A'+1);
	_chdir(dir);
	strcat(name,".AVI");

	if (AVIFileOpen(&pavi,name,OF_CREATE
		| OF_WRITE | OF_SHARE_DENY_NONE,NULL)!=0) {
		MessageBox(hWnd,"保存するファイルが開けませんでしたわ。","こまりましたわ",MB_OK);
		AVIFileExit();
		return NULL;
	}
#else
	if (AVIFileOpen(&pavi,file,OF_CREATE
		| OF_WRITE | OF_SHARE_DENY_NONE,NULL)!=0) {
		MessageBox(hWnd,"保存するファイルが開けませんでしたわ。","こまりましたわ",MB_OK);
		AVIFileExit();
		return NULL;
	}
#endif

	if (AVIFileCreateStream(pavi,&pstm,&si)!=0) {
		MessageBox(hWnd,"編集用ストリームが作られませんでしたわ。","こまりましたわ",MB_OK);
		AVIFileRelease(pavi);
		pavi = NULL;
		AVIFileExit();
		return NULL;
	}
	
	if (AVIMakeCompressedStream(&ptmp,pstm,&opt,NULL)!=AVIERR_OK){
		MessageBox(hWnd,"圧縮ストリームの作成に失敗しました。","たいへんですわ",MB_OK);
		AVIStreamRelease(pstm);
		pstm = NULL;
		AVIFileRelease(pavi);
		pavi=NULL;
		AVIFileExit();
		return NULL;
	}

	//ストリームのフォーマットを設定しますわ
    if(AVIStreamSetFormat(ptmp,0,&bmih,sizeof(BITMAPINFOHEADER))!=0){
		MessageBox(hWnd,"ストリームのフォーマットを設定するのに失敗しましたわ。","たいへんですわ",MB_OK);
		AVIStreamRelease(pstm);
		pstm = NULL;
		AVIStreamRelease(ptmp);
		ptmp = NULL;
		AVIFileRelease(pavi);
		pavi=NULL;
		AVIFileExit();
		return NULL;
	}
	


	if ((hDC=GetDC(hWnd))==NULL) {
		MessageBox(hWnd,"HDCが取得できませんでしたわ。","たいへんですわ",MB_OK);
		AVIStreamRelease(pstm);
		pstm = NULL;
		AVIFileRelease(pavi);
		pavi=NULL;
		AVIFileExit();
		return NULL;
	}

	if ((hMemDC=CreateCompatibleDC(hDC))==NULL) {
		MessageBox(hWnd,"メモリDCが作れませんでしたわ。","たいへんですわ",MB_OK);
		AVIStreamRelease(pstm);
		pstm = NULL;
		AVIFileRelease(pavi);
		pavi=NULL;
		ReleaseDC(NULL,hDC);
		AVIFileExit();
		return NULL;
	}

	if (ReleaseDC(hWnd,hDC)!=1) {
		MessageBox(hWnd,"HDCを開放できませんでしたわ。","たいへんですわ",MB_OK);
		AVIStreamRelease(pstm);
		pstm = NULL;
		AVIFileRelease(pavi);
		pavi=NULL;
		DeleteDC(hMemDC);
		hMemDC = NULL;
		AVIFileExit();
		return NULL;
	}

	hBmp = CreateDIBSection(hMemDC,(LPBITMAPINFO)&bmih,DIB_RGB_COLORS,&lpBmp,NULL,0);
	
	if(hBmp==NULL){
		MessageBox(hWnd,"HBITMAPが作れませんでしたわ。","たいへんですわ",MB_OK);
		AVIStreamRelease(pstm);
		pstm = NULL;
		AVIFileRelease(pavi);
		pavi=NULL;
		DeleteDC(hMemDC);
		hMemDC = NULL;
		AVIFileExit();
		return NULL;
	}

	hBmpOld = (HBITMAP)SelectObject(hMemDC,hBmp);

	return hMemDC;
}
bool EasyAVI::Save(void)
{
	if(pstm==NULL||lpBmp==NULL){
		return false;
	}
	if (AVIStreamWrite(ptmp,pos++,1,lpBmp,nSize,AVIIF_KEYFRAME,NULL,NULL)!=0) {
		return false;
	}
	return true;
}
void EasyAVI::Clear(void)
{
	if(ptmp!=NULL){
		AVIStreamRelease(ptmp);
		ptmp = NULL;
	}

	if(pstm!=NULL){
		AVIStreamRelease(pstm);
		pstm = NULL;
	}
	if (pavi!=NULL) {
		AVIFileRelease(pavi);
		pavi=NULL;
	}
	if (hBmp!=NULL) {
		DeleteObject(SelectObject(hMemDC,hBmpOld));
		hBmp=NULL;
	}
	if (hMemDC!=NULL) {
		DeleteDC(hMemDC);
		hMemDC = NULL;
	}
	ICCompressorFree(&cv);
	lpBmp = NULL;
	pos = 0;
	AVIFileExit();
}
LPVOID EasyAVI::GetBuf(void)
{
	return lpBmp;
}
HBITMAP EasyAVI::GetHBITMAP(void)
{
	return hBmp;
}
unsigned int EasyAVI::GetHeight(void)
{
	return nHeight;
}
unsigned int EasyAVI::GetWidth(void)
{
	return nWidth;
}
HDC EasyAVI::GetHDC(void)
{
	return hMemDC;
}
HDC EasyAVI::SetBits(LPBITMAPINFOHEADER pbmih)
{
	LPBYTE bits = ((LPBYTE)pbmih) + sizeof(BITMAPINFOHEADER);

	if (pbmih->biClrUsed==0){
		switch (pbmih->biBitCount) {
			case  1:bits += sizeof(RGBQUAD)*2;break;
			case  4:bits += sizeof(RGBQUAD)*16;break;
			case  8:bits += sizeof(RGBQUAD)*256;break;
			case 24:bits += 0;break;
			case 16:
			case 32:
				bits += (pbmih->biCompression==BI_RGB?0:sizeof(DWORD)*3);
		}
	}else{
			bits += pbmih->biClrUsed*sizeof(RGBQUAD);
	}

	SetDIBits(hMemDC,hBmp,0,pbmih->biHeight,(void*)bits,(LPBITMAPINFO)pbmih,DIB_RGB_COLORS);
	return hMemDC;
}
#endif
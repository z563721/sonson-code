// 
// Binarize
// Binarize.cpp
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
//// Binarize.cpp : Ax 用の初期化処理の定義を行います。
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// DirectShow用
#include <streams.h>
#include <initguid.h>
#include <math.h>

#include "Binarize.h"

// {F75623B6-AD0E-4897-AC46-70CBF680417E}
static const GUID CLSID_Binarize = {0xf75623b6,0xad0e,0x4897,{0xac,0x46,0x70,0xcb,0xf6,0x80,0x41,0x7e}};

// 入力ピンのメディアタイプ
// 必要に応じて変更する
const AMOVIESETUP_MEDIATYPE sudIPinTypes =
{
	&MEDIATYPE_Video,		// Major type
	&MEDIASUBTYPE_NULL		// Minor type
};

//////////////////////////////////////////////////////////////////////
// 出力ピンのメディアタイプ
// 必要に応じて変更する
const AMOVIESETUP_MEDIATYPE sudOPinTypes =
{
	&MEDIATYPE_Video,		// Major type
	&MEDIASUBTYPE_NULL		// Minor type
};

//////////////////////////////////////////////////////////////////////
// ピン構成情報
const AMOVIESETUP_PIN sudpPins[] =
{
	{
		L"Input",			// Pins string name
		FALSE,				// Is it rendered
		FALSE,				// Is it an output
		FALSE,				// Are we allowed none
		FALSE,				// And allowed many
		&CLSID_NULL,		// Connects to filter
		NULL,				// Connects to pin
		1,					// Number of types
		&sudIPinTypes		// Pin information
	},
	{
		L"Output",			// Pins string name
		FALSE,				// Is it rendered
		TRUE,				// Is it an output
		FALSE,				// Are we allowed none
		FALSE,				// And allowed many
		&CLSID_NULL,		// Connects to filter
		NULL,				// Connects to pin
		1,					// Number of types
		&sudOPinTypes		// Pin information
	}
};

//////////////////////////////////////////////////////////////////////
// フィルタ設定
const AMOVIESETUP_FILTER sudBinarize =
{
	&CLSID_Binarize,		// clsID
	L"Binarize",			// strName
	MERIT_DO_NOT_USE,	// dwMerit
	2,					// nPins
	sudpPins			// lpPin
};

//////////////////////////////////////////////////////////////////////
CFactoryTemplate g_Templates[] = {
	{
	L"Binarize"
	, &CLSID_Binarize
	, Binarize::CreateInstance
	, NULL
	, &sudBinarize
	}
};

//////////////////////////////////////////////////////////////////////
int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]);

//////////////////////////////////////////////////////////////////////
// レジストリへの登録
STDAPI DllRegisterServer()
{
    return AMovieDllRegisterServer2( TRUE );

}

//////////////////////////////////////////////////////////////////////
// レジストリからの解除
STDAPI DllUnregisterServer()
{
    return AMovieDllRegisterServer2( FALSE );

}

//////////////////////////////////////////////////////////////////////
// Binarize クラス
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// コンストラクタ
Binarize::Binarize(TCHAR *tszName, LPUNKNOWN pUnk, HRESULT *phr) :
    CTransformFilter(tszName, pUnk, CLSID_Binarize)
{
}
//////////////////////////////////////////////////////////////////////
// デストラクタ
Binarize::~Binarize()
{
}
//////////////////////////////////////////////////////////////////////
// インスタンスの生成
CUnknown *Binarize::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
    Binarize *pNewObject = new Binarize(NAME("Binarize filter"), punk, phr);
    if (pNewObject == NULL) {
        *phr = E_OUTOFMEMORY;
    }
    return pNewObject;
}
//////////////////////////////////////////////////////////////////////
// 入力ピンのメディアタイプチェック
HRESULT Binarize::CheckInputType(const CMediaType *mtIn)
{
   CheckPointer(mtIn,E_POINTER);

    // check this is a VIDEOINFOHEADER type

    if (*mtIn->FormatType() != FORMAT_VideoInfo) {
        return E_INVALIDARG;
    }

    // Can we transform this type

    if (CheckMediaType(mtIn)) {
        return NOERROR;
    }
    return E_FAIL;
}
//////////////////////////////////////////////////////////////////////
// 出力ピンのメディアタイプチェック
HRESULT Binarize::CheckTransform(const CMediaType *mtIn, const CMediaType *mtOut)
{
	// この場所でoutputピンが接続できるメディアタイプかチェックする
	CheckPointer(mtIn,E_POINTER);
	CheckPointer(mtOut,E_POINTER);
	if (*mtIn == *mtOut)
		return NOERROR;

	return E_FAIL;
}
//////////////////////////////////////////////////////////////////////
// このフィルタで使用できるフォーマットかをチェックする
BOOL Binarize::CheckMediaType(const CMediaType *pMediaType) const
{
	// ポインタのチェック
    CheckPointer(pMediaType,FALSE);
	// メディアタイプのチェック
    if (IsEqualGUID(*pMediaType->Type(), MEDIATYPE_Video)) 
    {
        if (IsEqualGUID(*pMediaType->Subtype(), MEDIASUBTYPE_RGB24)) 
        {
            VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *) pMediaType->Format();
            return (pvi->bmiHeader.biBitCount == 24);
        }
    }
    return FALSE;
}

//////////////////////////////////////////////////////////////////////
// フィルタ内部の処理
HRESULT Binarize::Transform(IMediaSample *pIn, IMediaSample *pOut){
	// InをOutにコピーして出力
	HRESULT hr = Copy(pIn, pOut);
    if (FAILED(hr)) {
        return hr;
    }
	BinarizeOutput(pOut);
    return NOERROR;
}

//////////////////////////////////////////////////////////////////////
// バッファサイズを決める
HRESULT Binarize::DecideBufferSize(
				IMemAllocator *pAlloc,ALLOCATOR_PROPERTIES *pProperties)
{
	// データ変換に必要なバッファサイズを設定する    
    if (m_pInput->IsConnected() == FALSE) {
        return E_UNEXPECTED;
    }

    CheckPointer(pAlloc,E_POINTER);
    CheckPointer(pProperties,E_POINTER);
    HRESULT hr = NOERROR;

    pProperties->cBuffers = 1;
    pProperties->cbBuffer = m_pInput->CurrentMediaType().GetSampleSize();
    ASSERT(pProperties->cbBuffer);

    // Ask the allocator to reserve us some sample memory, NOTE the function
    // can succeed (that is return NOERROR) but still not have allocated the
    // memory that we requested, so we must check we got whatever we wanted

    ALLOCATOR_PROPERTIES Actual;
    hr = pAlloc->SetProperties(pProperties,&Actual);
    if (FAILED(hr)) {
        return hr;
    }

    ASSERT( Actual.cBuffers == 1 );

    if (pProperties->cBuffers > Actual.cBuffers ||
            pProperties->cbBuffer > Actual.cbBuffer) {
                return E_FAIL;
    }
    return NOERROR;
}
//////////////////////////////////////////////////////////////////////
// このフィルタのアウトピンが接続可能なメディアのタイプを返す
HRESULT Binarize::GetMediaType(int iPosition, CMediaType *pMediaType)
{
	// outputピンが対応するメディアタイプを返す    
    if (m_pInput->IsConnected() == FALSE) {
        return E_UNEXPECTED;
    }

    // ピンの位置のチェック

    if (iPosition < 0) {
        return E_INVALIDARG;
    }
    if (iPosition > 0) {
        return VFW_S_NO_MORE_ITEMS;
    }

	// ピンをチェック
    CheckPointer(pMediaType,E_POINTER);
    *pMediaType = m_pInput->CurrentMediaType();

    return NOERROR;
}

// ピクセルひとつの値をHSVに変換する
unsigned char pixelRGB2HSV2( double red, double green, double blue){
	double y,c1,c2;
	double h; double s;double v;
	// YCCへ変換
	y = 0.299*red + 0.587*green + 0.114*blue;	
	c1= red -y;									
	c2= blue-y;
	if( c2 ==0 ){
		h=0;
	}
	if( c2>0 ){
		if( c1>=0)
			h = atan(c1/c2)*180.0/3.14;
		else
			h = 360.0 - atan(fabs(c1)/c2)*180.0/3.141519;
	}
	else{
		if( c1>=0)
			h = 180.0 - atan(c1/fabs(c2))*180.0/3.141519;
		else
			h = 180.0 + atan(fabs(c1/c2))*180.0/3.141519;
	}
	if( h < 0 )
		h += 360;
	// 処理用の値に直す
	s = sqrt( c1*c1 + c2*c2 );
	h -= 113.09;
	h = h*255.0/360.0;
	v=y;
	return (unsigned char)v;
}
//////////////////////////////////////////////////////////////////////
// フィルタ内部で行った入力を出力に返す処理
HRESULT Binarize::BinarizeOutput(IMediaSample *pOut){
	
	BYTE *oData;

	AM_MEDIA_TYPE* pType = &m_pInput->CurrentMediaType();
    VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *) pType->pbFormat;
    ASSERT(pvi);

    CheckPointer(pOut,E_POINTER);
    pOut->GetPointer(&oData);

    // Get the image properties from the BITMAPINFOHEADER

    int cxImage    = pvi->bmiHeader.biWidth;
    int cyImage    = pvi->bmiHeader.biHeight;
    int numPixels  = cxImage * cyImage;
	int iPixel;

	BYTE v;

    RGBTRIPLE *orgb=(RGBTRIPLE*) oData;            // Holds a pointer to the current pixel
	for (iPixel=0; iPixel < numPixels; iPixel++, orgb++) {
		v = pixelRGB2HSV2( orgb->rgbtRed, orgb->rgbtGreen, orgb->rgbtBlue);

		if( v < 50 ){
			orgb->rgbtRed = 0;
			orgb->rgbtGreen =0;
			orgb->rgbtBlue =0;
		}
		else{
			orgb->rgbtRed = 255;
			orgb->rgbtGreen =255;
			orgb->rgbtBlue =255;
		}
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// フィルタ内部で行った入力を出力に返す処理
HRESULT Binarize::Copy(IMediaSample *pSource, IMediaSample *pDest) const
{
	// バッファの確保
    BYTE *pSourceBuffer, *pDestBuffer;
    long lSourceSize = pSource->GetActualDataLength();
    long lDestSize	= pDest->GetSize();

    ASSERT(lDestSize >= lSourceSize);

	// 入力側のメディア情報から画像データのポインタを取得
    pSource->GetPointer(&pSourceBuffer);
	// 出力側のメディア情報から画像データのポインタを取得
    pDest->GetPointer(&pDestBuffer);

	// データをコピー
    CopyMemory( (PVOID) pDestBuffer,(PVOID) pSourceBuffer,lSourceSize);
/*
    DbgLog((LOG_TRACE,4,TEXT("CopyMemory::dest=%#x,source=%#x"),
    									pDestBuffer,pSourceBuffer));
*/
    // サンプリングタイムをコピーする．
    REFERENCE_TIME TimeStart, TimeEnd;
    if (NOERROR == pSource->GetTime(&TimeStart, &TimeEnd)) {
        pDest->SetTime(&TimeStart, &TimeEnd);
    }
	// メディアのタイミング情報をコピーする
    LONGLONG MediaStart, MediaEnd;
    if (pSource->GetMediaTime(&MediaStart,&MediaEnd) == NOERROR) {
        pDest->SetMediaTime(&MediaStart,&MediaEnd);
    }

    // 同期用のポイントを設定する．
    HRESULT hResult = pSource->IsSyncPoint();
    if (hResult == S_OK) {
        pDest->SetSyncPoint(TRUE);
    }
    else if (hResult == S_FALSE) {
        pDest->SetSyncPoint(FALSE);
    }
    else {  // an unexpected error has occured...
        return E_UNEXPECTED;
    }

    // 入力ピン側のメディアタイプを出力側のメディアタイプへコピーする
    AM_MEDIA_TYPE *pMediaType;
    pSource->GetMediaType(&pMediaType);
    pDest->SetMediaType(pMediaType);
    DeleteMediaType(pMediaType);

    // Prerollのチェック
    hResult = pSource->IsPreroll();
    if (hResult == S_OK) {
        pDest->SetPreroll(TRUE);
    }
    else if (hResult == S_FALSE) {
        pDest->SetPreroll(FALSE);
    }
    else {  // an unexpected error has occured...
        return E_UNEXPECTED;
    }

    // 連続性のチェックとコピー
    hResult = pSource->IsDiscontinuity();
    if (hResult == S_OK) {
	pDest->SetDiscontinuity(TRUE);
    }
    else if (hResult == S_FALSE) {
        pDest->SetDiscontinuity(FALSE);
    }
    else {  // an unexpected error has occured...
        return E_UNEXPECTED;
    }

    // 実際の画像のデータの長さをコピーする
    long lDataLength = pSource->GetActualDataLength();
    pDest->SetActualDataLength(lDataLength);

    return NOERROR;

}
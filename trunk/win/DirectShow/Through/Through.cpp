// 
// Through
// Through.cpp
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
//// Through.cpp : Ax 用の初期化処理の定義を行います。
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// DirectShow用
#include <streams.h>
#include <initguid.h>

#include <math.h>
#include "Through.h"

//////////////////////////////////////////////////////////////////////
// {52868D02-17B3-4373-AEE2-8C4FE1A2CCB6}
static const GUID CLSID_Through = { 0x52868d02, 0x17b3, 0x4373, { 0xae, 0xe2, 0x8c, 0x4f, 0xe1, 0xa2, 0xcc, 0xb6 } };


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
const AMOVIESETUP_FILTER sudThrough =
{
	&CLSID_Through,		// clsID
	L"Through",			// strName
	MERIT_DO_NOT_USE,	// dwMerit
	2,					// nPins
	sudpPins			// lpPin
};

//////////////////////////////////////////////////////////////////////
CFactoryTemplate g_Templates[] = {
	{
	L"Through"
	, &CLSID_Through
	, Through::CreateInstance
	, NULL
	, &sudThrough
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
// Through クラス
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// コンストラクタ
Through::Through(TCHAR *tszName, LPUNKNOWN pUnk, HRESULT *phr) :
    CTransformFilter(tszName, pUnk, CLSID_Through)
{
}
//////////////////////////////////////////////////////////////////////
// デストラクタ
Through::~Through()
{
}
//////////////////////////////////////////////////////////////////////
// インスタンスの生成
CUnknown *Through::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
    Through *pNewObject = new Through(NAME("Through filter"), punk, phr);
    if (pNewObject == NULL) {
        *phr = E_OUTOFMEMORY;
    }
    return pNewObject;
}
//////////////////////////////////////////////////////////////////////
// 入力ピンのメディアタイプチェック
HRESULT Through::CheckInputType(const CMediaType *mtIn)
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
HRESULT Through::CheckTransform(const CMediaType *mtIn, const CMediaType *mtOut)
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
BOOL Through::CheckMediaType(const CMediaType *pMediaType) const
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
HRESULT Through::Transform(IMediaSample *pIn, IMediaSample *pOut){
	// InをOutにコピーして出力
	HRESULT hr = Copy(pIn, pOut);
    if (FAILED(hr)) {
        return hr;
    }  
    return NOERROR;
}
//////////////////////////////////////////////////////////////////////
// バッファサイズを決める
HRESULT Through::DecideBufferSize(
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
HRESULT Through::GetMediaType(int iPosition, CMediaType *pMediaType)
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
//////////////////////////////////////////////////////////////////////
// フィルタ内部で行った入力を出力に返す処理
HRESULT Through::Copy(IMediaSample *pSource, IMediaSample *pDest) const
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
// 
// SkeltonMFC
// DirectShowSkeltonMFCView.h
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
//// DirectShowSkeltonMFCView.h : CDirectShowSkeltonMFCView クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTSHOWSKELTONMFCVIEW_H__A53B3383_FCC4_46A8_86BD_B80C586C3070__INCLUDED_)
#define AFX_DIRECTSHOWSKELTONMFCVIEW_H__A53B3383_FCC4_46A8_86BD_B80C586C3070__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dshow.h>

//////////////////////////////////////////////////////////////////////
// {52868D02-17B3-4373-AEE2-8C4FE1A2CCB6}
const GUID CLSID_Through = { 0x52868d02, 0x17b3, 0x4373, { 0xae, 0xe2, 0x8c, 0x4f, 0xe1, 0xa2, 0xcc, 0xb6 } };

class CDirectShowSkeltonMFCView : public CView
{
protected: // シリアライズ機能のみから作成します。
	CDirectShowSkeltonMFCView();
	DECLARE_DYNCREATE(CDirectShowSkeltonMFCView)

// アトリビュート
public:
	CDirectShowSkeltonMFCDoc* GetDocument();

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDirectShowSkeltonMFCView)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

private:
	IGraphBuilder			*m_pGraph;				// グラフ ビルダ
	IMediaControl			*m_pMediaCtrl;			// メディア コントロール
	IVideoWindow			*m_pVideoWindow;		// 描画用のウィンドウ
	ICaptureGraphBuilder2	*m_pBuilder;			// キャプチャビルダー
	IMediaEventEx			*m_pMediaEvent;			// メディアイベント

	IBaseFilter				*m_pSrc;				// ソース
	IBaseFilter				*m_pVideoRenderer;		// レンダラ

	IBaseFilter				*m_pThrough;			// このプログラムでつかうフィルタ

	// DirectShowフィルタの作成
	BOOL					CreateFilters(void);
	// DirectShowフィルタの接続
	BOOL					ConectFilters(void);
	// DirectShow描画領域の設定
	BOOL					SetWindow(void);
	// DirectShowフィルタの解放
	BOOL					ReleaseAll(void);
	// DirectShowキャプチャデバイスの取得と列挙
	BOOL					GetCaptureDevice(IBaseFilter **ppSrcFilter);
	// DirectShowの初期化
	BOOL					InitializeDirectShow(void);

// インプリメンテーション
public:
	virtual ~CDirectShowSkeltonMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CDirectShowSkeltonMFCView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DirectShowSkeltonMFCView.cpp ファイルがデバッグ環境の時使用されます。
inline CDirectShowSkeltonMFCDoc* CDirectShowSkeltonMFCView::GetDocument()
   { return (CDirectShowSkeltonMFCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DIRECTSHOWSKELTONMFCVIEW_H__A53B3383_FCC4_46A8_86BD_B80C586C3070__INCLUDED_)

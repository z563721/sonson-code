// 
// SkeltonMFC
// DirectShowSkeltonMFCView.cpp
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
//// DirectShowSkeltonMFCView.cpp : CDirectShowSkeltonMFCView クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "DirectShowSkeltonMFC.h"

#include "DirectShowSkeltonMFCDoc.h"
#include "DirectShowSkeltonMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment( lib, "strmBasd.lib" )		// DirectShow
#pragma comment( lib, "Quartz.lib" )		// AMGetErrorText()のために必要

/////////////////////////////////////////////////////////////////////////////
// CDirectShowSkeltonMFCView

IMPLEMENT_DYNCREATE(CDirectShowSkeltonMFCView, CView)

BEGIN_MESSAGE_MAP(CDirectShowSkeltonMFCView, CView)
	//{{AFX_MSG_MAP(CDirectShowSkeltonMFCView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirectShowSkeltonMFCView クラスの構築/消滅

CDirectShowSkeltonMFCView::CDirectShowSkeltonMFCView()
{
	// TODO: この場所に構築用のコードを追加してください。
	m_pGraph    = NULL;				// グラフ ビルダ
	m_pMediaCtrl = NULL;			// メディア コントロール
	m_pVideoWindow=NULL;			// 描画用のウィンドウ
	m_pBuilder = NULL;				// キャプチャビルダー
	m_pMediaEvent = NULL;			// メディアイベント

	m_pSrc		= NULL;				// ソース
	m_pVideoRenderer = NULL;		// レンダラ

	m_pThrough = NULL;				// このプログラムでつかうフィルタ
}

CDirectShowSkeltonMFCView::~CDirectShowSkeltonMFCView()
{
	ReleaseAll();
	CoUninitialize();		// COMの終了
}

BOOL CDirectShowSkeltonMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDirectShowSkeltonMFCView クラスの描画

void CDirectShowSkeltonMFCView::OnDraw(CDC* pDC)
{
	CDirectShowSkeltonMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	RECT rect;
	this->GetWindowRect(&rect);
	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}

/////////////////////////////////////////////////////////////////////////////
// CDirectShowSkeltonMFCView クラスの診断

#ifdef _DEBUG
void CDirectShowSkeltonMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CDirectShowSkeltonMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDirectShowSkeltonMFCDoc* CDirectShowSkeltonMFCView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDirectShowSkeltonMFCDoc)));
	return (CDirectShowSkeltonMFCDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDirectShowSkeltonMFCView クラスのメッセージ ハンドラ

/////////////////////////////////////////////////////////////////////////////////////////
// 初期化時のメッセージハンドラ
void CDirectShowSkeltonMFCView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// DirectShowの初期化
	if( !InitializeDirectShow()){
		// 初期化失敗
		ReleaseAll();
		CoUninitialize();		// COMの終
		this->MessageBox("DirectShowの初期化に失敗しました．\n強制終了します．","",MB_OK);
		::PostMessage(this->GetParent()->m_hWnd, WM_CLOSE, 0, 0);
								// アプリケーション終了
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
// リサイズのメッセージハンドラ
void CDirectShowSkeltonMFCView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// DirectShowのウィンドウが有効化を調べる
	if( !m_pVideoWindow )return;

	HRESULT hResult;
	// ウィンドウを不可視状態にする
	hResult = m_pVideoWindow->put_Visible(OAFALSE);
	if (hResult != S_OK)return;

	// ウィンドウの場所と大きさをセット
	hResult = m_pVideoWindow->SetWindowPosition(0, 0, cx, cy);
	if (hResult != S_OK)return;

	// ウィンドウを可視状態にする
	hResult = m_pVideoWindow->put_Visible(OATRUE);
	if (hResult != S_OK)return;
	
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShowフィルタの作成
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CDirectShowSkeltonMFCView::CreateFilters(void){
	HRESULT hResult;
	// Throughフィルタのインスタンスを作成
	hResult = CoCreateInstance(CLSID_Through, NULL,
		CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void **)&m_pThrough);
	if (hResult != S_OK)return FALSE;
	// グラフビルダに追加する
	hResult = m_pGraph->AddFilter(m_pThrough, L"Through");
	if (hResult != S_OK)return FALSE;

	// VideoRendererのインスタンスを作成
	hResult = CoCreateInstance(CLSID_VideoRenderer, NULL, 
		CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void **)&m_pVideoRenderer);
	if (hResult != S_OK)return FALSE;
	// グラフビルダに追加する
	hResult = m_pGraph->AddFilter(m_pVideoRenderer, L"Video Renderer");
	if (hResult != S_OK)return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShowフィルタの接続
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CDirectShowSkeltonMFCView::ConectFilters(void){
	HRESULT hResult;
	// ソースのフィルタをThroughフィルタに接続
	hResult = m_pBuilder->RenderStream(&PIN_CATEGORY_CAPTURE,&MEDIATYPE_Video,m_pSrc,0,m_pThrough);
	if (hResult != S_OK)return FALSE;

	// ThroughフィルタをVideoRendererに接続
	hResult = m_pBuilder->RenderStream( 0, &MEDIATYPE_Video, m_pThrough, NULL, m_pVideoRenderer );
	if (hResult != S_OK)return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow描画領域の設定
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CDirectShowSkeltonMFCView::SetWindow(void){
	HRESULT hResult;
	// グラフビルダからウィンドウを取得する
    hResult = m_pGraph->QueryInterface(IID_IVideoWindow, (void **) &m_pVideoWindow);
	if (hResult != S_OK)return FALSE;

	// ウィンドウのオーナーとなるウィンドウのハンドルを指定する
	hResult = m_pVideoWindow->put_Owner( (OAHWND)this->m_hWnd );
	if (hResult != S_OK)return FALSE;

	// ウィンドウのスタイルを指定する
	hResult = m_pVideoWindow->put_WindowStyle(WS_CHILD);
	if (hResult != S_OK)return FALSE;

	// ウィンドウの領域サイズを取得し，書き込む範囲を設定する
	RECT rect;
	this->GetWindowRect(&rect);
	hResult = m_pVideoWindow->SetWindowPosition(0, 0, rect.right-rect.left,rect.bottom-rect.top);
	if (hResult != S_OK)return FALSE;

	// ウィンドウを可視状態にする
	hResult = m_pVideoWindow->put_Visible(OATRUE);
	if (hResult != S_OK)return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShowフィルタの解放
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CDirectShowSkeltonMFCView::ReleaseAll(void){
	if(m_pMediaCtrl)m_pMediaCtrl->Stop();
	if(m_pGraph)m_pGraph->Release();
	if(m_pMediaCtrl)m_pMediaCtrl->Release();
	if(m_pSrc)m_pSrc->Release();
	if(m_pThrough)m_pThrough->Release();
	if(m_pVideoRenderer)m_pVideoRenderer->Release();
	if(m_pBuilder)m_pBuilder->Release();
	if(m_pVideoWindow)m_pVideoWindow->Release();
	if(m_pMediaEvent)m_pMediaEvent->Release();
	
	m_pGraph    = NULL;				// グラフ ビルダ
	m_pMediaCtrl = NULL;			// メディア コントロール
	m_pVideoWindow=NULL;			// 描画用のウィンドウ
	m_pBuilder = NULL;				// キャプチャビルダー
	m_pMediaEvent = NULL;			// メディアイベント

	m_pSrc		= NULL;				// ソース
	m_pVideoRenderer = NULL;		// レンダラ

	m_pThrough = NULL;				// このプログラムでつかうフィルタ
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShowキャプチャデバイスの取得と列挙
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CDirectShowSkeltonMFCView::GetCaptureDevice(IBaseFilter **ppSrcFilter)
{
	HRESULT hResult;

	// デバイスを列挙する
	ICreateDevEnum *pDevEnum = NULL;
	hResult = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC, IID_ICreateDevEnum, (void **)&pDevEnum);
	if (hResult != S_OK)return FALSE;

	// 列挙したデバイスの一番目をデバイスとして取得する
	IEnumMoniker *pClassEnum = NULL;
	hResult = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pClassEnum, 0);
	if (hResult != S_OK)return FALSE;

	// デバイスをフィルタに接続する
	ULONG cFetched;
	IMoniker *pMoniker = NULL;
	if (pClassEnum->Next(1, &pMoniker, &cFetched) == S_OK){
		// 最初のモニカをフィルタオブジェクトにバインドする
		pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void **)ppSrcFilter);
		pMoniker->Release();
	}else
		return FALSE;

	// グラフビルダに追加する
	hResult = m_pGraph->AddFilter(m_pSrc, L"Video Capture");
	if (hResult != S_OK)return FALSE;

	// オブジェクトの片づけ
	pClassEnum->Release();
	pDevEnum->Release();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShowの初期化
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CDirectShowSkeltonMFCView::InitializeDirectShow(void){
	HRESULT		hResult;

	hResult = CoInitialize( NULL );
	// フィルタグラフ作成
	hResult = CoCreateInstance(CLSID_FilterGraph, NULL, 
		CLSCTX_INPROC, IID_IGraphBuilder, (void **)&m_pGraph);
	if (hResult != S_OK)return FALSE;

	// キャプチャデバイス取得
	hResult = GetCaptureDevice(&m_pSrc);
	if (hResult != TRUE)return FALSE;

	// キャプチャビルダの作成
	hResult = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, 
		CLSCTX_INPROC, IID_ICaptureGraphBuilder2, (void **)&m_pBuilder);
	if (hResult != S_OK)return FALSE;

	// グラフにキャプチャビルダをセット
	hResult = m_pBuilder->SetFiltergraph(m_pGraph);
	if (hResult != S_OK)return FALSE;

	// メディアコントロールを取得
	m_pGraph->QueryInterface(IID_IMediaControl, (void **)&m_pMediaCtrl);

	// フィルタの作成
	if( !CreateFilters() )return FALSE;
	// フィルタの接続
	if( !ConectFilters() )return FALSE;
	// ウィンドウのセット
	if( !SetWindow() )return FALSE;
	
	// 処理開始
	hResult = m_pMediaCtrl->Run();
	return TRUE;
}
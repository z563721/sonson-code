// 
// SkeltonSDK
// DirectShowSkeltonSDK.cpp
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
//// DirectShowSkeltonSDK.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"
#include "resource.h"

#define MAX_LOADSTRING 100

#pragma comment( lib, "strmBasd.lib" )		// DirectShow
#pragma comment( lib, "Quartz.lib" )		// AMGetErrorText()のために必要

#include <dShow.h>							// DirectShow必須
#include "DirectShowSkeltonSDK.h"

/////////////////////////////////////////////////////////////////////////////////////////
// グローバル変数:
HINSTANCE hInst;					// 現在のインスタンス
TCHAR szTitle[MAX_LOADSTRING];				// タイトル バー テキスト
TCHAR szWindowClass[MAX_LOADSTRING];			// タイトル バー テキスト

/////////////////////////////////////////////////////////////////////////////////////////
// このコード モジュールに含まれる関数の前宣言:
ATOM				MyRegisterClass( HINSTANCE hInstance );
BOOL				InitInstance( HINSTANCE, int );
LRESULT CALLBACK	WndProc( HWND, UINT, WPARAM, LPARAM );
LRESULT CALLBACK	About( HWND, UINT, WPARAM, LPARAM );

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow関係
IGraphBuilder			*g_pGraph    = NULL;				// グラフ ビルダ
IMediaControl			*g_pMediaCtrl = NULL;				// メディア コントロール
IVideoWindow			*g_pVideoWindow;					// 描画用のウィンドウ
ICaptureGraphBuilder2	*g_pBuilder = NULL;					// キャプチャビルダー
IMediaEventEx			*g_pMediaEvent = NULL;				// メディアイベント

IBaseFilter				*g_pSrc		= NULL;					// ソース
IBaseFilter				*g_pVideoRenderer = NULL;			// レンダラ

IBaseFilter				*g_pThrough = NULL;					// このプログラムでつかうフィルタ

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShowフィルタの作成
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CreateFilters(void){
	HRESULT hResult;
	// Throughフィルタのインスタンスを作成

	hResult = CoCreateInstance(CLSID_Through, NULL,
		CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void **)&g_pThrough);
	if (hResult != S_OK)return FALSE;
	// グラフビルダに追加する
	hResult = g_pGraph->AddFilter(g_pThrough, L"Through");
	if (hResult != S_OK)return FALSE;

	// VideoRendererのインスタンスを作成
	hResult = CoCreateInstance(CLSID_VideoRenderer, NULL, 
		CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void **)&g_pVideoRenderer);
	if (hResult != S_OK)return FALSE;
	// グラフビルダに追加する
	hResult = g_pGraph->AddFilter(g_pVideoRenderer, L"Video Renderer");
	if (hResult != S_OK)return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShowフィルタの接続
/////////////////////////////////////////////////////////////////////////////////////////
BOOL ConectFilters(void){
	HRESULT hResult;
	// ソースのフィルタをThroughフィルタに接続
	hResult = g_pBuilder->RenderStream(&PIN_CATEGORY_CAPTURE,&MEDIATYPE_Video,g_pSrc,0,g_pThrough);
	if (hResult != S_OK)return FALSE;

	// ThroughフィルタをVideoRendererに接続
	hResult = g_pBuilder->RenderStream( 0, &MEDIATYPE_Video, g_pThrough, NULL, g_pVideoRenderer );
	if (hResult != S_OK)return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShowの描画ウィンドウをリサイズ
/////////////////////////////////////////////////////////////////////////////////////////
BOOL ResizeWindow(HWND hWnd){
	HRESULT hResult;

	// ウィンドウが有効化をチェック
	if( !g_pVideoWindow )return FALSE;

	// ウィンドウを不可視状態にする
	hResult = g_pVideoWindow->put_Visible(OAFALSE);
	// ウィンドウの領域サイズを取得し，書き込む範囲を設定する
	RECT rect;
	GetWindowRect(hWnd,&rect);
	hResult = g_pVideoWindow->SetWindowPosition(0, 0, rect.right-rect.left,rect.bottom-rect.top);
	if (hResult != S_OK)return FALSE;

	// ウィンドウを可視状態にする
	hResult = g_pVideoWindow->put_Visible(OATRUE);
	if (hResult != S_OK)return FALSE;
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow描画領域の設定
/////////////////////////////////////////////////////////////////////////////////////////
BOOL SetWindow(HWND hWnd){
	HRESULT hResult;
	// グラフビルダからウィンドウを取得する
    hResult = g_pGraph->QueryInterface(IID_IVideoWindow, (void **) &g_pVideoWindow);
	if (hResult != S_OK)return FALSE;

	// ウィンドウのオーナーとなるウィンドウのハンドルを指定する
	hResult = g_pVideoWindow->put_Owner( (OAHWND)hWnd );
	if (hResult != S_OK)return FALSE;

	// ウィンドウのスタイルを指定する
	hResult = g_pVideoWindow->put_WindowStyle(WS_CHILD| WS_CLIPSIBLINGS);
	if (hResult != S_OK)return FALSE;

	// ウィンドウの領域サイズを取得し，書き込む範囲を設定する
	RECT rect;
	GetWindowRect(hWnd,&rect);
	hResult = g_pVideoWindow->SetWindowPosition(0, 0, rect.right-rect.left,rect.bottom-rect.top);
	if (hResult != S_OK)return FALSE;

	// ウィンドウを可視状態にする
	hResult = g_pVideoWindow->put_Visible(OATRUE);
	if (hResult != S_OK)return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShowフィルタの解放
/////////////////////////////////////////////////////////////////////////////////////////
BOOL ReleaseAll(void){
	if(g_pMediaCtrl)g_pMediaCtrl->Stop();
	if(g_pGraph)g_pGraph->Release();
	if(g_pMediaCtrl)g_pMediaCtrl->Release();
	if(g_pSrc)g_pSrc->Release();
	if(g_pThrough)g_pThrough->Release();
	if(g_pVideoRenderer)g_pVideoRenderer->Release();
	if(g_pBuilder)g_pBuilder->Release();
	if(g_pVideoWindow)g_pVideoWindow->Release();
	if(g_pMediaEvent)g_pMediaEvent->Release();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShowキャプチャデバイスの取得と列挙
/////////////////////////////////////////////////////////////////////////////////////////
BOOL GetCaptureDevice(IBaseFilter **ppSrcFilter)
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
	hResult = g_pGraph->AddFilter(g_pSrc, L"Video Capture");
	if (hResult != S_OK)return FALSE;

	// オブジェクトの片づけ
	pClassEnum->Release();
	pDevEnum->Release();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShowフィルタの初期化処理
/////////////////////////////////////////////////////////////////////////////////////////
BOOL InitializeDirectDraw(HWND hWnd){
	
	HRESULT		hResult;

	// フィルタグラフ作成
	hResult = CoCreateInstance(CLSID_FilterGraph, NULL, 
		CLSCTX_INPROC, IID_IGraphBuilder, (void **)&g_pGraph);
	if (hResult != S_OK)return FALSE;

	// キャプチャデバイス取得
	hResult = GetCaptureDevice(&g_pSrc);
	if (hResult != TRUE)return FALSE;

	// キャプチャビルダの作成
	hResult = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, 
		CLSCTX_INPROC, IID_ICaptureGraphBuilder2, (void **)&g_pBuilder);
	if (hResult != S_OK)return FALSE;

	// グラフにキャプチャビルダをセット
	hResult = g_pBuilder->SetFiltergraph(g_pGraph);
	if (hResult != S_OK)return FALSE;

	// メディアコントロールを取得
	g_pGraph->QueryInterface(IID_IMediaControl, (void **)&g_pMediaCtrl);

	// フィルタの作成
	if( !CreateFilters() )return FALSE;
	// フィルタの接続
	if( !ConectFilters() )return FALSE;
	// ウィンドウのセット
	if( !SetWindow(hWnd) )return FALSE;
	
	// 処理開始
	hResult = g_pMediaCtrl->Run();

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////////
// main
/////////////////////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
 	// TODO: この位置にコードを記述してください。
	HRESULT		hResult;				// COM系 APIの戻り値保存用

	// COMライブラリの初期化
	hResult = CoInitialize( NULL );

	MSG msg;
	HACCEL hAccelTable;

	// グローバル ストリングを初期化します
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DIRECTSHOWSKELTONSDK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass( hInstance );

	// アプリケーションの初期化を行います:
	if( !InitInstance( hInstance, nCmdShow ) ) 
	{
		ReleaseAll();
		CoUninitialize();		// COMの終了
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_DIRECTSHOWSKELTONSDK);

	// メイン メッセージ ループ:
	while( GetMessage(&msg, NULL, 0, 0) ) 
	{
		if( !TranslateAccelerator (msg.hwnd, hAccelTable, &msg) ) 
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}

	ReleaseAll();
	CoUninitialize();		// COMの終了

	return msg.wParam;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//  関数: MyRegisterClass()
//
//  用途: ウィンドウ クラスの登録
//
//  コメント:
//
//    この関数およびその使用はこのコードを Windows 95 で先に追加された
//    'RegisterClassEx' 関数と Win32 システムの互換性を保持したい場合に
//    のみ必要となります。アプリケーションが、アプリケーションに関連付け
//    られたスモール アイコンを取得できるよう、この関数を呼び出すことは
//    重要です。
//
/////////////////////////////////////////////////////////////////////////////////////////
ATOM MyRegisterClass( HINSTANCE hInstance )
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style		= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon		= LoadIcon(hInstance, (LPCTSTR)IDI_DIRECTSHOWSKELTONSDK);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_DIRECTSHOWSKELTONSDK;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx( &wcex );
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//   関数: InitInstance(HANDLE, int)
//
//   用途: インスタンス ハンドルの保存とメイン ウィンドウの作成
//
//   コメント:
//
//        この関数では、インスタンス ハンドルをグローバル変数に保存し、プログラムの
//        メイン ウィンドウを作成し表示します。
//
/////////////////////////////////////////////////////////////////////////////////////////
BOOL InitInstance( HINSTANCE hInstance, int nCmdShow )
{
   HWND hWnd;

   hInst = hInstance; // グローバル変数にインスタンス ハンドルを保存します

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if( !hWnd ) 
   {
      return FALSE;
   }

   ShowWindow( hWnd, nCmdShow );
   UpdateWindow( hWnd );

   if( !InitializeDirectDraw(hWnd) )
	   return FALSE;

   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//  関数: WndProc(HWND, unsigned, WORD, LONG)
//
//  用途: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND	- アプリケーション メニューの処理
//  WM_PAINT	- メイン ウィンドウの描画
//  WM_DESTROY	- 終了メッセージの通知とリターン
//
//
/////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch( message ) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// メニュー選択の解析:
			switch( wmId ) 
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow( hWnd );
				   break;
				default:
				   return DefWindowProc( hWnd, message, wParam, lParam );
			}
			break;
		case WM_SIZE:
			ResizeWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage( 0 );
			break;
		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
   }
   return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
// バージョン情報ボックス用メッセージ ハンドラ
LRESULT CALLBACK About( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if( LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL ) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

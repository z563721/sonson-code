// 
// simple
// Main.cpp
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
//////////////////////////////////////////////////////////////////////
//メイン
//アイドリング時にアニメーションをする

#include "main.h"

CHAR szAppName[]="アイドリング処理によるアニメーション";

////////////////////////////////////////////////////////////////////
//グローバル変数
HGLRC hRC=NULL;								//OpenGL
HDC		hDC=NULL;						//デバイスコンテキストハンドル

GLfloat LookAt[][4] = {
	{0.0, 0.0, 0.0},
	{1.0, 1.0, 2.5}
};										//視点の初期位置

GLfloat Look_deg =0;	//視点の角度
float tt=0;

////////////////////////////////////////////////////////////////////
//ウィンドウ関数
LONG   WINAPI MainWndProc (HWND, UINT, WPARAM, LPARAM);
void Draw(void);
////////////////////////////////////////////////////////////////////
// エントリポイント
int APIENTRY WinMain(HINSTANCE hInstance,
                        HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine,
                        int nCmdShow )
{
	WNDCLASSEX wcex;	// ウインドウクラス構造体
	HWND hWnd;			// ウインドウハンドル
	MSG msg;			// メッセージ構造体

	// ウィンドウクラス構造体を設定します。
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = (WNDPROC)MainWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(NULL);
	wcex.lpszClassName = "ModelApp";
	wcex.hIconSm = NULL;//LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	
	// ウインドウクラスを登録します。
	RegisterClassEx(&wcex);

	// ウインドウを作成します。
   	hWnd = CreateWindow(wcex.lpszClassName,						// ウインドウクラス名
		szAppName, 		// キャプション文字列
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,									// ウインドウのスタイル
		CW_USEDEFAULT,			// 水平位置
		CW_USEDEFAULT,			// 垂直位置
		CW_USEDEFAULT,					// 幅
		CW_USEDEFAULT,					// 高さ
		NULL,					// 親ウインドウ
		NULL,					// ウインドウメニュー
		hInstance,				// インスタンスハンドル
		NULL);					// WM_CREATE情報
	
	// ウインドウを表示します。
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//アイドル時にアニメーションさせるためのメッセージループ
	while(TRUE){
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
			//WM_QUITを明示的に処理する
			if(msg.message==WM_QUIT){
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//他になにも処理がないので描画する
		else{
			Draw();
		}
	}
	// 戻り値を返します。
	return msg.wParam;
}

////////////////////////////////////////////////////////////////////
//ウィンドウプロシージャ
LONG WINAPI MainWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	LONG    lRet = 1;

    switch (uMsg)
    {
    	case WM_CREATE:
			//OpenGLの初期化
			if((hRC=Init_Pixel(hWnd))==NULL){
				MessageBox(hWnd,"","",MB_OK);
			}
			//カレントコンテキスト
			hDC = GetDC(hWnd);
			wglMakeCurrent(hDC,hRC);
			StartFunction();
			break;			
		case WM_SIZE:
			//リサイズ時のOpenGLの処理
	        Resize(hWnd);
            break;
		case WM_DESTROY:
			//コンテキストの解放
			Release_GLWindow(hWnd);
			PostQuitMessage (0);
			break;
	   	default:
            lRet = DefWindowProc (hWnd, uMsg, wParam, lParam);
			break;
    }
    return lRet;
}
//描画関数
void Draw(void){
	//ウィンドウを塗りつぶす
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//視点の変換行列の初期化
	glLoadIdentity();
	//視点の決定
	gluLookAt(LookAt[1][0],LookAt[1][1],LookAt[1][2],
		LookAt[0][0],LookAt[0][1],LookAt[0][2],
		0.0, 1.0, 0.0);
	//四角形の描画
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3d(1.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glColor3d(1.0, 1.0, 0.0);
			glVertex3f(0.0, 0.0, 1.0);
			glColor3d(1.0, 0.0, 1.0);
			glVertex3f(1.0, 0.0, 1.0);
			glVertex3f(1.0, 0.0, 0.0);
		glEnd();
	glPopMatrix();
	hDC = wglGetCurrentDC();
	//ダブルバッファ
	SwapBuffers(hDC);
}
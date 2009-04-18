// 
// mfc_gl_mdi
// mfcmdi_glView.cpp
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
//// mfcmdi_glView.cpp : CMfcmdi_glView クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "mfcmdi_gl.h"

#include "mfcmdi_glDoc.h"
#include "mfcmdi_glView.h"

#include "InitGL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glView

IMPLEMENT_DYNCREATE(CMfcmdi_glView, CView)

BEGIN_MESSAGE_MAP(CMfcmdi_glView, CView)
	//{{AFX_MSG_MAP(CMfcmdi_glView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glView クラスの構築/消滅

CMfcmdi_glView::CMfcmdi_glView()
{
	// TODO: この場所に構築用のコードを追加してください。

}

CMfcmdi_glView::~CMfcmdi_glView()
{
	// OpenGLの開放
	wglMakeCurrent(NULL,NULL);
    wglDeleteContext(hRC);
	delete cDC;
}

BOOL CMfcmdi_glView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glView クラスの描画

void CMfcmdi_glView::OnDraw(CDC* pDC)
{
	CMfcmdi_glDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: この場所にネイティブ データ用の描画コードを追加します。
	
	wglMakeCurrent (cDC->m_hDC, hRC);    // 現在のcontext切り替え

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	glLoadIdentity();
	gluLookAt(
		1,1,2,
		0,0,0,
		0,1,0);
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
	glFinish();
	SwapBuffers(cDC->m_hDC) ;
}

/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glView クラスの印刷

BOOL CMfcmdi_glView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// デフォルトの印刷準備
	return DoPreparePrinting(pInfo);
}

void CMfcmdi_glView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CMfcmdi_glView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glView クラスの診断

#ifdef _DEBUG
void CMfcmdi_glView::AssertValid() const
{
	CView::AssertValid();
}

void CMfcmdi_glView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfcmdi_glDoc* CMfcmdi_glView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcmdi_glDoc)));
	return (CMfcmdi_glDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glView クラスのメッセージ ハンドラ

int CMfcmdi_glView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: この位置に固有の作成用コードを追加してください
	
	cDC = new CClientDC(this) ;             // DCの生成
	hRC = Init_Pixel(cDC->m_hDC) ;          // OpenGL用にPixel Formatを指定
	wglMakeCurrent (cDC->m_hDC, hRC);    // 現在のcontext設定
	StartFunction();
	return 0;
}

void CMfcmdi_glView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	Resize(cx,cy);
}

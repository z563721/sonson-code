// 
// mfc_gl_sdi
// mfcsdi_glView.cpp
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
//// mfcsdi_glView.cpp : CMfcsdi_glView クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "mfcsdi_gl.h"

#include "mfcsdi_glDoc.h"
#include "mfcsdi_glView.h"

#include "InitGL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcsdi_glView

IMPLEMENT_DYNCREATE(CMfcsdi_glView, CView)

BEGIN_MESSAGE_MAP(CMfcsdi_glView, CView)
	//{{AFX_MSG_MAP(CMfcsdi_glView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcsdi_glView クラスの構築/消滅

CMfcsdi_glView::CMfcsdi_glView()
{
	// TODO: この場所に構築用のコードを追加してください。

}

CMfcsdi_glView::~CMfcsdi_glView()
{
	// OpenGLの開放
	wglMakeCurrent(NULL,NULL);
    wglDeleteContext(hRC);
	delete cDC;
}

BOOL CMfcsdi_glView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMfcsdi_glView クラスの描画

void CMfcsdi_glView::OnDraw(CDC* pDC)
{
	CMfcsdi_glDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: この場所にネイティブ データ用の描画コードを追加します。

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	glLoadIdentity();
	gluLookAt(
		2,2,3,
		0,0,0,
		0,1,0);
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
// CMfcsdi_glView クラスの印刷

BOOL CMfcsdi_glView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// デフォルトの印刷準備
	return DoPreparePrinting(pInfo);
}

void CMfcsdi_glView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CMfcsdi_glView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

/////////////////////////////////////////////////////////////////////////////
// CMfcsdi_glView クラスの診断

#ifdef _DEBUG
void CMfcsdi_glView::AssertValid() const
{
	CView::AssertValid();
}

void CMfcsdi_glView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfcsdi_glDoc* CMfcsdi_glView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcsdi_glDoc)));
	return (CMfcsdi_glDoc*)m_pDocument;
}
#endif //_DEBUG

int CMfcsdi_glView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CMfcsdi_glView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	Resize(cx,cy);	
}

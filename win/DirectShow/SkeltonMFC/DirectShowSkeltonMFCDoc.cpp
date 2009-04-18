// 
// SkeltonMFC
// DirectShowSkeltonMFCDoc.cpp
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
//// DirectShowSkeltonMFCDoc.cpp : CDirectShowSkeltonMFCDoc クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "DirectShowSkeltonMFC.h"

#include "DirectShowSkeltonMFCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirectShowSkeltonMFCDoc

IMPLEMENT_DYNCREATE(CDirectShowSkeltonMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CDirectShowSkeltonMFCDoc, CDocument)
	//{{AFX_MSG_MAP(CDirectShowSkeltonMFCDoc)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirectShowSkeltonMFCDoc クラスの構築/消滅

CDirectShowSkeltonMFCDoc::CDirectShowSkeltonMFCDoc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。

}

CDirectShowSkeltonMFCDoc::~CDirectShowSkeltonMFCDoc()
{
}

BOOL CDirectShowSkeltonMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDirectShowSkeltonMFCDoc シリアライゼーション

void CDirectShowSkeltonMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: この位置に保存用のコードを追加してください。
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください。
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDirectShowSkeltonMFCDoc クラスの診断

#ifdef _DEBUG
void CDirectShowSkeltonMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDirectShowSkeltonMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDirectShowSkeltonMFCDoc コマンド

// 
// Through
// Through.h
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
//#if !defined(AFX_THROUGH_H__44E84F41_9DE1_4F4A_9C4D_8B20CB9830A1__INCLUDED_)
#define AFX_THROUGH_H__44E84F41_9DE1_4F4A_9C4D_8B20CB9830A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Through : public CTransformFilter  
{
public:
    DECLARE_IUNKNOWN;

	virtual ~Through();

	static CUnknown *CreateInstance(LPUNKNOWN punk, HRESULT *pHr);

	HRESULT CheckInputType(const CMediaType *mtIn);
	HRESULT CheckTransform(const CMediaType *mtIn, const CMediaType *mtOut);

	HRESULT Transform(IMediaSample *pIn, IMediaSample *pOut);
	HRESULT DecideBufferSize(IMemAllocator *pAlloc,
			     ALLOCATOR_PROPERTIES *pProperties);
	HRESULT GetMediaType(int iPosition, CMediaType *pMediaType);

private:
	Through(TCHAR *tszName, LPUNKNOWN pUnk, HRESULT *pHr);
	BOOL CheckMediaType(const CMediaType *pMediaType) const;
	HRESULT Copy(IMediaSample *pSource, IMediaSample *pDest) const;
};

#endif // !defined(AFX_THROUGH_H__44E84F41_9DE1_4F4A_9C4D_8B20CB9830A1__INCLUDED_)

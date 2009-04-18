// 
// Binarize
// IBinarize.h
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
//#ifndef __IBinarize__
#define __IBinarize__

#define BINARIZE_MODE	1
#define NORMAL_MODE		2

// IBinarizeインタフェースのGUID
// {2E3295FB-5542-4c9e-ADA5-F35F80BCF4BC}
DEFINE_GUID( IID_IBinarize, 0x2e3295fb, 0x5542, 0x4c9e, 0xad, 0xa5, 0xf3, 0x5f, 0x80, 0xbc, 0xf4, 0xbc);

//////////////////////////////////////////////////////////////////////
// インタフェース
MIDL_INTERFACE("2E3295FB-5542-4c9e-ADA5-F35F80BCF4BC")
IBinarize : public IUnknown
{
    public:
        virtual HRESULT STDMETHODCALLTYPE SetMode( int )PURE;
        virtual HRESULT STDMETHODCALLTYPE AdjustThreshold( int )PURE;
};

#endif

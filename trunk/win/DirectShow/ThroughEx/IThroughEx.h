// 
// ThroughEx
// IThroughEx.h
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
//#ifndef __ITHROUGHEX__
#define __ITHROUGHE__


#define PARAM_MESSAGE_FROM_FILTER 1

// IThroughExインタフェースのGUID
/* 53621561-B4A8-4579-BEE9-01C90BC9E4E25 */
DEFINE_GUID( IID_IThroughEx, 0x53621561, 0xb4a8, 0x4579, 0xbe, 0xe9, 0x1, 0xc9, 0xb, 0xc9, 0xe4, 0xe2);

//////////////////////////////////////////////////////////////////////
// インタフェース
MIDL_INTERFACE("53621561-B4A8-4579-BEE9-01C90BC9E4E2")
IThroughEx : public IUnknown
{
    public:
        
        virtual HRESULT STDMETHODCALLTYPE Call( void ) = 0;
};

#endif

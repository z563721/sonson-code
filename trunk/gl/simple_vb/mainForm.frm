' 
' simple_vb
' mainForm.frm
' 
' The MIT License
' 
' Copyright (c) 2009 sonson, sonson@Picture&Software
' 
' Permission is hereby granted, free of charge, to any person obtaining a copy
' of this software and associated documentation files (the "Software"), to deal
' in the Software without restriction, including without limitation the rights
' to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
' copies of the Software, and to permit persons to whom the Software is
' furnished to do so, subject to the following conditions:
' 
' The above copyright notice and this permission notice shall be included in
' all copies or substantial portions of the Software.
' 
' THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
' IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
' FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
' AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
' LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
' OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
' THE SOFTWARE.
'VERSION 5.00
Begin VB.Form mainForm 
   Caption         =   "OpenGLスケルトンコード version3.0"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows の既定値
End
Attribute VB_Name = "mainForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'レンダリングコンテキスト
Dim hRC&
Public Function CreateGLWindow() As Boolean
    Dim PixelFormat As GLuint
    Dim pfd As PIXELFORMATDESCRIPTOR                'ピクセルフォーマット構造体

    With pfd
        .cColorBits = 16
        .cDepthBits = 16
        .dwFlags = PFD_DRAW_TO_WINDOW Or PFD_SUPPORT_OPENGL Or PFD_DOUBLEBUFFER
        .iLayerType = PFD_MAIN_PLANE
        .iPixelType = PFD_TYPE_RGBA
        .nVersion = 1
    End With
    
    mainForm.ScaleMode = vbPixels
        
    PixelFormat = ChoosePixelFormat(mainForm.hDC, pfd)
    If PixelFormat = 0 Then                     'ピクセルフォーマットの選定に失敗
        Call KillGLWindow                            'ウィンドウ破棄
        MsgBox "ピクセルフォーマット選択失敗", vbExclamation, "警告"
        CreateGLWindow = False                  '戻り値
        Exit Function
    End If

    If SetPixelFormat(mainForm.hDC, PixelFormat, pfd) = 0 Then 'ピクセルフォーマットの設定に失敗
        Call KillGLWindow                            'ウィンドウ破棄
        MsgBox "ピクセルフォーマット設定失敗", vbExclamation, "警告"
        CreateGLWindow = False                  '戻り値
        Exit Function
    End If
    
    hRC = wglCreateContext(mainForm.hDC)
    If (hRC = 0) Then                           'レンダリングコンテキストの作成に失敗
        Call KillGLWindow                            'ウィンドウ破棄
        MsgBox "レンダリングコンテキスト作成失敗", vbExclamation, "警告"
        CreateGLWindow = False                  '戻り値
        Exit Function
    End If

    If wglMakeCurrent(mainForm.hDC, hRC) = 0 Then    'レンダリングコンテキストをカレントコンテキストに設定
        Call KillGLWindow
         MsgBox "コンテキストの設定失敗", vbExclamation, "警告"
        CreateGLWindow = False
        Exit Function
    End If

    CreateGLWindow = True
End Function

Public Function InitGL()
'OpenGLに用いる関数の初期化等に関する関数

    glClearColor 0#, 0#, 0#, 0#         '背景色の設定
    glClearDepth 1#                     'デプスバッファの設定
    glEnable glcDepthTest               'デプスバッファの使用開始

End Function
Public Sub KillGLWindow()
'OpenGLで使用したレンダリングコンテキストの破棄
    If hRC Then                                     'レンダリングコンテキストの有無の確認
        If wglMakeCurrent(0, 0) = 0 Then            'レンダリングコンテキストの確認
            MsgBox "コンテキスト破棄失敗", vbInformation, "警告"
        End If

        If wglDeleteContext(hRC) = 0 Then           'レンダリングコンテキストの破棄
            MsgBox "レンダリングコンテキスト破棄失敗", vbInformation, "警告"
        End If
        hRC = 0                                     '一応NULLを代入？
    End If
End Sub
Public Function DrawGLScene()
'描画関数
'描画コードはここに記述します
    glClear clrColorBufferBit Or clrDepthBufferBit  'カラーバッファとデプスバッファのクリア
    glLoadIdentity                                  '単位行列の呼び出し
    gluLookAt 0, 0, 4, 0, 0, 0, 0, 1, 0
'四角形の描画コード
    glBegin bmTriangles
        glColor3f 1, 0, 0
        glVertex3f 0#, 1#, 0#
        glColor3f 0, 1, 0
        glVertex3f -1#, 0#, 0#
        glColor3f 0, 0, 1
        glVertex3f 1#, 0#, 0#
    glEnd
End Function
Private Sub Form_Initialize()
'初期化作業
    'GLウィンドウの作成
    If CreateGLWindow = False Then
        Call KillGLWindow
        End
    End If
    'OpenGLの命令設定
    Call InitGL

End Sub
Private Sub Form_Paint()
'描画命令時に再描画する
    Call DrawGLScene
    'ダブルバッファを交換する
    SwapBuffers mainForm.hDC
End Sub

Private Sub Form_Unload(Cancel As Integer)
'ウィンドウを破棄時
    Call KillGLWindow
End Sub
Private Sub Form_Resize()
    Dim Height As Integer
'ウィンドウのリサイズ時の処理
    'ビューポートなどを設定する
    'ウィンドウサイズが０になると
    'アスペクト比算出のときにDevide by 0エラーになるので
    'サイズが０のときは１として処理する。
    Height = mainForm.ScaleHeight
    If Height = 0 Then
        Height = 1
    End If
    
'ビューポートの設定
    glViewport 0, 0, mainForm.ScaleWidth, Height  'ビューポートをウィンドウの大きさに合わせる
    glMatrixMode mmProjection       'プロジェクションマトリクスモードへ移行
    glLoadIdentity                  'プロジェクションマトリクスを単位行列にリセット

    'ウィンドウのアスペクト比を算出し、アスペクト比を代入する
    gluPerspective 45#, mainForm.ScaleWidth / Height, 0.1, 100#

    glMatrixMode mmModelView        'モデルビューモードへ移行
    glLoadIdentity

'リサイズ時に再描画
    Call DrawGLScene
    SwapBuffers mainForm.hDC
End Sub


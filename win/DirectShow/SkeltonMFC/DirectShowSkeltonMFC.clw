; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CDirectShowSkeltonMFCView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DirectShowSkeltonMFC.h"
LastPage=0

ClassCount=5
Class1=CDirectShowSkeltonMFCApp
Class2=CDirectShowSkeltonMFCDoc
Class3=CDirectShowSkeltonMFCView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX

[CLS:CDirectShowSkeltonMFCApp]
Type=0
HeaderFile=DirectShowSkeltonMFC.h
ImplementationFile=DirectShowSkeltonMFC.cpp
Filter=N

[CLS:CDirectShowSkeltonMFCDoc]
Type=0
HeaderFile=DirectShowSkeltonMFCDoc.h
ImplementationFile=DirectShowSkeltonMFCDoc.cpp
Filter=N

[CLS:CDirectShowSkeltonMFCView]
Type=0
HeaderFile=DirectShowSkeltonMFCView.h
ImplementationFile=DirectShowSkeltonMFCView.cpp
Filter=C
LastObject=CDirectShowSkeltonMFCView
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=DirectShowSkeltonMFC.cpp
ImplementationFile=DirectShowSkeltonMFC.cpp
Filter=D

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_APP_ABOUT
CommandCount=11

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889


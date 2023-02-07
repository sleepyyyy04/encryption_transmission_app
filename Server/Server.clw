; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDecipherDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Server.h"

ClassCount=4
Class1=CServerApp
Class2=CServerDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SERVER_DIALOG
Class4=CDecipherDlg
Resource4=IDD_DIALOG_DECIPHER

[CLS:CServerApp]
Type=0
HeaderFile=Server.h
ImplementationFile=Server.cpp
Filter=N

[CLS:CServerDlg]
Type=0
HeaderFile=ServerDlg.h
ImplementationFile=ServerDlg.cpp
Filter=D
LastObject=CServerDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ServerDlg.h
ImplementationFile=ServerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SERVER_DIALOG]
Type=1
Class=CServerDlg
ControlCount=6
Control1=IDLOGIN,button,1342242817
Control2=IDEXIT,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SNAME,edit,1350631552
Control6=IDC_SPSWORD,edit,1350631584

[DLG:IDD_DIALOG_DECIPHER]
Type=1
Class=CDecipherDlg
ControlCount=18
Control1=IDEXIT,button,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDITSERVER,edit,1350633600
Control5=IDC_STATIC,button,1342177287
Control6=IDC_CIPHERTEXT,edit,1352728580
Control7=IDC_STATIC,static,1342308352
Control8=IDC_KEY,edit,1352728580
Control9=IDC_STATIC,static,1342308352
Control10=IDC_BDECIPHER,button,1342242816
Control11=IDC_STATIC,button,1342177287
Control12=IDC_PLAINTEXT,edit,1352728580
Control13=IDC_STATIC,static,1342308352
Control14=IDC_BCLEAR,button,1342242816
Control15=IDC_BSAVEPLTXT,button,1342242816
Control16=IDC_BSAVECPTXT,button,1342242816
Control17=IDC_STATIC,static,1342308352
Control18=IDC_CLIENTIP,edit,1350633600

[CLS:CDecipherDlg]
Type=0
HeaderFile=DecipherDlg.h
ImplementationFile=DecipherDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_KEY


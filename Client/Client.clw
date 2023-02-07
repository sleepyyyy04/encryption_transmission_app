; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEnciperDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Client.h"

ClassCount=4
Class1=CClientApp
Class2=CClientDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_CLIENT_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CEnciperDlg
Resource4=IDD_DIALOG_ENCIPHER

[CLS:CClientApp]
Type=0
HeaderFile=Client.h
ImplementationFile=Client.cpp
Filter=N

[CLS:CClientDlg]
Type=0
HeaderFile=ClientDlg.h
ImplementationFile=ClientDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CClientDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=ClientDlg.h
ImplementationFile=ClientDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CLIENT_DIALOG]
Type=1
Class=CClientDlg
ControlCount=6
Control1=IDLOGIN,button,1342242817
Control2=IDEXIT,button,1342242816
Control3=IDC_EDITCNAME,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDITCPSWD,edit,1350631584
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_ENCIPHER]
Type=1
Class=CEnciperDlg
ControlCount=23
Control1=IDEXIT,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,button,1342177287
Control4=IDC_CLIENT,edit,1350633600
Control5=IDC_STATIC,static,1342308352
Control6=IDC_BCONNECT,button,1342242816
Control7=IDC_IPADDRESS,SysIPAddress32,1342242816
Control8=IDC_STATIC,button,1342177287
Control9=IDC_PLAINTEXT,edit,1352728580
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_KEYY,edit,1352728580
Control13=IDC_STATIC,button,1342177287
Control14=IDC_BSEND,button,1342242816
Control15=IDC_BSAVECT,button,1342242816
Control16=IDC_BCLEAR,button,1342242816
Control17=IDC_STATIC,static,1342308352
Control18=IDC_CIPHERTEXT,edit,1352728580
Control19=IDC_BENCIPHER,button,1342242816
Control20=IDC_BOPENPT,button,1342242816
Control21=IDC_KEYX,edit,1352728580
Control22=IDC_STATES,static,1342308352
Control23=IDC_STATIC,static,1342308352

[CLS:CEnciperDlg]
Type=0
HeaderFile=EnciperDlg.h
ImplementationFile=EnciperDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CEnciperDlg


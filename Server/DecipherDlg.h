#if !defined(AFX_DECIPHERDLG_H__65029413_E3F8_4F39_A0F3_E008B5FA6634__INCLUDED_)
#define AFX_DECIPHERDLG_H__65029413_E3F8_4F39_A0F3_E008B5FA6634__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DecipherDlg.h : header file
//
#include "winsock2.h"
#define BIT_LEN 800 
#define KEY_LONG 128  //私钥比特长
#define P_LONG 200    //有限域P比特长
#define EN_LONG 40    //一次取明文字节数(x,20)(y,20)
#include "tommath.h"
#include"tommath_class.h"
#include"tommath_superclass.h"
#pragma comment(lib,"WS2_32.lib")
#pragma comment(lib,"MathLib.lib")
/////////////////////////////////////////////////////////////////////////////
// CDecipherDlg dialog
#define WM_SOCK WM_USER+1 //定义自定义消息
class CDecipherDlg : public CDialog
{
// Construction
public:
	int miwendraw(mp_int *a,char *ch,int chlong);
	int GetPrime(mp_int *m,int lon);
	void Get_X_Y(mp_int *x1,mp_int *y1,mp_int *b,mp_int *a,mp_int *p);
	bool Ecc_points_mul(mp_int *qx,mp_int *qy, mp_int *px, mp_int *py,mp_int *d,mp_int *a,mp_int *p);
	int Two_points_add(mp_int *x1,mp_int *y1,mp_int *x2,mp_int *y2,mp_int *x3,mp_int *y3,mp_int *a,bool zero,mp_int *p);
	int chmistore(mp_int *a,FILE *fp);
	int chdraw(mp_int *a,char *ch);
	unsigned int SDBMHash16(char *str);
	void NumToStr(unsigned __int64 a,char z[100]);
	void Hashstring(char temphash[800],unsigned __int64 *hash,int n1);
	static int myrng(unsigned char *dst, int len, void *dat);
	int putin(mp_int *a,char *ch,int chlong);
	unsigned int SDBMHash32(char *str);
	CDecipherDlg(CWnd* pParent = NULL);   // standard constructor
	SOCKET s;//服务器监听套接字
	SOCKET s1;//服务器数据收发套接字
	sockaddr_in addr;
	sockaddr_in addr1;
	sockaddr_in add;
	int i,j,k;
	int n,n2;
	CString str14;
////	HFILE hfile;
////	char buff[100];
////	CString str;
	int s11;
	char *name[15];


//	WSADATA data;


	void SetName(CString name);

// Dialog Data
	//{{AFX_DATA(CDecipherDlg)
	enum { IDD = IDD_DIALOG_DECIPHER };
	CString	m_ciphertext;
	CString	m_servername;
	CString	m_plaintext;
	CString	m_clientIP;
	CString	m_key;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecipherDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CDecipherDlg)
	afx_msg void OnBclear();
	afx_msg void OnBdecipher();
	afx_msg void OnBsavecptxt();
	afx_msg void OnBsavepltxt();
	afx_msg void OnExit();
	afx_msg void Onsockt(WPARAM wParam,LPARAM lParam);//套接字消息响应函数
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DECIPHERDLG_H__65029413_E3F8_4F39_A0F3_E008B5FA6634__INCLUDED_)

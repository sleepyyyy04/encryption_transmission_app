#if !defined(AFX_ENCIPERDLG_H__2B7247AB_6011_44E2_9E4C_B0F181B31A9A__INCLUDED_)
#define AFX_ENCIPERDLG_H__2B7247AB_6011_44E2_9E4C_B0F181B31A9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EnciperDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEnciperDlg dialog
#include <winsock2.h>
#define WM_SOCKT WM_USER+1
#define BIT_LEN 800 
#define KEY_LONG 128  //私钥比特长
#define P_LONG 200    //有限域P比特长
#define EN_LONG 40    //一次取明文字节数(x,20)(y,20)
#include "tommath.h"
#include"tommath_class.h"
#include"tommath_superclass.h"
#pragma comment(lib,"WS2_32.lib")
#pragma comment(lib,"MathLib.lib")
class CEnciperDlg : public CDialog
{
// Construction
public:
	unsigned int SDBMHash32(char *str);
	CString fpathp;
	int putin(mp_int *a,char *ch,int chlong);
	static int myrng(unsigned char *dst, int len, void *dat);
	void Hashstring(char temphash[800],unsigned __int64 *hash,int n1);
	void NumToStr(unsigned __int64 a,char z[100]);
	unsigned int SDBMHash16(char *str);
	int chdraw(mp_int *a,char *ch);
	int chmistore(mp_int *a,FILE *fp);
	int Two_points_add(mp_int *x1,mp_int *y1,mp_int *x2,mp_int *y2,mp_int *x3,mp_int *y3,mp_int *a,bool zero,mp_int *p);
	bool Ecc_points_mul(mp_int *qx,mp_int *qy, mp_int *px, mp_int *py,mp_int *d,mp_int *a,mp_int *p);
	void Get_X_Y(mp_int *x1,mp_int *y1,mp_int *b,mp_int *a,mp_int *p);
	int GetPrime(mp_int *m,int lon);
	CEnciperDlg(CWnd* pParent = NULL);   // standard constructor
	CString ip;//服务器IP地址
	SOCKET s;//声明套接字对象
////	int port;
	char buff[100];
	CString str;
	char str12[100];
	
// Dialog Data
	//{{AFX_DATA(CEnciperDlg)
	enum { IDD = IDD_DIALOG_ENCIPHER };
	CIPAddressCtrl	m_serverIP;
	CString	m_ciphertext;
	CString	m_clientname;
	CString	m_plaintext;
	CString	m_keyx;
	CString	m_keyy;
	//}}AFX_DATA
	void SetName(CString name);
	int KDF(const char* cdata, int datalen, int keylen, char* retdata);
		
	sockaddr_in addr;//声明套接字地址结构变量
	WSADATA data;
	int i;
	int n;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnciperDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEnciperDlg)
	afx_msg void OnBclear();
	afx_msg void OnBconnect();
	afx_msg void OnBencipher();
	afx_msg void OnBopenpt();
	afx_msg void OnBsavect();
	afx_msg void OnBsend();
	afx_msg void OnExit();
	virtual BOOL OnInitDialog();
	afx_msg void Onsockt(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENCIPERDLG_H__2B7247AB_6011_44E2_9E4C_B0F181B31A9A__INCLUDED_)

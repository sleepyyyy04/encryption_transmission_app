// EnciperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "EnciperDlg.h"
#include "locale.h"
#include "tommath.h"
#include"tommath_class.h"
#include"tommath_superclass.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW

#define BIT_LEN 800 
#define KEY_LONG 128  //˽Կ���س�
#define P_LONG 200    //������P���س�
#define EN_LONG 40    //һ��ȡ�����ֽ���(x,20)(y,20)

#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnciperDlg dialog


CEnciperDlg::CEnciperDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEnciperDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEnciperDlg)
	m_ciphertext = _T("");
	m_clientname = _T("");
	m_plaintext = _T("");
	m_keyx = _T("");
	m_keyy = _T("");
	//}}AFX_DATA_INIT
}


void CEnciperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnciperDlg)
	DDX_Control(pDX, IDC_IPADDRESS, m_serverIP);
	DDX_Text(pDX, IDC_CIPHERTEXT, m_ciphertext);
	DDX_Text(pDX, IDC_CLIENT, m_clientname);
	DDX_Text(pDX, IDC_PLAINTEXT, m_plaintext);
	DDX_Text(pDX, IDC_KEYX, m_keyx);
	DDX_Text(pDX, IDC_KEYY, m_keyy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEnciperDlg, CDialog)
	//{{AFX_MSG_MAP(CEnciperDlg)
	ON_BN_CLICKED(IDC_BCLEAR, OnBclear)
	ON_BN_CLICKED(IDC_BCONNECT, OnBconnect)
	ON_BN_CLICKED(IDC_BENCIPHER, OnBencipher)
	ON_BN_CLICKED(IDC_BOPENPT, OnBopenpt)
	ON_BN_CLICKED(IDC_BSAVECT, OnBsavect)
	ON_BN_CLICKED(IDC_BSEND, OnBsend)
	ON_BN_CLICKED(IDEXIT, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnciperDlg message handlers

void CEnciperDlg::OnBclear() 
{
	// TODO: Add your control notification handler code here
	m_ciphertext="";
	m_keyx="";
	m_keyy="";
	m_plaintext="";
	UpdateData(FALSE);
}

void CEnciperDlg::OnBconnect() 
{
	// TODO: Add your control notification handler code here
	BYTE a1,a2,a3,a4;  
	m_serverIP.GetAddress(a1,a2,a3,a4);  
	ip.Format("%d.%d.%d.%d",a1,a2,a3,a4);//������IP
/*		
	::bind(s,(sockaddr*)&addr,sizeof(addr));//���׽���
	::listen(s,1);//�����׽���
	WSAAsyncSelect(s,this->m_hWnd,WM_SOCKT,FD_READ|RD_ACCEPT);
	*/
	addr.sin_family=AF_INET;//����׽��ֵ�ַ�ṹ
	addr.sin_port=htons(100);//ָ������ͨ�ŵĶ˿�
	addr.sin_addr.S_un.S_addr=inet_addr(ip);//ָ��������IP��ַ
	s=::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//�����׽��֣�����������


	if(connect(s,(sockaddr*)&addr,sizeof(addr))!=-1)
	{//�������������������
		MessageBox("���ӳɹ���","��ʾ",MB_ICONWARNING);
		GetDlgItem(IDC_BSEND)->EnableWindow(true);
		::WSAAsyncSelect(s,this->m_hWnd,WM_SOCKT,FD_READ|FD_ACCEPT);
//		::WSAAsyncSelect(s,this->m_hWnd,WM_SOCKT,FD_READ);
	}
}

void CEnciperDlg::OnBencipher() 
{
	// TODO: Add your control notification handler code here
	mp_int GX;
	mp_int GY;
	mp_int K;//˽����Կ
	mp_int A;
	mp_int B;
	mp_int QX;
	mp_int QY;
	mp_int P;//Fp�е�p(������P)
	mp_int c1x,c1y;
	mp_int c2x,c2y;
	mp_int k;//�����k
	mp_int tempx,tempy;
	mp_int temp1;

	mp_init(&GX);
	mp_init(&GY);
	mp_init(&K);
	mp_init(&A);
	mp_init(&B);
	mp_init(&QX);
	mp_init(&QY);
	mp_init(&P);
	mp_init(&c1x);
	mp_init(&c1y);
	mp_init(&c2x);
	mp_init(&c2y);
	mp_init(&k);
	mp_init(&tempx);
	mp_init(&tempy);
	//mp_init(&m);
	mp_init(&temp1);


		FILE *fp,*fq;

	char fout1_name[40]="D:\\test����.txt";

	unsigned __int64 buffer[20000];
//	char test[20000];
	//short buffer[20000],mingwen[20000],buffer1[20000];
	//unsigned __int64 m=9146744073709451615;
	unsigned __int64 hash;
	unsigned __int64 e;
	unsigned __int64 c3;
	int len;
	char z1[100]={0};
	char z2[100]={0};

	//printf("\n\n%I64d\n\n",m);

	//GetPrime(&m,32);
	

 

//    printf("SM2��Բ���ߵĲ�������(��ʮ������ʾ):\n");	

    GetPrime(&P,P_LONG);//��ȡ����P������P�У�����ΪP_LONGbit
//	printf("������ P ��:\n");	
	char temp[800]={0};
	//"1468039979770436987538226329858940350654932893478866333482611"};
    mp_toradix(&P,temp,10);//������P����temp��
//    printf("%s\n",temp);//������P������� 
//		putin(&P,temp,61);

    GetPrime(&A,30);
	char tempA[800]={0};//"671825333"};
//	printf("���߲��� A ��:\n");	
    mp_toradix(&A,tempA,10);
 //   printf("%s\n",tempA); 
//	putin(&A,tempA,9);
//	A=671825333;
	Get_X_Y(&GX,&GY,&B,&A,&P);

     char tempB[800]={0};
//	printf("���߲��� B ��:\n");	
    mp_toradix(&B,tempB,10);
//    printf("%s\n",tempB); 
//	putin(&B,tempB,12);
	

	char tempGX[800]={0};
//	printf("����G��X������:\n");	
    mp_toradix(&GX,tempGX,10);
//    printf("%s\n",tempGX); 
//	putin(&GX,tempGX,9);


	char tempGY[800]={0};
//	printf("����G��Y������:\n");
    mp_toradix(&GY,tempGY,10);
 //   printf("%s\n",tempGY);
//	putin(&GY,tempGY,14);
	

	

	//------------------------------------------------------------------
    GetPrime(&K,KEY_LONG);
    char tempK[800]={0};
//	printf("˽Կ dB ��:\n");
    mp_toradix(&K,tempK,10);
//    printf("%s\n",tempK); 

	Ecc_points_mul(&QX,&QY,&GX,&GY,&K,&A,&P);
	

    char tempQX[800]={0};
//	printf("��ԿX������:\n");
    mp_toradix(&QX,tempQX,10);
//    printf("%s\n",tempQX); 
	m_keyx=tempQX;

	char tempQY[800]={0};
//	printf("��ԿY������:\n");
    mp_toradix(&QY,tempQY,10);
//    printf("%s\n",tempQY); 
	m_keyy=tempQY;

	/*��
	printf("������������ļ������磺D:\\test.txt����");
	cin>>fin_name;
	cout<<"���������Ĵ���ļ������磺D:\\test����.txt����";
	cin>>fout1_name;
	cout<<"��������ܺ����Ĵ���ļ������磺D:\\test���ܺ�����.txt����";
	cin>>fout2_name;
	��*/
	


	/*printf("\n\n����������m ��:\n");	
	char tempm[800]={0};
    mp_toradix(&m,tempm,10);//������P����temp��
    printf("%s\n",tempm);//������P������� */
	
	/*��	
	if((fp=fopen(fin_name,"rb"))==NULL)
	{
		printf("can not open the file!");
		exit(1);
	}
	��*/
	fq=fopen(fout1_name,"wb+");

	/*if(fq==NULL)
	{
		puts("�����ļ����ڴ���������\n");
		//getchar();
	}*/

	fp=fopen(fpathp,"rb");//�����ƴ��ļ�����
	len=fread(buffer,8,10005,fp);


	char tempc1x[800]={0};
	char tempc1y[800]={0};
	char temphash1[800]={0};
	char tempmhash[800]={0};
	char temphash2[800]={0};

//    printf("\n��ʼ��������...   \n");
    for(int i=0;i<len;i++)
	{
	GetPrime(&k,100);
	memset(tempmhash,0,800);//�ڴ��ʼ��
	memset(temphash1,0,800);
	memset(temphash2,0,800);
	Ecc_points_mul(&c1x,&c1y,&GX,&GY,&k,&A,&P);//����C1=[k]G kΪѡȡ�������.
	Ecc_points_mul(&c2x,&c2y,&QX,&QY,&k,&A,&P);//����C2=[k]Q kΪѡȡ�������.
    mp_toradix(&c2x,temphash1,10);//��c2x����temphash1��
	mp_toradix(&c2y,temphash2,10);
	strcat(tempmhash,temphash1);//�����ַ�������temphash1����tempmhash�󷵻�tempmhash
	strcat(tempmhash,temphash2);
	//KDF
    hash=SDBMHash32(tempmhash);
    //Hashstring(tempmhash,hash,sizeof(buffer[i]));

    e=buffer[i]^hash;
	NumToStr(buffer[i],z1);
	strcat(temphash1,z1);
	strcat(temphash1,temphash2);//x2||M||y2
	c3=SDBMHash32(temphash1);
	chmistore(&c1x,fq);
	chmistore(&c1y,fq);
	fwrite(&e,1,8,fq);
	fwrite(&c3,1,4,fq);
	}
	fclose(fp);
	fclose(fq);

	CString fpath="D:\\test����.txt";//�ļ�·����
	CStdioFile file;
	char* oldLocale = _strdup(setlocale(LC_CTYPE, NULL));//�����ڴ�
	setlocale(LC_CTYPE, "chs");//�������ԣ�ʹ���ʶ������
	file.Open(fpath, CFile::modeRead); //ֻ�����ļ�
	CString t;
		while (file.ReadString(t))
		{//��ȡ���ݸ�������
			 m_ciphertext+=t;
		}
		file.Close();//�ر��ļ�
		setlocale(LC_CTYPE, oldLocale);
		free(oldLocale);//�ͷ��ڴ�
		UpdateData(FALSE);

	//cout<<"���ܽ�����"<<endl;
    //printf("\n\n\n��ʼ��������...   \n\n\n");


		/*
	if((fp=fopen(fout1_name,"rb"))==NULL)
	{
		printf("can not open the file!");
		exit(1);
	}
	fq=fopen(fout2_name,"wb+");
	char tempd[800]={0};
	char tempc11x[800]={0};
	char tempc11y[800]={0};
	int j=0;
	mp_int tempzero;
	mp_init(&tempzero);
	char stemp[700]={0};
	while(!feof(fp))
	{
		 
         i=0;
		 while(1)
		{
		     stemp[i]=fgetc(fp);
		     if(i%4==0)
			{
                 if(int(stemp[i]&0xFF) == 255 ) goto L1;
			}
		    i++;
		}
		     
L1:     miwendraw(&c1x, stemp, i);
         i=0;
		 while(1)
		{
		     stemp[i]=fgetc(fp);
		     if(i%4==0)
			{
                 if(int(stemp[i]&0xFF) == 255 ) goto L2;
			}
		    i++;
		}
		     
L2:     miwendraw(&c1y, stemp, i);


	    mp_zero(&tempzero);
        if(mp_cmp(&c1x, &tempzero)==0) break;
		fread(&e,1,8,fp);
		fread(&c3,1,4,fp);
		memset(tempd,0,800);
		memset(tempc11x,0,800);
		mp_toradix(&c1x,tempc1x,10);
		mp_toradix(&c1y,tempc1y,10);
		Ecc_points_mul(&tempx,&tempy,&c1x,&c1y,&K,&A,&P);
		mp_toradix(&tempx,tempc11x,10);
		mp_toradix(&tempy,tempc11y,10);
		strcat(tempd,tempc11x);
		strcat(tempd,tempc11y);
		//printf("��Ҫ����Hashֵ���ַ�����%s\n",tempd);
		//Hashstring(tempd,&hash,sizeof(e));
		hash=SDBMHash32(tempd);
		buffer[j]=e^hash;
		NumToStr(buffer[j],z2);
		j++;
		strcat(tempc11x,z2);
		strcat(tempc11x,tempc11y);
		c31=SDBMHash32(tempc11x);
	}
	fwrite(buffer,8,j,fq);
	fclose(fp);
	fclose(fq);
	cout<<"�ļ����ܽ�����"<<endl;
    */


	/*char tempw[800]={0};
	printf("���ܺ�������:\n");
    mp_toradix(&mx,tempw,10);
    printf("%s\n",tempw); */

//	t_end=clock();
//	cout<<"����ʱ��(��λ��ms):"<<t_end-t_start<<endl;


	/*printf("\n------------------------------------------------------------------------\n");

	Ecc_encipher(&QX,&QY,&GX,&GY,&A,&P);//����

	printf("\n------------------------------------------------------------------------\n");

	Ecc_decipher(&K,&A,&P);//����

	printf("\n------------------------------------------------------------------------\n");*/

//	char cc;
//    cout<<"\n\n���һ���˳�!\n";
//	cin>>cc;

	mp_clear(&GX);
	mp_clear(&GY);
	mp_clear(&K);//˽����Կ
	mp_clear(&A);
	mp_clear(&B);
	mp_clear(&QX);
	mp_clear(&QY);
	mp_clear(&P);//Fp�е�p(������P)


}

void CEnciperDlg::OnBopenpt() 
{
	// TODO: Add your control notification handler code here
	CFileDialog fdlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"TXT Files(*.txt)|*.txt|PDF Files(*.pdf)|*.pdf|All Files(*.*)|*.*||");//���ļ��Ի���
	if(fdlg.DoModal()==IDOK)
	{
		fpathp=fdlg.GetPathName();//�ļ�·����
		CStdioFile file;
		char* oldLocale = _strdup(setlocale(LC_CTYPE, NULL));//�����ڴ�
		setlocale(LC_CTYPE, "chs");//�������ԣ�ʹ���ʶ������
		file.Open(fpathp, CFile::modeRead); //ֻ�����ļ�
		CString temp;
		m_plaintext="";
		while (file.ReadString(temp))
		{//��ȡ���ݸ�������
			 m_plaintext+= temp;
		}
		file.Close();//�ر��ļ�
		setlocale(LC_CTYPE, oldLocale);
		free(oldLocale);//�ͷ��ڴ�
		UpdateData(FALSE);
	}
}

void CEnciperDlg::OnBsavect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CFileDialog fdlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"TXT Files(*.txt)|*.txt|All Files(*.*)|*.*||");
	if(fdlg.DoModal()==IDOK)
	{
		CString filepath="";
		filepath=fdlg.GetPathName(); 
		CFile file(_T(filepath), CFile::modeCreate|CFile::modeWrite);
		file.Write(m_ciphertext, m_ciphertext.GetLength());
		file.Close();
		UpdateData(FALSE);
		AfxMessageBox("�������ĳɹ���",MB_OK);
	}
}

void CEnciperDlg::OnBsend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//���Ҫ���͵�����
	if(m_ciphertext!="")//�жϷ��������Ƿ�Ϊ��
		send(s,m_ciphertext,10000,0);//��������
}

void CEnciperDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	WSACleanup();//�ͷ��׽��ֿ�
	CDialog::OnCancel();
}

void CEnciperDlg::SetName(CString name) 
{
	// TODO: Add your control notification handler code here
	m_clientname=name;
}

BOOL CEnciperDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	//�����ӷ�����ǰ���÷��Ͱ�ť
	GetDlgItem(IDC_BSEND)->EnableWindow(false);

	DWORD ss=MAKEWORD(2,0);//��ʼ���׽��ֿ�
	::WSAStartup(ss,&data);
	/*
	s=::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//�����׽��֣�����������

	BYTE a1,a2,a3,a4;  
	m_serverIP.GetAddress(a1,a2,a3,a4);  
	CString ip;  
	ip.Format("%d.%d.%d.%d",a1,a2,a3,a4);//������IP
	addr.sin_addr.S_un.S_addr=inet_addr(ip);//ָ��������IP��ַ
	
	addr.sin_family=AF_INET;//����׽��ֵ�ַ�ṹ
	addr.sin_port=htons(80);//ָ������ͨ�ŵĶ˿�
	addr.sin_addr.S_un.S_addr=inet_addr(ip);//��ipת��Ϊ�����ֽ�˳��
	::bind(s,(sockaddr*)&addr,sizeof(addr));//���׽���
	::listen(s,1);//�����׽���
	WSAAsyncSelect(s,this->m_hWnd,WM_SOCKT,FD_READ|RD_ACCEPT);
*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEnciperDlg::Onsockt(WPARAM wParam,LPARAM lParam)
{
	switch(lParam)
	{
	case FD_READ://�����ȡ�¼�
//		char s2[100]={0},ssa[20000];
		sockaddr_in add;
		::memset(&add,0,sizeof(add));
//		::getpeername(s,(SOCKADDR*)&add,(int*)sizeof(add));
//		recv(s,s2,100,NULL);
		

	}
}

int CEnciperDlg::myrng(unsigned char *dst, int len, void *dat)
{
	int x;
	for(x=0;x<len;x++)
		dst[x]=rand()&0xFF;
	return len;
}


int CEnciperDlg::GetPrime(mp_int *m, int lon)
{//�õ�lon���س�����
	mp_prime_random_ex(m, 10, lon,(rand()&1)?LTM_PRIME_2MSB_OFF:LTM_PRIME_2MSB_ON,myrng, NULL);
   return MP_OKAY;
}

void CEnciperDlg::Get_X_Y(mp_int *x1, mp_int *y1, mp_int *b, mp_int *a, mp_int *p)
{//�õ�B��G��X����G��Y����

	mp_int tempx,tempy;
    mp_int temp;
	mp_int compare;
	mp_int temp1;
	mp_int temp2;
	mp_int temp3;
	mp_int temp4;
	mp_int temp5;
	mp_int temp6;
	mp_int temp7;
	mp_int temp8;
    
	mp_init_set_int (&compare, 0);
	mp_init(&tempx);
	mp_init(&tempy);
	mp_init(&temp);
    mp_init(&temp1);
	mp_init(&temp2);
	mp_init(&temp3);
	mp_init(&temp4);
	mp_init(&temp5);
	mp_init(&temp6);
	mp_init(&temp7);
	mp_init(&temp8);

 
   while(1)
   {
     
	 //4a3+27b2��0 (mod p)
     GetPrime(b,40);
	 mp_expt_d(a, 3, &temp1);
     mp_sqr(b, &temp2);
	 mp_mul_d(&temp1, 4, &temp3);
	 mp_mul_d(&temp2, 27, &temp4);
     mp_add(&temp3, &temp4, &temp5);
	 mp_mod(&temp5,p,&temp);

     if(mp_cmp(&temp, &compare)!=0 )
	 {
		 break;
	 }
   }

   //y2=x3+ax+b,�������X����,����X�������Y����
   GetPrime(x1,30);
   mp_expt_d(x1, 3, &temp6);
   mp_mul(a, x1, &temp7);
   mp_add(&temp6, &temp7, &temp8);
   mp_add(&temp8, b, &tempx);
   mp_sqrt(&tempx, y1);



   mp_clear(&tempx);
   mp_clear(&tempy);
   mp_clear(&temp);
   mp_clear(&temp1);
   mp_clear(&temp2);
   mp_clear(&temp3);
   mp_clear(&temp4);
   mp_clear(&temp5);
   mp_clear(&temp6);
   mp_clear(&temp7);
   mp_clear(&temp8);

}

bool CEnciperDlg::Ecc_points_mul(mp_int *qx, mp_int *qy, mp_int *px, mp_int *py, mp_int *d, mp_int *a, mp_int *p)
{//���

	mp_int X1, Y1;
mp_int X2, Y2;
mp_int X3, Y3;
mp_int XX1, YY1;
mp_int A,P;

int i;
bool zero=false;
char Bt_array[800]={0};
char cm='1';

    mp_toradix(d,Bt_array,2); 

    mp_init_set_int(&X3, 0);
    mp_init_set_int(&Y3, 0);
	mp_init_copy(&X1, px);
	mp_init_copy(&X2, px);
    mp_init_copy(&XX1, px);
	mp_init_copy(&Y1, py);
	mp_init_copy(&Y2, py);
	mp_init_copy(&YY1, py);

	mp_init_copy(&A, a);
	mp_init_copy(&P, p);

	for(i=1;i<=KEY_LONG-1;i++)
	{
	   mp_copy(&X2, &X1);
	   mp_copy(&Y2, &Y1);
	   Two_points_add(&X1,&Y1,&X2,&Y2,&X3,&Y3,&A,zero,&P);  
       mp_copy(&X3, &X2);
	   mp_copy(&Y3, &Y2);
	   if(Bt_array[i]==cm)
	   {
		  
		   mp_copy(&XX1, &X1);
		   mp_copy(&YY1, &Y1);
		   Two_points_add(&X1,&Y1,&X2,&Y2,&X3,&Y3,&A,zero,&P);
		   mp_copy(&X3, &X2);
		   mp_copy(&Y3, &Y2);

	   }

	}
		
   if(zero)
   {
//	   cout<<"It is Zero_Unit!";
       return false;//���QΪ����²���D
   }

   mp_copy(&X3, qx);
   mp_copy(&Y3, qy);

   mp_clear(&X1);
   mp_clear(&Y1);
   mp_clear(&X2);
   mp_clear(&Y2);
   mp_clear(&X3);
   mp_clear(&Y3);
   mp_clear(&XX1);
   mp_clear(&YY1);
   mp_clear(&A);
   mp_clear(&P);
  
   return true;
}

int CEnciperDlg::Two_points_add(mp_int *x1, mp_int *y1, mp_int *x2, mp_int *y2, mp_int *x3, mp_int *y3, mp_int *a, bool zero, mp_int *p)
{//���

	mp_int x2x1;
mp_int y2y1;
mp_int tempk;
mp_int tempy;
mp_int tempzero;
mp_int k;
mp_int temp1;
mp_int temp2;
mp_int temp3;
mp_int temp4;
mp_int temp5;
mp_int temp6;
mp_int temp7;
mp_int temp8;
mp_int temp9;
mp_int temp10;


mp_init(&x2x1);
mp_init(&y2y1);
mp_init(&tempk);
mp_init(&tempy);
mp_init(&tempzero);
mp_init(&k);
mp_init(&temp1);
mp_init(&temp2);
mp_init_set(&temp3,2);
mp_init(&temp4);
mp_init(&temp5);
mp_init(&temp6);
mp_init(&temp7);
mp_init(&temp8);
mp_init(&temp9);
mp_init(&temp10);


   if(zero)
   {
	  mp_copy(x1, x3);
      mp_copy(y1, y3);
	  zero=false;
	  goto L;
   }
   mp_zero(&tempzero);
   mp_sub(x2, x1, &x2x1);
   if(mp_cmp(&x2x1,&tempzero)==-1)
   {
	  
	  mp_add(&x2x1, p, &temp1);
	  mp_zero(&x2x1);
      mp_copy(&temp1, &x2x1);
   }
   mp_sub(y2, y1, &y2y1);
   if(mp_cmp(&y2y1,&tempzero)==-1)
   {
     
	  mp_add(&y2y1, p, &temp2);
	  mp_zero(&y2y1);
      mp_copy(&temp2, &y2y1);
   }
   if(mp_cmp(&x2x1, &tempzero)!=0)
   {
	   
	   mp_invmod(&x2x1,p,&tempk);
	   
	   mp_mulmod(&y2y1, &tempk, p, &k);
   }
   else
   {
	   if(mp_cmp(&y2y1, &tempzero)==0)
	   {
		  
		  mp_mulmod(&temp3,y1,p,&tempy);
          mp_invmod(&tempy,p,&tempk);
          mp_sqr(x1, &temp4);     
		  mp_mul_d(&temp4, 3, &temp5);
		  mp_add(&temp5, a, &temp6);
          mp_mulmod(&temp6, &tempk, p, &k);
		  
	   }
	   else
	   {
		  zero=true;
		  goto L;
	   }
   }  
 
   mp_sqr(&k, &temp7);
   mp_sub(&temp7, x1, &temp8);
   mp_submod(&temp8, x2, p, x3);
 
   mp_sub(x1, x3, &temp9);
   mp_mul(&temp9, &k, &temp10);
   mp_submod(&temp10, y1, p, y3);


L:

   mp_clear(&x2x1);
   mp_clear(&y2y1);
   mp_clear(&tempk);
   mp_clear(&tempy);
   mp_clear(&tempzero);
   mp_clear(&k);
   mp_clear(&temp1);
   mp_clear(&temp2);
   mp_clear(&temp3);
   mp_clear(&temp4);
   mp_clear(&temp5);
   mp_clear(&temp6);
   mp_clear(&temp7);
   mp_clear(&temp8);
   mp_clear(&temp9);
   mp_clear(&temp10);

   return 1;
}

int CEnciperDlg::chmistore(mp_int *a, FILE *fp)
{//�����ƴ洢����

	   int i,j;
   char ch;
   char chtem[4];

   mp_digit yy=(mp_digit)255;
   for (i=0; i <= a->used - 1;  i++) { 

      chtem[3]=(char)(a->dp[i] & yy);     
      chtem[2]=(char)((a->dp[i] >> (mp_digit)8) & yy);	    
	  chtem[1]=(char)((a->dp[i] >> (mp_digit)16) & yy);    
      chtem[0]=(char)((a->dp[i] >> (mp_digit)24) & yy);

      for(j=0;j<4;j++)
	  {
	      fprintf(fp,"%c",chtem[j]);
	  }
      
  }  

  ch=char(255);
  fprintf(fp, "%c", ch);
  return MP_OKAY;
}

int CEnciperDlg::putin(mp_int *a, char *ch, int chlong)
{//�Ѷ�ȡ���ַ�����mp_int����

		mp_digit *temp,yy;
	int i,j,res;
	if(a->alloc<chlong*2/7+2)
	{
		if((res=mp_grow(a,chlong*2/7+2))!=MP_OKAY)
			return res;
	}
    
	a->sign=0;
	mp_zero(a);
	temp=a->dp;
	i=0;
	yy=(mp_digit)15;

	if(chlong<4)
	{
            for(j=chlong-1;j>=0;j--)
			{
			   *temp |= (mp_digit)(ch[j] & 255);
               *temp <<= (mp_digit)CHAR_BIT;
			}
			*temp >>= (mp_digit)8;
			a->used=1;
			return MP_OKAY;
	}

	if(chlong<7)
	{
	        i+=4;
            *++temp |= (mp_digit)(ch[i-1] & yy);
		    *temp <<= (mp_digit)CHAR_BIT;
            *temp |= (mp_digit)(ch[i-2] & 255);
		    *temp <<= (mp_digit)CHAR_BIT;
            *temp |= (mp_digit)(ch[i-3] & 255);
		    *temp <<= (mp_digit)CHAR_BIT;
            *temp-- |= (mp_digit)(ch[i-4] & 255); //��ű��зֵ��ַ��ĵ���λ

            
            for(j=chlong-1;j>=i;j--)
			{  
			   *temp |= (mp_digit)(ch[j] & 255);
			   *temp <<= (mp_digit)CHAR_BIT;			                
			}
            *temp >>= (mp_digit)4;
            *temp |= (mp_digit)((ch[i-1] & 255) >> 4);  //��ű��зֵ��ַ��ĸ���λ
            
			a->used=2;
			return MP_OKAY;
	}

        //��7���ַ�Ϊ��Ԫѭ�������߸��ַ������mp_int ��������Ԫ��
	for(j=0;j<chlong/7;j++)
	{
		i+=7;
		*++temp |= (mp_digit)(ch[i-1] & 255);
		*temp <<= (mp_digit)CHAR_BIT;
        *temp |= (mp_digit)(ch[i-2] & 255);
		*temp <<= (mp_digit)CHAR_BIT;
        *temp |= (mp_digit)(ch[i-3] & 255);
		*temp <<= (mp_digit)4;
        *temp-- |= (mp_digit)((ch[i-4] & 255) >> 4);    //��ű��зֵ��ַ��ĸ���λ

		*temp |= (mp_digit)(ch[i-4] & yy);      //��ű��зֵ��ַ��ĵ���λ
        *temp <<= (mp_digit)CHAR_BIT;
        *temp |= (mp_digit)(ch[i-5] & 255);
		*temp <<= (mp_digit)CHAR_BIT;
        *temp |= (mp_digit)(ch[i-6] & 255);
		*temp <<= (mp_digit)CHAR_BIT;
        *temp++ |= (mp_digit)(ch[i-7] & 255); 

		temp++;
	
	}
 
	if((chlong>=7)&&(chlong%7!=0))        //ʣ���ַ��Ĵ��
	{
		if(chlong%7 < 4)           //ʣ���ַ�����4��ʱ��ֻ��һ��mp_digit��Ԫ���
		{
			for(j=chlong-1;j>=i;j--)
			{
			   *temp |= (mp_digit)(ch[j] & 255);
               *temp <<= (mp_digit)CHAR_BIT;
			}
			*temp >>= (mp_digit)8;
			a->used=chlong*2/7+1;
		}
		else
		{                       //ʣ���ַ���С��4��ʱ��������mp_digit��Ԫ���
			i+=4;
            *temp |= (mp_digit)(ch[i-1] & yy);
		    *temp <<= (mp_digit)CHAR_BIT;
            *temp |= (mp_digit)(ch[i-2] & 255);
		    *temp <<= (mp_digit)CHAR_BIT;
            *temp |= (mp_digit)(ch[i-3] & 255);
		    *temp <<= (mp_digit)CHAR_BIT;
            *temp++ |= (mp_digit)(ch[i-4] & 255); //��ű��зֵ��ַ��ĵ���λ

            
            for(j=chlong-1;j>=i;j--)
			{  
			   *temp |= (mp_digit)(ch[j] & 255);
			   *temp <<= (mp_digit)CHAR_BIT;			                
			}
            *temp >>= (mp_digit)4;
            *temp |= (mp_digit)((ch[i-1] & 255) >> 4);  //��ű��зֵ��ַ��ĸ���λ
            
			a->used=chlong*2/7+2;
		}

	}
	else
	{
	   a->used=chlong*2/7;
	}
	return MP_OKAY;
}


int CEnciperDlg::chdraw(mp_int *a, char *ch)
{//ʵ�ֽ�mp_int��a�еı��ش���ԭΪ�ַ����������ַ���ch��

		int i,j;
	mp_digit *temp,xx,yy;

	temp=a->dp;
	i=0;
	yy=(mp_digit)255;  //����λ�����㣬ȡ��λ���ش�
	xx=(mp_digit)15;  //����λ�����㣬ȡ��λ���ش�

	for(j=0;j<a->used/2;j++)  //��������ԪΪѭ������������Ԫ�ı��ش�����7���ַ�
	{
		i+=7;
        ch[i-4]=(char)(*++temp & xx);
        ch[i-3]=(char)((*temp >> (mp_digit)4) & yy);	
		ch[i-2]=(char)((*temp >> (mp_digit)12) & yy);
        ch[i-1]=(char)((*temp-- >> (mp_digit)20) & yy);

		ch[i-7]=(char)(*temp & yy);
		ch[i-6]=(char)((*temp >> (mp_digit)8) & yy);
		ch[i-5]=(char)((*temp >> (mp_digit)16) & yy);
		ch[i-4] <<= 4;
		ch[i-4]+=(char)((*temp++ >> (mp_digit)24) & xx);
		temp++;
	}
	if(a->used%2!=0)  //ʣ��һ����Ԫ�Ĵ���
	{
		ch[i++] = (char)(*temp & yy);
		ch[i++] = (char)((*temp >> (mp_digit)8) & yy);
		ch[i++] = (char)((*temp >> (mp_digit)16) & yy);
	}
	--i;
    while(int(ch[i]&0xFF) != 255 && i>0) i--;
	return i;
}

unsigned int CEnciperDlg::SDBMHash16(char *str)
{//��������ַ�������Hashֵ�����Ϊһ��32λ������

	unsigned int hash = 0;

  
     while (*str)
      {
         // equivalent to: hash = 65599*hash + (*str++);
         hash = (*str++) + (hash << 6) + (hash << 16) - hash;
     }
  
     return (hash & 0xFFFF);
}

void CEnciperDlg::NumToStr(unsigned __int64 a, char z[])
{

		int i=0;
	//char z[100];
	while(a!=0)
	{
		z[i]=a%10+48;
		a=a/10;
		i++;
	}
}

void CEnciperDlg::Hashstring(char temphash[], unsigned __int64 *hash, int n1)
{

		int h[20000];
	int num=1,i;
	char c[4],h1[16];

	int hash1,j=0,j1,j2=0;
	for(i=0;i<n1;i++)
	{
		itoa(i,c,10);
		strcat(temphash,c);
		hash1=SDBMHash16(temphash);
		itoa(hash1,h1,2);
		j1=j+16;
		j2=0;
		for(;j<j1;j++)
		{
			h[j]=h1[j2];
			j2++;
		}
	}
	for(i=0;i<j-1;i++)
	{
		*hash+=h[j]*num;
		num*=2;
	}
}



unsigned int CEnciperDlg::SDBMHash32(char *str)
{

	unsigned int hash = 0;

  
     while (*str)
      {
         // equivalent to: hash = 65599*hash + (*str++);
         hash = (*str++) + (hash << 6) + (hash << 16) - hash;
     }
  
     return (hash & 0x7FFFFFFF);
}

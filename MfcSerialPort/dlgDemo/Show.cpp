// Show.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "Show.h"
#include "math.h"
#include  "dlgDemoDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define PI 3.1415926
#define B 0
#define G 1
#define R 2
int ColorTranTable[3][256];
unsigned char *pBmpBuf24;
/////////////////////////////////////////////////////////////////////////////
// CShow dialog


CShow::CShow(CWnd* pParent /*=NULL*/)
	: CDialog(CShow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShow)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	With=CDlgDemoDlg::bmpInfo.biWidth;
	Height=CDlgDemoDlg::bmpInfo.biHeight;
	Withbytes=(((With * 24) + 31) & (~31)) / 8 ; //每行实际占用的大小（每行都被填充到一个4字节边界）
	dataByte=CDlgDemoDlg::bmpHeader.bfSize - CDlgDemoDlg::bmpHeader.bfOffBits;
	pBmpData=(BYTE*)new char[dataByte];
	picsavepath="e:\\Capture";
}


void CShow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShow)
	DDX_Control(pDX, IDC_STATI_PICTURE, m_picture);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShow, CDialog)
	//{{AFX_MSG_MAP(CShow)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_Denoise, OnDenoise)
	ON_BN_CLICKED(IDC_INCREASE, OnIncrease)
	ON_BN_CLICKED(IDC_RESERVER, OnReserver)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_VisualColor, OnVisualColor)
	ON_BN_CLICKED(IDC_PictureIncrease, OnPictureIncrease)
	//}}AFX_MSG_MAP
	ON_STN_CLICKED(IDC_STATI_PICTURE, &CShow::OnStnClickedStatiPicture)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShow message handlers

void CShow::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	 //定义变量存储图片信息
    BITMAPINFO *pBmpInfo;       //记录图像细节
	With=CDlgDemoDlg::bmpInfo.biWidth;
	Height=CDlgDemoDlg::bmpInfo.biHeight;
	Withbytes=(((With * 24) + 31) & (~31)) / 8 ; //每行实际占用的大小（每行都被填充到一个4字节边界）
	pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];
	//为图像数据申请空间
	memcpy(pBmpInfo,&(CDlgDemoDlg::bmpInfo),sizeof(BITMAPINFOHEADER));
	DWORD dataBytes = CDlgDemoDlg::bmpHeader.bfSize - CDlgDemoDlg::bmpHeader.bfOffBits;
	//显示图像
	CWnd *pWnd=GetDlgItem(IDC_STATI_PICTURE); //获得pictrue控件窗口的句柄
	CRect rect;
	pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域
	CDC *pDC=pWnd->GetDC(); //获得pictrue控件的DC
	pDC->SetStretchBltMode(COLORONCOLOR);
	StretchDIBits(pDC->GetSafeHdc(),0,0,rect.Width(),rect.Height(),0,0,
			CDlgDemoDlg::bmpInfo.biWidth,CDlgDemoDlg::bmpInfo.biHeight,pBmpData,pBmpInfo,DIB_RGB_COLORS,SRCCOPY);
	delete [] pBmpInfo;
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CShow::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//记录图像细节
	BYTE *tempData;
	BYTE *p_temp=NULL;
	BYTE *ptemp1=NULL;//图像数据
	With=CDlgDemoDlg::bmpInfo.biWidth;
	Height=CDlgDemoDlg::bmpInfo.biHeight;
	Withbytes=(((With * 24) + 31) & (~31)) / 8 ; //每行实际占用的大小（每行都被填充到一个4字节边界）
	//为图像数据申请空间
	DWORD dataBytes = CDlgDemoDlg::bmpHeader.bfSize - CDlgDemoDlg::bmpHeader.bfOffBits;
	tempData = (BYTE*)new char[dataBytes];
	memcpy(tempData,CDlgDemoDlg::Globbuff,dataBytes);
    /*翻转图像*///p_temp1=pdata+j*sizeImageSave.cx; p_temp[i]
	for(int j=Height-1,k=0;j>=0;j--,k++)
	{
		p_temp=tempData+j*Withbytes;
		ptemp1=pBmpData+k*Withbytes;
		for(unsigned int i=0;i<Withbytes;i++)
		{
			ptemp1[i]=p_temp[i];
			
		}
			
	}
	delete [] tempData;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CShow::OnDenoise() 
{
	// TODO: Add your control notification handler code here
    BYTE *p_temp1=NULL,*p_temp2=NULL;//=new BYTE[nWidth*nHeight];//临时数据缓冲区
    //普通中值滤波
    int yy,xx,n2,nn,chuo,chg,m,medi,madom,mado[10],i;
    int min,max;//窗口中排序后的最小值和最大值;
    int n=3;//n为滤波矩阵数
	unsigned int j;
    n2=(n-1)/2;
    nn=n*n;
    chuo=(nn-1)/2;
	/*普通中值滤波*/
    for(j=n2;j<Height-n2;j++)
    {
	//把n*n屏蔽窗口部分的所有像素值放入mado[m]
	  for(i=n2;i<Withbytes-n2;i++)
		m=0;
		p_temp1=pBmpData+j*Withbytes;
		for(yy=j-n2;yy<=j+n2;yy++)
		{
			p_temp2=pBmpData+yy*Withbytes;
			for(xx=i-n2;xx<=i+n2;xx++)
			{
				mado[m]=p_temp2[xx];
		     	m++;
			}
		}
		//把mado[m]数据排序（冒泡）
		do
		{
			chg=0;
			for(m=0;m<nn-1;m++)
			{
				if(mado[m]<mado[m+1])
				{
					madom=mado[m];
					mado[m]=mado[m+1];
					mado[m+1]=madom;
					chg=1;
				}
			}
		}while(chg==1);
        medi=mado[chuo];
		//把中值放入临时缓冲区
		p_temp1[i]=medi;

   }
   /*改进的max-min算子检测器*/
    /*for( int j=n2;j<Height-n2;j++)
	{
		 p_temp1=pBmpData+j*Withbytes;
		 for(  int i=n2;i<Withbytes-n2;i++)
		 {
		//把n*n屏蔽窗口部分的所有像素值放入mado[m]
			m=0;
			for(yy=j-n2;yy<=j+n2;yy++)
			{	
					p_temp2=pBmpData+yy*Withbytes;
					for(xx=i-n2;xx<=i+n2;xx++)
					{
						mado[m]=p_temp2[xx];
		     			m++;
					}
			}
			//把mado[m]数据排序（冒泡）
			do
			{
				chg=0;
				for(int l=0;l<m;l++)
				{
					if(mado[l]<mado[l+1])
					{
						madom=mado[l];
						mado[l]=mado[l+1];
						mado[l+1]=madom;
						chg=1;
					}
				}
			}while(chg==1);
			max=mado[0];
			min=mado[m-1];
			int k=0;//窗口内非噪声点个数
			double cout=0;//窗口内非噪声点像素值之和
			double mean=0,std=0;//mean为非噪声点的平均值，std为均方差；
			double temp=0.0;
			int num=0;
			int temp1[10];
			//判断窗口内是否存在某点介于最大最小之间，存在则该窗口内有有效像素，不存在则说明该窗口全为噪声
			for(yy=0;yy<m;yy++)
			{
				if(mado[yy]<max&&mado[yy]>min)
				{
					if((p_temp1[i]==min)||(p_temp1[i]==max))//pdata[j*wide+i]为xij的坐标
					{
						for(yy=0;yy<m;yy++)
						{
							if((mado[yy]!=max)&&(mado[yy]!=min))
							{
								cout+=mado[yy];
								k++;
								temp1[num++]=mado[yy];
							}
						}
						mean=cout/(k*1.00);
						for(yy=0;yy<m;yy++)
						{
							if((mado[yy]!=max)&&(mado[yy]!=min))
							{
								temp+=pow(mado[yy]-mean,2);
							}
						}
						temp=temp/(k*1.00);
						std=sqrt(temp);
						if(fabs((p_temp1[i]-mean))>std)
						{
						   do
							{
								chg=0;
								for(yy=0;yy<num;yy++)
								{
									if(temp1[yy]<temp1[yy+1])
									{
										madom=temp1[yy];
										temp1[yy]=temp1[yy+1];
										temp1[yy+1]=madom;
										chg=1;
									}
								}
							}while(chg==1);
							if(num%2==1)
								medi=temp1[(num-1)/2];
							else
								medi=(temp1[(num-2)/2]+temp1[num/2])/2;
							//把中值放入临时缓冲区
							p_temp1[i]=medi;

						}
						else
							 p_temp1[i]=p_temp1[i];
					}
					break;
				}
			}
		 }
	}*/
	Invalidate();
}

//图像锐化
void CShow::OnIncrease() 
{
	// TODO: Add your control notification handler code here
			//记录图像细节
	BYTE *tempData;
	BYTE *p_temp=NULL;
	BYTE *ptemp1=NULL;//图像数据
	With=CDlgDemoDlg::bmpInfo.biWidth;
	Height=CDlgDemoDlg::bmpInfo.biHeight;
	Withbytes=(((With * 24) + 31) & (~31)) / 8 ; //每行实际占用的大小（每行都被填充到一个4字节边界）
	//为图像数据申请空间
	DWORD dataBytes = CDlgDemoDlg::bmpHeader.bfSize - CDlgDemoDlg::bmpHeader.bfOffBits;
	tempData = (BYTE*)new char[dataBytes];
	memset(tempData,0,dataBytes);
	BYTE temp;
	BYTE *lpSrc;
	BYTE *lpSrc1;
	BYTE *lpSrc2;
	for(unsigned int i=0;i<Height-1;i++)
	{
		for(unsigned int j=0;j<Withbytes-1;j++)
		{
			lpSrc=(BYTE *)pBmpData+Withbytes*i+j;
			lpSrc1=(BYTE *)pBmpData+Withbytes*(i+1)+j;
			lpSrc2=(BYTE *)pBmpData+Withbytes*i+j+1;
			temp=abs((*lpSrc)-(*lpSrc1))+abs((*lpSrc)-(*lpSrc2));
			if(temp>=10)
			{
				if((*lpSrc+30)>=255)
					*lpSrc=255;
				else
					*lpSrc=*lpSrc+30;
			}
			else
				*lpSrc=*lpSrc;
		}
			
	}
	delete [] tempData;
	Invalidate();
}

void CShow::OnReserver() 
{
	// TODO: Add your control notification handler code here
	BYTE *p_temp=NULL;
	With=CDlgDemoDlg::bmpInfo.biWidth;
	Height=CDlgDemoDlg::bmpInfo.biHeight;
	Withbytes=(((With * 24) + 31) & (~31)) / 8 ; //每行实际占用的大小（每行都被填充到一个4字节边界）
	for(unsigned int j=0;j<Height;j++)
	{
		p_temp=pBmpData+j*Withbytes;
		for(unsigned int i=0;i<Withbytes;i++)
		{
			p_temp[i]=255-p_temp[i];	
		}
			
	}
	Invalidate();
}

void CShow::OnSave() 
{
	// TODO: Add your control notification handler code here
	CTime time = CTime::GetCurrentTime();
			//文件名
    CString strPath = picsavepath+"\\" + time.Format("%Y%m%d-%H%M%S.bmp");
	int widthStep = (((With * 24) + 31) & (~31)) / 8 ; //每行实际占用的大小（每行都被填充到一个4字节边界）  
	int DIBSize = widthStep * Height ;  //buffer的大小 （字节为单位） 
	TCHAR BMPFileName[1024]; 
	strcpy(BMPFileName,strPath);  
	CFile file;  
	try  
	{  
		if(file.Open(BMPFileName,CFile::modeWrite | CFile::modeCreate))  
		{//写入文件  
			
			file.Write((LPSTR)&(CDlgDemoDlg::bmpHeader),sizeof(BITMAPFILEHEADER));  
			file.Write((LPSTR)&(CDlgDemoDlg::bmpInfo),sizeof(BITMAPINFOHEADER));  
			file.Write(pBmpData,DIBSize);  
			file.Close(); 
		}  
		
	} 
	catch (...)   
	{  
		AfxMessageBox("MyDC::SaveDIB2Bmp");  
	} 
	::AfxMessageBox("Snap Bmp Ok!: "+strPath);

	
}

void CShow::OnExit() 
{
	// TODO: Add your control notification handler code here
	EndDialog(IDC_EXIT);
}

void CShow::OnVisualColor() 
{
	// TODO: Add your control notification handler code here
	BYTE *p_temp=NULL;
	With=CDlgDemoDlg::bmpInfo.biWidth;
	Height=CDlgDemoDlg::bmpInfo.biHeight;
	Withbytes=(((With * 24) + 31) & (~31)) / 8 ; //每行实际占用的大小（每行都被填充到一个4字节边界）
	
	//位图数据的指针
	unsigned char *imgData=pBmpData;
		//为图像数据申请空间
	DWORD dataBytes = CDlgDemoDlg::bmpHeader.bfSize - CDlgDemoDlg::bmpHeader.bfOffBits;
	double degree;
	//循环变量，图像坐标
	int i,j;
	for(i=0;i<=255;i++)
	{
		//将1-255的图像信息编程PI，进行正弦和余弦函数的计算
			degree=i*3*PI*(1.0/255)/2;
			if(degree<=PI/2&&degree>=0)
			{
				ColorTranTable[B][i]=cos(degree)*255;
				ColorTranTable[G][i]=sin(degree)*255;
				ColorTranTable[R][i]=0;
			}
			else if(degree>PI/2 && degree<=PI)
			{
				ColorTranTable[B][i]=0;
				ColorTranTable[G][i]=sin(degree)*255;
				ColorTranTable[R][i]=-cos(degree)*255;
			}
			else if(degree>PI && degree<=PI*3/2)
			{
				ColorTranTable[B][i]=-sin(degree)*255;
				ColorTranTable[G][i]=0;
				ColorTranTable[R][i]=-cos(degree)*255;
			}
	}
	pBmpBuf24=new unsigned char[Withbytes *Height];
	
	int val;
	//得到24位的数据
	for(i=0;i<Height;i++)
	{
		for(j=0;j<(Withbytes-3)/3;j++)
		{
             if((*(pBmpData+i*Withbytes+3*j+0))<120)
			 {
				 *(pBmpBuf24+i*Withbytes+3*j+0)=ColorTranTable[B][*(imgData+i*Withbytes+3*j+0)];//blue
				*(pBmpBuf24+i*Withbytes+3*j+1)=ColorTranTable[G][*(imgData+i*Withbytes+3*j+1)];//green
				*(pBmpBuf24+i*Withbytes+3*j+2)=ColorTranTable[R][*(imgData+i*Withbytes+3*j+2)];//red
			 }
				
		}
	}
	memcpy(pBmpData,pBmpBuf24,dataBytes);
	delete [] pBmpBuf24;
	//刷新显示
	Invalidate();
}

void CShow::OnPictureIncrease() 
{
	// TODO: Add your control notification handler code here
	
//	Once(1);
	LowIncrease();
	//IDWT(1);
}
/*
	void Once(int n);
	void IDWT (int n);
	void LowIncrease();
**/
//对小波变换后的低频区域做增强处理,线性增强，小波的效果还不如线性增强
void CShow::LowIncrease()
{
	int originmin,lastmin,j;
	int originmax,lastmax;
	originmin=*pBmpData;
	originmax=*pBmpData;
	lastmin=0;
	lastmax=255;
	// TODO: Add your control notification handler code here
	BYTE *p_temp=NULL;
	for(unsigned int j=0;j<Height;j++)
	{
		p_temp=pBmpData+j*Withbytes;
		for(unsigned int i=0;i<Withbytes;i++)
		{
		   if(p_temp[i]<=originmin)
			   	originmin=p_temp[i];
		   if(p_temp[i]>=originmax)
				originmax=p_temp[i];
		}
			
	}
	//线性灰度变换
    for(j=0;j<Height;j++)
	{
		p_temp=pBmpData+j*Withbytes;
		for(unsigned int i=0;i<Withbytes;i++)
		{
		   if(p_temp[i]<=originmin)
			   p_temp[i]=lastmin;
		  else if(p_temp[i]>=originmax)
			  p_temp[i]=255;
		  else
			  p_temp[i]=((lastmax-lastmin)/(originmax-originmin))*( p_temp[i]-originmin)+lastmin;
		}
			
	}
	/*float gamma=0.6;
	double  temp=0.00;
	for( j=0;j<Height;j++)
	{
		p_temp=pBmpData+j*Withbytes;
		for(unsigned int i=0;i<Withbytes;i++)
		{
	    	temp= (double)	p_temp[i]/lastmax;
			p_temp[i]=pow(temp,gamma)*lastmax;
		}
	
	}*/
	//刷新显示
	Invalidate();
}


/********************************************************************************
*函数描述：	Once实现小波变换
*函数参数：	int n 小波变换的层数 
*函数返回值：函数无返回值						  
*********************************************************************************/
void CShow::Once(int n)
{
	int i,j;
	LONG wide,height,nWide,nHeight;
	LPBYTE temp1, temp2,m_pData2;
	for(int k=1;k<=n;k++)
    {
		wide=Withbytes;
		height=Height;
		m_pData2=pBmpData;
		//分配临时数据空间
		temp1 = new BYTE[height*wide];
		temp2 = new BYTE[height*wide];
		nWide=wide/pow(2.,k);
		nHeight=height/pow(2.,k);
		//完成行变换
		for(j = height*(1-1/pow(2.,(k-1))); j < height; j ++)            
		{
			for(i = 0; i < nWide; i ++)           
			{
				int w = i *2;
				temp1[j*wide+i] = m_pData2[j*wide+w];		//偶
				temp1[j*wide+nWide+i] = m_pData2[j*wide+w+1];	//奇
			}
		}
		//通过图像的差分，完成小波变换
		for(j= height*(1-1/pow(2.,(k-1))); j<height; j++)
		{
			for(i=0; i<nWide-1; i++)
			{
				temp1[j*wide+nWide-1+i] =temp1[j*wide+nWide-1+i] - temp1[j*wide+i]+128;	
			}
		}
		//完成列变换
		for(i = 0; i < wide/pow(2.,k-1); i ++)            
		{
			for(j =  height*(1-1/pow(2.,(k-1))); j <  height*(1-1/pow(2.,(k-1)))+nHeight; j ++)           
			{
				int m, h;
				m=height*(1-1/pow(2.,(k-1)));
				h= (j-m)*2 ;
				temp2[j*wide+i] = temp1[(m+h)*wide+i];		//even
				temp2[(nHeight + j)*wide+i] = temp1[(m+h+1)*wide+i];	//odd
			}
		}
		//通过图像的差分，完成小波变换
		for(i=0; i<wide/pow(2.,k-1); i++)
		{
			for(j =  height*(1-1/pow(2.,(k-1))); j <  height*(1-1/pow(2.,(k-1)))+nHeight; j ++) 
			{
				temp2[ j*wide+i] = temp2[j*wide+i]-temp2[(nHeight + j)*wide+i]+128;
			}
		}
		//小波经过处理后，放入显示缓存中
		for(j = height*(1-1/pow(2.,(k-1))); j < height; j ++)    
		{
			for(i=0; i<wide/pow(2.,k-1); i++)
			{
				m_pData2[j*wide+i]  = temp2[j*wide+i];
			}
		}
		//删除临时的数据空间
		delete temp1;
		delete temp2;
	}

}

/********************************************************************************
*函数描述：	IDWT 实现小波反变换
*函数参数：	int n 小波变换的层数 
*函数返回值：函数无返回值						  
*********************************************************************************/
void CShow::IDWT(int n)
{
	int i,j;
	LONG wide,height,nWide,nHeight;
	LPBYTE temp1, temp2,temp3,m_pData2;
	for(int k=n;k>=1;k--)
    {
		wide=Withbytes;
		height=Height;
		m_pData2=pBmpData;
		//分配临时数据空间
		temp1 = new BYTE[height*wide];
		temp2 = new BYTE[height*wide];
		temp3 = new BYTE[height*wide];
		nWide=wide/pow(2.,k);
		nHeight=height/pow(2.,k);
		memcpy(temp1,m_pData2,height*wide);
		for(i=0; i<wide/pow(2.,k-1); i++)
		{
			for(j =  height*(1-1/pow(2.,(k-1))); j <  height*(1-1/pow(2.,(k-1)))+nHeight; j ++) 
			{
				temp1[ j*wide+i]=temp1[(nHeight + j)*wide+i]+ temp1[j*wide+i]-128;
			}
		}
		for(i = 0; i < wide/pow(2.,k-1); i ++)            
		{
			for(j =  height*(1-1/pow(2.,(k-1))); j <  height*(1-1/pow(2.,(k-1)))+nHeight; j ++)           
			{
				int m, h;
				m=height*(1-1/pow(2.,(k-1)));
				h= (j-m)*2 ;
				temp2[(m+h)*wide+i]=temp1[j*wide+i];
				temp2[(m+h+1)*wide+i]=temp1[(nHeight + j)*wide+i];
			}
		}
		for(j= height*(1-1/pow(2.,(k-1))); j<height; j++)
		{
			for(i=0; i<nWide-1; i++)
			{
				temp2[j*wide+nWide+i] += temp2[j*wide+i]-128;	
			}
		}
		for(j = height*(1-1/pow(2.,(k-1))); j < height; j ++)            
		{
			for(i = 0; i < nWide; i ++)           
			{
				int w = i *2;
				temp3[j*wide+w]=temp2[j*wide+i];
				temp3[j*wide+w+1]=temp2[j*wide+nWide+i];
			}
		}		
		//小波经过处理后，放入显示缓存中
		for(j = height*(1-1/pow(2.,(k-1))); j < height; j ++)    
		{
			for(i=0; i<wide/pow(2.,k-1); i++)
			{
				m_pData2[j*wide+i]  = temp3[j*wide+i];
			}
		}
		//删除临时的数据空间
		delete temp1;
		delete temp2;
	}
}



void CShow::OnStnClickedStatiPicture()
{
	// TODO: 在此添加控件通知处理程序代码
}

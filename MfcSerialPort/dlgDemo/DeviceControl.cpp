// DeviceControl.cpp: implementation of the DeviceControl class.
//  video device sdk class
//  write by tony yu  2810482962@qq.com
///  copyright shenzhen zhongan vision
//  2013/12
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dlgDemo.h"
#include "DeviceControl.h"
#include "dlgDemoDlg.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DeviceControl::DeviceControl()
{
	

}

DeviceControl::~DeviceControl()
{

}
int DeviceControl::InitDevice ()
{
	int NumDevice;
	DXInitialize();
	NumDevice=DXGetDeviceCount();
	return NumDevice;

}
void DeviceControl::UnInitDevice ()
{

	DXUninitialize();
	
}
HANDLE DeviceControl::OpenDevice(int nCard,unsigned*OpenDevState)
{

	HANDLE DeviceChancel;
	DeviceChancel=DXOpenDevice(nCard,OpenDevState);
	return DeviceChancel;
	
}
void DeviceControl::CloseDevice(HANDLE ChannelHandle)
{

	DXCloseDevice(ChannelHandle);
	
}

BOOL DeviceControl::ConnectDevice(HANDLE ChannelHandle, int VideoStandard, int ColorSpace,int nWidth, int nHeight, float FrameRate)
{
	DXSetVideoPara(ChannelHandle,VideoStandard,ColorSpace,nWidth,nHeight,FrameRate);
	if (DXDeviceRun(ChannelHandle)==0)
	{

		return true;
	}
	else
	{

		return false;
	}
	
}
// set video source
BOOL DeviceControl::SetVideoSource(HANDLE ChannelHandle,unsigned VidSource)
{
	int ok=1;
	unsigned char SourceNum=10;
	//�õ��豸����Ƶ����Դ��������ֻ��һ���Ͳ�����
	DXGetVideoSources(ChannelHandle,NULL,NULL,&SourceNum);
	if (SourceNum>1)
	{

			ok=DXSetVideoSource(ChannelHandle,VidSource);
		
	}

	if(ok==0)
	{

		return true ;
	}
	else
	{

		return false;
	}
	
}
void DeviceControl::DisConnectDevice(HANDLE ChannelHandle )
{

	DXStopPreview(ChannelHandle);
	DXDeviceStop(ChannelHandle);
}
BOOL DeviceControl::GetVideoPara(HANDLE ChannelHandle, unsigned& nWidth, unsigned& nHeight, unsigned& ColorSpace, unsigned& VideoStandard, float& FrameRate)
{


	DXGetVideoPara(ChannelHandle,VideoStandard,ColorSpace,nWidth,nHeight,FrameRate);
	return true ;
}
BOOL DeviceControl::StartPrview(HANDLE ChannelHandle,HWND PrvHwnd,PRECT rect, unsigned PrvModle,bool PrvEnable)
{
	if(PrvEnable)
	{
			DXStartPreview(ChannelHandle,PrvHwnd,rect,PrvModle);
	}
	return true;
	
}
BOOL DeviceControl::StopPrview(HANDLE ChannelHandle)
{
	DXStopPreview(ChannelHandle);
	return true;
}
BOOL DeviceControl::FreezePreview(HANDLE ChannelHandle,BOOL bFreeze)
{
	DXFreezePreview(ChannelHandle,bFreeze);
	return true;
}

//get video signal
BOOL DeviceControl::GetSignalPresent(HANDLE ChannelHandle, unsigned& signal)
{
	//0 NoSignal 1: signal is ok
	DXGetSignalPresent(ChannelHandle,signal);
	return true;
}

//snap pciture
BOOL DeviceControl::SnapPicture(HANDLE ChannelHandle, TCHAR* szFileName,int PictureType, PRECT rect)
{
	int ok=1;
	if (PictureType==0)
	{
		ok=DXSnapToBMPFile(ChannelHandle,szFileName,rect);
	}
	else
	{
		ok=DXSnapToJPGFile(ChannelHandle,szFileName,100,rect);
	}
	if(ok==0)
	{

		return true ;
	}
	else
	{

		return false;
	}

}
// video flip
BOOL DeviceControl::SetVideoFlip(HANDLE ChannelHandle,BOOL FlipEnable)
{
	int ok=1;
	ok=DXFlipVideo(ChannelHandle,FlipEnable);
	if (ok==0)
	{

		return true;
	}
	else

	{
			return false;
		
	}
}

// video mirro
BOOL DeviceControl:: SetVideoMirro(HANDLE ChannelHandle,BOOL MirroEnable)
{
	int ok=1;
	ok=DXMirrorVideo(ChannelHandle,MirroEnable);
	if (ok==0)
	{

		return true;
	}
	else

	{
			return false;
		
	}
}


// osd para
BOOL DeviceControl::SetOSDPara(HANDLE ChannelHandle, unsigned OsdType, int OsdNo, LPCTSTR OsdFile, int x, int y, int pointSize, LPCTSTR faceName, COLORREF OSDcolor, COLORREF Backcolor, BOOL transparent, unsigned char PicAlpha)
{
	int ok=1;
	switch(OsdType)
	{
			case 0:
				
					ok=DXSetTimeOSD(ChannelHandle,x,y,pointSize,faceName,OSDcolor,Backcolor,transparent);
			
			break;
			case 1:
				
								
					ok=DXSetTextOSD(ChannelHandle,x,y,OsdNo,OsdFile,pointSize,faceName,OSDcolor,Backcolor,transparent);
				
		
			break;
			case 2:
			
					ok=DXSetPictureOSD(ChannelHandle,x,y,OsdNo,OsdFile,transparent);
		
			break;
			
		
	}
	if (ok==0)
	{

		return true;
	}
	else

	{
			return false;
		
	}

}
///



/// start osd
BOOL DeviceControl::StartOsd(HANDLE ChannelHandle,unsigned OsdType,int OsdNo,BOOL OSDEnable)
{
	int ok=1;
	ok=DXEnOSDDisp(ChannelHandle,OsdType,OsdNo,OSDEnable);
	if (ok==0)
	{

		return true;
	}
	else

	{
			return false;
		
	}
}



// enable deinterlace
BOOL DeviceControl:: EnableDeinterlace(HANDLE ChannelHandle,int DeintType,BOOL enable)
{
	int ok=1;
	ok=DXEnableDeinterlace(ChannelHandle,DeintType);
	if(enable==false)
	{
			ok=DXEnableDeinterlace(ChannelHandle,-1);
	}

	if (ok==0)
	{

		return true;
	}
	else

	{
			return false;
		
	}
}
BOOL DeviceControl::GetCurBuffer(HANDLE ChannelHandle,
								 unsigned BufType,
								unsigned char* pbuffer,
								unsigned bufferLen,
								unsigned width,
								unsigned height,
								BOOL EnableFilp)
{


	int ok=1;

	switch(BufType)
	{
		case 0:
			ok=DXGetFrameBuffer(ChannelHandle,pbuffer,bufferLen,NULL,NULL,&width,&height,NULL,NULL);	
			break;
		case 1:
			unsigned char* buffer = new unsigned char[bufferLen];
			ok=DXGetFrameBuffer(ChannelHandle,buffer,bufferLen,NULL,NULL,&width,&height,NULL,NULL);
			DXConvertYUVtoRGB(ChannelHandle,buffer,pbuffer,width,height,EnableFilp,false);
			break;
			
	}

		if (ok==0)
	{

		return true;
	}
	else

	{
			return false;
		
	}
}
// yuv2 to rgb24
BOOL DeviceControl:: ConvertYUVtoRGB(HANDLE ChannelHandle,
						void* pYUVBuf,
						void* pRGBBuf,
						long lImgWidth, 
						long lImgHeight,
						BOOL bInverted,
						BOOL bInvertColor)
{
	int ok=1;
	ok=DXConvertYUVtoRGB(ChannelHandle,
						pYUVBuf,
						pRGBBuf,
						lImgWidth,
						lImgHeight,
						bInverted,
						bInvertColor);
	if (ok==0)
	{
		return true;
	}
	else

	{
			return false;
	}

}

//����buffer��bmp�ļ�  

//iWidth��ͼ��� iHeight��ͼ��ߣ�pBuffer��ͼ��RGB���ݣ�
bool DeviceControl::SaveRGBToBmp( const char * fileName,  int iWidth, int iHeight, BYTE *pBuffer)  
{  
	
	BITMAPINFOHEADER bih;  
	DeviceControl::ConstructBih(iWidth,iHeight,bih);  
	BITMAPFILEHEADER bhh;  
	DeviceControl::ContructBhh(iWidth,iHeight,bhh);  
	
	TCHAR BMPFileName[1024];  
	int widthStep = (((iWidth * 24) + 31) & (~31)) / 8 ; //ÿ��ʵ��ռ�õĴ�С��ÿ�ж�����䵽һ��4�ֽڱ߽磩  
	int DIBSize = widthStep * iHeight ;  //buffer�Ĵ�С ���ֽ�Ϊ��λ��  
		
    /*ͼ���ˣ�Ҫת����*/
	BYTE *tempData;
	BYTE *p_temp=NULL;
	BYTE *ptemp1=NULL;//ͼ������
	int Withbytes=(((iWidth * 24) + 31) & (~31)) / 8 ; //ÿ��ʵ��ռ�õĴ�С��ÿ�ж�����䵽һ��4�ֽڱ߽磩
	//Ϊͼ����������ռ�
	DWORD dataBytes = CDlgDemoDlg::bmpHeader.bfSize - CDlgDemoDlg::bmpHeader.bfOffBits;
	tempData = (BYTE*)new char[dataBytes];
	memcpy(tempData,pBuffer,dataBytes);
    /*��תͼ��*///p_temp1=pdata+j*sizeImageSave.cx; p_temp[i]
	for(int j=iHeight-1,k=0;j>=0;j--,k++)
	{
		p_temp=tempData+j*Withbytes;
		ptemp1=pBuffer+k*Withbytes;
		for(int i=0;i<Withbytes;i++)
		{
			ptemp1[i]=p_temp[i];
			
		}
			
	}
	delete [] tempData;

	
	strcpy(BMPFileName,fileName);  
	CFile file;  
	try  
	{  
		if(file.Open(BMPFileName,CFile::modeWrite | CFile::modeCreate))  
		{//д���ļ�  
			
			file.Write((LPSTR)&bhh,sizeof(BITMAPFILEHEADER));  
			file.Write((LPSTR)&bih,sizeof(BITMAPINFOHEADER));  
			file.Write(pBuffer,DIBSize);  
			file.Close();  
			return true;  
		}  
		
	}  
	catch (...)   
	{  
		AfxMessageBox("MyDC::SaveDIB2Bmp");  
	}  
	return false;  
}  



//����BMPλͼ�ļ�ͷ  
void DeviceControl::ContructBhh(int nWidth,int nHeight,BITMAPFILEHEADER& bhh) 
{  
	int widthStep = (((nWidth * 24) + 31) & (~31)) / 8 ; //ÿ��ʵ��ռ�õĴ�С��ÿ�ж�����䵽һ��4�ֽڱ߽磩  
	bhh.bfType = ((WORD) ('M' << 8) | 'B');  //'BM'  
	bhh.bfSize = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + widthStep * nHeight;  
	bhh.bfReserved1 = 0;  
	bhh.bfReserved2 = 0;  
	bhh.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);  
	
}  


//����BMP�ļ���Ϣͷ  
void DeviceControl::ConstructBih(int nWidth,int nHeight,BITMAPINFOHEADER& bih)   
{  
	int widthStep = (((nWidth * 24) + 31) & (~31)) / 8 ;   
	
	bih.biSize=40;       // header size  
	bih.biWidth=nWidth;  
	bih.biHeight=nHeight;  
	bih.biPlanes=1;  
	bih.biBitCount=24;     // RGB encoded, 24 bit  
	bih.biCompression=BI_RGB;   // no compression ��ѹ��  
	bih.biSizeImage=widthStep*nHeight*3;  
	bih.biXPelsPerMeter=0;  
	bih.biYPelsPerMeter=0;  
	bih.biClrUsed=0;  
	bih.biClrImportant=0;   
	
}  

BOOL DeviceControl:: StartRecord(HANDLE ChannelHandle, CString szFileName,CString CodecType, VidCodecX264Para H264CodecPara)
{
		unsigned CodecNum=100;
		CString VidCodec[100];
		int CurVidCodec=0;
		int ok=1;
		CString strVideo;
		DEVICE_TAG VideoCodec[100];
		DXEnumVideoCodecs(VideoCodec, CodecNum);
		
		//ָ��������Ϊxvid
		for (unsigned i=0; i< CodecNum;i++)
		{
			strVideo.Format (_T("%s"),VideoCodec[i].deviceName);
			VidCodec[i].Format (_T("%s"),VideoCodec[i].deviceName);
	
			if (strcmp(strVideo,CodecType)==0)
			{
				CurVidCodec=i;
			}

		}

		//���ñ�����
      
		ok=DXSetVideoCodec(ChannelHandle,&VideoCodec[CurVidCodec]);

		//����264����������

		if (strcmp(X264CODEC_FILTER,CodecType)==0)
		{
			DXSetVideoCodecPara(ChannelHandle, codec_x264, &H264CodecPara);	
		}
		 


		ok=DXStartCapture(ChannelHandle, TEXT(szFileName.GetBuffer(szFileName.GetLength())), FALSE, NULL, NULL, NULL);

		
		if (ok==0)
		{

		return true;
		}
		else

		{
			return false;
		
		}

}

BOOL DeviceControl::StopRecord(HANDLE ChannelHandle)
{
		int ok=1;
		ok=DXStopCapture(ChannelHandle);
		if (ok==0)
		{

			return true;
		}
		else

		{
			return false;
		
		}
	
	
}
BOOL DeviceControl::FreezeRecord(HANDLE ChannelHandle,BOOL Enable)
{
		int ok=1;
		ok=DXFreezeCaputre(ChannelHandle,Enable);
		if (ok==0)
		{

			return true;
		}
		else

		{
			return false;
		
		}
}
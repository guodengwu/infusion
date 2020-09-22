#include "misc.h"


void delay_ms(u16 ms)
{    
   u16 i=0;  
   while(ms--)
   {
      i=4500;  //�Լ�����
      while(i--) ;    
   }
}

s16 FUN_MIN16S(s16 x, s16 y)
{
	if(x > y)	{
		return y;
	}
		return x;
}
//�Լ�д��log����
float MYLOG(float a)
{
   int N = 10;//ȡ5+1�����
   int k,nk;
   float x,xx,y;
   x = (a-1)/(a+1);
   xx = x*x;
   nk = 2*N+1;
   y = 1.0/nk;
   for(k=N;k>0;k--)
   {
     nk = nk - 2;
     y = 1.0/nk+xx*y;
   }
	x *= (float)2.0;
   return (float)(x*y);
}

/*********************************************************************
 *  FUNCTION: FloatTo4uint8Format							          *
 *																	  *
 *  PARAMETERS:  							                          *
 *																	  *
 *  DESCRIPTION: ?Float?????char??              			  *
 *																 	  *
 *  RETURNS: ?													   	  *
 *																	  *
 *********************************************************************/
u16 FloatTo4uint8Format(u8* Dest, const float Source)
{
    u16 Len,i;
    u32 temp = Source;
    Len = sizeof(float);
    //temp = *(u32*)&Source;

    for (i = 0; i < Len; i++)
    {
        *Dest++ = (u8)(temp >> (8*(Len-i-1)));
    }

    return Len;
}

s32 floatToInt(float f)
{
    s32 i = 0;
    if(f>0) //
      i = (s32)((f*10 + 5)/10);
    else if(f<0) //
      i = (s32)((f*10 - 5)/10);
    else i = 0;

    return i;
}
//ð������
u8 BubbleSort(u8 *pbuf,u32 size)
{
	u8 i,j,flag;
	u8 x,y;

	if(size==0)	{
			return 0;
	}
	i=0;
	/*---------------- ð������,��С�������� -----------------*/
	do{
		flag=0;
		for (j=0;j<size-i-1;j++)
		{
			if (pbuf[j] > pbuf[j+1])
			{
				x = pbuf[j];
				pbuf[j]   = pbuf[j+1];
				pbuf[j+1] = x;
				flag = 1;
			}
			if (pbuf[j] > pbuf[j+1])
			{
				y = pbuf[j];
				pbuf[j] = pbuf[j+1];
				pbuf[j+1] = y;
				flag = 1;
			}
		}
		i++;
	}while((i<size) && flag);
	//////////////////////////////////////////////////////
	return 1;
}

//BCD��תʮ���ƺ���������BCD������ʮ����
u8 BCD_Decimal(u8 bcd)
{
	u8 Decimal;

	Decimal=bcd>>4;
	return(Decimal=Decimal*10+(bcd&=0x0F));
}
//ʵ��split��ĳ���ַ��ָ�һ���ַ���
//		src Դ�ַ������׵�ַ(buf�ĵ�ַ) strtok�������ƻ�Դ�ַ�������
//		separator ָ���ķָ��ַ�
//		dest �������ַ���������
//		num �ָ�����ַ����ĸ���
void split(char *src,const char *separator,char **dest,u16 *num) 
{
	char *pNext;
	u16 count;

	count = 0;
	if (src == NULL || strlen(src) == 0) //�������ĵ�ַΪ�ջ򳤶�Ϊ0��ֱ����ֹ 
		return;
	if (separator == NULL || strlen(separator) == 0) //��δָ���ָ���ַ�����ֱ����ֹ 
		return;
	pNext = (char *)strtok(src,separator); //����ʹ��(char *)����ǿ������ת��(��Ȼ��д�еı������в������ָ�����)
	while(pNext != NULL) {
		*dest++ = pNext;
		++count;
		pNext = (char *)strtok(NULL,separator);  //����ʹ��(char *)����ǿ������ת��
	}
	*num = count;
}

void findbuff_max(s32 *pbuf, u8 size, u32 *max, u8 *idx)
{	
	u8 i,maxidx;
	u32 maxdata;
	
	maxdata = pbuf[0];
	maxidx = 0;
	for(i=0;i<size;i++)//���ҵ����ֵ �ٽ����ֵǰ5��+��5��ȥƽ�� �õ�PD��ֵ
    {
        if(pbuf[i] > maxdata)
        {
            maxdata = pbuf[i];
            maxidx = i;
        }
	}
	*idx = maxidx;
	*max = maxdata;
}

void findbuff_min(s32 *pbuf, u8 size, u32 *max, u8 *idx)
{	
	u8 i,maxidx;
	u32 maxdata;
	
	maxdata = pbuf[0];
	maxidx = 0;
	for(i=0;i<size;i++)//���ҵ����ֵ �ٽ����ֵǰ5��+��5��ȥƽ�� �õ�PD��ֵ
    {
        if(pbuf[i] < maxdata)
        {
            maxdata = pbuf[i];
            maxidx = i;
        }
	}
	*idx = maxidx;
	*max = maxdata;
}

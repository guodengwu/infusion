#include "misc.h"


void delay_ms(u16 ms)
{    
   u16 i=0;  
   while(ms--)
   {
      i=4500;  //自己定义
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
//自己写的log函数
float MYLOG(float a)
{
   int N = 10;//取5+1项计算
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
//冒泡排序
u8 BubbleSort(u8 *pbuf,u32 size)
{
	u8 i,j,flag;
	u8 x,y;

	if(size==0)	{
			return 0;
	}
	i=0;
	/*---------------- 冒泡排序,由小到大排序 -----------------*/
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

//BCD码转十进制函数，输入BCD，返回十进制
u8 BCD_Decimal(u8 bcd)
{
	u8 Decimal;

	Decimal=bcd>>4;
	return(Decimal=Decimal*10+(bcd&=0x0F));
}
//实现split以某个字符分割一个字符串
//		src 源字符串的首地址(buf的地址) strtok函数会破坏源字符串完整
//		separator 指定的分割字符
//		dest 接收子字符串的数组
//		num 分割后子字符串的个数
void split(char *src,const char *separator,char **dest,u16 *num) 
{
	char *pNext;
	u16 count;

	count = 0;
	if (src == NULL || strlen(src) == 0) //如果传入的地址为空或长度为0，直接终止 
		return;
	if (separator == NULL || strlen(separator) == 0) //如未指定分割的字符串，直接终止 
		return;
	pNext = (char *)strtok(src,separator); //必须使用(char *)进行强制类型转换(虽然不写有的编译器中不会出现指针错误)
	while(pNext != NULL) {
		*dest++ = pNext;
		++count;
		pNext = (char *)strtok(NULL,separator);  //必须使用(char *)进行强制类型转换
	}
	*num = count;
}

void findbuff_max(s32 *pbuf, u8 size, u32 *max, u8 *idx)
{	
	u8 i,maxidx;
	u32 maxdata;
	
	maxdata = pbuf[0];
	maxidx = 0;
	for(i=0;i<size;i++)//先找到最大值 再将最大值前5个+后5个去平均 得到PD均值
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
	for(i=0;i<size;i++)//先找到最大值 再将最大值前5个+后5个去平均 得到PD均值
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

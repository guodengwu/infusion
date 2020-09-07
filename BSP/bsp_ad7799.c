/*
********************************************************************************
* bsp_ad7799.c
*
*   Copyright (C) 2010-2016 ACEA Biosciences, Inc. All rights reserved.
*   Author: AlexShi <shiweining123@163.com>
*
********************************************************************************
*/

/*
********************************************************************************
* Included Files
********************************************************************************
*/

#include "bsp_ad7799.h"

/*
********************************************************************************
* Pre-processor Definitions
********************************************************************************
*/

#define AD7799_CS_LOW()          	 HAL_GPIO_WritePin(AD7799_CS_GPIO_Port, AD7799_CS_Pin, GPIO_PIN_RESET)//AD7799_SCLK_GPIO_Port
#define AD7799_CS_HIGH()            HAL_GPIO_WritePin(AD7799_CS_GPIO_Port, AD7799_CS_Pin, GPIO_PIN_SET)
#define	AD7799_SPI		hspi3
#define	AD7799_TIMEOUT_VALUE	3
/*
********************************************************************************
* Shared Types
********************************************************************************
*/



/*
********************************************************************************
* Private Types
********************************************************************************
*/



/*
********************************************************************************
* Private Function Prototypes
********************************************************************************
*/

static void ad7799_write(ad7799_dev_t *pdev, CPU_INT08U len, CPU_INT32U data);
static CPU_INT32U ad7799_read(ad7799_dev_t *pdev, CPU_INT08U len);
static void ad7799_reg_write(ad7799_dev_t *pdev, CPU_INT08U reg, CPU_INT08U len, CPU_INT32U data);
static CPU_INT32U ad7799_reg_read(ad7799_dev_t *pdev, CPU_INT08U reg, CPU_INT08U len);

/*
********************************************************************************
* Shared Data
********************************************************************************
*/



/*
********************************************************************************
* Private Data
********************************************************************************
*/

static ad7799_dev_t g_ad7799_dev[AD7799_ID_NUMS] = {
    [AD7799_ID1] = {
        .id     = AD7799_ID1,
        //.spix   = CONFIG_AD7799_ID1_SPI,
        .clksrc = AD7799_CLKSRC_ExtClock,
        .vref   = 3.065f,
       // .cs_mask= AD7799_ID1_CS
    }
};

/*
********************************************************************************
* Private Functions
********************************************************************************
*/

/*
 * @brief
 *
 * @param
 *
 * @return
 *
 * @notes
 */
#if CONFIG_AD7799_LOCK_EN
static void __unused bsp_ad7799_lock(ad7799_dev_t *pdev)
{
    CPU_INT08U os_err;

    OSSemPend(pdev->lock, 0, &os_err);
    OSErrorCheck(os_err);
}

static void __unused bsp_ad7799_unlock(ad7799_dev_t *pdev)
{
    CPU_INT08U os_err;

    os_err = OSSemPost(pdev->lock);
    OSErrorCheck(os_err);
}
#endif

void ad7799_cs_low()
{
	AD7799_CS_LOW();
}

void ad7799_cs_high()
{
	AD7799_CS_HIGH();
}
u8 ad7799_txbuf[5], ad7799_rxbuf[5];
static void ad7799_write(ad7799_dev_t *pdev, CPU_INT08U len, CPU_INT32U data)
{
	u32 temp;
	
	temp = data;
	if(len==1)	ad7799_txbuf[0] = temp;
	else if(len==2)	{ad7799_txbuf[0] = temp>>8;ad7799_txbuf[1] = temp&0xff;}
	else if(len==3)	{ad7799_txbuf[0] = temp>>16;ad7799_txbuf[1] = temp>>8;ad7799_txbuf[2] = temp&0xff;}
	else if(len==4)	{ad7799_txbuf[0] = temp>>24;ad7799_txbuf[1] = temp>>16;ad7799_txbuf[2] = temp>>8;ad7799_txbuf[3] = temp&0xff;}
	else 
		return ;
	HAL_SPI_Transmit(pdev->p_spi, ad7799_txbuf, len, AD7799_TIMEOUT_VALUE);
}

static CPU_INT32U ad7799_read(ad7799_dev_t *pdev, CPU_INT08U len)
{
    u32 temp=0;
	
	if(len>4)
		return 0;
	memset(ad7799_rxbuf, 0 ,5);
	HAL_SPI_Receive(pdev->p_spi, ad7799_rxbuf, len, AD7799_TIMEOUT_VALUE);
	if(len==1)	temp = ad7799_rxbuf[0];
	else if(len==2)	{temp = ad7799_rxbuf[0]<<8|ad7799_rxbuf[1];}
	else if(len==3)	{temp = ad7799_rxbuf[0]<<16|ad7799_rxbuf[1]<<8|ad7799_rxbuf[2];}
	else if(len==4)	{temp = ad7799_rxbuf[0]<<24|ad7799_rxbuf[1]<<16|ad7799_rxbuf[2]<<8|ad7799_rxbuf[3];}
    return temp;
}

static void ad7799_reg_write(ad7799_dev_t *pdev, CPU_INT08U reg, CPU_INT08U len, CPU_INT32U data)
{
    ad7799_reg_comm_t r;

    r.ubyte = 0;
    r.bits.RW = AD7799_W;
    r.bits.RS = reg;
	
	ad7799_cs_low();
    ad7799_write(pdev, 1, r.ubyte);
    ad7799_write(pdev, len, data);
	ad7799_cs_high();
}

static CPU_INT32U ad7799_reg_read(ad7799_dev_t *pdev, CPU_INT08U reg, CPU_INT08U len)
{
    ad7799_reg_comm_t r;
	CPU_INT32U ret;

    r.ubyte = 0;
    r.bits.RW = AD7799_R;
    r.bits.RS = reg;
	
	ad7799_cs_low();
    ad7799_write(pdev, 1, r.ubyte);
    ret = ad7799_read(pdev, len);
	ad7799_cs_high();
	return ret;
}

/*
********************************************************************************
* Public Functions
********************************************************************************
*/

/*
 * @brief
 *
 * @param
 *
 * @return
 *
 * @notes
 */
void bsp_ad7799_reset(ad7799_dev_t *pdev)
{
	ad7799_cs_low();
    ad7799_write(pdev, 4, 0xFFFFFFFF);
    ad7799_write(pdev, 4, 0xFFFFFFFF);
	ad7799_cs_high();
	HAL_Delay(1);
}

CPU_INT08U bsp_ad7799_status_get(ad7799_dev_t *pdev)
{
    CPU_INT08U ret;

    ret = (CPU_INT08U)ad7799_reg_read(pdev, AD7799_REG_STATUS, 1);
    return ret;
}

CPU_INT08U bsp_ad7799_id_get(ad7799_dev_t *pdev)
{
    CPU_INT08U ret;

    ret = (CPU_INT08U)ad7799_reg_read(pdev, AD7799_REG_ID, 1);
    return ret;
}
//#if 0
//CPU_INT32U bsp_ad7799_mode_get(ad7799_dev_t *pdev)
//{
//    CPU_INT32U ret;

//    ret = (CPU_INT32U)ad7799_reg_read(pdev, AD7799_REG_MODE, 3);
//    return ret;
//}

//CPU_INT32U bsp_ad7799_cfg_get(ad7799_dev_t *pdev)
//{
//    CPU_INT32U ret;

//    ret = (CPU_INT32U)ad7799_reg_read(pdev, AD7799_REG_CONFIGURATION, 3);
//    return ret;
//}

//CPU_INT08U bsp_ad7799_gpocon_get(ad7799_dev_t *pdev)
//{
//    CPU_INT08U ret;

//    ret = (CPU_INT08U)ad7799_reg_read(pdev, AD7799_REG_GPOCON, 1);
//    return ret;
//}

//CPU_INT32U bsp_ad7799_offset_get(ad7799_dev_t *pdev)
//{
//    CPU_INT32U ret;

//    ret = (CPU_INT32U)ad7799_reg_read(pdev, AD7799_REG_OFFSET, 3);
//    return ret;
//}

//CPU_INT32U bsp_ad7799_fullscale_get(ad7799_dev_t *pdev)
//{
//    CPU_INT32U ret;

//    ret = (CPU_INT32U)ad7799_reg_read(pdev, AD7799_REG_FULL_SCALE, 3);
//    return ret;
//}
//#endif
CPU_INT32U bsp_ad7799_mode_get(ad7799_dev_t *pdev)
{
	CPU_INT32U ret;

    ret = (CPU_INT32U)ad7799_reg_read(pdev, AD7799_REG_MODE, 2);
    return ret;
}

CPU_INT32U bsp_ad7799_cfg_get(ad7799_dev_t *pdev)
{
    CPU_INT32U ret;

    ret = (CPU_INT32U)ad7799_reg_read(pdev, AD7799_REG_CONFIG, 2);
    return ret;
}

void bsp_ad7799_mode_set(ad7799_dev_t *pdev)
{
    ad7799_reg_mode_t r;

    r.uword = 0;
	r.bits.FS = 1;
	r.bits.PSW = 0;
	r.bits.MD = AD7799_MODE_SINGLE_CNV;//单次触发模式
    ad7799_reg_write(pdev, AD7799_REG_MODE, 2, r.uword);
}

void bsp_ad7799_cfg_set(ad7799_dev_t *pdev, const ad7799_chcfg_t *pcfg)
{
    ad7799_reg_cfg_t r;

    r.uword = 0;	
	r.bits.BURNOUT = pcfg->burnout;
	r.bits.U_B    = pcfg->U_B;
	r.bits.GAIN   = pcfg->intgain;
	r.bits.REF_DET = 1;//参考电压检测使能
	r.bits.REFBUF    = 1;
	r.bits.CH = pcfg->channel;
    ad7799_reg_write(pdev, AD7799_REG_CONFIG, 2, r.uword);
}

ad7799_dev_t* bsp_ad7799_find(CPU_INT08U id)
{
    if (id < AD7799_ID_NUMS) {
        return &g_ad7799_dev[id];
    }

    return NULL;
}

CPU_INT08U bsp_ad7799_conv_ready(ad7799_dev_t *pdev, CPU_INT08U *perr)
{
//    CPU_INT32U ret = 0;
    CPU_INT08U status, errint;

    status = bsp_ad7799_status_get(pdev);
    if (status == 0xFF) {
        errint = AD7799_ERR_INACTIVE;
        goto _exit;
    }

    if (status & AD7799_STATUS_ERR) {
        if (status & AD7799_STATUS_NOREF) {
            errint = AD7799_ERR_NOREF;
        } else {
            errint = AD7799_ERR_ACTIVE;
        }
    } else if (!(status & AD7799_STATUS_RDY)) {
        errint = AD7799_ERR_NONE;			
    } else {
        errint = AD7799_ERR_BUSY;
    }

_exit:
    *perr = errint;
    return status&0x07;
}

CPU_INT32U bsp_ad7799_value_get(ad7799_dev_t *pdev)
{
	return ad7799_reg_read(pdev, AD7799_REG_DATA, 3);
}

ad7799_dev_t* bsp_ad7799_init(CPU_INT08U id)
{
    ad7799_dev_t *pdev = NULL;

    if (id < AD7799_ID_NUMS) {
        pdev = &g_ad7799_dev[id];
    } else return pdev;

    if (pdev->flags & DEF_FLAGS_AD7799_INIT) return pdev;

//    pdev->p_spi   = bsp_spi_get(SPI_ID1);
	pdev->p_spi = &hspi1;
    bsp_ad7799_reset(pdev);

    pdev->flags |= DEF_FLAGS_AD7799_INIT;
    return pdev;
}

/*
********************************************************************************
* No More!
********************************************************************************
*/

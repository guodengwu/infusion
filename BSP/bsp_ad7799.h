/*
********************************************************************************
* bsp_ad7799.h
*
*   Copyright (C) 2010-2016 ACEA Biosciences, Inc. All rights reserved.
*   Author: AlexShi <shiweining123@163.com>
*
********************************************************************************
*/

#ifndef BSP_AD7799_H
#define BSP_AD7799_H

/*
********************************************************************************
* Included Files
********************************************************************************
*/
#include "includes.h"
/*
********************************************************************************
* Pre-processor Definitions
********************************************************************************
*/

#define AD7799_R                                           DEF_High
#define AD7799_W                                            DEF_Low

#define DEF_INT_08_BITS                                          8u
#define DEF_INT_16_BITS                                         16u
#define DEF_INT_24_BITS                                         24u
#define DEF_INT_32_BITS                                         32u

#define AD7799_CLKSRC_ExtClock                                    1 // external clock
#define AD7799_CLKSRC_ExtCrystal                                  0 // external crystal
#define MODE_PSEUDO_DIFF_INPUT                                 TRUE
#define MODE_DIFF_INPUT                                       FALSE
#define DETECT_VOLTAGE                       MODE_PSEUDO_DIFF_INPUT
#define DETECT_CURRENT                              MODE_DIFF_INPUT

#define AD7799_PIN_RDY                               DEF_BIT02_MASK
#define AD7799_STATUS_RDY                            DEF_BIT07_MASK
#define AD7799_STATUS_ERR                            DEF_BIT06_MASK
#define AD7799_STATUS_NOREF                          DEF_BIT05_MASK
#define AD7799_STATUS_PARITY                         DEF_BIT04_MASK
#define AD7799_ERRCHK_None                     0
#define AD7799_ERRCHK_Warning                  1
#define AD7799_ERRCHK_Inactive                 2
#define AD7799_ERRCHK_Error                    3

#define DEF_CHANNEL(name)                   name, #name
#define	AD7799_ID		0X09

/*
********************************************************************************
* Shared Types
********************************************************************************
*/



/*
********************************************************************************
* Public Types
********************************************************************************
*/

enum _ad7799_id {
    AD7799_ID1 = 0
};
#define AD7799_ID_MIN     AD7799_ID1
#define AD7799_ID_MAX     AD7799_ID1
#define AD7799_ID_NUMS   (AD7799_ID_MAX-AD7799_ID_MIN+1)

#define MONITOR1_USE_AD7799     AD7799_ID1

enum _ad7799_channel {
    uCH_0    = 0x00,
    uCH_1    = 0x1,
    uCH_2    = 0x2,
//    uCH_3    = 0x3,
//    uCH_4    = 0x4,
//    uCH_5    = 0x5,
//    uCH_6    = 0x6,
//    uCH_7    = 0x7,
//    uCH_8    = 0x8,
//    uCH_9    = 0x9,
//    uCH_A    = 0xA,
//    uCH_B    = 0xB,
//    uCH_C    = 0xC,
//    uCH_D    = 0xD,
//    uCH_E    = 0xE,
//    uCH_F    = 0xF,
};

enum _ad7799_AIN {
    AIN0    = 0x00,
    AIN1    = 0x1,
    AIN2    = 0x2,
//    AIN3    = 0x3,
//    AIN4    = 0x4,
//    AIN5    = 0x5,
//    AIN6    = 0x6,
//    AIN7    = 0x7,
//		AIN_TEMP	= 0X10,//温度采集
//		AIN_AVSS	= 0X11,//AVss
//		AIN_AVREF	= 0X12,//内部基准电压
//		AIN_DGND	= 0X13,
//		AIN_AVDD_AVSS1	= 0X14,
//		AIN_AVDD_AVSS0	= 0X15,
};

//enum _ad7799_config_x {
//    CONFIG_0    = 0x00,
//    CONFIG_1    = 0x1,
//    CONFIG_2    = 0x2,
//    CONFIG_3    = 0x3,
//    CONFIG_4    = 0x4,
//    CONFIG_5    = 0x5,
//    CONFIG_6    = 0x6,
//    CONFIG_7    = 0x7,
//};

/*
enum _ad7799_channel {
    uCH_0    = 0x00,
    uCH_1    = 0x1,
    uCH_2    = 0x2,
    uCH_3    = 0x3,
    uCH_4    = 0x4,
    uCH_5    = 0x5,
    uCH_6    = 0x6,
    uCH_7    = 0x7,
    uCH_8    = 0x8,
    uCH_9    = 0x9,
    uCH_A    = 0xA,
    uCH_B    = 0xB,
    uCH_C    = 0xC,
    uCH_D    = 0xD,
    uCH_E    = 0xE,
    uCH_F    = 0xF,
};*/

enum _ad7799_err {
    AD7799_ERR_NONE     = 0,
    AD7799_ERR_BUSY     = 1,
    AD7799_ERR_ACTIVE   = 2,
    AD7799_ERR_NOREF    = 3,
    AD7799_ERR_INACTIVE = 4,
    AD7799_ERR_CHANNEL = 5
};

/* AD7799 Register List */
enum _ad7799_reg {
    AD7799_REG_COMMUNICATIONS               = 00,//COMM
    AD7799_REG_STATUS                       = 00,//STATUS
    AD7799_REG_MODE                         = 01,
    AD7799_REG_CONFIG                		= 02,
    AD7799_REG_DATA                         = 03,
    AD7799_REG_ID                           = 04,//ID
	AD7799_REG_IO                           = 05,//IO
    AD7799_REG_OFFSET                       = 06,
    AD7799_REG_FULL_SCALE                   = 07,
};

/* AD7799 Operating Modes Register */
enum _ad7799_mode {
    AD7799_MODE_CONTINUOUS_CNV              = 00,
    AD7799_MODE_SINGLE_CNV                  = 01,
    AD7799_MODE_IDLE                    = 02,
    AD7799_MODE_POWER_DOWN                  = 03,
    AD7799_MODE_INTERNAL_ZERO_SCALE         = 04,
    AD7799_MODE_INTERNAL_FULL_SCALE         = 05,
    AD7799_MODE_SYSTEM_ZERO_SCALE           = 06,
    AD7799_MODE_SYSTEM_FULL_SCALE           = 7
};

enum _ad7799_gain_key {
    AD7799_GAIN_1_MUL                       = 00,
    AD7799_GAIN_2_MUL                       = 01,
    AD7799_GAIN_4_MUL                      = 02,
    AD7799_GAIN_8_MUL                      = 03,
    AD7799_GAIN_16_MUL                      = 04,
	AD7799_GAIN_32_MUL                      = 05,
	AD7799_GAIN_64_MUL                      = 06,
    AD7799_GAIN_128_MUL                     = 07
};
/*#define AD7799_GAIN_KV(gain)    {AD7799_GAIN_##gain##_MUL, gain}

typedef struct _ad7799_gain {
    CPU_INT08U key;
    CPU_INT08U value;
} ad7799_gain_t;*/

typedef union _ad7799_reg_comm {
    struct {
        CPU_INT08U  RSVD   :2;          // Set to 0
        CPU_INT08U  CRED   :1;          // Continuous read of the data register
        CPU_INT08U  RS     :3;          // Register address bits
        CPU_INT08U  RW     :1;          // Read/Write operation select
        CPU_INT08U  WEN    :1;          // Write enable bit
    } bits;
    CPU_INT08U ubyte;
} ad7799_reg_comm_t;

typedef union _ad7799_reg_status {
    struct {
        CPU_INT08U  CHD    :3;          // Indicate which channel corresponds to the data register contents
        CPU_INT08U  PARITY :2;          // Parity check of the data register
        CPU_INT08U  NOREF  :1;          // No external reference bit
        CPU_INT08U  ERR    :1;          // ADC error bit
        CPU_INT08U  RDY    :1;          // Ready bit for the ADC
    } bits;
    CPU_INT08U ubyte;
} ad7799_reg_status_t;

typedef union _ad7799_reg_mode {
    struct {
        CPU_INT16U  FS     	:4;         // Filter output data rate select bits
		CPU_INT16U  RSVD  	:8;          // Set to 0
        CPU_INT16U  PSW 	:1;         // Enable the transmission of status register contents after ench data register read
        CPU_INT16U  MD      :3;         // Mode select bits
    } bits;
    CPU_INT16U  uword;
} ad7799_reg_mode_t;

typedef union _ad7799_reg_cfg {
    struct {
       
        CPU_INT32U  CH      :3;         // Channel select bits
        CPU_INT16U  RSVD2   :1;         // Set to 0
        CPU_INT16U  REFBUF  :1;         // Reference select bits
		CPU_INT16U  REF_DET    :1;         // 
		CPU_INT16U  RSVD1    :2;         // Unused
		CPU_INT16U  GAIN      :3;          // Gain select bits
		CPU_INT16U  RSVD    :1;         // Unused
        CPU_INT16U  U_B    :1;         // Polarity select bit(0-bipolar, 1-unipolar)
		CPU_INT16U  BURNOUT   :1;         // Set to 0
        CPU_INT16U  UNUSED    :2;         // Unused
    } bits;
    CPU_INT16U  uword;
} ad7799_reg_cfg_t;


#define UNIPOLAR    1u
#define BIPOLAR     0u

typedef struct _ad7124_chcfg {
    CPU_INT08U channel;         // Test Channel
   // const CPU_CHAR *chname;     // Channel name
    CPU_INT08U enable;       // idx
    CPU_INT08U U_B;             // Unipolar or Bipolar
    CPU_INT08U burnout;            // unit
//	CPU_INT08U AINP;
//	CPU_INT08U AINM;
    CPU_INT08S extgain;         // external gain
    //ad7124_gain_t intgain;      // AD internal gain
	CPU_INT08U intgain;	// AD internal gain
} ad7799_chcfg_t;

#define DEF_FLAGS_AD7799_INIT       DEF_BIT00_MASK
typedef struct _ad7799_dev {
    const CPU_INT08U id;
    //const CPU_INT08U p_spi;
    const CPU_INT08U clksrc;
    const CPU_FP32   vref;
    CPU_INT32U cs_mask;
    CPU_INT32U flags;
//    spi_t 				*p_spi;
	SPI_HandleTypeDef	*p_spi;
    void *priv;
} ad7799_dev_t;

/*
********************************************************************************
* Inline Functions
********************************************************************************
*/



/*
********************************************************************************
* Shared Data
********************************************************************************
*/



/*
********************************************************************************
* Public Data
********************************************************************************
*/



/*
********************************************************************************
* Public Function Prototypes
********************************************************************************
*/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C" {
#else
#define EXTERN extern
#endif

EXTERN void bsp_ad7799_reset(ad7799_dev_t *pdev);
EXTERN CPU_INT08U bsp_ad7799_status_get(ad7799_dev_t *pdev);
EXTERN CPU_INT08U bsp_ad7799_id_get(ad7799_dev_t *pdev);
EXTERN CPU_INT32U bsp_ad7799_mode_get(ad7799_dev_t *pdev);
EXTERN CPU_INT32U bsp_ad7799_cfg_get(ad7799_dev_t *pdev);
EXTERN CPU_INT08U bsp_ad7799_gpocon_get(ad7799_dev_t *pdev);
EXTERN CPU_INT32U bsp_ad7799_offset_get(ad7799_dev_t *pdev);
EXTERN CPU_INT32U bsp_ad7799_fullscale_get(ad7799_dev_t *pdev);
CPU_INT32U bsp_ad7799_errorreg_get(ad7799_dev_t *pdev);
EXTERN void bsp_ad7799_control_set(ad7799_dev_t *pdev);
EXTERN ad7799_dev_t* bsp_ad7799_find(CPU_INT08U id);
EXTERN CPU_INT32U bsp_ad7799_value_get(ad7799_dev_t *pdev);
EXTERN ad7799_dev_t* bsp_ad7799_init(CPU_INT08U id);
CPU_INT32U bsp_ad7799_control_get(ad7799_dev_t *pdev);

void bsp_ad7799_mode_set(ad7799_dev_t *pdev);
void bsp_ad7799_cfg_set(ad7799_dev_t *pdev, const ad7799_chcfg_t *pcfg);
void bsp_ad7799_errorreg_set(ad7799_dev_t *pdev, u8 flag);
CPU_INT08U bsp_ad7799_conv_ready(ad7799_dev_t *pdev, CPU_INT08U *perr);
void ad7799_cs_low(void);
void ad7799_cs_high(void);
void bsp_ad7799_value_get_dma(ad7799_dev_t *pdev);
void bsp_ad7799_status_get_dma(ad7799_dev_t *pdev);
#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif      /* __BSP_AD7799_H */

/*
********************************************************************************
* No More!
********************************************************************************
*/

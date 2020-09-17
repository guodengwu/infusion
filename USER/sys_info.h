#ifndef __SYS_INFO_H__
#define __SYS_INFO_H__

#include "includes.h"

#define SYSINFO_SIZE          20
#define SYS_FW_TYPE           "Debug"
/*
********************************************************************************
* Pre-processor Definitions
********************************************************************************
*/
#define CONFIG_SYSINFO_Name                            "Weigh"
#define CONFIG_SYSINFO_Type                            "xxxxxx"
#define CONFIG_SYSINFO_SN                              "2001000001"
//#define CONFIG_SYSINFO_BoardSN                  		"********"
#define CONFIG_SYSINFO_HW_Version   				   	"V0.1"
#define CONFIG_SYSINFO_BOARD_Version                  	"V0.1"
#define CONFIG_SYSINFO_FW_Version   				   	"V0.0.1"
#define CONFIG_SYSINFO_BuildDate                      	__DATE__
#define CONFIG_SYSINFO_BuildTime                     	__TIME__
#define CONFIG_SYSINFO_Manufacturer                    "xxxxx, Inc."

typedef struct _ident_infor {
    char    type[SYSINFO_SIZE];
    char    product_sn[SYSINFO_SIZE];
    char    pcbver[SYSINFO_SIZE];
    char    pcbaver[SYSINFO_SIZE];
    char    board_sn[SYSINFO_SIZE];
	//u16 	crc;
} ident_infor_t;

typedef struct _sys_infor {
    char        *pname;
    char        *pfwver;
	char 		*pfwtype;
    char        *pbuilddate;
    char        *pbuildtime;
	char 		*pmanufacturer;
    ident_infor_t *pident;
} sys_infor_t;

extern const sys_infor_t g_sys_infor;
#endif


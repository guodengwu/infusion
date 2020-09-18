#include "sys_info.h"


////////////////////��Щ��Ϣ�ǿ��޸ĵ�/////////////////////
ident_infor_t g_ident_infor = {//�����汾��Ϣ
    .type           = CONFIG_SYSINFO_Type,//Ĭ�ϲ�Ʒ�ͺ�
    .product_sn     = CONFIG_SYSINFO_SN,//Ĭ�ϲ�Ʒ���к�
    .pcbver			= CONFIG_SYSINFO_HW_Version,//Ĭ��PCBA��
    .pcbaver		= CONFIG_SYSINFO_BOARD_Version,//Ĭ��PCB��
//    .board_sn    	= CONFIG_SYSINFO_BoardSN//Ĭ�ϰ����к�
};

////////////////////////////////////////////////////////
const sys_infor_t g_sys_infor = {
    .pname          = CONFIG_SYSINFO_Name,
    .pfwver         = CONFIG_SYSINFO_FW_Version,
	.pfwtype		= SYS_FW_TYPE,
    .pbuilddate     = CONFIG_SYSINFO_BuildDate,
    .pbuildtime     = CONFIG_SYSINFO_BuildTime,
    .pmanufacturer  = CONFIG_SYSINFO_Manufacturer,
    .pident         = &g_ident_infor,
};

void show_sys_info(void)
{
    sys_infor_t const *pinfo = &g_sys_infor;
    ident_infor_t *pident = pinfo->pident;

    SYS_PRINTF("Producte name:        \t\t%s",    pinfo->pname);
    SYS_PRINTF("Producte type:        \t\t%s",    pident->type);
    SYS_PRINTF("Producte SN:          \t\t%u",    pident->product_sn.uword);
    SYS_PRINTF("Board SN:        \t\t%s",  pident->board_sn);
    SYS_PRINTF("Firmware Type:      \t\t%s",    pinfo->pfwtype);
    SYS_PRINTF("Firmware Version:   \t\t%s",    pinfo->pfwver);
    SYS_PRINTF("Hardware Version:   \t\t%s",    pident->pcbver);
    SYS_PRINTF("Board Version:      \t\t%s",    pident->pcbaver);
    SYS_PRINTF("Firmware Build Date:\t\t%s",    pinfo->pbuilddate);
    SYS_PRINTF("Firmware Build Time:\t\t%s",    pinfo->pbuildtime);
    SYS_PRINTF("Manufacturer:       \t\t%s",    pinfo->pmanufacturer);
}


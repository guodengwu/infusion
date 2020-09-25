#include "protocol.h"
#include "UartTask.h"


uint8_t  UsartRxGetINT8U (uint8_t *buf,uint32_t *idx)
{
    return (buf[(*idx)++]);
}

uint16_t  UsartRxGetINT16U (uint8_t *buf,uint32_t *idx)
{
    uint16_t  lowbyte;
    uint16_t  highbyte;

    highbyte  = UsartRxGetINT8U(buf,idx);
    lowbyte = UsartRxGetINT8U(buf,idx);
    return ((highbyte << 8) | lowbyte);
}

uint32_t  UsartRxGetINT32U (uint8_t *buf,uint32_t *idx)
{
    uint32_t  highword;
    uint32_t  lowword;

    highword = UsartRxGetINT16U(buf,idx);
    lowword = UsartRxGetINT16U(buf,idx);
    return ((highword << 16) | lowword);
}

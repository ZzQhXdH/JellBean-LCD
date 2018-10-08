#include "DEXFile.h"
#include <stdarg.h>

const char __HEX_LIST[] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'A', 'B',
    'C', 'D', 'E', 'F',
};

static uint32_t xStrValueOf(char *target, uint32_t value)
{
    uint32_t length = 1;
    uint32_t tmp = value;

    while ((tmp /= 10) != 0)
    {
        length ++;
    }

    for (uint32_t i = 0; i < length; i ++)
    {
        target[length - i - 1] = '0' + (value % 10);
        value /= 10;
    }
    return length;
}

static uint32_t xStrHexOf(char *target, uint32_t value)
{
    uint32_t length = 1;
    uint32_t tmp = value;

    while ((tmp >>= 4) != 0)
    {
        length ++;
    }

    for (uint32_t i = 0; i < length; i ++)
    {
        target[length - i - 1] = __HEX_LIST[ value & 0x0F ];
        value >>= 4;
    }

    return length;
}

static uint32_t xStrCopy(char *target, const char *source)
{
    char c;
    uint32_t length = 0;
    while ((c = *source) != '\0')
    {
        *target = c;
        target ++;
        source ++;
        length ++;
    }
    return length;
}

static void calc_crc(uint32_t *pCrc, uint8_t uData)
{
    int32_t iBit;

    for (iBit = 0; iBit < 8; iBit ++, uData >>= 1)
    {
        if ((uData ^ *pCrc) & 0x01)
        {
            *pCrc >>= 1;
            *pCrc ^= 0xA001;
        }
        else
        {
            *pCrc >>= 1;
        }
    }
}

static uint32_t getCrc(uint8_t *bytes, uint32_t length)
{
    uint32_t crc = 0x00;
    for (uint32_t i = 0; i < length; i ++)
    {
        calc_crc(&crc, bytes[i]);
    }
    return crc ;
}

DEXFile::DEXFile(void)
{
}

const char *DEXFile::build(void)
{
    uint32_t crc = getCrc(mRawBytes + nStartIndex, nIndex - nStartIndex);
    formatWrite("G85", "x", crc);
    formatWrite("ST", "ds", nMessageCount + 1, "0001");
    formatWrite("DXE", "ss", "1", "1");
    mRawBytes[nIndex] = '\0';
    return (const char *) mRawBytes;
}

DEXFile &DEXFile::setBuffer(void *pBuffer)
{
    mRawBytes = (uint8_t *) pBuffer;
    nIndex = 0;
    formatWrite("DXS", "ssss", "HOH1234567", "VA", "V0/6", "1");
    nStartIndex = nIndex;
    formatWrite("ST", "ss", "001", "0001");
    formatWrite("ID1", "s0000s", "MCU1234567", "12345");
    nMessageCount = 1;
    return *this;
}

DEXFile &DEXFile::appendProductMessage(const char *productId, uint32_t price, bool isPrease)
{
    uint32_t status = (isPrease ? 0 : 1);
    formatWrite("PA1", "sd0000d00", productId, price, status);
    return *this;
}

DEXFile &DEXFile::appendEventMessage(const char *id, uint32_t count, bool isActive)
{
    formatWrite("EA2", "sd00d0", id, count, (uint32_t) isActive);
    return *this;
}

void DEXFile::formatWrite(const char *header, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    char c;
    uint32_t ret = xStrCopy((char *)mRawBytes + nIndex, header);
    nIndex += ret;

    while ((c = *format) != '\0')
    {
        mRawBytes[nIndex ++] = '*';

        switch (c)
        {
            case 'd':
                ret = xStrValueOf((char *) mRawBytes + nIndex, va_arg(ap, uint32_t));
                nIndex += ret;
                break;

            case 'x':
                ret =  xStrHexOf((char *) mRawBytes + nIndex, va_arg(ap, uint32_t));
                nIndex += ret;
                break;

            case 's':
                ret = xStrCopy((char *) mRawBytes + nIndex, va_arg(ap, const char *));
                nIndex += ret;
                break;
        }

        format ++;
    }
    mRawBytes[nIndex ++] = '\r';
    mRawBytes[nIndex ++] = '\n';
    nMessageCount ++;
}





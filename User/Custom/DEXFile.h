#ifndef     __DEX_FILE_H
#define     __DEX_FILE_H

#include <stdint.h>

#define SOH 	0x01
#define STX 	0x02
#define ETX 	0x03
#define EOT 	0x04
#define ENQ 	0x05
#define LF  	0x0A
#define CR  	0x0D
#define DLE 	0x10
#define NAK 	0x15
#define SYN 	0x16
#define ETB 	0x17


class DEXFile
{
    public:

        static DEXFile& instance(void)
        {
            static DEXFile file;
            return file;
        }

        DEXFile &setBuffer(void *pBuffer);

        const char *build(void);
		
        DEXFile &appendProductMessage(const char *productId, uint32_t price, bool isPrease); // PA1产品信息

        DEXFile &appendEventMessage(const char *id, uint32_t count, bool isActive); // EA2状态信息

    private:
        uint8_t *mRawBytes;
        uint32_t nIndex;
        uint32_t nStartIndex;
        uint32_t nMessageCount;

    private:
        DEXFile(void);

        void formatWrite(const char *header, const char *format, ...);
};

#endif

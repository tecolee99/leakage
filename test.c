#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SYS_NOT_SUPPORT 0xff
#define SYS_FAILED 0xfe
#define SYS_NOERROR 0
#define SYS_NO_FUNCTCION 1
#define WiFiIfaceName "wlan0"

static int s_WIFI_IsConnect()
{
    return 1;
}

static signed long s_PercentToDbm(unsigned char Percent)
{
    return 100;
}

int test(signed long* piRssiValue) {
    if(piRssiValue == NULL) return SYS_FAILED;
    if (!s_WIFI_IsConnect()) return SYS_NO_FUNCTCION;

    if (1) {
        FILE* fp;
        char WifiRxFile[60], *pResultBuf, *ptempBuf1, *ptempBuf2;
        unsigned short int ResultBuffLen = 200;
        unsigned char Percent;

        pResultBuf = malloc(ResultBuffLen * sizeof(unsigned char));
        sprintf(WifiRxFile, "/proc/net/bbb/%s/rx_signal", WiFiIfaceName);

        if ((fp = fopen(WifiRxFile, "r")) == NULL) {
            printf("%s not found!\n", WiFiIfaceName);
            return SYS_FAILED;
        }

        ResultBuffLen = fread(pResultBuf, sizeof(unsigned char), ResultBuffLen, fp);
        if (0 == fclose(fp)) {
            printf("%s\n", pResultBuf);

            if ((ptempBuf1 = strstr(pResultBuf, "KKKKKK =")) == 0) {
                printf("Can't find KKKKKK!\n");
                return SYS_FAILED;
            }
            Percent = (signed long)strtol(ptempBuf1 + strlen("KKKKKK ="), NULL, 10);
            piRssiValue[0] = s_PercentToDbm(Percent);

            if ((ptempBuf1 = strstr(pResultBuf, "KKKK_A =")) == 0) {
                printf("Can't find KKKK_A!\n");
                return SYS_FAILED;
            }
            Percent = (signed long)strtol(ptempBuf1 + strlen("KKKK_A ="), &ptempBuf2, 10);
            piRssiValue[1] = s_PercentToDbm(Percent);
            if ((ptempBuf1 = strstr(ptempBuf2, "KKKK_B =")) == 0) {
                printf("Can't find KKKK_B!\n");
                return SYS_FAILED;
            }
            Percent = (signed long)strtol(ptempBuf1 + strlen("KKKK_B ="), NULL, 10);
            piRssiValue[2] = s_PercentToDbm(Percent);
            return SYS_NOERROR;
        }
        return SYS_FAILED;
    } else {
        return SYS_NOT_SUPPORT;
    }
}

int main(int argc, char *argv[])
{
	signed long dbm = 0;
	test(&dbm);
}

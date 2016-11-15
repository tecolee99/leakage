#define SYS_NOT_SUPPORT 0xff
#define SYS_FAILED 0xfe
#define SYS_NOERROR 0
#define SYS_NO_FUNCTCION 1

int test(signed long* piRssiValue) {
    if(piRssiValue == NULL) return SYS_FAILED;
    if (!APP_WIFI_IsConnect()) return SYS_NO_FUNCTCION;

    if (1) {
        FILE* fp;
        char WifiRxFile[60], *pResultBuf, *ptempBuf1, *ptempBuf2;
        unsigned short int ResultBuffLen = 200;
        unsigned char Percent;

        pResultBuf = malloc(ResultBuffLen * sizeof(trid_char));
        sprintf(WifiRxFile, "/proc/net/bbb/%s/rx_signal", WiFiIfaceName);

        if ((fp = fopen(WifiRxFile, "r")) == NULL) {
            printf("%s not found!\n", WiFiIfaceName);
            return SYS_FAILED;
        }

        ResultBuffLen = fread(pResultBuf, sizeof(trid_uint8), ResultBuffLen, fp);
        if (0 == fclose(fp)) {
            printf("%s\n", pResultBuf);

            if ((ptempBuf1 = strstr(pResultBuf, "KKKKKK =")) == 0) {
                printf("Can't find KKKKKK!\n");
                return SYS_FAILED;
            }
            Percent = (trid_sint32)strtol(ptempBuf1 + strlen("KKKKKK ="), NULL, 10);
            piRssiValue[0] = s_PercentToDbm(Percent);

            if ((ptempBuf1 = strstr(pResultBuf, "KKKK_A =")) == 0) {
                printf("Can't find KKKK_A!\n");
                return SYS_FAILED;
            }
            Percent = (trid_sint32)strtol(ptempBuf1 + strlen("KKKK_A ="), &ptempBuf2, 10);
            piRssiValue[1] = s_PercentToDbm(Percent);
            if ((ptempBuf1 = strstr(ptempBuf2, "KKKK_B =")) == 0) {
                printf("Can't find KKKK_B!\n");
                return SYS_FAILED;
            }
            Percent = (trid_sint32)strtol(ptempBuf1 + strlen("KKKK_B ="), NULL, 10);
            piRssiValue[2] = s_PercentToDbm(Percent);
            return SYS_NOERROR;
        }
        return SYS_FAILED;
    } else {
        return SYS_NOT_SUPPORT;
    }
}
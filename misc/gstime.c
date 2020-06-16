#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

#define LOCAL_TIME_CORRECTION_HOUR 8
#define LOCAL_TIME_CORRECTION (LOCAL_TIME_CORRECTION_HOUR*3600) //本地时间时区偏移







struct tm *  LocalTime(uint32_t dwTimeStamp, struct tm * ptm) {
    time_t tTm = dwTimeStamp;
    tTm += LOCAL_TIME_CORRECTION;
    if (ptm) {
        return gmtime_r(&tTm, ptm);
    }
    else {
        static struct tm s_tm_tmp;
        return gmtime_r(&tTm, &s_tm_tmp);
    }
}
const   char *  Format(uint32_t dwTime, const char * pszFmt) {
    static char szFormatBuffer[32];
    strftime(szFormatBuffer, sizeof(szFormatBuffer), pszFmt,
                    LocalTime(dwTime, NULL));
    return szFormatBuffer;
}


int main() {

    printf("1592278765 :  %s\n", Format(1592278765, "%Y-%m-%d %H:%M:%S"));
    printf("1592280546 :  %s\n", Format(1592280546, "%Y-%m-%d %H:%M:%S"));

    return 0;
}

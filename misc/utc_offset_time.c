#include <sys/time.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdio.h>


extern int daylight;
extern long timezone;

inline int get_local_daylight() {
    tzset();
    return daylight;
}

inline int get_local_utc_offset() {
    tzset();
    return -timezone;
}


static int s_iSetUTCOffset = 8 * 3600;
#define SECONDS_ADAY 86400

int GetNatureAbsDayIdx(time_t tTime) {
    time_t tTimeLocal = tTime + s_iSetUTCOffset;
    int iTimeDays = tTimeLocal / SECONDS_ADAY;
    return iTimeDays;
}


time_t ToNatureTodayClockTime(time_t tTime ){

    int iAbsDay = GetNatureAbsDayIdx(tTime);
    return iAbsDay*SECONDS_ADAY - s_iSetUTCOffset ;
}

int main() {
  
     
    printf("local offset :%d \n", get_local_utc_offset());    
    

    uint32_t timenow = time(0);
    printf("Nature Day Start Time:%zu \n", ToNatureTodayClockTime(timenow));    
    
    
    return 0;
}

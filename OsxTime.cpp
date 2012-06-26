#include "DateTime.hpp"
#include <stdint.h>
#include <sys/time.h>
//#include <ctime>
//#include <mach/mach.h>
#include <mach/mach_time.h>

void Sleep(TimeSpan inTimeSpan)
{
    usleep(inTimeSpan.Microseconds());
}

const DateTime GetNativeTime()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    int64_t microseconds = tv.tv_sec * 1000000;
    microseconds += tv.tv_usec;
    
    DateTime epoch;
    epoch.Set(1970, 1, 1);
    
    return epoch + TimeSpan::FromMicroseconds(microseconds);
}

static uint64_t start = 0;
static mach_timebase_info_data_t timeBaseInfo;

void ResetTimer()
{
    mach_timebase_info(&timeBaseInfo);
    start = mach_absolute_time();
}

const TimeSpan ReadTimer()
{
    uint64_t end = mach_absolute_time();
    uint64_t elapsed = end - start;
    uint64_t nanoseconds = elapsed * timeBaseInfo.numer / timeBaseInfo.denom;
    return TimeSpan::FromNanoseconds(nanoseconds);
}
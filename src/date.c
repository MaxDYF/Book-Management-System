#include "date.h"
#include <stdio.h>
#include <stdlib.h>
uint32_t nowTime;
#define MAX_CHAR_BUFFER 100
void timeInit()
{
    // Get the current time as time_t
    time_t rawtime;
    time(&rawtime);

    // Use localtime to convert to local time (POSIX version)
    struct tm *timeinfo = localtime(&rawtime);
    // For Windows, you would use localtime_s as follows:
    // struct tm timeinfo;
    // localtime_s(&timeinfo, &rawtime);
    Date nt;
    // Assign the date components to the Date structure
    nt.year = timeinfo->tm_year + 1900; // tm_year is years since 1900
    nt.month = timeinfo->tm_mon + 1;    // tm_mon is months since January (0-11)
    nt.day = timeinfo->tm_mday;         // tm_mday is day of the month (1-31)
    nowTime = getTimefromDate(nt);
}
Date getDatefromTime(uint32_t time)
{
    Date date;
    date.year = 1970;
    date.month = 1;
    date.day = 1;
#define isLeapYear(date) ((date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0))
    while (time > 365 + (int)isLeapYear(date))
    {
        time -= 365 + (int)isLeapYear(date);
        date.year++;
    }
    int month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(date))
        month[2] = 29;
#undef isLeapYear
    for (int i = 1; i <= 12; i++)
    {
        if (time > month[i])
        {
            time -= month[i];
            date.month++;
        }
        else
        {
            date.day += time;
            return date;
        }
    }
}
uint32_t getTimefromDate(Date date)
{
#define isLeapYear(date) ((date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0))
    Date a;
    a.year = 1970;
    a.month = 1;
    a.day = 1;
    uint32_t time = 0;
    while (a.year < date.year)
    {
        time += 365 + (int)isLeapYear(a);
        a.year++;
    }
    int month[] = {0, 31, 28 + (int)isLeapYear(date), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int mon = 1; mon < date.month; ++mon)
        time += month[mon];
    time += date.day - 1;
    return time;
#undef isLeapYear
}
char *timeToString(Date date)
{
    char *str = (char *)malloc(sizeof(char) * MAX_CHAR_BUFFER);
    sprintf(str, "%hu年%hu月%hu日", date.year, date.month, date.day);
    return str;
}
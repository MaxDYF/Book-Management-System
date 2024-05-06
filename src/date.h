#include <stdint.h>
#include <time.h>
#ifndef _DATE_H_
#define _DATE_H_
typedef struct Date
{
    int16_t year;
    int16_t month;
    int16_t day;
} Date;
/*
 *  将内部整数类型时间转换为标准日期格式
 */
Date getDatefromTime(uint32_t time);
/*
 *  将标准日期格式转换为内部整数类型时间
 */
uint32_t getTimefromDate(Date date);
char *timeToString(Date date);
void timeInit();
#endif
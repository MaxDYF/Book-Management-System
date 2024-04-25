#include <stdint.h>
typedef struct Date;
/*
 *  将内部整数类型时间转换为标准日期格式
 */
Date getDatefromTime(uint32_t time);
/*
 *  将标准日期格式转换为内部整数类型时间
 */
uint32_t getTimefromDate(Date date);
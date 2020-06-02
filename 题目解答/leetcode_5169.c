#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int year;
    int month;
    int day;
} DateStruct;

bool isLeapYear(int year)
{
    if (year % 100 == 0 && year % 400 == 0) {
        return true;
    } else if (year % 4 == 0 && year % 100 != 0){
        return true;
    }
    return false;
}

int calcuMonthDay(int month, bool leapYear)
{
    // 注意这里的月份是从1开始的，为了简单期间，把第0个月设置成0天。
    int tmp[13] = {0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int num = 0;
    for (int i = 0; i < month; i++) {
        num += tmp[i];
    }
    if (leapYear && month > 2) { // 注意这里的大2判断，如果当前月份不大于2，就没有必要。
        return num + 1;        
    } 
    return num; 
}

int calcuNum(DateStruct* data)
{
    int leepYear = 0;
    int i;
    int firstNum = 0;
    for (i = 1971; i < data->year; i++) {
        if (isLeapYear(i)) {
            leepYear++;
        }
    }
    int firstNumYear = 365 * (data->year - 1971 - leepYear) + 366 * leepYear;
    int firstNumMonth = calcuMonthDay(data->month, isLeapYear(data->year));
    firstNum = firstNumYear + firstNumMonth + data->day;
    return firstNum;
}

int daysBetweenDates(char * date1, char * date2){
    if (date1 == NULL || date2 == NULL) {
        return 0;
    }

    DateStruct dat1 = {0};
    DateStruct dat2 = {0};
    char year[5] = {0};
    char month[3] = {0};
    char day[3] = {0};
    
    memcpy(year, date1, 4);
    dat1.year = atoi(year);
    memcpy(month, (date1 + 5), 2);
    dat1.month = atoi(month);
    memcpy(day, (date1 + 8), 2);
    dat1.day = atoi(day);

    memcpy(year, date2, 4);
    dat2.year = atoi(year);
    memcpy(month, (date2 + 5), 2);
    dat2.month = atoi(month);
    memcpy(day, (date2 + 8), 2);
    dat2.day = atoi(day);

    int firstNum = calcuNum(&dat1);
    int secNum = calcuNum(&dat2);
    // 从给的用例来看，相隔的天数是大于0的数。
    if (secNum > firstNum) { 
        return secNum - firstNum;
    } else if (secNum < firstNum) {
        return firstNum - secNum;
    }
    return 0;
}



int main(void)
{
    char dat1[] = {"1973-01-01"};
    char dat2[] = {"1972-01-01"};
    int result = daysBetweenDates(dat1, dat2);
    printf("%d", result);
    system("pause");
}
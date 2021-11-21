### leetcode 1396. 设计地铁系统
#### 思路
1. 熟练使用UT_hash_handle
2. 这里数据结构使用很关键，使用2个hash table. 第一个使用id作为key,保存站名和开始时间；
第二个以开始和结束站名为key,保存总人数和总时间数。这个非常关键，在这个表中就能计算出总的时间，也能统计出总的人数，所以对于后面的计算都很有帮忙
#### 代码
```
#define STATION_NAME_LEN 24
typedef struct {
    int key; // 顾客ID
    char stationName[STATION_NAME_LEN];
    int startTime;
    UT_hash_handle hh;
} CheckIn;

typedef struct{
    char key[STATION_NAME_LEN];
    int totalNum;
    int totalTime;
    UT_hash_handle hh;
} CheckOut;

typedef struct {
    CheckIn* inUsers;
    CheckOut* outUsers;
} UndergroundSystem;


UndergroundSystem* undergroundSystemCreate() {
    UndergroundSystem* obj = (UndergroundSystem* )malloc(sizeof(UndergroundSystem));
    obj->inUsers = NULL;
    obj->outUsers = NULL;
    return obj;
}

void undergroundSystemCheckIn(UndergroundSystem* obj, int id, char * stationName, int t) {
    int key = id;
    CheckIn* add = (CheckIn*)malloc(sizeof(CheckIn));
    memset(add, 0, sizeof(CheckIn));
    add->key = id;
    strcpy(add->stationName, stationName);
    add->startTime = t;
    HASH_ADD_INT(obj->inUsers, key, add);
    //printf("[In] id=%d,time=%d\n", id, t); 
}

void undergroundSystemCheckOut(UndergroundSystem* obj, int id, char * stationName, int t) {
    CheckIn* findIn;
    int key = id;
    HASH_FIND_INT(obj->inUsers, &key, findIn);
    if (findIn) { // 找到了。
        CheckOut* findOut;
        char keyStr[STATION_NAME_LEN] = {0};
        strcpy(keyStr, findIn->stationName);
        strcat(keyStr, "-");
        strcat(keyStr, stationName);
        //printf("keyStr=%s\n", keyStr);
        HASH_FIND_STR(obj->outUsers, keyStr, findOut);
        if (findOut != NULL) {
            findOut->totalNum++;
            findOut->totalTime +=(t - findIn->startTime);
        } else {
            CheckOut* add = (CheckOut* )malloc(sizeof(CheckOut));
            memset(add, 0, sizeof(CheckOut));
            char tmp[STATION_NAME_LEN] = {0};
            strcpy(tmp, findIn->stationName);
            strcat(tmp, "-");
            strcat(tmp, stationName);
            //printf("%s\n", tmp);
            strcpy(add->key, tmp);
            add->totalNum = 1;
            add->totalTime = (t - findIn->startTime); // 这里totalTime是指当前要出站的乘客所用时间。
            //printf("[OUT] id=%d, totalTime=%d, num=%d, key=%s\n", id, add->totalTime, add->totalNum, tmp);
            HASH_ADD_STR(obj->outUsers, key, add);           
        }

    } else {
        printf("cannot find\n");
    }
}

double undergroundSystemGetAverageTime(UndergroundSystem* obj, char * startStation, char * endStation) {
    CheckOut* avg;
    char key[STATION_NAME_LEN] = {0};
    strcpy(key, startStation);
    strcat(key, "-");
    strcat(key, endStation);
    HASH_FIND_STR(obj->outUsers, key, avg);
    //printf("[AVG] key=%s totalTime=%d, totalNum=%d\n", key, avg->totalTime, avg->totalNum);
    return (double)avg->totalTime / (double)avg->totalNum;
}

void undergroundSystemFree(UndergroundSystem* obj) {
    CheckIn* cur;
    CheckIn* tmp;
    HASH_ITER(hh, obj->inUsers, cur, tmp) {
        HASH_DEL(obj->inUsers, cur);
        free(cur);
    }
    CheckOut* cur1;
    CheckOut* tmp1;
    HASH_ITER(hh, obj->outUsers, cur1, tmp1) {
        HASH_DEL(obj->outUsers, cur1);
        free(cur1);
    }
    free(obj);
}

```
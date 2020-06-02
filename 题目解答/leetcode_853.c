/*
* 该题目就是说，在到达终点时，有多少批车是同时到达的。
* 首先根据位置，速度，距离信息，整理出每辆车目前的距离以及到终点的时间（时间使用float型来存储）关系对。
* 对距离进行升序排序。
* 然后从后往前遍历，计算每一辆车和他后面的一辆车 到达终点的时间关系。有2种情况需要考虑，见下面解法。
*/
typedef struct {
    int position;
    float spendTime;
} formatData;

int cmp(const void* a, const void* b)
{
    formatData* aa = (formatData*)a;
    formatData* bb = (formatData*)b;
    return aa->position - bb->position; // 按照距离的升序排序。
}

int carFleet(int target, int* position, int positionSize, int* speed, int speedSize){
    //printf("\n%d,%d,%d\n", target, positionSize, speedSize);
    if (positionSize == 0 || speedSize == 0) {
        return 0;
    }
    if (positionSize == 1) {
        return 1;
    }

    formatData* data = (formatData*)malloc(sizeof(formatData) * positionSize);
    for (int i = 0; i < positionSize; i++) {
        data[i].position = position[i];
        data[i].spendTime = (float)(target - position[i]) / (float)speed[i];
       // printf("\n%d, %f\n", data[i].position, data[i].spendTime);
    }
    //printf("\n%d, %d\n", sizeof(formatData), sizeof(formatData*));
    qsort(data, positionSize, sizeof(formatData), cmp);
    int group = 1;

    for (int k = positionSize - 1; k > 0; k--) {
        if (data[k].spendTime < data[k - 1].spendTime) { // 后面的车追不上，车队数增加1
            group++;
        } else if (data[k].spendTime > data[k - 1].spendTime) { // 后面车追上来了，车队数不增加。
            data[k - 1].spendTime = data[k].spendTime; // 要更新当前车所用的时间,因为不能超车，所以跟上来后就只能减速和K一样行驶。
        }
    }
    return group;
}

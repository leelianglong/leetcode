/*
* 该题目可以看成有面气球墙，可以从地面任意位置发射箭，箭向上射穿气球。题目给了每个气球的直径（在水平方向上）的起始位置和结束位置。
* 解题思路：
* 1、通过排序，以每个气球的直径的结束位置从低到高来排序。
* 2、气球直径的起始和结束位置有可能重叠。
* 3、然后找出有多少个重叠的，那么使用的箭的数就是总的气球数减去重叠的数。
* 4、如何找重叠则是关键所在：以排序后的第0个气球的xend值为起始值left。然后从第1开始，比较第i个气球的xstart是否小于 left，如果小于，则说明这2个
     气球有重叠，那么把重叠的数加 1， 然后更新left值，这个left要取 left 和 第 i个 气球xend中较小的值。
     如果不小，则没有重叠，直接更新 left值为 第i个气球的xend.
*/
int cmp(const void* a, const void* b)
{
    int* aa = *(int**)a;
    int* bb = *(int**)b;
    return aa[1] - bb[1];
}

int findMinArrowShots(int** points, int pointsSize, int* pointsColSize){
    if (pointsSize <= 0) {
        return 0;
    }
    qsort(points, pointsSize, sizeof(int*), cmp);
    //for (int i = 0; i < pointsSize; i++) {
    //    printf("(%2d, %2d)\n", points[i][0], points[i][1]);
   // }
    int start = points[0][1]; // 右边界起始值，如果有气球的xstart值小于这个起始值，则它们用1个箭即可
    int noNeedOtherArrowCounter = 0;
    for (int i = 1; i < pointsSize; i++) {
        if (points[i][0] <= start) {
            noNeedOtherArrowCounter++;
            start = start < points[i][1] ? start : points[i][1];
        } else {
            start  = points[i][1];
        }
    }
    //printf("\n final %d", noNeedOtherArrowCounter);
    return pointsSize - noNeedOtherArrowCounter;
}

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

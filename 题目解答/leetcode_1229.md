## 题目
```
给定两个人的空闲时间表：slots1 和 slots2，以及会议的预计持续时间 duration，请你为他们安排 时间段最早 且合适的会议时间。

如果没有满足要求的会议时间，就请返回一个 空数组。

「空闲时间」的格式是 [start, end]，由开始时间 start 和结束时间 end 组成，表示从 start 开始，到 end 结束。 

题目保证数据有效：同一个人的空闲时间不会出现交叠的情况，也就是说，对于同一个人的两个空闲时间 [start1, end1] 和 [start2, end2]，要么 start1 > end2，要么 start2 > end1。

 

示例 1：

输入：slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 8
输出：[60,68]
示例 2：

输入：slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 12
输出：[]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/meeting-scheduler
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
```
### 思路
```
1. 要安排2个人的会议，首先得找到2个人同时空闲的时段，所以要找交集
2. 把空闲时间按照起始时间排序。
3. 依次比较2个人空闲的开始或结束时间，如果a的结束时间比b的开始时间要小，这样当日a和b不可能有交集，所以需要遍历a的下一个时间段，反之亦然。
4. 注意交集时间段的左右边界的处理
5. 如果交集时间符合要求就直接退出了，题目要求的是最早符合要求的
```
### 代码
```
int cmp(const void* a, const void* b)
{
    int* aa = *(int**)a;
    int* bb = *(int**)b;
    return aa[0] - bb[0];
}

int* minAvailableDuration(int** slots1, int slots1Size, int* slots1ColSize, int** slots2, int slots2Size, int* slots2ColSize, int duration, int* returnSize){
    qsort(slots1, slots1Size, sizeof(slots1[0]), cmp);
    qsort(slots2, slots2Size, sizeof(slots2[0]), cmp);
    int a1 = 0;
    int b1 = 0;
    int* res = (int*)calloc(2, sizeof(int));
    *returnSize = 0;
    for (a1 = 0, b1 = 0; a1 < slots1Size && b1 < slots2Size;) {
        if (slots1[a1][0] > slots2[b1][1]) {
            b1++;
        } else if (slots1[a1][1] < slots2[b1][0]) {
            a1++;
        } else {
            int left = fmax(slots1[a1][0], slots2[b1][0]);
            int right = fmin(slots1[a1][1], slots2[b1][1]);
            if (slots1[a1][1] < slots2[b1][1]) { // 在交叉情况下，slot1的结束时间 < slot2的结束时间，所以把slot1的遍历加1.
                a1++; 
            } else {
                b1++;
            }
            if (right - left >= duration) {
                res[0] = left;
                res[1] = left + duration;
                *returnSize = 2;
                break;
            }
        }
    }
    return res;
}
```

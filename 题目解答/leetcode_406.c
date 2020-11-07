/*
重建队列

思路：
1、其实最终重建好的队列就是期望站的队列。它们根据高矮顺序站好了，并且能够看到前面有多少个人。这里能看到的人有个特点就是，要比自己高。如果比自己矮的话是看不到的。现在题目是给出的顺序是打乱的了
2、根据上面所说的只能看到比自己高的，那么首先要根据身高从高到低排序， 在身高一样的情况下，根据他能看到的人的数量从小到大排序。这样排好序之后，就基本满足要求。
3、然后，遍历数组，并根据他能够看到的人数，把他插入到对应的位置上，关键点见代码注释。
*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int cmp(const void* a, const void* b)
{
    int* aa = *(int**)a;
    int* bb = *(int**)b;
    if (aa[0] != bb[0]) {
        return bb[0] - aa[0]; // 根据身高从高到低排序
    } else {
        return aa[1] - bb[1]; // 根据前面人数，从少到多排序
    }
}

int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes){
    int** res = (int**)malloc(sizeof(int*) * peopleSize);
    for (int i = 0; i < peopleSize; i++) {
        res[i] = (int*)malloc(sizeof(int) * peopleColSize[i]);
        for (int j = 0; j < peopleColSize[i]; j++) {
            res[i][j] = 0;
        }
    }

    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(sizeof(int) * peopleSize);
    for (int i = 0; i < peopleSize; i++) {
        (*returnColumnSizes)[i] = peopleColSize[i];
    }

    qsort(people, peopleSize, sizeof(people[0]), cmp);

    for (int i = 0; i < peopleSize; i++) {
        //printf("(%d %d)", people[i][0], people[i][1]);
        int idx = people[i][1]; // 这个是当前人应该去的位置。
        for (int j = i; j > idx; j--) { // 如果这个位置上有人了，就把它们逐个往后面移动一下。
            res[j][0] = res[j - 1][0];
            res[j][1] = res[j - 1][1];
        }
        res[idx][0] = people[i][0]; //移动完了之后，就把它们放在要去的位置上
        res[idx][1] = people[i][1];
    }
    *returnSize = peopleSize;
    return res;
}

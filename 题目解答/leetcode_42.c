/*
* 遍历数组中元素，第一个和最后一个不用遍历， 分别找当前元素的左边最大值和右边最大值；
* 取两边最大值中较小值，用其中较小值减取当前元素的高度，就是当前元素能够盛的最多的水。
* 然后把各个节点盛的水的总量加起来。
*/

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) > (b) ? (b) : (a))

int trap(int* height, int heightSize){
    int res = 0;
    for (int i = 1; i < heightSize - 1; i++) {
        int maxLeft = 0;
        int maxRight = 0;
        for (int j = i; j >= 0; j--) {
            maxLeft = MAX(maxLeft, height[j]);
        }
        for (int k = i; k < heightSize; k++) {
            maxRight = MAX(maxRight, height[k]);
        }
        printf("%d,", MIN(maxRight, maxLeft) - height[i]);
        res += MIN(maxRight, maxLeft) - height[i];
    }
    return res;
}

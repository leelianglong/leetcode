/*
* 盛水最多的容器，盛水是由2个柱子中较矮的来决定的，盛水多少也就是面积，2个柱子之间的距离，乘以其中一边较矮的柱子高度。
* 这里使用双指针，两边向中间移动，在移动的过程中计算面积，更新最大面积。
* 移动的规则是：如果左边的高度小与 右边，则要把左边的坐标右移，即，left++;反之则要把右边的向左移动，即right--.
* 这样移动的原因是：要想下一个矩形面积比当前的大，要把较短的边向中间移动才行。
*/

int maxArea(int* height, int heightSize){
    int max = 0;
    int left = 0;
    int right = heightSize - 1;
    while (left < right) {
        int area = (right - left) * (height[right] > height[left] ? height[left] : height[right]);
        max = max > area ? max : area;
        if (height[left] > height[right]) {
            right--;
        } else {
            left++;
        }
    }
    return max;
}

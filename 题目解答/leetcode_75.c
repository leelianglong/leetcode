void sortColors(int* nums, int numsSize){
    if (nums == NULL || numsSize <= 0) {
        return;
    }
    int hashColor[3] = {0};

    for (int i = 0; i < numsSize; i++) {
        hashColor[nums[i]]++;
    }

    for (int red = 0; red < hashColor[0]; red++) {
        nums[red] = 0;
    }

    for (int white = hashColor[0]; white < hashColor[1] + hashColor[0]; white++) {
        nums[white] = 1;
    }

    for (int blue = hashColor[0] + hashColor[1]; blue < numsSize; blue++) {
        nums[blue] = 2;
    }
}


// 根据快排的思想，使用2个指针把数组分成3个部分，然后遍历交换，得到下面的算法
#define SWAP(a, b) do {\
    int tmp = a;\
    a = b;\
    b = tmp;\
} while (0)

void sortColors(int* nums, int numsSize){
    int zero = 0; // 使用下面2个指针 把数组划分成3部分 zero前面的表示小于等于0的。 大于等于two的在这个后面
    int two = numsSize; 
    int i = 0;
    while (i < two) {
        if (nums[i] == 0) { // 遇到0了，要把它换到zero前面，并且zero本身也有加1，避免下一次的计算结果被覆盖
            SWAP(nums[zero], nums[i]);
            i++;
            zero++;
        } else if (nums[i] == 1) {
            i++;
        } else { // 如果遇到2，要把它放到two的后面。并且two要减1.这样下次调整的时候就不会覆盖上次的。
            two--;
            SWAP(nums[i], nums[two]);
        }
    } 
}

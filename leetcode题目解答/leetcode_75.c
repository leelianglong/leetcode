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
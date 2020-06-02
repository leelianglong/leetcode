/**
 * 本题的意思是给定一些餐厅信息，通过特定条件，按照规则输出餐厅序号。
 * 思路就是根据条件，多次使用qsort来排序，每次特定条件后，餐厅的数量就会变化。当把所有条件都遍历完，就得到最终的结果。
 */
int cmpVegan(const void* a, const void* b)
{   
    int* aa = *(int**)a;
    int* bb = *(int**)b;
    return bb[2] - aa[2];
}


int cmpPrice(const void* a, const void* b)
{
    int* aa = *(int**)a;
    int* bb = *(int**)b;

    return aa[3] - bb[3];
}

int cmpDistance(const void* a, const void* b)
{
    int* aa = *(int**)a;
    int* bb = *(int**)b;
    return aa[4] - bb[4];
}

int cmpRating(const void* a, const void* b)
{
    int* aa = *(int**)a;
    int* bb = *(int**)b;  
    if (aa[1] == bb[1]) {
        return bb[0] - aa[0];
    } else {
        return bb[1] - aa[1];
    }
}

int* filterRestaurants(int** restaurants, int restaurantsSize, int* restaurantsColSize, int veganFriendly, int maxPrice, int maxDistance, int* returnSize){
    //printf("\n %2d, %2d %2d ,%2d\n", sizeof(uintptr_t*), sizeof(int**), restaurantsSize, veganFriendly);
    int leaveVegan = 0;
    if (veganFriendly == 1) {
        qsort(restaurants, restaurantsSize, sizeof(int*), cmpVegan);
        for (leaveVegan = 0; leaveVegan < restaurantsSize; leaveVegan++) {
            if (restaurants[leaveVegan][2] != 1) {
                //printf("\n leaveVegan \n");
                break;
            }
        }
    } else {
        leaveVegan = restaurantsSize;
    }
    //printf("\n leaveVegan = %d\n", leaveVegan);
    int leavePri = 0;
    qsort(restaurants, leaveVegan, sizeof(int*), cmpPrice);
    for (leavePri = 0; leavePri < leaveVegan; leavePri++) {
        if (restaurants[leavePri][3] > maxPrice) {
            break;
        }
    }
    //printf("\n leavePri = %d\n", leavePri);
    int leaveDis = 0;
    qsort(restaurants, leavePri, sizeof(int*), cmpDistance);
    for (leaveDis = 0; leaveDis < leavePri; leaveDis++) {
        if (restaurants[leaveDis][4] > maxDistance) {
            break;
        }
    }
    printf("\n leaveDis = %d\n", leaveDis);
    int leaveRat = 0;
    qsort(restaurants, leaveDis, sizeof(int*), cmpRating);

    int* res = (int*)malloc(sizeof(int) * leaveDis);
    for (int k = 0; k < leaveDis; k++) {
        res[k] = restaurants[k][0];
    }
    *returnSize = leaveDis;
    return res;
}

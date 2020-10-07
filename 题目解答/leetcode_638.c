 int result;
void dfs(int* need, int needsSize, int** special, int specialSize, int* specialColSize, int* specialTotalPrice, int needTotalPrice) {
    for (int i = 0; i < needsSize;i++) {
        if (need[i] < 0) { // 当某个需要的物品已经买够了之后，就退出。
            return;
        }
    }
    result = result > needTotalPrice ? needTotalPrice : result;

    for (int i = 0; i < specialSize; i++) { // 从总的需求中减去每一个大礼包中的物品
        for (int j = 0; j < specialColSize[i] - 1; j++) {
            need[j] -= special[i][j];
        }
        dfs(need, needsSize, special, specialSize, specialColSize, specialTotalPrice, needTotalPrice - specialTotalPrice[i] + special[i][specialColSize[i] - 1]);
        for (int k = 0; k < specialColSize[i] - 1; k++) { // 这里相当是回溯，把前面减去的，这里再加上。
            need[k] += special[i][k];
        }
    }
}

int shoppingOffers(int* price, int priceSize, int** special, int specialSize, int* specialColSize, int* needs, int needsSize){
    if (specialSize <= 0) {
        return 0;
    }
    int specialTotalPrice[specialSize];// 记录每个大礼包中的物品的真实总价，即用单价乘以数量。
    for (int i = 0; i < specialSize; i++) {
        int tmp = 0;
        for (int j = 0; j < specialColSize[i] - 1; j++) {
            tmp += (price[j] * special[i][j]);
        }
        specialTotalPrice[i] = tmp;
        tmp = 0;
    }

    int needTotalPrice = 0; // 购买需要的物品所需的总价（不使用大礼包的情况）
    for (int i = 0; i < needsSize; i++) { 
        needTotalPrice += (price[i] * needs[i]);
    }

    result = needTotalPrice;
    dfs(needs, needsSize, special, specialSize, specialColSize, specialTotalPrice, needTotalPrice);
    return result;

}

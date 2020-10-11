/*
本题思路：
1、要分析那种情况下行星会碰撞，如何碰撞，是撞一下就完了，还是在有可能的情况下，逐个撞击，本题的题意是后者。
第一种：序列本身就是空，此时不会产生碰撞，直接放入行星序列的尾端。
第二种：当序列的最尾端是负数，nextItem < 0，这时方向相同并且速度相同，两个同方向的行星不会产生碰撞，直接放入行星序列的尾端。
第三种：当序列的最尾端是负数，nextItem > 0，这时两个行星的运动方向相反，并不会产生碰撞（比如[-5,-10]在右端放入5），直接放入行星序列的尾端。
第四种：当序列的最尾端是正数，nextItem > 0，这时方向相同并且速度相同，两个同方向的行星不会产生碰撞，直接放入行星序列的尾端。
第五种：当序列的最尾端是正数，nextItem < 0，这时方向相对，两个方向的行星必定会产生碰撞，按照碰撞规则：两个行星相互碰撞，较小的行星会爆炸。如果两颗行星大小相同，则两颗行星都会爆炸。
也就是说，只有第五种情况需要特殊处理。
*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 #define MAX_ASTEROID_COUNTER  10001

typedef struct {
    int top;
    int data[MAX_ASTEROID_COUNTER];
} Stack;

Stack* Init(void) {
    Stack* obj = (Stack*)malloc(sizeof(Stack));
    obj->top = -1;
    memset(obj->data, 0, sizeof(int) * MAX_ASTEROID_COUNTER);
    return obj;
}
bool Push(Stack* obj, int data) {
    if (obj->top >= MAX_ASTEROID_COUNTER - 1) {
        return false;
    }
    obj->top++;
    obj->data[obj->top] = data;
    return true;
}

bool Pop(Stack* obj, int* data) {
    if (obj->top < 0) {
        return false;
    }
    *data = obj->data[obj->top];
    obj->top--;
    return true;
}

int GetTopElement(Stack* obj) {
    return obj->data[obj->top];
}

bool IsEmpty(Stack* obj) {
    return obj->top < 0;
}

int* asteroidCollision(int* asteroids, int asteroidsSize, int* returnSize){
    *returnSize = 0;
    int* result = (int*)malloc(sizeof(int) * asteroidsSize);
    memset(result, 0, sizeof(int) * asteroidsSize);
    if (asteroidsSize <= 0) {
        return result;
    }
    Stack* obj = Init();
    int popElement = 0;
    int topElement = 0;
    for (int i = 0; i < asteroidsSize; i++) {
        if (IsEmpty(obj)) {
            //printf("\n %d\n", asteroids[i]);
            Push(obj, asteroids[i]);
        } else if (GetTopElement(obj) > 0 && asteroids[i] < 0) { // 考虑栈顶元素为正，当前元素为负的情况，这种就是有撞击可能的，把所有撞击可能都计算在内。
            while (!IsEmpty(obj) && (GetTopElement(obj) > 0 ) && asteroids[i] < 0) {
                int calcu = GetTopElement(obj) + asteroids[i];
                if (calcu < 0) {
                    // 表面栈顶元素小，要爆炸
                    Pop(obj, &popElement);
                } else if (calcu == 0) {
                    // 表面当前元素和栈顶元素都要爆炸
                    Pop(obj, &popElement);
                    asteroids[i] = INT_MAX; // 表名当前元素爆炸
                    break;
                } else {
                    asteroids[i] = INT_MAX; // 表名当前元素爆炸
                    break;
                }
            }
            if (asteroids[i] != INT_MAX) {
                Push(obj, asteroids[i]);
            }
        } else { // 其他情况都直接入栈
            Push(obj, asteroids[i]);
        }
    }
    int counter = obj->top;
    //printf("size=%d", obj->top);
    *returnSize = counter + 1;
    int counter1 = obj->top;
    for (int i = 0; i <= counter; i++) {
        Pop(obj, &popElement);
        result[counter1--] = popElement;
    }

    return result;
}

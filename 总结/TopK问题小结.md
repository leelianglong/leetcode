### 例如题目：
1、最小的K个数：
输入整数数组 arr ，找出其中最小的 k 个数。例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。

#### 方案一： 快速排序的手动实现。
#### 思路
1. 快排的思路是先随机选择一个元素作为基准，然后把比它大的元素放在该基准的左边，比它小的元素放在该基准的右边。
2. 该基准的选择最好是随机的。
3. 这里需要一个额外的变量 big,记录最后一个比基准大的元素的位置。每次遍历的时候，它需要赋值成 start - 1. 然后在[start, end]，范围内查找有比基准大的元素，如果有，就先把big++,然后交换他们。最后，再把big++,然后把基准和big对应的元素交换一下。
4. 返回big，这个值就是本次基准在最终排好序的队列中的位置。

#### 代码
当前题目是 offer 76
```
void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partion(int* nums, int start, int end)
{
    int rad = rand() % (end - start + 1) + start;
    swap(&nums[rad], &nums[end]);
    int big = start - 1; // 要放在 start前面，用于跟踪比选定元素小的最后一个元素位置。
    for (int j = start; j < end; j++) {
        if (nums[j] > nums[end]) { // 找到有比选定元素还大的元素，此时需要交换。刚开始的big是0，找到一个后，自增，然后和当前元素进行调换。
            big++;
            swap(&nums[big], &nums[j]); // 范围[0,big)之间的元素都是大于选定元素的。但是他们自身没有顺序。
        }
    }
    big++;// 遍历完之后，把big自增后，再和最后的元素调换一下，就把选定的元素接到比它都大的元素后面，这样选定的元素在整个数组中的位置就确定了。
    swap(&nums[big], &nums[end]);
    return big; // 确定选定元素在排序后的位置。
}

int findKthLargest(int* nums, int numsSize, int k){
    int start = 0;
    int end = numsSize - 1;
    int check = partion(nums, start, end);
    while (check != k - 1) {
        if (check < k - 1) {
            start += 1; // 如果确定的位置比与其的要小，说明预期的元素在该区域的后半部分，所以把start + 1. 反之，则把该end -1.
        } else { 
            end -= 1;
        }
        check = partion(nums, start, end);
    }
    return nums[check];
}
```

### 方案二：
对于n个数，我们可以统计每个数出现的次数，借助hash思路，那么从hash table中的数据的意义 hash[data],表示 data在整个输入的数据中出现的次数。
如果从头遍历hash[]则相当于把整个输入的数据排好序了。
这个方案使用于数据量已知，并且不太巨大的情况。

```
#define HASH_LENGTH   10001

int* getLeastNumbers(int* arr, int arrSize, int k, int* returnSize)
{
	int* res = NULL;
	int i;
	int hash[HASH_LENGTH] = {0};
	int idx = 0;
	
	if (arr == NULL || returnSize == NULL) {
		return NULL;
	}
	
	for (i = 0; i < arrSize; i++) {
		hash[arr[i]]++;
	}
	
	res = (int*)malloc(sizeof(int) * k);
	for (i = 0; i < HASH_LENGTH; i++) { // 这里从头开始搜索hash表
		while (hash[i]-- > 0 && idx < k) { // 这里使用while的原因在于可能有重复元素
			res[idx++] = i;	
		}
		if (idx == k) {
			break;
		}
	}
	*returnSize = k;
	return res;
}
```
### 题目，给定一个数组，请返回第K小的数据
#### 思路
#### 代码
```
void swap(int *arr, int l, int r)
{
    int tmp = arr[l];
    arr[l] = arr[r];
    arr[r] = tmp;
}

int *partion(int *arr, int L, int R, int pivot)
{
    int less = L - 1;
    int more = R + 1;
    int cur = L;

    while (cur < L) {
        if (arr[cur] < pivot) {
            swap(arr, ++less, cur);
        } else if (arr[cur] > pivot) {
            swap(arr, cur, --more);
        } else {
            cur++;
        }
    }
    int *res = (int *)malloc(sizeof(int) * 2);
    res[0] = less + 1;
    res[1] = more - 1;
    return res;
}

// arr 数组，在L 和 R的范围内，如果排序的话，找index 位置的数据。
int KSmallest(int *arr, int L, int R, int index)
{
    if (L == R) {
        return arr[L];
    }
    int pivot = arr[L + (int)rand() * (R - L + 1) % (R - L + 1)];
    int *range = partion(arr, L, R, pivot); // range[0] range[1] 分别表示 pivot把原来划分数组划分c成3等分，小于pivot 大于pivot的， 其中partion返回的值就是等于pivot的左边界和右边界序号。
    if (index >= range[0] && index <= range[1]) {
        return arr[index];
    } else if (index < range[0]) { // 在左边界左边进行递归
        return KSmallest(arr, L, range[0] - 1, index);
    }
    return KSmallest(arr, range[1] + 1, R, index);
}

int main() {
    printf("Hello, World!\n");
    int test[] = {1,100,4,56,6,7,8,9};
    int result = KSmallest(test, 0, sizeof(test) / sizeof(test[0]) - 1, 7);
    printf("result = %d", result);
    return 0;
}
```
### leetcode 451
#### 思路
1. 题目的意思是按照字符出现的频率，从大到小的重新输出字符串。
2. 使用二维数组map[128][2]来记录单个字符出现的频率。
3. 然后按照频率从高到低排序。
4. 然后遍历map把字符串重新构建
#### 代码
```
int cmp(const void* a, const void* b)
{
    int* aa  = *(int**)a;
    int* bb  = *(int**)b;
    return bb[1] - aa[1];
}
#define MAP_SIZE  256
char * frequencySort(char * s){
    int** map = (int**)malloc(sizeof(int*) * MAP_SIZE);
    for (int i = 0; i < MAP_SIZE; i++) {
        map[i] = (int*)malloc(sizeof(int) * 2);
        memset(map[i], 0, sizeof(int) * 2);
    }
    for (int i = 0; i < strlen(s); i++) {
        map[s[i] - ' '][0] = s[i] - ' ';
        map[s[i] - ' '][1]++;
    }

    qsort(map, MAP_SIZE, sizeof(map[0]), cmp);
    char* res = (char*)malloc(strlen(s) + 1);
    memset(res, 0, strlen(s) + 1);
    int count = 0;
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < map[i][1]; j++) {
            res[count++] = map[i][0] + ' ';
        }
    }
    return res;
}
```

### 面试17.14
#### 思路
1. 基于快排的思想，只需要排序好前面的K个元素即可。
2. 下面有2种方法，第一种最后1个用例超时，第二种，能够通过
#### 代码1
```
#define SWAP(a, b) do {\
    int tmp = a;\
    a = b;\
    b = tmp;\
} while (0)

int split(int* arr, int lo, int hi)
{
    int i = lo;
    int x = arr[i];
    int j;
    for (j = lo + 1; j <= hi; j++) {
        if (arr[j] <= x) {
            i++;
            SWAP(arr[i], arr[j]);
        }
    }
    SWAP(arr[lo], arr[i]);
    return i;
}


int* smallestK(int* arr, int arrSize, int k, int* returnSize){
    int count = 0;
    int* res = (int*)malloc(sizeof(int) * (k + 1));
    memset(res, 0, sizeof(int) * (k + 1));
    int lo = 0;
    int hi = arrSize - 1;
    *returnSize = 0;
    if (k == 0) {
        return res;
    }
    while (1) {
        int idx = split(arr, lo, hi);
        if (idx < k) {
            lo++;
        } else if (idx > k){
            hi--;
        } else {
            for (int m = 0; m < k; m++) {
                res[m] = arr[m];
            }
            break;
        }
    }
    
    *returnSize = k;
    return res;
}
```
#### 代码2
```
#define SWAP(a, b) do {\
    int tmp = a;\
    a = b;\
    b = tmp;\
} while (0)

void partition(int* nums, int lo, int hi, int k, int* res)
{
    int flag = nums[lo];
    int i = lo;
    int j = hi;

    while (i < j) {
        while (i < j && nums[j] >= flag) {
            j--; // 从右向左找到第一个小于比较元素的数
        }
        while (i < j && nums[i] <= flag) {
            i++; // 从左向右找到第一个大于比较元素的数
        }
        /* 上面的i，j 顺序不能调换顺序， 否则i会走过头，以至于将后面大于比较元素的数放到数组的头 */
        if (i != j) {
            SWAP(nums[i], nums[j]);
        }
    }
    SWAP(nums[lo], nums[i]);
    // 当前的索引i表示已经排好到i位置了。如果i > k,意味着，我们要找的k个最小元素在i 之前就够了。
    if (i > k) {
        partition(nums, lo, i - 1, k, res);
    } else if (i < k) { // 说明当前位置i前面的元素还不够，需要扩大搜索范围。
        partition(nums, i + 1, hi, k, res);
    } else { // 当前索引 i 刚好等于k, 说明前i个元素已经排好了，可以直接获取。
        for (int m = 0; m < k; m++) {
            res[m] = nums[m];
        }
    }
}

int* smallestK(int* arr, int arrSize, int k, int* returnSize){
    int count = 0;
    int* res = (int*)malloc(sizeof(int) * (k + 1));
    memset(res, 0, sizeof(int) * (k + 1));
    int lo = 0;
    int hi = arrSize - 1;
    *returnSize = 0;
    if (k == 0) {
        return res;
    }
    partition(arr, lo, hi, k, res);
    *returnSize = k;
    return res;
}
```


### leetcode 973
#### 思路
1. 通过手写快速排序的方法来找到前k个元素。
2. 最终要返回的是坐标点，所以添加一个结构保存下坐标点的距离和在原来points中的索引。然后基于距离来排序，找到前k个合适的距离后，根据其坐标索引，拿到原来points中的坐标返回。

#### 代码
```
typedef struct {
    int distance;
    int idx;
} Num;

#define SWAP(a, b) do {\
    Num tmp = a;\
    a = b;\
    b = tmp;\
} while (0)

int split(Num* nums, int lo, int hi)
{
    int x = nums[lo].distance;
    int i = lo;
    for (int j = lo + 1; j <= hi; j++) {
        if (nums[j].distance <= x) {
            i++;
            SWAP(nums[i],  nums[j]);
        }
    }
    SWAP(nums[lo], nums[i]);
    return i;
}

int** kClosest(int** points, int pointsSize, int* pointsColSize, int k, int* returnSize, int** returnColumnSizes){
    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(sizeof(int) * k);
    memset(*returnColumnSizes, 0, sizeof(int) * k);
    if (k == pointsSize) {
        *returnSize = pointsSize;
        for (int i = 0; i < pointsSize; i++) {
            (*returnColumnSizes)[i] = 2;
        }
        return points;
    }
    int** res = (int**)malloc(sizeof(int*) * k);
    for (int i = 0; i < k; i++) {
        res[i] = (int*)malloc(sizeof(int) * 2);
        memset(res[i], 0, sizeof(int) * 2);
    }
    Num* nums = (Num*)malloc(sizeof(Num) * pointsSize);
    for (int i = 0; i < pointsSize; i++) {
        nums[i].distance = 0;
        nums[i].idx = -1;
    }
    for (int i = 0; i < pointsSize; i++) {
        nums[i].distance = (points[i][0] * points[i][0] + points[i][1] * points[i][1]);
        nums[i].idx = i;
    }
    int lo = 0;
    int hi = pointsSize - 1;
    while (true) {
        int idx = split(nums, lo, hi);
        if (idx == k) {
            for (int m = 0; m < k; m++) {
                res[m][0] = points[nums[m].idx][0];
                res[m][1] = points[nums[m].idx][1];
                (*returnColumnSizes)[m] = 2;
            }
            break;
        } else if (idx < k) {
            lo++;
        } else {
            hi--;
        }
    }
    *returnSize = k;
    return res;
}
```
### leetcode 347
#### 思路
1. 使用ut_hash库函数，对每个数字出现的频率做统计
2. 然后基于频率排序
3. 使用HASH_ITER宏来取出需要的元素

#### 代码
```
struct Hash {
    int key;
    int times;
    UT_hash_handle hh;
};

struct Hash* users;
int cmp(const void* a, const void* b)
{
    struct Hash* aa = (struct Hash*)a;
    struct Hash* bb = (struct Hash*)b;
    return bb->times - aa->times;
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize){
    int* res = (int*)malloc(sizeof(int) * k);
    memset(res, 0, sizeof(int) * k);
    *returnSize = 0;
    users = NULL;
    for (int i = 0; i < numsSize; i++) {
        struct Hash* find;
        int key = nums[i];
        HASH_FIND_INT(users, &key, find);
        if (find == NULL) {
            struct Hash* add = (struct Hash*)malloc(sizeof(struct Hash));
            add->key = nums[i];
            add->times = 1;
            HASH_ADD_INT(users, key, add);
        } else {
            find->times++;
        }
    }
    HASH_SORT(users, cmp);
    struct Hash* cur;
    struct Hash* tmp;
    HASH_ITER(hh, users, cur, tmp) {
        if (*returnSize == k) {
            break;
        }
        res[(*returnSize)] = cur->key;
        (*returnSize)++;
    }

    return res;
}
```
### leetcode 692
#### 思路
1. 使用hash 思路，以字符串作为key,他们出现的频率设置为value。
2. 先基于频率排序，在频率一样的情况下，再以字符顺序排序

#### 代码
```
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define COUNT 32
typedef struct {
    char* src;
    int times;
} Hash;

int cmp(const void* a, const void* b)
{
    Hash* aa = (Hash*)a;
    Hash* bb = (Hash*)b;
    if (aa->times != bb->times) {
        return bb->times - aa->times;
    }
    return strcmp(aa->src, bb->src);
}

void putItem(Hash* obj, int objSize, char* str)
{
    int i;
    bool flag = false;
    //printf("enter: %s\n", str);
    for (i = 0; strlen(obj[i].src) > 0 && i < objSize; i++) {
        //printf("enter for\n");
        if (strcmp(obj[i].src, str) == 0) {
            obj[i].times++;
            //printf("find same\n");
            flag = true;
            break;
        }
    }
    if (!flag) {
        //printf("exit for\n");
        strncpy(obj[i].src, str, strlen(str));
        obj[i].times = 1;
    }
}

void dbgPrint(Hash* obj, int size)
{
    printf("hash str:\n");
    for (int i = 0; i < size; i++) {
        printf("pos=%d, src=%s, times=%d\n", i, obj[i].src, obj[i].times);
    }
    printf("\n");
}

char ** topKFrequent(char ** words, int wordsSize, int k, int* returnSize){
    char** res = (char**)malloc(sizeof(char*) * k);
    for (int i = 0; i < k; i++) {
        res[i] = (char*)malloc(sizeof(char) * COUNT);
        memset(res[i], 0, COUNT);
    }
    *returnSize = 0;
    if (wordsSize == k) {

    }
    Hash* obj = (Hash*)malloc(sizeof(Hash) * wordsSize);
    for (int i = 0; i < wordsSize; i++) {
        obj[i].src = (char*)malloc(sizeof(char) * COUNT);
        memset(obj[i].src, 0, sizeof(char) * COUNT);
        obj[i].times = 0;
    }

    for (int i = 0; i < wordsSize; i++) {
        //printf("%s\n", words[i]);
        putItem(obj, wordsSize, words[i]);
    }
    //dbgPrint(obj, wordsSize);
    qsort(obj, wordsSize, sizeof(obj[0]), cmp);
    dbgPrint(obj, wordsSize);
    for (int i = 0; i < k; i++) {
        strcpy(res[i], obj[i].src);
    }
    *returnSize = k;
    return res;
}
```


### leetcode 251
1. 手写快速排序的思路，找到第k个索引即可。

#### 代码
```
#define SWAP(a, b)    do {\
                        int tmp = a;\
                        a = b;\
                        b = tmp;\
                        } while (0)

int partition(int* nums, int lo, int hi)
{
    int flag = nums[lo];
    int i = lo;
    int j = hi;

    while (i < j) {
        while (i < j && nums[j] >= flag) {
            j--; // 从右向左找到第一个小于比较元素的数
        }
        while (i < j && nums[i] <= flag) {
            i++; // 从左向右找到第一个大于比较元素的数
        }
        /* 上面的i，j 顺序不能调换顺序， 否则i会走过头，以至于将后面大于比较元素的数放到数组的头 */
        if (i != j) {
            SWAP(nums[i], nums[j]);
        }
    }
    SWAP(nums[lo], nums[i]);
    return i;
}

int findKthLargest(int* nums, int numsSize, int k){
    int target = numsSize - k;
    int lo = 0;
    int hi = numsSize - 1;
    while (1) {
        int idx = partition(nums, lo, hi);
        if (idx == target) {
            return nums[idx];
        } else if (idx < target) {
            lo++;
        } else {
            hi--;
        }
    }
    return 0;
}
```
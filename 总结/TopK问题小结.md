例如题目：
1、最小的K个数：
输入整数数组 arr ，找出其中最小的 k 个数。例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。

方案一： 排序 qsort

方案二：
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

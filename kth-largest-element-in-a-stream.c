/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);
 
 * kthLargestFree(obj);
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int k;
    int numsSize;
    int* data;
} KthLargest;

int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
   int i;
   if (nums == NULL || numsSize <= 0) {
       return NULL;
   } 
   int* data = (int*)malloc((numsSize + 1) * sizeof(int));
   if (data == NULL) {
       return NULL;
   }
   KthLargest* tmp = (KthLargest*) malloc(sizeof(KthLargest));
   if (tmp == NULL) {
       return NULL;
   }
   tmp->k = k;
   tmp->numsSize = numsSize;
   tmp->data = data;
   for (i = 0; i < numsSize; i++) {
       tmp->data[i] = nums[i];
   }
   qsort(&(tmp->data[0]), numsSize, sizeof(tmp->data[0]), cmp);
   return tmp;
}

int kthLargestAdd(KthLargest* obj, int val) {
  int i;
  int counter;
  int j = 0;

  if (val > obj->data[obj->numsSize-1]) {
      obj->data[obj->numsSize] = val;
  }
  else if (val < obj->data[0]) {
      for (i = obj->numsSize; i > 0; i--) {
          obj->data[i] = obj->data[i - 1];
      }
      obj->data[0] = val;
  } else {
    for (i = 0; i < obj->numsSize; i++) {
        if (val >= obj->data[i]) {
            counter = i;
            for (j = obj->numsSize; j > counter; j--) {
                obj->data[j] = obj->data[j - 1];
            }
            obj->data[counter] = val;
            break;
        }
    }
  }

  return obj->data[obj->k - 1];
}

void kthLargestFree(KthLargest* obj) {
    if (obj == NULL) {
        return ;
    }
    free(obj->data);
    free(obj);
}

int main(void)
{
    KthLargest* test = NULL;
    int data[4] = {4,5,8,2};
    int k = 3;
    int result = 0;

    test = kthLargestCreate(k, data, 4);

    result = kthLargestAdd(test, 9);
    printf("\r\n%4d\r\n", result);
    #if 0
    result = kthLargestAdd(test, 5);
    printf("\r\n%4d\r\n", result);
    result = kthLargestAdd(test, 10);
    printf("\r\n%4d\r\n", result);
    result = kthLargestAdd(test, 9);
    printf("\r\n%4d\r\n", result);
    result = kthLargestAdd(test, 9);
    printf("\r\n%4d\r\n", result);
    #endif
    system("pause");
}
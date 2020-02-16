#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 当前题目实际上是链表的操作，当前的解法超时了（在大量数据的下）。可以尝试一下链表逆序再乘以k值。
typedef struct {
    int data;
    int* next;
} ProductOfNumbers;

#define HEAD_VALUE 1
ProductOfNumbers* productOfNumbersCreate() {
    ProductOfNumbers* tmp = (ProductOfNumbers*)malloc(sizeof(ProductOfNumbers));
    if (tmp == NULL) {
        return NULL;
    }
    tmp->data = HEAD_VALUE;
    tmp->next = NULL;
    return tmp;
}

void productOfNumbersAdd(ProductOfNumbers* obj, int num) {
    while(obj->next != NULL) {
        obj = obj->next;
    }
    ProductOfNumbers* tmp = productOfNumbersCreate();
    tmp->data = num;
    obj->next = tmp;
    obj =tmp;
}

int productOfNumbersGetProduct(ProductOfNumbers* obj, int k) {
    ProductOfNumbers* tmp1 = obj->next;
    ProductOfNumbers* tmp2 = obj->next;
    int res = 1;
    int counter1 = 0;
    int counter2 = 0;
    int flag = 0;
    while (tmp1) {
        counter1++;
        tmp1 = tmp1->next;
    } 
    printf("num counter = %d\r\n", counter1);
    while (tmp2) {
        if (flag) {
            tmp2 = tmp2->next;
            if (tmp2 == NULL) {
                break;
            }
            res *= tmp2->data;
            continue;
        }
        counter2++;
        if (counter2 == counter1 - k) {
            flag = 1;
        } else {
            tmp2 = tmp2->next;
        }
    }
    return res;
}

void productOfNumbersFree(ProductOfNumbers* obj) {
    ProductOfNumbers* next = NULL;
    while (obj) {
        next = obj->next;
        free(obj);
        obj = next;
    }
}


int main(void)
{
    int i;
    int test[] = {3,0,2,5,4,8};
    ProductOfNumbers* head = productOfNumbersCreate();
    for (i = 0; i < 6; i++) {
        productOfNumbersAdd(head, test[i]);
    }
    int res = productOfNumbersGetProduct(head, 6);
    printf("final res = %d\r\n", res);
    ProductOfNumbers* tmp = head->next;
    while (tmp != NULL) {
        printf("%4d", tmp->data);
        tmp=tmp->next;
    }
    productOfNumbersFree(head);
    system("pause");
}
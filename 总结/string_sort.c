#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void* a, const void* b)
{
    char* aa = *(char**)a;
    char* bb = *(char**)b;
    //return strcmp(bb, aa);
    #if 1
    int i;
    for (i = 0; i < 4; i++) {
        if (aa[i] == bb[i]) {
            continue;
        }
        return bb[i]-aa[i];
    }
   #endif
}

int main(void)
{
    char* test[] = {"ahcg", "abcd", "abtk", "aqfb", "ahcd"};
    qsort(test, sizeof(test) / sizeof(test[0]), sizeof(char*), cmp);

    int i;
    for (i = 0; i < sizeof(test) / sizeof(test[0]); i++) {
        printf("%s\n", test[i]);
    }
    return 1;
}
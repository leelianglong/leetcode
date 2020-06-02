#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfLongestSubstring(char* s){
    if(s == NULL || strlen(s) == 0) {
        return 0;
    }

    char window[26] = {0};
    int left = 0;
    int right = 0;
    int counter = 0;
    int maxLength = 0;

    while (right < strlen(s)) {
        char c1 = s[right];
        if (window[c1 - 'a'] == 0) {
            window[c1 - 'a']++;
            counter++;     
            //printf("%2d, %2d\n", maxLength, counter);
        } else {
            maxLength = counter > maxLength ? counter : maxLength; 
            c1 = s[left];
            while (left < right) {
                if (window[c1 - 'a'] >= 1) {
                    window[c1 - 'a']--;
                    counter--;
                    //printf("%2d\n", counter);
                }
                left++;
            }
        }
        right++;
    }
    //printf("final %2d %2d", right, left);
    maxLength = maxLength > (right - left) ? maxLength : (right - left);
    return maxLength ;
}

//下面是正确的解答：
int lengthOfLongestSubstring(char* s){
    if(s == NULL || strlen(s) == 0) {
        return 0;
    }

    char window[128] = {0};
    int left = 0;
    int right = 0;
    int counter = 0;
    int maxLength = 0;
    int i;

    while (right < strlen(s)) {
        window[s[right]]++; // 这里要放到里面来加。如果放在外面，下面==2的判断就有问题
        counter += window[s[right]] == 2 ? 1 : 0; // ==2的原因是在while里面相加的，只要等于2说明就重复了
        if (counter == 0) {
            right++; // 这移动有边界
            continue;
        }
        // 下面计算长度也使用的是边界相减，不要另外使用一个变量。
        maxLength = (right - left) > maxLength ? (right - left) : maxLength;
        for(i = left; i < right; i++) { // 这里要处理左边界了，不要把左边界left当做循环变量，这里会改变这个值。
            window[s[i]]--; // 进来就减。
            counter -= window[s[i]] == 1 ? 1 : 0;
            if (counter == 0) {
                left = i + 1; //这里修改左边界。
                break;
            }
        }
        right++;
    }
    maxLength = maxLength > (right - left) ? maxLength : (right - left);
    return maxLength ;
}

int main(void)
{
    char str[] = "bbc";
    int result = lengthOfLongestSubstring(str);
    printf("%d", result);
    system("pause");
}

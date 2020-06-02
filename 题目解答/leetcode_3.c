/*
* 滑动窗口解决本题。
*/

int lengthOfLongestSubstring(char * s){
    int left = 0;
    int right =0;
    int hashWindow[255] = {0};  // 窗口
    int max = 0;

    while(right < strlen(s)) {
        char c1 = s[right];
        hashWindow[c1]++; // 先把字符放入窗口，直到遇到重复字符为止
        right++;
        while (hashWindow[c1] > 1) { // 说明有重复的字符
            char c2 = s[left];
            hashWindow[c2]--; // 移动左指针，从window中移除左边的元素。
            left++;
        }
        max = (right - left) > max ? (right - left) : max; // 这里要求最长的子串，所以在每次右边界增加时，更新最长值。
    }
    return max;
}

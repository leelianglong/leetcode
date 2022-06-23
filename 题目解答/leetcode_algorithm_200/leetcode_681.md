### 题目
```
给定一个形如 "HH:MM" 表示的时刻 time ，利用当前出现过的数字构造下一个距离当前时间最近的时刻。每个出现数字都可以被无限次使用。

你可以认为给定的字符串一定是合法的。例如， "01:34" 和  "12:09" 是合法的，“1:34” 和 “12:9” 是不合法的。

输入: "19:34"
输出: "19:39"
解释: 利用数字 1, 9, 3, 4 构造出来的最近时刻是 19:39，是 5 分钟之后。
结果不是 19:33 因为这个时刻是 23 小时 59 分钟之后。

输入: "23:59"
输出: "22:22"
解释: 利用数字 2, 3, 5, 9 构造出来的最近时刻是 22:22。 
答案一定是第二天的某一时刻，所以选择可构造的最小时刻。

```

### 思路
1. 在24 * 60的范围内每次模拟加1分钟。
2. 判断当前的这个时间是否符合要求，也就是判断当前时间数字有没有起始时间数字意外的数字

### 代码
```
bool check(int h, int m, char* s)
{
    int target[4] = {0};
    target[0] = s[0] - '0';
    target[1] = s[1] - '0';
    target[2] = s[3] - '0';
    target[3] = s[4] - '0';

    bool a1 = false;
    bool b1 = false;
    bool c1 = false;
    bool d1 = false;
    for (int i = 0; i < 4; i++) {
        if (h % 10 != target[i]) {
            continue;
        }
       a1  = true;
    }
    for (int i = 0; i < 4; i++) {
        if (h / 10 != target[i]) {
            continue;
        }
        b1 = true;
    }
    for (int i = 0; i < 4; i++) {
        if (m / 10 != target[i]) {
            continue;
        }
        c1 = true;
    }
    for (int i = 0; i < 4; i++) {
        if (m % 10 != target[i]) {
            continue;
        }
        d1 = true;
    }
    return a1 && b1 && c1 && d1;
}
char * nextClosestTime(char * time){
    char cmp[6] = {0};
    strcpy(cmp, time);
    char* tmp = strtok(time, ":");
    int times[2] = {0};
    int i = 0;

    while (tmp) {
       times[i++] = atoi(tmp);
       tmp = strtok(NULL, ":");
    }
    int h = times[0];
    int m = times[1];
    int max = 24 * 60;
    int start = h * 60 + m;
    char* res = (char*)calloc(6, sizeof(char));
    int offset = 0;

    for (int i = 0; i < max; i++) {
        m++;
        if (m >= 60) {
            h++;
            m = 0;
        }
        if (h >= 24) {
            h = 0;
        }
        if (check(h, m, cmp)) {
            offset = sprintf(res, "%02d:", h);
            sprintf(res + offset, "%02d", m);
            break;
        }
    }
    return res;
}
```

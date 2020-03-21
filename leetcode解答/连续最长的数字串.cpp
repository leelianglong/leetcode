
string GetLongNumbers(const string& inputString)
{
    int i;
    int j;
    int start;
    int left = 0;
    int right = 0;
    int cur_window = 0;
    int tmp_window;
    int couterDot = 0;
    int dotPos;
    int bakupLeft;
    int bakupRight;

    for (i = 0; i < inputString.size(); i++) {
        couterDot = 0;
        if (isdigit(inputString[i]) || inputString[i] == '.') {
            start = i;
            left = start;

            for (j = start; j < inputString.size(); j++) {
                if (isdigit(inputString[j]) || inputString[j] == '.') {
                    if (inputString[j] == '.') {
                        couterDot++;
                        if (couterDot == 1) {
                            dotPos = j; /* 第一个点的位置*/
                        }
                    }
                    if (couterDot == 2) {
                        tmp_window = j - start; // 这里是一个合适的窗口
                        if (tmp_window >= cur_window) {
                            cur_window = tmp_window;
                            if (isdigit(inputString[j + 1])) { /* 点左右两边都是数字*/
                                right = j;
                            } else {
                                right = j - 1;
                            }
                            i = dotPos;
                            bakupLeft = left;
                            bakupRight = right;
                        }
                        break;
                    }
                } else {
                    tmp_window = j - start;
                    if (tmp_window >= cur_window) {
                        cur_window = tmp_window;
                        right = j;
                        i += cur_window;
                        bakupLeft = left;
                        bakupRight = right;
                    }
                    break;
                }
            }
            if (j == inputString.size()) {
                tmp_window = inputString.size() - left;
                if (cur_window < tmp_window) {
                    bakupLeft = left;
                    bakupRight = inputString.size();
                }
                break;
            }
        }
    }

    return inputString.substr(bakupLeft, bakupRight - bakupLeft);
}

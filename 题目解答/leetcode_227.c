// 本题的关键在与把符号和数字，看成成对出现的（+2  +2  *3  -5  /6），在最开始的地方增加一个 + 号， 然后通过栈根据数字前面的符号，来确定如何入栈，最终把栈中所有的数字加起来返回即可。

#define SIZE  200000
typedef struct {
    int top;
    int* data;
} Stack;

Stack* InitStack(int n)
{
    Stack* obj = (Stack*)malloc(sizeof(Stack));
    obj->data = (int*)malloc(sizeof(int) * n);
    memset(obj->data, 0, sizeof(int) * n);
    obj->top = -1;
    return obj;
}

bool PushStack(Stack* obj, int data)
{
    if (obj->top > SIZE - 1) {
        return false;
    }
    obj->top++;
    obj->data[obj->top] = data;
    return true;
}

bool PopStack(Stack* obj, int* data)
{
    if (obj->top < 0) {
        return false;
    }
    *data = obj->data[obj->top];
    obj->top--;
    return true;
}

int GetTopElement(Stack* obj)
{
    return obj->data[obj->top];
}

int calculate(char * s){
    int* num = (int*)malloc(sizeof(int) * strlen(s));
    memset(num, 0, sizeof(int) * strlen(s));
    int numCounter = 0;
    char* tmpTarget  = (char*)malloc(sizeof(char) * (strlen(s) + 1));
    memset(tmpTarget, 0, sizeof(char) * (strlen(s) + 1));
    strcpy(tmpTarget, s);
    char* strNum = strtok(tmpTarget, "+-/* ");
    while (strNum != NULL) {
        num[numCounter++] = atoi(strNum);
        strNum = strtok(NULL, "+-/* ");
    }
    char* sysbol = (char*)malloc(sizeof(char) * strlen(s));
    memset(sysbol, 0, sizeof(char) * strlen(s));
    int sysbolCounter = 0;
    int i = 0;
    while (s[i] != '\0') {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
            sysbol[sysbolCounter++] = s[i];
        }
        i++;
    }
    printf("(%d %d)", numCounter, sysbolCounter);
    int* cmb = (int*)malloc(sizeof(int) * (numCounter + sysbolCounter + 1));
    memset(cmb, 0, sizeof(int) * (numCounter + sysbolCounter + 1));
    int length = 0;
    cmb[length++] = '+';
    for (int i = 0; i < sysbolCounter; i++) {
        cmb[length++] = num[i];
        cmb[length++] = sysbol[i];
    }
    cmb[length] = num[numCounter - 1]; // 上面这个for循环是关键
    Stack* obj = InitStack(2*numCounter);

    for (int i = 0; i < 2 * numCounter; i += 2) { // 根据数字前的符号，把数字进行计算后入栈。
        switch(cmb[i]) {
            case '+': {
                PushStack(obj, cmb[i + 1]);
                break;
            }
            case '-': {
                int pre = cmb[i + 1];
                pre = -pre;
                PushStack(obj, pre);
                break;
            }
            case '*': {
                int pre = GetTopElement(obj);
                int pop = 0;
                PopStack(obj,&pop);
                pre *= cmb[i + 1];
                PushStack(obj, pre);
                break;
            }
            case '/': {
                int pre = GetTopElement(obj);
                int pop = 0;
                PopStack(obj, &pop);
                pre /= cmb[i + 1];
                PushStack(obj, pre);
                break;
            }
        }
    }
    int sum = 0;
    int calcu = 0;
    while (PopStack(obj, &calcu)) {
        sum += calcu;
    }
    return sum;
}

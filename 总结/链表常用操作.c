#include <iostream>
 
using namespace std;
 
struct List {
    int val;
    struct List* next;
};
 
void Init(struct List* L) { //创建链表
    int cur;
    cin >> cur;
    while (cur != -1) {
        struct List* ptr = (struct List*)malloc(sizeof(struct List));
        ptr->val = cur;
        ptr->next = NULL;
        L->next = ptr;
        L = L->next;
        cin >> cur;
    }
}
 
void Show(struct List* L) { //遍历链表值
    cout << "链表遍历:" ;
    
    while (L->next) {
        cout << L->next->val << " ";
        L = L->next;
    }
    cout << endl;
}
 
//在第K个位置前插入data元素,最后链表 的第K个位置就是data
void InsertList (struct List* L, int k, int data) {
    
    struct List* pre = NULL; //存储第K-1个元素的值
    struct List* ptr = (struct List*)malloc(sizeof(struct List));   //申请空间
    ptr->val = data;
    ptr->next = NULL;
    
    while (k && L->next) {  //查找到放置data元素的位置
        pre = L;
        L = L->next;
        k --;
    }
    
    if (k > 0) {    //如果K > 0 直接插到链表的表尾
        L->next = ptr;
        L = L->next;
    }else {
        pre->next = ptr;    //链接链表
        ptr->next = L;
    }
}
 
int lengthList (struct List* L) {   //求链表长度
    int len = 0;
    while (L->next) { 
        len ++;
        L = L->next;
    }
    return len;
}
void DeleteList (struct List* L, int x) {   //删除值为x的结点（链表无重复值）
    if (lengthList(L) <= 0) {
        cout << "表空，没有元素可删除" << endl;
        return;
    }
 
    struct List* ptr = L->next;
    struct List* pre = L;   //记录ptr的前一个位置的结点
    while (ptr) {
        if (ptr->val == x) {
            pre->next = ptr->next;  //把x值的结点的前一个结点的next指向ptr的next结点
            free(ptr);  //释放空间
            return;
        }
        pre = ptr;
        ptr = pre->next;
    }
}
 
void DeleteList_Position(struct List* L, int k) {   //删除第K个位置的结点
    if (lengthList(L) <= 0) {
        cout << "表空，没有元素可删除" << endl;
        return;
    }
 
    struct List* ptr = L->next;
    struct List* pre = L;   //记录ptr的前一个位置的结点
    k = k - 1;  //因为如果k = 1,直接用pre->next = ptr->next就把ptr删掉了，所以要减1
    while (k-- && ptr) {
        pre = ptr;
        ptr = ptr->next;
    } 
    if (ptr == NULL || k > 0) {
        cout << "要删除的位置不存在" << endl;
    }else {
        pre->next = ptr->next;  //删除ptr结点
        free(ptr);  //释放空间
    }
}
 
bool IsEmptyList(struct List* L) {  //判断链表是否为空
    if (L->next == NULL) {
        return true;
    }else {
        return false;
    }
}
 
 
int GetElemList(struct List* L, int i) {    //返回第i个位置的值
    struct List* ptr = L;
    int k = i;  //标记i的值，以防不存在输出显示
    while (i > 0 && ptr->next) {
        ptr = ptr->next;
        i --;
    }
 
    if (i == 0 && ptr != NULL) {    //当i == 0 和 ptr 不为空代表找到了第i个位置的元素
        return ptr->val;
    }else {
        cout << "第" << k << "个位置不存在" << endl;
        return -1;
    }
}
 
void ClearList(struct List* L) {    //清空链表
     struct List* ptr = L;
    if (lengthList(L) > 0) {
        while (ptr->next) {
           struct List* temp = ptr->next;
           ptr->next = ptr->next->next;
           free(temp);  //释放空间
        }
    }
}
 
int main() {
    
    struct List* head = (struct List*)malloc(sizeof(struct List));  //头结点(不存值)
    head->next = NULL;  
    Init(head); //初始化链表
    
    Show(head);
    int i, data;
    cout << "请输入要插入的位置和值：";
    cin >> i;
    cin >> data;
    
    InsertList(head, i, data);  //在第i个位置前插入data
    
    Show(head);
 
    int x;
    cout << "请输入要删除的值: ";
    cin >> x;
 
    DeleteList(head, x);    //删除链表中值为x的结点（链表值无重复）
    Show(head);
 
    int position;
    cout << "请输入要删除的位置: ";
    cin >> position;
    DeleteList_Position(head, position);    
    Show(head);
 
    if (IsEmptyList(head))
        cout << "链表是空链表!" << endl;
    else 
        cout << "链表不空!" << endl;
 
    cout << "链表的长度为: " << lengthList(head) << endl;
 
    int n;
    cout << "请输入要查找的位置: ";
    cin >> n;
    if (GetElemList(head, n) != -1)
        cout << "第" << n << "个位置的值为: " << GetElemList(head, n) << endl; 
 
    cout << "没有清空链表前链表长度 : " << lengthList(head) << endl;
    ClearList(head);
    cout << "清空链表后链表长度 : " << lengthList(head) << endl;
    
    
    
    return 0;
}
 
 
输入：23 33 42 56 -1
 
输出结果：
链表遍历:23 33 42 56 
 
请输入要插入的位置和值：2 28
链表遍历:23 28 33 42 56 
 
链表的长度为: 5
 
请输入要删除的值: 28
链表遍历:23 33 42 56 
 
请输入要删除的位置: 1
链表遍历:33 42 56 
 
链表不空!
 
请输入要查找的位置: 4
第4个位置不存在
 
没有清空链表前链表长度 : 3
清空链表后链表长度 : 0
————————————————
版权声明：本文为CSDN博主「SnapTap」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq_43126471/article/details/92065858

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/*
* 常识：
* 二叉树无论是什么序的遍历，都是访问根节点的数据，把根节点的数据取出来。
*/
/****************** 浜屽弶鏍戠粨鏋勫畾涔� ****************/
typedef struct BTNode {
    int data;
    struct BTNode* lchild;
    struct BTNode* rchild;
} BinaryNode, *BinaryTree;
/****************** 浜屽弶鏍戠粨鏋勫畾涔� ****************/

/****************** 鏍堢殑缁撴瀯瀹氫箟 *****************/
#define  STATCK_LENGTH           1000
typedef struct {
    int top;
    BinaryTree* data; /* 杩欓噷闇€瑕佷娇鐢ㄤ簩鍙夋爲鎸囬拡鐨勬寚閽� */
} Stack;
/****************** 鏍堢殑缁撴瀯瀹氫箟 *****************/

/****************** 闃熷垪缁撴瀯瀹氫箟 *****************/
typedef struct QNode {
    BinaryTree* data;
    struct QNode* next;
} QueueNode,*QueueList;

typedef struct LQ {
    QueueList front, rear; // 瀵瑰ご鎻掑叆锛岄槦灏惧垹闄�
} LinkQueue;
/****************** 闃熷垪缁撴瀯瀹氫箟 *****************/

/***************************************鏍堝熀鏈搷浣�**************************************/
bool InitStack(Stack* para)
{
    if (para == NULL) {
        return false;
    }
    para->data = (BinaryTree*)malloc(STATCK_LENGTH * sizeof(BinaryTree));
    if (para->data == NULL) {
        return false;
    }
    memset(para->data, 0, STATCK_LENGTH * sizeof(BinaryTree));
    para->top = -1;
    return true;
}

/*
涓嬮潰瀹炵幇鐨勬爤鏄悜涓婂闀匡細
涓€寮€濮媡op鍦ㄦ渶搴曟锛屾瘡娆″叆鏍堬紝top鍏堝鍔狅紝鎶婂厓绱犳斁鍒版爤椤躲€�
鍑烘爤鏃讹紝鍏堜粠鏍堥《鎷垮嚭鍏冪礌锛岀劧鍚庢爤椤舵寚閽坱op鍐嶅噺鍑忋€�
*/
bool PushStack(Stack* para, BinaryTree data)
{
    if (para == NULL) {
        return false;
    }
    if (para->top > STATCK_LENGTH - 1) {
        return false;
    }
    para->data[++para->top] = data;
    return true;
}

bool PopStack(Stack* para, BinaryTree* data)
{
    if (para == NULL) {
        return false;
    }
    if (para->top < 0) {
        return false;
    }
    *data = para->data[para->top--];
    return true;
}

bool CheckStackIsEmpty(Stack* para)
{
    return para->top == -1 ? true : false;
}
/***************************************鏍堝熀鏈搷浣�**************************************/

/**************************************闃熷垪鍩烘湰鎿嶄綔**************************************/
bool InitQueue(LinkQueue* lq)
{
    lq->front = lq->rear = (QueueList)malloc(sizeof(QueueNode));
    if (lq->front == NULL) {
        return false;
    }
    lq->front->next = NULL;
    return true;
}

void DestoryQueue(LinkQueue* lq)
{
    while (lq->front) {
        lq->rear = lq->front->next;
        free(lq->front);
        lq->front = lq->rear;
    }
}

bool QueueIsEmpty(LinkQueue lq)
{
    return lq.rear == lq.front ? true : false;
}

int GetQueueLength(LinkQueue lq)
{
    int i = 0;
    QueueList p = lq.front;
    while (lq.rear != p) {
        i++;
        p = p->next;
    }
    return i;
}

bool InsertQueue(LinkQueue* lq, BinaryTree data)
{
    QueueList p;
    p = (QueueList)malloc(sizeof(QueueNode));
    if (p == NULL) {
        return false; 
    }
    p->data = data;
    p->next = NULL;
    lq->rear->next = p; //璧峰垵闃熷熬鑺傜偣鐨勪笅涓€涓槸null锛岃繖閲屾柊鍒涘缓涓€涓妭鐐瑰氨鎺ヤ笂銆�
    lq->rear = p; //鏂板垱寤虹殑鑺傜偣鍙樻垚闃熷熬銆�
    return true;
}

bool DelQueue(LinkQueue* lq, BinaryTree* data)
{
    QueueList p;
    if (lq->rear == lq->front) {
        return false;
    }
    p = lq->front->next;
    *data = p->data;
    lq->front->next = p->next;
    if (lq->rear == p) {
        lq->rear = lq->front;
    }
    free(p);
    return true;
}
/**************************************闃熷垪鍩烘湰鎿嶄綔**************************************/




/* 
鍒涘缓浜屼簩鍙夋爲锛�
杩欑鏄互鍓嶅簭鏂瑰紡鏉ュ垱寤轰簩鍙夋爲锛屽湪鏋勯€犳暟鎹椂锛屼竴瀹氳鎶婂彾瀛愯妭鐐圭殑宸﹀瓙鏍戝拰鍙冲瓙鏍戦兘璁剧疆鎴愮粨鏉熺銆�
鎵嶈兘鎸夌収棰勬湡鐢熸垚浜屽弶鏍戙€傚氨鏄妸浜屽弶鏍戞瀯閫犳垚婊′簩鍙夋爲锛屾墍鏈夌殑鍙跺瓙闃舵鐨勯兘鏄� 缁撴潫绗︺€�
娉ㄦ剰锛氶€掑綊璋冪敤涔熸槸鍑芥暟姣忔閲嶅叆涓€娆★紝璇ュ嚱鏁颁腑鐨勫眬閮ㄥ彉閲忎篃浼氬湪閲嶅叆鐨勬椂鍊欐秷澶憋紝濡傛灉闇€瑕佸湪鏁翠釜
鍑芥暟閫€鍑轰箣鍓嶉兘闇€瑕佷繚鎸佺殑鍙橀噺锛岃璁剧疆鎴愬叏灞€鍙橀噺锛屾垨鑰呴潤鎬佸眬閮ㄥ彉閲忥紝鎴栬€呬娇鐢ㄦ寚閽堜紶鍏ャ€�
褰撳墠鍑芥暟鍦ㄥ娆¤皟鐢ㄦ椂锛岃璁板緱鎶奵ounter娓呴浂銆�
*/
void CreatBinary(BinaryTree* bt, int* data, int* counter)
{
    if (data[(*counter)] == 999) {
        *bt = NULL;
        (*counter)++;
        return;
    }
    (*bt) = (BinaryTree)malloc(sizeof(BinaryNode));
    if (*bt == NULL) {
        return;
    }
    (*bt)->data = data[(*counter)];
    (*counter)++;
    CreatBinary(&(*bt)->lchild, data, counter);
    CreatBinary(&(*bt)->rchild, data, counter);
}

/*
浜屽弶鏍戦攢姣�
*/
int DestoryBinaryTree(BinaryTree bt)
{
    if (bt) {
        if (bt->lchild) {
            DestoryBinaryTree(bt->lchild);
        }
        if (bt->rchild) {
            DestoryBinaryTree(bt->rchild);
        }
        free(bt);
        bt = NULL;
    }
}

/*
浜屽弶鏍戝垽绌�
*/
bool BinaryTreeIsEmpety(BinaryTree bt)
{
    return bt == NULL ? true : false;
}

/*
鑾峰彇浜屽弶鏍戠殑娣卞害(閫掑綊鏂规)
*/
int GetBinaryTreeDeepth(BinaryTree bt)
{
    int i, j;
    if (bt == NULL) {
        return 0;
    }
    if (bt->lchild) {
        i = GetBinaryTreeDeepth(bt->lchild);
    }
    else
    {
        i = 0;
    }

    if (bt->rchild) {
        j = GetBinaryTreeDeepth(bt->rchild);
    }
    else
    {
        j = 0;
    }
    return i > j ? i + 1 : j + 1;
}

/*
鑾峰彇鏍戞繁搴︾殑鍙︿竴绉嶇畝鍗曢€掑綊鐗堟湰鍐欐硶,鍏堣绠楀乏瀛愭爲鐨勬繁搴︼紝鍐嶈绠楀彸瀛愭爲鐨勬繁搴︼紝鐒跺悗鍙栧叾涓緝澶х殑锛屾渶鍚�
鍐嶅姞涓婃牴鑺傜偣鐨勬繁搴�1锛屽氨鏄暣涓簩鍙夋爲鐨勬繁搴�
*/
int dfs_deepth(BinaryTree bt) 
{
    if (bt == NULL) {
        return 0;
    }
    int leftDeepth = dfs_deepth(bt->lchild) + 1;
    int rightDeepth = dfs_deepth(bt->rchild) + 1;
    return (leftDeepth > rightDeepth ? leftDeepth : rightDeepth);
}

int GetBinaryTreeDeepthV1(BinaryTree bt)
{
    if (bt == NULL) {
        return 0;
    }
    return dfs_deepth(bt);
}

/*
缁熻鍙跺瓙鑺傜偣鐨勪釜鏁�
*/
int dfs_leaf_count(BinaryTree bt, int* counter)
{
    if (bt == NULL) {
        return 0;
    }
    if (bt->lchild == NULL && bt->rchild == NULL) {
        return (*counter)++;
    }
    if (bt->lchild) {
        dfs_leaf_count(bt->lchild, counter);
    }
    if (bt->rchild) {
        dfs_leaf_count(bt->rchild, counter);
    }
}

int GetLeafCounter(BinaryTree bt) {
    static int counter = 0;
    if (bt == NULL) {
        return 0;
    }
    dfs_leaf_count(bt, &counter);
    return counter;
}

/*
缁熻浜屽弶鏍戞墍鏈夎妭鐐逛釜鏁�
*/
int GetNodeCounter(BinaryTree bt)
{
    int leftHigh = 0;
    int rightHigh = 0;
    BinaryTree left = bt;
    BinaryTree right = bt;
    if (bt == NULL) {
        return 0;
    }
    while (left) {
        left = left->lchild;
        leftHigh++;
    }

    while (right) {
        right = right->rchild;
        rightHigh++;
    }

    if (leftHigh == rightHigh) {
        return (int)(1 << rightHigh) - 1; // 宸﹀彸瀛愭爲涓€鏍烽珮锛屾槸婊′簩鍙夋爲锛岃妭鐐逛釜鏁� = 2^n - 1;
    } 
    return 1 + GetNodeCounter(bt->lchild) + GetNodeCounter(bt->rchild);
}

/*
鍓嶅簭閬嶅巻锛岄€掑綊鐗堟湰
*/
void PreOrderTraverse(BinaryTree bt, int* saveData, int* counter)
{
    if (bt == NULL) {
        return ;
    }
    saveData[(*counter)++] = bt->data;   
    if (bt->lchild) {
        PreOrderTraverse(bt->lchild, saveData, counter);    
    }
    if (bt->rchild) {
        PreOrderTraverse(bt->rchild, saveData, counter);
    }
}

/*
浜屽弶鏍戠殑鍓嶅簭閬嶅巻(闈為€掑綊鐗堟湰锛屾爤瀹炵幇)锛屽厛鎶婃爤椤跺厓绱犲叆鏍堬紝鐒跺悗鍑烘爤锛屽啀鎶婂彸瀛愭爲鍏ユ爤锛屽啀鎶婂乏瀛愭爲鍏ユ爤锛岀劧鍚庡啀鍑烘爤锛屼竴鐩村惊鐜埌鏍堜负绌恒€�
*/
int* PreOrderTraverseByStack(BinaryTree bt, int* counter)
{
    Stack binaryTree = {0};
    int* saveData = (int*)malloc(STATCK_LENGTH * sizeof(int));
    if (saveData == NULL) {
        return NULL;
    }
    memset(saveData, 0, STATCK_LENGTH * sizeof(int));
    InitStack(&binaryTree);
    PushStack(&binaryTree, bt);

    while (!CheckStackIsEmpty(&binaryTree)) {
        PopStack(&binaryTree, &bt);
        saveData[(*counter)++] = bt->data;
        if (bt->rchild) {
            PushStack(&binaryTree, bt->rchild);
        }
        if (bt->lchild) {
            PushStack(&binaryTree, bt->lchild);
        }
    }
    return saveData;
}

/*
浜屽弶鏍戠殑涓簭閬嶅巻(閫掑綊鐗堟湰)
*/
void MiddleOrderTraverse(BinaryTree bt, int* saveData, int* counter)
{
    if (bt == NULL) {
        return ;
    }
    if (bt->lchild) {
        MiddleOrderTraverse(bt->lchild, saveData, counter);        
    }
    saveData[(*counter)++] = bt->data;
    if (bt->rchild) {
        MiddleOrderTraverse(bt->rchild, saveData, counter);        
    }
}

/**
 * 涓簭闈為€掑綊閬嶅巻锛岋紙宸﹀瓙鏍戯紝鏍硅妭鐐癸紝鍙冲瓙鏍戯級锛岃棣栧厛鎵惧埌宸﹀瓙鏍戠殑宸﹀彾瀛愯妭鐐癸紝鎵€浠ヨ鎶婃墍鏈夊乏瀛愭爲鍏ユ爤锛岀瓑鎵€鏈夌殑宸﹀瓙鏍戝叆鏍堝悗锛屽彇鏍堥《鍏冪礌锛�
 * 閬嶅巻鍙冲瓙鏍�
 * */
int* MiddleOrderTraverseByStack(BinaryTree bt, int* counter)
{
    Stack binaryTree = {0};
    int* saveData = (int*)malloc(STATCK_LENGTH * sizeof(int));
    if (saveData == NULL) {
        return NULL;
    }
    memset(saveData, 0, STATCK_LENGTH * sizeof(int));
    InitStack(&binaryTree);
    while (bt != NULL || binaryTree.top != -1) {
        while (bt != NULL) { // 鍏堟妸宸﹀瓙鏍戝叏閮ㄥ叆鏍�
            PushStack(&binaryTree, bt);
            bt = bt->lchild;
        }
        if (binaryTree.top != -1) { // 宸﹀瓙鏍戝叆鏍堢粨鏉熷悗锛屽彇鏍堥《鍏冪礌锛岃緭鍑烘爤椤跺厓绱狅紝閬嶅巻鍙冲瓙鏍�
            PopStack(&binaryTree, &bt);
            saveData[(*counter)++] = bt->data;
            bt = bt->rchild;
        }
    }
    return saveData;
}

/*
浜屽弶鏍戠殑鍚庡簭閬嶅巻(閫掑綊鐗堟湰)
*/
void PostOrderTraverse(BinaryTree bt, int* saveData, int* counter)
{
    if (bt == NULL) {
        return ;
    }
    PostOrderTraverse(bt->lchild, saveData, counter);
    PostOrderTraverse(bt->rchild, saveData, counter);
    saveData[(*counter)++] = bt->data;
}

/*******************************************************************************
鎬濊矾锛�
1銆佸湪杩涜鍚庡簭閬嶅巻鐨勬椂鍊欐槸鍏堣閬嶅巻宸﹀瓙鏍戯紝鐒跺悗鍦ㄩ亶鍘嗗彸瀛愭爲锛屾渶鍚庢墠閬嶅巻鏍硅妭鐐广€傛墍浠ュ湪闈為€掑綊鐨勫疄鐜颁腑瑕佸厛鎶婃牴鑺傜偣鍏ユ爤
2銆佸啀鎶婂乏瀛愭爲鍏ユ爤鐩村埌宸﹀瓙鏍戜负绌猴紝姝ゆ椂鍋滄鍏ユ爤銆傛鏃舵爤椤跺氨鏄渶瑕佽闂殑鍏冪礌锛屾墍浠ョ洿鎺ュ彇鍑鸿闂畃銆傚湪璁块棶缁撴潫鍚庯紝杩樿鍒ゆ柇琚
   闂殑鑺傜偣p鏄惁涓烘爤椤惰妭鐐圭殑宸﹀瓙鏍�
3銆佸鏋滄槸鐨勮瘽閭ｄ箞杩橀渶瑕佽闂爤椤惰妭鐐圭殑鍙冲瓙鏍戯紝鎵€浠ュ皢鏍堥《鑺傜偣鐨勫彸瀛愭爲鍙栧嚭璧嬪€肩粰p
4銆佸鏋滀笉鏄殑璇濆垯璇存槑鏍堥《鑺傜偣鐨勫彸瀛愭爲宸茬粡璁块棶瀹屼簡锛岄偅涔堢幇鍦ㄥ彲浠ヨ闂爤椤惰妭鐐逛簡锛屾墍浠ユ鏃跺皢p璧嬪€间负null
*******************************************************************************/
int* PostOrderTraversByStack(BinaryTree bt, int* counter)
{
    Stack binaryTree = {0};
    BinaryTree haveAccess = NULL; // 鐢ㄦ潵鏍囪鍙冲瓙鏍戞槸鍚﹁闂埌浜嗭紝鍦ㄨ闂埌鐨勬儏鍐典笅锛屾墠鑳借闂牴鑺傜偣銆�
    int* saveData = (int*)malloc(STATCK_LENGTH * sizeof(int));
    if (saveData == NULL) {
        return NULL;
    }
    memset(saveData, 0, STATCK_LENGTH * sizeof(int));
    InitStack(&binaryTree);
    while (bt != NULL || binaryTree.top != -1)
    {
        while (bt != NULL) { // 閬嶅巻瀹屾墍鏈夊乏瀛愭爲
            PushStack(&binaryTree, bt);
            bt = bt->lchild;
        }
        PopStack(&binaryTree, &bt);
        if (bt->rchild == NULL || haveAccess == bt->rchild) {
            saveData[(*counter)++] = bt->data;
            haveAccess = bt;
            bt = NULL;
        } else {
            PushStack(&binaryTree, bt); //鍦ㄥ洖鍒版牴鑺傜偣鏃讹紝鍐嶆鎶婃牴鑺傜偣鍏ユ爤
            bt = bt->rchild;
        }
    }
    return saveData;
}


/*
浜屽弶鏍戠殑灞傛閬嶅巻
*/
int* LevelTraverse(BinaryTree bt, int* counter)
{
    int* res = (int*)malloc(STATCK_LENGTH * sizeof(int));
    if (res == NULL) {
        return NULL;
    }
    LinkQueue lq = {0};
    InitQueue(&lq);
    InsertQueue(&lq, bt);
    while (GetQueueLength(lq)) {
        DelQueue(&lq, &bt);
        res[(*counter)++] = bt->data;
        if (bt->lchild) {
            InsertQueue(&lq, bt->lchild);
        }
        if (bt->rchild) {
            InsertQueue(&lq, bt->rchild);
        }
    }
    return res;
}

int main(void)
{
    int data[] = {1,2,4,999,999,5,999,999,3,6,999,999,7,999,999,999,999,999,999,999}; // 浣跨敤杩欑鏂规硶鍒涘缓浜屽弶鏍戯紝闇€瑕佸湪鏈€鍚庝竴涓妭鐐规暟鎹悗闈㈠彸瓒冲鐨�999.
    int counter = 0;
    int i;
    int saveData[10] = {0};
    BinaryTree root = NULL;
    int accessCounter = 0;
    int* result = NULL;

    CreatBinary(&root, data, &counter);
    PreOrderTraverse(root, saveData, &accessCounter);
    printf("\r\n鍓嶅簭閬嶅巻锛氶€掑綊\r\n");
    for(i = 0; i < accessCounter; i++) {
        printf("%4d", saveData[i]);
    }
    int deepth = GetBinaryTreeDeepth(root);
    int leafCount = GetLeafCounter(root);
    accessCounter = 0;
    result = PostOrderTraversByStack(root, &accessCounter);
    printf("\r\n鍓嶅簭閬嶅巻锛氶潪閫掑綊\r\n");
    for (i = 0; i < accessCounter; ++i) {
        printf("%4d", result[i]);
    }
    counter = GetNodeCounter(root);
    printf("\r\nnode is %u\r\n", counter);

    printf("\r\nlevel traverse\r\n");
    counter = 0;
    result = LevelTraverse(root, &counter);
    for (i = 0; i < counter; ++i) {
        printf("%4d", result[i]);
    }
    system("pause");
}

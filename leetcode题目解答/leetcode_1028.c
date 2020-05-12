/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/*
用栈维护当前节点的祖先节点集合。
如果当前深度大于栈的长度，将多余的节点出栈，保证栈中只包含当前节点的祖先节点。
栈顶为当前节点的父节点。
如果父节点的左子树为空，则将当前值赋给左子树，否则赋值给右子树

*/

#define STACK_SIZE 1000
typedef struct {
    int top;
    struct TreeNode* data[STACK_SIZE];
} TreeStack;

TreeStack* InitStack()
{
    TreeStack* tmp = (TreeStack*)malloc(sizeof(TreeStack));
    tmp->top = -1;
    for (int i = 0; i < STACK_SIZE; i++) {
        tmp->data[i] = NULL;
    }
    return tmp;
}

bool PushStack(TreeStack* st, struct TreeNode* element)
{
    if (st->top > STACK_SIZE - 1) {
        return false;
    }
    st->top++;
    st->data[st->top] = element;
    return true;
}

struct TreeNode* PopStack(TreeStack* st)
{
    struct TreeNode* element = NULL;
    if (st->top == -1) {
        return element;
    }
    element = st->data[st->top];
    st->top--;
    return element;
}
struct TreeNode* GetTopElement(TreeStack* st)
{
    return st->data[st->top];
}

int findNum(char* data, int index)
{
    while (index < strlen(data) && data[index] >= '0' && data[index] <= '9') {
        index++;
    }
    return index;
}

int findDeepth(char* data, int index) {
    while (index < strlen(data) && data[index] == '-') {
        index++;
    }
    return index;
}

struct TreeNode* recoverFromPreorder(char * S){
    char tmpSaveStr[100] = {0};
    TreeStack* stack = InitStack();
    int index = findNum(S, 0);
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left = NULL;
    root->right = NULL;
    strncpy(tmpSaveStr, &S[0], index);
    root->val = atoi(tmpSaveStr);

    memset(tmpSaveStr, 0, sizeof(tmpSaveStr));
    PushStack(stack, root);

    for (; index < strlen(S); index++) {
        int r = findDeepth(S, index);
        //printf("\ntop=%d, r=%d, index=%d", stack->top, r, index);
        while (stack->top > r - index) {
            PopStack(stack);
        }
        struct TreeNode* node = GetTopElement(stack);
        int e = findNum(S, r);
        //printf("\ne=%d", e);
        strncpy(tmpSaveStr, &S[r],  e - r);
        int num = atoi(tmpSaveStr);
        //printf("\nnum=%d", num);
        memset(tmpSaveStr, 0, sizeof(tmpSaveStr));
        struct TreeNode* tmp = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        tmp->val = num;
        tmp->left = NULL;
        tmp->right = NULL;
        if (node->left) {
            node->right = tmp;
        } else {
            node->left = tmp;
        }
        PushStack(stack, tmp);
        index = e;
    }
    return root;
}

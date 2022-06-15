## 题目
```
给你一棵二叉树，请按以下要求的顺序收集它的全部节点：

依次从左到右，每次收集并删除所有的叶子节点
重复如上过程直到整棵树为空
示例:

输入: [1,2,3,4,5]
  
          1
         / \
        2   3
       / \     
      4   5    

输出: [[4,5,3],[2],[1]]
 

解释:

1. 删除叶子节点 [4,5,3] ，得到如下树结构：

          1
         / 
        2          
 

2. 现在删去叶子节点 [2] ，得到如下树结构：

          1          
 

3. 现在删去叶子节点 [1] ，得到空树：

          []        
```

### 思路
```
1. 采用后续遍历
2. 当获取了叶子节点后，记得把他们的父节点设置成NULL
3. 学习当前的递归的使用
```
### 代码
```
void dfs(struct TreeNode* root, int* res, int* cnt)
{
    struct TreeNode* left, *right;
    if (root->left) {
        left = root->left;
        if (!left->left && !left->right) {
            res[(*cnt)++] = left->val;
            root->left = NULL; // 相当于把root的左孩子完全删除了，因为它左孩子的2个孩子都没有。
            printf("L=%d\n", left->val);
        } else {
            printf("not find l\n");
            dfs(root->left, res, cnt);
        }
    }
    if (root->right) {
        right = root->right;
        if (!right->left && !right->right) {
            res[(*cnt)++] = right->val;
            root->right = NULL;
            printf("R=%d\n", right->val);
        } else {
            printf("not find r\n");
            dfs(root->right, res, cnt);
        }
    }
    printf("exit\n");
}
#define CNT 10000
#define LEN 100
int** findLeaves(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    int** result = (int**)calloc(CNT, sizeof(int*));
    int* tmp = (int*)calloc(LEN, sizeof(int));
    *returnSize = 0;
    if (root == NULL) {
        return result;
    }
    *returnColumnSizes = (int*)calloc(CNT, sizeof(int));
    int cnt = 0;
    while (root->left || root->right) {
        dfs(root, tmp, &cnt);
        printf("cnt=%d\n", cnt);
        result[*returnSize] = (int*)calloc(cnt, sizeof(int));
        memcpy(result[*returnSize], tmp, sizeof(int) * cnt);
        (*returnColumnSizes)[*returnSize] = cnt;
        (*returnSize)++;
        cnt = 0;
    }
    result[*returnSize] = (int*)calloc(1, sizeof(int));
    result[*returnSize][0] = root->val;
    (*returnColumnSizes)[*returnSize] = 1;
    (*returnSize)++;
    return result;
}
```

### 题目，leetcode 187

题目要求重复的字符串。这个字符串的长度是10，在给定的字符串中有重复出现的。

学习：下面的的手动实现hash的算法。

### 代码
```
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
size_t get_hash(char *str)
{//ensure strlen(str)>=10
    register size_t hash=0;
    for(int i=0;i<10;i++)
    {
        hash=hash*131+str[i];
    }
    return hash;
}
struct Hash{
    size_t val;//保存hash,相同的hash视为同一字符串
    bool save;//是否已经保存，用于去重
    struct Hash *next_hash;//链表处理hash冲突
};

char ** findRepeatedDnaSequences(char * s, int* returnSize){
    int hash_size=strlen(s)-9;
    char **ret=NULL;
    *returnSize=0;
    if(hash_size<2)return ret;
    struct Hash **hash_map=calloc(hash_size,sizeof(struct Hash *));
    for(int i=0;i<hash_size;i++)
    {
        size_t hash_key=get_hash(s+i);
        struct Hash *hash_node=hash_map[hash_key%hash_size];
        struct Hash * new_node=NULL;
        if(!hash_node)
        {
            new_node=(struct Hash *)malloc(sizeof(struct Hash));
            new_node->next_hash=NULL;
            new_node->val=hash_key;
            new_node->save=false;
            hash_map[hash_key%hash_size]=new_node;
        }
        else
        {
            while(hash_node)
            {
                if(hash_node->val==hash_key)
                {
                    if(!hash_node->save)
                    {
                        hash_node->save=true;
                        (*returnSize)++;
                        ret=(char **)realloc(ret,sizeof(char *)*(*returnSize));
                        ret[(*returnSize)-1]=(char *)calloc(11,sizeof(char));
                        strncpy(ret[(*returnSize)-1],s+i,sizeof(char)*10);
                        printf("%s\n",ret[(*returnSize)-1]);
                    }
                    break;
                }
                else
                {
                    if(!hash_node->next_hash)
                    {
                        new_node=(struct Hash *)malloc(sizeof(struct Hash));
                        new_node->next_hash=NULL;
                        new_node->val=hash_key;
                        new_node->save=false;
                        hash_node->next_hash=new_node;
                        break;
                    }
                    hash_node=hash_node->next_hash;
                }
            }
        }
    }
    for(int i=0;i<hash_size;i++)
    {
        struct Hash *hash=hash_map[i];
        while(hash)
        {
            struct Hash *tmp=hash;
            hash=hash->next_hash;
            free(tmp);
        }
    }
    free(hash_map);
    return ret;
}

作者：mu-mian-hua-yu
链接：https://leetcode-cn.com/problems/repeated-dna-sequences/solution/c-hash-by-mu-mian-hua-yu-2/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

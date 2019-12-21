/* 
* 思路：
* （1）因为所有的皇后都不能放在同一列，因此任意两个a[0].....a[7]的值不能存在相同的两个值
* （2）所有的皇后都不能在对角线上，那么该如何检测两个皇后是否在同一个对角线上？我们将棋盘的方格成一个二维数组，
      假设有两个皇后被放置在（i，j）和（k，l）的位置上，明显，当且仅当|i-k|=|j-l| 时，两个皇后才在同一条对角线上
*/
#include <stdio.h>
int queens(int Queens){
    int i, k, flag, not_finish=1, count=0;
    //正在处理的元素下标，表示前i-1个元素已符合要求，正在处理第i个元素
	int a[Queens+1];    //八皇后问题的皇后所在的行列位置，从1幵始算起，所以加1
    i=1;
    a[1]=1;  //为数组的第一个元素赋初值

    while(not_finish){  //not_finish=l:处理尚未结束
        while(not_finish && i<=Queens){  //处理尚未结束且还没处理到第Queens个元素            for(flag=1,k=1; flag && k<i; k++) //判断是否有多个皇后在同一行
                if(a[k]==a[i]){
                    flag=0;
}

            for (k=1; flag&&k<i; k++){  //判断是否有多个皇后在同一对角线
                if( (a[i]==a[k]-(k-i)) || (a[i]==a[k]+(k-i)) ){
                    flag=0;
                }
            }

            if(!flag){  //若存在矛盾不满足要求，需要重新设置第i个元素
                if(a[i]==a[i-1]){  //若a[i]的值已经经过一圈追上a[i-1]的值
                    i--;  //退回一步，重新试探处理前一个元素

                    if(i>1 && a[i]==Queens){
                        a[i]=1;  //当a[i]为Queens时将a[i]的值置1
                    }
                    else {
                        if(i==1 && a[i]==Queens){
                            not_finish=0;  //当第一位的值达到Queens时结束
                        }
                        else{
                            a[i]++;  //将a[il的值取下一个值
                       }
                    }
                }else if(a[i] == Queens){
                    a[i]=1;
                }
                else{
                    a[i]++;  //将a[i]的值取下一个值
               }
            }else if(++i<=Queens){
                if(a[i-1] == Queens ) {
                    a[i]=1;  //若前一个元素的值为Queens则a[i]=l
     }
                else {
                    a[i] = a[i-1]+1;  //否则元素的值为前一个元素的下一个值
               }
        }

        if(not_finish){
            ++count;    
            if(a[Queens-1]<Queens){
                a[Queens-1]++;  //修改倒数第二位的值
            }
            else {
                a[Queens-1]=1;
            }
            i = Queens -1;    //开始寻找下一个满足条件的解
        }
    }
	return count;
}



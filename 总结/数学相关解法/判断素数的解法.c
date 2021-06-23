// 下面是素数判断的一个
bool isPrime(int n)
{
    if (n == 2 || n == 3) return 1;
    if (n % 6 != 1 && n % 6 != 5) return 0;
    
    for (int i = 5; i <= floor(sqrt(n)); i += 6) {
        if ((n % i == 0) || (n % (i + 2)) == 0) {
           return 0;
         }    
    }
            
    return 1;
}

//下面的方法也可行，但是比较耗时
bool isPrimeSelf(int n)
{
    int i;

    for(i = 2; i <= floor(sqrt(n)); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

#include<stdio.h>

int operation(int n1,int n2, int sum){
    *p = malloc(strlen(*p))
    if (*p =="sum"){
        return n1+n2;
    }
    if(*p == "diff"){
        return n1-n2;
    }
    if (*p =="multiplication")
    {
        return n1*n2;
    }
}

int main()
{
    int n1, n2;
    scanf("%d",&n1);
    scanf("%d",&n2);

    printf("%d+%d=%d\n",n1, n2, operation(n1, n2, sum));
    printf("%d-%d=%d\n",n1, n2, operation(n1, n2, diff));
    printf("%d*%d=%d\n",n1, n2, operation(n1, n2, multiplication));
}

#include <iostream>

#include <stdio.h>

#define MAX_DATA  8192




int main()
{
    char a[] = "1中国-人名大学fa大福大";        //要加密的密码
    char b[] = "A";     //密钥
    int len = strlen(a);
    int i;
    //加密代码
    for (i = 0; i < len; i++)
    {
        a[i] = ~a[i];
        a[i] = a[i] ^ b[0];
    }
    printf("Your Password is encrypted: %s\n", a);

    /*解密代码*/
    for (i = 0;i < len;i++)
    {
        a[i] = a[i] ^ b[0];
        a[i] = ~a[i];
    }

    printf("You Password: %s\n", a);

    return 0;
}


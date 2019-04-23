#include<alloca.h>
#include<stdio.h>

void f()
{
    char*buf=(char * )alloca(600);
    snprintf(buf,600,"hi! %d %d %d\n",1,2,3);
    puts(buf);
}

int main()
{
    f();
}

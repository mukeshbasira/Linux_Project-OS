#include <unistd.h>
#include <stdio.h>

#define __NR_myfork 335
int myfork()
{
return syscall(__NR_myfork);
}

void myfork_test()
{
myfork();
printf("Hello World");
return;
}

int main()
{
myfork_test();
return 0;
}

#include <string.h>
#include <sys/random.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>




int checkPrime(int nu)//function to check prime number
{
double num=nu;
num=sqrt(num);

int tempNum=(int)num;
int i=2;

if(nu%(i)==0&&nu!=2)
{
return 1;
}
i=3;
while(i<=tempNum)
{
if(nu%i==0)
{
return 1;
}
i+=2;
}

return 0;
}

void getxy(int *x,int *y)// getting ramdom number using system call for better randomization
{
int * buff=(int *)malloc(sizeof(int));
getrandom((void*)buff,sizeof(int),1);
srandom(*buff);

*x=random()%10;
*y=random()%10;

while(*x==*y)
*y=random()%10;


}



int main(int argc,char **argv)
{
//creating pipe
int pip1[2];
if(pipe(pip1)==-1)
perror("error Pipe");



int pid1=fork();






if(pid1 == 0)//child program
{
int S=0;
int gn=0;
close(pip1[1]);
char buf[5];
while(1)
{

read(pip1[0],buf,5);
sscanf(buf,"%d",&gn);
if(checkPrime(gn)==1)
{
printf("%d is NOT prime \n sum till now is %d\n",gn,S);

}else
{
S+=gn;
printf("%d iS  PRIME \n sum till now is %d\n ",gn,S);
}

if(gn==-1)
break;

gn=gn%3;
wait(&gn);
}
close(pip1[1]);
}


if(pid1!=0)//parent program
{

int  nm[10][2];
int x,y;

for(int i=0;i<10;i++)
{
nm[i][0]=10+i;
nm[i][1]=0;
}

int flag=0;


close(pip1[0]);
char snum[5];

while(flag!=10)
{
getxy(&x,&y);
//printing x and y
printf("\nx:%d",nm[x][0]);
printf("\ny:%d",nm[y][0]);

sprintf(snum,"%d",nm[y][0]);
write(pip1[1],snum,5);

if(nm[y][1]==0)
{
nm[y][1]=1;
flag++;
}


int t=nm[x][0];
t=t/3;
sleep(t);//wait for parent 
}

sprintf(snum,"%d",-1);
write(pip1[1],snum,5);

close(pip1[1]);
}


return 0;
}

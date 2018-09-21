// gedit .bashrc
// in .bashrc add source ~/OS_Assignment/.newgrep.sh
//run the following command in OS_Assignment folder
//chmod +x .newgrep.sh
//source ~/.newgrep.sh



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>
char* cconcat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
int main(int argc,char **argv)
{
	char foo[4096];
	int pid;

  int status;
	int fd[2];
	if(pipe(fd)==-1)
		perror("pipe");
	pid=fork();
	if(pid==0)                             //child process
	{
		dup2(fd[1],STDOUT_FILENO);
		close(fd[0]);      // closing  the read descriptor
		close(fd[1]);         // closing  the write descriptor

  char *oo =  cconcat("grep -n ",argv[1]); // concat first argument
 char *ii = cconcat(oo," ");
 char *returnn = cconcat(ii, argv[2] ); //concat tge second ar
  char *s=  cconcat(returnn,  "|cut -d : -f1" );
printf("%s \n",s);
       char *p[] = {"/bin/sh","-c",s,'\0'};

		execv(p[0],p);
	}
	else
	{
		close(fd[1]);
		int bytes=read(fd[0],foo,sizeof(foo));
		printf("Output : (%.*s)\n",bytes,foo);
		wait(&status);
	}
	return 0;
}

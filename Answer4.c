#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>

int main()
{
	int n,r,k;
	scanf("%d %d %d",&n,&k,&r);  //taking input
	int pid;
	int fd[2];
	char newk[100];
	int child_fd[2],par_fd[2];
	sprintf(newk,"%d",k+1);  // converting k into String for passing into exec() command
	pipe(par_fd);            // creating pipe for reading
	pipe(child_fd); 	//creating another pipe for duplex
	if(pipe(fd)==-1)
		perror("Pipe failed");
	pid=fork();			//creating a new process for printing the process
	if(pid==0)
	{
		char read_pid[10];
		char signal[10];
		int lens=sprintf(signal,"%d",1);
		close(child_fd[0]);
		close(par_fd[1]);
		int cnt=0;
			while(1)
					{
						sleep(n);      // sleep for n seconds
						cnt++;
						char foo[5000];
						int pid2;
						int fd2[2];
						if(pipe(fd2))
							perror("Pipe2 failed");
						pid2=fork();          
						if(pid2==0)
						{
							int pid3=fork();
							if(pid3==0)
							{
			//sleep(n);
								//dup2(fd2[1],STDOUT_FILENO);
								close(fd2[0]);
								close(1);
								dup(fd2[1]);
								execlp("ps","ps","-ef","--sort=-pcpu",NULL);  ///command for getting process details in sorted order
								exit(0);
							}
							else
							{

								wait(NULL);

								int pid4=fork();
								if(pid4==0)
								{
									close(fd2[1]);
									close(0);
									dup(fd2[0]);
									printf("\n\n");
									execlp("head","head","-n",newk,NULL);  //getting top k process and printing them
									exit(0);
								}
								else
								{
									wait(NULL);
									exit(0);
								}
							}
						}
						else
						{
							wait(NULL);
						}
			

						if(cnt%r==0)     // if it has printed for r times then asking for id from parents to kill.
						{
							
							cnt=0;
							int pid5=fork();
							if(pid5==0)
							{

								write(child_fd[1],signal,lens);
								sleep(3);                      // waiting for 3 sec to take id no from parent to kill the process
								read(par_fd[0],read_pid,10);  // reading the id no that is to be killed.
								if(read_pid[0]=='$')
								{
									exit(0);
								}
								int y=read_pid[0]-'0';
								int kills_id=0;
								int cnts=1;
								while(cnts<=y)			/// converting the string recieved from parent to id no.
								{
									kills_id=kills_id*10+(read_pid[cnts]-'0');
									cnts++;
								}
								char v[100];
								sprintf(v,"%d",kills_id);
								execlp("kill","kill",v,NULL);   // command for killling a process
								exit(0);
							}
							else
							{
								wait(NULL);
							}
						}
					}
	}
	else
	{
		char buff[10],ss[100];
		int kill_id;
		close(child_fd[1]);
		close(par_fd[0]);
		while(1)
		{
			sleep(n);
			read(child_fd[0],buff,10);
			if(buff[0]=='1')
			{
				printf("Id to kill ?\n" );
				scanf("%d",&kill_id);    // taking id from parent
				int id=kill_id;
				int dig=0;
				while(id>0)          // counting no of digit in the id.
				{
					dig++;
					id=id/10;
				}
				int x;
				if(kill_id==-1)
				{
					x=sprintf(ss,"$");
				}
				else
					x=sprintf(ss,"%d%d\n",dig,kill_id);  // storing the length and kill id in ss.
				write(par_fd[1],ss,x);   // writing into the pipe
			}
		}
		wait(NULL);
		exit(0);
	}

}

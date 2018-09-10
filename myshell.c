#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>

// intro of the makers of myshell
void myshell_shell_started()
{   time_t t;
  time(&t);
  printf("\n*************************************************");
  printf("\n***                 MYSHELL                   ***");
  printf("\n***      by Mukesh ,Vivek and Vaibhav         ***");
  printf("\n         %s ",ctime(&t));                                // getting system time
  printf("\n*************************************************\n");
}

char  *builtin_cmds[] = {"cd","help","quit","echo","ls","wc"};  // available commands
/*      cd command to change the current directory              */
int cd_command(char **arg)
{
  if(arg[1] == NULL)
  {
    fprintf(stderr, "myshell_cd_error: expected argument to \"cd\"\n");
  }
  else
  {

   if(chdir(arg[1])!=0) // chdir system call
    perror("myshell_error ");

  }

  return 1;
}
//quit myshell
int quit_command()
{
  return 0;
}
// get help for myshell Commands
int help_command(char **arg)
{
  printf("\n***  WELCOME TO MYSHELL HELP    *** \n*** List of Commands supported:  \n1. cd <directory> \n2. echo <comment>​\n3. ls <directory> \n4. wc <option> <file>  \n5. quit​ \n");

  return 1 ;
}
int myshell_launch(char **arguments)
{
  pid_t pid;
// Executing system commands and libraries by forking a child and calling execvp().
  pid = fork();
  if(arguments[0])
  if (pid == 0) // child process
   {
        if ( execvp(arguments[0], arguments) == -1)
      {
      perror("myshell - execvp_error  ");
       }
     exit(-1);
   }
  else if(pid < 0)   // pid error
   {  perror("myshell_pid_error  ");
  }
   else // parent process waiting for child to complete
   {
       waitpid(pid, NULL, 0);
  }

  return 1;
}
int builtin_cmds_func(char **arr , int i)
{
  switch (i) {
    case 0 : return cd_command(arr);
    case 1 : return help_command(arr);
    case 2 : return  quit_command();
    default :  return myshell_launch(arr);
  }
return 1;
}
/* executing user input commands if available in myshell  */
int myshell_execute(char **arguments)
{
  int i;

  if (arguments[0] == NULL) {
    return 1;
  }

  for (i = 0; i < (sizeof(builtin_cmds) / sizeof(builtin_cmds[0])); i++) {
    if (strcmp(arguments[0], builtin_cmds[i]) == 0) {
      return builtin_cmds_func(arguments,i);                                         // checking for builtin commands
    }
  else if(i==5)                                                                     // error if command doesn't exist
    {
      printf("\nmyshell ERROR : Command Doesn't exist \n **      try help    ** \n" );
    }
  }

  return 1;
}
/*  Reading user input from myshell  */
char *myshell_read_line()
{
  char *user_input = NULL;
  size_t length = 0;
  getline(&user_input, &length, stdin);
  return user_input;
}


#define BUFSIZE 128
#define TOKEN_DELIMATERS " \t\r\n\a"                                              //  delimaters for tokenization
/*  fucntion for splitting user input */
char **myshell_split_line(char *user_input)
{
  int bufsize  = BUFSIZE ;
  int position = 0;
  char **new_tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!new_tokens) {
    fprintf(stderr, "myshell_split_line_new_tokens : allocation error\n");
  exit(-1);
  }

  token = strtok(user_input, TOKEN_DELIMATERS);                                 // tokenizing user input
  while (token != NULL) {
    new_tokens[position] = token;
    position++;
    token = strtok(NULL, TOKEN_DELIMATERS);
    if (position >= bufsize) {
      bufsize += BUFSIZE;
      new_tokens = realloc(new_tokens, bufsize * sizeof(char*));                // reallocation for new_tokens (to provide it more buffer size)
      if (!new_tokens) {
        fprintf(stderr, "myshell_split_line_new_tokens: allocation error\n");
      exit(-1);
      }
    }

  }
  new_tokens[position] = NULL;
  return new_tokens;
}

/*
 a loop for user input function , splitter function , execute function
*/

void myshell_shell_loop()
{
  char *user_input;
  char **arguments;
  int status;

  do {
    char buff[FILENAME_MAX];
    getcwd( buff, FILENAME_MAX );
    printf("myshell: %s $>>",buff);
    user_input = myshell_read_line();
    arguments = myshell_split_line(user_input);
    status = myshell_execute(arguments);

    free(user_input);
    free(arguments);
  } while (status);
}
// cntrl + c (sigint) handler funtion
void sigintHandler(int sig_num)
{
  printf("\n Cannot be terminated using Ctrl+C . Type \"quit\" to exit myshell else press \"ENTER\"  \n");
}
int main()
{
  myshell_shell_started();                                                      // shell intro
  signal(SIGINT, sigintHandler);                                                // handler fucntion for cntrl + c
  myshell_shell_loop();                                                         // looping for various input
  return 0;
}

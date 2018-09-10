************************************************                                    
******************  MYSHELL ********************
************************************************


                        The Basics

After a command is entered, the following things are done:

1. Command is entered and if length is non-null ,continue .
2. Splitting : Splitting is the breaking up of commands into individual words and strings.
3. Checking if built-in commands are asked for .
4. Executing system commands and libraries by forking a child and calling execvp().
5. Printing current directory name and asking for next input.

                        Implementation

For splitting the user input strtok() is used.
For executing cd chdir() function present in <unistd.h> is used.
The exec() system call to launch the specified command like ls, echo and wc.
For remaining commands like quit and help , respective functions are made


List of Commands supported: 
1. cd <directory>      --- to change directory
2. echo <comment>      ​--- to display comment on shell
3. ls <directory>      --- to show the contents of directory
4. wc <option> <file>  --- show the word count in file
5. quit​                --- to quit myshell

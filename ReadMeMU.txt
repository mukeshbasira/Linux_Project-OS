Team Members
 
1. Vivek Pratap Deo 2016A7PS0056H
2. Mukesh 2016A7PS0116H
3. Vaibhav Tyagi 2016A7PS0141H     



         ************************************************
              ******************  MYSHELL ********************
              ************************************************

Question 1
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
********************************************************************************

Question 2
Used __do_fork system call to create a custom call for fork. To add
the system call to the kernel we used asmlinker for x64. Further to removed the
need to memorize the call number we created a wrapper function of the same name
to achieve similar functionality.

********************************************************************************

Question 3
We use to pipe to communicate between the parent and child process.
And used wait in child and sleep in parent to get the requested delay so that
the execution of one remains un-interrupted.
The Programs might revisit the same number multiple times but will stop once all
number are visited.

********************************************************************************
Question 4
We are using fork() command to create child process,execlp() commands to get top
process in a sorted order and using the child process to print it.
After r iteration the control goes to parent process which ask the user to
input process id which the child needs to kill. This id is passed to child process
and child process used kill command to kill the process.

********************************************************************************

Question 5

We created child using fork. The child executed grep command to match the pattern
the output is then delimited using cut command. And finally the parent receives
the output using pipe and displays it.

Commands for adding newgrep into bash are in the Answer file itself

# Shell-Command-Execution-Simulation

Variable Choices

For command choice I went with grep because I spent so long trying to understand how grep worksI
thought I should print it. The full command is man grep | grep -e -A -A 2 -m 2. This command prints
out a few lines where manual explains exactly how grep function outputs. -e and -A are for finding
the part of the manual where I wanted to output and -A 2, -m 2 are the limitations of the output such
as number of lines etc. -A 2 print 2 lines and -m is the function that makes the program stop reading
after a certain number of words. output.txtwas given with the hw pdf and it is the output
destination.

Process hierarchy

I created 2 childs for the SHELL process. Created a file descriptor array with 2 elements for piping.
Then I created a rc variable like in the recitations and used fork on it to begin the manual procedure.
Checked if rc < 0 to see if fork failed. If successful, start executing with execlp command. I used
execlp here because I tried the other execs(execl, execv, execvp, execvpe etc) and they execlp was
the only one that worked since I had a const char* file and lots of arguments. The other exec
functions didn’t take that many arguments. Dup2allocates a file descriptor that refers to filedesc[1]
and writes to it. After man procedure, I initialized another rc and forked it and did the same
processes for grep child process this time. Output.txt is created , output from man is taken to reading
part of the pipe and grep’s process is printed out to output.txt. Lastly the childs wait and program
ends.

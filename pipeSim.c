#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

//Anil Ozan Ayhan PA1 CS 307
int main(){
// first cout statement explaining the program
    printf("I'm SHELL process, with PID: %d - Main command is: man grep | grep -e -A -A 2 -m 2 \n", getpid());
   
    // pipe the fds and make a child fork rc1
    int fd[2];
    pipe(fd);
    int rc1 = fork();

    if (rc1 < 0){
        exit(1);
    }
    else if (rc1 == 0){
        printf("I’m MAN process, with PID: %d - My command is: man grep \n", getpid());

        dup2(fd[1], STDOUT_FILENO);
        //the only exec command that works is execlp since i use -m 2 as well
        //as -a 2
        //and execlp takes 2 const char* and all the other arguments
        //execl,execle,execv,execvp and execvpe dont work
        execlp("man", "man", "grep", NULL);
    }
    else{

        //another child but this time for grep
        int rc2 = fork();
       
        if (rc2 < 0){
            exit(1);
        }
        else if (rc2 == 0){
            printf("I’m GREP process, with PID: %d - My command is: grep -e -A -A 2 -m 2 \n", getpid());

            //o creat == if output.txt doesnt exits, create it
            //o wronly == write only mode
            //s irusr and s iwusr read and write permissions from owner(me)
            int filefd = open("output.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
   
            dup2(fd[0], STDIN_FILENO);
            // output the grep into txt
            dup2(filefd, STDOUT_FILENO);
            execlp("grep", "grep", "-e", "-A", "-A", "2", "-m", "2", NULL);
        }
        else{
            //until child is done, wait
            waitpid(rc1, NULL, 0);
            waitpid(rc2, NULL, 0);            
            printf("I’m SHELL process, with PID: %d - execution is completed, you can find the results in output.txt ", getpid());
        }
    }
    return 0;
}
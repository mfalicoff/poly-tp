#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

int main() {
    int fd[2];
    int origal= dup(1);

    if(fork() == 0)//fils 2
    {
        pipe(fd);
        int tempFile2 = open( "Out.txt" , O_WRONLY | O_CREAT | O_TRUNC, 0660);
        
        if(fork() == 0) //fils 1)
        {   
            close(fd[0]);
            dup2(fd[1], 1);
            execlp("rev", "rev", "In.txt", NULL);
            close(fd[1]);
        }
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        dup2(tempFile2, 1);
        execlp("rev", "rev",NULL);
    }
    wait(NULL);
    dup2(origal, STDOUT_FILENO);
    if(fork()==0)
    {
        execlp("diff", "diff", "In.txt", "Out.txt", "-s", NULL);
    
    }
    return 0;    
}
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
    mkfifo("tubeA", 0660);

    if(fork() == 0)//fils 2
    {
        //pipe(fd);
        int tempFile2 = open( "Outn.txt" , O_WRONLY | O_CREAT | O_TRUNC, 0660);
        
        if(fork() == 0) //fils 1)
        {   
            int f1= open("tubeA", O_WRONLY);
            dup2(f1, 1);
            execlp("rev", "rev", "In.txt", NULL);
        }
        int f2 = open("tubeA", O_RDONLY);
        dup2(f2, 0);
        dup2(tempFile2, 1);
        execlp("rev", "rev",NULL);
    }
    wait(NULL);
    dup2(origal, STDOUT_FILENO);
    if(fork()==0)
    {
        execlp("diff", "diff", "In.txt", "Outn.txt", "-s", NULL);
    
    }
    return 0;    
}
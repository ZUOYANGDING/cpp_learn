#include <iostream>
#include "../apue.h"
#include <sys/wait.h>

void sig_int(int sig) {
    std::cout<< "interrupt signal is: "<<  sig << std::endl;
}

int main(void) {
    char buff[MAXLINE];
    pid_t pid;
    int status;
    
    if (signal(SIGINT, sig_int) == SIG_ERR) {
        std::cout<< "signal error" <<std::endl;
    }

    std::cout<< "%% ";
    while (fgets(buff, MAXLINE, stdin)!=NULL) {
        if (buff[strlen(buff)-1] == '\n') {
            buff[strlen(buff)-1] = 0;
        }
        if ((pid = fork()) < 0) {
            std::cout<< "error fork" <<std::endl;
        } else if (pid == 0) {
            // child process
            execlp(buff, buff, (char *) 0);
            std::cout<< "cannot execute: " << buff <<std::endl;
            exit(127);
        }
        
        // parent process
        if ((pid=waitpid(pid, &status, 0))<0) {
            std::cout<< "waitpid error" <<std::endl;
        }
        std::cout<<"%% ";
    }
    exit(0);
}
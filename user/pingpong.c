// user/pingpong.c

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int pipeIn[2];
    int pipeOut[2];
    if(pipe(pipeIn)<0){
        fprintf(2, "failed to create pipe");
        exit(1);
    }
    if(pipe(pipeOut)<0){
        fprintf(2, "failed to create pipe");
        exit(1);
    }

    int pid = fork();
    if (pid == 0){
        // child process
        close(pipeIn[1]);
        close(pipeOut[0]);

        // wait buf from parent
        char buf[512];
        read(pipeIn[0], buf, 1);

        // display output
        int childPIP = getpid();
        printf("%d: received ping\n", childPIP);

        // return
        write(pipeOut[1], "pong", 1);
        exit(0);
    }else if (pid > 1){
        // parent process
        // the parent process closes the read fd on pipeIn,
        // and the write fd on pipeOut
        close(pipeIn[0]);
        close(pipeOut[1]);
        
        write(pipeIn[1], "ping", 1);
        // wait buf from parent
        char buf[512];
        read(pipeOut[0], buf, 1);
        int parentPID = getpid();
        printf("%d: received pong\n", parentPID);
        exit(0);
    }else{
        printf("failed to fork");
        exit(1);
    }
}

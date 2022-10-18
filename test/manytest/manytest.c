#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thread_fun(void *arg);

int main(void) {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_fun, NULL);
    pthread_join(thread, NULL);
    return 0;
}

void *thread_fun(void *arg) {
    pid_t pid = fork();
    if(pid) {
        printf("hi\n");
        waitpid(pid, NULL, 0);
        pthread_exit(NULL);
    } else {
        printf("hi\n");
        exit(0);
    }
}

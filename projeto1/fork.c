#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void trata_SIGALRM(int signum) {
    printf("[%d -> %d] Ai que sono! Queria dormir mais...\n", getpid(), getppid());
    exit(0);
}

void sighandler(int signum) {
   printf("Caught signal %d, coming out...\n", signum);
//   exit(0);
}

int main() {
    int pid;

    signal(SIGINT, sighandler);

    printf("[%d -> %d] born\n", getpid(), getppid());
    fflush(stdout);

    pid = fork();
    if (pid != 0) {
        printf("[%d -> %d] born\n", pid, getpid());
        fflush(stdout);

//    sleep(10);
        signal(SIGALRM, trata_SIGALRM); /* Instala¸c~ao do tratador de sinal */
        pause(); /* Pai espera ser acordado pelo filho */
    } else {
        printf("[%d -> %d] kill\n", getpid(), getppid());
        fflush(stdout);

        kill(getppid(), SIGALRM); /* Filho envia sinal para acordar o pai */
    }

    printf("[%d -> %d] end\n", getpid(), getppid());

    return 0;
}

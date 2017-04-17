#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void trata_SIGALRM(int signum) {
    printf("[%d] Ai que sono! Queria dormir mais...\n", getppid());
}

void sighandler(int signum) {
   printf("Caught signal %d, coming out...\n", signum);
//   exit(0);
}

int main() {
    int pid;

    signal(SIGINT, sighandler);

    printf("[%d] born\n", getppid());
    fflush(stdout);

    pid = fork();
    if (pid != 0) {
        printf("[%d] born\n", pid);
        fflush(stdout);

        signal(SIGALRM, trata_SIGALRM); /* Instala¸c~ao do tratador de sinal */
        pause(); /* Pai espera ser acordado pelo filho */
    } else {
        printf("[%d] kill\n", getppid());
        fflush(stdout);

        kill(getppid(), SIGALRM); /* Filho envia sinal para acordar o pai */
    }

    printf("[%d] end\n", getppid());

    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
  pid_t P, P_A, P_B, P_C;

  P = getpid();
  P_A = fork();
  if (P_A == 0)
  {
    printf("\nSou P_A com PID %d, filho de PID %d\n", getpid(), P);
    P_B = fork();
    if (P_B == 0)
    {
      printf("Eu P_A criei P_B!\n");
      printf("Sou P_B com PID %d, PID interno %d, filho do PID %d\n", getpid(), P_B, getppid());
      P_C = fork();
      if (P_C == 0)
      {
        printf("Eu P_B criei P_C!\n");
        printf("Sou P_C com PID %d, PID interno %d, filho do PID %d\n", getpid(), P_B, getppid());
        printf("Eu P_C executei: ps\n", name);
        execl("/bin/ps", "ps", "l", NULL);
      }
      wait(NULL);
      printf("Eu P_B aguardei o P_C terminar!\n");
      printf("Eu P_B executei: ps\n", name);
      execl("/bin/ps", "ps", "l", NULL);
    }
    wait(NULL);
    printf("Eu P_A aguardei o P_B terminar!\n");
    printf("Eu P_A executei: ps\n", name);
    execl("/bin/ps", "ps", "l", NULL);
  }
  exit(0);
}
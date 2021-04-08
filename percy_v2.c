#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define READ_END 0
#define WRITE_END 1

static int flag = 0;

void confirma_saida2(int sig)
{
  flag = 1;
}

int main()
{
  char tecla, c;
  pid_t pid;
  int fd[2];
  int fd2[2];

  signal(SIGINT, confirma_saida2);
  printf("**Bem vindo ao perseverance**\n");

  if (pipe(fd) == -1)
  {
    fprintf(stderr, "Pipe failed");
    return 1;
  }

  if (pipe(fd2) == -1)
  {
    fprintf(stderr, "Pipe failed");
    return 1;
  }

  while (1)
  {
    printf("perseverance@MAIN$ \"MAIN PID %d - Navegação exitosa\"\n", getpid());
    sleep(1);

    if (flag == 1)
    {
      flag = 0;

      printf("perseverance@TELEOPERACAO$ ");
      tecla = getchar();

      if (tecla == 'w')
      {
        pid = fork();
        if (pid < 0)
        {
          fprintf(stderr, "Fork failed");
          return 1;
        }

        if (pid > 0)
        {
          int read_msg;
          close(fd[WRITE_END]);
          read(fd[READ_END], &read_msg, sizeof(read_msg));
          close(fd[READ_END]);

          printf("perseverance@MAIN$ MAIN PID %d Criando  SUBSYS1 %d\n", getpid(), read_msg);

          printf("perseverance@SUBSYS1$ \"SUBSYS PID %d - MOTORES a frente\"\n", read_msg);
          sleep(2);
          printf("perseverance@SUBSYS1$ \"SUBSYS PID %d \"", read_msg);
          execlp("pstree", "pstree", "-p", (int *)NULL);

          sleep(2);
          printf("perseverance@MAIN$ \"MAIN PID %d - SUBSYS PID %d terminou\"\n", getpid(), read_msg);
          sleep(1);
          wait(NULL);
        }
        else if (pid == 0)
        {
          close(fd[READ_END]);

          int write_msg = getpid();

          write(fd[WRITE_END], &write_msg, sizeof(write_msg));
          close(fd[WRITE_END]);
          exit(0);
        }
      }
      else if (tecla == 's')
      {
        int read_msg;

        pid = fork();
        if (pid < 0)
        {
          printf("Erro");
        }

        if (pid == 0)
        {
          close(fd2[READ_END]);

          int write_msg = getpid();

          write(fd2[WRITE_END], &write_msg, sizeof(write_msg));
          close(fd2[WRITE_END]);
          exit(0);
        }
        else if (pid > 0)
        {
          FILE *pont_alfa;
          int bufferLength = 255;
          char buffer[bufferLength];

          close(fd2[WRITE_END]);
          read(fd2[READ_END], &read_msg, sizeof(read_msg));

          printf("perseverance@MAIN$ \"MAIN PID %d - Criando  SUBSYS2 PID %d\"\n", getpid(), read_msg);
          sleep(1);
          printf("perseverance@SUBSYS2$ \"SUBSYS2 PID %d - CAMERA iniciou\"\n", read_msg);
          sleep(1);
          printf("perseverance@SUBSYS2$ \"SUBSYS2 PID %d - Enviando foto de Marte\"\n", read_msg);
          sleep(1);
          pont_alfa = fopen("mars-photo.bag", "r");
          if (pont_alfa == NULL)
          {
            printf("Erro na abertura do arquivo!");
            return 1;
          }
          else
          {
            while (fgets(buffer, bufferLength, pont_alfa))
            {
              printf("%s", buffer);
              sleep(1);
            }
          }
          sleep(1);
          fclose(pont_alfa);
          printf("perseverance@SUBSYS2$ \"SUBSYS2 PID %d - Foto enviada com sucesso\"\n", read_msg);
          wait(NULL);
        }
        sleep(1);
        printf("perseverance@MAIN$ \"MAIN PID %d SUBSYS2 PID %d terminou\"\n", getpid(), read_msg);
        close(fd2[READ_END]);
        sleep(1);
      }
      else if (tecla == 'a')
      {
        printf("perseverance@MAIN$ \"MAIN PID %d - Processos em execucao\"\n", getpid());
        sleep(2);
        system("ps -ef");
        exit(0);
      }
      else if (tecla == 'd')
      {
        printf("perseverance@MAIN$ \"MAIN PID %d - Abortando missao...\"\n", getpid());
        exit(0);
      }
      else
      {
        printf("perseverance@MAIN$ \"MAIN PID %d - comando inválido\"\n", getpid());
        sleep(1);
      }
      wait(NULL);
    }
  }

  return 0;
}
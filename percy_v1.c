#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

static int flag = 0;

void confirma_saida2(int sig)
{
  flag = 1;
}

int main()
{
  char tecla, c;
  pid_t pid;

  signal(SIGINT, confirma_saida2);
  printf("Bem vindo ao perseverance\n");

  while (1)
  {
    printf("perseverance@MAIN$ \"MAIN - Navegação exitosa\"\n");
    sleep(1);

    if (flag == 1)
    {
      flag = 0;

      printf("perseverance@TELEOPERACAO$ ");
      tecla = getchar();

      if (tecla == 'w')
      {
        printf("perseverance@MAIN$ Criando SUBSYS1\n");
        sleep(1);
        pid = fork();
        if (pid < 0)
        {
          fprintf(stderr, "Fork failed");
          return 1;
        }
        else if (pid == 0)
        {
          printf("perseverance@SUBSYS1$ MOTORES a frente\n");
          sleep(2);
          printf("perseverance@SUBSYS1$");
          execlp("pstree", "pstree", "-p", (int *)NULL);
          exit(0);
        }
        else if (pid > 0)
        {
          wait(NULL);
          sleep(2);
          printf("perseverance@SUBSYS1$ SUBSYS1 terminou\n");
          sleep(1);
        }
      }
      else if (tecla == 's')
      {
        printf("perseverance@SUBSYS2$ Criando SUBSYS2\n");
        sleep(1);
        pid = fork();
        if (pid < 0)
        {
          fprintf(stderr, "Fork failed");
          return 1;
        }
        else if (pid == 0)
        {
          FILE *pont_alfa;
          int bufferLength = 255;
          char buffer[bufferLength];

          printf("perseverance@SUBSYS2$ CAMERA iniciou\n");
          sleep(1);
          printf("perseverance@SUBSYS2$ Enviando foto de Marte\n");
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
          printf("perseverance@SUBSYS2$ Foto enviada com sucesso\n");
          exit(0);
        }
        else if (pid > 0)
        {
          wait(NULL);
        }
        sleep(1);
        printf("perseverance@SUBSYS2$ SUBSYS2 terminou\n");
        sleep(1);
      }
      else if (tecla == 'a')
      {
        printf("perseverance@MAIN$ Processos em execucao\n");
        sleep(2);
        system("ps -ef");
        exit(0);
      }
      else if (tecla == 'd')
      {
        printf("perseverance@MAIN$ Abortando missao...\n");
        exit(0);
      }
      else
      {
        printf("perseverance@MAIN$ Comando invalido\n");
        sleep(1);
      }
      wait(NULL);
    }
  }

  return 0;
}